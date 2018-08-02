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


import android.content.Context;
import android.util.Log;
import android.view.SurfaceHolder;
import android.view.SurfaceView;

public class ViERenderer {

    // View used for local rendering that Cameras can use for Video Overlay.
    private static SurfaceHolder g_localRenderer;

    public static SurfaceView CreateRenderer(Context context) {
        return CreateRenderer(context, false,false);
    }

    public static SurfaceView CreateRenderer(Context context,
            boolean useOpenGLES2,boolean isVideo) {
//        if(useOpenGLES2 == true && ViEAndroidGLES20.IsSupported(context)){
//        	Log.i("", "videoChatActivity.....CreateRenderer....111");
////            return new ViEAndroidGLES20(context);
//        	if(isVideo){
//        		return new ViEAndroidGLES20(context);
//        	}else{
//        		return new GLDragView(context);
//        	}
//        }else{
//        	Log.i("", "videoChatActivity.....CreateRenderer....222");
        		return new SurfaceView(context);
//        }
    }

    // Creates a SurfaceView to be used by Android Camera
    // service to display a local preview.
    // This needs to be used on Android prior to version 2.1
    // in order to run the camera.
    // Call this function before ViECapture::StartCapture.
    // The created view needs to be added to a visible layout
    // after a camera has been allocated
    // (with the call ViECapture::AllocateCaptureDevice).
    // IE.
    // CreateLocalRenderer
    // ViECapture::AllocateCaptureDevice
    // LinearLayout.addview
    // ViECapture::StartCapture
    public static SurfaceView CreateLocalRenderer(Context context)  {
//    	Log.i("", "Raycom....videoChatActivity.VideoCaptureAndroid....2222222");
        SurfaceView localRender = new SurfaceView(context);
        g_localRenderer = localRender.getHolder();
        g_localRenderer.setType(SurfaceHolder.SURFACE_TYPE_PUSH_BUFFERS);
        return localRender;
    }
    

    public static SurfaceHolder GetLocalRenderer() {
//     	Log.i("", "Raycom....videoChatActivity.VideoCaptureAndroid.111...111111");
        return g_localRenderer;
    }

}
