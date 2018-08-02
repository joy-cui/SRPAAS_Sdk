package org.webrtc.videoengine;

import android.annotation.SuppressLint;
import android.graphics.ImageFormat;
import android.graphics.PixelFormat;
import android.media.MediaCodec;
import android.media.MediaCodecInfo;
import android.media.MediaCodecList;
import android.media.MediaFormat;
import android.util.Log;

import java.io.IOException;
import java.nio.ByteBuffer;
import java.util.Arrays;

/*import com.interfaces.androidencode.NetLog;*/

@SuppressLint("NewApi")

public class AvcEncoder
{
	private final static String TAG = "WEBRTC";
	private MediaCodec mediaCodec;
	int m_width;
	int m_height;
	int m_color_format = 0;
	int suportColorFormat = MediaCodecInfo.CodecCapabilities.COLOR_FormatYUV420Planar;
	private ByteBuffer byteYuvBuffer = null;
	private ByteBuffer byteH264Buffer = null;
	byte[] m_info = null;
	private static int inst_nbr = 0;
	private int PIXEL_FORMAT = ImageFormat.NV21;
	PixelFormat pixelFormat = new PixelFormat();
	static boolean 	m_NV21=true;
	
	private static int getSupportColorFormat()
    {
		int ret_flag = 0;
        int numCodecs = MediaCodecList.getCodecCount();
        MediaCodecInfo codecInfo = null;
        for (int i = 0; i < numCodecs && codecInfo == null; i++)
        {
            MediaCodecInfo info = MediaCodecList.getCodecInfoAt(i);
            if (!info.isEncoder())
            {
                continue;
            }
            String[] types = info.getSupportedTypes();
            boolean found = false;
            for (int j = 0; j < types.length && !found; j++)
            {
                if (types[j].equals("video/avc"))
                {
                    System.out.println("found");
                    found = true;
                }
            }
            if (!found)
                continue;
            codecInfo = info;
        }
        
        // Find a color profile that the codec supports
        int colorFormat = 0;
        MediaCodecInfo.CodecCapabilities capabilities = codecInfo.getCapabilitiesForType("video/avc");
        System.out.println("length-" + capabilities.colorFormats.length + "=="
                + Arrays.toString(capabilities.colorFormats));
        
        for (int i = 0; i < capabilities.colorFormats.length&& colorFormat == 0; i++)
        {
             int format = capabilities.colorFormats[i];
            switch (format)
            {
                case MediaCodecInfo.CodecCapabilities.COLOR_FormatYUV420Planar:
                	 Log.d("h264-enc","MediaCodecInfo.CodecCapabilities.COLOR_FormatYUV420Planar");
                	ret_flag |= 0x01;
                	break;
                case MediaCodecInfo.CodecCapabilities.COLOR_FormatYUV420PackedPlanar:
                	 Log.d("h264-enc","MediaCodecInfo.CodecCapabilities.COLOR_FormatYUV420PackedPlanar");
                	ret_flag |= 0x04;
                    break;
                case MediaCodecInfo.CodecCapabilities.COLOR_FormatYUV420SemiPlanar:
                	Log.d("h264-enc","MediaCodecInfo.CodecCapabilities.COLOR_FormatYUV420SemiPlanar");
                	ret_flag |= 0x02;
                    break;
                case MediaCodecInfo.CodecCapabilities.COLOR_FormatYUV420PackedSemiPlanar:
                	Log.d("h264-enc","MediaCodecInfo.CodecCapabilities.COLOR_FormatYUV420PackedSemiPlanar");
                	ret_flag |= 0x08;
                    break;
                case MediaCodecInfo.CodecCapabilities.COLOR_TI_FormatYUV420PackedSemiPlanar:
                	Log.d("h264-enc","MediaCodecInfo.CodecCapabilities.COLOR_TI_FormatYUV420PackedSemiPlanar");
                    ret_flag |= 0x10;
                    break;
                default:
                    break;
            }            
        }
        
        return ret_flag;
    }
	private byte[] yuv420 = null; 
	
	public AvcEncoder()
	{
		byteYuvBuffer = null;
		byteH264Buffer = null;
	}
	
	public static AvcEncoder CreateAvcEncoder(int in_id)
	{
		Log.d("h264-enc","Java: Create AvcEncoder....");
		int color_format_flag = getSupportColorFormat();
		if ((color_format_flag & 0x02)==0x02) {
			String cpu_name = CpuManager.getProcessName();
			if (cpu_name.indexOf("K3V2") >=0) {
				m_NV21 = false;
			}			
		}
		
		AvcEncoder self = new AvcEncoder();
		if(self != null) {
			return self;
		}
		return null;
	}
	
	public static int AvcIsSupported(int type)
	{
        int numCodecs = MediaCodecList.getCodecCount();
        for (int i = 0; i < numCodecs; i++)
        {
            MediaCodecInfo info = MediaCodecList.getCodecInfoAt(i);
            if (!info.isEncoder())
            {
                continue;
            }
            String[] types = info.getSupportedTypes();
            for (int j = 0; j < types.length; j++)
            {
                if (types[j].equals("video/avc"))
                {
                    System.out.println("found");
                    return 0;
                }
            }   
        }
		return -1;
	}
	
	public int InitAvc(int width, int height, int framerate, int bitrate) {
		
		Log.d(TAG, "Init avcencoder"+"width="+width+"height="+height+"framerate="+framerate+"bitrate="+bitrate);
		if (inst_nbr >= 1) {
			return -10000;
		}
		
		m_width  = width;
		m_height = height;
		yuv420 = new byte[width*height*3/2];
		try {
			mediaCodec = MediaCodec.createEncoderByType("video/avc");
		} catch (IOException e) {
			e.printStackTrace();
		}
		MediaFormat mediaFormat = MediaFormat.createVideoFormat("video/avc", width, height);
	    mediaFormat.setInteger(MediaFormat.KEY_BIT_RATE, bitrate);
	    mediaFormat.setInteger(MediaFormat.KEY_FRAME_RATE, framerate);
	    mediaFormat.setInteger(MediaFormat.KEY_I_FRAME_INTERVAL, framerate*3);
	    int color_format_flag = getSupportColorFormat();
	    suportColorFormat  = 0;
	    if ((color_format_flag & 0x01) == 1) {
	    	suportColorFormat = MediaCodecInfo.CodecCapabilities.COLOR_FormatYUV420Planar;
	    }else if ((color_format_flag & 0x02)==0x02){
	    	suportColorFormat = MediaCodecInfo.CodecCapabilities.COLOR_FormatYUV420SemiPlanar;
	    }else {
	    	return -1;
	    	
	    }
	    mediaFormat.setInteger(MediaFormat.KEY_COLOR_FORMAT, suportColorFormat);    
	    
	    mediaFormat.setInteger(MediaFormat.KEY_I_FRAME_INTERVAL, 3);
	    mediaCodec.configure(mediaFormat, null, null, MediaCodec.CONFIGURE_FLAG_ENCODE);
	    mediaCodec.start();
	    
	    if (byteYuvBuffer == null) {
			byteYuvBuffer = ByteBuffer.allocateDirect(width*height*3/2);
		}
	    if (byteH264Buffer == null) {
			byteH264Buffer = ByteBuffer.allocateDirect(width*height*3/2);
		}
	    inst_nbr++;

	   // mediaCodec.setParameters(100);
	    return 0;
		
	}
	
    public int GetAvcColorFormate()
    {
    	 int color_format_flag = getSupportColorFormat();
    	 return color_format_flag;
    }
	
	@SuppressLint("NewApi")
	public int Close(int i) {
		Log.i("avc","AvcEncoder close is entry");
		inst_nbr=0;
		m_info = null;
		
		MediaCodec.BufferInfo bufferInfo = new MediaCodec.BufferInfo();
		int outputBufferIndex = mediaCodec.dequeueOutputBuffer(bufferInfo,0);

		while (outputBufferIndex >= 0) 
		{
			bufferInfo = new MediaCodec.BufferInfo();
			mediaCodec.releaseOutputBuffer(outputBufferIndex, false);
			outputBufferIndex = mediaCodec.dequeueOutputBuffer(bufferInfo,0);
		}
		byteYuvBuffer = null;
		byteH264Buffer = null;
		yuv420 = null;
		
		Log.i("avc","AvcEncoder close <mediaCodec.flush()>");
		//mediaCodec.flush();
		Log.i("avc","AvcEncoder close <buffer release is ok>");
      //  mediaCodec.stop();
        Log.i("avc","AvcEncoder close <call mediaCodec.stop() is ok>");
        mediaCodec.release();
        Log.i("avc","AvcEncoder close <call mediaCodec.release() is ok>");
	   Log.i("avc","AvcEncoder close is exit");
		return 0;
	}

	public ByteBuffer GetYuvByteBuffer() {
		if (byteYuvBuffer == null) {
			byteYuvBuffer = ByteBuffer.allocateDirect(m_width*m_height*3/2);
		}
		
		return byteYuvBuffer;
	}
	
	public ByteBuffer GetH264ByteBuffer() {
		if (byteH264Buffer == null) {
			byteH264Buffer = ByteBuffer.allocateDirect(m_width*m_height*3/2);
		}
		return byteH264Buffer;
	}
	
	@SuppressLint("NewApi")
	public int Encode(int yuv_length) 
	{
		int pos = 0;
		Log.d("h264-enc","Entry Java:AvcEncoder Encode Func,input yuv_length:"+yuv_length);

		SwapI420ToDest(byteYuvBuffer.array(), yuv420, m_width, m_height);
		//System.arraycopy(byteYuvBuffer.array(),0,yuv420,0,m_width*m_height*3/2);
		Log.d("h264-enc","to execute the SwapI420ToDest Func is Successful");

		try {
			ByteBuffer[] inputBuffers = mediaCodec.getInputBuffers();
			ByteBuffer[] outputBuffers = mediaCodec.getOutputBuffers();
			int inputBufferIndex = mediaCodec.dequeueInputBuffer(-1);
			while (inputBufferIndex <0) {
				inputBufferIndex = mediaCodec.dequeueInputBuffer(-1);
			}
			if (inputBufferIndex >= 0)
			{
				ByteBuffer inputBuffer = inputBuffers[inputBufferIndex];
				inputBuffer.clear();
				inputBuffer.put(yuv420);
				mediaCodec.queueInputBuffer(inputBufferIndex, 0, yuv420.length, 0, 0);
			}

			MediaCodec.BufferInfo bufferInfo = new MediaCodec.BufferInfo();
			int outputBufferIndex = mediaCodec.dequeueOutputBuffer(bufferInfo,0);

			while (outputBufferIndex >= 0) 
			{
				ByteBuffer outputBuffer = outputBuffers[outputBufferIndex];
				byte[] outData = new byte[bufferInfo.size];
				outputBuffer.get(outData);

				if(m_info != null)
				{
					System.arraycopy(outData, 0,  byteH264Buffer.array(), pos, outData.length);
					pos += outData.length;
				}

				else
				{
					ByteBuffer spsPpsBuffer = ByteBuffer.wrap(outData);
					
					if (spsPpsBuffer.getInt() == 0x00000001) 
					{
						m_info = new byte[outData.length];
						System.arraycopy(outData, 0, m_info, 0, outData.length);
					}else 
					{  
						return -1;
					}  	
				}

				mediaCodec.releaseOutputBuffer(outputBufferIndex, false);
				outputBufferIndex = mediaCodec.dequeueOutputBuffer(bufferInfo, 0);
			}

			if((byteH264Buffer.array()[4] &0x1F) == 0x05) //key frame
			{
				System.arraycopy(byteH264Buffer.array(), 0,  yuv420, 0, pos);
				System.arraycopy(m_info, 0,  byteH264Buffer.array(), 0, m_info.length);
				System.arraycopy(yuv420, 0,  byteH264Buffer.array(), m_info.length, pos);
				pos += m_info.length;
			}

		} catch (Throwable t) {
			t.printStackTrace();
		}
		Log.d("h264-enc","Entry Java:AvcEncoder Encode Func Ended");
		return pos;
	}
	
	public int SetEncBitrate(int bitrate) 
	{
	//	mediaCodec.
		
		return 0;
	}
	
	
	
    private void SwapI420ToDest(byte[] i420bytes, byte[] destbytes, int width, int height) 
    {
    	int y_size = 0,u_size = 0;
    	y_size = width*height;
    	u_size = width*height/4;
    	Log.i("h264-enc","SwapI420ToDest suportColorFormat"+suportColorFormat+"width="+width+"height="+height);
    	if (suportColorFormat == MediaCodecInfo.CodecCapabilities.COLOR_FormatYUV420SemiPlanar) {
    		System.arraycopy(i420bytes,0,destbytes,0,y_size);
    		int n=0;
        	for (int i = 0; i < u_size*2;i+=2) {
        		if (m_NV21 == true) {   //nv21
        			destbytes[y_size+i] =i420bytes[y_size+n];
            		destbytes[y_size+i+1] = i420bytes[y_size+u_size+n];
        		}else {					//nv12
        			destbytes[y_size+i] =i420bytes[y_size+u_size+n];
            		destbytes[y_size+i+1] = i420bytes[y_size+n];
        		}
        		n++;
        	}
    	}else {
    		System.arraycopy(i420bytes,0,destbytes,0,width*height*3/2);
    	}
    }  
  
}


