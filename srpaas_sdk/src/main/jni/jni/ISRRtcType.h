#ifndef SUIRUI_RTC_TYPE_API_H_H_
#define SUIRUI_RTC_TYPE_API_H_H_

#ifdef _WIN32
#include <Windows.h> //For HWND defination
#endif


#include <stdio.h>
#include <string.h>
#include <string>
#include <deque>
#include <list>

#ifndef _WIN32
#include <stdint.h>
typedef  void*  HWND;
typedef uint64_t UINT64;
typedef uint32_t UINT32;
typedef int64_t  INT64;
typedef int32_t  INT32;
#endif
using namespace std;

namespace suirui
{
    namespace rtc
    {
        typedef void* view_t;

        enum SR_VIDEO_RAW_FORMAT_TYPE
        {
            SR_FORMAT_RAW_TYPE_YUV420 = 0,  //YUV 420 format
            SR_FORMAT_RAW_TYPE_NV12,        //NV12 format
            SR_FORMAT_RAW_TYPE_NV21,        //NV21 format
            SR_FORMAT_RAW_TYPE_YV12,        //YV12 format
            SR_FORMAT_RAW_TYPE_RGB,         //RGB format
            SR_FORMAT_RAW_TYPE_ARGB,        //ARGB format
            SR_FORMAT_RAW_TYPE_264,        //264 format
        };

        enum SR_VIDEO_RAW_ROTATION_MODE
        {
            SR_ROTATION_MODE_NONE = 0,
            SR_ROTATION_MODE_90 = 90,
            SR_ROTATION_MODE_180 = 180,
            SR_ROTATION_MODE_270 = 270,
        };


        enum SR_VIDEO_STREAM_TYPE
        {
            SR_TYPE_SCREEN_STREAM = 0,
            SR_TYPE_VIDEO_STREAM,
        };

        //SR_CFG_VIDEO_SIZE_1080HP 编1080p码率更高
        enum SR_CFG_SELECT_VIDEO_STREAM
        {
            SR_CFG_VIDEO_CLOSE = 0,                     //关闭选看的终端视频流(注:不会自动关闭桌面共享流)
            SR_CFG_VIDEO_SIZE_90P,                      //160*90           1
            SR_CFG_VIDEO_SIZE_144P,                     //256*144     2
            SR_CFG_VIDEO_SIZE_180P,                     //320*180     3
            SR_CFG_VIDEO_SIZE_216P,                     //384*216     4
            SR_CFG_VIDEO_SIZE_240P,                     //432*240     5
            SR_CFG_VIDEO_SIZE_270P,                     //480*270     6
            SR_CFG_VIDEO_SIZE_360P,                     //640*360     7
            SR_CFG_VIDEO_SIZE_480P,                     //846*480     8
            SR_CFG_VIDEO_SIZE_540P,                     //960*540     9
            SR_CFG_VIDEO_SIZE_720P,                     //1280*720    10
            SR_CFG_VIDEO_SIZE_1080P,                    //1920*1080   11
            SR_CFG_VIDEO_SIZE_1080HP,                   //1920*1080   12
            SR_CFG_VIDEO_SIZE_1440P,                    //2560*1440   13
            SR_CFG_VIDEO_SIZE_2160P,                    //3840*2160   14

            SR_CFG_DESKTOP_OPEN,                        //选看终端的桌面共享流   15
            SR_CFG_DESKTOP_CLOSE,                       //关闭终端的桌面共享流   16
        };

        enum SR_MAX_DEVICE_ID_LENGTH_TYPE
        {
            SR_MAX_DEVICE_ID_LENGTH = 128,
            SR_MAX_FILE_ID_LENGTH = 256,
            SR_MAX_STRING_ID_LENGTH = 256,
            SR_MAX_BUFFER_ID_LENGTH = 256,
            SR_MAX_NET_ID_LENGTH = 64
        };

        //定义对称加密方式
        enum SR_S_CRYPTION_MODE_TYPE
        {
            SR_S_CRYPTION_MODE_NONE = 0,
            SR_S_CRYPTION_MODE_SM4,
            SR_S_CRYPTION_MODE_AES,
        };

        //定义非对称加密方式
        enum SR_A_CRYPTION_MODE_TYPE
        {
            SR_A_CRYPTION_MODE_NONE = 0,
            SR_A_CRYPTION_MODE_SM2,
        };

        enum SR_WARN_CODE_TYPE
        {
            WARN_PENDING = 20,

        };

        //设备热插拔方式
        enum SR_DEVICE_CHANGE_TYPE
        {
            SR_CAMERA_DEVICE_CHANGE_ADD = 0,
            SR_CAMERA_DEVICE_CHANGE_REMOVE,

            SR_AUDIO_INPUTDEVICE_CHANGE_ADD = 10,
            SR_AUDIO_INPUTDEVICE_CHANGE_REMOVE,           //11
            SR_AUDIO_OUTPUTDEVICE_CHANGE_ADD,             //12
            SR_AUDIO_OUTPUTDEVICE_CHANGE_REMOVE,          //13
            SR_AUDIO_INOUTPUTDEVICE_CHANGE_ADD,           //14
            SR_AUDIO_INOUTPUTDEVICE_CHANGE_REMOVE,        //15
        };



        enum SREngineShareDeskSts
        {
            kDualStatusIdle = 0,
            kDualStatusSendingStream,
            kDualStatusRecvingStream,
        };

        //网络类型
        enum SREngineNetworkType
        {
            SR_NETWORK_TYPE_NONE = 0,
            SR_NETWORK_TYPE_WIRE,
            SR_NETWORK_TYPE_VPN,
            SR_NETWORK_TYPE_ADSL,
            SR_NETWORK_TYPE_WIFI,
            SR_NETWORK_TYPE_2G,
            SR_NETWORK_TYPE_3G_TD,
            SR_NETWORK_TYPE_3G_WCDMA,
            SR_NETWORK_TYPE_3G_CDMA2000,
            SR_NETWORK_TYPE_4G_TDD,
            SR_NETWORK_TYPE_4G_FDD
        };

        //网络状况
        enum SREngineNetworkStatus
        {
            SR_NETWORK_STATUS_NONE = 0,     //暂时不知道
            SR_NETWORK_STATUS_POOR,          //极差
            SR_NETWORK_STATUS_GENERAL,    //一般
            SR_NETWORK_STATUS_GOOD         //很好
        };

        //运营商类型
        enum SREngineNetworkOperator
        {
            SR_NETWORK_OPERATOR_TYPE_NONE = 0,
            SR_NETWORK_OPERATOR_TYPE_CMCC,     //中国移动
            SR_NETWORK_OPERATOR_TYPE_CUCC,     //中国联通
            SR_NETWORK_OPERATOR_TYPE_CTCC      //中国电信
        };

        //平台类型
        enum SREnginePlatFormType
        {
            SR_PLATFORM_TYPE_NONE = 0,
            SR_PLATFORM_TYPE_WINDOWS,
            SR_PLATFORM_TYPE_ANDROID,
            SR_PLATFORM_TYPE_IOS,
            SR_PLATFORM_TYPE_LINUX,
            SR_PLATFORM_TYPE_ANDROID_BOX
        };


        //终端设置当前的cpu
        class SRCpuUsageParam
        {
        public:
            short       usage; //使用率百分比 %57----57整数
            char        flag;  //自定义的标志
            SRCpuUsageParam()
                : usage(0)
                , flag(0)
            {
            }
            //  copy constructor
            SRCpuUsageParam(const SRCpuUsageParam &other)
            {
                usage = other.usage;
                flag = other.flag;
            }

            // // Equal overload
            SRCpuUsageParam & operator =(const SRCpuUsageParam &other)
            {
                // (1) Check self
                if(this == &other)
                    return *this;

                // (2) Free original memory resources
                // （3）Allocate new memory resources, copy the content
                usage = other.usage;
                flag = other.flag;
                // （4）Returns a reference to this object
                return *this;
            }
        };


        //网络消息设置
        class SRNetWorkInfoParam
        {
        public:
            SREngineNetworkType      network_type;                 //网络类型
            SREngineNetworkOperator  network_operator;        //网络运营商
            SREnginePlatFormType       platform_type;               //平台类型

            SRNetWorkInfoParam()
                : network_type(SR_NETWORK_TYPE_NONE)
                , network_operator(SR_NETWORK_OPERATOR_TYPE_NONE)
                , platform_type(SR_PLATFORM_TYPE_NONE)
            {
            }

            //  copy constructor
            SRNetWorkInfoParam(const SRNetWorkInfoParam &other)
            {
                network_type = other.network_type;
                network_operator = other.network_operator;
                platform_type = other.platform_type;
            }

            // // Equal overload
            SRNetWorkInfoParam & operator =(const SRNetWorkInfoParam &other)
            {
                // (1) Check self
                if(this == &other)
                    return *this;

                // (2) Free original memory resources
                // （3）Allocate new memory resources, copy the content
                network_type = other.network_type;
                network_operator = other.network_operator;
                platform_type = other.platform_type;
                // （4）Returns a reference to this object
                return *this;
            }

        };


        //用户需要通知sdk的信息
        class SRUserSetParam
        {
        public:
            bool  has_cpu_param;            //是否需要通知cpu消息
            SRCpuUsageParam cpu_param;

            bool  has_network_param;        //是否需要通知网络消息
            SRNetWorkInfoParam network_param;


            SRUserSetParam()
                : has_cpu_param(false)
                , has_network_param(false)
            {
            }

            //  copy constructor
            SRUserSetParam(const SRUserSetParam &other)
            {
                has_cpu_param = other.has_cpu_param;
                cpu_param = other.cpu_param;
                has_network_param = other.has_network_param;
                network_param = other.network_param;
            }

            // // Equal overload
            SRUserSetParam & operator =(const SRUserSetParam &other)
            {
                // (1) Check self
                if(this == &other)
                    return *this;

                // (2) Free original memory resources
                // （3）Allocate new memory resources, copy the content
                has_cpu_param = other.has_cpu_param;
                cpu_param = other.cpu_param;
                has_network_param = other.has_network_param;
                network_param = other.network_param;
                // （4）Returns a reference to this object
                return *this;
            }
        };



        class SRUseApmType
        {
        public:
            std::string version3;
            std::string id3;
            std::string appId; //需要用户自己去填写
            std::string clientModel;
            std::string clientVersion;

            SRUseApmType(std::string _version3, std::string _id3, std::string _appId, std::string _clientModel, std::string _clientVersion)
                : version3(_version3)
                , id3(_id3)
                , appId(_appId)
                , clientModel(_clientModel)
                , clientVersion(_clientVersion)
            {
            }

            SRUseApmType()
                : version3("")
                , id3("")
                , appId("")
                , clientModel("")
                , clientVersion("")
            {
            }

            ~SRUseApmType()
            {
            }

        };

        //加密方式类型
        class CryptionContent
        {
        public:
            //key Symmetric 对称加密
            SR_S_CRYPTION_MODE_TYPE s_mode;
            std::string s_secretkey;
            //key aSymmetric非对称加密
            SR_A_CRYPTION_MODE_TYPE a_mode;
            std::string a_publickey;
            std::string a_privatekey;


            CryptionContent()
                : s_mode(SR_S_CRYPTION_MODE_NONE)
                , s_secretkey("")
                , a_mode(SR_A_CRYPTION_MODE_NONE)
                , a_publickey("")
                , a_privatekey("")
            {}

            //  copy constructor
            CryptionContent(const CryptionContent &other)
            {
                s_mode = other.s_mode;
                s_secretkey = other.s_secretkey;
                a_mode = other.a_mode;
                a_publickey = other.a_publickey;
                a_privatekey = other.a_privatekey;
            }

            // // Equal overload
            CryptionContent & operator =(const CryptionContent &other)
            {
                // (1) Check self
                if(this == &other)
                    return *this;

                // (2) Free original memory resources
                s_secretkey.clear();
                a_publickey.clear();
                a_privatekey.clear();
                // （3）Allocate new memory resources, copy the content
                s_mode = other.s_mode;
                s_secretkey = other.s_secretkey;
                a_mode = other.a_mode;
                a_publickey = other.a_publickey;
                a_privatekey = other.a_privatekey;
                // （4）Returns a reference to this object
                return *this;
            }
        };


        enum SR_ERROR_CODE_TYPE
        {
            SR_RTC_SUCCESS = 0,

            ERR_STACK_CONNECT_ERROR = 50,
            ERR_STACK_HEARTBEATTIMEOUT,
            ERR_STACK_RECONNECT_DOREQUESTTERMLIST,

            ERR_RELAY_SERVER_CRASH,


            ERR_REQ_TERMLIST_TIMEOUT = 101,
            ERR_STREAM_STATE_TIMEOUT = 102,

            ERR_RSP_SENDDUAL_VIDEO_BUY = 201,
            ERR_RSP_SENDDUAL_VIDEO_BY_PEER,

            ERR_INITIALIZATION_MC_PROTOCAL_STATCK_FAILED = 6000,
            ERR_MC_PROTOCAL_STATCK = 6001,

            ERR_REASON_UNKONOWN = 7000,

            ERR_REASON_BY_USER = 8000,

            ERR_NONE = 11000
        };

		enum SR_OK_CODE_TYPE
		{
			SR_OK_SUCCESS = 0,
			SR_STACK_RECONNECT_OK = 1200

		};

        enum SREngineTermType
        {
            SR_TERM_TYPE_MEDIA_PROCESS_DEMO = 0, //媒体处理实例
            SR_TERM_TYPE_PHONE,                  //移动
            SR_TERM_TYPE_PC,                     //PC
            SR_TERM_TYPE_TV,                     //tv
        };


        enum SREngineFromType
        {
            SR_FROMTERM_SUIRUI_PLATFORM = 0,     //来自随锐平台(即随锐自有RP终端)
            SR_FROMTERM_SUIRUI_GATEWAY = 1,     //来自随锐网关(即H.323终端、SIP终端)
        };


        //终端类型
        enum SREngineUserType
        {
            SR_FROMTERM_SUIRUI_USER_TEMP = 0,  //0-临时(匿名)用户
            SR_FROMTERM_SUIRUI_USER_OFFICIAL = 1,  //1-正式(注册)用户
            SR_FROMTERM_SUIRUI_USER_UBOX = 2,  //2-Ubox
            SR_FROMTERM_SUIRUI_USER_STANDARD = 3,  //3-标准终端(H.323/sip)
        };


        class VideoAndAudioParameter
        {
        public:
            //针对视频
            //摄像头采集的（宽，高，帧率）
            int CollectWidth;
            int CollectHeight;
            int CollectFps;

            //最大编码（宽，高，帧率）
            int EncodeHighWidth;
            int EncodeHighHeight;
            int EncodeHighFps;

            //最大编码码率
            int EncodeHighStartBitrate;  //开始码率
            int EncodeHighMinBitrate;    //最小码率
            int EncodeHighMaxBitrate;    //最大码率

            VideoAndAudioParameter()
                : CollectWidth(1280)
                , CollectHeight(720)
                , CollectFps(30)
                , EncodeHighWidth(1280)
                , EncodeHighHeight(720)
                , EncodeHighFps(24)
                , EncodeHighStartBitrate(1500)
                , EncodeHighMinBitrate(50)
                , EncodeHighMaxBitrate(3500)
            {
            }
            //  copy constructor
            VideoAndAudioParameter(const VideoAndAudioParameter &other)
            {
                CollectWidth = other.CollectWidth;
                CollectHeight = other.CollectHeight;
                CollectFps = other.CollectFps;
                EncodeHighWidth = other.EncodeHighWidth;
                EncodeHighHeight = other.EncodeHighHeight;
                EncodeHighFps = other.EncodeHighFps;
                EncodeHighStartBitrate = other.EncodeHighStartBitrate;
                EncodeHighMinBitrate = other.EncodeHighMinBitrate;
                EncodeHighMaxBitrate = other.EncodeHighMaxBitrate;
            }

            //Equal overload
            VideoAndAudioParameter & operator =(const VideoAndAudioParameter &other)
            {
                // (1) Check self
                if(this == &other)
                    return *this;

                // (2) Free original memory resources
                // （3）Allocate new memory resources, copy the content
                CollectWidth = other.CollectWidth;
                CollectHeight = other.CollectHeight;
                CollectFps = other.CollectFps;
                EncodeHighWidth = other.EncodeHighWidth;
                EncodeHighHeight = other.EncodeHighHeight;
                EncodeHighFps = other.EncodeHighFps;
                EncodeHighStartBitrate = other.EncodeHighStartBitrate;
                EncodeHighMinBitrate = other.EncodeHighMinBitrate;
                EncodeHighMaxBitrate = other.EncodeHighMaxBitrate;
                // （4）Returns a reference to this object
                return *this;
            }
        };



        class SRConferenceAbnormal
        {
        public:
            void  SetError(SR_ERROR_CODE_TYPE error)
            {
                cur_error = error;
            }

            void SetErrorMessage(const std::string & errorReason)
            {
                brief_reason.clear();
                brief_reason = errorReason;
            }

            SRConferenceAbnormal()
                : cur_error(ERR_NONE)
                , brief_reason("")
                , detail_reason("")
            {
            }

            //  copy constructor
            SRConferenceAbnormal(const SRConferenceAbnormal &other)
            {
                cur_error = other.cur_error;
                brief_reason = other.brief_reason;
                detail_reason = other.detail_reason;
            }

            //Equal overload
            SRConferenceAbnormal & operator =(const SRConferenceAbnormal &other)
            {
                // (1) Check self
                if(this == &other)
                    return *this;

                // (2) Free original memory resources
                brief_reason.clear();
                detail_reason.clear();
                // （3）Allocate new memory resources, copy the content
                cur_error = other.cur_error;
                brief_reason = other.brief_reason;
                detail_reason = other.detail_reason;
                // （4）Returns a reference to this object
                return *this;
            }

            SR_ERROR_CODE_TYPE cur_error;
            std::string  brief_reason;
            std::string detail_reason;//暂时不用

        };



        class McInfo
        {
        public:
            list<std::string>   relaymc_info; //例如:10.10.10.10:2000---10.10.10.11:4000
            UINT64        ipandport;          //mc 的ip和port的组合
            int           listenport;         //暂时不用

            McInfo()
                : ipandport(0)
                , listenport(0)
            {
            }
            ~McInfo()
            {
                relaymc_info.clear();
            }

            //  copy constructor
            McInfo(const McInfo &other)
            {
                relaymc_info = other.relaymc_info;
                ipandport = other.ipandport;
                listenport = other.listenport;
            }

            //Equal overload
            McInfo & operator =(const McInfo &other)
            {
                // (1) Check self
                if(this == &other)
                    return *this;

                // (2) Free original memory resources
                relaymc_info.clear();
                // （3）Allocate new memory resources, copy the content
                relaymc_info = other.relaymc_info;
                ipandport = other.ipandport;
                listenport = other.listenport;
                // （4）Returns a reference to this object
                return *this;
            }

        };

        class UserInfo
        {
        public:
            UINT32         termUId;     //终端唯一标识(由终端产生)
            std::string    termUName;   // 终端的名称(name size <128)

            int mediagroupid; //该终端所属域分组id
            int specialtype;  //特殊类型, 0 - 普通终端类型, 1 - 投屏终端类型

            SREngineUserType  usertype;  //user type

            UserInfo()
                : termUId(0)
                , termUName("")
                , mediagroupid(0)
                , specialtype(0)
                , usertype(SR_FROMTERM_SUIRUI_USER_OFFICIAL)
            {
            }

            //  copy constructor
            UserInfo(const UserInfo &other)
            {
                termUId = other.termUId;
                termUName = other.termUName;
                mediagroupid = other.mediagroupid;
                specialtype = other.specialtype;
                usertype = other.usertype;
            }

            // Equal overload
            UserInfo & operator =(const UserInfo &other)
            {
                // (1) Check self
                if(this == &other)
                    return *this;

                // (2) Free original memory resources
                termUName.clear();
                // （3）Allocate new memory resources, copy the content
                termUId = other.termUId;
                termUName = other.termUName;
                mediagroupid = other.mediagroupid;
                specialtype = other.specialtype;
                usertype = other.usertype;
                // （4）Returns a reference to this object
                return *this;
            }

        };

        class ConfInfo
        {
        public:
            UINT64              conf_id;           //会议号
            std::string         password;          //会议密码

            ConfInfo()
                : conf_id(0)
                , password("")
            {
            }

            //  copy constructor
            ConfInfo(const ConfInfo &other)
            {
                conf_id = other.conf_id;
                password = other.password;
            }

            // Equal overload
            ConfInfo & operator =(const ConfInfo &other)
            {
                // (1) Check self
                if(this == &other)
                    return *this;

                // (2) Free original memory resources
                password.clear();
                // （3）Allocate new memory resources, copy the content
                conf_id = other.conf_id;
                password = other.password;
                // （4）Returns a reference to this object
                return *this;
            }

        };



        /*
        *
        *数据帧传递结构
        */
        class VideoFrame
        {
        public:
            SR_VIDEO_RAW_FORMAT_TYPE format;               //数据帧的类型
            SR_VIDEO_RAW_ROTATION_MODE rotation;           //旋转角度
            bool isMirror;                                 //是否镜像
            int width;                                     //数据帧的宽
            int height;                                    //数据帧的高
            //for I420
            int ySize;                                     //对于I420 的数据y的大小
            int uSize;                                     //对于I420 的数据u的大小
            int vSize;                                     //对于I420 的数据v的大小
            void* yBuffer;                                 //对于I420 的数据y的buffer
            void* uBuffer;                                 //对于I420 的数据u的buffer
            void* vBuffer;                                 //对于I420 的数据v的buffer

            //如果不是I420格式， 直接放入yBuffer， 填写y的大小ySize

            VideoFrame()
                : format(SR_FORMAT_RAW_TYPE_YUV420)
                , rotation(SR_ROTATION_MODE_NONE)
                , isMirror(false)
                , width(0)
                , height(0)
                , ySize(0)
                , uSize(0)
                , vSize(0)
                , yBuffer(NULL)
                , uBuffer(NULL)
                , vBuffer(NULL)
            {
            }

            VideoFrame(int m_width, int m_height)
                : format(SR_FORMAT_RAW_TYPE_YUV420)
                , rotation(SR_ROTATION_MODE_NONE)
                , isMirror(false)
                , width(m_width)
                , height(m_height)
                , ySize(m_height * m_width)
                , uSize((m_height * m_width) >> 2)
                , vSize((m_height * m_width) >> 2)
                , yBuffer(NULL)
                , uBuffer(NULL)
                , vBuffer(NULL)
            {
            }

            //  copy constructor
            VideoFrame(const VideoFrame &other)
            {
                format = other.format;
                rotation = other.rotation;
                isMirror = other.isMirror;
                width = other.width;
                height = other.height;
                ySize = other.ySize;
                uSize = other.uSize;
                vSize = other.vSize;
                yBuffer = other.yBuffer;
                uBuffer = other.uBuffer;
                vBuffer = other.vBuffer;
                rotation = other.rotation;
            }

            //Equal overload
            VideoFrame & operator =(const VideoFrame &other)
            {
                // (1) Check self
                if(this == &other)
                    return *this;

                // (2)Free original memory resources
                yBuffer = NULL;
                uBuffer = NULL;
                vBuffer = NULL;
                // （3）Allocate new memory resources, copy the content
                format = other.format;
                rotation = other.rotation;
                isMirror = other.isMirror;
                width = other.width;
                height = other.height;
                ySize = other.ySize;
                uSize = other.uSize;
                vSize = other.vSize;
                yBuffer = other.yBuffer;
                uBuffer = other.uBuffer;
                vBuffer = other.vBuffer;
                rotation = other.rotation;
                // （4）Returns a reference to this object
                return *this;
            }
        };


        class MediaAudioOpt
        {
        public:
            bool useDrc;    /* 是否开启drc */
            bool useStereo; /* 是否开启立体声 */
            int plfreq;     /* 音频编码采样率 16000， 32000， 48000*/

            MediaAudioOpt()
                : useDrc(false)
                , useStereo(false)
#if defined(WIN32) || defined(OS_LINUX)
                , plfreq(48000)
#else
                , plfreq(16000)
#endif
            {
            }

            // copy constructor
            MediaAudioOpt(const MediaAudioOpt &other)
            {
                useDrc = other.useDrc;
                useStereo = other.useStereo;
                plfreq = other.plfreq;
            }

            // Equal overload
            MediaAudioOpt & operator =(const MediaAudioOpt &other)
            {
                // (1) Check self
                if(this == &other)
                    return *this;

                // (2)Free original memory resources
                // （3）Allocate new memory resources, copy the content
                useDrc = other.useDrc;
                useStereo = other.useStereo;
                plfreq = other.plfreq;
                // （4）Returns a reference to this object
                return *this;
            }
        };

        /*
        *
        *对于终端的属性
        */
        class TermInfo
        {
        public:
            int     termid;           //终端加入会议时mc产生的,不在线时填0
            std::string  tername;     //终端的名称
            bool    ismuted;          //该终端是否静音
            bool    iscamera_on;      //该终端是否打开摄像头
            bool    ishandup;         //该终端是否举手
            UINT32  suid;             //终端唯一标识(由终端产生)
            bool    isonline;         //是否在线,true表示在线，false表示不在线
            int     specialtype;  //特殊类型, 0-普通终端类型,1-投屏终端类型

            //目前针对第三方的终端
            std::string       ip;            //终端ip
            int               protocoltype;  //标准终端的呼叫协议类型,0-自动、1-sip、2-H.323,SR终端强制填入0
            int               bandwidth;     //终端呼叫带宽
            SREngineUserType  usertype;      //用户类型,0-临时用户,1-正式用户,2-Ubox,3-标准终端(H.323/sip)
            int               devicetype;    //设备类型,0-终端,1-MCU
            std::string       calloption;    //呼叫选项,一般是通知给gw供devicetype==1情况分析用, 这个一般邀请第三方终端的时候填写

            TermInfo()
                : termid(0)
                , tername("")
                , ismuted(false)
                , iscamera_on(false)
                , ishandup(false)
                , suid(0)
                , isonline(false)
                , specialtype(0)
                , ip("")
                , protocoltype(0)
                , bandwidth(0)
                , usertype(SR_FROMTERM_SUIRUI_USER_OFFICIAL)
                , devicetype(0)
                , calloption("")
            {
            }
            ~TermInfo()
            {
                tername.clear();
                ip.clear();
                calloption.clear();
            }
            //  copy constructor
            TermInfo(const TermInfo &other)
            {
                termid = other.termid;
                ismuted = other.ismuted;
                iscamera_on = other.iscamera_on;
                ishandup = other.ishandup;
                tername = other.tername;
                suid = other.suid;
                isonline = other.isonline;
                specialtype = other.specialtype;
                ip = other.ip;
                protocoltype = other.protocoltype;
                bandwidth = other.bandwidth;
                usertype = other.usertype;
                devicetype = other.devicetype;
                calloption = other.calloption;
            }

            //Equal overload
            TermInfo & operator =(const TermInfo &other)
            {
                //Check self
                if(this == &other)
                    return *this;

                //Free original memory resources
                tername.clear();
                ip.clear();
                calloption.clear();
                //Allocate new memory resources, copy the content
                termid = other.termid;
                ismuted = other.ismuted;
                iscamera_on = other.iscamera_on;
                ishandup = other.ishandup;
                tername = other.tername;
                suid = other.suid;
                isonline = other.isonline;
                specialtype = other.specialtype;
                ip = other.ip;
                protocoltype = other.protocoltype;
                bandwidth = other.bandwidth;
                usertype = other.usertype;
                devicetype = other.devicetype;
                calloption = other.calloption;
                //Returns a reference to this object
                return *this;
            }
        };





        /*
        *
        *请求选看某路流
        */

        class RequestVideoParam
        {
        public:
            int                                 sterm_id;                    //选看终端的id
            int                                 mp_screen_id;                //mp屏幕数量id

            //预留定义
            view_t                              wnd;                         //大窗体句柄,调用端传空
            view_t                              low_wnd;                     //小窗体句柄,调用端传空

            SR_CFG_SELECT_VIDEO_STREAM          video_type;                  //流类型

            int delayflag;      // 0:立即处理 1:延迟处理
            int replaceterid;   // 替代终端tid，默认值为0
            int expectfps;      // 期望终端最大帧率，默认 0（0帧） 1（8帧），2（16帧），3（24帧），4(30帧)，5（60帧）


            RequestVideoParam()
                : sterm_id(0)
                , mp_screen_id(0)
                , wnd(NULL)
                , low_wnd(NULL)
                , video_type(SR_CFG_VIDEO_SIZE_90P)
                , delayflag(0)
                , replaceterid(0)
                , expectfps(3)
            {
            }

            //  copy constructor
            RequestVideoParam(const RequestVideoParam &other)
            {
                sterm_id = other.sterm_id;
                mp_screen_id = other.mp_screen_id;
                video_type = other.video_type;
                wnd = other.wnd;
                low_wnd = other.low_wnd;
                delayflag = other.delayflag;
                replaceterid = other.replaceterid;
                expectfps = other.expectfps;
            }

            //Equal overload
            RequestVideoParam & operator =(const RequestVideoParam &other)
            {
                // (1) Check self
                if(this == &other)
                    return *this;

                // (2) Free original memory resources
                // （3）Allocate new memory resources, copy the content
                sterm_id = other.sterm_id;
                mp_screen_id = other.mp_screen_id;
                video_type = other.video_type;
                wnd = other.wnd;
                low_wnd = other.low_wnd;
                delayflag = other.delayflag;
                replaceterid = other.replaceterid;
                expectfps = other.expectfps;
                // （4）Returns a reference to this object
                return *this;
            }

        } ;

        class NetWorkStatus
        {
        public:
            SREngineNetworkStatus     network_upload_status;      //网络上行方向的状况
            SREngineNetworkStatus     network_download_status; //网络下行方向的状况

            NetWorkStatus()
                : network_upload_status(SR_NETWORK_STATUS_NONE)
                , network_download_status(SR_NETWORK_STATUS_NONE)
            {
            }

            //  copy constructor
            NetWorkStatus(const NetWorkStatus &other)
            {
                network_upload_status = other.network_upload_status;
                network_download_status = other.network_download_status;
            }

            // Equal overload
            NetWorkStatus & operator =(const NetWorkStatus &other)
            {
                // (1) Check self
                if(this == &other)
                    return *this;

                // (2) Free original memory resources
                // （3）Allocate new memory resources, copy the content
                network_upload_status = other.network_upload_status;
                network_download_status = other.network_download_status;
                // （4）Returns a reference to this object
                return *this;
            }

        };

        /*
        *
        *获取会中发送以及接收的数据的相关属性
        */
        class SendStreamInfo
        {
        public:
            char                audioCodecName[8];                 //音频发送编码名称
            int                 audioSampleRate;                   //音频发送采样率
            int                 audioBitrate;                      //音频发送码率

            char                videoCodecName[8];                 //视频发送编码名称
            int                 videoLFps;                         //视频发送小流帧率
            int                 videoLBitrate;                     //视频发送小流码率
            int                 videoLWidth;                       //视频发送小流宽
            int                 videoLHeight;                      //视频发送小流高

            int                 videoMFps;                         //视频发送中流帧率
            int                 videoMBitrate;                     //视频发送中流码率
            int                 videoMWidth;                       //视频发送中流宽
            int                 videoMHeight;                      //视频发送中流高

            int                 videoHFps;                         //视频发送大流帧率
            int                 videoHBitrate;                     //视频发送大流码率
            int                 videoHWidth;                       //视频发送大流宽
            int                 videoHHeight;                      //视频发送大流高

            char                h239CodecName[8];                  //视频h239通道发送编码名称
            int                 h239Fps;                           //视频发送桌面共享帧率
            int                 h239Bitrate;                       //视频发送桌面共享流码率
            int                 h239Width;                         //视频发送桌面共享流宽
            int                 h239Height;                        //视频发送桌面共享流高

            int                 up_qos_kbps;                       //上行评估码率
            SREngineNetworkStatus     network_upload_status;      //网络上行方向的状况

            SendStreamInfo()
                : audioSampleRate(0)
                , audioBitrate(0)
                , videoLFps(0)
                , videoLBitrate(0)
                , videoLWidth(0)
                , videoLHeight(0)
                , videoMFps(0)
                , videoMBitrate(0)
                , videoMWidth(0)
                , videoMHeight(0)
                , videoHFps(0)
                , videoHBitrate(0)
                , videoHWidth(0)
                , videoHHeight(0)
                , h239Fps(0)
                , h239Bitrate(0)
                , h239Width(0)
                , h239Height(0)
                , up_qos_kbps(0)
                , network_upload_status(SR_NETWORK_STATUS_NONE)
            {
                memset(audioCodecName, 0, 8);
                memset(videoCodecName, 0, 8);
                memset(h239CodecName, 0, 8);
            }

            //  copy constructor
            SendStreamInfo(const SendStreamInfo &other)
            {
                memcpy(audioCodecName, other.audioCodecName, 8);
                audioSampleRate = other.audioSampleRate;
                audioBitrate = other.audioBitrate;
                memcpy(videoCodecName, other.videoCodecName, 8);
                videoLFps = other.videoLFps;
                videoLBitrate = other.videoLBitrate;
                videoLWidth = other.videoLWidth;
                videoLHeight = other.videoLHeight;
                videoMFps = other.videoMFps;
                videoMBitrate = other.videoMBitrate;
                videoMWidth = other.videoMWidth;
                videoMHeight = other.videoMHeight;
                videoHFps = other.videoHFps;
                videoHBitrate = other.videoHBitrate;
                videoHWidth = other.videoHWidth;
                videoHHeight = other.videoHHeight;
                memcpy(h239CodecName, other.h239CodecName, 8);
                h239Fps = other.h239Fps;
                h239Bitrate = other.h239Bitrate;
                h239Width = other.h239Width;
                h239Height = other.h239Height;
                up_qos_kbps = other.up_qos_kbps;
                network_upload_status = other.network_upload_status;
            }

            // Equal overload
            SendStreamInfo & operator =(const SendStreamInfo &other)
            {
                // (1) Check self
                if(this == &other)
                    return *this;

                // (2) Free original memory resources
                memset(audioCodecName, 0, 8);
                memset(videoCodecName, 0, 8);
                memset(h239CodecName, 0, 8);
                // （3）Allocate new memory resources, copy the content
                memcpy(audioCodecName, other.audioCodecName, 8);
                audioSampleRate = other.audioSampleRate;
                audioBitrate = other.audioBitrate;
                memcpy(videoCodecName, other.videoCodecName, 8);
                videoLFps = other.videoLFps;
                videoLBitrate = other.videoLBitrate;
                videoLWidth = other.videoLWidth;
                videoLHeight = other.videoLHeight;
                videoMFps = other.videoMFps;
                videoMBitrate = other.videoMBitrate;
                videoMWidth = other.videoMWidth;
                videoMHeight = other.videoMHeight;
                videoHFps = other.videoHFps;
                videoHBitrate = other.videoHBitrate;
                videoHWidth = other.videoHWidth;
                videoHHeight = other.videoHHeight;
                memcpy(h239CodecName, other.h239CodecName, 8);
                h239Fps = other.h239Fps;
                h239Bitrate = other.h239Bitrate;
                h239Width = other.h239Width;
                h239Height = other.h239Height;
                up_qos_kbps = other.up_qos_kbps;
                network_upload_status = other.network_upload_status;
                // （4）Returns a reference to this object
                return *this;
            }
        } ;

        class RecvAudioStream
        {
        public:
            int                 id;                                      //接收音频流id
            char               codecName[8];                             //接收音频流Name
            int                  sampleRate;                             //接收音频流采样率
            int                  bitRate;                                //接收音频流码率 (bps)
            int                  recCodecChs;                            //接收音频流通道（1：单声道，2：立体音）
            float               loseRate;                                //接收音频流丢包率
            RecvAudioStream()
                : id(0)
                , sampleRate(0)
                , bitRate(0)
                , recCodecChs(0)
                , loseRate(0.0f)
            {
                memset(codecName, 0, 8);
            }

            //  copy constructor
            RecvAudioStream(const RecvAudioStream &other)
            {
                id = other.id;
                sampleRate = other.sampleRate;
                bitRate = other.bitRate;
                recCodecChs = other.recCodecChs;
                loseRate = other.loseRate;
                memcpy(codecName, other.codecName, 8);
            }

            // Equal overload
            RecvAudioStream & operator =(const RecvAudioStream &other)
            {
                // (1) Check self
                if(this == &other)
                    return *this;

                // (2)Free original memory resources
                memset(codecName, 0, 8);
                // （3）Allocate new memory resources, copy the content
                id = other.id;
                sampleRate = other.sampleRate;
                bitRate = other.bitRate;
                recCodecChs = other.recCodecChs;
                loseRate = other.loseRate;
                memcpy(codecName, other.codecName, 8);
                // （4）Returns a reference to this object
                return *this;
            }

        } ;

        class RecvVideoStream
        {
        public:
            int                 id;                               //接收视频流ID
            char               codecName[10];                     //接收视频流Name
            int                 fps;                              //接收视频流帧率
            int                 bitRate;                          //接收视频流码率(bps)
            unsigned int           loseRate;                      //接收视频丢包率
            int                 width;                            //接收视频流宽度
            int                 height;                           //接收视频流高度

            RecvVideoStream()
                : id(0)
                , fps(0)
                , bitRate(0)
                , loseRate(0)
                , width(0)
                , height(0)
            {
            }

            //  copy constructor
            RecvVideoStream(const RecvVideoStream &other)
            {
                id = other.id;
                fps = other.fps;
                bitRate = other.bitRate;
                loseRate = other.loseRate;
                width = other.width;
                height = other.height;
                memcpy(codecName, other.codecName, 8);
            }

            // Equal overload
            RecvVideoStream & operator =(const RecvVideoStream &other)
            {
                // (1) Check self
                if(this == &other)
                    return *this;

                // (2) Free original memory resources
                memset(codecName, 0, 8);
                // （3）Allocate new memory resources, copy the contents
                id = other.id;
                fps = other.fps;
                bitRate = other.bitRate;
                loseRate = other.loseRate;
                width = other.width;
                height = other.height;
                memcpy(codecName, other.codecName, 8);
                // （4）Returns a reference to this object
                return *this;
            }
        } ;


        class RecvStreamInfo
        {
        public:
            std::deque<RecvAudioStream> audioStreams;
            std::deque<RecvVideoStream> videoStreams;
            RecvVideoStream              h239Stream;
            int                                       down_qos_kbps;                  //下行评估码率
            SREngineNetworkStatus     network_download_status; //网络下行方向的状况

            RecvStreamInfo()
                : down_qos_kbps(0)
                , network_download_status(SR_NETWORK_STATUS_NONE)
            {
                audioStreams.clear();
                videoStreams.clear();
            }

            ~RecvStreamInfo()
            {
                audioStreams.clear();
                videoStreams.clear();
                down_qos_kbps = 0;
            }

        } ;

        /*
        *
        *对应会议那个与会者说话的能量属性
        */
        class SRVoiceActiveInfo
        {
        public:
            int             talk_id;
            unsigned int    energy;
            SRVoiceActiveInfo()
                : talk_id(0)
                , energy(0)
            {
            }

            //  copy constructor
            SRVoiceActiveInfo(const SRVoiceActiveInfo &other)
            {
                talk_id = other.talk_id;
                energy = other.energy;
            }

            // Equal overload
            SRVoiceActiveInfo & operator =(const SRVoiceActiveInfo &other)
            {
                // (1) Check self
                if(this == &other)
                    return *this;

                // (2) Free original memory resources
                // （3）Allocate new memory resources, copy the content
                talk_id = other.talk_id;
                energy = other.energy;
                // （4）Returns a reference to this object
                return *this;
            }

        } ;

        /*
        *
        *本地网卡相关的信息，针对windows平台和linux平台
        */
        class SRLocalAdaptInfo
        {
        public:
            char        adapt_name[SR_MAX_NET_ID_LENGTH];
            char        mac_addr[SR_MAX_NET_ID_LENGTH];
            char        local_ip[SR_MAX_NET_ID_LENGTH];
            char        mask[SR_MAX_NET_ID_LENGTH];
            char        gateway[SR_MAX_NET_ID_LENGTH];
            SRLocalAdaptInfo()
            {
                memset(adapt_name, 0, SR_MAX_NET_ID_LENGTH);
                memset(mac_addr, 0, SR_MAX_NET_ID_LENGTH);
                memset(local_ip, 0, SR_MAX_NET_ID_LENGTH);
                memset(mask, 0, SR_MAX_NET_ID_LENGTH);
                memset(gateway, 0, SR_MAX_NET_ID_LENGTH);
            }

            //  copy constructor
            SRLocalAdaptInfo(const SRLocalAdaptInfo &other)
            {
                memcpy(adapt_name, other.adapt_name, SR_MAX_NET_ID_LENGTH);
                memcpy(mac_addr, other.mac_addr, SR_MAX_NET_ID_LENGTH);
                memcpy(local_ip, other.local_ip, SR_MAX_NET_ID_LENGTH);
                memcpy(mask, other.mask, SR_MAX_NET_ID_LENGTH);
                memcpy(gateway, other.gateway, SR_MAX_NET_ID_LENGTH);
            }

            // Equal overload
            SRLocalAdaptInfo & operator =(const SRLocalAdaptInfo &other)
            {
                // (1)Check self
                if(this == &other)
                    return *this;

                // (2) Free original memory resources
                memset(adapt_name, 0, SR_MAX_NET_ID_LENGTH);
                memset(mac_addr, 0, SR_MAX_NET_ID_LENGTH);
                memset(local_ip, 0, SR_MAX_NET_ID_LENGTH);
                memset(mask, 0, SR_MAX_NET_ID_LENGTH);
                memset(gateway, 0, SR_MAX_NET_ID_LENGTH);
                // （3）Allocate new memory resources, copy the content
                memcpy(adapt_name, other.adapt_name, SR_MAX_NET_ID_LENGTH);
                memcpy(mac_addr, other.mac_addr, SR_MAX_NET_ID_LENGTH);
                memcpy(local_ip, other.local_ip, SR_MAX_NET_ID_LENGTH);
                memcpy(mask, other.mask, SR_MAX_NET_ID_LENGTH);
                memcpy(gateway, other.gateway, SR_MAX_NET_ID_LENGTH);
                // （4）Returns a reference to this object
                return *this;
            }

        } ;


        /*
        *
        *mp 内的屏幕的相关信息
        *
        */
        class SRMediaPScreenInfo
        {
        public:
            int screenid;       //混屏布局对应屏幕id
            int screentype;     //混屏布局对应屏幕类型，1-网关(标准终端)屏幕、2-终端转码屏幕、3-双流屏幕、4-录制直播屏幕

            SRMediaPScreenInfo()
                : screenid(0)
                , screentype(0)
            {
            }

            //  copy constructor
            SRMediaPScreenInfo(const SRMediaPScreenInfo &other)
            {
                screenid = other.screenid;
                screentype = other.screentype;
            }

            // Equal overload
            SRMediaPScreenInfo & operator =(const SRMediaPScreenInfo &other)
            {
                // (1) Check self
                if(this == &other)
                    return *this;

                // (2) Free original memory resources
                // （3）Allocate new memory resources, copy the content
                screenid = other.screenid;
                screentype = other.screentype;
                // （4）Returns a reference to this object
                return *this;
            }

        } ;

        /*
        *
        *mp 相关信息
        *
        */

        class SRMediaPInfo
        {
        public:
            // 混屏布局对应屏幕所属媒体处理实例通道
            int channelid;
            // mp上有很多屏
            std::list<SRMediaPScreenInfo> screens;

            SRMediaPInfo()
                : channelid(0)
            {
                screens.clear();
            }

            ~SRMediaPInfo()
            {
                screens.clear();
            }

            //  copy constructor
            SRMediaPInfo(const SRMediaPInfo &other)
            {
                channelid = other.channelid;
                screens = other.screens;
            }

            // Equal overload
            SRMediaPInfo & operator =(const SRMediaPInfo &other)
            {
                // (1) Check self
                if(this == &other)
                    return *this;

                // (2) Free original memory resources
                screens.clear();
                // （3）Allocate new memory resources, copy the content
                channelid = other.channelid;
                screens = other.screens;
                // （4）Returns a reference to this object
                return *this;
            }

        };


        /*标签属性定义*/
        //暂时先这么用， 后续接口会提供一个buffer供用户自己去定义
        class SRScreenLableAttr
        {
        public:
            int             labelterid;
            int             operatetype;
            int             lableid;
            int             labletype;
            int             lablesize;
            int             lablecolor;
            int             linetype;

            int             leftuppoints_x;
            int             leftuppoints_y;

            int             rightdownpoints_x;
            int             rightdownpoints_y;

            int             resolution_x;
            int             resolution_y;

            SRScreenLableAttr()
                : labelterid(0)
                , operatetype(0)
                , lableid(0)
                , labletype(0)
                , lablesize(0)
                , lablecolor(0)
                , linetype(0)
                , leftuppoints_x(0)
                , leftuppoints_y(0)
                , rightdownpoints_x(0)
                , rightdownpoints_y(0)
                , resolution_x(0)
                , resolution_y(0)
            {
            }

            //  copy constructor
            SRScreenLableAttr(const SRScreenLableAttr &other)
            {
                labelterid = other.labelterid;
                operatetype = other.operatetype;
                lableid = other.lableid;
                labletype = other.labletype;
                lablesize = other.lablesize;
                lablecolor = other.lablecolor;
                linetype = other.linetype;
                leftuppoints_x = other.leftuppoints_x;
                leftuppoints_y = other.leftuppoints_y;
                rightdownpoints_x = other.rightdownpoints_x;
                rightdownpoints_y = other.rightdownpoints_y;
                resolution_x = other.resolution_x;
                resolution_y = other.resolution_y;
            }

            // Equal overload
            SRScreenLableAttr & operator =(const SRScreenLableAttr &other)
            {
                // (1) Check self
                if(this == &other)
                    return *this;

                labelterid = other.labelterid;
                operatetype = other.operatetype;
                lableid = other.lableid;
                labletype = other.labletype;
                lablesize = other.lablesize;
                lablecolor = other.lablecolor;
                linetype = other.linetype;
                leftuppoints_x = other.leftuppoints_x;
                leftuppoints_y = other.leftuppoints_y;
                rightdownpoints_x = other.rightdownpoints_x;
                rightdownpoints_y = other.rightdownpoints_y;
                resolution_x = other.resolution_x;
                resolution_y = other.resolution_y;
                // （4）Returns a reference to this object
                return *this;
            }


        } ;
        //---------------------------------screenlayout------------------------------

        //Sponsor tye
        enum SR_CONFERENCE_SPONSOR_TYPE
        {
            SR_CONFERENCE_SPONSOR_TYPE_TER = 1, //发起者是终端
            SR_CONFERENCE_SPONSOR_TYPE_WEB = 2, //发起者是web会控
        };



        //master drop terminal
        class SRConferenceCtrlDropTerm
        {
        public:
            //drop terminal's stermid
            int drop_stermid;


            int sponsortype;//发起者类型,1-ter、2-web

            SRConferenceCtrlDropTerm()
                : drop_stermid(0)
                , sponsortype(1)
            {
            }
        };

        //Transfer master
        class SRConferenceCtrlMasterTransfer
        {
        public:
            //new master stermid
            int new_stermid;


            int sponsortype; //发起者类型,1-ter、2-web

            SRConferenceCtrlMasterTransfer()
                : new_stermid(0)
                , sponsortype(1)
            {
            }
        };

        //CmdSetAssistChairman
        class SRConferenceCtrlAssistChairman
        {
        public:
            //辅助主席的stermid   0--取消辅助主席
            int assist_chairman_stermid;


            int sponsortype;     //发起者类型,1-ter、2-web

            SRConferenceCtrlAssistChairman()
                : assist_chairman_stermid(0)
                , sponsortype(1)
            {
            }
        };


        //The Master lock the video(other term or self)
        class SRConferenceCtrlLockVideo
        {
        public:
            //要锁定的终端的stermid
            int lock_stermid;


            int sponsortype; //发起者类型,1-ter、2-web

            SRConferenceCtrlLockVideo()
                : lock_stermid(0)
                , sponsortype(1)
            {
            }
        };


        //取消锁定视频
        class SRConferenceCtrlUnLockVideo
        {
        public:

            int unlock_stermid;  //已经锁定了某个终端视频， 取消锁定这个终端

            int sponsortype;     //发起者类型,1-ter、2-web

            SRConferenceCtrlUnLockVideo()
                : unlock_stermid(0)
                , sponsortype(1)
            {
            }
        };

        //主持结束会议
        class SRConferenceCtrlChairEndConf
        {
        public:
            int sponsortype;        //发起者类型,1-ter、2-web

            SRConferenceCtrlChairEndConf()
                : sponsortype(1)
            {
            }
        };

        //全体是否静音
        class SRConferenceCtrlMuteAudioAllTerm
        {
        public:
            //true:静音   false:取消静音
            bool ismute;

            int sponsortype;      //发起者类型,1-ter、2-web
            SRConferenceCtrlMuteAudioAllTerm()
                : ismute(false)
                , sponsortype(1)
            {
            }
        };

        //是否锁定会议
        class SRConferenceCtrlLockConf
        {
        public:
            //true : lock  false : cancel lock
            bool islock;

            int sponsortype; //发起者类型,1-ter、2-web
            SRConferenceCtrlLockConf()
                : islock(false)
                , sponsortype(1)
            {
            }
        };

		//是否允许某人发言，对其举手回应
		class SRConferenceCtrlPermissionHandUp
		{
		public:	
			int sponsortype;           //发起者类型,1-ter、2-web

			int 	permissionstermid; //被允许的终端stermid
			bool ispermission;       //true表示同意，false表示拒绝

			SRConferenceCtrlPermissionHandUp()
				: sponsortype(1)
				, permissionstermid(0)
				, ispermission(false)
			{
			}
		};

		//取消所有人发言
		class SRConferenceCtrlPutAllHandDown
		{
		public:
			int sponsortype;           //发起者类型,1-ter、2-web

			SRConferenceCtrlPutAllHandDown()
				: sponsortype(1)
			{
			}
		};	
		

        //主持人切换会议模式
        class SRConferenceCtrlChangeConfMode
        {
        public:
            int newconfmode;  //会议模式:0 - 自由模式 1 - 主席模式
            int sponsortype;  //发起者类型,1-ter、2-web

            SRConferenceCtrlChangeConfMode()
                : newconfmode(0)
                , sponsortype(1)
            {
            }
        };

        //请求会议状态信息
        class SRConferenceCtrlReqConfStatus
        {
        public:
            int sponsortype;  //发起者类型,1-ter、2-web

            SRConferenceCtrlReqConfStatus()
                : sponsortype(1)
            {
            }
        };

        //会议强制静音控制
        class SRConferenceCtrlForceMute
        {
        public:
            int sponsortype;  //发起者类型,1-ter、2-web
            bool isforcemute;  //是否强制静音

            SRConferenceCtrlForceMute()
                : sponsortype(1)
                , isforcemute(false)
            {
            }
        };





        //分屏下小格子的属性
        class SRPaneInfo
        {
        public:

            int paneindex;                         //分屏id,从0开始
            int contenttype;                       //分屏中显示内容类型，0:终端; 1:voip位图; 2:空; 3:双流

            int optype;                            //分屏中操作类型，1:指定终端; 2:语音激励;3:自动轮巡.

            //如果窗格中的显示类型为“3:自动轮巡”，则此处定义的为轮询时间间隔，单位：秒, 如果不是自动轮询默认0
            int polltime;

            int terid;                            //显示终端的stermid
            std::string tername;                  //终端名称

            SRPaneInfo()
                : paneindex(0)
                , contenttype(0)
                , optype(1)
                , polltime(0)
                , terid(0)
                , tername("")
            {
            }

            //  copy constructor
            SRPaneInfo(const SRPaneInfo &other)
            {
                paneindex = other.paneindex;
                contenttype = other.contenttype;
                optype = other.optype;
                polltime = other.polltime;
                terid = other.terid;
                tername = other.tername;
            }

            // Equal overload
            SRPaneInfo & operator =(const SRPaneInfo &other)
            {
                // (1) Check self
                if(this == &other)
                    return *this;

                paneindex = other.paneindex;
                contenttype = other.contenttype;
                optype = other.optype;
                polltime = other.polltime;
                terid = other.terid;
                tername = other.tername;
                // （4）Returns a reference to this object
                return *this;
            }
        };

        //大分屏布局模式
        enum SR_CONFERENCE_LAYOUT_MODE
        {
            SR_CONFERENCE_LAYOUT_AUDO               = 0, //0-自动
            SR_CONFERENCE_LAYOUT_ONE                = 1, //1-单屏
            SR_CONFERENCE_LAYOUT_TWO                = 2, //2-2分屏
            SR_CONFERENCE_LAYOUT_THREE              = 3, //3-3分屏
            SR_CONFERENCE_LAYOUT_FOUR               = 4, //4-4分屏
            SR_CONFERENCE_LAYOUT_FIVE               = 5, //5-5分屏
            SR_CONFERENCE_LAYOUT_SIX                = 6, //6-6分屏
            SR_CONFERENCE_LAYOUT_SEVEN              = 7, //7-7分屏
            SR_CONFERENCE_LAYOUT_EIGHT              = 8, //8-8分屏
            SR_CONFERENCE_LAYOUT_NINE               = 9, //9-9分屏
            SR_CONFERENCE_LAYOUT_TEN                = 10, //10-10分屏
            SR_CONFERENCE_LAYOUT_THIRTEEN           = 11, //11-13分屏
            SR_CONFERENCE_LAYOUT_SIXTEEN            = 12, //12-16分屏
            SR_CONFERENCE_LAYOUT_RECORD             = 13, //13-录制屏
            SR_CONFERENCE_LAYOUT_TWENTY             = 14, //14-20分屏
            SR_CONFERENCE_LAYOUT_TWENTY_FIVE        = 15, //15-25分屏
            SR_CONFERENCE_LAYOUT_SPEECH_4_1         = 16, // 演讲者模式4+1布局
        };


        //大屏属性
        class SRLayoutInfo
        {
        public:

            int   layouttype;              //分屏布局类型，0-转发布局、1-混屏布局

            //分屏布局模式，0-自动、1-单屏、2-2分屏、3-3分屏、4-4分屏、、、11-13分屏、12-16分屏、13-录制屏、14-20分屏、15-25分屏
            SR_CONFERENCE_LAYOUT_MODE   layoutmode;

            std::list<SRPaneInfo> panes;  //分屏信息

            SRMediaPInfo  mpinfo;         //如果是混屏布局需要设置mp的相关配置

            SRLayoutInfo()
                : layouttype(0)
                , layoutmode(SR_CONFERENCE_LAYOUT_AUDO)
            {
                panes.clear();
            }

            //  copy constructor
            SRLayoutInfo(const SRLayoutInfo &other)
            {
                layouttype = other.layouttype;
                layoutmode = other.layoutmode;
                panes = other.panes;
                mpinfo = other.mpinfo;
            }

            // Equal overload
            SRLayoutInfo & operator =(const SRLayoutInfo &other)
            {
                // (1) Check self
                if(this == &other)
                    return *this;

                panes.clear();
                layouttype = other.layouttype;
                layoutmode = other.layoutmode;
                panes = other.panes;
                mpinfo = other.mpinfo;
                // （4）Returns a reference to this object
                return *this;
            }
        };


        class SRConferenceCtrlSRLayoutInfo
        {
        public:
            //辅助主席的stermid   0--取消辅助主席
            SRLayoutInfo layout;

            int sponsortype;//发起者类型,1-ter、2-web

            SRConferenceCtrlSRLayoutInfo()
                : sponsortype(1)
            {
            }
        };

        //获取当前的分屏信息
        class SRConferenceCtrlReqLayoutInfo
        {
        public:

            int   layouttype;         //获取那种类型的布局分屏布局类型，0-转发布局、1-混屏布局
            int   sponsortype;          //发起者类型,1-ter、2-web
            SRConferenceCtrlReqLayoutInfo()
                : layouttype(0)
                , sponsortype(1)
            {
            }
        };

        class SubtitleInfo                 //字幕信息
        {
        public:
            UINT32       displaytime;      //字幕滚动时间，单位：秒，设置为0，则停止字幕显示
            int          msgpos;           //滚动字幕的位置：1-上、2-中、3-下
            std::string  msgcolor;         //消息字体颜色:RGB颜色值,6位十六进制值,如:黑色 #000000、白色 #FFFFFF、红色 #FF0000、绿色 #00FF00、蓝色 #0000FF、黄色 #FFFF00
            int          msgfontsize;      //字体大小：1-大、2-中、3-小
            bool         enableMsgBg;      //使能会场名称背景
            std::string  msgbgcolor;       //字体背景颜色:RGB颜色值,6位十六进制值,如:黑色 #000000、白色 #FFFFFF、红色 #FF0000、绿色 #00FF00、蓝色 #0000FF、黄色 #FFFF00

            SubtitleInfo()
                : displaytime(0)
                , msgpos(0)
                , msgcolor("")
                , msgfontsize(0)
                , enableMsgBg(false)
                , msgbgcolor("")
            {
            }

            //  copy constructor
            SubtitleInfo(const SubtitleInfo &other)
            {
                displaytime = other.displaytime;
                msgpos = other.msgpos;
                msgcolor = other.msgcolor;
                msgfontsize = other.msgfontsize;
                enableMsgBg = other.enableMsgBg;
                msgbgcolor = other.msgbgcolor;
            }

            // Equal overload
            SubtitleInfo & operator =(const SubtitleInfo &other)
            {
                // (1) Check self
                if(this == &other)
                    return *this;

                msgcolor.clear();
                msgbgcolor.clear();
                displaytime = other.displaytime;
                msgpos = other.msgpos;
                msgcolor = other.msgcolor;
                msgfontsize = other.msgfontsize;
                enableMsgBg = other.enableMsgBg;
                msgbgcolor = other.msgbgcolor;
                // （4）Returns a reference to this object
                return *this;
            }

        };




        class WhiteListInfo
        {
        public:
            int whitelisttype;                //白名单类型,0-主席模式白名单、1-直播模式白名单
            std::list<UINT32> terlists;       //白名单列表,参会者suid集合

            WhiteListInfo()
                : whitelisttype(0)
            {
                terlists.clear();
            }

            ~WhiteListInfo()
            {
                terlists.clear();
            }

            //  copy constructor
            WhiteListInfo(const WhiteListInfo &other)
            {
                whitelisttype = other.whitelisttype;
                terlists = other.terlists;
            }

            // Equal overload
            WhiteListInfo & operator =(const WhiteListInfo &other)
            {
                // (1) Check self
                if(this == &other)
                    return *this;

                terlists.clear();
                whitelisttype = other.whitelisttype;
                terlists = other.terlists;
                // （4）Returns a reference to this object
                return *this;
            }

        };


        //直播设置相关信息
        class LiveSetting
        {
        public:
            std::string     chairman; //直播主持人
            std::string     subject;   //直播主题
            std::string     digest;     //直播摘要/简介
            int                ispublic;  //是否公开,0-不公开,1-公开
            std::string     livepwd;  //直播密码
            int                isuserec;    //是否启用录制,0-不启用录制,1-启用录制

            LiveSetting()
                : chairman("")
                , subject("")
                , digest("")
                , ispublic(1)
                , livepwd("")
                , isuserec(0)
            {
            }

            //  copy constructor
            LiveSetting(const LiveSetting &other)
            {
                chairman = other.chairman;
                subject = other.subject;
                digest = other.digest;
                ispublic = other.ispublic;
                livepwd = other.livepwd;
                isuserec = other.isuserec;
            }

            // Equal overload
            LiveSetting & operator =(const LiveSetting &other)
            {
                // (1) Check self
                if(this == &other)
                    return *this;

                chairman.clear();
                subject.clear();
                digest.clear();
                livepwd.clear();
                chairman = other.chairman;
                subject = other.subject;
                digest = other.digest;
                ispublic = other.ispublic;
                livepwd = other.livepwd;
                isuserec = other.isuserec;
                // （4）Returns a reference to this object
                return *this;
            }

        };

        //直播相关信息
        class LiveInfo
        {
        public:
            int                   livestate;        //直播状态,0-停止直播,1-开始直播
            std::string       failreason;      //用来表示livestate为0时的停止原因,为空或者"default"为正常停止,其它为具体原因
            std::string       liveplayurl;     //livestate为1开始直播时,终端(主席)显示用
            LiveSetting   livesetinfo; //直播参数设置

            LiveInfo()
                : livestate(0)
                , failreason("")
                , liveplayurl("")
            {
            }

            //  copy constructor
            LiveInfo(const LiveInfo &other)
            {
                livestate = other.livestate;
                failreason = other.failreason;
                liveplayurl = other.liveplayurl;
                livesetinfo = other.livesetinfo;
            }

            // Equal overload
            LiveInfo & operator =(const LiveInfo &other)
            {
                // (1) Check self
                if(this == &other)
                    return *this;

                failreason.clear();
                liveplayurl.clear();
                livestate = other.livestate;
                failreason = other.failreason;
                liveplayurl = other.liveplayurl;
                livesetinfo = other.livesetinfo;
                // （4）Returns a reference to this object
                return *this;
            }

        };


        //录制相关信息
        class RecInfo
        {
        public:
            int                     recstate;            //录制会议状态,0-停止录制,1-开始录制
            std::string       failreason;         //用来表示recstate为0时的停止原因,为空或者"default"为正常停止,其它为具体原因

            RecInfo()
                : recstate(0)
                , failreason("")
            {
            }

            //  copy constructor
            RecInfo(const RecInfo &other)
            {
                recstate = other.recstate;
                failreason = other.failreason;
            }

            // Equal overload
            RecInfo & operator =(const RecInfo &other)
            {
                // (1) Check self
                if(this == &other)
                    return *this;

                failreason.clear();
                recstate = other.recstate;
                failreason = other.failreason;
                // （4）Returns a reference to this object
                return *this;
            }
        };

        class ConfStatus
        {
        public:
            std::string             confname;                //会议名称,对应subject会议主题
            int                          confmode;                //conf mode,0-自由模式、1-主席模式、
            std::list<UINT32>       participants;       //参会者列表,参会者suid集合
            UINT32                  chairmansuid;       //会议主席,对应数据库里会议创建者的suid
            std::list<UINT32>       assistchairmans;    //辅助主席,参会者suid集合
            int                     duovideoterid;      //拥有双流令牌的与会者
            int                     stdterseeingstyle;  //标准终端观看方式，0-跟随主持人、1-仅显示主席会场、2-标准终端观看网关分屏布局
            bool                    isduovideostart;    //是否开启双流
            bool                    isconflocked;       //会议是否被锁定
            bool                    isforcemute;        //强制禁音是否开启，true表示设置，false表示取消
            bool                    isdisplaytername;   //是否显示会场名称，true表示显示，false表示隐藏
            bool                      issubtitlestart;    //滚动字幕是否开启，true表示开启，false表示关闭
            std::string               subtitlemsg;
            SubtitleInfo              subtitle;            //滚动字幕信息
            bool                           has_record;       //是否有录制
            RecInfo                   recordinfo;             //录制信息
            bool                           has_live;               //是否有直播
            LiveInfo                     liveinfo;                   //直播信息
            std::list<WhiteListInfo>  whitelists;         //会议白名单

            ConfStatus()
                : confname("")
                , confmode(0)
                , chairmansuid(0)
                , duovideoterid(0)
                , stdterseeingstyle(0)
                , isduovideostart(false)
                , isconflocked(false)
                , isforcemute(false)
                , isdisplaytername(false)
                , issubtitlestart(false)
                , subtitlemsg("")
                , has_record(false)
                , has_live(false)
            {
                participants.clear();
                assistchairmans.clear();
            }

            //  copy constructor
            ConfStatus(const ConfStatus &other)
            {
                confname = other.confname;
                confmode = other.confmode;
                participants = other.participants;
                chairmansuid = other.chairmansuid;
                assistchairmans = other.assistchairmans;
                duovideoterid = other.duovideoterid;
                stdterseeingstyle = other.stdterseeingstyle;
                isduovideostart = other.isduovideostart;
                isconflocked = other.isconflocked;
                isforcemute = other.isforcemute;
                isdisplaytername = other.isdisplaytername;
                issubtitlestart = other.issubtitlestart;
                subtitlemsg = other.subtitlemsg;
                subtitle = other.subtitle;
                has_record = other.has_record;
                recordinfo = other.recordinfo;
                has_live = other.has_live;
                liveinfo = other.liveinfo;
                whitelists = other.whitelists;
            }

            // Equal overload
            ConfStatus & operator =(const ConfStatus &other)
            {
                // (1) Check self
                if(this == &other)
                    return *this;

                participants.clear();
                assistchairmans.clear();
                subtitlemsg.clear();
                confname = other.confname;
                confmode = other.confmode;
                participants = other.participants;
                chairmansuid = other.chairmansuid;
                assistchairmans = other.assistchairmans;
                duovideoterid = other.duovideoterid;
                stdterseeingstyle = other.stdterseeingstyle;
                isduovideostart = other.isduovideostart;
                isconflocked = other.isconflocked;
                isforcemute = other.isforcemute;
                isdisplaytername = other.isdisplaytername;
                issubtitlestart = other.issubtitlestart;
                subtitlemsg = other.subtitlemsg;
                subtitle = other.subtitle;
                has_record = other.has_record;
                recordinfo = other.recordinfo;
                has_live = other.has_live;
                liveinfo = other.liveinfo;
                whitelists = other.whitelists;
                // （4）Returns a reference to this object
                return *this;
            }

        };

        //增加滚动字幕
        class SRConferenceCtrlAddSubtitle
        {
        public:
            int           sponsortype;   //发起者类型,1-ter、2-web
            std::string   subtitlemsg;   //字幕的内容
            SubtitleInfo  subtitle_info; //字幕显示信息

            SRConferenceCtrlAddSubtitle()
                : sponsortype(1)
                , subtitlemsg("")
            {
            }
        };

        //停止滚动字幕
        class SRConferenceCtrlStopSubtitle
        {
        public:
            int sponsortype;  //发起者类型,1-ter、2-web

            SRConferenceCtrlStopSubtitle()
                : sponsortype(1)
            {
            }
        };

        //显示会场名
        class SRConferenceCtrlDisplayTername
        {
        public:
            int sponsortype;             //发起者类型,1-ter、2-web
            SubtitleInfo  subtitle_info; //会场名显示的位置信息

            SRConferenceCtrlDisplayTername()
                : sponsortype(1)
            {
            }
        };

        //隐藏会场名
        class SRConferenceCtrlHideTername
        {
        public:
            int sponsortype;  //发起者类型,1-ter、2-web

            SRConferenceCtrlHideTername()
                : sponsortype(1)
            {
            }
        };

        //会控者修改会议密码
        class SRConferenceCtrlChangeConfCryptoKey
        {
        public:
            int sponsortype;        //发起者类型,1-ter、2-web
            std::string  cryptokey; //新的会议密钥

            SRConferenceCtrlChangeConfCryptoKey()
                : sponsortype(1)
                , cryptokey("")
            {
            }
            //  copy constructor
            SRConferenceCtrlChangeConfCryptoKey(const SRConferenceCtrlChangeConfCryptoKey &other)
            {
                sponsortype = other.sponsortype;
                cryptokey = other.cryptokey;
            }

            // Equal overload
            SRConferenceCtrlChangeConfCryptoKey & operator =(const SRConferenceCtrlChangeConfCryptoKey &other)
            {
                // (1) Check self
                if(this == &other)
                    return *this;

                cryptokey.clear();
                sponsortype = other.sponsortype;
                cryptokey = other.cryptokey;
                // （4）Returns a reference to this object
                return *this;
            }
        };

        //会控者设置标准终端观看方式
        class SRConferenceCtrlSetStdTerSeeingStyle
        {
        public:
            int sponsortype;  //发起者类型,1-ter、2-web
            int seeingstyle;  //观看方式，0-跟随主持人、1-仅显示主席会场、2-标准终端观看网关分屏布局

            SRConferenceCtrlSetStdTerSeeingStyle()
                : sponsortype(1)
                , seeingstyle(0)
            {
            }

            //  copy constructor
            SRConferenceCtrlSetStdTerSeeingStyle(const SRConferenceCtrlSetStdTerSeeingStyle &other)
            {
                sponsortype = other.sponsortype;
                seeingstyle = other.seeingstyle;
            }

            // Equal overload
            SRConferenceCtrlSetStdTerSeeingStyle & operator =(const SRConferenceCtrlSetStdTerSeeingStyle &other)
            {
                // (1) Check self
                if(this == &other)
                    return *this;

                sponsortype = other.sponsortype;
                seeingstyle = other.seeingstyle;
                // （4）Returns a reference to this object
                return *this;
            }
        };

        //会控者设置白名单
        class SRConferenceCtrlSetWhitelist
        {
        public:
            int sponsortype;             // 发起者类型,1-ter、2-web
            WhiteListInfo whitelistinfo; // 白名单信息

            SRConferenceCtrlSetWhitelist()
                : sponsortype(1)
            {
            }

            //  copy constructor
            SRConferenceCtrlSetWhitelist(const SRConferenceCtrlSetWhitelist &other)
            {
                sponsortype = other.sponsortype;
                whitelistinfo = other.whitelistinfo;
            }

            // Equal overload
            SRConferenceCtrlSetWhitelist & operator =(const SRConferenceCtrlSetWhitelist &other)
            {
                // (1) Check self
                if(this == &other)
                    return *this;

                sponsortype = other.sponsortype;
                whitelistinfo = other.whitelistinfo;
                // （4）Returns a reference to this object
                return *this;
            }

        };


        //增加参会人
        class SRConferenceCtrlAddParticipants
        {
        public:
            int sponsortype;             // 发起者类型,1-ter、2-web

            //参会人信息
            //重点填写的tername/suid/ip/protocoltype/bandwidth/usertype/devicetype
            std::list<TermInfo> participants;

            SRConferenceCtrlAddParticipants()
                : sponsortype(1)
            {
                participants.clear();
            }

            //  copy constructor
            SRConferenceCtrlAddParticipants(const SRConferenceCtrlAddParticipants &other)
            {
                sponsortype = other.sponsortype;
                participants = other.participants;
            }

            // Equal overload
            SRConferenceCtrlAddParticipants & operator =(const SRConferenceCtrlAddParticipants &other)
            {
                // (1) Check self
                if(this == &other)
                    return *this;

                participants.clear();
                sponsortype = other.sponsortype;
                participants = other.participants;
                // （4）Returns a reference to this object
                return *this;
            }

        };

        //删除参会人
        class SRConferenceCtrlDelParticipants
        {
        public:
            int sponsortype;             // 发起者类型,1-ter、2-web

            //参会人的suid集合
            std::list<UINT32> participants;

            SRConferenceCtrlDelParticipants()
                : sponsortype(1)
            {
                participants.clear();
            }

            //  copy constructor
            SRConferenceCtrlDelParticipants(const SRConferenceCtrlDelParticipants &other)
            {
                sponsortype = other.sponsortype;
                participants = other.participants;
            }

            // Equal overload
            SRConferenceCtrlDelParticipants & operator =(const SRConferenceCtrlDelParticipants &other)
            {
                // (1) Check self
                if(this == &other)
                    return *this;

                participants.clear();
                sponsortype = other.sponsortype;
                participants = other.participants;
                // （4）Returns a reference to this object
                return *this;
            }

        };

        //邀请参会人
        class SRConferenceCtrlInvitParticipants
        {
        public:
            int sponsortype;             // 发起者类型,1-ter、2-web

            //参会人信息
            //重点填写的tername/suid/ip/protocoltype/bandwidth/usertype/devicetype
            //如果devicetype 为1即MCU，可以设置呼叫选项calloption
            std::list<TermInfo> participants;

            SRConferenceCtrlInvitParticipants()
                : sponsortype(1)
            {
                participants.clear();
            }

            //  copy constructor
            SRConferenceCtrlInvitParticipants(const SRConferenceCtrlInvitParticipants &other)
            {
                sponsortype = other.sponsortype;
                participants = other.participants;
            }

            // Equal overload
            SRConferenceCtrlInvitParticipants & operator =(const SRConferenceCtrlInvitParticipants &other)
            {
                // (1) Check self
                if(this == &other)
                    return *this;

                participants.clear();
                sponsortype = other.sponsortype;
                participants = other.participants;
                // （4）Returns a reference to this object
                return *this;
            }

        };

        class SRConferenceCtrlStartMeetingRecord
        {
        public:
            int sponsortype;             // 发起者类型,1-ter、2-web
            bool is_record_mp;           //是否录制mp
            int stermid;                 //不录制mp,传入想要录制的终端的stermid
            SRMediaPInfo  mp_info;
            // 录制mp传入想要录制的mp,屏幕设置其中一个
            // 屏幕类型,1 - 会议屏幕 / 网关(标准终端)屏幕、2 - 终端屏幕、3 - 双流屏幕
            // 暂时只能录制1 - 会议屏幕 / 网关(标准终端)屏幕

            SRConferenceCtrlStartMeetingRecord()
                : sponsortype(1)
                , is_record_mp(false)
                , stermid(0)
            {
            }
        };


        class SRConferenceCtrlStopMeetingRecord
        {
        public:
            int sponsortype;             // 发起者类型,1-ter、2-web

            //属性参见SRConferenceCtrlStartMeetingRecord
            bool is_record_mp;
            int stermid;
            SRMediaPInfo  mp_info;


            SRConferenceCtrlStopMeetingRecord()
                : sponsortype(1)
                , is_record_mp(false)
                , stermid(0)
            {
            }
        };

        //开启直播
        class SRConferenceCtrlStartMeetingLive
        {
        public:
            int sponsortype;             // 发起者类型,1-ter、2-web
            bool is_live_mp;            //是否直播mp
            int stermid;                    //不直播mp,传入想要直播的终端的stermid

            SRMediaPInfo  mp_info;
            // 直播mp传入想要直播的mp,屏幕设置其中一个
            // 屏幕类型,1 - 会议屏幕 / 网关(标准终端)屏幕、2 - 终端屏幕、3 - 双流屏幕
            // 暂时只能直播1 - 会议屏幕 / 网关(标准终端)屏幕

            LiveSetting   livesetinfo;      //每次直播的参数设置

            //这个地址需要从restful获取
            std::string     pulladdrprefix;   //直播的拉流地址前缀,与confid+channelid拼成拉流url
            std::string     playaddrprefix;  //直播的播放地址前缀,与confid+channelid拼成播放url

            SRConferenceCtrlStartMeetingLive()
                : sponsortype(1)
                , is_live_mp(false)
                , stermid(0)
                , pulladdrprefix("")
                , playaddrprefix("")
            {
            }
        };


        //停止直播
        class SRConferenceCtrlStopMeetingLive
        {
        public:
            int sponsortype;             // 发起者类型,1-ter、2-web

            //属性参见SRConferenceCtrlStartMeetingLive
            bool is_live_mp;
            int stermid;
            SRMediaPInfo  mp_info;


            SRConferenceCtrlStopMeetingLive()
                : sponsortype(1)
                , is_live_mp(false)
                , stermid(0)
            {
            }
        };

        //修改直播设置
        class SRConferenceCtrlChangeLiveSetting
        {
        public:
            int sponsortype;                     // 发起者类型,1-ter、2-web
            LiveSetting   new_setting;      //新的直播的参数设置


            SRConferenceCtrlChangeLiveSetting()
                : sponsortype(1)
            {
            }
        };


        //投屏终端类型转换
        class SRConferenceCtrlTransferSpecialtype
        {
        public:
            int sponsortype;             // 发起者类型,1-ter、2-web
            int nspcltype;               //new special type, 0-普通终端类型,1-投屏终端类型

            SRConferenceCtrlTransferSpecialtype()
                : sponsortype(1)
                , nspcltype(0)
            {
            }
        };

    }//rtc
} //suirui

#endif //SUIRUI_RTC_TYPE_API_H
