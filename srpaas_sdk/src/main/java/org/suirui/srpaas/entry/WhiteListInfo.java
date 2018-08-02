package org.suirui.srpaas.entry;

import java.util.List;

/**
 * @authordingna
 * @date2017-10-31
 **/
public class WhiteListInfo {
    private int whitelisttype;                //白名单类型,0-主席模式白名单、1-直播模式白名单
    private List<Integer> terlists;       //白名单列表,参会者suid集合

    public int getWhitelisttype() {
        return whitelisttype;
    }

    public void setWhitelisttype(int whitelisttype) {
        this.whitelisttype = whitelisttype;
    }

    public List<Integer> getTerlists() {
        return terlists;
    }

    public void setTerlists(List<Integer> terlists) {
        this.terlists = terlists;
    }
}
