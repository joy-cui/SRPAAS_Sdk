package org.suirui.srpaas.entry;

import java.util.ArrayList;
import java.util.List;

/**
 * Created by cui.li on 2016/12/26.
 */

public class SRSdkConferenceInfo {
    public long conferenceId;//会议号
    public String password;//会议密码
    public ArrayList<McAdress> relaymcInfo;// (relaymc_info;//例如:10.10.10.10:2000)list显示
    public long pandPort;//对应meetingfo中的mc_addr
    public String relay_server; //relay server 192.168.1.1:8000/192.168.1.2:8003
    public String OCI;//当前在线会议客户端数量信息
    public SRSdkConferenceInfo(){

    }

    public SRSdkConferenceInfo(long conferenceId, String relay_server, long pandPort, ArrayList<McAdress> relaymcInfo, String password) {
        this.conferenceId = conferenceId;
        this.relay_server = relay_server;
        this.pandPort = pandPort;
        this.relaymcInfo = relaymcInfo;
        this.password = password;
    }

    public long getConferenceId() {
        return conferenceId;
    }

    public void setConferenceId(long conferenceId) {
        this.conferenceId = conferenceId;
    }

    public String getPassword() {
        return password;
    }

    public void setPassword(String password) {
        this.password = password;
    }

    public List<McAdress> getRelaymcInfo() {
        return relaymcInfo;
    }

    public void setRelaymcInfo(ArrayList<McAdress> relaymcInfo) {
        this.relaymcInfo = relaymcInfo;
    }

    public long getPandPort() {
        return pandPort;
    }

    public void setPandPort(long pandPort) {
        this.pandPort = pandPort;
    }

    public String getRelay_server() {
        return relay_server;
    }

    public void setRelay_server(String relay_server) {
        this.relay_server = relay_server;
    }

    public String getOCI() {
        return OCI;
    }

    public void setOCI(String OCI) {
        this.OCI = OCI;
    }
}
