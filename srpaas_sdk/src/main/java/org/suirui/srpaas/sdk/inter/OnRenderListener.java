package org.suirui.srpaas.sdk.inter;

public interface OnRenderListener {
	// 显示渲染视频
	void onRenderCallBackCallBack(int id, int flag,int format, byte[] ybuf, byte[] ubuf,
								  byte[] vbuf, int width, int height,int length);


}
