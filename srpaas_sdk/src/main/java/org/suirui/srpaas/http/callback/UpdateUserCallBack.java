package org.suirui.srpaas.http.callback;

import org.suirui.srpaas.entry.UserInfo;
import org.suirui.srpaas.http.bean.LoginBean;

import okhttp3.Call;


public abstract class UpdateUserCallBack {
    public void onUpdateSuccess(LoginBean userInfo) {

    }

    public void onError(int errorCode, String msg) {

    }

    public void onError(Call call, Exception e, int i) {

    }
}
