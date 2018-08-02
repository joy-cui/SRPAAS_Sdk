#include <jni.h>

#ifndef _Included_Conference_jni
#define _Included_Conference_jni

#include <signal.h>
#include "typedefs.h"
#include "SRRtcEngineConferenceSdk.h"

#ifdef __cplusplus
extern "C" {
#endif
void android_sigaction(int signal, siginfo_t *info, void *reserved);


jstring stoJstring(JNIEnv *env, const char *pat);
jobject SendStreamInfoStruct(JNIEnv *env, const SendStreamInfo &stats, jobject info_obj);
jobject RecvStreamInfoStruct(JNIEnv *env, const RecvStreamInfo &stats, jobject info_obj);
jobject RecvVideoStreamStruct(JNIEnv *env, int id, jstring codecName,
                              int fps, int bitRate, float loseRate,
                              int width, int height, jobject info_obj);

jobject RecvAudioStreamStruct(JNIEnv *env, int id, jstring codecName,
                              int sampleRate, int bitRate, int recCodecChs,
                              float loseRate, jobject info_obj);
jobject RecvH239StreamStruct(JNIEnv *env, int id, jstring codecName,
                             int fps, int bitRate, float loseRat,
                             int width, int height, jobject info_obj);


JNIEXPORT jint
JNICALL Java_org_suirui_srpaas_jni_JniNative_InitSDK(JNIEnv *env,
                                                     jclass jcls,
                                                     jboolean isopensdklog,jboolean isH264Decode,jint platformType);
JNIEXPORT jint
JNICALL Java_org_suirui_srpaas_jni_JniNative_UnInitSDK(
        JNIEnv *env, jclass jcls);


//共享内存
JNIEXPORT jint
JNICALL Java_org_suirui_srpaas_jni_JniNative_SREngineInVideoRawStreamDataBuf(JNIEnv *env, jclass jcls, jint streamType, jint formatType, jobject byteArray, jint width, jint height, jint rotationType, jboolean isMirror, jint size);
//初始化配置H264数据大小
JNIEXPORT jint
JNICALL Java_org_suirui_srpaas_jni_JniNative_setReceiveByteBufferData(
        JNIEnv *env, jclass jcls,jobject bufObj);





//加入会议
JNIEXPORT jint
JNICALL Java_org_suirui_srpaas_jni_JniNative_reqestJoinConf(JNIEnv *env, jclass jcls,
                                                            jobject joinConfObject,
                                                            jobject userInfoObject,
                                                            jboolean isCameraOn,
                                                            jboolean isMute);


//退出会议
JNIEXPORT jint
JNICALL Java_org_suirui_srpaas_jni_JniNative_requestExitConf(JNIEnv *env, jclass jcls,
                                                             jstring exit_reason);

//主持人结束会议
JNIEXPORT jint
JNICALL Java_org_suirui_srpaas_jni_JniNative_requestChairEndConf(JNIEnv *env, jclass jcls);

//  向SREngine发送数据帧(发送流 )
JNIEXPORT jint
JNICALL Java_org_suirui_srpaas_jni_JniNative_SREngineInVideoRawStreamRGB(JNIEnv *env, jclass jcls,
                                                                         jint streamType,
                                                                         jint formatType,
                                                                         jint width, jint height,
                                                                         jintArray rgbArray,
                                                                         jint size);

//  向SREngine发送数据帧(发送流 )
JNIEXPORT jint
JNICALL Java_org_suirui_srpaas_jni_JniNative_SREngineInVideoRawStreamYUV(JNIEnv *env, jclass jcls,
                                                                         jint streamType,
                                                                         jint formatType,
                                                                         jint width, jint height,
                                                                         jbyteArray byteArray,
                                                                         jint size);

//获取参会人列表
JNIEXPORT jint
JNICALL Java_org_suirui_srpaas_jni_JniNative_requestTerminalmList(
        JNIEnv *env, jclass jcls);


//选看视频
JNIEXPORT jint
JNICALL Java_org_suirui_srpaas_jni_JniNative_requestSelectRemoteVideo(JNIEnv *env, jclass jcls,
                                                                      jobject videoparamList);

/**
 * 开启共享
 */
JNIEXPORT jint
JNICALL Java_org_suirui_srpaas_jni_JniNative_requestStartSendDualVideo(JNIEnv *env, jclass jcls,
                                                                       jobject wnd_);

//   停止共享
JNIEXPORT jint
JNICALL Java_org_suirui_srpaas_jni_JniNative_requestStopSendDualVideo(JNIEnv *env, jclass jcls);


// 暂停共享
JNIEXPORT jint
JNICALL Java_org_suirui_srpaas_jni_JniNative_requestPauseSendDualVideo(JNIEnv *env, jclass jcls);

// 恢复共享
JNIEXPORT jint
JNICALL Java_org_suirui_srpaas_jni_JniNative_requestResumeSendDualVideo(JNIEnv *env, jclass jcls);
//恢复共享申请者
JNIEXPORT jint
JNICALL Java_org_suirui_srpaas_jni_JniNative_resposeSendDualVideoProxy(JNIEnv *env, jclass jcls,
                                                                       jint avterid, jboolean isok,
                                                                       jstring rejectreason);
// 桌面共享其他客户端添加备注
JNIEXPORT jint
JNICALL Java_org_suirui_srpaas_jni_JniNative_requestAddScreenLabel(JNIEnv *env, jclass jcls,
                                                                   jobject addLabelObject);


//打开本地摄像头指示
JNIEXPORT jint
JNICALL Java_org_suirui_srpaas_jni_JniNative_openCamera(JNIEnv *env, jclass jcls,
                                                        jint unmute_stermid);

//关闭本地相机
JNIEXPORT jint
JNICALL Java_org_suirui_srpaas_jni_JniNative_closeCamera(JNIEnv *env, jclass jcls,
                                                         jint mute_stermid);


//静音
JNIEXPORT jint
JNICALL Java_org_suirui_srpaas_jni_JniNative_muteAudio(JNIEnv *env, jclass jcls,
                                                       jint mute_stermid);

//取消静音
JNIEXPORT jint
JNICALL Java_org_suirui_srpaas_jni_JniNative_unMuteAudio(JNIEnv *env, jclass jcls,
                                                         jint unmute_stermid);


//全部静音/取消全部静音
JNIEXPORT jint
JNICALL Java_org_suirui_srpaas_jni_JniNative_MuteAudioAllTerm(JNIEnv *env, jclass jcls,
                                                              jboolean isMute);


//举手
JNIEXPORT jint
JNICALL Java_org_suirui_srpaas_jni_JniNative_requestHandUp(JNIEnv *env, jclass jcls,
                                                           jboolean handUp);

//改名
JNIEXPORT jint
JNICALL Java_org_suirui_srpaas_jni_JniNative_changeName(JNIEnv *env, jclass jcls,
                                                        jstring changename);
//设置焦点视频
JNIEXPORT jint
JNICALL Java_org_suirui_srpaas_jni_JniNative_lockOrUnLockVideo(JNIEnv *env, jclass jcls,
                                                               jint lock_id, jboolean isLock);

//主持人踢人
JNIEXPORT jint
JNICALL Java_org_suirui_srpaas_jni_JniNative_requestRemoveTerminal(JNIEnv *env, jclass jcls,
                                                                   jint termid);
//会中有共享，主持人可结束
JNIEXPORT jint
JNICALL Java_org_suirui_srpaas_jni_JniNative_chairEndDataShare(JNIEnv *env, jclass jcls);

//主持人权限转移
JNIEXPORT jint
JNICALL Java_org_suirui_srpaas_jni_JniNative_setMasterId(JNIEnv *env, jclass jcls,
                                                         jint newMasterId);
//使能获取当前收到流统计信息状态, 传0 代表停止统计
JNIEXPORT jint
JNICALL Java_org_suirui_srpaas_jni_JniNative_getSendStreamInfoIndication(JNIEnv *env, jclass jcls,
                                                                         jint interval);

//使能获取当前发送统计信息状态, 传0 代表停止统计
JNIEXPORT jint
JNICALL Java_org_suirui_srpaas_jni_JniNative_getRecvStreamInfoIndication(JNIEnv *env, jclass jcls,
                                                                         jint interval);

//相机采集的数据
JNIEXPORT jint
JNICALL Java_org_suirui_srpaas_jni_JniNative_SREngineInVideoRawStreamData(JNIEnv *env, jclass jcls,
                                                                          jint videoStreamType,
                                                                          jint formatType,
                                                                          jbyteArray byteArray,
                                                                          jint width,
                                                                          jint height,
                                                                          jint rotationType,
                                                                          jboolean isMirror,
                                                                          jint size);

//测试按钮写文件
JNIEXPORT jint
JNICALL Java_org_suirui_srpaas_jni_JniNative_SRSetUserCmdToEngine(JNIEnv *env, jclass jcls,
                                                                  jobjectArray strArray);

//网络监听
JNIEXPORT jint
JNICALL Java_org_suirui_srpaas_jni_JniNative_SREngineNetworkChanged(JNIEnv *env, jclass jcls);


//设置扬声器的模式
JNIEXPORT jint
JNICALL Java_org_suirui_srpaas_jni_JniNative_SREngineSetSpeakerMode(JNIEnv *env, jclass jcls,
                                                                    jint mode);
//设置终端状态
JNIEXPORT jint
JNICALL Java_org_suirui_srpaas_jni_JniNative_SREngineRunningStatusNotify(JNIEnv *env, jclass jcls,
                                                                         jint sta_class,
                                                                         jint sta_sub_class,
                                                                         jstring status_str);

//获取apm认证mac信息
JNIEXPORT jstring
JNICALL Java_org_suirui_srpaas_jni_JniNative_getApmInfo(JNIEnv *env, jclass jcls);

//设置APM认证key
JNIEXPORT jint
JNICALL Java_org_suirui_srpaas_jni_JniNative_setApmKeyContent(JNIEnv *env, jclass jcls,
                                                              jstring key);


jboolean file_open(const char *filename);
JNIEXPORT jboolean
JNICALL Java_org_suirui_srpaas_jni_JniNative_openFile(JNIEnv *env, jclass jcls, jstring filename);
JNIEXPORT jint
JNICALL Java_org_suirui_srpaas_jni_JniNative_closeFile(JNIEnv *env, jclass jcls);

//设置当前扬声器的音量
JNIEXPORT jint
JNICALL Java_org_suirui_srpaas_jni_JniNative_SRSetOutputDeviceVolume(JNIEnv *env, jclass jcls,
                                                                     jint volume);

//设置强制静音
JNIEXPORT jint
JNICALL Java_org_suirui_srpaas_jni_JniNative_SRSetForceMuteAudio(JNIEnv *env, jclass jcls,
                                                                 jint sorttype,
                                                                 jboolean isforcemute);
//获取会议信息
JNIEXPORT jint
JNICALL Java_org_suirui_srpaas_jni_JniNative_SRReqSRConfStatus(JNIEnv *env, jclass jcls,
                                                               jint sorttype);
//锁定会议
JNIEXPORT jint
JNICALL Java_org_suirui_srpaas_jni_JniNative_SRLockConf(JNIEnv *env, jclass jcls,
                                                        jboolean islockconf);
//锁定会议时，主持人踢除参会人
JNIEXPORT jint
JNICALL Java_org_suirui_srpaas_jni_JniNative_SRDelParticipants(JNIEnv *env, jclass jcls,
                                                               jobject delparlist);
//重启音频设备
JNIEXPORT jint
JNICALL Java_org_suirui_srpaas_jni_JniNative_SRresetAudioDevice(JNIEnv *env, jclass jcls);

//设置用户需要设置的信息给sdk
JNIEXPORT jint
JNICALL Java_org_suirui_srpaas_jni_JniNative_SRSetUsrNotify(JNIEnv *env, jclass jcls, jint netType);

//开始会议的录制
JNIEXPORT jint
JNICALL Java_org_suirui_srpaas_jni_JniNative_StartMeetingRecord(JNIEnv *env, jclass jcls,
                                                                jint channelid,
                                                                jobject screensList);
//停止会议录制
JNIEXPORT jint
JNICALL Java_org_suirui_srpaas_jni_JniNative_StopMeetingRecord(JNIEnv *env, jclass jcls,
                                                               jint channelid,
                                                               jobject screensList);
//获取当前的网络状态
JNIEXPORT jobject
JNICALL Java_org_suirui_srpaas_jni_JniNative_SRGetNetWorkStatus(JNIEnv *env, jclass jcls);

//开启直播
JNIEXPORT jint
JNICALL Java_org_suirui_srpaas_jni_JniNative_StartMeetingLive(JNIEnv *env, jclass jcls,
                                                              jobject onliveInfo,
                                                              jint channelid,
                                                              jobject screensList);

//停止直播
JNIEXPORT jint
JNICALL Java_org_suirui_srpaas_jni_JniNative_StopMeetingLive(JNIEnv *env, jclass jcls,
                                                             jint channelid,
                                                             jobject screensList);

//修改直播的参数
JNIEXPORT jint
JNICALL Java_org_suirui_srpaas_jni_JniNative_ChangeLiveSetting(JNIEnv *env, jclass jcls,
                                                               jobject onliveInfo);

//聊天发送消息
JNIEXPORT jint
JNICALL Java_org_suirui_srpaas_jni_JniNative_sendConfMessage(JNIEnv *env, jclass jcls,
                                                             jobject termIdList, jstring message);
void file_write_log(const char *format, ...);
JNIEnv *getJNIEnv(int *needsDetach);
//void detachThread(int *needsDetach);

/***********************回调***********************************************************************************/
//加入会议回调
void OnRspJoinConfCallBack_JNI(const bool isok, const SRConferenceAbnormal &error,
                               const int stermid);


//退出会议回调
void OnExitConfCallBack_JNI(const char *exit_reason);
//新终端加入会议
void onNewTermJoinCallBack_JNI(const TermInfo &join_info);
//终端离开会议
void OnTermLeaveCallBack_JNI(const int leave_stermid, const SRConferenceAbnormal &leave_reason);
//收到流回调
void OnRenderFrameCallBack_JNI(int stermid, int flag,
                               VideoFrame &frame);

//参会人列表回调
void OnRspConfTermListCallBack_JNI(const bool isOk, const SRConferenceAbnormal &error,
                                   const int master_id,
                                   const int duo_term_id,
                                   std::deque <TermInfo> termInfos);
//请求客服端发送视频流(selectvideo触发)
void OnStartSendVideoCallBack_JNI(const int video_size);

// 请求客户端关闭视频流
void OnStopSendVideoCallBack_JNI();
//请求开启共享 回调
void onRspSendDualVideoCallBack_JNI(const bool isOk, const SRConferenceAbnormal &error);
//其他终端收到有人共享的回调
void OnRecvDualVideoOpenCallBack_JNI(const int dualvideo_send_stermid);
//其他终端结束共享的回调
void OnRecvDualVideoCloseCallBack_JNI(const int dualvideo_close_stermid);
//其他终端暂停共享(已处理)
void OnRecvDualVideoPauseCallBack_JNI(const int dualvideo_pause_stermid);
//其他终端恢复共享
void OnRecvDualVideoResumeCallBack_JNI(const int dualvideo_resume_stermid);
//共享人收到其他终端申请共享
void OnReqAssistVideoProxyCallBack_JNI(const int who_want_send_dualvideo_stermid);
//参会人标注回调
void OnScreenDrawLabelCallBack_JNI(SRScreenLableAttr *attr);
void OnScreenClearLabelCallBack_JNI(const int cleard_stermid);
//打开相机回调
void onOpenCameraCallBack_JNI(const int open_stermid);

//关闭相机回调
void onCloseCameraCallBack_JNI(const int close_stermid);

//静音
void onTermAudioRecMuteCallBack_JNI(const int mute_stermid);

//取消静音
void onTermAudioRecUnMuteCallBack_JNI(const int cancel_stermid);

//全部静音/取消全部静音
void onMuteAudioAllTermNotifyCallBack_JNI(const bool ismute);

//主持人结束会议
void OnIndChairEndConfCallBack_JNI(const int chair_stermid,
                                   const char *chair_name);

//某个终端举手回调
void OnTermHandUpCallBack_JNI(const int handup_stermid,
                              const bool is_handup);

//新主持人收到回调
void OnMasterTransferCallBack_JNI(const int chair_stermid);

//主持人指定会议室内其它人看某一个客户端的视频回调
void onLockOrUnLockVideoCallBack_JNI(const int lock_stermid, const bool islock);

//主持人结束共享回调
void OnIndChairEndDataShareCallBack_JNI(const int chair_stermid,
                                        const char *chair_name);

//修改终端的名称
void OnTermChangeNameCallBack_JNI(const int change_stermid, const char *term_name);

//语音激励
void OnActiveVoiceCallBack_JNI(std::deque <SRVoiceActiveInfo> voice_acives);

//接收数据统计信息回调
void onRecvStreamInfoStatsCallBack_JNI(const RecvStreamInfo &stats);

//发送数据统计信息回调
void onSendStreamInfoStatsCallBack_JNI(const SendStreamInfo &stats);

//服务器返回错误码
void onServerErrorCallBack_JNI(SR_ERROR_CODE_TYPE err);

//检测其他终端的状态回调
void OnOtherTermRunningStatusCallBack_JNI(const int stautsTermid,
                                          const int staClass, const int staSubCls,
                                          const std::string staStr);

//主持人设置强制静音其他参会人收到的回调
void OnConfForceMuteCallBack_JNI(const bool isforcemute);

//网络状态改变回调
void OnNetwrokNotify_JNI(int status);

//获取会议信息的回调
void OnRspConfStatusCallBack_JNI(const bool isok, ConfStatus &confstatus,
                                 const SRConferenceAbnormal &error);

//新加入的终端可能会出收到该消息，与GetTermList类似
void OnAllMPInfoCallBack_JNI(std::list <SRMediaPInfo> &mpis);

//channelid 对应的那个mp
//screenid 混屏布局对应屏幕id
//screentype 屏幕类型，1-会议屏幕/网关(标准终端)屏幕、2-终端屏幕、3-双流屏幕
//addordel 屏幕的是否增加删除 1:add  2:del
void OnMPScreenInfoCallback_JNI(const int channelid, const int screenid,
                                const int screentype, const int addordel);

/**
* 终端收主持人开启会议录制停止会议录制
* @param [in] recstate
*          0-停止录制,1-开始录制
*/
void OnIndTerCRSRecStateCallBack_JNI(const int recstate, const SRConferenceAbnormal &error);

//参会人列表更新(增加)
void OnUpdateAddPaticipantsCallBack_JNI(std::list <TermInfo> &paticipants);

//参会人列表更新(删除)
void OnUpdateDelPaticipantsCallBack_JNI(std::list <TermInfo> &paticipants);

//投频终端的回调
void OnIndTerSpecialtypeTransferCallBack_JNI(const int nspclterid, const int nspcltype);

//直播状态的回调
void OnIndTerCRSLiveStateCallBack_JNI(const int livestate, const std::string &liveplayurl,
                                      const SRConferenceAbnormal &error);

//直播设置变更回调
void OnIndLiveSettingChangedCallBack_JNI(const LiveSetting &new_setting);

//聊天中 接收到的信息
void OnRecvIMMessageCallBack_JNI(const int from_stermid, const std::string &message);

//网络异常后，又重新链接成功
void onServerOkCallBack_JNI(const SR_OK_CODE_TYPE ok);
#ifdef __cplusplus
}
#endif
#endif
