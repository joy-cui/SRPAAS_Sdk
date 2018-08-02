package org.suirui.srpaas.http.bean;

import android.telecom.Conference;

import java.util.List;

/**
 * Created by cui on 2018/4/8.
 */

public class MeetingListBean {
    public String token;
    public data data;
    public String code;
    public static class data {
        public String timestamp;
        public List<Conference> list;

    }
    public static class Conference{
        public String confId;
        public String confName;
        public String subject;
        public String confPwd;
        public String suid;
        public String nickname;
        public String startTime;
        public String endTime;
        public String confType;
        public String startType;
        public String anonymous;
        public String maxterm;
        public String videoenable;
        public String audioenable;
        public String permanentenable;
        public String ctrluserid;
        public String ctrlpwd;
        public String hasStarted;

    }

    @Override
    public String toString() {
        return "MeetingListBean{" +
                "token='" + token + '\'' +
                ", data='" + data + '\'' +
                ", code='" + code + '\'' +
                '}';
    }
}
