package org.suirui.srpaas.http.bean;

/**
 * Created by cui.li on 2017/4/5.
 */

public class MeetingBean {
//    {timestamp=2017-04-05 17:29:21, paasUid=39437226, paasToken=beb7da4ced7c42a085c3c99697f9aa42-1491386361594,
//            code=200, conference={
//            startTime=, hasStarted=0, confId=27263350064, confStartType=3, subject=27263350064, relayServer=[],
//        TAK=S0S5-32CF-E2E0-C0EB-0EFE-C9F3, endTime=,
//            relaymcAddr=[103.249.255.252:4001, 103.249.255.252:4000], mcAddr=4395805749356277818, confType=1}}

    public String timestamp;
    public String paasUid;
    public String paasToken;
    public String code;
    public conference conference;

    public static class conference {
        public String startTime;
        public String hasStarted;
        public String confId;
        public String confStartType;
        public String subject;
        public String[] relayServer;
        public String TAK;
        public String endTime;
        public String[] relaymcAddr;
        public String mcAddr;
        public String confType;
        public String videoenable;
        public String audioenable;
        public String confPwd;
        public String micautoenable;
        public String camaraautoenable;
        public String confName;
        public String mediaGroupId;
        public String OCI;
        public String[] relayMcInfo;
        public String playAddrPrefix;
        public String pullAddrPrefix;
    }

    @Override
    public String toString() {
        return "MeetingBean{" +
                "timestamp='" + timestamp + '\'' +
                ", paasUid='" + paasUid + '\'' +
                ", paasToken='" + paasToken + '\'' +
                ", code='" + code + '\'' +
                ", conference=" + conference +
                '}';
    }
}
