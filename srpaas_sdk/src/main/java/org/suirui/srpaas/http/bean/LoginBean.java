package org.suirui.srpaas.http.bean;

/**
 * @authordingna
 * @date2017-05-23
 **/
public class LoginBean {
    public String code;
    public data data;

    @Override
    public String toString() {
        return "LoginBean{" +
                "code='" + code + '\'' +
                ", data=" + data +
                '}';
    }

    public static class data {
        public String suid;
        public String email;
        public String phone;
        public String nickname;
        public String token;
        public String timestamp;
    }
}
