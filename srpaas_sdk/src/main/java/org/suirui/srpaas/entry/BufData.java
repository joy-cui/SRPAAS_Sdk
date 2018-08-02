package org.suirui.srpaas.entry;

import java.nio.ByteBuffer;

/**
 * Created by cui on 2018/5/22.
 */

public class BufData {
    private ByteBuffer yData;
    private ByteBuffer uData;
    private ByteBuffer vData;

    public ByteBuffer getyData() {
        return yData;
    }

    public void setyData(ByteBuffer yData) {
        this.yData = yData;
    }

    public ByteBuffer getuData() {
        return uData;
    }

    public void setuData(ByteBuffer uData) {
        this.uData = uData;
    }

    public ByteBuffer getvData() {
        return vData;
    }

    public void setvData(ByteBuffer vData) {
        this.vData = vData;
    }
}
