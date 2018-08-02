package org.suirui.srpaas.http.bean;

import java.util.List;

/**
 * Created by cui on 2018/4/12.
 */

public class MeetDetailInfoBean {
    public String code;
    public String token;
    public data data;
    public static class data {
        public String confId;
        public String confName;
        public String subject;
        public String confPwd;
        public String suid;
        public String nickname;
        public String createtime;
        public String startTime;
        public String endTime;
        public String confType;
        public String startType;
        public String anonymous;
        public String maxterm;
        public String audioenable;
        public String videoenable;
        public String permanentenable;
        public String ctrluserid;
        public String ctrlpwd;
        public String micautoenable;
        public String camaraautoenable;
        public String encryptalg;
        public String chairman;
        public String chairmanname;
        public String hasStarted;
        public String msgtype;
        public List<Participantes> participates ;
        public List<Participantes> rooms ;

        @Override
        public String toString() {
            return "data{" +
                    "confId='" + confId + '\'' +
                    ", confName='" + confName + '\'' +
                    ", subject='" + subject + '\'' +
                    ", confPwd='" + confPwd + '\'' +
                    ", suid='" + suid + '\'' +
                    ", nickname='" + nickname + '\'' +
                    ", createtime='" + createtime + '\'' +
                    ", startTime='" + startTime + '\'' +
                    ", endTime='" + endTime + '\'' +
                    ", confType='" + confType + '\'' +
                    ", startType='" + startType + '\'' +
                    ", anonymous='" + anonymous + '\'' +
                    ", maxterm='" + maxterm + '\'' +
                    ", audioenable='" + audioenable + '\'' +
                    ", videoenable='" + videoenable + '\'' +
                    ", permanentenable='" + permanentenable + '\'' +
                    ", ctrluserid='" + ctrluserid + '\'' +
                    ", ctrlpwd='" + ctrlpwd + '\'' +
                    ", micautoenable='" + micautoenable + '\'' +
                    ", camaraautoenable='" + camaraautoenable + '\'' +
                    ", encryptalg='" + encryptalg + '\'' +
                    ", chairman='" + chairman + '\'' +
                    ", chairmanname='" + chairmanname + '\'' +
                    ", hasStarted='" + hasStarted + '\'' +
                    ", msgtype='" + msgtype + '\'' +
                    ", participates=" + participates +
                    ", rooms=" + rooms +
                    '}';
        }
    }
    public static class Participantes{
        public String suid;
        public String nickname;
        public String thirduid;
        public String type;

    }

//    public static class Rooms{
//        public String suid;
//        public String nickname;
//        public String thirduid;
//        public String type;
//    }

    @Override
    public String toString() {
        return "MeetDetailInfoBean{" +
                "code='" + code + '\'' +
                ", token='" + token + '\'' +
                ", data=" + data +
                '}';
    }
}
