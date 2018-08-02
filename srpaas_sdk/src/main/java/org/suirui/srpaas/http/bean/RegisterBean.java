package org.suirui.srpaas.http.bean;

/**
 * @authordingna
 * @date2017-05-23
 **/
public class RegisterBean {

    public String code;
    public data data;

    @Override
    public String toString() {
        return "RegisterBean{" +
                "code='" + code + '\'' +
                ", data=" + data +
                '}';
    }

    public static class data {
        public String suid;
        public String nickName;
    }
}
