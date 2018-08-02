package org.suirui.srpaas.entry;

/**
 * @authordingna
 * @date2017-12-27
 **/
public class InviteInfo {
    private String participants;
    private int termId;
    private String termName;
    private String confId;
    private String msgType;
    private String token;
    private String appId;
    private String secretKey;
    private String rooms;
    private int sendMsg;
    private String callOption;

    public String getParticipants() {
        return participants;
    }

    public void setParticipants(String participants) {
        this.participants = participants;
    }

    public int getTermId() {
        return termId;
    }

    public void setTermId(int termId) {
        this.termId = termId;
    }

    public String getTermName() {
        return termName;
    }

    public void setTermName(String termName) {
        this.termName = termName;
    }

    public String getConfId() {
        return confId;
    }

    public void setConfId(String confId) {
        this.confId = confId;
    }

    public String getMsgType() {
        return msgType;
    }

    public void setMsgType(String msgType) {
        this.msgType = msgType;
    }

    public String getToken() {
        return token;
    }

    public void setToken(String token) {
        this.token = token;
    }

    public String getAppId() {
        return appId;
    }

    public void setAppId(String appId) {
        this.appId = appId;
    }

    public String getSecretKey() {
        return secretKey;
    }

    public void setSecretKey(String secretKey) {
        this.secretKey = secretKey;
    }

    public String getRooms() {
        return rooms;
    }

    public void setRooms(String rooms) {
        this.rooms = rooms;
    }

    public int getSendMsg() {
        return sendMsg;
    }

    public void setSendMsg(int sendMsg) {
        this.sendMsg = sendMsg;
    }

    public String getCallOption() {
        return callOption;
    }

    public void setCallOption(String callOption) {
        this.callOption = callOption;
    }
}
