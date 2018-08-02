package org.suirui.srpaas.entry;

/**
 * Created by cui.li on 2016/10/17.
 */

public class OnJoinConf {
    private boolean status;
    private String failReason;
    private int tearId;

    public boolean isStatus() {
        return status;
    }

    public void setStatus(boolean status) {
        this.status = status;
    }

    public String getFailReason() {
        return failReason;
    }

    public void setFailReason(String failReason) {
        this.failReason = failReason;
    }

    public int getTearId() {
        return tearId;
    }

    public void setTearId(int tearId) {
        this.tearId = tearId;
    }
}
