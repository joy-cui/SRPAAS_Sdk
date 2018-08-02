package org.suirui.srpaas.entry;

import java.io.Serializable;

/**
 * 统计信息
 *
 * @authordingna
 * @date2017-01-17
 **/
public class SRSendStreamInfo implements Serializable {
    private String audioCodecName;                 //音频发送编码名称
    private int audioSampleRate;                       //音频发送采样率
    private int audioBitrate;                               //音频发送码率

    private String videoCodecName;                 //视频发送编码名称
    private int videoLFps;                                   //视频发送小流帧率
    private int videoLBitrate;                             //视频发送小流码率
    private int videoLWidth;                               //视频发送小流宽
    private int videoLHeight;                             //视频发送小流高

    private int videoMFps;                                 //视频发送中流帧率
    private int videoMBitrate;                           //视频发送中流码率
    private int videoMWidth;                            //视频发送中流宽
    private int videoMHeight;                           //视频发送中流高

    private int videoHFps;                                 //视频发送大流帧率
    private int videoHBitrate;                           //视频发送大流码率
    private int videoHWidth;                             //视频发送大流宽
    private int videoHHeight;                            //视频发送大流高

    private String h239CodecName;                //视频h239通道发送编码名称
    private int h239Fps;                                    //视频发送桌面共享帧率
    private int h239Bitrate;                              //视频发送桌面共享流码率
    private int h239Width;                               //视频发送桌面共享流宽
    private int h239Height;                              //视频发送桌面共享流高
    private int up_qos_kbps;//上行评估码率
    private int network_state;//网络上行方向的状况

    public String getAudioCodecName() {
        return audioCodecName;
    }

    public void setAudioCodecName(String audioCodecName) {
        this.audioCodecName = audioCodecName;
    }

    public int getAudioSampleRate() {
        return audioSampleRate;
    }

    public void setAudioSampleRate(int audioSampleRate) {
        this.audioSampleRate = audioSampleRate;
    }

    public int getAudioBitrate() {
        return audioBitrate;
    }

    public void setAudioBitrate(int audioBitrate) {
        this.audioBitrate = audioBitrate;
    }

    public String getVideoCodecName() {
        return videoCodecName;
    }

    public void setVideoCodecName(String videoCodecName) {
        this.videoCodecName = videoCodecName;
    }

    public int getVideoLFps() {
        return videoLFps;
    }

    public void setVideoLFps(int videoLFps) {
        this.videoLFps = videoLFps;
    }

    public int getVideoLBitrate() {
        return videoLBitrate;
    }

    public void setVideoLBitrate(int videoLBitrate) {
        this.videoLBitrate = videoLBitrate;
    }

    public int getVideoLWidth() {
        return videoLWidth;
    }

    public void setVideoLWidth(int videoLWidth) {
        this.videoLWidth = videoLWidth;
    }

    public int getVideoLHeight() {
        return videoLHeight;
    }

    public void setVideoLHeight(int videoLHeight) {
        this.videoLHeight = videoLHeight;
    }

    public int getVideoMFps() {
        return videoMFps;
    }

    public void setVideoMFps(int videoMFps) {
        this.videoMFps = videoMFps;
    }

    public int getVideoMBitrate() {
        return videoMBitrate;
    }

    public void setVideoMBitrate(int videoMBitrate) {
        this.videoMBitrate = videoMBitrate;
    }

    public int getVideoMWidth() {
        return videoMWidth;
    }

    public void setVideoMWidth(int videoMWidth) {
        this.videoMWidth = videoMWidth;
    }

    public int getVideoMHeight() {
        return videoMHeight;
    }

    public void setVideoMHeight(int videoMHeight) {
        this.videoMHeight = videoMHeight;
    }

    public int getVideoHFps() {
        return videoHFps;
    }

    public void setVideoHFps(int videoHFps) {
        this.videoHFps = videoHFps;
    }

    public int getVideoHBitrate() {
        return videoHBitrate;
    }

    public void setVideoHBitrate(int videoHBitrate) {
        this.videoHBitrate = videoHBitrate;
    }

    public int getVideoHWidth() {
        return videoHWidth;
    }

    public void setVideoHWidth(int videoHWidth) {
        this.videoHWidth = videoHWidth;
    }

    public int getVideoHHeight() {
        return videoHHeight;
    }

    public void setVideoHHeight(int videoHHeight) {
        this.videoHHeight = videoHHeight;
    }

    public String getH239CodecName() {
        return h239CodecName;
    }

    public void setH239CodecName(String h239CodecName) {
        this.h239CodecName = h239CodecName;
    }

    public int getH239Fps() {
        return h239Fps;
    }

    public void setH239Fps(int h239Fps) {
        this.h239Fps = h239Fps;
    }

    public int getH239Bitrate() {
        return h239Bitrate;
    }

    public void setH239Bitrate(int h239Bitrate) {
        this.h239Bitrate = h239Bitrate;
    }

    public int getH239Width() {
        return h239Width;
    }

    public void setH239Width(int h239Width) {
        this.h239Width = h239Width;
    }

    public int getH239Height() {
        return h239Height;
    }

    public void setH239Height(int h239Height) {
        this.h239Height = h239Height;
    }

    public int getUp_qos_kbps() {
        return up_qos_kbps;
    }

    public void setUp_qos_kbps(int up_qos_kbps) {
        this.up_qos_kbps = up_qos_kbps;
    }

    public int getNetwork_state() {
        return network_state;
    }

    public void setNetwork_state(int network_state) {
        this.network_state = network_state;
    }
}
