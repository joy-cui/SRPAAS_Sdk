package org.suirui.srpaas.entry;

/**
 * @authordingna
 * @date2017-12-11
 **/
public class SRMediaPScreenInfo {
    private int screenid;       //混屏布局对应屏幕id
    private int screentype;     //屏幕类型，1-会议屏幕/网关(标准终端)屏幕、2-终端屏幕、3-双流屏幕

    public int getScreenid() {
        return screenid;
    }

    public void setScreenid(int screenid) {
        this.screenid = screenid;
    }

    public int getScreentype() {
        return screentype;
    }

    public void setScreentype(int screentype) {
        this.screentype = screentype;
    }
}
