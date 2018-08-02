#include <jni.h>
#ifndef _Included_Conference_jni
#define _Included_Conference_jni
#include <signal.h>
#include "typedefs.h"
#include "srengine_api.h"
#ifdef __cplusplus
extern "C" {
#endif
void android_sigaction(int signal, siginfo_t *info, void *reserved);
jstring stoJstring(JNIEnv* env, const char* pat);
JNIEXPORT jint JNICALL Java_org_suirui_srpaas_jni_JniNative_changeName(
		JNIEnv *env, jclass jcls,  jstring change_name);
JNIEXPORT jobject JNICALL Java_org_suirui_srpaas_jni_JniNative_allocNativeBuffer(
		JNIEnv *env, jclass jcls, jlong size);
JNIEXPORT void JNICALL Java_org_suirui_srpaas_jni_JniNative_freeNativeBuffer(JNIEnv *env,
		jclass jcls,jobject globalRef);

JNIEXPORT jint JNICALL Java_org_suirui_srpaas_jni_JniNative_InitSDK(JNIEnv *env,
		jclass jcls, jboolean debug_en, jstring pLogPath);
JNIEXPORT jint JNICALL Java_org_suirui_srpaas_jni_JniNative_UnInitSDK(
		JNIEnv *env, jclass jcls);

JNIEXPORT jint JNICALL Java_org_suirui_srpaas_jni_JniNative_requestInitMC(
		JNIEnv *env, jclass jcls, jstring mc_adress, jint relaymc_nsize,
		jint termUId, jlong mcuport);

JNIEXPORT jint JNICALL Java_org_suirui_srpaas_jni_JniNative_requestInitMCArray(
		JNIEnv *env, jclass jcls, jobject mcAdressList, jint relaymc_nsize,
		jint termUId, jlong mcuport);

JNIEXPORT jint JNICALL Java_org_suirui_srpaas_jni_JniNative_requestUnInitMC(
		JNIEnv *env, jclass jcls);
JNIEXPORT jint JNICALL Java_org_suirui_srpaas_jni_JniNative_requestJoinConference(
		JNIEnv *env, jclass jcls, jlong conf_id, jstring password,
		jstring term_name, jint term_id, jobject local_wnd, jboolean isMuted,
		jboolean isCameraOn);

JNIEXPORT jint JNICALL Java_org_suirui_srpaas_jni_JniNative_requestExitConference(
		JNIEnv *env, jclass jcls, jlong conf_id, jint term_id,
		jstring exit_reason, jboolean isEnd);
JNIEXPORT jint JNICALL Java_org_suirui_srpaas_jni_JniNative_requestTerminalmList(
		JNIEnv *env, jclass jcls);

JNIEXPORT jint JNICALL Java_org_suirui_srpaas_jni_JniNative_requestStartSendDualVideo(
		JNIEnv *env, jclass jcls, jobject wnd_);
JNIEXPORT jint JNICALL Java_org_suirui_srpaas_jni_JniNative_requestStopSendDualVideo(
		JNIEnv *env, jclass jcls);
JNIEXPORT jint JNICALL Java_org_suirui_srpaas_jni_JniNative_openCamera(
		JNIEnv *env, jclass jcls);
JNIEXPORT jint JNICALL Java_org_suirui_srpaas_jni_JniNative_closeCamera(
		JNIEnv *env, jclass jcls);
JNIEXPORT jint JNICALL Java_org_suirui_srpaas_jni_JniNative_requestSelectRemoteVideo(
		JNIEnv *env, jclass jcls, jobject videoparamList);

JNIEXPORT jint JNICALL Java_org_suirui_srpaas_jni_JniNative_requestHandUp(
		JNIEnv *env, jclass jcls, jboolean handUp);

JNIEXPORT jint JNICALL Java_org_suirui_srpaas_jni_JniNative_requestRemoveTerminal(
		JNIEnv *env, jclass jcls, jint drop_id);
JNIEXPORT jint JNICALL Java_org_suirui_srpaas_jni_JniNative_setMasterId(
		JNIEnv *env, jclass jcls, jint masterId);

JNIEXPORT jint JNICALL Java_org_suirui_srpaas_jni_JniNative_openOrCloseCamera(
		JNIEnv *env, jclass jcls, jboolean isOpen);

JNIEXPORT jint JNICALL Java_org_suirui_srpaas_jni_JniNative_setMute(JNIEnv *env,
		jclass jcls, jboolean isMute, jint mute_term_id);
JNIEXPORT jint JNICALL Java_org_suirui_srpaas_jni_JniNative_SREngineMuteAudio(
		JNIEnv *env, jclass jcls, jint term_id);
JNIEXPORT jint JNICALL Java_org_suirui_srpaas_jni_JniNative_SREngineUnMuteAudio(
		JNIEnv *env, jclass jcls, jint unterm_id);

JNIEXPORT jstring JNICALL Java_org_suirui_srpaas_jni_JniNative_getExtAudioProcessVersion(
		JNIEnv *env, jclass jcls);
JNIEXPORT jstring JNICALL Java_org_suirui_srpaas_jni_JniNative_getExtAudioProcessId(
		JNIEnv *env, jclass jcls);
JNIEXPORT jint JNICALL Java_org_suirui_srpaas_jni_registerExtAudioProcessLicence(
		JNIEnv *env, jclass jcls, jstring licence, jint len);
/**************************************
 入参数：函数功能：4.1.38	获取下行网络估计带宽
 输      media_type: 0-audio, 1-video low, 2-video-high
 ************/
JNIEXPORT jint JNICALL Java_org_suirui_srpaas_jni_JniNative_getDownLoadBitrate(
		JNIEnv *env, jclass jcls, jint stream_id, jint media_type);

JNIEXPORT jint JNICALL Java_org_suirui_srpaas_jni_JniNative_SREngineInVideoRawStreamRGB(
		JNIEnv *env, jclass jcls, jint videoStreamType, jint type, jint width,
		jint height, jintArray rgbArray, jint size);
JNIEXPORT jint JNICALL Java_org_suirui_srpaas_jni_JniNative_SREngineInVideoRawStreamYUV(
		JNIEnv *env, jclass jcls, jint videoStreamType, jint type, jint width,
		jint height, jbyteArray buffer, jint size);

JNIEXPORT jint JNICALL Java_org_suirui_srpaas_jni_JniNative_RequestInVideoRawStream(
		JNIEnv *env, jclass jcls, jint type, jint width, jint height);

JNIEXPORT jint JNICALL Java_org_suirui_srpaas_jni_JniNative_SREngineSetRelayServer(
		JNIEnv *env, jclass jcls, jstring address);
JNIEXPORT jint JNICALL Java_org_suirui_srpaas_jni_JniNative_resposeSendDualVideoProxy(
		JNIEnv *env, jclass jcls, jlong conf_id, jint termid, jint avterid,
		jboolean isok, jstring rejectreason);

JNIEXPORT jint JNICALL Java_org_suirui_srpaas_jni_JniNative_getAudioActiveInf(
		JNIEnv *env, jclass jcls);

JNIEXPORT jint JNICALL Java_org_suirui_srpaas_jni_JniNative_MuteAudioAllTerm(
		JNIEnv *env, jclass jcls, jlong confid, jint termid, jboolean ismute);

JNIEXPORT jint JNICALL Java_org_suirui_srpaas_jni_JniNative_SREngineSetSpeakerMode(
		JNIEnv *env, jclass jcls, jint mode);
JNIEXPORT jint JNICALL Java_org_suirui_srpaas_jni_JniNative_SREngineRunningStatusNotify(
		JNIEnv *env, jclass jcls, jlong confid, jint termid, jint sta_class,
		jint sta_sub_class, jstring status_str);

JNIEXPORT jint JNICALL Java_org_suirui_srpaas_jni_JniNative_SREngineNetworkChanged(
		JNIEnv *env, jclass jcls);

JNIEXPORT jint JNICALL Java_org_suirui_srpaas_jni_JniNative_lockOrUnLockVideo(JNIEnv *env, jclass jcls,jlong  confi_id, jint term_id, jint lock_id,jboolean isLock );

/***********************回调***********************************************************************************/
void onTermChangeNameCallBack_JNI(const UINT64 conf_id, const int term_id,
								  const int changeterid, const char *term_name);
void onMuteAudioAllTermNotifyCallBack_JNI(const UINT64 conf_id,
		const int term_id, const bool is_mute);
void onInitMCStatusCallBack_JNI(bool status);
void OnUnInitMCStatusCallBack_JNI(bool status);
void OnRspJoinConfCallBack_JNI(const bool isOk, const char *fail_reason,
		const int sTermId);
void OnExitConfCallBack_JNI(const char *exit_reason);
void onRspConfTermListCallBack_JNI(const bool isOk, const UINT64 conf_id,
		const int term_id, const int master_id, const int duo_term_id,
		const int totalnums, TermInfo **termInfo, const int nSize,
		const char *fail_reason);
void onRspSendDualVideoCallBack_JNI(const bool isOk, const UINT64 conf_id,
		const int term_id, const char *fail_reason);
void OnRecvDualVideoOpenCallBack_JNI(const UINT64 conf_id, const int term_id,
		const int send_id);
void OnRecvDualVideoCloseCallBack_JNI(const UINT64 conf_id, const int term_id);
void onRenderCallBackCallBack_JNI(int id, int flag, unsigned char *ybuf,
		unsigned char *ubuf, unsigned char *vbuf, int width, int height);

//新终端加入回调
void onNewTermJoinCallBack_JNI(const UINT64 conf_id, const int term_id,
		const TermInfo *joinInfo);

//其他终端退出会议
void onTermLeaveCallBack_JNI(const UINT64 conf_id, const int term_id,
		const char *leave_reason, const int leaveterid);

//新终端进入时,告知双流进行的指示
void onDualVideoOnCallBack_JNI(const UINT64 conf_id, const int term_id,
		const int dual_id);
//主持人退出会议
void onChairEndConfCallBack_JNI(const UINT64 confid, const int termid,
		const int chairid, const char* chairname);
/**
 * 其它客户端取消禁音回调
 */
void onTermAudioRecUnMuteCallBack_JNI(const UINT64 conf_id, const int term_id,
		const int sponsorid, const int cancelterid);
/**
 * 其它客户端禁音回调
 */
void onTermAudioRecMuteCallBack_JNI(const UINT64 conf_id, const int term_id,
		const int sponsorid, const int muteterid);
/**
 * 主持人身份切换回调
 */
void onMasterTransferCallBack_JNI(const UINT64 conf_id, const int term_id,
		const int new_id);
/**
 *设置焦点视频
 */
void onLockVideoCallBack_JNI(const UINT64 conf_id, const int term_id,
		const int unlock_id);
/**
 * 取消焦点视频
 */
void onUnLockVideoCallBack_JNI(const UINT64 conf_id, const int term_id,
		const int unlock_id);
/**
 * 举手
 */
void onTermHandUpCallBack_JNI(const UINT64 conf_id, const int term_id,
							  const int handupterid, const bool isHandUp);

void onReqDualVideoProxyCallBack_JNI(const UINT64 confid, const int termid,
		const int avtermid);
void onActiveVoiceCallBack_JNI(SRVoiceActiveInfo *voice_acive, int num);

void OnScreenDrawLabelCallBack_JNI(UINT64 conf_id, int term_id,
		ScreenLableAttr attr);
void OnScreenClearLabelCallBack_JNI(UINT64 conf_id, int term_id, int cleardid);
void OnRecvConfMessageCallBack_JNI(UINT64 conf_id, int from_id, char *message,
		int message_len);
void OnStackConnErrorCallBack_JNI(int type);
void SREngineRunningStatusNotifyCallBack_JNI(const UINT64 confid,
		const int termid, const int stautsTermid, const int staClass,
		const int staSubCls, const char* staStr);

void onOpenCameraCallBack_JNI(const UINT64 conf_id, const int term_id,
		const int open_id);
void onCloseCameraCallBack_JNI(const UINT64 conf_id, const int term_id,
		const int close_id);

#ifdef __cplusplus
}
#endif
#endif
