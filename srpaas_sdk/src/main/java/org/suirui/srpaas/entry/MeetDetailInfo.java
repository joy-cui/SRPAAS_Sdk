package org.suirui.srpaas.entry;

import java.util.List;

/**
 * Created by cui on 2018/4/13.
 */

public class MeetDetailInfo {
    private String confId;
    private String confName;
    private String subject;
    private String confPwd;
    private String suid;
    private String nickname;
    private String  createtime;
    private String startTime;
    private String endTime;
    private String confType;
    private String startType;
    private String anonymous;
    private String maxterm;
    private String audioenable;
    private String videoenable;
    private String permanentenable;
    private String ctrluserid;
    private String ctrlpwd;
    private String micautoenable;
    private String cameraautoenable;
    private String encryptalg;
    private String chairman;
    private String chairmanname;
    private String hasStarted;
    private String msgtype;
    private List<Participantes> participates ;
    private List<Participantes> rooms ;
    public static class Participantes{
        private String suid;
        private String nickname;
        private String thirduid;
        private String type;

        public String getSuid() {
            return suid;
        }

        public void setSuid(String suid) {
            this.suid = suid;
        }

        public String getNickname() {
            return nickname;
        }

        public void setNickname(String nickname) {
            this.nickname = nickname;
        }

        public String getThirduid() {
            return thirduid;
        }

        public void setThirduid(String thirduid) {
            this.thirduid = thirduid;
        }

        public String getType() {
            return type;
        }

        public void setType(String type) {
            this.type = type;
        }
    }


    public String getConfName() {
        return confName;
    }

    public void setConfName(String confName) {
        this.confName = confName;
    }

    public String getSubject() {
        return subject;
    }

    public void setSubject(String subject) {
        this.subject = subject;
    }

    public String getConfPwd() {
        return confPwd;
    }

    public void setConfPwd(String confPwd) {
        this.confPwd = confPwd;
    }

    public String getSuid() {
        return suid;
    }

    public void setSuid(String suid) {
        this.suid = suid;
    }

    public String getNickname() {
        return nickname;
    }

    public void setNickname(String nickname) {
        this.nickname = nickname;
    }

    public String getStartTime() {
        return startTime;
    }

    public void setStartTime(String startTime) {
        this.startTime = startTime;
    }

    public String getEndTime() {
        return endTime;
    }

    public void setEndTime(String endTime) {
        this.endTime = endTime;
    }

    public String getConfType() {
        return confType;
    }

    public void setConfType(String confType) {
        this.confType = confType;
    }

    public String getStartType() {
        return startType;
    }

    public void setStartType(String startType) {
        this.startType = startType;
    }

    public String getAnonymous() {
        return anonymous;
    }

    public void setAnonymous(String anonymous) {
        this.anonymous = anonymous;
    }

    public String getMaxterm() {
        return maxterm;
    }

    public void setMaxterm(String maxterm) {
        this.maxterm = maxterm;
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

    public String getPermanentenable() {
        return permanentenable;
    }

    public void setPermanentenable(String permanentenable) {
        this.permanentenable = permanentenable;
    }

    public String getCtrluserid() {
        return ctrluserid;
    }

    public void setCtrluserid(String ctrluserid) {
        this.ctrluserid = ctrluserid;
    }

    public String getCtrlpwd() {
        return ctrlpwd;
    }

    public void setCtrlpwd(String ctrlpwd) {
        this.ctrlpwd = ctrlpwd;
    }

    public String getMicautoenable() {
        return micautoenable;
    }

    public void setMicautoenable(String micautoenable) {
        this.micautoenable = micautoenable;
    }

    public String getCameraautoenable() {
        return cameraautoenable;
    }

    public void setCameraautoenable(String cameraautoenable) {
        this.cameraautoenable = cameraautoenable;
    }

    public String getEncryptalg() {
        return encryptalg;
    }

    public void setEncryptalg(String encryptalg) {
        this.encryptalg = encryptalg;
    }

    public String getChairmanname() {
        return chairmanname;
    }

    public void setChairmanname(String chairmanname) {
        this.chairmanname = chairmanname;
    }

    public String getHasStarted() {
        return hasStarted;
    }

    public void setHasStarted(String hasStarted) {
        this.hasStarted = hasStarted;
    }

    public String getConfId() {
        return confId;
    }

    public void setConfId(String confId) {
        this.confId = confId;
    }

    public String getCreatetime() {
        return createtime;
    }

    public void setCreatetime(String createtime) {
        this.createtime = createtime;
    }

    public String getChairman() {
        return chairman;
    }

    public void setChairman(String chairman) {
        this.chairman = chairman;
    }

    public String getMsgtype() {
        return msgtype;
    }

    public void setMsgtype(String msgtype) {
        this.msgtype = msgtype;
    }

    public List<Participantes> getParticipates() {
        return participates;
    }

    public void setParticipates(List<Participantes> participates) {
        this.participates = participates;
    }

    public List<Participantes> getRooms() {
        return rooms;
    }

    public void setRooms(List<Participantes> rooms) {
        this.rooms = rooms;
    }
}
