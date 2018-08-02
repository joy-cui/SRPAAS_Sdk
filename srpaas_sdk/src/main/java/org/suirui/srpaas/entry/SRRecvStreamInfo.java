package org.suirui.srpaas.entry;

import java.io.Serializable;
import java.util.ArrayList;

/**
 * 统计信息
 *
 * @authordingna
 * @date2017-01-17
 **/
public class SRRecvStreamInfo implements Serializable{
    ArrayList<RecvAudioStreamInfo> recvAudioStreamInfoList;//音频
    ArrayList<RecvVideoStreamInfo> recvVideoStreamInfoList;//视频
    RecvVideoStreamInfo recvH239StreamInfo;//h239
    int down_qos_kbps;//下行评估码率
    int network_status;//网络下行方向的状况

    public ArrayList<RecvAudioStreamInfo> getRecvAudioStreamInfoList() {
        return recvAudioStreamInfoList;
    }

    public void setRecvAudioStreamInfoList(ArrayList<RecvAudioStreamInfo> recvAudioStreamInfoList) {
        this.recvAudioStreamInfoList = recvAudioStreamInfoList;
    }

    public ArrayList<RecvVideoStreamInfo> getRecvVideoStreamInfoList() {
        return recvVideoStreamInfoList;
    }

    public void setRecvVideoStreamInfoList(ArrayList<RecvVideoStreamInfo> recvVideoStreamInfoList) {
        this.recvVideoStreamInfoList = recvVideoStreamInfoList;
    }

    public RecvVideoStreamInfo getRecvH239StreamInfo() {
        return recvH239StreamInfo;
    }

    public void setRecvH239StreamInfo(RecvVideoStreamInfo recvH239StreamInfo) {
        this.recvH239StreamInfo = recvH239StreamInfo;
    }

    public int getDown_qos_kbps() {
        return down_qos_kbps;
    }

    public void setDown_qos_kbps(int down_qos_kbps) {
        this.down_qos_kbps = down_qos_kbps;
    }

    public int getNetwork_status() {
        return network_status;
    }

    public void setNetwork_status(int network_status) {
        this.network_status = network_status;
    }
}
