package org.suirui.srpaas.http.bean;

/**
 * Created by cui on 2018/4/12.
 */

public class HasPwdBean {
    public String code;
    public String token;
    public String confId;
    public String hasPwd;//是否有密码 1是 0否

    @Override
    public String toString() {
        return "HasPwdBean{" +
                "code='" + code + '\'' +
                ", token='" + token + '\'' +
                ", confId='" + confId + '\'' +
                ", hasPwd='" + hasPwd + '\'' +
                '}';
    }
}
