package org.suirui.srpaas.sdk;

import org.suirui.srpaas.entry.UserInfo;

import okhttp3.Call;

/**
 * @authordingna
 * @date2017-06-05
 **/
public interface AuthLoginListener {
    /**
     * 登录错误
     *
     * @param error
     */
    void onLoginError(SRPaas.eLoginError error);

    /**
     * 登录成功
     *
     * @param userInfo
     */
    void onLoginSuccess(UserInfo userInfo);

    /**
     * 服务器相关操作返回的错误
     *
     * @param errorCode
     * @param msg
     */
    void onHttpAuthError(int errorCode, String msg);

    /**
     * 服务器相关操作返回的错误
     *
     * @param call
     * @param e
     * @param i
     */
    void onHttpError(Call call, Exception e, int i);
}
