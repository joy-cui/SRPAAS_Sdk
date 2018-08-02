package org.suirui.srpaas.sdk.inter;

public interface OnMsgListener {
	// 关闭数据共享提示(关闭界面)
	void OnRecvDualVideoCloseCallBack(long conf_id, int term_id);
}
