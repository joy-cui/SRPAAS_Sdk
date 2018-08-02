package org.suirui.srpaas.sdk;

public class SRPaas {
    public enum eHttpError {
        eMeetingHttp_error_NO_CONFID,//会议号不存在
        eMeetingHttp_error, // 服务器连接错误
        eMeetingHttp_param_error;// 服务器参数错误

    }

    // 离开会议命令类型
    public enum eLeaveMeetingCmd {
        eLeaveDefault(false), // 离开会议，不结束
        eLeaveEndMeeting(true);// 离开并结束会议
        private boolean type;

        // 构造方法
        private eLeaveMeetingCmd(boolean type) {
            this.type = type;
        }

        public boolean getValue() {
            return type;
        }
    }

    // 会控类型
    public enum eMeetingControlType {
        eMeetingControlType_Mute, // 静音
        eMeetingControlType_HandUp, // 举手
        eMeetingControlType_DropTerminal, // 请终端离开
        eMeetingControlType_MasterTransfer// 主持人权限转移
    }

    // 会议错误
    public enum eMeetingError {
        eMeetingNoError, // 无错误
        eMeetingError_InvalidMeetingNumber, // 非法会议号
        eMeetingError_DeviceError, // 设备错误
        eMeetingError_ServerConnetError, // 服务器连接错误
        eMeetingError_InitMcuFailer, // 初始化失败
        eMeetingError_JoinMeetingFailer, // 加入会议失败
        eMeetingError_StaratMeetingFailer,// 開始会议失败
        eMeetingError_PASSWORD_WRONG,//密码错误
        eMeetingError_CHAIR_FIRST,//加入会议失败（主持人未入会）
        eMeetingError_GETAPM_MAC_ERROR,//获取apm认证mac信息失败
    }

    // 会议状态
    public enum Enumerator {
        eMeetingState_Idle, // 空闲
        eMeetingState_Connecting, // 入会中
        eMeetingState_InMeeting, // 会议中
        eMeetingState_OutMeeting// 退出中
    }

    public enum VideoType {
        SR_CFG_VIDEO_CLOSE(0),                                        //关闭选看的终端视频流(注:不会自动关闭桌面共享流)
        SR_CFG_VIDEO_SIZE_90P(1),                        //160*90
        SR_CFG_VIDEO_SIZE_144P(2),                        //256*144
        SR_CFG_VIDEO_SIZE_180P(3),                        //320*180
        SR_CFG_VIDEO_SIZE_216P(4),                        //384*216
        SR_CFG_VIDEO_SIZE_240P(5),                        //432*240
        SR_CFG_VIDEO_SIZE_270P(6),                        //480*270
        SR_CFG_VIDEO_SIZE_360P(7),                        //640*360
        SR_CFG_VIDEO_SIZE_480P(8),                        //846*480
        SR_CFG_VIDEO_SIZE_540P(9),                        //960*540
        SR_CFG_VIDEO_SIZE_720P(10),                        //1280*720
        SR_CFG_VIDEO_SIZE_1080P(11),                    //1920*1080
        SR_CFG_VIDEO_SIZE_1440P(12),                    //2560*1440
        SR_CFG_VIDEO_SIZE_2160P(13),                    //3840*2160
        SR_CFG_VIDEO_SIZE_4320P(14),                    //6480*4320
        //选看终端的桌面共享流
        SR_CFG_DESKTOP_OPEN(15),
        SR_CFG_DESKTOP_CLOSE(16);                                //关闭终端的桌面共享流


        private int type;

        // 构造方法
        private VideoType(int type) {
            this.type = type;
        }

        public int getValue() {
            return type;
        }
    }

    public enum SRVideoStreamType {
        kSRScreenStream(0), // 数据共享
        kSRVideoStream(1);// 视频流
        private int type;

        private SRVideoStreamType(int type) {
            this.type = type;
        }

        public int getValue() {
            return type;
        }
    }


    //采集数据的格式
    public enum SRVideoRawFormat {
        SR_FORMAT_RAW_TYPE_YUV420(0),  //YUV 420 format
        SR_FORMAT_RAW_TYPE_NV12(1),  //NV12 format
        SR_FORMAT_RAW_TYPE_NV21(2),  //NV21 format
        SR_FORMAT_RAW_TYPE_YV12(3),  //YV12 format
        SR_FORMAT_RAW_TYPE_RGB(4),
        SR_FORMAT_RAW_TYPE_ARGB(5);
        private int type;

        private SRVideoRawFormat(int type) {
            this.type = type;
        }

        public int getValue() {
            return type;
        }
    }


    //采集的视频要旋转的角度
    public enum SRVideoRotation {
        SR_ROTATION_MODE_NONE(0),
        SR_ROTATION_MODE_90(90),
        SR_ROTATION_MODE_180(180),
        SR_ROTATION_MODE_270(270);
        private int type;

        private SRVideoRotation(int type) {
            this.type = type;
        }

        public int getValue() {
            return type;
        }
    }

    public enum SRErrorCode {
        SR_RTC_SUCCESS,
        ERR_STACK_HEAT_BEAT_TIMEOUT,
        ERR_STACK_CONNECT_ERROR,
        ERR_STACK_HEARTBEATTIMEOUT,
        ERR_RELAY_SERVER_CRASH,
        ERR_REQ_TERMLIST_TIMEOUT,
        ERR_RSP_SENDDUAL_VIDEO_BUY,
        ERR_RSP_SENDDUAL_VIDEO_BY_PEER,
        ERR_INITIALIZATION_MC_PROTOCAL_STATCK_FAILED,
        ERR_MC_PROTOCAL_STATCK,
        ERR_REASON_UNKONOWN,
        ERR_REASON_BY_USER,
        ERR_NONE,
        ERR_STREAM_STATE_TIMEOUT;
    }

    //登录错误
    public enum eLoginError {
        eLoginError_InvalidAccount,//非法账号
        eLoginError_ACCOUNT,//账号错误
        eLoginError_Pwd,//密码错误
    }

    //错误
    public enum eError {
        eError_Parm_Null,//
        eError_Error,//
    }

    //注册错误
    public enum eRegisterError {
        eRegisterError_InvalidAccount,//非法账号
        eRegisterError_ACCOUNT,//账号错误
        eRegisterError_Appid,//appid错误
        eRegisterError_Nikename,//昵称错误
        eRegisterError_Pwd,//密码错误
        eRegisterError_Url,//服务地址错误
        eRegisterError_UNknow,//
    }

    public static class Delayflag {
        public static final int Delayflag_0 = 0;// 0:立即处理
        public static final int Delayflag_1 = 1;//1:延迟处理
    }
}
