package org.suirui.srpaas.entry;

import java.util.List;

/**
 * @authordingna
 * @date2017-10-31
 **/
public class ConfInfoStatus {
    private String confname;            //会议名称,对应subject会议主题
    private int confmode;           //conf mode,0-自由模式、1-主席模式、
    private List<Integer> participants;       //参会者列表,参会者suid集合
    private int chairmansuid;       //会议主席,对应数据库里会议创建者的suid
    private List<Integer> assistchairmans;    //辅助主席,参会者suid集合
    private int duovideoterid;      //拥有双流令牌的与会者
    private int stdterseeingstyle;  //标准终端观看方式，0-跟随主持人、1-仅显示主席会场、2-标准终端观看网关分屏布局
    private boolean isduovideostart;    //是否开启双流
    private boolean isconflocked;       //会议是否被锁定
    private boolean isforcemute;        //强制禁音是否开启，true表示设置，false表示取消
    private boolean isdisplaytername;   //是否显示会场名称，true表示显示，false表示隐藏
    private boolean issubtitlestart;    //滚动字幕是否开启，true表示开启，false表示关闭
    private String subtitlemsg;
    private SubtitleInfo subtitle;            //滚动字幕信息
    private List<WhiteListInfo> whitelists;         //会议白名单
    private int recstate;                  //录制会议状态,0-停止录制,1-开始录制
    private String recfailreason;         //录制错误的信息
    private int livestate;//直播状态,0-停止直播,1-开始直播
    private String livefailreason;      //用来表示livestate为0时的停止原因,为空或者"default"为正常停止,其它为具体原因
    private String liveplayurl;          //livestate为1开始直播时,终端(主席)显示用

    public String getConfname() {
        return confname;
    }

    public void setConfname(String confname) {
        this.confname = confname;
    }

    public int getConfmode() {
        return confmode;
    }

    public void setConfmode(int confmode) {
        this.confmode = confmode;
    }

    public List<Integer> getParticipants() {
        return participants;
    }

    public void setParticipants(List<Integer> participants) {
        this.participants = participants;
    }

    public int getChairmansuid() {
        return chairmansuid;
    }

    public void setChairmansuid(int chairmansuid) {
        this.chairmansuid = chairmansuid;
    }

    public List<Integer> getAssistchairmans() {
        return assistchairmans;
    }

    public void setAssistchairmans(List<Integer> assistchairmans) {
        this.assistchairmans = assistchairmans;
    }

    public int getDuovideoterid() {
        return duovideoterid;
    }

    public void setDuovideoterid(int duovideoterid) {
        this.duovideoterid = duovideoterid;
    }

    public int getStdterseeingstyle() {
        return stdterseeingstyle;
    }

    public void setStdterseeingstyle(int stdterseeingstyle) {
        this.stdterseeingstyle = stdterseeingstyle;
    }

    public boolean isconflocked() {
        return isconflocked;
    }

    public void setIsconflocked(boolean isconflocked) {
        this.isconflocked = isconflocked;
    }

    public boolean isduovideostart() {
        return isduovideostart;
    }

    public void setIsduovideostart(boolean isduovideostart) {
        this.isduovideostart = isduovideostart;
    }

    public boolean isforcemute() {
        return isforcemute;
    }

    public void setIsforcemute(boolean isforcemute) {
        this.isforcemute = isforcemute;
    }

    public boolean isdisplaytername() {
        return isdisplaytername;
    }

    public void setIsdisplaytername(boolean isdisplaytername) {
        this.isdisplaytername = isdisplaytername;
    }

    public boolean issubtitlestart() {
        return issubtitlestart;
    }

    public void setIssubtitlestart(boolean issubtitlestart) {
        this.issubtitlestart = issubtitlestart;
    }

    public String getSubtitlemsg() {
        return subtitlemsg;
    }

    public void setSubtitlemsg(String subtitlemsg) {
        this.subtitlemsg = subtitlemsg;
    }

    public SubtitleInfo getSubtitle() {
        return subtitle;
    }

    public void setSubtitle(SubtitleInfo subtitle) {
        this.subtitle = subtitle;
    }

    public List<WhiteListInfo> getWhitelists() {
        return whitelists;
    }

    public void setWhitelists(List<WhiteListInfo> whitelists) {
        this.whitelists = whitelists;
    }

    public int getRecstate() {
        return recstate;
    }

    public void setRecstate(int recstate) {
        this.recstate = recstate;
    }

    public String getRecfailreason() {
        return recfailreason;
    }

    public void setRecfailreason(String recfailreason) {
        this.recfailreason = recfailreason;
    }

    public int getLivestate() {
        return livestate;
    }

    public void setLivestate(int livestate) {
        this.livestate = livestate;
    }

    public String getLivefailreason() {
        return livefailreason;
    }

    public void setLivefailreason(String livefailreason) {
        this.livefailreason = livefailreason;
    }

    public String getLiveplayurl() {
        return liveplayurl;
    }

    public void setLiveplayurl(String liveplayurl) {
        this.liveplayurl = liveplayurl;
    }
}
