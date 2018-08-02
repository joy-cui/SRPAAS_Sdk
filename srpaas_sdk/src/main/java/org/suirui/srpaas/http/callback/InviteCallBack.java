package org.suirui.srpaas.http.callback;

import okhttp3.Call;

/**
 * @authordingna
 * @date2017-12-26
 **/
public abstract class InviteCallBack {
    public void onInviteSuccess() {

    }

    public void onError(int errorCode, String msg) {

    }

    public void onError(Call call, Exception e, int i) {

    }
}
