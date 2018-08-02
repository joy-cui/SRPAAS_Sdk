package org.suirui.srpaas.entry;

/**
 * Created by cui.li on 2016/10/17.
 */

public class onRender {
    private int id;
    private int flag;
    private byte[] ybuf;
    private byte[] ubuf;
    private byte[] vbuf;
    private int width;
    private int height;

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public int getFlag() {
        return flag;
    }

    public void setFlag(int flag) {
        this.flag = flag;
    }

    public byte[] getYbuf() {
        return ybuf;
    }

    public void setYbuf(byte[] ybuf) {
        this.ybuf = ybuf;
    }

    public byte[] getUbuf() {
        return ubuf;
    }

    public void setUbuf(byte[] ubuf) {
        this.ubuf = ubuf;
    }

    public byte[] getVbuf() {
        return vbuf;
    }

    public void setVbuf(byte[] vbuf) {
        this.vbuf = vbuf;
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
