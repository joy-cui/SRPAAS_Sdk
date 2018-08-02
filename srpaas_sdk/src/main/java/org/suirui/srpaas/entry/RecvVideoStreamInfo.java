package org.suirui.srpaas.entry;

import java.io.Serializable;

/**
 * @authordingna
 * @date2017-01-17
 **/
public class RecvVideoStreamInfo implements Serializable {
    private int id;                                 //接收视频流ID
    private String codecName;                     //接收视频流Name
    private int fps;                                   //接收视频流帧率
    private int bitRate;                           //接收视频流码率(bps)
    private float loseRate;                              //接收视频丢包率
    private int width;                            //接收视频流宽度
    private int height;                           //接收视频流高度

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

    public int getFps() {
        return fps;
    }

    public void setFps(int fps) {
        this.fps = fps;
    }

    public int getBitRate() {
        return bitRate;
    }

    public void setBitRate(int bitRate) {
        this.bitRate = bitRate;
    }

    public float getLoseRate() {
        return loseRate;
    }

    public void setLoseRate(float loseRate) {
        this.loseRate = loseRate;
    }

    public int getWidth() {
        return width;
    }

    public void setWidth(int width) {
        this.width = width;
    }

    public int getHeight() {
        return height;
    }

    public void setHeight(int height) {
        this.height = height;
    }
}
