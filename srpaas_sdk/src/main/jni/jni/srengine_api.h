#ifndef SRENGINE_API_H
#define SRENGINE_API_H

#ifdef SRENGINE_EXPORTS
#define SRENGINE_API __declspec(dllexport)
#else
#ifdef SRENGINE_IMPORTS
#define SRENGINE_API __declspec(dllimport)
#else 
#define SRENGINE_API extern
#endif
#endif

#ifndef WIN32
typedef  void*  HWND;
typedef unsigned long long UINT64;
typedef long long INT64;
#endif

#ifdef WIN32
#include <Windows.h> //For HWND defination
#endif
#include <stdlib.h>

/* error code define */
typedef enum {
	SRE_SUCCESS = 0,				/* success */
	SRE_FAILURE = -1,				/* failure */
	SRE_INGROUP_ERR = -2,			/* argument error*/
	SRE_STATUS_ERR = -3,			/* internal engine error*/
	SRE_FATAL_ERR = -4,				/* fatal error */
	SRE_NET_FAILURE = -5,			/*  net connect failure*/
	SRE_DOMAIN_FAILURE = -6,
}SRE_ERROR_CODE;


typedef enum _SRENGINE_EVENT_ID
{
	SRE_ACCEPT_CALL_EVENT = 1,
	SRE_SERVER_INIT_FAILED,
}SRENGINE_EVENT_ID;


#ifndef _NETWORK_TYPE_
#define _NETWORK_TYPE_
typedef enum _SRENGINE_NetworkType {
	NETWORK_TYPE_NONE,
	NETWORK_TYPE_WIFI,
	NETWORK_TYPE_2G,
	NETWORK_TYPE_3G_TD,
	NETWORK_TYPE_3G_WCDMA,
	NETWORK_TYPE_3G_CDMA2000,
	NETWORK_TYPE_4G_TDD,
	NETWORK_TYPE_4G_FDD
}_NetworkType;
#else
typedef _NetworkType _SRENGINE_NetworkType;
#endif

typedef struct _SRE_Picture{
	int w,h;
	unsigned char *planes[4];
	int strides[4];
}SRE_Picture;

typedef struct _SRE_NetAdaptInfo
{
	char		adapt_name[64];
	char		mac_addr[64];
	char		local_ip[64];
	char		mask[64];
	char		gateway[64];
}SRE_NetAdaptInfo;

#define SRCODEC_MAX_NAME_LEN  (20)



typedef enum _SR_VIDEO_SIZE
{
	CFG_VIDEO_LOW_TYPE = 1,					//选看终端的小流
	CFG_VIDEO_MIDDLE_TYPE,					//选看终端的中流
	CFG_VIDEO_HIGH_TYPE,					//选看终端的大流
	CFG_VIDEO_DESKTOP_TYPE,					//选看终端的桌面共享流
	CFG_VIDEO_DESKTOP_CLOSE_TYPE,			//关闭终端的桌面共享流
	CFG_VIDEO_CLOSE,						//关闭选看的终端视频流(注:不会自动关闭桌面共享流)
}SR_CFG_VIDEO_TYPE;

typedef struct _RVideoParam
{
	int 					term_id;					//选看终端的id
	HWND 					wnd;						//大窗体句柄,调用端传空
	HWND 					low_wnd;					//小窗体句柄,调用端传空
	SR_CFG_VIDEO_TYPE		video_type;					//流类型
}RVIDEO_PARAM; 


typedef struct _StreamInfo_Send
{
	char				*audioCodecName;				//音频发送编码名称
	int					audioSampleRate;				//音频发送采样率
	int					audioBitrate;					//音频发送码率

	char				*videoCodecName;				//视频发送编码名称
	int					videoLFps;						//视频发送小流帧率
	int					videoLBitrate;					//视频发送小流码率
	int					videoLWidth;					//视频发送小流宽
	int					videoLHeight;					//视频发送小流高

	int					videoMFps;						//视频发送中流帧率
	int					videoMBitrate;					//视频发送中流码率
	int					videoMWidth;					//视频发送中流宽
	int					videoMHeight;					//视频发送中流高

	int					videoHFps;						//视频发送大流帧率
	int					videoHBitrate;					//视频发送大流码率
	int					videoHWidth;					//视频发送大流宽
	int					videoHHeight;					//视频发送大流高



	char				*h239CodecName;					//视频发送桌面共享帧率
	int					h239Fps;						//视频发送桌面共享流码率
	int					h239Bitrate;					//视频发送桌面共享流宽
	int					h239Width;						//视频发送桌面共享流高
	int					h239Height;
}SendStreamInfo;

typedef struct _StreamInfo_RecvAudio
{
	int					id;								//接收音频流id
	char				*codecName;						//接收音频流Name
	int					sampleRate;						//接收音频流采样率
	int					bitRate;						//接收音频流码率 (bps)
	int                 recCodecChs;                    //接收音频流通道（1：单声道，2：立体音）
	float				loseRate;						//接收音频流丢包率
}RecvAudioStream;

typedef struct _StreamInfo_RecvVideo
{
	int					id;								//接收视频流ID
	char				*codecName;						//接收视频流Name
	int					fps;							//接收视频流帧率
	int					bitRate;						//接收视频流码率(bps)
	float				loseRate;						//接收视频丢包率
	int					width;							//接收视频流宽度
	int					height;							//接收视频流高度

}RecvVideoStream;

typedef struct _StreamInfo_Recv
{
	int						 audioStreamCnt;			//音频流接收个数
	RecvAudioStream			 *audioStreams;				//音频流接收列表

	int						 videoStreamCnt;			//视频流接收个数
	RecvVideoStream			 *videoStreams;				//视频流接收列表

	RecvVideoStream			 *h239Stream;				//桌面共享流接收信息
}RecvStreamInfo;

typedef struct _StreamInfo
{
	SendStreamInfo  send;		//发送信息统计
	RecvStreamInfo  recv;		//接收信息统计
}StreamInfo;				//音视频媒体流信息

typedef struct _MediaAudioOpt{
	bool useDrc;    /* 是否开启drc */
	bool useStereo; /* 是否开启立体声 */
	int plfreq; /* 音频编码采样率 16000， 32000， 48000*/
}MediaAudioOpt;

typedef struct _SRTermInfo
{
	int termid;
	char  tername[128];
	bool ismuted;
	bool iscamera_on;
	bool ishandup;
}TermInfo;

typedef enum {
	LabelType_Line,
	LabelType_Rectangle,
	LabelType_Circular
}LableType;

/*网络类型*/
typedef enum  {
	NETWORK_WIFI = 1,
	NETWORK_CLASS_2_G,
	NETWORK_CLASS_3_G,
	NETWORK_CLASS_4_G
}NETWORK_TYPE_CLASS;

/*标签属性定义*/
typedef struct {
	int				labelterid;
	int				operatetype;
	int				lableid;
	int				labletype;
	int				lablesize;
	int				lablecolor;
	int				linetype;

	int				leftuppoints_x;
	int				leftuppoints_y;

	int				rightdownpoints_x;
	int				rightdownpoints_y;

	int				resolution_x;
	int				resolution_y;
}ScreenLableAttr;

typedef enum {
	kVideoRawFormatYUV420P = 0,
	kVideoRawFormatRGB,
	kVideoRawFormatARGB,
}SRVideoRawFormat;

typedef enum {
	kSRScreenStream = 0,
	kSRVideoStream,
}SRVideoStreamType;




typedef struct {
	int				talk_id;
	unsigned int	energy;
}SRVoiceActiveInfo;

typedef void(*ActiveVoiceCallBack)(SRVoiceActiveInfo *voice_acive, int num);

#ifndef FUNC_SENDMESSAGE
#define FUNC_SENDMESSAGE
typedef void (*FuncSendMessage)(char *message);//发送消息
#endif

typedef void(*SRE_OnInitMCStatus)(const bool isOk);
typedef void(*SRE_OnUnInitMCStatus)(const bool isOk);
typedef void (*SRE_OnRspJoinConf)(const bool isOk, const char *fail_reason, const int sTermId);   //isOk 成功:true 失败:false fail_reson:失败原因
typedef void (*SRE_OnRspConfTermList) (const bool isOk,   		//isOk 成功 true  失败false
									   const UINT64 conf_id,   	//会议id
									   const int term_id, 		//终端id
									   const int master_id,   	//主席id
									   const int duo_term_id,
									   const int totalnums,
									   TermInfo **termInfo,   //终端信息
									   const int nSize, 		//终端信息结构大小
									   const char *fail_reason);  //失败原因
typedef void(*SRE_OnExitConf)(const char *exit_reason);

typedef void(*SRE_OnRspSendDualVideo) (const bool isOk, const UINT64 conf_id, const int term_id, const char *fail_reason);
typedef void(*SRE_OnRecvDualVideoOpen) (const UINT64 conf_id, const int term_id, const int send_id);
typedef void(*SRE_OnRecvDualVideoClose) (const UINT64 conf_id, const int term_id);
typedef void(*SRE_OnStartSendVideo) (const UINT64 conf_id, const int term_id, const int video_size);
typedef void(*SRE_OnStopSendVideo) (const UINT64 conf_id, const int term_id);
typedef void(*SRE_OnNewTermJoinConf)(const UINT64 conf_id, const int term_id, const TermInfo  *joinInfo);
typedef void(*SRE_OnTermLeave) (const UINT64 conf_id, const int term_id, const char *leave_reason, const int leaveterid);
typedef void(*SRE_OnTermHandUp)(const UINT64 conf_id, const int term_id, const int handupterid, const bool isHandUp);
typedef void(*SRE_OnMasterTransfer) (const UINT64 conf_id, const int term_id, const int new_id);

typedef void(*SRE_OnTermAudioRecMute) (const UINT64 conf_id, const int term_id, const int sponsorid, const int muteterid);
typedef void(*SRE_OnTermAudioRecUnMute) (const UINT64 conf_id, const int term_id, const int sponsorid, const int cancelterid);
typedef void(*SRE_OnTermChangeName) (const UINT64 conf_id, const int term_id, const int changeterid, const char *term_name);
typedef void(*SRE_OnDualVideoOn) (const UINT64 conf_id, const int term_id, const int dual_id);  		//dual_id 开启双流的客户端id
typedef void(*SRE_OnNetwrokNotify)(const int status);			// -1 网络掉线   // 0 网络恢复
typedef void(*SRE_OnLockVideo)(const UINT64 conf_id, const int term_id, const int unlock_id);
typedef void(*SRE_OnUnLockVideo)(const UINT64 conf_id, const int term_id, const int unlock_id);
typedef void(*SRE_OnStreamInfo)(StreamInfo *info);
typedef void(*SRE_OnOpenCamera)(const UINT64 conf_id, const int term_id, const int open_id);
typedef void(*SRE_OnCloseCamera)(const UINT64 conf_id, const int term_id, const int close_id);
typedef void(*SRE_OnOtherTerChangeHighVideoSts)(const UINT64 conf_id, const int term_id, const int chang_id, const bool  openclose);		// openclose: true:open  false:close
typedef void(*SRE_OnIndChairEndConf)(const UINT64 confid, const int termid, const int chairid, const char* chairname);

/* flag: 0-low resolution video, 1-high resolution video, 2-datashare */
typedef void(*SRE_OnRenderCallback)(int id, int flag, unsigned char *ybuf, unsigned char *ubuf, unsigned char *vbuf,int width, int height);
typedef void(*SRE_OnScreenDrawLabel)(UINT64 conf_id, int term_id,ScreenLableAttr *attr);
typedef void(*SRE_OnScreenClearLabel)(UINT64 conf_id, int term_id, int cleardid);
typedef void(*SRE_OnRecvConfMessage)(UINT64 conf_id, int from_id, char *message, int message_len);
typedef void(*SRE_OnReqAssistVideoProxy)(const UINT64 confid, const int termid, const int avtermid);
typedef void(*SRE_OnMuteAudioAllTermNotify)(const UINT64 confid, const int termid, const bool is_mute);
typedef void(*SRE_OnOtherTermRunningStatus)(const UINT64 confid, const int termid, const int stautsTermid, const int staClass, const int staSubCls, const char* staStr);

typedef enum _StackConnErrType
{
	SR_RELAYMC_CONN_ERROR = 1,					//客户端重新入会
	SR_MC_CONN_ERRROR							//客户端重新入会
}StackConnErrType;

typedef void(*SREG_OnStackConnError)(StackConnErrType type);
typedef void(*SREG_OnRelayServerCrash)(int err_nbr);
typedef struct _SRENGINE_CALLBACK
{
	SRE_OnInitMCStatus			onInitMcSts;				//初始化mc状态
	SRE_OnUnInitMCStatus        onUnInitMcSts;
	SRE_OnRspJoinConf       	onRspJoinConf; 				//入会状态
	SRE_OnExitConf				onExitConf;
	SRE_OnRspConfTermList   	onRspConfTermList; 			//获取会议中所有终端信息
	SRE_OnRspSendDualVideo  	onRspSendDualVideo; 		//开启发送双流ACK
	SRE_OnRecvDualVideoOpen     onRecvDualVideoOpen;  		//接收端收到接收双流  send_id:发送双流终端
	SRE_OnRecvDualVideoClose    onRecvDualVideoClose; 		//接收端收到关闭双流
	SRE_OnStartSendVideo  		onStartSendVideoNotify; 	//请求客户端发送视频流,由其它客户端selectvideo触发
	SRE_OnStopSendVideo 		onStopSendVideoNotify; 		//请求客户端关闭视频流
	SRE_OnNewTermJoinConf 		onNewTermJoin; 				//新的客户端加入会议
	SRE_OnTermLeave  			onTermLeave; 				//其它客户端退出会议
	SRE_OnTermHandUp 			onTermHandUp; 				//其它客户端举手或放手
	SRE_OnMasterTransfer 		onMasterTransfer; 			//主持人身份切换
	SRE_OnTermAudioRecMute      onTermAudioRecMute;  		//其它客户端禁音
	SRE_OnTermAudioRecUnMute    onTermAudioRecUnMute;  		//其它客户端取消禁音
	SRE_OnTermChangeName 		onTermChangeName; 			//其它客户端修改名称

	

	SRE_OnDualVideoOn 			onDualVideoOn; 				//新终端进入时,告知双流进行的指示
	SRE_OnLockVideo				onLockVideo;
	SRE_OnUnLockVideo			onUnLockVideo;

	SRE_OnOpenCamera			onOpenCamera;
	SRE_OnCloseCamera			onCloseCamera;

	SRE_OnOtherTerChangeHighVideoSts		onOtherTerChangeHighVideoSts;


	
	SRE_OnRenderCallback		onRenderCallBack;
	SRE_OnIndChairEndConf		onChairEndConf;

	SREG_OnStackConnError		onStackConnErr;



	SREG_OnRelayServerCrash		onRelayServerCrash;

	SRE_OnScreenDrawLabel		onScreenDrawLabel;
	SRE_OnScreenClearLabel		onScreenClearLabel;
	SRE_OnRecvConfMessage		onRecvMessage;
	SRE_OnReqAssistVideoProxy	onReqDualVideoProxy;			//其它客户端申请共享
	SRE_OnMuteAudioAllTermNotify		onMuteAudioAllTermNotify;
	SRE_OnOtherTermRunningStatus		onOtherTermRunningStatus;
}SRECALLBACK;

/*对调类*/
class ISRengineCallback
{
public:
	virtual void onInitMcSts(const bool isOk) = 0;
	virtual void onUnInitMcSts(const bool isOk) = 0;
	virtual void onRspJoinConf(const bool isOk, const char *fail_reason, const int sTermId) = 0;   //isOk 成功:true 失败:false fail_reson:失败原因
	virtual void onExitConf(const char *exit_reason) = 0;
	virtual void onRspConfTermList(const bool isOk,   		//isOk 成功 true  失败false
		const UINT64 conf_id,   	//会议id
		const int term_id, 		//终端id
		const int master_id,   	//主席id
		const int duo_term_id,
		const int totalnums,
		TermInfo **termInfo,   //终端信息
		const int nSize, 		//终端信息结构大小
		const char *fail_reason) = 0;  //失败原因
	
	virtual  void onRspSendDualVideo(const bool isOk, const UINT64 conf_id, const int term_id, const char *fail_reason) = 0;
	virtual  void onRecvDualVideoOpen(const UINT64 conf_id, const int term_id, const int send_id) = 0;
	virtual void onRecvDualVideoClose(const UINT64 conf_id, const int term_id) = 0;
	virtual void onStartSendVideoNotify(const UINT64 conf_id, const int term_id, const int video_size) = 0;
	virtual void onStopSendVideoNotify(const UINT64 conf_id, const int term_id) = 0;
	virtual void onNewTermJoin(const UINT64 conf_id, const int term_id, const TermInfo  *joinInfo) = 0;
	virtual void onTermLeave(const UINT64 conf_id, const int term_id, const char *leave_reason, const int leaveterid) = 0;
	virtual void onTermHandUp(const UINT64 conf_id, const int term_id, const int handupterid, const bool isHandUp) = 0;
	virtual void onMasterTransfer(const UINT64 conf_id, const int term_id, const int new_id) = 0;

	virtual void onTermAudioRecMute(const UINT64 conf_id, const int term_id, const int sponsorid, const int muteterid) = 0;
	virtual void onTermAudioRecUnMute(const UINT64 conf_id, const int term_id, const int sponsorid, const int cancelterid) = 0;
	virtual void onTermChangeName(const UINT64 conf_id, const int term_id, const int changeterid, const char *term_name) = 0;
	virtual void onDualVideoOn(const UINT64 conf_id, const int term_id, const int dual_id) = 0;  		//dual_id 开启双流的客户端id
	virtual void onLockVideo(const UINT64 conf_id, const int term_id, const int unlock_id) = 0;
	virtual void onUnLockVideo(const UINT64 conf_id, const int term_id, const int unlock_id) = 0;
	virtual void onOpenCamera(const UINT64 conf_id, const int term_id, const int open_id) = 0;
	virtual void onCloseCamera(const UINT64 conf_id, const int term_id, const int close_id) = 0;
	virtual void onOtherTerChangeHighVideoSts(const UINT64 conf_id, const int term_id, const int chang_id, const bool  openclose) = 0;		// openclose: true:open  false:close
	
	/* flag: 0-low resolution video, 1-high resolution video, 2-datashare */
	virtual void onRenderCallBack(int id, int flag, unsigned char *ybuf, unsigned char *ubuf, unsigned char *vbuf, int width, int height) = 0;
	virtual void onChairEndConf(const UINT64 confid, const int termid, const int chairid, const char* chairname) = 0;

	virtual void OnStackConnError(StackConnErrType  type) = 0;
	virtual void OnScreenDrawLabel(UINT64 conf_id, int term_id, ScreenLableAttr attr) = 0;
	virtual void OnScreenClearLabel(UINT64 conf_id, int term_id, int cleardid) = 0;
	virtual void OnRecvConfMessage(UINT64 conf_id, int from_id, char *message, int message_len) = 0;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//											业务层接口定义
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
/************************************************************************************************
函数名称:返回本地IP地址，只在windows版本有效
输入参数：
返回值: IP地址
************************************************************************************************/
SRENGINE_API char* SREngine_GetLocalIp(void);

/************************************************************************************************
函数名称:本函数需要客户端在启动时调用（应用程序启动）
输入参数：
callback	回调函数
debug_en	启用DEBUG SDK    true: 启用log文件输出  false: 反之
返回值: 0 成功  非0 失败
************************************************************************************************/
SRENGINE_API int SREngine_Init(SRECALLBACK	*callback,
	const bool	debug_en,
	const  char	*pLogPath);

/************************************************************************************************
函数功能：函数功能:本函数需要客户端退出时调用
输入参数：
返回值: 0 成功  非0 失败
*************************************************************************************************/
SRENGINE_API int SREngine_Uninit();

/************************************************************************************************
函数功能：初始化MC  
输入参数：relaymc_info relaymc信息(包括ip) relaymc_nsize relaymcinfo大小  termUId  ipandport
termUId  从服务端获取    ipandport从服务端获取
返回值: 0 成功  非0 失败
*************************************************************************************************/
SRENGINE_API  int SREngine_InitMC(const char	**relaymc_info,
	const  int	relaymc_nsize,
	const  int	termUId,
	const  UINT64 ipandport);

SRENGINE_API  int SREngine_UnInitMC();



/************************************************************************************************
函数功能：注册回调函数
输入参数：callback
返回值: 0 成功
*************************************************************************************************/
SRENGINE_API  int SREngine_RegisterCallBack(ISRengineCallback *callback);

/************************************************************************************************
函数功能：释放已注册的回调函数
输入参数：
返回值: 0 成功
*************************************************************************************************/
SRENGINE_API  int SREngine_UnRegisterCallBack();

/************************************************************************************************
函数功能：加入一个会议(调用成功后需要等待ACK)
输入参数： conf_id  会议ID   password 会议密码   term_name 终端名称  term_id 终端id(终端注册时的id)
  		   local_wnd 本地视频窗体
返回值: 0 成功  非0 失败
*************************************************************************************************/
SRENGINE_API  int SREngine_ReqJoinConf(const UINT64 conf_id,
									  const char *password,
									  const char *term_name,
									  const int   term_id,
									  HWND 		local_wnd,
									  bool		isMuted,
									  bool		isCameraOn);

/************************************************************************************************
函数功能：退出会议  (不需要等待ACK)
输入参数： conf_id  会议ID   term_id 终端id(终端注册时的id)  exit_reason 退出原因
返回值: 0 成功  非0 失败
*************************************************************************************************/
SRENGINE_API  int  SREngine_ExitConf(const UINT64 conf_id,
									const int term_id,
									const char *exit_reason);

/************************************************************************************************
函数功能:  获取会议中的终端信息,客户端需要根据终端信息开启接受视频(需要等待ACK)
输入参数： 
返回值: 0 成功  非0 失败
*************************************************************************************************/
SRENGINE_API  int  SREngine_ReqConfTermList();

/************************************************************************************************
函数功能:  开始发送双流(需要等ACK) 
输入参数： wnd 共享的窗体
返回值: 0 成功  非0 失败
*************************************************************************************************/
SRENGINE_API int SREngine_StartSendDualVideo(HWND wnd);

/************************************************************************************************
函数功能:  停止发送双流(不需要等ACK) 
输入参数： conf_id  会议ID   term_id 终端id(终端注册时的id)
返回值: 0 成功  非0 失败
*************************************************************************************************/
SRENGINE_API int SREngine_StopSendDualVideo();

/************************************************************************************************
函数功能:  选看远端视频
输入参数： mul_stream:选看视频id和窗口
返回值: 0 成功  非0 失败
*************************************************************************************************/
SRENGINE_API int SREngine_SelectVideo(const RVIDEO_PARAM *mul_stream, const int size);

/************************************************************************************************
函数功能:  本地终端举手(不需要等ACK) 
输入参数： hand_up 举手:true 放手:false 
返回值: 0 成功  非0 失败
*************************************************************************************************/
SRENGINE_API int SREngine_HandUp(const bool hand_up);

/************************************************************************************************
函数功能:  主持人将其他终端踢出会议命令,只有主持人可以发出去
输入参数： drop_id  被踢id
返回值: 0 成功  非0 失败
*************************************************************************************************/
SRENGINE_API int SREngine_DropTerm(const int drop_id);

/************************************************************************************************
函数功能:  主持人转让主持人身份,只有主持人可以发出去(需要ACK) 
输入参数： conf_id  会议ID   term_id 终端id(终端注册时的id)  new_id  新的主持人id
返回值: 0 成功  非0 失败
*************************************************************************************************/
SRENGINE_API int SREngine_MasterTransfer(const int new_id);

/************************************************************************************************
函数功能:  打开本地摄像头指示(不需要等ack) 
输入参数： conf_id  会议ID   term_id 终端id(终端注册时的id)
返回值: 0 成功  非0 失败
*************************************************************************************************/
SRENGINE_API int SREngine_OpenCamera();

/************************************************************************************************
函数功能:  关闭本地摄像头指示(不需要等ack) 
输入参数： conf_id  会议ID   term_id 终端id(终端注册时的id)
返回值: 0 成功  非0 失败
*************************************************************************************************/
SRENGINE_API int SREngine_CloseCamera();

/************************************************************************************************
函数功能:  禁止音频(不需要等ack)  (无区分本地和远端) 禁用本地mic，mute_term_id等于本地id
输入参数： mute_term_id:mute id
返回值: 0 成功  非0 失败
*************************************************************************************************/
SRENGINE_API int SREngine_AudioRecMute(const int mute_term_id);

/************************************************************************************************
函数功能:  恢复音频(不需要等ack)   (无区分本地和远端) 禁用本地mic，mute_term_id等于本地id
输入参数： unmute_term_id: unmute id
返回值: 0 成功  非0 失败
*************************************************************************************************/
SRENGINE_API int SREngine_AudioRecUnMute(const int unmute_term_id);



///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////音视频设备管理////////////////////////////////////////

/************************************************************************************************
函数功能：返回本地音频采集设备
输入参数：
返回值: 返回设备列表
************************************************************************************************/
SRENGINE_API const char**SREngine_GetAudioCaptureDevices();

/************************************************************************************************
函数功能：设置本地音频采集设备
输入参数：
const char * audio_name  音频采集设备名称
返回值: 0 成功  非0 失败
************************************************************************************************/
SRENGINE_API int SREngine_SetAudioCaptureDev(const char * audio_name);

/************************************************************************************************
函数功能：获取当前音频采集设备
输入参数：
返回值: 返回当前设备列表
************************************************************************************************/
SRENGINE_API const char *SREngine_GetCurrentAudioCaptureDev();

/************************************************************************************************
函数功能：获取所有音频播放设备列表
输入参数：
返回值: 返回设备列表
************************************************************************************************/
SRENGINE_API const char **SREngine_GetAudioOutputDevices();

/************************************************************************************************
函数功能：设置音频播放设备
输入参数：
const char * audio_name  音频输出设备名称
返回值: 0 成功  非0 失败
************************************************************************************************/
SRENGINE_API int SREngine_SetAudioOutputDevice(const char *audio_name);

/************************************************************************************************
函数功能：获取camera列表
输入参数：
返回值: 返回设备列表
************************************************************************************************/
SRENGINE_API const char **SREngine_GetCameraDevices();

/************************************************************************************************
函数功能：设置camera
输入参数：
char *videoid camera的名字
返回值: 0 成功  非0 失败
************************************************************************************************/
SRENGINE_API int SREngine_SetCameraDevice(const char *videoid);

/************************************************************************************************
函数功能：获取当前设置的camera
输入参数：

返回值: camera的名字
************************************************************************************************/
SRENGINE_API const char *SREngine_GetCurrentCameraDevice();


/************************************************************************************************
函数功能：开始测试speaker
输入参数：
p_spk_name 测试speaker设备名称
p_file 测试文件 (wav格式)
loop 是否循环播放  1:循环播放  0:不循环播放
返回值: 0 成功  非0 失败
************************************************************************************************/
SRENGINE_API int SREngine_TestSpeakerStart(const char * p_spk_name, const char * p_file, int loop);

/************************************************************************************************
函数功能：结束测试speaker
输入参数：
返回值: 0 成功  非0 失败
************************************************************************************************/
SRENGINE_API int SREngine_TestSpeakerStop(const char * p_spk_name);

/************************************************************************************************
函数功能：开始测试Mic 在测试过程中客户端需要一直调用该方法。
输入参数：
p_mic_name mic  名称
p_value         返回音量值  最大值255*800
返回值: 0 成功  非0 失败
************************************************************************************************/
SRENGINE_API int SREngine_TestMicStart(const char * p_mic_name, int * p_value, int * p_schedule, void * p_mic_dev);

/************************************************************************************************
函数功能：停止测试MIC
输入参数：p_mic_name 设备名称
返回值: 0 成功  非0 失败
************************************************************************************************/
SRENGINE_API int SREngine_TestMicStop(const char * p_mic_name);

/************************************************************************************************
函数功能：
输入参数：
返回值: 0 成功  非0 失败
************************************************************************************************/
SRENGINE_API int SREngine_TestMicStop(const char * p_mic_name);


/************************************************************************************************
函数功能：设置当前音频设备的 音量值
输入参数：
level 取值范围 0 ~ 255
返回值:
************************************************************************************************/
SRENGINE_API void SREngine_SetSpeakerLevel(int level);

/************************************************************************************************
函数功能：返回值当前音频设备的 音量值大小
输入参数：
返回值: 取值范围 0 ~ 255
************************************************************************************************/
SRENGINE_API int SREngine_GetSpeakerLevel();


/************************************************************************************************
函数功能：视频预览接口  D3D方式
输入参数：
返回值: 0 成功  非0 失败
************************************************************************************************/
SRENGINE_API int SREngine_StartVideoPreview2(const char *videoid, void *hwnd);

/************************************************************************************************
函数功能：停止视频预览
输入参数：
返回值: 0 成功  非0 失败
************************************************************************************************/
SRENGINE_API int SREngine_StopVideoPreview2();



/************************************************************************************************
函数功能：注册获取每路音频流的能量值信息
输入参数：ActiveVoiceCallBack cb 回调
返回值: 0 成功  非0 失败
************************************************************************************************/
SRENGINE_API void SREngine_RegisterGetAudioActiveInfo(ActiveVoiceCallBack  cb);


/************************************************************************************************
函数功能：主持人指定会议室内其它人看某一个客户端的视频
输入参数：
返回值: 0 成功  非0 失败
************************************************************************************************/
SRENGINE_API int SREngine_LockVideo(const UINT64  confi_id, const int term_id, const int lock_id);

/************************************************************************************************
函数功能：主持人取消指定会议室内其它人看某一个客户端的视频
输入参数：
返回值: 0 成功  非0 失败
************************************************************************************************/
SRENGINE_API int SREngine_UnLockVideo(const UINT64  confi_id, const int term_id, const int unlock_id);


/************************************************************************************************
函数功能：获取统计信息
输入参数：
返回值: 0 成功  非0 失败
************************************************************************************************/
SRENGINE_API StreamInfo * SREngine_GetStreamInfo();

/************************************************************************************************
函数功能：修改终端名称
输入参数：
返回值: 0 成功  非0 失败
************************************************************************************************/
SRENGINE_API  int SREngine_ChangeName(const char *new_name);

/************************************************************************************************
函数功能：修改终端名称
输入参数：  streamid   media_type: 0-audio, 1-video low, 2-video-high
返回值: 0 成功  非0 失败
************************************************************************************************/
SRENGINE_API int SREngine_GetDownLoadBitrate(int stream_id, int media_type);

/************************************************************************************************
函数功能：设置音频参数, 入会之前调用
输入参数：  opt 音频参数信息
返回值: 0 成功  非0 失败
************************************************************************************************/
SRENGINE_API int SREngine_SetAudioOpt(MediaAudioOpt *opt);


/*主持人结束会议*/
SRENGINE_API int SREngine_ChairEndConf(const UINT64 confid, const int termid);

/*设置relay 地址
char *address:  example:192.168.1.1:8000/192.168.1.2:8003
*/

SRENGINE_API int SREngine_SetRelayServer(char *address);

/*
添加桌面共享标注
conf_id 会议ID， term_id 本地终端ID， attr,共享LABLE属性
*/
SRENGINE_API int SREngine_AddScreenLabel(UINT64 conf_id, int term_id, ScreenLableAttr attr);

SRENGINE_API int SREngine_SendConfMessage(UINT64 confid, const int termid, int *to_termid_list, int to_termid_count,char *message_body, int message_len);
SRENGINE_API int SREngine_InVideoRawStream(SRVideoStreamType type, SRVideoRawFormat format, int width, int height, char *buf[3], int buf_size[3]);
SRENGINE_API int SREngine_InAudioRawStream(int sample, int channel, char *buf, char *buf_size);

SRENGINE_API  int SREngine_StartPlayingFileAsMicrophone(const char *name);
SRENGINE_API  int SREngine_StopPlayingFileAsMicrophone();
SRENGINE_API int SREngine_StartSendVideoDebug(int size);

SRENGINE_API int SREngine_SetAndroidObjects(void* javaVM, void* env, void* context);

/************************************************************************************************
函数功能：回复桌面共享申请
输入参数：  confid 会议ID  termid 本地ID，avterid 请求共享端ID， isok 是否同意其它客户端共享 rejectreason 拒绝原因，同意可置空
返回值: 0 成功  非0 失败
************************************************************************************************/
SRENGINE_API int SREngine_RspSendDualVideoProxy(const UINT64 confid, const int termid, const int avterid, const bool isok, const char* rejectreason);


/************************************************************************************************
函数功能：网络类型
输入参数： NETWORK_TYPE_CLASS  type
返回值: 0 成功  非0 失败
************************************************************************************************/
SRENGINE_API int SREngine_MobileNetworkTypeNotify(NETWORK_TYPE_CLASS  type);


/************************************************************************************************
函数功能：除主持人外其它所有终端静音
输入参数： confid  会议ID， termid 本地s_termid   ismute true:静音   false:取消静音
返回值: 0 成功  非0 失败
************************************************************************************************/
SRENGINE_API int SREngine_MuteAudioAllTerm(const UINT64 confid, const int termid,const bool ismute);

/************************************************************************************************
函数功能：锁定会议(主持人锁定会议后，新终端无法加入会议)
输入参数： confid  会议ID， termid 本地s_termid  isLock  true: 锁定   false:取消锁定
返回值: 0 成功  非0 失败
************************************************************************************************/
SRENGINE_API int SREngine_LockConf(const UINT64 confid, const int termid, const bool isLock);


/************************************************************************************************
函数功能：第三方音频库lisence注册
输入参数： licence 字符串  len 长度
返回值: 0 成功  非0 失败
************************************************************************************************/
SRENGINE_API int SREngine_RegisterExtAudioProcessLicence(const char *licence, int len);

/************************************************************************************************
函数功能：获取第三方音频库版本和Id
输入参数：
返回值:   返回版本号字符串
************************************************************************************************/
SRENGINE_API char* SREngine_GetExtAudioProcessVersion();
SRENGINE_API char* SREngine_GetExtAudioProcessId();

/************************************************************************************************
函数功能：通知其它客户端状态
输入参数：
返回值:  0 成功  非0 失败
************************************************************************************************/
SRENGINE_API int SREngine_RunningStatusNotify(const UINT64 confid, const int termid, const int sta_class, const int sta_sub_class, const char *status_str);

/************************************************************************************************
函数功能：设置音频播放模式（仅限android版本调用）
输入参数： mode:   0:听筒模式   1:外音模式
返回值:  0 成功  非0 失败
************************************************************************************************/
SRENGINE_API int SREngine_SetSpeakerMode(int mode);

/************************************************************************************************
函数功能：重启音频设备（仅限ios版本使用）
返回值:  0 成功  非0 失败
************************************************************************************************/
SRENGINE_API int SREngine_ResetAudioDevice();

SRENGINE_API int SREngine_NetworkChanged();

#endif
