#include "srengine_api.h"
#include "typedefs.h"
#ifdef __cplusplus
extern "C" {
#endif

////************************************
//// 函数名称:    onRegisterNotify
//// 函数说明:    注册服务器状态
//// 作    者:    licui
////************************************
//int onRegisterNotify(int status);

/*****回调start**************************************************************************************/

/**
 * 初始化mcu回调
 */
void OnInitMCStatusCallBack(const bool isOk);
/**
 * 注销mcu初始化回调
 */
void OnUnInitMCStatusCallBack(const bool isOk);

/**
 * 入会状态回调
 *
 * isOk 成功:true 失败:false fail_reson:失败原因
 *
 *  sTermId 终端id
 */
void OnRspJoinConfCallBack(const bool isOk, const char *fail_reason,
		const int sTermId);

/**
 * 退出会议回调
 */
void OnExitConfCallBack(const char *exit_reason);
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
		const char *fail_reason);
/**
 * 开启发送双流ACK回调
 * *isOk 成功 true  失败false
 *  conf_id 会议id
 * term_id 终端id
 * fail_reason 失败原因
 */
void onRspSendDualVideoCallBack(const bool isOk, const UINT64 conf_id,
		const int term_id, const char *fail_reason);
/**
 * 接收端收到接收双流  回调
 * conf_id 会议id
 * term_id 终端id
 * send_id 发送双流终端
 */
void OnRecvDualVideoOpenCallBack(const UINT64 conf_id, const int term_id,
		const int send_id);
/**
 * 接收端收到关闭双流 回调
 * conf_id 会议id
 * term_id 终端id
 */
void OnRecvDualVideoCloseCallBack(const UINT64 conf_id, const int term_id);
/**
 * 请求客户端发送视频流,由其它客户端selectvideo触发
 * conf_id 会议id
 * term_id 终端id
 */
void onStartSendVideoNotifyCallBack(const UINT64 conf_id, const int term_id,
		const int video_size);
/**
 * 请求客户端关闭视频流回调
 * * conf_id 会议id
 * term_id 终端id
 */
void onStopSendVideoNotifyCallBack(const UINT64 conf_id, const int term_id);

/**
 * 新的客户端加入会议回调
 * conf_id 会议id
 * term_id 终端id
 */
void onNewTermJoinCallBack(const UINT64 conf_id, const int term_id,
		const TermInfo *joinInfo);

/**
 * 其它客户端退出会议回调
 */
void onTermLeaveCallBack(const UINT64 conf_id, const int term_id,
		const char *leave_reason, const int leaveterid);
/**
 * 其它客户端举手或放手回调
 * conf_id 会议id
 * term_id 终端id
 * handupterid
 * isHandUp
 */
void onTermHandUpCallBack(const UINT64 conf_id, const int term_id,
		const int handupterid, const bool isHandUp);
/**
 * 主持人身份切换回调
 */
void onMasterTransferCallBack(const UINT64 conf_id, const int term_id,
		const int new_id);
/**
 * 其它客户端禁音回调
 */
void onTermAudioRecMuteCallBack(const UINT64 conf_id, const int term_id,
		const int sponsorid, const int muteterid);

/**
 * 其它客户端取消禁音回调
 */
void onTermAudioRecUnMuteCallBack(const UINT64 conf_id, const int term_id,
		const int sponsorid, const int cancelterid);

/**
 * 其它客户端修改名称回调
 */
void onTermChangeNameCallBack(const UINT64 conf_id, const int term_id,
		const int changeterid, const char *term_name);

/**
 * 新终端进入时,告知双流进行的指示回调
 * dual_id 开启双流的客户端id
 */
void onDualVideoOnCallBack(const UINT64 conf_id, const int term_id,
		const int dual_id);
/**
 *
 */
void onLockVideoCallBack(const UINT64 conf_id, const int term_id,
		const int unlock_id);

void onUnLockVideoCallBack(const UINT64 conf_id, const int term_id,
		const int unlock_id);

void onOpenCameraCallBack(const UINT64 conf_id, const int term_id,
		const int open_id);
void onCloseCameraCallBack(const UINT64 conf_id, const int term_id,
		const int close_id);
/**
 *  openclose: true:open  false:close
 */
void onOtherTerChangeHighVideoStsCallBack(const UINT64 conf_id,
		const int term_id, const int chang_id, const bool openclose);
void onChairEndConfCallBack(const UINT64 confid, const int termid,
		const int chairid, const char* chairname);
void onRenderCallBackCallBack(int id, int flag, unsigned char *ybuf,
		unsigned char *ubuf, unsigned char *vbuf, int width, int height);
void onStackConnErrCallBack();
void onRelayServerCrashCallBack(int error);

void onReqDualVideoProxyCallBack(const UINT64 confid, const int termid,
		const int avtermid); //共享端收到其它终端的共享申请

void onActiveVoiceCallBack(SRVoiceActiveInfo *voice_acive, int num);
void onMuteAudioAllTermNotifyCallBack(const UINT64 confid, const int termid,
		const bool is_mute);

void OnScreenDrawLabelCallBack(UINT64 conf_id, int term_id,
		ScreenLableAttr attr);
void OnScreenClearLabelCallBack(UINT64 conf_id, int term_id, int cleardid);
void OnRecvConfMessageCallBack(UINT64 conf_id, int from_id, char *message,
		int message_len);
void OnStackConnErrorCallBack(StackConnErrType type);
void SREngineRunningStatusNotifyCallBack(const UINT64 confid, const int termid,
		const int stautsTermid, const int staClass, const int staSubCls,
		const char* staStr);

/*****回调结束**************************************************************************************/

#ifdef __cplusplus
}
#endif
class DataProcess {
public:
	//回调
	DataProcess();
	virtual ~DataProcess(void);

public:
	/************************************************************************************************
	 函数名称:本函数需要客户端在启动时调用（应用程序启动）
	 输入参数：
	 callback	回调函数
	 debug_en	启用DEBUG SDK    true: 启用log文件输出  false: 反之
	 返回值: 0 成功  非0 失败
	 ************************************************************************************************/
	int initSdk(const bool debug_en, const char *pLogPath);

	/************************************************************************************************
	 函数功能：函数功能:本函数需要客户端退出时调用
	 输入参数：
	 返回值: 0 成功  非0 失败
	 *************************************************************************************************/
	int UnInitSDK();
	/************************************************************************************************
	 函数功能：初始化MC
	 输入参数：const char	*mc_ip  mc地址  const  int	mc_port 端口号    listenport: 本地监听(填0)
	 返回值: 0 成功  非0 失败
	 *************************************************************************************************/
	int requestInitMC(char *relaymcAdreess, int relaymc_nsize, int termUId,
			UINT64 ipandports);

	int requestInitMCArray(const char **relaymc_info, int relaymc_nsize,
			int termUId, UINT64 ipandports);
	/**
	 * 注销mc初始化
	 */
	int requestUnInitMC();
	/**
	 *加入会议
	 */
	int requestJoinConference(UINT64 conf_id, char *password, char *term_name,
			int term_id, void* local_wnd, bool isMuted, bool isCameraOn);
	/**
	 * 退出会议
	 */
	int requestExitConference(UINT64 conf_id, int term_id, char *exit_reason,
			bool isEnd);
	/**
	 * 获取会议中的终端信息,客户端需要根据终端信息开启接受视频(需要等待ACK)
	 */
	int requestTerminalmList();
	/**
	 * 函数功能:  开始发送双流(需要等ACK)
	 */
	int requestStartSendDualVideo(void* wnd);
	/**
	 * 函数功能:  停止发送双流(不需要等ACK)
	 */
	int requestStopSendDualVideo();

	/**
	 * 打开本地相机
	 */
	int SREngineOpenCamera();
	int SREngineCloseCamera();
	/************************************************************************************************
	 函数功能:  选看远端视频
	 输入参数： mul_stream:选看视频id和窗口
	 返回值: 0 成功  非0 失败
	 *************************************************************************************************/
	int requestSelectRemoteVideo(RVIDEO_PARAM *param, int size);
	/************************************************************************************************
	 函数功能:  本地终端举手(不需要等ACK)
	 输入参数： hand_up 举手:true 放手:false
	 返回值: 0 成功  非0 失败
	 *************************************************************************************************/
	int requestHandUp(const bool hand_up);
	/************************************************************************************************
	 函数功能:  主持人将其他终端踢出会议命令,只有主持人可以发出去
	 输入参数： drop_id  被踢id
	 返回值: 0 成功  非0 失败
	 *************************************************************************************************/
	int requestRemoveTerminal(const int terminalId);
	/************************************************************************************************
	 函数功能:  主持人转让主持人身份,只有主持人可以发出去(需要ACK)
	 输入参数：masterId  新的主持人id
	 返回值: 0 成功  非0 失败
	 *************************************************************************************************/
	int setMasterId(const int masterId);
	/**************************************
	 入参数：函数功能：4.1.38	获取下行网络估计带宽
	 输      media_type: 0-audio, 1-video low, 2-video-high
	 ************/
	int getDownLoadBitrate(int stream_id, int media_type);
	//打开本地相机
	int openOrCloseCamera(bool isOpen);
	//设置静音
	int setMute(const int mute_term_id, bool isMute);

	//:SREngineInVideoRawStream(int, int, int, char**, int*)
	int SREngineInVideoRawStream(int videoStreamType, int type, int width,
			int height, char *buf[3], int buf_size[3]);
	int SREngineSetRelayServer(char *address);

	int SREngineMuteAudio(const int mute_term_id);
	int SREngineUnMuteAudio(const int unmute_term_id);
	int SREngineRspSendDualVideoProxy(const UINT64 confid, const int termid,
			const int avterid, const bool isok, const char* rejectreason);
	void SRRegisterGetAudioActiveInfo();
	int SREngineMuteAudioAllTerm(const UINT64 confid, const int termid,
			const bool ismute);
	//获取第三方音频库版本
	char* SREngineGetExtAudioProcessVersion();
	char* SREngineGetExtAudioProcessId();
	int SREngineRegisterExtAudioProcessLicence(const char *licence, int len);

	int SREngineSetSpeakerMode(int mode);
	int SREngineRunningStatusNotify(const UINT64 confid, const int termid,
			const int sta_class, const int sta_sub_class,
			const char *status_str);

	int SREngineNetworkChanged();
	int changeName(const char *new_name);
	int lockOrUnLockVideo(const UINT64  confi_id, const int term_id, const int lock_id,bool isLock );

private:
	SRECALLBACK *pCallBack;
};

extern DataProcess *g_dataProcess;

//#endif
