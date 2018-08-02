#include "SREngineConferenceCallback.h"
#include <android/log.h>
#include "Log.h"
#include "SRSdkJni.h"

SREngineConferenceCallback::SREngineConferenceCallback() :
        ISRRtcEngineConferenceEventCallback() {

}

/**
    * @brief OnRspJoinConf 加入会议的回调
    * @param isok          是否加入会议ok
    * @param error   如果失败， 失败错误码
    * @param stermid       返回当前对应的stermid
    */

void SREngineConferenceCallback::OnRspJoinConf(const bool isok, const SRConferenceAbnormal &error,
                                               const int stermid) {

    Log("SRSdkJni..OnRspJoinConf....isok:%d____stermid:%d", isok, stermid);

    OnRspJoinConfCallBack_JNI(isok, error, stermid);
}

/**
 * @brief OnExitConf        退出会议的回调
 * @param exit_reason       exit_reason
 */
void SREngineConferenceCallback::OnExitConf(const char *exit_reason) {
    OnExitConfCallBack_JNI(exit_reason);
}

/**
 * @brief OnNewTermJoinConf     新终端的加入会议
 * @param join_info             新终端信息
 */
void SREngineConferenceCallback::OnNewTermJoinConf(const TermInfo &join_info) {
    onNewTermJoinCallBack_JNI(join_info);
}

/**
 * @brief OnTermLeave       终端的离开会议
 * @param leave_stermid     离开终端termId
 * @param leave_reason      终端离开原因
 */
void SREngineConferenceCallback::OnTermLeave(const int leave_stermid,
                                             const SRConferenceAbnormal &leave_reason) {
    OnTermLeaveCallBack_JNI(leave_stermid, leave_reason);
}

/**
 * @brief OnRspConfTermList
 * @param isok                      //isok 成功 true  失败false
 * @param fail_reason               //失败原因
 * @param chair_stermid             //主席id
 * @param dualvideo_stermid         //共享端的id
 * @param termInfos                 //终端信息链表
 */

void SREngineConferenceCallback::OnRspConfTermList(const bool isok,         //isok 成功 true  失败false
                                                   const SRConferenceAbnormal &error,
                                                   const int chair_stermid,    //主席id
                                                   const int dualvideo_stermid, //共享端的id
                                                   std::deque <TermInfo> & termInfos) { //终端信息链表

    OnRspConfTermListCallBack_JNI(isok, error,
                                  chair_stermid,
                                  dualvideo_stermid, termInfos);
}

/**
 * @brief OnRenderFrame     收到视频数据
 * @param stermid           视频所属终端termid
 * @param flag              视屏类型
 * @param frame             视频数据
 */
void SREngineConferenceCallback::OnRenderFrame(int stermid, int flag,
                                               VideoFrame &frame) {
    OnRenderFrameCallBack_JNI(stermid, flag, frame);
}

/**
 * @brief OnStartSendVideo 请求客户端发送视频流,由其它客户端selectvideo触发
 * @param video_size       视频大小
 */
void SREngineConferenceCallback::OnStartSendVideo(const int video_size) {
    OnStartSendVideoCallBack_JNI(video_size);
}

/**
 * @brief OnStopSendVideo 请求客户端关闭视频流
 */
void SREngineConferenceCallback::OnStopSendVideo() {
    OnStopSendVideoCallBack_JNI();
}

/**
 * @brief OnRspSendDualVideo        开启共享回调
 * @param isok                      是否可以开启共享
 * @param error               失败原因
 */
void SREngineConferenceCallback::OnRspSendDualVideo(const bool isok,
                                                    const SRConferenceAbnormal &error) {
    onRspSendDualVideoCallBack_JNI(isok, error);
}

/**
 * @brief OnRecvDualVideoOpen       其他终端收到有人共享的回调
 * @param dualvideo_send_stermid    共享人termid
 */
void SREngineConferenceCallback::OnRecvDualVideoOpen(const int dualvideo_send_stermid) {
    OnRecvDualVideoOpenCallBack_JNI(dualvideo_send_stermid);
}

/**
 * @brief OnRecvDualVideoClose      其他终端结束共享
 * @param dualvideo_close_stermid   共享终端termid
 */
void SREngineConferenceCallback::OnRecvDualVideoClose(const int dualvideo_close_stermid) {
    OnRecvDualVideoCloseCallBack_JNI(dualvideo_close_stermid);
}

/**
 * @brief OnRecvDualVideoPause      其他终端暂停共享
 * @param dualvideo_pause_stermid   共享终端termid
 */
void SREngineConferenceCallback::OnRecvDualVideoPause(const int dualvideo_pause_stermid) {
    OnRecvDualVideoPauseCallBack_JNI(dualvideo_pause_stermid);
}

/**
 * @brief OnRecvDualVideoResume     其他终端恢复共享
 * @param dualvideo_resume_stermid  共享终端termid
 */
void SREngineConferenceCallback::OnRecvDualVideoResume(const int dualvideo_resume_stermid) {
    OnRecvDualVideoResumeCallBack_JNI(dualvideo_resume_stermid);
}

/**
 * @brief OnReqAssistVideoProxy             共享人收到其他终端在共享
 * @param who_want_send_dualvideo_stermid   申请共享人termid
 */
void SREngineConferenceCallback::OnReqAssistVideoProxy(const int who_want_send_dualvideo_stermid) {
    OnReqAssistVideoProxyCallBack_JNI(who_want_send_dualvideo_stermid);
}

/**
 * @brief OnScreenDrawLabel     参会人标注回调，共享人接收
 * @param attr                  标注信息
 */
void SREngineConferenceCallback::OnScreenDrawLabel(SRScreenLableAttr *attr) {
    OnScreenDrawLabelCallBack_JNI(attr);
}

/**
 * @brief OnScreenClearLabel    参会人清除自己标注的回调，共享人接收
 * @param cleard_stermid        取消标注的参会人termid
 */
void SREngineConferenceCallback::OnScreenClearLabel(int cleard_stermid) {
    OnScreenClearLabelCallBack_JNI(cleard_stermid);
}

/**
 * @brief OnRecvIMMessage     收到其他终端发送的文字信息
 * @param from_stermid          发送的终端termid
 * @param message               文字信息
 */
void
SREngineConferenceCallback::OnRecvIMMessage(const int from_stermid, const std::string &message) {
    OnRecvIMMessageCallBack_JNI(from_stermid,message);
}

/**
 * @brief OnOpenCamera      其他终端摄像头打开的回调
 * @param open_stermid      对应终端termId
 */
void SREngineConferenceCallback::OnOpenCamera(const int open_stermid) {
    onOpenCameraCallBack_JNI(open_stermid);
}

/**
 * @brief OnCloseCamera     其他终端关闭摄像头
 * @param close_stermid     对应终端termid
 */
void SREngineConferenceCallback::OnCloseCamera(const int close_stermid) {
    onCloseCameraCallBack_JNI(close_stermid);
}

/**
 * @brief OnTermAudioRecMute    终端被静音的回调
 * @param mute_stermid          被静音的终端termid
 */
void SREngineConferenceCallback::OnTermAudioRecMute(const int mute_stermid) {
    onTermAudioRecMuteCallBack_JNI(mute_stermid);
}

/**
 * @brief OnTermAudioRecUnMute  终端被解除静音的回调
 * @param cancel_stermid        被解除静音的termid
 */
void SREngineConferenceCallback::OnTermAudioRecUnMute(const int cancel_stermid) {
    onTermAudioRecUnMuteCallBack_JNI(cancel_stermid);
}

/**
 * @brief OnOtherTermRunningStatus      透传回调
 * @param stautsTermid                  透传信息的发起终端termid
 * @param staClass                      透传信息类型
 * @param staSubCls                     透传信息子类型
 * @param staStr                        透传信息字符串信息
 */
void SREngineConferenceCallback::OnOtherTermRunningStatus(const int stautsTermid,
                                                          const int staClass, const int staSubCls,
                                                          const std::string staStr) {
    OnOtherTermRunningStatusCallBack_JNI(stautsTermid, staClass, staSubCls, staStr);
}

/**
* @brief onMpInfo       有mpinfo添加或者删除
* @param channelid		mp的channelId
* @param addordel       1：添加 2:删除
* @return
*/
void SREngineConferenceCallback::OnMPInfo(const int channelid, const int addordel) {

}

/**
* @brief onMpScreenInfo     有mpinfo添加或者删除
* @param channelid          mp的channelId
* @param screenid           流id
* @param screentype         流类型
* @param addordel           1：添加 2:删除
* @return
*/
void SREngineConferenceCallback::OnMPScreenInfo(const int channelid, const int screenid,
                                                const int screentype, const int addordel) {
    OnMPScreenInfoCallback_JNI(channelid, screenid, screentype, addordel);
}

/**
* @brief onAllMPInfo    mpinfo整体更新
* @param mpiNum         mpinfo的个数
* @param mpis           mpinfo列表
* @return
*/
void SREngineConferenceCallback::OnAllMPInfo(std::list<SRMediaPInfo>& mpis) {
    OnAllMPInfoCallBack_JNI(mpis);
}

/**
 * @brief onServerError 服务器错误回调（包括之前的onStackConnectError）,仍然需要主动退会
 * @param err           错误类型
 */
void SREngineConferenceCallback::onServerError(SR_ERROR_CODE_TYPE err) {
    onServerErrorCallBack_JNI(err);
}

/**
 * @brief OnTelphoneCallComing      其他手机终端进入通话中状态
 * @param call_telphone_stermid     对应手机终端termid
 */
void SREngineConferenceCallback::OnTelphoneCallComing(const int call_telphone_stermid) {

}

/**
 * @brief OnTelphoneHangUp          其他手机终端结束通话状态
 * @param handup_telphone_stermid   对应手机终端termid
 */
void SREngineConferenceCallback::OnTelphoneHangUp(const int handup_telphone_stermid) {

}


 /**
 * @brief onServerOk          网络异常，重新连接成功了
 * @param SR_OK_CODE_TYPE
 */
void SREngineConferenceCallback::onServerOk(const SR_OK_CODE_TYPE ok){
    onServerOkCallBack_JNI(ok);
}

