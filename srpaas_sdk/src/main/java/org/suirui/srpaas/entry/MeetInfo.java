package org.suirui.srpaas.entry;

public class MeetInfo {
    MeetingOptions m_options;// (开始会议)
    private String m_confId;// 会议号
    private String m_confPwd;// 会议密码
    private String m_livePwd;// 直播密码
    private String thirdAudioVersion;// 第三方音频库版本
    private String thirdAudioId;// 第三方音频库ID(macAdress)
    private String nickName;// 昵称
    // 开始会议
    private String m_subject;// 会议主题
    private String m_startTime;// 开始时间(开始会议)
    private String m_endTime;// 结束时间 (开始会议)
    private boolean isCameraOn;//是否打开相机
    private boolean isMute;//是否静音
    private String token;
    private String audioenable;//是否启用音频
    private String videoenable;//启用视频
    private String confDomain;

    public String getConfDomain() {
        return confDomain;
    }

    public void setConfDomain(String confDomain) {
        this.confDomain = confDomain;
    }

    public String getToken() {
        return token;
    }

    public void setToken(String token) {
        this.token = token;
    }

    public String getM_confId() {
        return m_confId;
    }

    public void setM_confId(String m_confId) {
        this.m_confId = m_confId;
    }

    public String getM_confPwd() {
        return m_confPwd;
    }

    public void setM_confPwd(String m_confPwd) {
        this.m_confPwd = m_confPwd;
    }

    public String getM_livePwd() {
        return m_livePwd;
    }

    public void setM_livePwd(String m_livePwd) {
        this.m_livePwd = m_livePwd;
    }

    public String getThirdAudioVersion() {
        return thirdAudioVersion;
    }

    public void setThirdAudioVersion(String thirdAudioVersion) {
        this.thirdAudioVersion = thirdAudioVersion;
    }

    public String getThirdAudioId() {
        return thirdAudioId;
    }

    public void setThirdAudioId(String thirdAudioId) {
        this.thirdAudioId = thirdAudioId;
    }

    public String getNickName() {
        return nickName;
    }

    public void setNickName(String nickName) {
        this.nickName = nickName;
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

    public MeetingOptions getM_options() {
        return m_options;
    }

    public void setM_options(MeetingOptions m_options) {
        this.m_options = m_options;
    }

    public boolean isCameraOn() {
        return isCameraOn;
    }

    public void setCameraOn(boolean cameraOn) {
        isCameraOn = cameraOn;
    }

    public boolean isMute() {
        return isMute;
    }

    public void setMute(boolean mute) {
        isMute = mute;
    }

    public String getAudioenable() {
        return audioenable;
    }

    public void setAudioenable(String audioenable) {
        this.audioenable = audioenable;
    }

    public String getVideoenable() {
        return videoenable;
    }

    public void setVideoenable(String videoenable) {
        this.videoenable = videoenable;
    }
}
