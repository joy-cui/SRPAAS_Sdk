package org.suirui.srpaas.entry;

/**
 * Created by cui.li on 2016/10/17.
 */

public class OnRecvDualVideoOpen {
    private long conf_id;
    private int term_id;
    private int send_id;

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

    public int getSend_id() {
        return send_id;
    }

    public void setSend_id(int send_id) {
        this.send_id = send_id;
    }
}
