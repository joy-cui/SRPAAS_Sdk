package org.suirui.srpaas.entry;

import java.util.ArrayList;

/**
 * @authordingna
 * @date2017-12-11
 **/
public class SRMediaPInfo {
    private int channelid;
    private ArrayList<SRMediaPScreenInfo> screens;// mp上有很多屏

    public int getChannelid() {
        return channelid;
    }

    public void setChannelid(int channelid) {
        this.channelid = channelid;
    }

    public ArrayList<SRMediaPScreenInfo> getScreens() {
        return screens;
    }

    public void setScreens(ArrayList<SRMediaPScreenInfo> screens) {
        this.screens = screens;
    }
}
