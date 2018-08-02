#include "DataProcess.h"
#include "Conference_jni.h"
#include "srengine_api.h"
#include "typedefs.h"
#include "jni.h"
#include <android/log.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include<iostream>
#include<sstream>
#include "Log.h"
#include <arpa/inet.h>
using namespace std;
SRECALLBACK *pCallBack = 0;

//typedef std::function<void (const bool)> fpi;

DataProcess::DataProcess() {
}

DataProcess::~DataProcess(void) {
}

//***********************主调start************************************/
//************************************
// 函数说明:    初始化SDK
// 作    者:    licui
//************************************
int DataProcess::initSdk(const bool debug_en, const char *pLogPath) {
	pCallBack = new SRECALLBACK();
//	fpi=OnInitMCStatusCallBack;
//	fpi(true);
	pCallBack->onInitMcSts = (SRE_OnInitMCStatus) OnInitMCStatusCallBack; //mcu初始化
	pCallBack->onUnInitMcSts = (SRE_OnUnInitMCStatus) OnUnInitMCStatusCallBack; //注销mcu初始化回调
	pCallBack->onRspJoinConf = (SRE_OnRspJoinConf) OnRspJoinConfCallBack; //入会状态回调
	pCallBack->onExitConf = (SRE_OnExitConf) OnExitConfCallBack;
	pCallBack->onRspConfTermList =
			(SRE_OnRspConfTermList) onRspConfTermListCallBack; //获取会议中所有终端信息
	pCallBack->onRspSendDualVideo =
			(SRE_OnRspSendDualVideo) onRspSendDualVideoCallBack; //开启发送双流ACK
	pCallBack->onRecvDualVideoOpen =
			(SRE_OnRecvDualVideoOpen) OnRecvDualVideoOpenCallBack; //接收端收到接收双流  send_id:发送双流终端
	pCallBack->onRecvDualVideoClose =
			(SRE_OnRecvDualVideoClose) OnRecvDualVideoCloseCallBack; //接收端收到关闭双流
	pCallBack->onStartSendVideoNotify =
			(SRE_OnStartSendVideo) onStartSendVideoNotifyCallBack; //请求客户端发送视频流,由其它客户端selectvideo触发
	pCallBack->onStopSendVideoNotify =
			(SRE_OnStopSendVideo) onStopSendVideoNotifyCallBack; //请求客户端关闭视频流
	pCallBack->onNewTermJoin = (SRE_OnNewTermJoinConf) onNewTermJoinCallBack; //新的客户端加入会议
	pCallBack->onTermLeave = (SRE_OnTermLeave) onTermLeaveCallBack; //其它客户端退出会议
	pCallBack->onTermHandUp = (SRE_OnTermHandUp) onTermHandUpCallBack; //其它客户端举手或放手
	pCallBack->onMasterTransfer =
			(SRE_OnMasterTransfer) onMasterTransferCallBack; //主持人身份切换
	pCallBack->onTermAudioRecMute =
			(SRE_OnTermAudioRecMute) onTermAudioRecMuteCallBack; //其它客户端禁音
	pCallBack->onTermAudioRecUnMute =
			(SRE_OnTermAudioRecUnMute) onTermAudioRecUnMuteCallBack; //其它客户端取消禁音
	pCallBack->onTermChangeName =
			(SRE_OnTermChangeName) onTermChangeNameCallBack; //其它客户端修改名称
	pCallBack->onDualVideoOn = (SRE_OnDualVideoOn) onDualVideoOnCallBack; //新终端进入时,告知双流进行的指示
	pCallBack->onLockVideo = (SRE_OnLockVideo) onLockVideoCallBack;
	pCallBack->onUnLockVideo = (SRE_OnUnLockVideo) onUnLockVideoCallBack;
	pCallBack->onOpenCamera = (SRE_OnOpenCamera) onOpenCameraCallBack;
	pCallBack->onCloseCamera = (SRE_OnCloseCamera) onCloseCameraCallBack;
	pCallBack->onOtherTerChangeHighVideoSts =
			(SRE_OnOtherTerChangeHighVideoSts) onOtherTerChangeHighVideoStsCallBack;
	pCallBack->onChairEndConf = (SRE_OnIndChairEndConf) onChairEndConfCallBack;

	pCallBack->onRenderCallBack =
			(SRE_OnRenderCallback) onRenderCallBackCallBack;

	pCallBack->onStackConnErr = (SREG_OnStackConnError) onStackConnErrCallBack;

	pCallBack->onRelayServerCrash =
			(SREG_OnRelayServerCrash) onRelayServerCrashCallBack;

	pCallBack->onReqDualVideoProxy =
			(SRE_OnReqAssistVideoProxy) onReqDualVideoProxyCallBack;

	pCallBack->onMuteAudioAllTermNotify =
			(SRE_OnMuteAudioAllTermNotify) onMuteAudioAllTermNotifyCallBack;

	pCallBack->onScreenDrawLabel =
			(SRE_OnScreenDrawLabel) OnScreenDrawLabelCallBack;
	pCallBack->onScreenClearLabel =
			(SRE_OnScreenClearLabel) OnScreenClearLabelCallBack;
	pCallBack->onRecvMessage =
			(SRE_OnRecvConfMessage) OnRecvConfMessageCallBack;
	pCallBack->onStackConnErr =
			(SREG_OnStackConnError) OnStackConnErrorCallBack;
	pCallBack->onOtherTermRunningStatus =
			(SRE_OnOtherTermRunningStatus) SREngineRunningStatusNotifyCallBack;

///bool debug_en, char *pLogPath

//	char pLogPath[128];
	int intSdk = SREngine_Init(pCallBack, debug_en, pLogPath);
#if defined(LOG_JNI)
	Log("DataProcess:___intSdk_.....intSdk=%d",intSdk);
#endif
	return intSdk;
}
/**
 * 注销sdk初始化
 */
int DataProcess::UnInitSDK() {
	return SREngine_Uninit();
}
/************************************************************************************************
 函数功能：初始化MC
 输入参数：const char	*mc_ip  mc地址  const  int	mc_port 端口号    listenport: 本地监听(填0)
 返回值: 0 成功  非0 失败
 *************************************************************************************************/

int DataProcess::requestInitMC(char *relaymcAdreess, int relaymc_nsize,
		int termUId, UINT64 ipandports) {
#if defined(LOG_JNI)
	Log("DataProcess:requestInitMC.....___termUId:%d____ipandport:%llu",termUId,ipandports);
#endif
	char *prelayInfo[1];
	prelayInfo[0] = relaymcAdreess;
	return SREngine_InitMC((const char **) prelayInfo, 1, termUId, ipandports);
}

int DataProcess::requestInitMCArray(const char **relaymc_info,
		int relaymc_nsize, int termUId, UINT64 ipandports) {
#if defined(LOG_JNI)
	Log("DataProcess:requestInitMCArray....._");
#endif
	return SREngine_InitMC(relaymc_info, relaymc_nsize, termUId, ipandports);
}
/**
 * 注销mc初始化
 */
int DataProcess::requestUnInitMC() {
#if defined(LOG_JNI)
	Log("DataProcess:requestUnInitMC...");
#endif
	return SREngine_UnInitMC();
}
/**
 * 加入会议
 */
int DataProcess::requestJoinConference(UINT64 conf_id, char *password,
		char *term_name, int term_id, void* local_wnd, bool isMuted,
		bool isCameraOn) {
#if defined(LOG_JNI)
	Log("DataProcess:requestJoinConference.....___conf_id:%llu_______term_id:%d",conf_id,term_id);
#endif

	return SREngine_ReqJoinConf(conf_id, password, term_name, term_id,
			local_wnd, isMuted, isCameraOn);
}
/**
 * 退出会议
 */
int DataProcess::requestExitConference(UINT64 conf_id, int term_id,
		char *exit_reason, bool isEnd) {
#if defined(LOG_JNI)
	Log("DataProcess:requestExitConference.....___conf_id:%llu____term_id___%d____",conf_id,term_id);
#endif
	if (isEnd) { //主持人结束会议
		SREngine_ChairEndConf(conf_id, term_id);
		return SREngine_ExitConf(conf_id, term_id, exit_reason);
	} else {
		return SREngine_ExitConf(conf_id, term_id, exit_reason);
	}
}

/**
 * 获取会议中的终端信息,客户端需要根据终端信息开启接受视频(需要等待ACK)
 */
int DataProcess::requestTerminalmList() {
#if defined(LOG_JNI)
	Log("DataProcess:requestTerminalmList......");
#endif
	return SREngine_ReqConfTermList();
}

/**
 * 函数功能:  开始发送双流(需要等ACK)
 */
int DataProcess::requestStartSendDualVideo(void* wnd) {
#if defined(LOG_JNI)
	Log("DataProcess:requestStartSendDualVideo......");
#endif
	return SREngine_StartSendDualVideo(wnd);
}
/**
 * 函数功能:  停止发送双流(不需要等ACK)
 */
int DataProcess::requestStopSendDualVideo() {
#if defined(LOG_JNI)
	Log("DataProcess:requestStopSendDualVideo......");
#endif
	return SREngine_StopSendDualVideo();
}

int DataProcess::SREngineOpenCamera() {
#if defined(LOG_JNI)
	Log("DataProcess:SREngineOpenCamera......");
#endif
	return SREngine_OpenCamera();
}

/************************************************************************************************
 函数功能:  关闭本地摄像头指示(不需要等ack)
 输入参数： conf_id  会议ID   term_id 终端id(终端注册时的id)
 返回值: 0 成功  非0 失败
 *************************************************************************************************/
int DataProcess::SREngineCloseCamera() {
	return SREngine_CloseCamera();

}
/************************************************************************************************
 函数功能:  选看远端视频
 输入参数： term_id
 size（1,2,3,）大流小流
 addordel //1表示add,2表示del
 返回值: 0 成功  非0 失败
 *************************************************************************************************/
int DataProcess::requestSelectRemoteVideo(RVIDEO_PARAM *param, int size) {
#if defined(LOG_JNI)
	Log("DataProcess:requestSelectRemoteVideo......size:%d....param.term_id:%d...param.video_type:%d",size,param->term_id,param->video_type);
#endif
	return SREngine_SelectVideo(param, size);
}

/************************************************************************************************
 函数功能:  本地终端举手(不需要等ACK)
 输入参数： hand_up 举手:true 放手:false
 返回值: 0 成功  非0 失败
 *************************************************************************************************/
int DataProcess::requestHandUp(const bool hand_up) {
	return SREngine_HandUp(hand_up);
}

/************************************************************************************************
 函数功能:  主持人将其他终端踢出会议命令,只有主持人可以发出去
 输入参数： drop_id  被踢id
 返回值: 0 成功  非0 失败
 *************************************************************************************************/
int DataProcess::requestRemoveTerminal(const int terminalId) {
	return SREngine_DropTerm(terminalId);
}

/************************************************************************************************
 函数功能:  主持人转让主持人身份,只有主持人可以发出去(需要ACK)
 输入参数：masterId  新的主持人id
 返回值: 0 成功  非0 失败
 *************************************************************************************************/
int DataProcess::setMasterId(const int masterId) {
	return SREngine_MasterTransfer(masterId);
}

int DataProcess::getDownLoadBitrate(int stream_id, int media_type) {
	return SREngine_GetDownLoadBitrate(stream_id, media_type);
}
/**
 * 打开本地相机
 */
int DataProcess::openOrCloseCamera(bool isOpen) {
	if (isOpen) { //打开
		return SREngine_OpenCamera();
	} else { //关闭
		return SREngine_CloseCamera();
	}

}

//设置静音
int DataProcess::setMute(const int mute_term_id, bool isMute) {
	if (isMute) { //静音
		return SREngine_AudioRecMute(mute_term_id);
	} else { //取消静音
		return SREngine_AudioRecUnMute(mute_term_id);
	}

}

//char *buf[3], int buf_size[3]
int DataProcess::SREngineInVideoRawStream(int videoStreamType, int type,
		int width, int height, char *buf[3], int buf_size[3]) {
	SRVideoStreamType streamType = (SRVideoStreamType) videoStreamType;
	SRVideoRawFormat enumType = (SRVideoRawFormat) type;
	return SREngine_InVideoRawStream(streamType, enumType, width, height, buf,
			buf_size);
}
int DataProcess::SREngineSetRelayServer(char *address) {
	return SREngine_SetRelayServer(address);

}
//静音
int DataProcess::SREngineMuteAudio(const int mute_term_id) {
	return SREngine_AudioRecMute(mute_term_id);
}
//取消静音
int DataProcess::SREngineUnMuteAudio(const int unmute_term_id) {
	return SREngine_AudioRecUnMute(unmute_term_id);
}

int DataProcess::SREngineRspSendDualVideoProxy(const UINT64 confid,
		const int termid, const int avterid, const bool isok,
		const char* rejectreason) {
	return SREngine_RspSendDualVideoProxy(confid, termid, avterid, isok,
			rejectreason);
}
//获取音频数量
void DataProcess::SRRegisterGetAudioActiveInfo() {
	ActiveVoiceCallBack cb = onActiveVoiceCallBack;
	SREngine_RegisterGetAudioActiveInfo(cb);
}

int DataProcess::SREngineMuteAudioAllTerm(const UINT64 confid, const int termid,
		const bool ismute) {
	return SREngine_MuteAudioAllTerm(confid, termid, ismute);
}

char* DataProcess::SREngineGetExtAudioProcessVersion() {
	return SREngine_GetExtAudioProcessVersion();
}
int DataProcess::SREngineNetworkChanged() {
	Log("DataProcess:SREngineNetworkChanged....");
	return SREngine_NetworkChanged();
}

int DataProcess::changeName(const char *new_name) {
	return SREngine_ChangeName(new_name);
}
int DataProcess::lockOrUnLockVideo(const UINT64  confi_id, const int term_id, const int lock_id,bool isLock ){
    if(isLock){
     return SREngine_LockVideo(confi_id,   term_id,  lock_id);
    }else{
     return SREngine_UnLockVideo(confi_id, term_id,   lock_id);
    }
}
char* DataProcess::SREngineGetExtAudioProcessId() {
	Log("DataProcess:SREngineGetExtAudioProcessId....");
	return SREngine_GetExtAudioProcessId();
}

int DataProcess::SREngineRegisterExtAudioProcessLicence(const char *licence,
		int len) {
	return SREngine_RegisterExtAudioProcessLicence(licence, len);
}
int DataProcess::SREngineSetSpeakerMode(int mode) {
	return SREngine_SetSpeakerMode(mode);

}
int DataProcess::SREngineRunningStatusNotify(const UINT64 confid,
		const int termid, const int sta_class, const int sta_sub_class,
		const char *status_str) {
	return SREngine_RunningStatusNotify(confid, termid, sta_class,
			sta_sub_class, status_str);

}

//***********************主调end************************************/
//***********************回调start************************************/
void SREngineRunningStatusNotifyCallBack(const UINT64 confid, const int termid,
		const int stautsTermid, const int staClass, const int staSubCls,
		const char* staStr) {
	SREngineRunningStatusNotifyCallBack_JNI(confid, termid, stautsTermid,
			staClass, staSubCls, staStr);
}
void OnStackConnErrorCallBack(StackConnErrType type) {
#if defined(LOG_JNI)
	Log("DataProcess:OnStackConnErrorCallBack....");
#endif
	OnStackConnErrorCallBack_JNI((int) type);
}
void OnScreenDrawLabelCallBack(UINT64 conf_id, int term_id,
		ScreenLableAttr attr) {
#if defined(LOG_JNI)
	Log("DataProcess:OnScreenDrawLabelCallBack....");
#endif
	OnScreenDrawLabelCallBack_JNI(conf_id, term_id, attr);
}
void OnScreenClearLabelCallBack(UINT64 conf_id, int term_id, int cleardid) {
#if defined(LOG_JNI)
	Log("DataProcess:OnScreenClearLabelCallBack....");
#endif
	OnScreenClearLabelCallBack_JNI(conf_id, term_id, cleardid);
}
void OnRecvConfMessageCallBack(UINT64 conf_id, int from_id, char *message,
		int message_len) {
#if defined(LOG_JNI)
	Log("DataProcess:OnRecvConfMessageCallBack....");
#endif
	OnRecvConfMessageCallBack_JNI(conf_id, from_id, message, message_len);
}

void onMuteAudioAllTermNotifyCallBack(const UINT64 confid, const int termid,
		const bool is_mute) {
#if defined(LOG_JNI)
	Log("DataProcess:onMuteAudioAllTermNotifyCallBack....");
#endif
	onMuteAudioAllTermNotifyCallBack_JNI(confid, termid, is_mute);
}
void onActiveVoiceCallBack(SRVoiceActiveInfo *voice_acive, int num) {
	if (num > 0)
		onActiveVoiceCallBack_JNI(voice_acive, num);

}
/**
 * 初始化mcu回调
 */

void OnInitMCStatusCallBack(const bool isOk) {
#if defined(LOG_JNI)
	Log("DataProcess:OnInitMCStatusCallBack.....___%d",isOk);
#endif
	onInitMCStatusCallBack_JNI(isOk);

}
/**
 * 注销mcu初始化回调
 */
void OnUnInitMCStatusCallBack(const bool isOk) {
#if defined(LOG_JNI)
	Log("DataProcess:OnUnInitMCStatusCallBack.....");
#endif
	OnUnInitMCStatusCallBack_JNI(isOk);
}
/**
 * 入会状态回调
 *
 * isOk 成功:true 失败:false fail_reson:失败原因
 *
 *  sTermId 终端id
 */
void OnRspJoinConfCallBack(const bool isOk, const char *fail_reason,
		const int sTermId) {
#if defined(LOG_JNI)
	Log("DataProcess:OnRspJoinConfCallBack.....___%d________%d",isOk,sTermId);
#endif
	OnRspJoinConfCallBack_JNI(isOk, fail_reason, sTermId);

}
/**
 * 退出会议回调
 */
void OnExitConfCallBack(const char *exit_reason) {
#if defined(LOG_JNI)
	Log("DataProcess:OnExitConfCallBack..");
#endif
	OnExitConfCallBack_JNI(exit_reason);
}
/**
 * 获取会议中所有终端信息回调
 *isOk 成功 true  失败false
 * UINT64 conf_id 会议id
 * term_id 终端id
 * master_id 主席id
 * duo_term_id
 * TermInfo **termInfo, //终端信息
 * nSize 终端信息结构大小
 * fail_reason 失败原因
 */
void onRspConfTermListCallBack(const bool isOk, const UINT64 conf_id,
		const int term_id, const int master_id, const int duo_term_id,
		const int totalnums, TermInfo **termInfo, const int nSize,
		const char *fail_reason) {
	if (fail_reason != NULL) {
#if defined(LOG_JNI)
		Log("DataProcess:onRspConfTermListCallBack.....____conf_id:%llu_____%d___%d___%d__",conf_id,term_id,master_id,duo_term_id);
#endif
	}

	onRspConfTermListCallBack_JNI(isOk, conf_id, term_id, master_id,
			duo_term_id, totalnums, termInfo, nSize, fail_reason);

}
/**
 * 开启发送双流ACK回调
 * *isOk 成功 true  失败false
 *  conf_id 会议id
 * term_id 终端id
 * fail_reason 失败原因
 */
void onRspSendDualVideoCallBack(const bool isOk, const UINT64 conf_id,
		const int term_id, const char *fail_reason) {

#if defined(LOG_JNI)
	if(fail_reason!=NULL) {
		Log("DataProcess:onRspSendDualVideoCallBack.....____%d_____conf_id:%llu___%d___",isOk,conf_id,term_id);
	}
#endif
	onRspSendDualVideoCallBack_JNI(isOk, conf_id, term_id, fail_reason);
}
/**
 * 接收端收到接收双流  回调
 * conf_id 会议id
 * term_id 终端id
 * send_id 发送双流终端
 */
void OnRecvDualVideoOpenCallBack(const UINT64 conf_id, const int term_id,
		const int send_id) {
#if defined(LOG_JNI)
	Log("DataProcess:OnRecvDualVideoOpenCallBack.....____conf_id:%llu_____%d___%d",conf_id,term_id,send_id);
#endif

	OnRecvDualVideoOpenCallBack_JNI(conf_id, term_id, send_id);
}
/**
 * 接收端收到关闭双流 回调
 * conf_id 会议id
 * term_id 终端id
 */
void OnRecvDualVideoCloseCallBack(const UINT64 conf_id, const int term_id) {
#if defined(LOG_JNI)
	Log("DataProcess:OnRecvDualVideoCloseCallBack.....____conf_id:%llu_____%d",conf_id,term_id);
#endif

	OnRecvDualVideoCloseCallBack_JNI(conf_id, term_id);

}

/**
 * 请求客户端发送视频流回调,由其它客户端selectvideo触发
 * conf_id 会议id
 * term_id 终端id
 */
void onStartSendVideoNotifyCallBack(const UINT64 conf_id, const int term_id,
		const int video_size) {
#if defined(LOG_JNI)
	Log("DataProcess:onStartSendVideoNotifyCallBack.....____conf_id:%llu_____%d_____%d",conf_id,term_id,video_size);
#endif
}
/**
 * 请求客户端关闭视频流回调
 * conf_id 会议id
 * term_id 终端id
 */
void onStopSendVideoNotifyCallBack(const UINT64 conf_id, const int term_id) {
#if defined(LOG_JNI)
	Log("DataProcess:onStopSendVideoNotifyCallBack.....____conf_id:%llu_____%d",conf_id,term_id);
#endif
}
/**
 * 新的客户端加入会议回调
 * conf_id 会议id
 * term_id 终端id
 */
void onNewTermJoinCallBack(const UINT64 conf_id, const int term_id,
		const TermInfo *joinInfo) {
#if defined(LOG_JNI)
	Log("DataProcess:onNewTermJoinCallBack.....____conf_id:%llu_____%d",conf_id,term_id);
#endif
	onNewTermJoinCallBack_JNI(conf_id, term_id, joinInfo);
}
/**
 * 其它客户端退出会议回调
 * conf_id 会议id
 * term_id 终端id
 */
void onTermLeaveCallBack(const UINT64 conf_id, const int term_id,
		const char *leave_reason, const int leaveterid) {
#if defined(LOG_JNI)
	if(leave_reason!=NULL) {
		Log("DataProcess:onTermLeaveCallBack.....____%d_____%d",conf_id,term_id);
	}
#endif
	onTermLeaveCallBack_JNI(conf_id, term_id, leave_reason, leaveterid);
}
/**
 * 其它客户端举手或放手回调
 * conf_id 会议id
 * term_id 终端id
 * handupterid
 * isHandUp
 */
void onTermHandUpCallBack(const UINT64 conf_id, const int term_id,
		const int handupterid, const bool isHandUp) {
#if defined(LOG_JNI)
	Log("DataProcess:onTermHandUpCallBack.....____conf_id:%llu_____%d",conf_id,term_id);
#endif
onTermHandUpCallBack_JNI(conf_id, term_id, handupterid,isHandUp);

}
/**
 * 主持人身份切换回调
 */
void onMasterTransferCallBack(const UINT64 conf_id, const int term_id,
		const int new_id) {
#if defined(LOG_JNI)
	Log("DataProcess:onMasterTransferCallBack.....____conf_id:%llu_____%d_____%d",conf_id,term_id,new_id);
#endif
	onMasterTransferCallBack_JNI(conf_id, term_id, new_id);
}
/**
 * 其它客户端禁音回调
 */
void onTermAudioRecMuteCallBack(const UINT64 conf_id, const int term_id,
		const int sponsorid, const int muteterid) {
#if defined(LOG_JNI)
	Log("DataProcess:onTermAudioRecMuteCallBack.....____conf_id:%llu_____%d",conf_id,term_id);
#endif

	onTermAudioRecMuteCallBack_JNI(conf_id, term_id, sponsorid, muteterid);

}
/**
 * 其它客户端取消禁音回调
 */
void onTermAudioRecUnMuteCallBack(const UINT64 conf_id, const int term_id,
		const int sponsorid, const int cancelterid) {
#if defined(LOG_JNI)
	Log("DataProcess:onTermAudioRecUnMuteCallBack.....____conf_id:%llu_____%d",conf_id,term_id);
#endif
	onTermAudioRecUnMuteCallBack_JNI(conf_id, term_id, sponsorid, cancelterid);
}
/**
 * 其它客户端修改名称回调
 */
void onTermChangeNameCallBack(const UINT64 conf_id, const int term_id,
		const int changeterid, const char *term_name) {
#if defined(LOG_JNI)
	if(term_name!=NULL) {
		Log("DataProcess:onTermChangeNameCallBack.....____conf_id:%llu_____%d____",conf_id,term_id);
	}
#endif
onTermChangeNameCallBack_JNI(conf_id,term_id,changeterid,term_name);

}
/**
 * 新终端进入时,告知双流进行的指示回调
 * dual_id 开启双流的客户端id
 */
void onDualVideoOnCallBack(const UINT64 conf_id, const int term_id,
		const int dual_id) {
#if defined(LOG_JNI)
	Log("DataProcess:onDualVideoOnCallBack.....____conf_id:%llu_____%d",conf_id,term_id);
#endif
	onDualVideoOnCallBack_JNI(conf_id, term_id, dual_id);
}
/**
 *设置焦点视频
 */
void onLockVideoCallBack(const UINT64 conf_id, const int term_id,
		const int unlock_id) {
#if defined(LOG_JNI)
	Log("DataProcess:onLockVideoCallBack.....____conf_id:%llu_____%d____unlock_id:%d",conf_id,term_id,unlock_id);
#endif
	onLockVideoCallBack_JNI(conf_id, term_id, unlock_id);
}
/**
 * 取消焦点视频回调
 */
void onUnLockVideoCallBack(const UINT64 conf_id, const int term_id,
		const int unlock_id) {
#if defined(LOG_JNI)
	Log("DataProcess:onUnLockVideoCallBack.....____conf_id:%llu_____%d____unlock_id:%d",conf_id,term_id,unlock_id);
#endif
	onUnLockVideoCallBack_JNI(conf_id, term_id, unlock_id);

}
void onOpenCameraCallBack(const UINT64 conf_id, const int term_id,
		const int open_id) {
#if defined(LOG_JNI)
	Log("DataProcess:onOpenCameraCallBack.....");
#endif
	onOpenCameraCallBack_JNI(conf_id, term_id, open_id);
}
void onCloseCameraCallBack(const UINT64 conf_id, const int term_id,
		const int close_id) {
#if defined(LOG_JNI)
	Log("DataProcess:onCloseCameraCallBack.....");
#endif
	onCloseCameraCallBack_JNI(conf_id, term_id, close_id);

}
/**
 *  openclose: true:open  false:close
 */
void onOtherTerChangeHighVideoStsCallBack(const UINT64 conf_id,
		const int term_id, const int chang_id, const bool openclose) {

}
/**
 * 主持人退出会议
 */
void onChairEndConfCallBack(const UINT64 confid, const int termid,
		const int chairid, const char* chairname) {
#if defined(LOG_JNI)
	Log("DataProcess:onChairEndConfCallBack----termid:%d.....chairid:%d....",termid,chairid);
#endif
	onChairEndConfCallBack_JNI(confid, termid, chairid, chairname);

}
void onStackConnErrCallBack() {

}
void onRelayServerCrashCallBack(int error) {
#if defined(LOG_JNI)
	Log("DataProcess:onRelayServerCrashCallBack----%d",error);
#endif

}

void onReqDualVideoProxyCallBack(const UINT64 conf_id, const int termid,
		const int avtermid) {
#if defined(LOG_JNI)
	Log("DataProcess:onReqDualVideoProxyCallBack");
#endif
	onReqDualVideoProxyCallBack_JNI(conf_id, termid, avtermid);

}

/**
 * 渲染
 */
void onRenderCallBackCallBack(int id, int flag, unsigned char *ybuf,
		unsigned char *ubuf, unsigned char *vbuf, int width, int height) {
	onRenderCallBackCallBack_JNI(id, flag, ybuf, ubuf, vbuf, width, height);
}
