package org.suirui.srpaas.http.callback;

import org.suirui.srpaas.entry.UserInfo;

import okhttp3.Call;

/**
 * @authordingna
 * @date2017-05-23
 **/
public abstract class LoginCallBack {
    public void onLoginSuccess(UserInfo userInfo) {

    }

    public void onError(int errorCode, String msg) {

    }

    public void onError(Call call, Exception e, int i) {

    }
}
