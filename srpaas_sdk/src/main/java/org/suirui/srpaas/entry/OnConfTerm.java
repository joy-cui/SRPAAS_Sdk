package org.suirui.srpaas.entry;

/**
 * Created by cui.li on 2016/10/17.
 */

public class OnConfTerm {
    private long conf_id;
    private int term_id;
    private boolean isOk;
    private String reason;
    private TermInfo termInfo;
    private boolean isMute;
    private int otherTermId;
    private String othername;
    private int staClass;
    private int staSubCls;

    public long getConf_id() {
        return conf_id;
    }

    public void setConf_id(long conf_id) {
        this.conf_id = conf_id;
    }

    public int getTerm_id() {
        return term_id;
    }

    public void setTerm_id(int term_id) {
        this.term_id = term_id;
    }

    public boolean isOk() {
        return isOk;
    }

    public void setOk(boolean ok) {
        isOk = ok;
    }

    public String getReason() {
        return reason;
    }

    public void setReason(String reason) {
        this.reason = reason;
    }

    public TermInfo getTermInfo() {
        return termInfo;
    }

    public void setTermInfo(TermInfo termInfo) {
        this.termInfo = termInfo;
    }


    public boolean isMute() {
        return isMute;
    }

    public void setMute(boolean mute) {
        isMute = mute;
    }


    public int getOtherTermId() {
        return otherTermId;
    }

    public void setOtherTermId(int otherTermId) {
        this.otherTermId = otherTermId;
    }

    public String getOthername() {
        return othername;
    }

    public void setOthername(String othername) {
        this.othername = othername;
    }

    public int getStaClass() {
        return staClass;
    }

    public void setStaClass(int staClass) {
        this.staClass = staClass;
    }

    public int getStaSubCls() {
        return staSubCls;
    }

    public void setStaSubCls(int staSubCls) {
        this.staSubCls = staSubCls;
    }
}
