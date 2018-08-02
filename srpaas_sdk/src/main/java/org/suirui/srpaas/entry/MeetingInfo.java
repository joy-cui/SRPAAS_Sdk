package org.suirui.srpaas.entry;

/**
 * 会议的相关属性（提供第三方使用） 返回的参数
 *
 * @author cui.li
 */
public class MeetingInfo {
    public String videoenable;//是否启用视频
    public String audioenable;//是否启用音频
    MeetingOptions m_options;// 开始会议的时候需要填写的
    private String m_confId;// 会议号
    private String m_subject;// 会议主题
    private String m_startTime;// 开始时间
    private String m_endTime;// 结束时间
    private String m_mcAddr;// mc地址（对应ipandport）
    private String m_relaymcAddr;// relay地址
    private String m_relayServer;// relayServer地址
    private String thirdAudioKey;
    private String userName;// 加入会议的昵称
    private String hasStarted;//是否已经start过本次会议  by 20160904
    private String confPwd;//会议密码
    private String micautoenable;//入会自动静音,0否 1是
    private String camaraautoenable;//入会自动打开视频,0否 1是
    private String confName;//会议主题
    private String mediaGroupId;//该终端所属域分组id
    private String OCI;//当前在线会议客户端数量信息
    private String m_relaymcInfo;//Relaymc地址数组，包含内外网信息
    private String playAddrPrefix;//直播播放地址
    private String pullAddrPrefix;//拉流地址

    public String getM_confId() {
        return m_confId;
    }

    public void setM_confId(String m_confId) {
        this.m_confId = m_confId;
    }

    public String getM_subject() {
        return m_subject;
    }

    public void setM_subject(String m_subject) {
        this.m_subject = m_subject;
    }

    public String getM_startTime() {
        return m_startTime;
    }

    public void setM_startTime(String m_startTime) {
        this.m_startTime = m_startTime;
    }

    public String getM_endTime() {
        return m_endTime;
    }

    public void setM_endTime(String m_endTime) {
        this.m_endTime = m_endTime;
    }

    public String getM_mcAddr() {
        return m_mcAddr;
    }

    public void setM_mcAddr(String m_mcAddr) {
        this.m_mcAddr = m_mcAddr;
    }

    public String getM_relaymcAddr() {
        return m_relaymcAddr;
    }

    public void setM_relaymcAddr(String m_relaymcAddr) {
        this.m_relaymcAddr = m_relaymcAddr;
    }

    public String getM_relayServer() {
        return m_relayServer;
    }

    public void setM_relayServer(String m_relayServer) {
        this.m_relayServer = m_relayServer;
    }

    public MeetingOptions getM_options() {
        return m_options;
    }

    public void setM_options(MeetingOptions m_options) {
        this.m_options = m_options;
    }

    public String getUserName() {
        return userName;
    }

    public void setUserName(String userName) {
        this.userName = userName;
    }

    public String getThirdAudioKey() {
        return thirdAudioKey;
    }

    public void setThirdAudioKey(String thirdAudioKey) {
        this.thirdAudioKey = thirdAudioKey;
    }

    public String getHasStarted() {
        return hasStarted;
    }

    public void setHasStarted(String hasStarted) {
        this.hasStarted = hasStarted;
    }

    public String getVideoenable() {
        return videoenable;
    }

    public void setVideoenable(String videoenable) {
        this.videoenable = videoenable;
    }

    public String getAudioenable() {
        return audioenable;
    }

    public void setAudioenable(String audioenable) {
        this.audioenable = audioenable;
    }

    public String getConfPwd() {
        return confPwd;
    }

    public void setConfPwd(String confPwd) {
        this.confPwd = confPwd;
    }

    public String getMicautoenable() {
        return micautoenable;
    }

    public void setMicautoenable(String micautoenable) {
        this.micautoenable = micautoenable;
    }

    public String getCamaraautoenable() {
        return camaraautoenable;
    }

    public void setCamaraautoenable(String camaraautoenable) {
        this.camaraautoenable = camaraautoenable;
    }

    public String getConfName() {
        return confName;
    }

    public void setConfName(String confName) {
        this.confName = confName;
    }

    public String getMediaGroupId() {
        return mediaGroupId;
    }

    public void setMediaGroupId(String mediaGroupId) {
        this.mediaGroupId = mediaGroupId;
    }

    public String getOCI() {
        return OCI;
    }

    public void setOCI(String OCI) {
        this.OCI = OCI;
    }

    public String getM_relaymcInfo() {
        return m_relaymcInfo;
    }

    public void setM_relaymcInfo(String m_relaymcInfo) {
        this.m_relaymcInfo = m_relaymcInfo;
    }

    public String getPlayAddrPrefix() {
        return playAddrPrefix;
    }

    public void setPlayAddrPrefix(String playAddrPrefix) {
        this.playAddrPrefix = playAddrPrefix;
    }

    public String getPullAddrPrefix() {
        return pullAddrPrefix;
    }

    public void setPullAddrPrefix(String pullAddrPrefix) {
        this.pullAddrPrefix = pullAddrPrefix;
    }
}
