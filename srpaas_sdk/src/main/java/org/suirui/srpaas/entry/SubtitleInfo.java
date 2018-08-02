package org.suirui.srpaas.entry;

/**
 * @authordingna
 * @date2017-10-31
 **/
public class SubtitleInfo {
    private int displaytime;      //字幕滚动时间，单位：秒，设置为0，则停止字幕显示
    private int msgpos;           //滚动字幕的位置：1-上、2-中、3-下
    private String msgcolor;         //消息字体颜色:RGB颜色值,6位十六进制值,如:黑色 #000000、白色 #FFFFFF、红色 #FF0000、绿色 #00FF00、蓝色 #0000FF、黄色 #FFFF00
    private int msgfontsize;      //字体大小：1-大、2-中、3-小
    private boolean enableMsgBg;      //使能会场名称背景
    private String msgbgcolor;       //字体背景颜色:RGB颜色值,6位十六进制值,如:黑色 #000000、白色 #FFFFFF、红色 #FF0000、绿色 #00FF00、蓝色 #0000FF、黄色 #FFFF00

    public int getDisplaytime() {
        return displaytime;
    }

    public void setDisplaytime(int displaytime) {
        this.displaytime = displaytime;
    }

    public int getMsgpos() {
        return msgpos;
    }

    public void setMsgpos(int msgpos) {
        this.msgpos = msgpos;
    }

    public String getMsgcolor() {
        return msgcolor;
    }

    public void setMsgcolor(String msgcolor) {
        this.msgcolor = msgcolor;
    }

    public int getMsgfontsize() {
        return msgfontsize;
    }

    public void setMsgfontsize(int msgfontsize) {
        this.msgfontsize = msgfontsize;
    }

    public boolean isEnableMsgBg() {
        return enableMsgBg;
    }

    public void setEnableMsgBg(boolean enableMsgBg) {
        this.enableMsgBg = enableMsgBg;
    }

    public String getMsgbgcolor() {
        return msgbgcolor;
    }

    public void setMsgbgcolor(String msgbgcolor) {
        this.msgbgcolor = msgbgcolor;
    }
}
