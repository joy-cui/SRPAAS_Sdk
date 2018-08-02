package org.suirui.srpaas.entry;

/**
 * Created by cui.li on 2016/12/31.
 */

public class SRError {

    private int cur_error;
    private String brief_reason;
    private String detail_reason;//暂时不用


    public int getCur_error() {
        return cur_error;
    }

    public void setCur_error(int cur_error) {
        this.cur_error = cur_error;
    }

    public String getBrief_reason() {
        return brief_reason;
    }

    public void setBrief_reason(String brief_reason) {
        this.brief_reason = brief_reason;
    }

    public String getDetail_reason() {
        return detail_reason;
    }

    public void setDetail_reason(String detail_reason) {
        this.detail_reason = detail_reason;
    }
}
