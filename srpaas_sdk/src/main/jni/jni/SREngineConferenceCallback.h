#ifndef SRENGINECONFERENCECALLBACK_H
#define SRENGINECONFERENCECALLBACK_H

#include "ISRRtcEngine.h"

using namespace suirui::rtc;

/**
 * 会议相关回调
 */
class SREngineConferenceCallback : public ISRRtcEngineConferenceEventCallback {
public:
    SREngineConferenceCallback();

public:
    /**
     * @brief OnRspJoinConf 加入会议的回调(已处理)
     * @param isok          是否加入会议ok
     * @param fail_reason   如果失败， 失败错误码
     * @param stermid       返回当前对应的stermid
     */
    virtual void OnRspJoinConf(const bool isok, const SRConferenceAbnormal &error,
                               const int stermid);

    /**
     * @brief OnExitConf        退出会议的回调(已处理)
     * @param exit_reason       exit_reason
     */
    virtual void OnExitConf(const char *exit_reason);

    /**
     * @brief OnNewTermJoinConf     新终端的加入会议(已处理)
     * @param join_info             新终端信息
     */
    virtual void OnNewTermJoinConf(const TermInfo &join_info);

    /**
     * @brief OnTermLeave       终端的离开会议(已处理)
     * @param leave_stermid     离开终端termId
     * @param leave_reason      终端离开原因
     */
    virtual void OnTermLeave(const int leave_stermid, const SRConferenceAbnormal &leave_reason);

    /**
     * @brief OnRspConfTermList (已处理)
     * @param isok                      //isok 成功 true  失败false
     * @param fail_reason               //失败原因
     * @param chair_stermid             //主席id
     * @param dualvideo_stermid         //共享端的id
     * @param termInfos                 //终端信息链表
     */
    virtual void OnRspConfTermList(const bool isok,         //isok 成功 true  失败false
                                   const SRConferenceAbnormal &error,
                                   const int chair_stermid,    //主席id
                                   const int dualvideo_stermid, //共享端的id
                                   std::deque <TermInfo> & termInfos);   //终端信息链表

    /**
     * @brief OnRenderFrame     收到视频数据(已处理)
     * @param stermid           视频所属终端termid
     * @param flag              视屏类型
     * @param frame             视频数据
     */
    virtual void OnRenderFrame(int stermid, int flag, VideoFrame &frame);

    /**
     * @brief OnStartSendVideo 请求客户端发送视频流,由其它客户端selectvideo触发(已处理)
     * @param video_size       视频大小
     */
    virtual void OnStartSendVideo(const int video_size);

    /**
     * @brief OnStopSendVideo 请求客户端关闭视频流(已处理)
     */
    virtual void OnStopSendVideo();

    /**
     * @brief OnRspSendDualVideo        开启共享回调(已处理)
     * @param isok                      是否可以开启共享
     * @param fail_reason               失败原因
     */
    virtual void OnRspSendDualVideo(const bool isok, const SRConferenceAbnormal &error);

    /**
     * @brief OnRecvDualVideoOpen       其他终端收到有人共享的回调(已处理)
     * @param dualvideo_send_stermid    共享人termid
     */
    virtual void OnRecvDualVideoOpen(const int dualvideo_send_stermid);

    /**
     * @brief OnRecvDualVideoClose      其他终端结束共享(已处理)
     * @param dualvideo_close_stermid   共享终端termid
     */
    virtual void OnRecvDualVideoClose(const int dualvideo_close_stermid);

    /**
     * @brief OnRecvDualVideoPause      其他终端暂停共享(已处理)
     * @param dualvideo_pause_stermid   共享终端termid
     */
    virtual void OnRecvDualVideoPause(const int dualvideo_pause_stermid);

    /**
     * @brief OnRecvDualVideoResume     其他终端恢复共享(已处理)
     * @param dualvideo_resume_stermid  共享终端termid
     */
    virtual void OnRecvDualVideoResume(const int dualvideo_resume_stermid);

    /**
     * @brief OnReqAssistVideoProxy             共享人收到其他终端在共享(已处理)
     * @param who_want_send_dualvideo_stermid   申请共享人termid
     */
    virtual void OnReqAssistVideoProxy(const int who_want_send_dualvideo_stermid);

    /**
     * @brief OnScreenDrawLabel     参会人标注回调，共享人接收(已处理)
     * @param attr                  标注信息
     */
    virtual void OnScreenDrawLabel(SRScreenLableAttr *attr);

    /**
     * @brief OnScreenClearLabel    参会人清除自己标注的回调，共享人接收
     * @param cleard_stermid        取消标注的参会人termid
     */
    virtual void OnScreenClearLabel(int cleard_stermid);

    /**
     * @brief OnRecvIMMessage     收到其他终端发送的文字信息
     * @param from_stermid          发送的终端termid
     * @param message               文字信息
     */
    virtual void OnRecvIMMessage(const int from_stermid, const std::string &message);

    /**
     * @brief OnOpenCamera      其他终端摄像头打开的回调
     * @param open_stermid      对应终端termId
     */
    virtual void OnOpenCamera(const int open_stermid);

    /**
     * @brief OnCloseCamera     其他终端关闭摄像头
     * @param close_stermid     对应终端termid
     */
    virtual void OnCloseCamera(const int close_stermid);

    /**
     * @brief OnTermAudioRecMute    终端被静音的回调
     * @param mute_stermid          被静音的终端termid
     */
    virtual void OnTermAudioRecMute(const int mute_stermid);

    /**
     * @brief OnTermAudioRecUnMute  终端被解除静音的回调
     * @param cancel_stermid        被解除静音的termid
     */
    virtual void OnTermAudioRecUnMute(const int cancel_stermid);

    /**
     * @brief OnOtherTermRunningStatus      透传回调
     * @param stautsTermid                  透传信息的发起终端termid
     * @param staClass                      透传信息类型
     * @param staSubCls                     透传信息子类型
     * @param staStr                        透传信息字符串信息
     */
    virtual void OnOtherTermRunningStatus(const int stautsTermid, const int staClass,
                                          const int staSubCls, const std::string staStr);

    /**
    * @brief onMpInfo       有mpinfo添加或者删除
    * @param channelid		mp的channelId
    * @param addordel       1：添加 2:删除
    * @return
    */
    virtual void OnMPInfo(const int channelid, const int addordel);

    /**
    * @brief onMpScreenInfo     有mpinfo添加或者删除
    * @param channelid          mp的channelId
    * @param screenid           流id
    * @param screentype         流类型
    * @param addordel           1：添加 2:删除
    * @return
    */
    virtual void OnMPScreenInfo(const int channelid, const int screenid, const int screentype,
                                const int addordel);

    /**
    * @brief onAllMPInfo    mpinfo整体更新
    * @param mpiNum         mpinfo的个数
    * @param mpis           mpinfo列表
    * @return
    */
    virtual void OnAllMPInfo(std::list<SRMediaPInfo>& mpis);

    /**
     * @brief onServerError 服务器错误回调（包括之前的onStackConnectError）,仍然需要主动退会
     * @param err           错误类型
     */
    virtual void onServerError(SR_ERROR_CODE_TYPE err);

    /**
     * @brief OnTelphoneCallComing      其他手机终端进入通话中状态
     * @param call_telphone_stermid     对应手机终端termid
     */
    virtual void OnTelphoneCallComing(const int call_telphone_stermid);

    /**
     * @brief OnTelphoneHangUp          其他手机终端结束通话状态
     * @param handup_telphone_stermid   对应手机终端termid
     */
    virtual void OnTelphoneHangUp(const int handup_telphone_stermid);

    /**
    * @brief onServerOk          网络异常，重新连接成功了
    * @param SR_OK_CODE_TYPE
    */
    virtual void onServerOk(const SR_OK_CODE_TYPE ok);
};

#endif // SRENGINECONFERENCECALLBACK_H
