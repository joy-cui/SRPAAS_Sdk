package org.suirui.srpaas.entry;

import java.util.List;

/**
 * Created by cui.li on 2016/10/17.
 */

public class onRspConfTermList {
    private boolean status;
    private long confId;
    private int termId;
    private int masterId;
    private int duoTermId;
    private List<TermInfo> termInfoList;
    private String failReason;

    public boolean isStatus() {
        return status;
    }

    public void setStatus(boolean status) {
        this.status = status;
    }

    public long getConfId() {
        return confId;
    }

    public void setConfId(long confId) {
        this.confId = confId;
    }

    public int getTermId() {
        return termId;
    }

    public void setTermId(int termId) {
        this.termId = termId;
    }

    public int getMasterId() {
        return masterId;
    }

    public void setMasterId(int masterId) {
        this.masterId = masterId;
    }

    public int getDuoTermId() {
        return duoTermId;
    }

    public void setDuoTermId(int duoTermId) {
        this.duoTermId = duoTermId;
    }

    public List<TermInfo> getTermInfoList() {
        return termInfoList;
    }

    public void setTermInfoList(List<TermInfo> termInfoList) {
        this.termInfoList = termInfoList;
    }

    public String getFailReason() {
        return failReason;
    }

    public void setFailReason(String failReason) {
        this.failReason = failReason;
    }
}
