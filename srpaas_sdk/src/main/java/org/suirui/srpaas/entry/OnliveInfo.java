package org.suirui.srpaas.entry;

/**
 * 直播信息
 *
 * @authordingna
 * @date2018-04-02
 **/
public class OnliveInfo {
    private String pulladdrprefix;//直播的拉流地址前缀,与confid+channelid拼成拉流url
    private String playaddrprefix; //直播的播放地址前缀,与confid+channelid拼成播放url
    private String chairman;//直播主持人
    private String subject;//直播主题
    private String digest;//直播摘要/简介
    private int ispublic; //是否公开,0-不公开,1-公开
    private String livepwd;//直播密码

    public String getPulladdrprefix() {
        return pulladdrprefix;
    }

    public void setPulladdrprefix(String pulladdrprefix) {
        this.pulladdrprefix = pulladdrprefix;
    }

    public String getPlayaddrprefix() {
        return playaddrprefix;
    }

    public void setPlayaddrprefix(String playaddrprefix) {
        this.playaddrprefix = playaddrprefix;
    }

    public String getChairman() {
        return chairman;
    }

    public void setChairman(String chairman) {
        this.chairman = chairman;
    }

    public String getSubject() {
        return subject;
    }

    public void setSubject(String subject) {
        this.subject = subject;
    }

    public String getDigest() {
        return digest;
    }

    public void setDigest(String digest) {
        this.digest = digest;
    }

    public int getIspublic() {
        return ispublic;
    }

    public void setIspublic(int ispublic) {
        this.ispublic = ispublic;
    }

    public String getLivepwd() {
        return livepwd;
    }

    public void setLivepwd(String livepwd) {
        this.livepwd = livepwd;
    }
}
