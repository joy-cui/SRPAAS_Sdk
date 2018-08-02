package org.webrtc.videoengine;

//hard  decode
//is for debug only

import java.io.IOException;
import java.nio.ByteBuffer;
import java.util.concurrent.locks.ReentrantLock;


import android.annotation.TargetApi;
import android.media.MediaCodec;
import android.media.MediaFormat;
import android.media.MediaCodec.BufferInfo;
import android.os.Build;
import android.util.Log;
import android.view.Surface;
import android.view.SurfaceHolder;
import android.view.SurfaceHolder.Callback;
import android.view.SurfaceView;

@TargetApi(Build.VERSION_CODES.JELLY_BEAN)
public class HardDecodeSurfaceRender implements Callback {

	private final static String TAG = "WEBRTC";

	// the bitmap used for drawing.

	private ByteBuffer byteBuffer = null;
	private SurfaceHolder surfaceHolder = null;
	private Surface surfacedecode = null;

	// -------------------硬解添加--------

	private MediaCodec decoder = null;

	private boolean decode_ready = false; // 解码器是否准备OK
	private boolean isDestroyed = false; // 用来对于Destroyed进行防治

	private final String MIME_TYPE = "video/avc"; // H.264 Advanced Video Coding
	private MediaFormat format = null;
	private ByteBuffer[] inputBuffers = null;
	private ByteBuffer[] outputBuffers = null;

	private int sps_start = 0;
	private int pps_start = 0;
	private int i_start = 0;

	private int Video_width = 0;
	private int Video_height = 0;

	private static BufferInfo info = null;

	private ReentrantLock nativeFunctionLock = new ReentrantLock();

	public HardDecodeSurfaceRender() {

	}

	public HardDecodeSurfaceRender(SurfaceView view) {

		Log.d(TAG,
				"HardDecodeSurfaceRender..HardDecodeSurfaceRender::HardDecodeSurfaceRender1");

		surfaceHolder = view.getHolder();
		if (surfaceHolder == null)
			return;

		surfacedecode = surfaceHolder.getSurface();
		surfaceHolder.addCallback(this);
//		Configure.isChange = true; //by 9.30
//		Configure.isChanging = true;
		Log.d(TAG,
				"HardDecodeSurfaceRender..HardDecodeSurfaceRender::HardDecodeSurfaceRender2");
	}

	public void surfaceChanged(SurfaceHolder holder, int format, int in_width,
			int in_height) {

	}

	public void surfaceCreated(SurfaceHolder holder) {
		nativeFunctionLock.lock();
		Log.d(TAG,
				"HardDecodeSurfaceRender..HardDecodeSurfaceRender::surfaceCreated");
		if (null == byteBuffer) {
			byteBuffer = ByteBuffer.allocateDirect(409800); // 40k
		}
		if (null == info) {
			info = new BufferInfo();
		}
		
		isDestroyed = false;
		decode_ready = false;
		sps_start = 0;
		pps_start = 0;
		i_start = 0;
		Video_width = 0;
		Video_height = 0;
		nativeFunctionLock.unlock();

	}

	public void surfaceDestroyed(SurfaceHolder holder) {
		Log.d(TAG, "HardDecodeSurfaceRender..::surfaceDestroyed");
		nativeFunctionLock.lock();
		
		decode_ready = false;
		isDestroyed = true;

		byteBuffer = null;
		info = null;
		

		sps_start = 0;
		pps_start = 0;
		i_start = 0;
		Video_width = 0;
		Video_height = 0;
		if (decoder != null) {
			decoder.stop();
			decoder.release();
			decoder = null;
		}

		Log.d(TAG, "surfaceDestroyed------122----end!");
		nativeFunctionLock.unlock();

	}

	public ByteBuffer CreateByteBuffer() {
		if (null == byteBuffer) {
			byteBuffer = ByteBuffer.allocateDirect(409800); // 40k
		}
		if (null == info) {
			info = new BufferInfo();
		}

		return byteBuffer;
	}

	public int DrawNalBufInterface(int len) {
		int ret = 0;
		
//		if(Configure.MeetChatDoubleStreamCome)
//		{
//			return 0;
//		}
//		if (Configure.MeetChatStop) 
//		{			
//			return 0;
//		}
//		if (len <= 0) 
//		{
//			return -1;
//		}
//		try
//		{
//			if (byteBuffer != null && byteBuffer.hasArray()) {
//				byteBuffer.rewind();
//				ret = DrawNalBuf(byteBuffer.array(), len);
//			}
//		}catch (Exception e) {
//			e.printStackTrace();
//			return -1;
//		}
		return ret;
	}

	public int WH_Change_And_ParseInitialize(byte[] data, int len) {
//
//		if (null == info) {
//			return -1;
//		}
//		if (null == byteBuffer) {
//			return -1;
//		}
//
//		boolean hasSps = false;
//		boolean hasPps = false;
//		int i = 0;
//		int sps_len = 0;
//
//		int pps_len = 0;
//		int pps_header = 0;
//
//		sps_start = 0;
//		pps_start = 0;
//		i_start = len;
//		// find sps pps where
//		while (i < len) {
//			if (!hasSps) {
//				if ((data[i] == 0x00) && (data[i + 1] == 0x00)
//						&& (data[i + 2] == 0x00) && (data[i + 3] == 0x01)
//						&& ((data[i + 4] & 0X1F) == 0x07)) {
//					sps_start = i;
//					hasSps = true;
//					Log.d(TAG, "Has sps !");
//
//					i += 5;
//					continue;
//				}
//			}
//
//			if (!hasPps && hasSps) {
//				if ((data[i] == 0x00) && (data[i + 1] == 0x00)
//						&& (data[i + 2] == 0x01) && ((data[i + 3] & 0x1F)== 0x08)) {
//					hasPps = true;
//					pps_start = i;
//					pps_header = 3;
//					Log.d(TAG, "Has Pps !");
//
//					i += 4;
//					continue;
//				} else if ((data[i] == 0x00) && (data[i + 1] == 0x00)
//						&& (data[i + 2] == 0x00) && (data[i + 3] == 0x01)
//						&& ((data[i + 4] & 0X1F) == 0x08)) {
//					hasPps = true;
//					pps_start = i;
//					pps_header = 4;
//					i += 5;
//					continue;
//				}
//			}
//			if (hasPps && hasSps) {
//				if (((data[i] == 0x00) && (data[i + 1] == 0x00)
//						&& (data[i + 2] == 0x00) && (data[i + 3] == 0x01) && ((data[i + 4]&0x1F) == 0x05))
//						|| ((data[i] == 0x00) && (data[i + 1] == 0x00)
//								&& (data[i + 2] == 0x00)
//								&& (data[i + 3] == 0x01) && ((data[i + 4] & 0x1F) == 0x06))) {
//					i_start = i;
//					Log.d(TAG, "*************************************");
//					Log.d(TAG, "******* Now input a IDR Frame *******");
//					Log.d(TAG, "*************************************");
//					break;
//				}
//			}
//			i++;
//		}
//		if(!hasSps)
//		{
//			return -1;
//		}
//		if(!hasPps)
//		{
//			return -1;
//		}
//
//		sps_len = pps_start - sps_start - 4;
//		pps_len = i_start - pps_start - pps_header;
//
//		// width height no change
//
//		if (hasSps) {
//			// * 收到sps时创建解码器并将sps存入format
//			byte[] sps_data = new byte[sps_len + 4];
//			sps_data[0] = 0;
//			sps_data[1] = 0;
//			sps_data[2] = 0;
//			sps_data[3] = 1;
//			for (i = 0; i < sps_len; i++) {
//				sps_data[4 + i] = data[i + sps_start + 4];
//				// String stmp = java.lang.Integer.toHexString(sps_data[4+i] &
//				// 0XFF);
//				// Log.d(TAG, "DrawNalBuf----------2.1 sps_data[" + i + "] " +
//				// stmp);
//			}
//
//			// byte[] sps_parse_data = new byte[sps_len];
//			//
//			// for (i = 0; i < sps_len ;i ++)
//			// {
//			// sps_parse_data[i] = data[i + sps_start + 4];
//			// // String stmp = java.lang.Integer.toHexString(sps_data[4+i] &
//			// 0XFF);
//			// // Log.d(TAG, "DrawNalBuf----------2.1 sps_data[" + i + "] " +
//			// stmp);
//			// }
//
//			// get width and height
//			/*
//			 * 00 00 00 01 0x67 ,0x64 ,0x00 ,0x1E ,0xAC ,0x6D ,0x01 ,0xA8
//			 * ,0x7B,0x42,
//			 * 0x00,0X00,0x03,0x00,0x02,0x00,0x00,0x03,0x00,0x51,0x1E
//			 * ,0x24,0x4D,0x40 | ---------------------
//			 * --sps_len------------------------------------|
//			 */
//			ByteBuffer buf = ByteBuffer.wrap(sps_data, 4, sps_len);
//			SequenceParameterSet sps_tmp = SequenceParameterSet.parse(buf);
//			int width = sps_tmp.getWidth();
//			int height = sps_tmp.getHeight();
//			Log.d(TAG, "ParseAndInitialize----------width:" + width);
//			Log.d(TAG, "ParseAndInitialize----------height:" + height);
//
//			if (Video_width != sps_tmp.getWidth()
//					&& Video_height != sps_tmp.getHeight() && (width != 0)
//					&& (height != 0)) {
//				Log.d(TAG, "ParseAndInitialize----------Video_width"
//						+ Video_width + "----------- Video_height :"
//						+ Video_height);
//				if (decoder != null) {
//					decoder.stop();
//					decoder.release();
//					decoder = null;
//					decode_ready = false;
//				}
//				Video_width = sps_tmp.getWidth();
//				Video_height = sps_tmp.getHeight();
//
//				decoder = MediaCodec.createDecoderByType(MIME_TYPE);
//				if (decoder == null) {
//					Log.d(TAG, "ParseAndInitialize----------decoder is null");
//					Video_width = 0;
//					Video_height = 0;
//					return -1;
//				}
//
//				format = MediaFormat.createVideoFormat(MIME_TYPE, Video_width,
//						Video_height);
//
//				format.setInteger(MediaFormat.KEY_FRAME_RATE, 25);
//				// format.setInteger(MediaFormat.KEY_BIT_RATE, 87200);
//				// format.setInteger(MediaFormat.KEY_CHANNEL_COUNT, 1);
//
//				ByteBuffer sps_buff = ByteBuffer.wrap(sps_data, 0, sps_len + 4);
//				format.setByteBuffer("csd-0", sps_buff);
//				sps_data = null;
//			} else {
//				sps_start = 0;
//				pps_start = 0;
//				i_start = 0;
//				return 0; // 没有发生变化
//			}
//
//			if (hasPps) {
//				Log.d(TAG, "ParseAndInitialize----------3");
//				byte[] pps_data = new byte[pps_len + 4];
//				pps_data[0] = 0;
//				pps_data[1] = 0;
//				pps_data[2] = 0;
//				pps_data[3] = 1;
//				for (i = 0; i < pps_len; i++) {
//					pps_data[4 + i] = data[i + pps_start + pps_header];
//					// String stmp = java.lang.Integer.toHexString(pps_data[i] &
//					// 0XFF);
//					// Log.d(TAG, "DrawNalBuf----------2.1 pps_data[" + i + "] "
//					// +
//					// stmp);
//				}
////				for (i = 0; i < pps_len + 4; i++) {
////
////					String stmp = java.lang.Integer
////							.toHexString(pps_data[i] & 0XFF);
////					Log.d(TAG, "DrawNalBuf----------2.1 pps_data[" + i + "] "
////							+ stmp);
////				}
//				if (surfacedecode != null) {
//					
//					// * 将pps存入format的csd-1字段
//					ByteBuffer pps_buff = ByteBuffer.wrap(pps_data, 0,
//							pps_len + 4);
//					format.setByteBuffer("csd-1", pps_buff);
//					// format.setInteger("max_input_size", 138590);
//
//					try {
//						decoder.configure(format, surfacedecode, null, 0);
//					} catch (Exception e) {
//						e.printStackTrace();
//						Video_width = 0;
//						Video_height = 0;
//						decoder.release();
//						decoder = null;
//						return -1;
//					}
//					
//
//					decoder.start();
//					inputBuffers = decoder.getInputBuffers();
//					outputBuffers = decoder.getOutputBuffers();
//					pps_data = null;
//					decode_ready = true;
//				
//				}
//			}
//
//		}

		return 0;

	}


	@TargetApi(Build.VERSION_CODES.JELLY_BEAN)
	public int DrawNalBuf(byte[] data, int len) {

		nativeFunctionLock.lock();

		if (null == info) {
			nativeFunctionLock.unlock();
			return -1;
		}
		if (null == byteBuffer) {
			nativeFunctionLock.unlock();
			return -1;
		}
		if (isDestroyed) {
			nativeFunctionLock.unlock();
			return 0;
		}
		
		// a complete NAL data, include 0x00000001 trail.
		int ret = 0;
		byte[] nalu_data = null;

		// a complete NAL data, include 0x00000001 trail.
		// Parse SPS PPS
		// Detect width height no change
		// Init

		//Log.d(TAG, "DrawNalBuf----------a frame!");
		//监测sps 中宽高是否发生变化
		if ((data[4] & 0x1F) == 0x07) {
			ret = WH_Change_And_ParseInitialize(data, len);
		}
		
		if(true == decode_ready)
		{
			while (true) {
				int inIndex = -1;
				
				try {
					inIndex = decoder.dequeueInputBuffer(0);//10000
				}
				catch (Exception e) {
					e.printStackTrace();
					nativeFunctionLock.unlock();
					return -1;
				}
				
				if (inIndex >= 0) {
					// ByteBuffer buffer = inputBuffers[inIndex];
					// buffer = ByteBuffer.wrap(NalBuf, 0, NalBufUsed-4);
					if (len > 0) {

						nalu_data = new byte[len];
						for (int i = 0; i < len; i++) {
							nalu_data[i] = data[i];
						}

						ByteBuffer inputBuffer = inputBuffers[inIndex];
						inputBuffer.clear();
						inputBuffer.put(nalu_data);

						decoder.queueInputBuffer(inIndex, 0, len, 0, 0);

						nalu_data = null;

					} else {
						decoder.queueInputBuffer(inIndex, 0, 0, 0,
								MediaCodec.BUFFER_FLAG_END_OF_STREAM);
					}
					break;
				} else {
					// Log.d(TAG, "DrawNalBuf------410----end!");
					nativeFunctionLock.unlock();
					return 0;
				}
			}
			int outIndex = MediaCodec.INFO_TRY_AGAIN_LATER;
			//int outIndex = decoder.dequeueOutputBuffer(info, 10000);
			try {
				outIndex = decoder.dequeueOutputBuffer(info, 0);//10000
			} catch (Exception e) {
				e.printStackTrace();
				nativeFunctionLock.unlock();
				return -1;
			}

			switch (outIndex) {
			case MediaCodec.INFO_OUTPUT_BUFFERS_CHANGED:
				Log.d("DecodeActivity", "INFO_OUTPUT_BUFFERS_CHANGED");

				outputBuffers = decoder.getOutputBuffers();

				break;
			case MediaCodec.INFO_OUTPUT_FORMAT_CHANGED:
				Log.d("DecodeActivity",
						"New format " + decoder.getOutputFormat());
//				Configure.isFormate=true;
				break;
			case MediaCodec.INFO_TRY_AGAIN_LATER:
				Log.d("DecodeActivity", "dequeueOutputBuffer timed out!");
				break;
			default:
				ByteBuffer buffer = outputBuffers[outIndex];
//				Log.v("DecodeActivity",
//						"We can't use this buffer but render it due to the API limit, "
//								+ buffer);
				// We use a very simple clock to keep the video FPS, or the
				// video
				// playback will be too fast
				// while (info.presentationTimeUs / 1000 >
				// System.currentTimeMillis() - startMs) {
				// try {
				// sleep(10);
				// } catch (InterruptedException e) {
				// e.printStackTrace();
				// break;
				// }
				// }

				decoder.releaseOutputBuffer(outIndex, true);

				break;
			}

			// All decoded frames have been rendered, we can stop playing now
			// if ((info.flags & MediaCodec.BUFFER_FLAG_END_OF_STREAM) != 0) {
			// Log.d("DecodeActivity",
			// "OutputBuffer BUFFER_FLAG_END_OF_STREAM");
			// break;
			// }
		}

		if (false == decode_ready) {
			nativeFunctionLock.unlock();
			return -1;
		}
		//Log.d(TAG, "DrawNalBuf-------485---end!");
		nativeFunctionLock.unlock();

		return ret;

	}

}
