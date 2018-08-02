package org.suirui.srpaas.http.callback;

import org.suirui.srpaas.entry.UserInfo;

import okhttp3.Call;

/**
 * @authordingna
 * @date2017-05-23
 **/
public abstract class RegisterCallBack {
    public void onRegisterSuccess(UserInfo info) {

    }

    public void onError(int errorCode, String msg) {

    }

    public void onError(Call call, Exception e, int i) {

    }
}
