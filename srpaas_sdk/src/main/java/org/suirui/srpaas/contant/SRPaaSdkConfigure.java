package org.suirui.srpaas.contant;

/**
 * 传服务器接口需要的类属性
 *
 * @author cui.li
 */
public class SRPaaSdkConfigure {
//	public static String thirdAudioVersion = "";// 第三方音频库版本
//	public static String thirdAudioKey = "";// 第三方音频库key(调用startMeeting需要传递的参数)

    public static final int REPLAY_PORT = 12345;

    public static final String APP_ID = "appId";
    public static final String SECRET_KEY = "secretKey";
    public static final String U_ID = "uid";// 第三方用户唯一标识
    public static final String PHONE = "phone";
    public static final String EMAIL = "email";
    public static final String NICK_NAME = "nickName";
    public static final boolean isEnableIndication = false;//是否显示统计信息

    public static class MeetingInfo {
        public static final String m_serviceId = "serviceId";

        public static final String m_confId = "confId";
        public static final String m_subject = "subject";
        public static final String m_confPwd = "confPwd";
        public static final String m_startTime = "startTime";// 开始时间
        public static final String m_endTime = "endTime";// 结束时间
        public static final String m_confType = "confType";// 会议类型（1：传统会议
        // 2：直播会议)
        public static final String m_startType = "confStartType";// 开启方式（1:定点开启
        // 2:有人进入开启
        // 3:
        // 管理员进入开启）
        public static final String m_livePwd = "livePwd";
        public static final String m_mcAddr = "mcAddr";// mc地址
        public static final String m_relaymcAddr = "relaymcAddr";// relay地址
        public static final String m_relayServer = "relayServer";// relayServer地址
        public static final String m_thirdAudioId = "id3";// 第三方音频库id
        public static final String m_thirdAudioVersion = "version3";// 第三方音频库版本
        public static final String m_thirdAudioKey = "TAK";// 第三方音频库key
        public static final String m_paasUid = "paasUid";
        public static final String m_hasStarted = "hasStarted";
        public static final String m_token = "token";
        public static final String m_audioenable = "audioenable";//是否启用音频
        public static final String m_videoenable = "videoenable";//启用视频

    }

    public static class json {
        public static final String code = "code";

        // public static final String respCode = "respCode";

        public static class meetingInfo {
            public static final String paasToken = "paasToken";
            public static final String conference = "conference";
        }

    }


    public static class AccountInfo {
        public static final String m_login_account = "account";//账号
        public static final String m_appid = "appId";//密码（appid）
        public static final String m_register_phone = "phone";//注册的手机号
        public static final String m_register_nikename = "nikename";//昵称
        public static final String m_pwd = "pwd";//密码
        public static final String m_register_useim = "useIM";//若为1则同时在平台IM创建用户，0不创建
        public static final String m_type = "type";//终端的类型，解决移动端不能登录ubox的账号
    }

    public static class Invite {
        public static final String participants = "participants";
        public static final String sendMsg = "sendMsg";
        public static final String msgType = "msgType";
        public static final String terid = "terid";
        public static final String terName = "terName";
        public static final String confId = "confId";
        public static final String rooms = "rooms";
        public static final String secretKey = "secretKey";
        public static final String appId = "appId";
        public static final String token = "token";
        public static final String SUBJECT="subject";
        public static final String callOption = "callOption";
    }

    public static class MeetListingParams{
        public static final String m_appId="appId";
        public static final String m_secretKey="secretKey";
        public static final String m_token="token";
        public static final String m_timestamp="timestamp";
        public static final String m_start="start";
        public static final String m_itemNumPerPage="itemNumPerPage";
    }


    public static class MeetDetailInfo {
        public static final String confId = "confId";
        public static final String confName = "confName";
        public static final String subject = "subject";
        public static final String confPwd = "confPwd";
        public static final String suid = "suid";
        public static final String nickname = "nickname";
        public static final String createtime="createtime";
        public static final String startTime = "startTime";
        public static final String endTime = "endTime";
        public static final String confType = "confType";
        public static final String startType = "startType";
        public static final String anonymous = "anonymous";
        public static final String maxterm = "maxterm";
        public static final String audioenable = "audioenable";
        public static final String videoenable = "videoenable";
        public static final String permanentenable = "permanentenable";
        public static final String ctrluserid = "ctrluserid";
        public static final String ctrlpwd = "ctrlpwd";
        public static final String micautoenable = "micautoenable";
        public static final String camaraautoenable = "camaraautoenable";
        public static final String encryptalg = "encryptalg";
        public static final String chairman= "chairman";
        public static final String chairmanname = "chairmanname";
        public static final String hasStarted = "hasStarted";
        public static final String msgtype="msgtype";

        public static class Participantes {
            public static final String suid = "suid";
            public static final String nickname = "nickname";
            public static final String thirduid = "thirduid";
            public static final String type = "type";
        }
    }

    public static class SREnginePlatFormType{
        public static final int SR_PLATFORM_TYPE_NONE = 0;
        public static final int SR_PLATFORM_TYPE_WINDOWS=1;
        public static final int SR_PLATFORM_TYPE_ANDROID=2;
        public static final int SR_PLATFORM_TYPE_IOS=3;
        public static final int  SR_PLATFORM_TYPE_LINUX=4;
        public static final int SR_PLATFORM_TYPE_ANDROID_BOX=5;
        public static final int SR_PLATFORM_TYPE_ANDROID_TV=6;
    }
}
