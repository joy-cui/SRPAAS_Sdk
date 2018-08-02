package org.suirui.srpaas.entry;

public class RvideoParam {
	// CFG_VIDEO_LOW_TYPE = 1, //选看终端的小流
	// CFG_VIDEO_MIDDLE_TYPE, //选看终端的中流
	// CFG_VIDEO_HIGH_TYPE, //选看终端的大流
	// CFG_VIDEO_DESKTOP_TYPE, //选看终端的桌面共享流
	// CFG_VIDEO_DESKTOP_CLOSE_TYPE, //关闭终端的桌面共享流
	// CFG_VIDEO_CLOSE,
	private int termId;// 选看视频id
	private int videoType;// 流类型
	// 视频窗口
	int delayflag;		// 0:立即处理 1:延迟处理
	int replaceterid;	// 替代终端tid，默认值为0
	int expectfps;		// 期望终端最大帧率，默认2（24帧），1（12帧），0（6帧）

	public int getTermId() {
		return termId;
	}

	public void setTermId(int termId) {
		this.termId = termId;
	}

	public int getVideoType() {
		return videoType;
	}

	public void setVideoType(int videoType) {
		this.videoType = videoType;
	}

	public int getDelayflag() {
		return delayflag;
	}

	public void setDelayflag(int delayflag) {
		this.delayflag = delayflag;
	}

	public int getReplaceterid() {
		return replaceterid;
	}

	public void setReplaceterid(int replaceterid) {
		this.replaceterid = replaceterid;
	}

	public int getExpectfps() {
		return expectfps;
	}

	public void setExpectfps(int expectfps) {
		this.expectfps = expectfps;
	}
}
