package org.suirui.srpaas.util;


import android.graphics.Bitmap;
import android.util.Log;

public class Bmp2YUV {
	/**
	 * YUV420sp
	 * 
	 * @param inputWidth
	 * @param inputHeight
	 * @param scaled
	 * @return
	 */
	public static byte[] getYUV420sp(int inputWidth, int inputHeight,
			Bitmap scaled) {

		int[] argb = new int[inputWidth * inputHeight];

		scaled.getPixels(argb, 0, inputWidth, 0, 0, inputWidth, inputHeight);

//		byte[] yuv = new byte[inputWidth * inputHeight * 3 / 2];
//		encodeYUV420SP(yuv, argb, inputWidth, inputHeight);
		byte[] yuv= encodeToYUV420SP( argb, inputWidth, inputHeight);
		scaled.recycle();
       Log.e("", "yuv...length: "+yuv.length);
		return yuv;
	}
	
	public static byte[] toRGB(int inputWidth, int inputHeight,
			Bitmap scaled){
		
		
		
		return null;
		
	}
	private static	byte[] encodeToYUV420SP( int[] pixels, int width, int height) {
		int len=width*height;
		byte[] yuv=new byte[len*3/2];
		int y,u,v;
		for(int i=0;i<height;i++){
			for(int j=0;j<width;j++){
				int rgb=pixels[i*width+j]&0x00FFFFFF;
				int r=rgb&0xFF;
				int g=(rgb>>8)&0xFF;
				int b=(rgb>>16)&0xFF;
				//套用公式
				y = ( (  66 * r + 129 * g +  25 * b + 128) >> 8) +  16;
                u = ( ( -38 * r -  74 * g + 112 * b + 128) >> 8) + 128;
                v = ( ( 112 * r -  94 * g -  18 * b + 128) >> 8) + 128;
                y=y<16?16:(y>255?255:y);
                u=y<0?0:(u>255?255:u);
                v=v<0?16:(v>255?255:v);
                yuv[i*width+j]=(byte)y;
                yuv[len+(i>>1)*width+(j&~1+0)]=(byte)u;
                yuv[len+(i>>1)*width+(j&~1+1)]=(byte)v;
			}
		}
		return yuv;
		
		
		
//        final int frameSize = width * height;
//
//        int yIndex = 0;
//        int uvIndex = frameSize;
//
//        int a, R, G, B, Y, U, V;
////        int index = 0;
//        for (int j = 0; j < height; j++) {
//            for (int i = 0; i < width; i++) {
//
//                a = (argb[index] & 0xff000000) >> 24; // a is not used obviously
//                R = (argb[index] & 0xff0000) >> 16;
//                G = (argb[index] & 0xff00) >> 8;
//                B = (argb[index] & 0xff) >> 0;
//
////                 well known RGB to YUV algorithm
//                Y = ( (  66 * R + 129 * G +  25 * B + 128) >> 8) +  16;
//                U = ( ( -38 * R -  74 * G + 112 * B + 128) >> 8) + 128;
//                V = ( ( 112 * R -  94 * G -  18 * B + 128) >> 8) + 128;
//                
//
//                // NV21 has a plane of Y and interleaved planes of VU each sampled by a factor of 2
//                //    meaning for every 4 Y pixels there are 1 V and 1 U.  Note the sampling is every other
//                //    pixel AND every other scanline.
//                yuv420sp[yIndex++] = (byte) ((Y < 0) ? 0 : ((Y > 255) ? 255 : Y));
//                if (j % 2 == 0 && index % 2 == 0) { 
//                    yuv420sp[uvIndex++] = (byte)((V<0) ? 0 : ((V > 255) ? 255 : V));
//                    yuv420sp[uvIndex++] = (byte)((U<0) ? 0 : ((U > 255) ? 255 : U));
//                }
//
//                index ++;
//            }
//        }
}
	
	
	
	
	
	
	
	
	
	

	/**
	 * RGB转YUV420sp
	 * 
	 * @param yuv420sp
	 *            inputWidth * inputHeight * 3 / 2
	 * @param argb
	 *            inputWidth * inputHeight
	 * @param width
	 * @param height
	 */
	private static void encodeYUV420SP(byte[] yuv420sp, int[] argb, int width,
			int height) {
		// 帧图片的像素大小
		final int frameSize = width * height;
		// ---YUV数据---
		int Y, U, V;
		// Y的index从0开始
		int yIndex = 0;
		// UV的index从frameSize开始
		int uvIndex = frameSize;

		// ---颜色数据---
		int a, R, G, B;
		//
		int argbIndex = 0;
		//

		// ---循环所有像素点，RGB转YUV---
		for (int j = 0; j < height; j++) {
			for (int i = 0; i < width; i++) {

				// a is not used obviously
				a = (argb[argbIndex] & 0xff000000) >> 24;
				R = (argb[argbIndex] & 0xff0000) >> 16;
				G = (argb[argbIndex] & 0xff00) >> 8;
				B = (argb[argbIndex] & 0xff);
				//
				argbIndex++;

				// well known RGB to YUV algorithm
				Y = ((66 * R + 129 * G + 25 * B + 128) >> 8) + 16;
				U = ((-38 * R - 74 * G + 112 * B + 128) >> 8) + 128;
				V = ((112 * R - 94 * G - 18 * B + 128) >> 8) + 128;

				//
				Y = Math.max(0, Math.min(Y, 255));
				U = Math.max(0, Math.min(U, 255));
				V = Math.max(0, Math.min(V, 255));

				// NV21 has a plane of Y and interleaved planes of VU each
				// sampled by a factor of 2
				// meaning for every 4 Y pixels there are 1 V and 1 U. Note the
				// sampling is every other
				// pixel AND every other scanline.
				// ---Y---
				yuv420sp[yIndex++] = (byte) Y;
				// ---UV---
				if ((j % 2 == 0) && (i % 2 == 0)) {
					//
					yuv420sp[uvIndex++] = (byte) V;
					//
					yuv420sp[uvIndex++] = (byte) U;
				}
			}
		}
	}
	
	

}
