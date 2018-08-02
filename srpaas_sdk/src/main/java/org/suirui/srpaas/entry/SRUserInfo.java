package org.suirui.srpaas.entry;

/**
 * Created by cui.li on 2016/12/26.
 */

public class SRUserInfo {
    private  int termUId; //passUid
    private  String termUname;
    private int mediagroupid;
    private int userType;
    public SRUserInfo(){

    }
    public SRUserInfo(String termUname, int termUId) {
        this.termUname = termUname;
        this.termUId = termUId;
    }

    public int getTermUId() {
        return termUId;
    }

    public void setTermUId(int termUId) {
        this.termUId = termUId;
    }

    public String getTermUname() {
        return termUname;
    }

    public void setTermUname(String termUname) {
        this.termUname = termUname;
    }

    public int getMediagroupid() {
        return mediagroupid;
    }

    public void setMediagroupid(int mediagroupid) {
        this.mediagroupid = mediagroupid;
    }

    public int getUserType() {
        return userType;
    }

    public void setUserType(int userType) {
        this.userType = userType;
    }

}
