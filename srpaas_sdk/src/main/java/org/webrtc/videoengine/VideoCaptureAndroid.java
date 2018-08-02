/*
 *  Copyright (c) 2012 The WebRTC project authors. All Rights Reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */

package org.webrtc.videoengine;

import java.io.IOException;
import java.util.List;
import java.util.Locale;
import java.util.concurrent.locks.ReentrantLock;

import org.webrtc.videoengine.CaptureCapabilityAndroid;
import org.webrtc.videoengine.VideoCaptureDeviceInfoAndroid.AndroidVideoCaptureDevice;

import android.annotation.SuppressLint;
import android.graphics.ImageFormat;
import android.graphics.PixelFormat;
import android.graphics.Rect;
import android.graphics.YuvImage;
import android.hardware.Camera;
import android.hardware.Camera.Parameters;
import android.hardware.Camera.PreviewCallback;
import android.util.Log;
import android.view.SurfaceHolder;
import android.view.SurfaceHolder.Callback;

public class VideoCaptureAndroid implements PreviewCallback, Callback {

	private final static String TAG = "WEBRTC-JC";

	private Camera camera;
	private AndroidVideoCaptureDevice currentDevice = null;
	public ReentrantLock previewBufferLock = new ReentrantLock();
	// This lock takes sync with StartCapture and SurfaceChanged
	private ReentrantLock captureLock = new ReentrantLock();
	private int PIXEL_FORMAT = ImageFormat.NV21;
	PixelFormat pixelFormat = new PixelFormat();
	// True when the C++ layer has ordered the camera to be started.
	private boolean isCaptureStarted = false;
	private boolean isCaptureRunning = false;
	private boolean isSurfaceReady = false;

	private final int numCaptureBuffers = 3;
	private int expectedFrameSize = 0;
	private int orientation = 0;
	private int id = 0;
	// C++ callback context variable.
	private long context = 0;
	private SurfaceHolder localPreview = null;
	// True if this class owns the preview video buffers.
	private boolean ownsBuffers = false;

	private int mCaptureWidth = -1;
	private int mCaptureHeight = -1;
	private int mCaptureFPS = -1;

	public static void DeleteVideoCaptureAndroid(
			VideoCaptureAndroid captureAndroid) {
		if (captureAndroid.camera == null) {
			return;
		}

		captureAndroid.StopCapture();
		captureAndroid.camera.release();
		captureAndroid.camera = null;
		captureAndroid.context = 0;
	}

	public VideoCaptureAndroid(int in_id, long in_context, Camera in_camera,
			AndroidVideoCaptureDevice in_device) {
		id = in_id;
		context = in_context;
		// camera = in_camera;
		currentDevice = in_device;
	}

	private static int[] findClosestEnclosingFpsRange(int expectedFps,
			List<int[]> fpsRanges) {
		Log.d(TAG, "Searching for closest fps range from " + expectedFps);
		if (fpsRanges == null || fpsRanges.size() == 0) {
			return new int[] { 0, 0 };
		}

		// init with first element
		int[] closestRange = fpsRanges.get(0);
		int measure = Math.abs(closestRange[0] - expectedFps)
				+ Math.abs(closestRange[1] - expectedFps);
		Log.d(TAG, "closestRange[0]:===" + closestRange[0]
				+ "closestRange[1]==" + closestRange[1]);
		Log.d(TAG, "measure:===" + measure);
		for (int[] curRange : fpsRanges) {
			if (curRange[0] > expectedFps || curRange[1] < expectedFps)
				continue;
			int curMeasure = Math.abs(curRange[0] - expectedFps)
					+ Math.abs(curRange[1] - expectedFps);
			Log.d(TAG, "curRange[0]:===" + curRange[0] + "curRange[1]=="
					+ curRange[1]);
			Log.d(TAG, "curMeasure:===" + curMeasure);
			if (curMeasure < measure) {
				closestRange = curRange;
				measure = curMeasure;
				Log.d(TAG, "a better range has been found: w="
						+ closestRange[0] + ",h=" + closestRange[1]);
			}
		}
		Log.d(TAG, "The closest fps range is w=" + closestRange[0] + ",h="
				+ closestRange[1]);
		return closestRange;
	}

	@SuppressLint("NewApi")
	private int tryStartCapture(int width, int height, int frameRate) {
		if (camera == null /* || Configure.mCurrentCamera==null */) {
			Log.e(TAG, "Camera not initialized %d" + currentDevice.index);
			return -1;
		}

		// Log.d(TAG, "VideoCaptureAndroid......tryStartCapture: " + width + "x"
		// + height + ", frameRate: " + frameRate + ", isCaptureRunning: "
		// + isCaptureRunning + ", isSurfaceReady: " + isSurfaceReady
		// + ", isCaptureStarted: " + isCaptureStarted);

		if (isCaptureRunning || !isCaptureStarted) {
			return 0;
		}

		CaptureCapabilityAndroid currentCapability = new CaptureCapabilityAndroid();
		currentCapability.width = width;
		currentCapability.height = height;
		currentCapability.maxFPS = frameRate;
		PixelFormat.getPixelFormatInfo(PIXEL_FORMAT, pixelFormat);
		Parameters parameters = camera.getParameters();
		Log.d(TAG, "videoChatActivity.........getParameters: 11111..."+currentCapability.width+"...."+currentCapability.height);
		parameters.setPreviewSize(currentCapability.width,
				currentCapability.height);
		parameters.setPreviewFormat(PIXEL_FORMAT);
		// parameters.setPreviewFrameRate(currentCapability.maxFPS);
		// by cl.zhan from linphone
		int[] chosenFps = findClosestEnclosingFpsRange(30 * 1000,
				parameters.getSupportedPreviewFpsRange()); // 期望帧数增加到30帧
		parameters.setPreviewFpsRange(chosenFps[0], chosenFps[1]);

		if (parameters.isAutoWhiteBalanceLockSupported()) {
			parameters.setWhiteBalance(Parameters.WHITE_BALANCE_AUTO); // 设置白平衡自动
		}

		// 场景
		// parameters.setSceneMode(Parameters.SCENE_MODE_PORTRAIT); //人物图片

		// if(parameters.isZoomSupported())
		// {
		//
		// }

		camera.setParameters(parameters);
//		if (Configure.mCurrentCamera != null
//				&& Configure.mCurrentCamera.contains("front")) {
//			// 前相机
//			// Log.i(TAG, "cameraa......"+Configure.cameraDegrees);
//			int degree = 0;
//			switch (Configure.cameraDegrees) {
//			case 0:
//				degree = 90;
//				break;
//			case 90:
//				degree = 180;//
//				break;
//			case 180:
//				degree = 270;
//				break;
//			case 270:
//				degree = 0;
//				break;
//
//			default:
//				break;
//			}
//			// Log.e("", "cameraa........."+degree);
//			camera.setDisplayOrientation(degree);
//		} else {
//			camera.setDisplayOrientation(0);
//		}

		int bufSize = width * height * pixelFormat.bitsPerPixel / 8;
		byte[] buffer = null;
		for (int i = 0; i < numCaptureBuffers; i++) {
			buffer = new byte[bufSize];
			camera.addCallbackBuffer(buffer);
		}
		camera.setPreviewCallbackWithBuffer(this);
		ownsBuffers = true;

		camera.startPreview();
		previewBufferLock.lock();
		expectedFrameSize = bufSize;
		isCaptureRunning = true;
		previewBufferLock.unlock();

		isCaptureRunning = true;
		return 0;
	}

	@SuppressLint("NewApi")
	public int StartCapture(int width, int height, int frameRate) {
		// Get the local preview SurfaceHolder from the static render class
		int res = 0;
		try {
			Log.i(TAG, "videoChatActivity........StartCapture");

			captureLock.lock();
			if (camera != null) {
				Log.i(TAG, "Camera........StartCapture error");
			}

			camera = Camera.open(currentDevice.index);
			if (camera == null) {
				Log.i(TAG, "Camera........StartCapture open camera error!");
				captureLock.unlock();
				return -1;
			}

			localPreview = ViERenderer.GetLocalRenderer();
			if (localPreview != null) {
				if (localPreview.getSurface() != null) {
					surfaceCreated(localPreview);
				}
				localPreview.addCallback(this);
			}

			// captureLock.lock();
			isCaptureStarted = true;
			mCaptureWidth = width;
			mCaptureHeight = height;
			mCaptureFPS = frameRate;

			res = tryStartCapture(mCaptureWidth, mCaptureHeight, mCaptureFPS);

			captureLock.unlock();
		} catch (Exception e) {
			e.printStackTrace();
		}
		return res;

	}

	public int StopCapture() {

		try {
			if (camera != null) {
				previewBufferLock.lock();
				isCaptureRunning = false;
				previewBufferLock.unlock();
				camera.stopPreview();
				camera.setPreviewCallbackWithBuffer(null);
				camera.release();
				camera = null;
			}
		} catch (RuntimeException e) {
			Log.e(TAG, "Failed to stop camera", e);
			return -1;
		}

		isCaptureStarted = false;
		return 0;
	}

	native void ProvideCameraFrame(byte[] data, int length, long captureObject);

	public void onPreviewFrame(byte[] data, Camera camera) {
		previewBufferLock.lock();
		// Log.d("wxh---", "wxh------onPreviewFrame()");
		// The following line is for debug only
		// Log.v(TAG, "VideoCaptureAndroid.....175.... " + data.length +
		// " context" + context);
		if (isCaptureRunning) {
			// If StartCapture has been called but not StopCapture
			// Call the C++ layer with the captured frame
			if (data.length == expectedFrameSize) {
				ProvideCameraFrame(data, expectedFrameSize, context);
				if (ownsBuffers) {
					// Give the video buffer to the camera service again.
					camera.addCallbackBuffer(data);
				}
			}
		}
		previewBufferLock.unlock();
	}

	// Sets the rotation of the preview render window.
	// Does not affect the captured video image.
	public void SetPreviewRotation(int rotation) {
		Log.e(TAG, "SetPreviewRotation.........!");
		if (camera != null) {
			previewBufferLock.lock();
			int width = 0;
			int height = 0;
			int framerate = 0;

//			if (isCaptureRunning) {
//				width = mCaptureWidth;
//				height = mCaptureHeight;
//				framerate = mCaptureFPS;
//				StopCapture();
//			}

			int resultRotation = 0;
			if (currentDevice.frontCameraType == VideoCaptureDeviceInfoAndroid.FrontFacingCameraType.Android23) {
				// this is a 2.3 or later front facing camera.
				// SetDisplayOrientation will flip the image horizontally
				// before doing the rotation.
				resultRotation = (360 - rotation) % 360; // compensate the
															// mirror
			} else {
				// Back facing or 2.2 or previous front camera
				resultRotation = rotation;
			}
			camera.setDisplayOrientation(resultRotation);

//			if (isCaptureRunning) {
//				StartCapture(width, height, framerate);
//			}
			previewBufferLock.unlock();
		}
	}

	public void surfaceChanged(SurfaceHolder holder, int format, int width,
			int height) {
	}

	public void surfaceCreated(SurfaceHolder holder) {
		captureLock.lock();
		if (camera != null) {
			try {
				camera.setPreviewDisplay(holder);
			} catch (IOException e) {
				StopCapture();
				StartCapture(mCaptureWidth, mCaptureHeight, mCaptureFPS);
				try {
					camera.setPreviewDisplay(localPreview);
				} catch (IOException e1) {
					e1.printStackTrace();
				}
				Log.e(TAG, "Failed to set preview surface!", e);
			}
		} else {
			Log.d("wxh-------------", "wxh------camera is null !!!!!!!");
		}
		captureLock.unlock();
	}

	public void surfaceDestroyed(SurfaceHolder holder) {
		try {
			if (camera != null)
				camera.stopPreview();
		} catch (Exception e) {
			e.printStackTrace();
		}
		// captureLock.lock();
		// if (camera != null) {
		// try {
		// camera.setPreviewDisplay(null);
		// } catch (IOException e) {
		// Log.e(TAG, "Failed to clear preview surface!", e);
		// }
		// }
		// captureLock.unlock();
	}
}
