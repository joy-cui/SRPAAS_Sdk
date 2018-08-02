package org.suirui.srpaas.entry;

import java.io.Serializable;

/**
 * 终端信息
 *
 * @author cui.li
 */
public class TermInfo implements Serializable {
    private static final long serialVersionUID = 1L;
    private int delayflag = 0;        // 0:立即处理 1:延迟处理
    private int replaceterid = 0;    // 替代终端tid，默认值为0
    private int termid;           //终端加入会议时mc产生的,不在线时填0
    private String tername;     //终端的名称
    private boolean ismuted;          //该终端是否静音
    private boolean iscamera_on;      //该终端是否打开摄像头
    private boolean ishandup;         //该终端是否举手
    private int suid;             //终端唯一标识(由终端产生)
    private boolean isonline;         //是否在线,true表示在线，false表示不在线
    private int specialtype;  //特殊类型, 0-普通终端类型,1-投屏终端类型

    //目前针对第三方的终端
    private String ip;            //终端ip
    private int protocoltype;  //标准终端的呼叫协议类型,0-自动、1-sip、2-H.323,SR终端强制填入0
    private int bandwidth;     //终端呼叫带宽
    private int usertype;      //用户类型,0-临时用户,1-正式用户,2-Ubox,3-标准终端(H.323/sip)
    private int devicetype;    //设备类型,0-终端,1-MCU
    private String calloption;    //呼叫选项,一般是通知给gw供devicetype==1情况分析用, 这个一般邀请第三方终端的时候填写
    private int videoType;// 流类型(选择查看流类型)
    private int termState;// 参会人状态
    private int audioDeviceState;// 设备音频状态


    public int getTermid() {
        return termid;
    }

    public void setTermid(int termid) {
        this.termid = termid;
    }

    public String getTername() {
        return tername;
    }

    public void setTername(String tername) {
        this.tername = tername;
    }

    public boolean isIsmuted() {
        return ismuted;
    }

    public void setIsmuted(boolean ismuted) {
        this.ismuted = ismuted;
    }

    public boolean isIscamera_on() {
        return iscamera_on;
    }

    public void setIscamera_on(boolean iscamera_on) {
        this.iscamera_on = iscamera_on;
    }

    public boolean isIshandup() {
        return ishandup;
    }

    public void setIshandup(boolean ishandup) {
        this.ishandup = ishandup;
    }

    public int getVideoType() {
        return videoType;
    }

    public void setVideoType(int videoType) {
        this.videoType = videoType;
    }

    public int getTermState() {
        return termState;
    }

    public void setTermState(int termState) {
        this.termState = termState;
    }

    public int getAudioDeviceState() {
        return audioDeviceState;
    }

    public void setAudioDeviceState(int audioDeviceState) {
        this.audioDeviceState = audioDeviceState;
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

    public int getSuid() {
        return suid;
    }

    public void setSuid(int suid) {
        this.suid = suid;
    }

    public int getUsertype() {
        return usertype;
    }

    public void setUsertype(int usertype) {
        this.usertype = usertype;
    }

    public boolean isonline() {
        return isonline;
    }

    public void setIsonline(boolean isonline) {
        this.isonline = isonline;
    }

    public int getSpecialtype() {
        return specialtype;
    }

    public void setSpecialtype(int specialtype) {
        this.specialtype = specialtype;
    }

    public boolean isIsonline() {
        return isonline;
    }

    public String getIp() {
        return ip;
    }

    public void setIp(String ip) {
        this.ip = ip;
    }

    public int getProtocoltype() {
        return protocoltype;
    }

    public void setProtocoltype(int protocoltype) {
        this.protocoltype = protocoltype;
    }

    public int getBandwidth() {
        return bandwidth;
    }

    public void setBandwidth(int bandwidth) {
        this.bandwidth = bandwidth;
    }

    public int getDevicetype() {
        return devicetype;
    }

    public void setDevicetype(int devicetype) {
        this.devicetype = devicetype;
    }

    public String getCalloption() {
        return calloption;
    }

    public void setCalloption(String calloption) {
        this.calloption = calloption;
    }
}
