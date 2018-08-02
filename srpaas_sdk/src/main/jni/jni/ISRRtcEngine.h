#ifndef SUIRUI_RTC_ENGINE_API_H_H_
#define SUIRUI_RTC_ENGINE_API_H_H_

#include "ISRRtcType.h"

#if defined(SUIRUI_RTC_ENGINE_EXPORTS)
#define SUIRUI_RTC_ENGINE_API __declspec(dllexport)
#elif defined(SUIRUI_RTC_ENGINE_IMPORTS)
#define SUIRUI_RTC_ENGINE_API __declspec(dllimport)
#else
#define SUIRUI_RTC_ENGINE_API extern
#endif


namespace suirui
{

    namespace rtc
    {

        class ISRRtcEngineDeviceEventCallback
        {
        public:
            /**
            * camera 设备热插拔
            * @param [in] type
            *           热插拔类型
            * @param [in] device_name  热插拔的设备的名字
            */
            virtual void OnCameraChange(SR_DEVICE_CHANGE_TYPE type, const char * device_name)
            {
                (void)type;
                (void)device_name;
            }

            /**
            * audio 设备热插拔
            * @param [in] type
            *           热插拔类型
            *@param [in] device_name  热插拔的设备的名字
            */
            virtual void OnAudioChange(SR_DEVICE_CHANGE_TYPE type, const char * device_name)
            {
                (void)type;
                (void)device_name;
            }

            /**
            * 网络状态
            * @param [in] status
            *
            */
            virtual void OnNetwrokNotify(const int status)         // -1 网络掉线   // 0 网络恢复
            {
                (void)status;
            }
        };


        class  ISRRtcEngineConferenceControlEventCallback
        {

        public:
            /**
            * 某个终端举手回调
            * @param [in] handup_stermid
            *           举手终端的termid
            * @param [in] is_handup
            *           是否举手
            */
            virtual void OnTermHandUp(const int handup_stermid, const bool is_handup)
            {
                (void)handup_stermid;
                (void)is_handup;
            }

			/**
			* 主持人将允许发言的处理结果转给某终端或者对其申请的回应回调
			* @param [in] ispermission
			*           是否允许
			*/
			virtual void OnIndPermissionHandUp(const bool ispermission)
			{
				(void)ispermission;
			}

			/**
			* 取消所有申请 命令所有人放下手回调
			*/
			virtual void OnIndTerPutAllHandDown()
			{

			}

            /**
            * 新的主持人收到回调
            * @param [in] chair_stermid
            *           新的主持人的stermid
            */
            virtual void OnMasterTransfer(const int chair_stermid)
            {
                (void)chair_stermid;
            }

            /**
            * 其它终端收到主持人的静音回调
            * @param [in] ismute
            *           是否静音
            */
            virtual void OnMuteAudioAllTermNotify(const bool ismute)
            {
                (void)ismute;
            }

			/**
			* 主持人发出强制静音，其他客户端收到回调
			* 自己要禁用自己的声音，不允许打开，只有向主持人发起请求handup
			@param [in] isforcemute
			*           是否强制静音 true 代表强制静音，false代表解除强制静音
			*/
			virtual void OnConfForceMute(const bool isforcemute)
			{
				(void)isforcemute;
			}

            /**
            * 主持人指定会议室内其它人看某一个客户端的视频回调
            * @param [in] lock_stermid
            *           指定终端的sterm id
            */
            virtual void OnLockVideo(const int lock_stermid)
            {
                (void)lock_stermid;
            }
            virtual void OnUnLockVideo(const int unlock_stermid)
            {
                (void)unlock_stermid;
            }

            /**
            * 主持人结束会议回调
            * @param [in] chair_stermid
            *           主持人的chair_stermid
            * @param [in] chair_name
            *           主持人的名字
            */
            virtual void OnIndChairEndConf(const int chair_stermid, const char* chair_name)
            {
                (void)chair_stermid;
                (void)chair_name;
            }

			/**
			* 主持人结束会议回调
			* @param [in] chair_stermid
			*           主持人的chair_stermid
			* @param [in] chair_name
			*           主持人的名字
			* @param [in] error
			*           增加一个主持人结束会议的原因
			*/
			virtual void OnIndChairEndConf(const int chair_stermid, const char* chair_name, const SRConferenceAbnormal & error)
			{
				(void)chair_stermid;
				(void)chair_name;
				(void)error;
			}

            /**
            * 主持人结束共享回调
            * @param [in] chair_stermid
            *           主持人的chair_stermid
            * @param [in] chair_name
            *           主持人的名字
            */
            virtual void OnIndChairEndDataShare(const int chair_stermid, const char* chair_name)
            {
                (void)chair_stermid;
                (void)chair_name;
            }

            /**
            * 修改终端名称
            * @param [in] changeterid
            *           要改变终端的termid
            * @param [in] term_name
            *           要改变的名称
            */
            virtual void OnTermChangeName(const int change_stermid, const char* term_name)
            {
                (void)change_stermid;
                (void)term_name;
            }


			/**
			* 收到会议模式发生变化
			* @param [in] newconfmode
			*           会议模式  //0 - 自由模式 1 - 主席模式
			*/
			virtual void  OnChangeConfMode(const int newconfmode)
			{
				(void)newconfmode;
			}

			/**
			* 布局发生变化同步更新到终端，有可能把转发模式和混屏模式的布局都反馈给上层
			* @param [in] layoutinfos
			*           布局信息
			*/
			virtual void  OnScreenSRLayoutInfo(std::list<SRLayoutInfo>& layoutinfos)
			{
				(void)layoutinfos;
			}

			virtual void OnRspConfStatus(const bool isok, ConfStatus & confstatus, const SRConferenceAbnormal & error)
			{
				(void)isok;
				(void)confstatus;
				(void)error;

			}


			/**
			* 参会人变化同步更新到终端 增加和删除
			* @param [in] paticipants
			*           参会人列表
			*/
			virtual void OnUpdateAddPaticipants(std::list<TermInfo> &paticipants)
			{
				(void)paticipants;
			}
			virtual void OnUpdateDelPaticipants(std::list<TermInfo> &paticipants)
			{
				(void)paticipants;
			}


			/**
			* 收到增加滚动字幕消息
			* @param [in] subtitlemsg
			*           字幕内容
			* @param [in] subtitle_info
			*           字幕信息
			*/
			virtual void OnIndTerAddSubtitle(std::string & subtitlemsg, SubtitleInfo & subtitle_info)
			{
				(void)subtitlemsg;
				(void)subtitle_info;
			}

			/**
			* 收到停止滚动字幕消息
			*/
			virtual void OnIndTerStopSubtitle()
			{
			}


			/**
			* 收到显示会场名的消息
			* @param [in] subtitle_info
			*           字幕信息
			*/
			virtual void OnIndTerDisplayOtherTername(SubtitleInfo & subtitle_info)
			{
				(void)subtitle_info;
			}

			/**
			* 收到隐藏会场名消息
			* @param [in] subtitle_info
			*           字幕信息
			*/
			virtual void OnIndTerHideOtherTername()
			{

			}

			/**
			* 收到会控者设置标准终端观看方式
			* @param [in] seeingstyle
			*           观看方式，0-跟随主持人、1-仅显示主席会场、2-标准终端观看网关分屏布局
			*/
			virtual void OnIndStdTerSeeingStyle(const int seeingstyle)
			{
				(void)seeingstyle;
			}


			/**
			* 会控者收到白名单变化
			* @param [in] whitelistinfo
			*           白名单信息
			*/
			virtual void OnIndWhitelistInfo(const WhiteListInfo & whitelistinfo)
			{
				(void)whitelistinfo;
			}

			/**
			* 终端收到自己是否在白名单内
			* @param [in] whitelisttype
			*           白名单类型,0-主席模式白名单、1-直播模式白名单
			* @param [in] inwhitelist
			*           true表示在白名单中, false表示不在白名单中
			*/
			virtual void OnIndTerInWhitelistState(const int  whitelisttype, const bool inwhitelist)
			{
				(void)whitelisttype;
				(void)inwhitelist;
			}

			/**
			* 终端收主持人开启会议录制停止会议录制
			* @param [in] recstate
			*          0-停止录制,1-开始录制
			* @param [in] error
			*         recstate为0时表示停止，brief_reason原因为空或者"default"为正常停止,其它为具体原因
			*/
			virtual void OnIndTerCRSRecState(const int recstate, const SRConferenceAbnormal & error)
			{
				(void)recstate;
				(void)error;
			}

			/**
			* 终端收主持人开启会议直播状态
			* @param [in] livestate
			*         直播会议的状态,0-停止直播,1-开始直播
			* @param [in] liveplayurl
			*         livestate为1开始直播时,终端(主席)显示用
			* @param [in] error
			*        livestate为0时表示停止原因,为空或者"default"为正常停止,其它为具体原因
			*/
			virtual void OnIndTerCRSLiveState(const int livestate, const std::string & liveplayurl, const SRConferenceAbnormal & error)
			{
				(void)livestate;
				(void)liveplayurl;
				(void)error;
			}

			/**
			* 终端收直播设置变更
			* @param [in] new_setting
			*          新的直播设置
			*/
			virtual void OnIndLiveSettingChanged(const LiveSetting & new_setting)
			{
				(void)new_setting;
			}

			/**
			* MC将该消息群发到其他所有在会终端(包含主持人) 哪个终端类型转变
			* @param [in] nspclterid
			*          特殊类型变化的终端stermid
			* @param [in] nspcltype
			*          终端要转变的类型,变化后的特殊类型,	0-普通终端类型,1-投屏终端类型
			*/
			virtual void OnIndTerSpecialtypeTransfer(const int nspclterid,const int nspcltype)
			{
				(void)nspclterid;
				(void)nspcltype;
			}

        };

        class ISRRtcEngineConferenceEventCallback
        {
        public:
            virtual ~ISRRtcEngineConferenceEventCallback() {}

            /**
            * 加入会议的回调
            * @param [in] isok
            *        是否加入会议ok
            * @param [in] error
            *        如果失败， 失败错误类
            * @param [in] stermid
            *        返回当前对应的stermid
            */
            virtual void OnRspJoinConf(const bool isok, const SRConferenceAbnormal & error, const int stermid)
            {
                (void)isok;
                (void)error;
                (void)stermid;
            }

            /**
            * 退出会议的回调
            * @param [in] exit_reason
            *        退出原因
            */
            virtual void OnExitConf(const char*  exit_reason)
            {
                (void)exit_reason;
            }

            /**
            * 对于新终端的加入会议
            * @param [in] conf_id
            *
            */
            virtual void OnNewTermJoinConf(const TermInfo  & join_info)
            {
                (void)join_info;
            }

            /**
            * 对于终端的离开会议
            * @param [in] conf_id
            *
            */
            virtual void OnTermLeave(const int leave_stermid, const SRConferenceAbnormal &leave_reason)
            {
                (void)leave_stermid;
                (void)leave_reason;
            }

            /**
            * 获取参会人列表
            * @param [in] isok
            *
            */
            virtual void OnRspConfTermList(const bool isok,         //isok 成功 true  失败false
                                           const SRConferenceAbnormal & error,
                                           const int chair_stermid,    //主席id
                                           const int dualvideo_stermid, //共享端的id
                                           std::deque<TermInfo> & termInfos   //终端信息链表
                                          )
            {
                (void)isok;
                (void)error;
                (void)chair_stermid;
                (void)dualvideo_stermid;
                (void)termInfos;
            }



            /* flag: 0-low resolution video, 1-high resolution video, 2-datashare */ //TODO
            /**
            * yuv数据的回调
            * @param [in] stermid
            *           返回者的stermid
            @param [in] flag
            *           流类型
            @param [in] frame
            *           返回者的帧数据
            */
            virtual void OnRenderFrame(int stermid, int flag, VideoFrame & frame)
            {
                (void)stermid;
                (void)flag;
                (void)frame;
            }


            /**
            * 请求客户端发送视频流,由其它客户端selectvideo触发
            @param [in] video_size
            *
            */
            virtual void OnStartSendVideo(const int video_size)
            {
                (void)video_size;
            }
            virtual void OnStopSendVideo()//请求客户端关闭视频流
            {
            }

            /**
            * 开启共享回调
            * @param [in] isOk
            *           是否可以开启回调
            @param [in] error
            *           如果错误,返回错误类
            */
            virtual void OnRspSendDualVideo(const bool isok, const SRConferenceAbnormal &error)
            {
                (void)isok;
                (void)error;
            }

            /**
            * 对于其他人共享回调, 终端收到共享的回调
            @param [in] dualvideo_send_stermid
            *           谁发送的桌面共享的sterm id
            */
            virtual void OnRecvDualVideoOpen(const int dualvideo_send_stermid)
            {
                (void)dualvideo_send_stermid;
            }
            /**
            * 对于其他人共享回调, 终端收到停止共享的回调
            @param [in] dualvideo_send_stermid
            *           结束桌面共享终端的sterm id
            */
            virtual void OnRecvDualVideoClose(const int dualvideo_close_stermid)
            {
                (void)dualvideo_close_stermid;
            }

            /**
            * 对于其他人共享回调, 终端收到共享发起者暂停共享的回调
            @param [in] dualvideo_pause_stermid
            *           桌面共享发起终端的sterm id
            */
            virtual void OnRecvDualVideoPause(const int dualvideo_pause_stermid)
            {
                (void)dualvideo_pause_stermid;
            }

            /**
            * 对于其他人共享回调, 终端收到共享发起者恢复共享的回调
            @param [in] dualvideo_resume_stermid
            *           桌面共享恢复终端的sterm id
            */
            virtual void OnRecvDualVideoResume(const int dualvideo_resume_stermid)
            {
                (void)dualvideo_resume_stermid;
            }



            /**
            * 其他人申请共享时， 该回调是发给会中共享人的
            @param [in] who_want_send_dualvideo_stermid
            *           想要发送的桌面共享的sterm id
            */
            virtual void OnReqAssistVideoProxy(const int who_want_send_dualvideo_stermid)
            {
                (void)who_want_send_dualvideo_stermid;
            }


            /**
            * 添加备注的回调
            @param [in] attr
            *           备注结构
            */
            virtual void OnScreenDrawLabel(SRScreenLableAttr &attr)
            {
                (void)attr;
            }


            virtual void OnScreenClearLabel(int cleard_stermid)
            {
                (void)cleard_stermid;
            }


            /**
            * 收到消息体回调
            @param [in] from_stermid
            *            发出message消息终端的stermid 0-代表会控，非0-入会终端
            @param [in] message
            *           消息体
            */
			virtual void OnRecvConfMessage(const int from_stermid, const std::string & message)
            {
                (void)from_stermid;
                (void)message;
            }

			/**
			* 收到im消息体回调
			@param [in] from_stermid
			*            发出message消息终端的stermid 0-代表会控，非0-入会终端
			@param [in] message
			*           消息体
			*/
			virtual void OnRecvIMMessage(const int from_stermid, const std::string & message)
			{
				(void)from_stermid;
				(void)message;
			}

            /**
            *
            @param [in] close_stermid 和 open_stermid
            *           打开摄像头或者关闭摄像头终端的stermid
            */
            /*
            会中其他客户端打开和关闭摄像头
            */
            virtual void OnOpenCamera(const int open_stermid)
            {
                (void)open_stermid;
            }
            virtual void OnCloseCamera(const int close_stermid)
            {
                (void)close_stermid;
            }


            /**
            * 主持人可以静音其他客户端，其他客户端收到回调
            * 自己可以禁用自己的声音， 其他客户端收到我的静音回调
            @param [in] mute_stermid
            *           要静音的stermid
            */
            virtual void OnTermAudioRecMute(const int mute_stermid)
            {
                (void)mute_stermid;
            }
            virtual void OnTermAudioRecUnMute(const int cancel_stermid)
            {
                (void)cancel_stermid;
            }


		

            /**
            *通知其它客户端状态，自定义结构
            * @param [in ] stautsTermid
            *        状态通知的终端的s_termid
            * @param [in ] staClass staSubCls staStr
            *       自定义结构
            *
            */
            virtual void OnOtherTermRunningStatus(const int stautsTermid, const int staClass, const int staSubCls, const std::string staStr)
            {
                (void)stautsTermid;
                (void)staClass;
                (void)staSubCls;
                (void)staStr;
            }
         
            //MPServer信息
			//channelid 对应的那个mp
			//addordel 对应mp是否删除增加 1:add  2:del
            virtual void OnMPInfo(const int channelid, const int addordel)          //addordel 1:add  2:del
            {
                (void)channelid;
                (void)addordel;
            }

			//channelid 对应的那个mp
			//screenid 混屏布局对应屏幕id
			//screentype 屏幕类型，1-会议屏幕/网关(标准终端)屏幕、2-终端屏幕、3-双流屏幕
			//addordel 屏幕的是否增加删除 1:add  2:del
            virtual void OnMPScreenInfo(const int channelid, const int screenid, const int screentype, const int addordel)//addordel  1:add  2:del
            {
                (void)channelid;
                (void)screenid;
                (void)screentype;
                (void)addordel;
            }

            ///新加入的终端可能会出收到该消息，与GetTermList类似
            virtual void OnAllMPInfo(std::list<SRMediaPInfo>& mpis)
            {
                (void)mpis;
            }


            //virtual void OnStackConnError(StackConnErrType type);
            //virtual void OnRelayServerCrash(int err_nbr);

            /**
            * when error message come, the function will be called
            * @param [in] err
            *        error code
            */
            virtual void onServerError(const SR_ERROR_CODE_TYPE error)
            {
                (void)error;
            }

			/**
			* when ok message come, the function will be called
			* @param [in] ok
			*        ok code
			*/
			virtual void onServerOk(const SR_OK_CODE_TYPE ok)
			{
				(void)ok;
			}


            /**
            *通知其它客户端状态, 我处于打电话状态， 挂断电话状态
            * @param [in ] call_telphone_stermid handup_telphone_stermid
            *       打电话终端的stermid
            * @return
            */
            virtual void OnTelphoneCallComing(const int call_telphone_stermid)
            {
                (void)call_telphone_stermid;
            }
            virtual void OnTelphoneHangUp(const int  handup_telphone_stermid)
            {
                (void)handup_telphone_stermid;
            }

        };


        class ISRRtcEngineDataEventCallback
        {
        public:

            /**
            * 接收信息统计回调
            * @param [in] stats
            *           回调信息
            */
            virtual void onRecvStreamInfoStats(const RecvStreamInfo& stats)
            {
                (void)stats;
            }

            /**
            * 发送信息统计回调
            * @param [in] stats
            *           回调信息
            */
            virtual void onSendStreamInfoStats(const SendStreamInfo& stats)
            {
                (void)stats;
            }

            /**
            * 获取每路音频流的能量值信息
            * @param [in] voice_acive
            *           终端的能量值队列
            */
            virtual void OnActiveVoice(std::deque<SRVoiceActiveInfo> voice_acives)
            {
                (void)voice_acives;
            }

            /**
            * 通知用户重新获取key， 重新走认证流程
            * @param [in] type
            *           预留
            */
            virtual void OnGetApmAgain(int type)
            {
                (void)type;
            }
        };

        class ISRVideoDeviceCollection
        {
        public:
            virtual ~ISRVideoDeviceCollection() {}
            /**
            * get the available devices count
            * @return return the device count
            */
            virtual int getCount() = 0;

            /**
            * get video device information
            * @param [in] index
            *        the index of the device in the device list
            * @param [in out] deviceName
            *        the device name, UTF8 format
            * @param [in out] deviceId
            *        the device ID, UTF8 format
            * @return return 0 if success or an error code
            */
            virtual int getDevice(int index, char deviceName[SR_MAX_DEVICE_ID_LENGTH], char deviceId[SR_MAX_DEVICE_ID_LENGTH]) = 0;

            /**
            * release the resource
            */
            virtual void release() = 0;
        };

        class ISRVideoDeviceManager
        {
        public:
            ISRVideoDeviceManager() {}
            virtual ~ISRVideoDeviceManager() {}
            /**
            * create the ISRCameraDeviceCollection interface pointer
            * @return return the ISRCameraDeviceCollection interface or nullptr if failed
            */
            virtual ISRVideoDeviceCollection* EnumerateVideoDevices() = 0;

            /**
            * active the Camera device for current using
            * @param [in] deviceId
            *        the deviceId of the device you want to active currently
            * @return return 0 if success or the error code.
            */
            virtual int SetDevice(const char deviceId[SR_MAX_DEVICE_ID_LENGTH]) = 0;

            /**
            * get the current active Camera device
            * @param [in out] deviceId
            *        the device id of the current active video device
            * @return return 0 if success or an error code
            */
            virtual int GetCurrentDevice(char deviceId[SR_MAX_DEVICE_ID_LENGTH]) = 0;

            /**
            * test the Camera capture device to know whether it can worked well
            * @param [in] hwnd
            *        the HWND of the video-display window
            * @return return 0 if success or an error code
            */
            virtual int startDeviceTest(view_t hwnd) = 0;

            /**
            * stop the Camera device testing
            * @return return 0 if success or an error code
            */
            virtual int stopDeviceTest() = 0;
        };

        //Audio Device Management
        class ISRAudioDeviceManager
        {
        public:
            virtual ~ISRAudioDeviceManager() {}
            /**
            *
            * 获取当前音频扬声器输出列表
            * @param [out] device_names
            *                             列表通过该参数返回回来
            * @return return 0 if success or the error code.
            */

            virtual int  GetOutputDevices(list<std::string> &device_names) = 0;
            /**
            *
            * 获取当前音频麦克风输入列表
            * @param [out] device_names
            *                             列表通过该参数返回回来
            * @return return 0 if success or the error code.
            */
            virtual int  GetInputDevices(list<std::string> & device_names) = 0;

            //-------------------------------output----------------------
            /**
            *
            *输出设备设置， 会中如果切换也调用该接口
            * @param [in] device_name
            *        从列表当中选择你需要的扬声器设备
            * @return return 0 if success or the error code.
            */
            virtual int SetOutputDevice(const char* device_name) = 0;

            /**
            *获取当前使用的扬声器
            *
            * @param [out] device_name
            *        当前使用的扬声器， 需要事先分配空间
            * @return return 0 if success or an error code
            */
            virtual int GetCurrentOutputDevice(char device_name[SR_MAX_DEVICE_ID_LENGTH]) = 0;

            /**
            * 设置当前扬声器的音量
            *
            * @param [in] volume
            *        想要设置的音量值，区间 0-255
            * @return return 0 if success or an error code
            */
            virtual int SetOutputDeviceVolume(int volume) = 0;

            /**
            *获取当前扬声器的音量
            *
            * @return return 扬声器音量，区间 0-255
            */
            virtual int GetOutputDeviceVolume() = 0;


            /**
            *测试扬声器是否正常工作， 输入一个播放文件
            *
            * @param [in] testAudioFilePath
            *       wav格式的播放文件
            * @return return 0 if success and you can hear the sound of the .wav file or an error code.
            */
            virtual int StartOutputDeviceTest(const char *testAudioFilePath) = 0;

            /**
            * 停止测试
            * @return return 0 if success or an error code
            */
            virtual int StopOutputDeviceTest() = 0;


            //-----------------------------------input-----------------------
            /**
            *
            *输入设备设置， 会中如果切换也调用该接口
            * @param [in] device_name
            *       从列表当中选择你需要的麦克风设备
            * @return return 0 if success or the error code.
            */
            virtual int SetInputDevice(const char* device_name) = 0;

            /**
            * get the current active Input device
            * @param [in out] device_id
            *        the device id of the current active recording audio device
            * @return return 0 if success or an error code

            */
            virtual int  GetCurrentInputDevice(char device_name[SR_MAX_DEVICE_ID_LENGTH]) = 0;

            /**
            * set current Input device volume
            * @param [in] volume
            *        the volume you want to set 0-255
            * @return return 0 if success or an error code
            */
            virtual int SetInputDeviceVolume(int volume) = 0;

            /**
            * get current Input device volume
            * @return return Input device volume 0-255
            */
            virtual int GetInputDeviceVolume() = 0;

            /**
            * test the Input audio device to know whether it can worked well
            * @param [in out] value
            *      The value of the current microphone
            * @return return 0 if success or an error code
            *   需要循环去调用， 来获取value
            */
            virtual int GetInputDeviceValueTest(int & value) = 0;

            /**
            * stop the Input audio device testing
            * @return return 0 if success or an error code
            */
            virtual int StopInputDeviceTest() = 0;


            /**
            * 重启音频设备（仅限ios版本使用）
            * @return return 0 if success or an error code
            */
            virtual int ResetAudioDevice() = 0;
        };


        class ISRRtcEngineConferenceControl
        {
        public:
            virtual ~ISRRtcEngineConferenceControl() {}

            /**
            *主持人将其他终端踢出会议
            * @param [in ] drop_stermid
            *       踢出终端的sterm_id
            * @return return 0 if success or an error code
            */
            virtual int DropTerm(const int drop_stermid) = 0;

            /**
            *The Master drop other terminal in conference  only the Master can use
            * @param [in ] drop_term
            *       主持人踢人会控结构
            * @return return 0 if success or an error code
            */
            virtual int DropTerm(const SRConferenceCtrlDropTerm & drop_term) = 0;

            /**
            * 主持人转让主持人身份
            * @param [in ] new_termid
            *        新的终端的termid
            * @return return 0 if success or an error code
            */
            virtual int  MasterTransfer(const int new_stermid) = 0;

            /**
            * 主持人转让主持人身份
            * @param [in ] new_term
            *        主持人转移会控结构
            * @return return 0 if success or an error code
            */
            virtual int  MasterTransfer(const SRConferenceCtrlMasterTransfer & new_term) = 0;


            /**
            * 主持人设置辅助主席， 取消辅助主席
            * @param [in ] new_term
            *        设置辅助主席会控结构
            * @return return 0 if success or an error code
            */
            virtual int  SetAssistChairman(const SRConferenceCtrlAssistChairman & new_term) = 0;
            
			/**
            *主持人指定会议演讲人
            * @param [in ] lock_stermid
            *        要锁的终端的stermid
            * @return return 0 if success or an error code
            */
            virtual int LockVideo(const int lock_stermid) = 0;
            
			/**
            *主持人指定会议演讲人
            * @param [in ] lock_term
            *        锁定演讲人会控结构
            * @return return 0 if success or an error code
            */
            virtual int LockVideo(const SRConferenceCtrlLockVideo & lock_term) = 0;

            /**
             *主持人取消演讲人
             * @param [in ] unlock_stermid
             *        要取消的终端的stermid
             * @return return 0 if success or an error code
             */
            virtual int UnLockVideo(const int unlock_stermid) = 0;

            /**
            *主持人取消演讲人
            * @param [in ] unlock_term
            *         取消演讲人会控结构
            * @return return 0 if success or an error code
            */
            virtual int UnLockVideo(const SRConferenceCtrlUnLockVideo& unlock_term) = 0;
			
			/**
			*主持人结束会议
			* @return return 0 if success or an error code
			*/
			virtual int ChairEndConf() = 0;
           
			/**
            *主持人结束会议
            * @param [in ] end_conf
            *       主持人结束会议会控结构
            * @return return 0 if success or an error code
            */
            virtual int ChairEndConf(const SRConferenceCtrlChairEndConf& end_conf) = 0;


            /**
            *会中有共享，主持人可结束
            * @return return 0 if success or an error code
            */
            virtual int ChairEndDataShare() = 0;

            /**
            *除主持人外其它所有终端静音
            * @param [in ] ismute
            *        true:静音   false:取消静音
            * @return return 0 if success or an error code
            */
            virtual int MuteAudioAllTerm(const bool ismute) = 0;
            /**
            *除主持人外其它所有终端静音
            * @param [in ] muteall
            *        全体静音会控结构
            * @return return 0 if success or an error code
            */
            virtual int MuteAudioAllTerm(const SRConferenceCtrlMuteAudioAllTerm & muteall) = 0;
            /**
            *锁定会议(主持人锁定会议后，新终端无法加入会议)
            * @param [in ] isLock
            *        true: 锁定   false:取消锁定
            * @return return 0 if success or an error code
            */
            virtual int LockConf(const bool islock) = 0;

            /**
            *锁定会议(主持人锁定会议后，新终端无法加入会议)
            * @param [in ] lock_conf
            *        锁定会议会控结构
            * @return return 0 if success or an error code
            */
            virtual int LockConf(const SRConferenceCtrlLockConf& lock_conf) = 0;


			/**
			*主持人响应某人的申请
			* @param [in ] whohandup
			*   响应结构体
			* @return return 0 if success or an error code
			*/
			virtual int RspWhoHandUp(const SRConferenceCtrlPermissionHandUp &whohandup) = 0;

			/**
			*取消所有申请，命令所有人放下手
			* @param [in ] allhanddown
			*   取消所有人申请结构体
			* @return return 0 if success or an error code
			*/
			virtual int PutAllHandDown(const SRConferenceCtrlPutAllHandDown &allhanddown) = 0;

			/**
			*举手功能
			* @param [in ] hand_up
			*    举手:true 放手:false
			* @return return 0 if success or an error code
			*/
			virtual int HandUp(const bool handup) = 0;

            /**
            *修改终端名称
            * @param [in ] new_name
            *       终端的新名称
            * @return return 0 if success or an error code
            */
            virtual  int ChangeTermName(const char * new_name) = 0;

            /**
            *主持人切换会议模式
            * @param [in ] newconfmode
            *       切换会议模式会控结构
            * @return return 0 if success or an error code
            */
            virtual  int ChangeConfMode(const SRConferenceCtrlChangeConfMode& newconfmode) = 0;


            /**
            * 设置分屏布局显示
            * @param [in ] layout
            *        分屏布局会控结构
            * @return return 0 if success or an error code
            */
            virtual int  SetScreenSRLayout(const SRConferenceCtrlSRLayoutInfo & layout) = 0;


            /**
            * 请求当前屏幕的分屏信息
            * @param [in ] getlayoutinfo
            *        获取分屏信息会控结构
            * @return return 0 if success or an error code
            */
			virtual int  ReqSRLayoutInfo(const SRConferenceCtrlReqLayoutInfo & getlayoutinfo) = 0;

			/**
			* 请求会议状态信息， 这个不限于主持人， 其他客户端也要请求会议信息
			* @param [in ] getconfstatus
			*        获取会议状态会控结构
			* @return return 0 if success or an error code
			*/
			virtual int  ReqSRConfStatus(const SRConferenceCtrlReqConfStatus & getconfstatus) = 0;

			
			/**
			* 主持人会控者控制会议强制静音， 其他终端自己不能打开自己的音频需要主持人解除强制静音
			* @param [in ] forcemuteinfo
			*        强制静音会控结构
			* @return return 0 if success or an error code
			*/
			virtual int  ForceMuteAudio(const SRConferenceCtrlForceMute & forcemuteinfo) = 0;

			/**
			* 增加滚动字幕
			* @param [in ] addsubtitle
			*        增加字幕会控结构
			* @return return 0 if success or an error code
			*/
			virtual int  AddSubtitle(const SRConferenceCtrlAddSubtitle & addsubtitle) = 0;

			/**
			* 停止滚动字幕
			* @param [in ] stopsubtitle
			*        停止字幕会控结构
			* @return return 0 if success or an error code
			*/
			virtual int  StopSubtitle(const SRConferenceCtrlStopSubtitle & stopsubtitle) = 0;


			/**
			* 显示会场名
			* @param [in ] displaytername
			*        显示会场名会控结构
			* @return return 0 if success or an error code
			*/
			virtual int  DisplayTername(const SRConferenceCtrlDisplayTername & displaytername) = 0;

			/**
			* 隐藏会场名
			* @param [in ] hidetername
			*        隐藏会场名会控结构
			* @return return 0 if success or an error code
			*/
			virtual int  HideTername(const SRConferenceCtrlHideTername & hidetername) = 0;

	
			/**
			* 会控者修改会议密码
			* @param [in ] changeconfcryptkey
			*        会控者修改会议密码会控结构
			* @return return 0 if success or an error code
			*/
			virtual int  ChangeConfCryptoKey(const SRConferenceCtrlChangeConfCryptoKey & changeconfcryptkey) = 0;

			
			/**
			* 会控者设置标准终端观看方式
			* @param [in ] changeconfcryptkey
			*        会控者修改会议密码会控结构
			* @return return 0 if success or an error code
			*/
			virtual int  SetStdTerSeeingStyle(const SRConferenceCtrlSetStdTerSeeingStyle & setterseeingstyle) = 0;

			/**
			* 会控者设置白名单
			* @param [in ] setwhitelist
			*        会控者设置白名单会控结构
			* @return return 0 if success or an error code
			*/
			virtual int  SetWhitelist(const SRConferenceCtrlSetWhitelist & setwhitelist) = 0;

			/**
			* 增加参会人， 增加参会人后会增加到数据库， mc和会控都会更新
			* @param [in ] participants
			*        增加参会人会控结构
			* @return return 0 if success or an error code
			*/
			virtual int  AddParticipants(const SRConferenceCtrlAddParticipants & add_participants) = 0;

			/**
			* 删除参会人, 既可以删除在会的，也可以删除不在会的， 删除参会人后会删除数据库
			* @param [in ] participants
			*        删除参会人会控结构
			* @return return 0 if success or an error code
			*/
			virtual int  DelParticipants(const SRConferenceCtrlDelParticipants & del_participants) = 0;

			/**
			* 邀请参会人， 既可以邀请sr终端， 也可以邀请第三方终端比如323/sip等
			* @param [in ] participants
			*        邀请参会人会控结构
			* @return return 0 if success or an error code
			*/
			virtual int  InvitParticipants(const SRConferenceCtrlInvitParticipants & invit_participants) = 0;


			/**
			*开始会议录制
			* @param [in ] start_meeting_record
			*       开始会议录制会控结构
			* @return return 0 if success or an error code
			*/
			virtual int StartMeetingRecord(SRConferenceCtrlStartMeetingRecord & start_meeting_record) = 0;

			/**
			*停止录制
			* @param [in ] stop_meeting_record
			*       停止会议录制会控结构
			* @return return 0 if success or an error code
			*/
			virtual int StopMeetingRecord(SRConferenceCtrlStopMeetingRecord & stop_meeting_record) = 0;


			/**
			*开始会议直播
			* @param [in ] start_meeting_live
			*       开始会议直播会控结构
			* @return return 0 if success or an error code
			*/
			virtual int StartMeetingLive(SRConferenceCtrlStartMeetingLive & start_meeting_live) = 0;

			/**
			*停止会议直播
			* @param [in ] stop_meeting_live
			*       停止会议直播会控结构
			* @return return 0 if success or an error code
			*/
			virtual int StopMeetingLive(SRConferenceCtrlStopMeetingLive & stop_meeting_live) = 0;

			/**
			*修改会议直播设置
			* @param [in ] stop_meeting_live
			*       停止会议直播会控结构
			* @return return 0 if success or an error code
			*/
			virtual int ChangeLiveSetting(SRConferenceCtrlChangeLiveSetting & change_meeting_setting) = 0;

			/**
			*投屏终端类型转换
			* @param [in ] transfer_specialtype
			*       投屏终端类型转换 结构
			* @return return 0 if success or an error code
			*/
			virtual int TransferSpecialtype(SRConferenceCtrlTransferSpecialtype &transfer_specialtype) = 0;
        };

        class  ISRRtcEngineSystemMessageInfo
        {
        public:
            virtual ~ISRRtcEngineSystemMessageInfo() {}

            /**
            *获取网卡信息 WIN32
            * @param [in out ] info
            *           网卡信息
            * @return return 0 if success or an error code
            */
            virtual int  GetAdaptInfo(SRLocalAdaptInfo & info) = 0;


            /**
            *获取apm认证mac信息 针对android
            * @param []
            * @param    apm认证需要的mac消息
            * @return return 0 if success or an error code
            */
            virtual std::string  GetApmInfo() = 0;


            /**
            *获取apm认证结构信息
            * @param [in out ] info
            *           apm认证需要的结构消息
            * @return return 0 if success or an error code
            */
            virtual int  GetApmTypeStructInfo(SRUseApmType & info) = 0;


            /**
            *设置用户需要设置的信息给sdk
            * @param [in] param
            *           cpu设置信息
			*           网络类型等
            * @return return 0 if success or an error code
            */
			virtual int SetUsrNotify(const SRUserSetParam &param) = 0;


			/**
			*可单独获取当前的网络状况
			* @param [out] status      
			*           当前的网络状态
			* @return return 0 if success or an error code
			*/
			virtual int GetNetWorkStatusNotify(NetWorkStatus &status) = 0;

        };

        class SRRtcEngineInitContext
        {
        public:
            ISRRtcEngineDeviceEventCallback                             * event_device_callback;
            ISRRtcEngineConferenceControlEventCallback          * event_conference_control_callback;
            ISRRtcEngineConferenceEventCallback                      * event_conference_callback;
            ISRRtcEngineDataEventCallback                                 * event_data_callback;

			//是否使用log
			bool                                    uselog;
			//是否使用硬件解码
			bool                                    useHardDecode;

			//当前的平台类型
			SREnginePlatFormType       platform_type;

            std::string logFilePath;
            std::string confFilePath;
            SRRtcEngineInitContext()
                : event_device_callback(NULL)
                , event_conference_control_callback(NULL)
                , event_conference_callback(NULL)
                , event_data_callback(NULL)
				, uselog(true)
				, useHardDecode(false)
				, platform_type(SR_PLATFORM_TYPE_NONE)
                , logFilePath("")
                , confFilePath("")
            {
            }
            ~SRRtcEngineInitContext()
            {
                event_device_callback = NULL;
                event_conference_control_callback = NULL;
                event_conference_callback = NULL;
                event_data_callback = NULL;
                logFilePath.clear();
                confFilePath.clear();
            }
        };
        class SRRtcEngineJoinConfContext
        {
        public:
            //mc info
            McInfo   *mcinfo;
            //user info
            UserInfo  *userinfo;
            //conference info
            ConfInfo  *confinfo;

            //relay server 192.168.1.1:8000/192.168.1.2:8003
            std::string  relay_server_addrs;

			//当前系统所有设备(mc)负载信息(AES密文),终端入会时restful获取该密文信息透传给mc
			std::string systemload; 

            //set local view
            view_t  local_wnd;

            //set audio mute
            bool   ismuted;

            //set camera on
            bool   iscameraon;

            //term type
            SREngineTermType termtype;

            //come from type
            SREngineFromType  fromtype;

			//set video camera or encode
			VideoAndAudioParameter video_audio_parameter;

            SRRtcEngineJoinConfContext()
                : mcinfo(NULL)
                , userinfo(NULL)
                , confinfo(NULL)
                , relay_server_addrs("")
				, systemload("")
                , local_wnd(NULL)
                , ismuted(false)
                , iscameraon(false)
#if defined(_WIN32) || defined(OS_LINUX)
				, termtype(SR_TERM_TYPE_PC)
#else
				, termtype(SR_TERM_TYPE_PHONE)
#endif
				, fromtype(SR_FROMTERM_SUIRUI_PLATFORM)
            {}
        };

        class ISRRtcEngineConference
        {
        public:

            virtual ~ISRRtcEngineConference() {}
            //init
            /**
            * initialize the engine
            * @param [in] context
            *        the RTC engine context
            * @return return 0 if success or an error code
            */
            virtual int Initialize(const SRRtcEngineInitContext & init_context) = 0;

            //get interface
            /**
            * get interface ISRCameraDeviceManager
            * @param [in] none
            * @return return ISRCameraDeviceManager  ptr
            */
            virtual suirui::rtc::ISRVideoDeviceManager* GetVideoDeviceManagerInterface() = 0;

            /**
            * get interface ISRAudioDeviceManager
            * @param [in] none
            * @return return ISRAudioDeviceManager  ptr
            */
            virtual suirui::rtc::ISRAudioDeviceManager* GetAudioDeviceManagerInterface() = 0;

            /**
            * get interface ISRRtcEngineConferenceControl
            * @param [in] none
            * @return return ISRRtcEngineConferenceControl  ptr
            */
            virtual suirui::rtc::ISRRtcEngineConferenceControl* GetConferenceControlInterface() = 0;

            /**
            * get interface ISRRtcEngineSystemMessageInfo
            * @param [in] none
            * @return return ISRRtcEngineSystemMessageInfo  ptr
            */
            virtual suirui::rtc::ISRRtcEngineSystemMessageInfo* GetSystemMessageInfoInterface() = 0;


            /**
            * get the version information of the SDK
            * @param [in out] buildversion
            *        the build version
            * @return return 0 if success or an error code
            */
            virtual int  GetVersion(char build_version[SR_MAX_BUFFER_ID_LENGTH]) = 0;



            /**
            * 设置密钥模式内容
            * @param [in ] Mode
            *                   模式
            * @return return 0 if success or an error code
            */
            virtual int SetCryptionContent(const CryptionContent &content) = 0;


			/**
			* 会中可以动态设置编码的最大能力， 这个要根据自己的摄像头采集能力去设置
			* @param [in ] parameter
			*                   视频编码参数
			* @return return 0 if success or an error code
			*/
			virtual int SetVideoEncodeParameter(const VideoAndAudioParameter &parameter) = 0;

            /**
            * 设置APM认证key
            * @param [in ] key
            *                   key值
            * @return return 0 if success or an error code
            *     错误的时候需要重新认证， 不能入会
            */
            virtual int SetApmKeyContent(const std::string & key) = 0;

            //会中需要key时设置用此接口
            virtual int SetApmKeyInConferenceContent(const std::string & key) = 0;

            //jonin conf
            /**
            *加入会议
            * @param [in ] joinconf_context
            *        会议信息
            * @return return 0 if success or an error code
            */
            virtual int ReqJoinConf(const SRRtcEngineJoinConfContext  &joinconf_context) = 0;


            /**
            *退出会议
            @param [in ] exit_reason
            *        退会原因
            * @return return 0 if success or an error code
            */
            virtual int ExitConf(const char * exit_reason) = 0;


            //send video
            /**
            *往sdk送帧
            * @param [in ] frame
            *        帧数据
            *
            * @return return 0 if success or an error code
            */
            virtual  int InPutVideoRawStream(SR_VIDEO_STREAM_TYPE type, VideoFrame & frame) = 0;



            //获取列表
            /**
            *获取参会人列表
            * @param [in ] none
            *
            * @return return 0 if success or an error code
            */
            virtual int EnableReqConfTermList() = 0;


            //select video
            /**
            *选取要选看的与会者
            * @param [in ] mul_streams
            *        选看结构体链表,需要多个流都要加入到选看链表中
            * @return return 0 if success or an error code
            */
            virtual int SelectVideo(list<RequestVideoParam>& mul_streams) = 0;

            /**
            * 开启共享
            * @param [in ] capture_wnd
            *        采集的窗口
            **
            * @return return 0 if success or an error code
            */
            virtual int StartSendDualVideo(view_t capture_wnd) = 0;


            /**
            * 共享期间切换采集窗口
            * @param [in ] capture_wnd
            *        采集的窗口
            **
            * @return return 0 if success or an error code
            */
            virtual int SetSendDualVideo(view_t capture_wnd) = 0;

            /**
            * 停止共享
            * @param [in ] none
            *
            * @return return 0 if success or an error code
            */
            virtual int StopSendDualVideo() = 0;


            //目前这两个接口暂时没有实现， 后续完善
            virtual int PauseSendDualVideo() = 0;
            virtual int ResumeSendDualVideo() = 0;


            /**
            * 回复桌面共享申请者， 这个是在对端调用StartSendDualVideo之后， 第一个共享者收到回调OnReqAssistVideoProxy之后的动作
            * @param [in ] who_want_send_dualvideo_stermid
            *                   请求共享端ID
            * @param [in ] agree
            *                   是否同意
            * @param [in ] disagree_reason
            *                   拒绝原因
            * @return return 0 if success or an error code
            */
            virtual int RspSendDualVideoProxy(const int want_send_dualvideo_stermid, const bool agree, const char* disagree_reason) = 0;

            /**
            * 桌面共享其他客户端添加备注
            * @param [in ] attr
            *                   备注结构
            * @return return 0 if success or an error code
            */
            virtual int AddScreenLabel(SRScreenLableAttr & attr) = 0;

            /**
            * 主持人发送消息给其他人
            * @param [in ] to_termid_list
            *                   给哪些终端发的列表, 为空代表全体发送
            * @param [in ] message
            *                   发送消息内容
            * @return return 0 if success or an error code
            */
            virtual int SendConfMessage(std::list<int> & to_termid_list, const std::string& message) = 0;

			/**
			* 发送IM消息
			* @param [in ] to_termid_list
			*                   给哪些终端发的列表, 为空代表全体发送
			* @param [in ] message
			*                   发送消息内容
			* @return return 0 if success or an error code
			*/
			virtual int SendIMMessage(std::list<int> & to_termid_list, const std::string& message) = 0;

            /**
            * 开启预览功能
            @param [in ] wnds
            *                    窗体结构链表，如果需要多个窗体需加入到链表当中
            * @return return 0 if success or an error code
            */

            virtual int StartVideoPreview(list<view_t>& wnds) = 0;
            virtual int StopVideoPreview() = 0;


            /**
            * 要禁止哪个终端视频， 对于主持人可以禁用其他人， 不是主持人只能禁自己的视频
            * @param [in ]
            * @return return 0 if success or an error code
            */
            virtual int MuteVideo(const int mute_stermid) = 0;
            virtual  int UnMuteVideo(const int unmute_stermid) = 0;


            /**
            * 要禁止那个终端静音， 对于主持人可以禁用其他人， 不是主持人只能禁自己的声音
            * @param [in ] mute_stermid
            *                    禁止的终端stermid

            * @return return 0 if success or an error code
            */
            virtual int MuteAudio(const int mute_stermid) = 0;
            virtual int UnMuteAudio(const int unmute_stermid) = 0;


			/**
			* 要禁止那个终端静音播放，对于主持人可以禁用其他人， 不是主持人只能禁自己的声音播放
			* @param [in ] mute_stermid
			*                    禁止的终端stermid

			* @return return 0 if success or an error code
			*/
			virtual int MutePlayOutAudio(const int mute_stermid) = 0;
			virtual int UnMutePlayOutAudio(const int unmute_stermid) = 0;

            /**
            * 使能获取当前收到流统计信息状态, 传0 代表停止统计
            * @param [in ] interval
            *                    事件间隔 单位 毫秒 5000ms --->5s
            * @return return 0 if success or an error code
            */
            virtual int EnableRecvStreamInfoIndication(int interval) = 0;
            /**
            * 使能获取当前发送统计信息状态, 传0 代表停止统计
            * @param [in ] interval
            *                    事件间隔 单位 毫秒 5000ms --->5s
            * @return return 0 if success or an error code
            */
            virtual int EnableSendStreamInfoIndication(int interval) = 0;

            /**
            *通知其它客户端，我有电话打进来，针对手机
            * @param [in ]
            * @return return 0 if success or an error code
            */
            virtual int EnableTelphoneCallComing() = 0;
            virtual int DisableTelphoneCallComing() = 0;


            /**
            *给客户端自定义自己的传递状态的方式
            * @param [in ] sta_class sta_sub_class status_str
            *       自定义结构
            * @return return 0 if success or an error code
            */
            virtual int RunningStatusNotify(const int sta_class, const int sta_sub_class, const char * status_str) = 0;



            /**
            *入会后客户端可以开启本地声音代替麦克风采集的声音
            * @param [in ] wav_name
            *       声音文件
            * @return return 0 if success or an error code
            */
            virtual int StartPlayingFileAsMicrophone(const char* wav_name) = 0;
            virtual  int StopPlayingFileAsMicrophone() = 0;


            /**
            *设置音频播放模式 only by android
            * @param [in ] mode
            *        mode:   0:听筒模式   1:外音模式
            * @return return 0 if success or an error code
            */
            virtual int SetSpeakerMode(int mode) = 0;


            /**
            *接收命令输入
            * @param [in ] argc argv
            *       类似命令行输入
            * @return return 0 if success or an error code
            */
            virtual int SetUserCmdToEngine(int argc, char * argv[]) = 0;

            /**
            *通知网络发生变化
            * @param
            * @return return 0 if success or an error code
            */
            virtual int NotifyNetworkChanged() = 0;
        };

    }//rtc


} //suirui



/**
* create the RTC engine object
* @param [in out ] engine
*        the pointer ISRRtcEngineConference
* @return return 0 if success or an error code
*/
SUIRUI_RTC_ENGINE_API int  CreateSRRtcEngine(void** engine);

/**
* delete the RTC engine object and return the pointer
*/
SUIRUI_RTC_ENGINE_API  int DeleteSRRtcEngine(void** engine);



#endif //SUIRUI_RTC_ENGINE_API_H
