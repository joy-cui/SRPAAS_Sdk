package org.suirui.srpaas.http.callback;

/**
 * Created by cui on 2018/4/12.
 */

public interface OnHasPwdCallBack {
    void onError(int code,String msg);

    /**
     * 是否有密码
     * @param confId
     * @param hasPwd
     */
    void onSuccess(String confId,boolean hasPwd);
}
