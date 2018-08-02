package org.suirui.srpaas.entry;

import java.io.Serializable;

/**
 * @authordingna
 * @date2017-01-17
 **/
public class RecvAudioStreamInfo implements Serializable {
    private int id;                                                  //接收音频流id
    private String codecName;                             //接收音频流Name
    private int sampleRate;                                  //接收音频流采样率
    private int bitRate;                                          //接收音频流码率 (bps)
    private int recCodecChs;                                //接收音频流通道（1：单声道，2：立体音）
    private float loseRate;                                      //接收音频流丢包率

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public String getCodecName() {
        return codecName;
    }

    public void setCodecName(String codecName) {
        this.codecName = codecName;
    }

    public int getSampleRate() {
        return sampleRate;
    }

    public void setSampleRate(int sampleRate) {
        this.sampleRate = sampleRate;
    }

    public int getBitRate() {
        return bitRate;
    }

    public void setBitRate(int bitRate) {
        this.bitRate = bitRate;
    }

    public int getRecCodecChs() {
        return recCodecChs;
    }

    public void setRecCodecChs(int recCodecChs) {
        this.recCodecChs = recCodecChs;
    }

    public float getLoseRate() {
        return loseRate;
    }

    public void setLoseRate(float loseRate) {
        this.loseRate = loseRate;
    }
}
