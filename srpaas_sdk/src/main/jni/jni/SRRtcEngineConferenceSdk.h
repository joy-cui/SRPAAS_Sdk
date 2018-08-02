#ifndef SRSDKUNDERLINE_H
#define SRSDKUNDERLINE_H

#include "ISRRtcEngine.h"
#include "ISRRtcType.h"

using namespace suirui::rtc;

#define gSdk SR::SRRtcEngineConferenceSdk::instance()
#define gSdkConferenceControl SR::SRRtcEngineConferenceSdk::instance()->ConferenceControlInterface()
#define gSdkSystemMessageInfo SR::SRRtcEngineConferenceSdk::instance()->SystemMessageInfoInterface()
#define gSdkAudioDeviceManage SR::SRRtcEngineConferenceSdk::instance()->AudioDeviceManager()
#define gSdkSdkVideoDeviceManage SR::SRRtcEngineConferenceSdk::instance()->VideoDeviceManager()


class SREngineDataCallback;

class SREngineDeviceCallback;

class SREngineConferenceCallback;

class SREngineConferenceControlCallback;

namespace SR {

    class SRRtcEngineConferenceSdk {
    public:
        static SRRtcEngineConferenceSdk *instance();

    protected:
        SRRtcEngineConferenceSdk();

        ~SRRtcEngineConferenceSdk();

    public:
        /**获取视频设备管理器 */
        ISRVideoDeviceManager *VideoDeviceManager() const;

        /**获取音频设备管理器 */
        ISRAudioDeviceManager *AudioDeviceManager() const;

        /**获取系统信息接口 */
        ISRRtcEngineSystemMessageInfo *SystemMessageInfoInterface();

        /**获取会控管理接口 */
        ISRRtcEngineConferenceControl *ConferenceControlInterface() const;

        /**获取SREngine版本 */
        int GetVersion(char build_version[SR_MAX_BUFFER_ID_LENGTH]);

        /**
         * @brief SetCryptionContent    设置密钥模式内容
         * @param content               模式内容
         * @return                      0 if success or an error code
         */
        int SetCryptionContent(CryptionContent &content);

        /**
         * @brief ReqJoinConf           加入会议(已处理)
         * @param joinconf_context      会议信息
         * @return                      0 if success or an error code
         */
        int ReqJoinConf(const SRRtcEngineJoinConfContext &joinconf_context);

        /**
         * @brief ExitConf              退出会议(已处理)
         * @param exit_reason           退会原因
         * @return                      0 if success or an error code
         */
        int ExitConf(const char *exit_reason);

        /**
         *@brief ChairEndConf   主持人结束会议
         */
        int ChairEndConf();

        /**
         * @brief InPutVideoRawStream   向SREngine发送数据帧(已处理)
         * @param type                  数据帧类型
         * @param frame                 数据帧类容
         * @return                      0 if success or an error code
         */
        int InPutVideoRawStream(SR_VIDEO_STREAM_TYPE type, VideoFrame &frame);

        /**
         * @brief EnableReqConfTermList 获取参会人列表(已处理)
         * @return                      0 if success or an error code
         */
        int EnableReqConfTermList();

        /**
         * @brief SelectVideo           选看视频流(已处理)
         * @param mul_streams           选看信息列表
         * @return                      0 if success or an error code
         */
        int SelectVideo(list <RequestVideoParam> mul_streams);

        /**
         * @brief StartSendDualVideo    开启共享(已处理)
         * @param capture_wnd           采集的窗口
         * @return                      0 if success or an error code
         */
        int StartSendDualVideo(view_t capture_wnd);

        /**
         * @brief SetSendDualVideo      共享期间切换采集窗口
         * @param capture_wnd           采集的窗口句柄
         * @return                      0 if success or an error code
         */
        int SetSendDualVideo(view_t capture_wnd);

        /**
         * @brief StopSendDualVideo     停止共享(已处理)
         * @return                      0 if success or an error code
         */
        int StopSendDualVideo();

        /**
         * @brief PauseSendDualVideo    暂停共享(已处理)
         * @return                      0 if success or an error code
         */
        int PauseSendDualVideo();

        /**
         * @brief ResumeSendDualVideo   恢复共享(已处理)
         * @return                      0 if success or an error code
         */
        int ResumeSendDualVideo();

        /**
         * @brief RspSendDualVideoProxy (已处理)     回复桌面共享申请者， 这个是在对端调用StartSendDualVideo之后， 第一个共享者收到回调OnReqAssistVideoProxy之后的动作
         * @param want_send_dualvideo_stermid       请求共享端ID
         * @param agree                             是否同意
         * @param disagree_reason                   拒绝原因
         * @return                                  0 if success or an error code
         */
        int RspSendDualVideoProxy(const int want_send_dualvideo_stermid, const bool agree,
                                  const char *disagree_reason);

        /**
         * @brief AddScreenLabel        桌面共享其他客户端添加备注(已处理)
         * @param attr                  备注结构
         * @return                      0 if success or an error code
         */
        int AddScreenLabel(SRScreenLableAttr &attr);

        /**
         * @brief StartVideoPreview     开启预览功能
         * @param wnds                  窗体结构链表，如果需要多个窗体需加入到链表当中
         * @return                      0 if success or an error code
         */
        int StartVideoPreview(list <view_t> wnds);

        /**
         * @brief StopVideoPreview      停止预览
         * @return                      0 if success or an error code
         */
        int StopVideoPreview();

        /**
         * @brief RunningChgAudioCaptureDevice  设置麦克风
         * @param audio_input_name              麦克风
         * @return                              0 if success or an error code
         */
//        int RunningChgAudioCaptureDevice(const char *audio_input_name);

        /**
         * @brief RunningChgAudioOutputDevice   设置扬声器
         * @param audio_output_name             扬声器
         * @return                              0 if success or an error code
         */
//        int RunningChgAudioOutputDevice(const char *audio_output_name);

        /**
         * @brief RunningChgCameraCaptureDevice 切换摄像头
         * @param camera_name                   摄像头名字
         * @return                              0 if success or an error code
         */
//        int RunningChgCameraCaptureDevice(const char *camera_name);

        /**
         * @brief SetCameraOn               关闭/打开终端摄像头
         * @param stermid                   被关闭/打开终端termid（暂时只能关闭自己）
         * @param mute                      true:打开  false:关闭
         * @return                          0 if success or an error code
         */
        int SetCameraOn(const int stermid, bool on);

        /**
         * @brief SetAudioMute              紧音/解除紧音
         * @param stermid                   被禁音/解除禁音终端termid
         * @param on                        true:静音  false:解除静音
         * @return                          0 if success or an error code
         */
        int SetAudioMute(const int stermid, bool on);

        /**
       *全部静音/取消全部静音
       */
        int MuteAudioAllTerm(bool on);

        /**
         * @brief EnableRecvStreamInfoIndication    使能获取当前收到流统计信息状态, 传0 代表停止统计
         * @param interval                          事件间隔 单位 毫秒 5000ms --->5s
         * @return                                  0 if success or an error code
         */
        int EnableRecvStreamInfoIndication(int interval);

        /**
         * @brief EnableSendStreamInfoIndication    使能获取当前发送统计信息状态, 传0 代表停止统计
         * @param interval                          事件间隔 单位 毫秒 5000ms --->5s
         * @return                                  0 if success or an error code
         */
        int EnableSendStreamInfoIndication(int interval);

        /**
         * @brief EnableTelphoneCallComing      通知其它客户端，我有电话打进来，针对手机
         * @return                              0 if success or an error code
         */
        int EnableTelphoneCallComing();

        /**
         * @brief DisableTelphoneCallComing     通知其它客户端，我已经结束打电话，针对手机
         * @return                              0 if success or an error code
         */
        int DisableTelphoneCallComing();

        /**
         * @brief RunningStatusNotify       透传自定义信息
         * @param sta_class                 自定义信息类型
         * @param sta_sub_class             自定义信息子类型
         * @param status_str                自定义信息文字内容
         * @return                          0 if success or an error code
         */
        int RunningStatusNotify(const int sta_class, const int sta_sub_class,
                                const char *status_str);

        /**
         * @brief StartPlayingFileAsMicrophone  开启本地声音代替麦克风采集的声音
         * @param wav_name                      声音文件
         * @return                              0 if success or an error code
         */
        int StartPlayingFileAsMicrophone(const char *wav_name);

        /**
         * @brief StopPlayingFileAsMicrophone   停止本地声音代替麦克风采集的声音
         * @return                              0 if success or an error code
         */
        int StopPlayingFileAsMicrophone();

        /**
         * @brief  initSrEnginConferenceSdk    初始化
         */
        int initSrEnginConferenceSdk(bool isopensdklog,bool isH264Decode,int platformType);

        /**
         * @brief UnInitSDK 注销SDK
         */
        int UnInitSDK();

        /**
         *   @brief    DropTerm    主持人权限
         *   @param  drop_stermid
         */
        int DropTerm(const int drop_stermid);

        /**
         * @brief  MasterTransfer 主持人转让主持人身份,只有主持人可以发出去(需要ACK)
         * @param new_stermid
         */
        int MasterTransfer(const int new_stermid);

        /**
         * @brief  LockVideo 主持人指定会议室内其它人看某一个客户端的视频
         * @param lock_stermid
         */
        int LockVideo(const int lock_stermid);

        /**
        * @brief  UnLockVideo 主持人取消指定会议室内其它人看某一个客户端的视频
        * @param unlock_stermid
        */
        int UnLockVideo(const int unlock_stermid);

        /**
         * @brief  ChairEndDataShare 会中有共享，主持人可结束
         * @param unlock_stermid
         */
        int ChairEndDataShare();

        /**
         * @brief  LockConf 锁定会议(主持人锁定会议后，新终端无法加入会议)
         * @param islock
         */
        int LockConf(const bool islock);

        /**
         * @brief  HandUp 锁定会议(主持人锁定会议后，新终端无法加入会议)
         *  @param handup
         */
        int HandUp(const bool handup);

        /**
         * @brief  ChangeTermName 修改终端名称
         *  @param new_name
         */
        int ChangeTermName(const char *new_name);

        /**
         *@brief 测试按钮，写文件
         * @param argc argv[]
         */
        int SetUserCmdToEngine(int argc, char *argv[]);

        /**
        *@brief 切换网络
        *
        */
        int NotifyNetworkChanged();

        /**
         *设置扬声器的模式
         */
        int SetSpeakerMode(int mode);

        /**
         *获取apm认证mac信息
         */
        std::string GetApmInfoSDK();

        /**
         * 设置APM认证key
         */
        int SetApmKeyContentSDK(const std::string &key);

        /*
        *设置当前扬声器的音量
        */
        int SetOutputDeviceVolume(int volume);

        /**
         * 支持人设置强制静音
         */
        int ForceMuteAudio(const SRConferenceCtrlForceMute &forcemuteinfo);

        /**
         * 获取会议信息
         */
        int ReqSRConfStatus(const SRConferenceCtrlReqConfStatus &getconfstatus);

        /**
			* 删除参会人, 既可以删除在会的，也可以删除不在会的， 删除参会人后会删除数据库
			* @param [in ] participants
			*        删除参会人会控结构
			* @return return 0 if success or an error code
			*/
        int DelParticipants(const SRConferenceCtrlDelParticipants &del_participants);

        /**
         * 重启音频设备
         */
        int ResetAudioDevice();

        /**
         * 设置用户需要设置的信息给sdk
         */
        int SetUsrNotify(const SRUserSetParam &param);

        /**
         * 开始会议录制
         */
        int StartMeetingRecord(SRConferenceCtrlStartMeetingRecord &start_meeting_record);

        /**
         *停止会议录制
         */
        int StopMeetingRecord(SRConferenceCtrlStopMeetingRecord &stop_meeting_record);

        /**
         * 获取当前的网络状态
         */
        int GetNetWorkStatusNotify(NetWorkStatus &status);

        /**
         * 开启直播
         */
        int StartMeetingLive(SRConferenceCtrlStartMeetingLive &start_meeting_live);

        /**
         * 停止直播
         */
        int StopMeetingLive(SRConferenceCtrlStopMeetingLive &stop_meeting_live);

        /**
         * 改变直播参数
         */
        int ChangeLiveSetting(SRConferenceCtrlChangeLiveSetting &change_meeting_setting);

        /**
         * 发送消息
         * @param [in ] to_termid_list
         *                   给哪些终端发的列表
         * @param [in ] message
         *                   发送消息内容
         * @return return 0 if success or an error code
         */
        int SendIMMessage(std::list<int> &to_termid_list, const std::string &message);
    private:
        /**SREngine的指针 */
        ISRRtcEngineConference *m_pSRConferenceEngine;
        ISRRtcEngineConferenceControl *m_pSRConferenceEngineControl;
        ISRRtcEngineSystemMessageInfo *m_pSRRtcEngineSystemMessageInfo;
        ISRAudioDeviceManager *m_pISRAudioDeviceManager;

    private:
        static SRRtcEngineConferenceSdk *pInstance;
        /**数据回调 */
        SREngineDataCallback *m_pDataCallback;
        /**设备回调 */
        SREngineDeviceCallback *m_pDeviceCallback;
        /**会议信息回调 */
        SREngineConferenceCallback *m_pConferenceCallback;
        /**会控回调 */
        SREngineConferenceControlCallback *m_pConferenceControlCallback;
    };

}


#endif // SRSDKUNDERLINE_H
