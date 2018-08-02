package org.suirui.srpaas.sdk;

import org.suirui.srpaas.entry.AuthInfo;

/**
 * 登录注册接口
 *
 * @authordingna
 * @date2017-05-24
 **/
public interface AuthServer {

    void addAuthLoginListener(AuthLoginListener listener);

    void addAuthRegisterListener(AuthRegisterListener listener);

    void addUpdateListener(UpdateUserListener listener);

    /**
     * 注册
     *
     * @param info
     * @return
     */
    void Register(AuthInfo info);

    /**
     * 登录
     *
     * @param info
     * @return
     */
    void Login(AuthInfo info);

    /**
     * 更新用户信息
     */

    void updateUser(AuthInfo info);
    /**
     * 匿名登陆
     *
     * @return
     */
    void tempLogin();
}
