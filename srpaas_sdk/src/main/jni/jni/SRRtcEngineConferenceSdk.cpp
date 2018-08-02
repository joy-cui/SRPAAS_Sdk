#include "SRRtcEngineConferenceSdk.h"
#include "SREngineDataCallback.h"
#include "SREngineDeviceCallback.h"
#include "SREngineConferenceCallback.h"
#include "SREngineConferenceControlCallback.h"
#include <android/log.h>
#include "Log.h"

namespace SR {
//在此处初始化
    SRRtcEngineConferenceSdk *SRRtcEngineConferenceSdk::pInstance = new SRRtcEngineConferenceSdk();

    SRRtcEngineConferenceSdk *SRRtcEngineConferenceSdk::instance() {

//        if (!pInstance) {
//            pInstance = new SRRtcEngineConferenceSdk;
//        }

        return pInstance;
    }

/**
 * 初始化SDK
 */
    int SRRtcEngineConferenceSdk::initSrEnginConferenceSdk(bool isopensdklog,bool isH264Decode,int platformType) {
#if defined(LOG_JNI)
        Log("SRRtcEngineConferenceSdk:initSrEnginConferenceSdk.....");
#endif
        int ret = CreateSRRtcEngine((void **) &m_pSRConferenceEngine);
#if defined(LOG_JNI)
        Log("SRRtcEngineConferenceSdk:CreateSRRtcEngine.....ret=%d", ret);
#endif
        if (ret == 0) {
            SRRtcEngineInitContext context;
            context.event_data_callback = m_pDataCallback;
            context.event_device_callback = m_pDeviceCallback;
            context.event_conference_callback = m_pConferenceCallback;
            context.event_conference_control_callback = m_pConferenceControlCallback;
            context.uselog = isopensdklog;
            context.useHardDecode=isH264Decode;
            context.platform_type=(SREnginePlatFormType)platformType;
            ret = m_pSRConferenceEngine->Initialize(context);
#if defined(LOG_JNI)
            Log("SRRtcEngineConferenceSdk:Initialize.....ret=%d", ret);
#endif
            if (ret != 0) {
                //Init SREngine Failed

            }
            else {
                // "Init srEngine Successed";
                m_pSRConferenceEngineControl = ConferenceControlInterface();
                m_pSRRtcEngineSystemMessageInfo = SystemMessageInfoInterface();
                m_pISRAudioDeviceManager = AudioDeviceManager();
                Log(":m_pSRConferenceEngineControl..Init srEngine Successed.");
            }
        }
        else {
            //Creat SREngine Failed
        }
        return ret;
    }

    SRRtcEngineConferenceSdk::SRRtcEngineConferenceSdk() :
            m_pSRConferenceEngine(NULL),
            m_pDataCallback(new SREngineDataCallback()),
            m_pDeviceCallback(new SREngineDeviceCallback()),
            m_pConferenceCallback(new SREngineConferenceCallback()),
            m_pConferenceControlCallback(new SREngineConferenceControlCallback()) {
    }

    int SRRtcEngineConferenceSdk::UnInitSDK() {
        int ret = DeleteSRRtcEngine((void **) &m_pSRConferenceEngine);
        if (ret != 0) {
            // "DeleteSRRtcEngine failed:" ;
        }
        delete m_pDataCallback;
        delete m_pDeviceCallback;
        delete m_pConferenceCallback;
        delete m_pConferenceControlCallback;
        delete m_pSRConferenceEngineControl;
        delete m_pSRRtcEngineSystemMessageInfo;
        delete m_pISRAudioDeviceManager;
        return ret;
    }

    SRRtcEngineConferenceSdk::~SRRtcEngineConferenceSdk() {
        int ret = DeleteSRRtcEngine((void **) &m_pSRConferenceEngine);
        if (ret != 0) {
            // "DeleteSRRtcEngine failed:" ;
        }
        delete m_pDataCallback;
        delete m_pDeviceCallback;
        delete m_pConferenceCallback;
        delete m_pConferenceControlCallback;
        delete m_pSRConferenceEngineControl;
        delete m_pSRRtcEngineSystemMessageInfo;
        delete m_pISRAudioDeviceManager;
        return;
    }


    ISRVideoDeviceManager *SRRtcEngineConferenceSdk::VideoDeviceManager() const {
        return m_pSRConferenceEngine->GetVideoDeviceManagerInterface();
    }

    ISRAudioDeviceManager *SRRtcEngineConferenceSdk::AudioDeviceManager() const {
        return m_pSRConferenceEngine->GetAudioDeviceManagerInterface();
    }

    ISRRtcEngineSystemMessageInfo *SRRtcEngineConferenceSdk::SystemMessageInfoInterface() {
        return m_pSRConferenceEngine->GetSystemMessageInfoInterface();
    }

    ISRRtcEngineConferenceControl *SRRtcEngineConferenceSdk::ConferenceControlInterface() const {
        return m_pSRConferenceEngine->GetConferenceControlInterface();
    }

/**
 * 获取版本号
 */
    int SRRtcEngineConferenceSdk::GetVersion(char build_version[]) {
        return m_pSRConferenceEngine->GetVersion(build_version);
    }

    int SRRtcEngineConferenceSdk::SetCryptionContent(CryptionContent &content) {
        return m_pSRConferenceEngine->SetCryptionContent(content);
    }

    int SRRtcEngineConferenceSdk::ReqJoinConf(const SRRtcEngineJoinConfContext &joinconf_context) {
        Log("SRSdkJni:ReqJoinConf...%d____confid:%llu____",
            joinconf_context.userinfo->termUId,
            joinconf_context.confinfo->conf_id);
        return m_pSRConferenceEngine->ReqJoinConf(joinconf_context);
    }

    int SRRtcEngineConferenceSdk::ExitConf(const char *exit_reason) {
        Log("SRSdkJni:ExitConf......");
        return m_pSRConferenceEngine->ExitConf(exit_reason);
    }

    int SRRtcEngineConferenceSdk::InPutVideoRawStream(SR_VIDEO_STREAM_TYPE type,
                                                      VideoFrame &frame) {
//        Log(":SRRtcEngineConferenceSdk...%d____confid:%llu____");
        return m_pSRConferenceEngine->InPutVideoRawStream(type, frame);
    }

    int SRRtcEngineConferenceSdk::EnableReqConfTermList() {
        Log("SRSdkJni:EnableReqConfTermList......");
        return m_pSRConferenceEngine->EnableReqConfTermList();
    }

    int SRRtcEngineConferenceSdk::SelectVideo(list <RequestVideoParam> mul_streams) {
        return m_pSRConferenceEngine->SelectVideo(mul_streams);
    }

    int SRRtcEngineConferenceSdk::StartSendDualVideo(view_t capture_wnd) {
        return m_pSRConferenceEngine->StartSendDualVideo(capture_wnd);
    }

    int SRRtcEngineConferenceSdk::SetSendDualVideo(view_t capture_wnd) {
        return m_pSRConferenceEngine->SetSendDualVideo(capture_wnd);
    }

    int SRRtcEngineConferenceSdk::StopSendDualVideo() {
        return m_pSRConferenceEngine->StopSendDualVideo();
    }

    int SRRtcEngineConferenceSdk::PauseSendDualVideo() {
        return m_pSRConferenceEngine->PauseSendDualVideo();
    }

    int SRRtcEngineConferenceSdk::ResumeSendDualVideo() {
        return m_pSRConferenceEngine->ResumeSendDualVideo();
    }

    int SRRtcEngineConferenceSdk::RspSendDualVideoProxy(const int want_send_dualvideo_stermid,
                                                        const bool agree,
                                                        const char *disagree_reason) {
        return m_pSRConferenceEngine->RspSendDualVideoProxy(want_send_dualvideo_stermid, agree,
                                                            disagree_reason);
    }

    int SRRtcEngineConferenceSdk::AddScreenLabel(SRScreenLableAttr &attr) {
        return m_pSRConferenceEngine->AddScreenLabel(attr);
    }

    int SRRtcEngineConferenceSdk::StartVideoPreview(list <view_t> wnds) {
        return m_pSRConferenceEngine->StartVideoPreview(wnds);
    }

    int SRRtcEngineConferenceSdk::StopVideoPreview() {
        return m_pSRConferenceEngine->StopVideoPreview();
    }

//    int SRRtcEngineConferenceSdk::RunningChgAudioCaptureDevice(const char *audio_input_name) {
//        return m_pSRConferenceEngine->RunningChgAudioCaptureDevice(audio_input_name);
//    }

//    int SRRtcEngineConferenceSdk::RunningChgAudioOutputDevice(const char *audio_output_name) {
//        return m_pSRConferenceEngine->RunningChgAudioOutputDevice(audio_output_name);
//    }

//    int SRRtcEngineConferenceSdk::RunningChgCameraCaptureDevice(const char *camera_name) {
//        return m_pSRConferenceEngine->RunningChgCameraCaptureDevice(camera_name);
//    }

    int SRRtcEngineConferenceSdk::SetCameraOn(const int stermid, bool on) {
        if (!on) {
            return m_pSRConferenceEngine->MuteVideo(stermid);
        }
        else {
            return m_pSRConferenceEngine->UnMuteVideo(stermid);
        }
    }

    int SRRtcEngineConferenceSdk::SetAudioMute(const int stermid, bool on) {
        if (!on) {
            return m_pSRConferenceEngine->UnMuteAudio(stermid);
        }
        else {
            return m_pSRConferenceEngine->MuteAudio(stermid);
        }
    }

    int SRRtcEngineConferenceSdk::EnableRecvStreamInfoIndication(int interval) {
        return m_pSRConferenceEngine->EnableRecvStreamInfoIndication(interval);
    }

    int SRRtcEngineConferenceSdk::EnableSendStreamInfoIndication(int interval) {
        return m_pSRConferenceEngine->EnableSendStreamInfoIndication(interval);
    }

    int SRRtcEngineConferenceSdk::EnableTelphoneCallComing() {
        return m_pSRConferenceEngine->EnableTelphoneCallComing();
    }

    int SRRtcEngineConferenceSdk::DisableTelphoneCallComing() {
        return m_pSRConferenceEngine->DisableTelphoneCallComing();
    }

    int SRRtcEngineConferenceSdk::RunningStatusNotify(const int sta_class, const int sta_sub_class,
                                                      const char *status_str) {
        return m_pSRConferenceEngine->RunningStatusNotify(sta_class, sta_sub_class, status_str);
    }

    int SRRtcEngineConferenceSdk::StartPlayingFileAsMicrophone(const char *wav_name) {
        return m_pSRConferenceEngine->StartPlayingFileAsMicrophone(wav_name);
    }

    int SRRtcEngineConferenceSdk::StopPlayingFileAsMicrophone() {
        return m_pSRConferenceEngine->StopPlayingFileAsMicrophone();
    }

    int SRRtcEngineConferenceSdk::SetUserCmdToEngine(int argc, char *argv[]) {
        return m_pSRConferenceEngine->SetUserCmdToEngine(argc, argv);
    }

    int SRRtcEngineConferenceSdk::NotifyNetworkChanged() {
        return m_pSRConferenceEngine->NotifyNetworkChanged();
    }

    int SRRtcEngineConferenceSdk::SetSpeakerMode(int mode) {
        return m_pSRConferenceEngine->SetSpeakerMode(mode);
    }

    int SRRtcEngineConferenceSdk::SetApmKeyContentSDK(const std::string &key) {
        return m_pSRConferenceEngine->SetApmKeyContent(key);
    }
    int SRRtcEngineConferenceSdk::SendIMMessage(std::list<int> &to_termid_list, const std::string &message) {
        return m_pSRConferenceEngine->SendIMMessage(to_termid_list,message);
    }
    /*************************ConferenceControl*************************************/
    int SRRtcEngineConferenceSdk::ChairEndConf() {
        Log("SRSdkJni:ChairEndConf......");
        return m_pSRConferenceEngineControl->ChairEndConf();
    }

    int SRRtcEngineConferenceSdk::MuteAudioAllTerm(bool on) {
        return m_pSRConferenceEngineControl->MuteAudioAllTerm(on);
    }

    int SRRtcEngineConferenceSdk::DropTerm(const int drop_stermid) {
        return m_pSRConferenceEngineControl->DropTerm(drop_stermid);
    }

    int SRRtcEngineConferenceSdk::MasterTransfer(const int new_stermid) {
        return m_pSRConferenceEngineControl->MasterTransfer(new_stermid);
    }

    int SRRtcEngineConferenceSdk::LockVideo(const int lock_stermid) {
        return m_pSRConferenceEngineControl->LockVideo(lock_stermid);
    }

    int SRRtcEngineConferenceSdk::UnLockVideo(const int unlock_stermid) {
        return m_pSRConferenceEngineControl->UnLockVideo(unlock_stermid);
    }

    int SRRtcEngineConferenceSdk::ChairEndDataShare() {
        return m_pSRConferenceEngineControl->ChairEndDataShare();
    }

    int SRRtcEngineConferenceSdk::LockConf(const bool islock) {
        return m_pSRConferenceEngineControl->LockConf(islock);
    }

    int SRRtcEngineConferenceSdk::HandUp(const bool handup) {
        return m_pSRConferenceEngineControl->HandUp(handup);
    }

    int SRRtcEngineConferenceSdk::ChangeTermName(const char *new_name) {
        return m_pSRConferenceEngineControl->ChangeTermName(new_name);
    }

    int SRRtcEngineConferenceSdk::ForceMuteAudio(const SRConferenceCtrlForceMute &forcemuteinfo) {
        return m_pSRConferenceEngineControl->ForceMuteAudio(forcemuteinfo);
    }

    int SRRtcEngineConferenceSdk::ReqSRConfStatus(const SRConferenceCtrlReqConfStatus &getconfstatus){
        return m_pSRConferenceEngineControl->ReqSRConfStatus(getconfstatus);
    }

    int SRRtcEngineConferenceSdk::DelParticipants(const SRConferenceCtrlDelParticipants &del_participants){
        return m_pSRConferenceEngineControl->DelParticipants(del_participants);
    }

    int SRRtcEngineConferenceSdk::StartMeetingRecord(
            SRConferenceCtrlStartMeetingRecord &start_meeting_record) {
        return m_pSRConferenceEngineControl->StartMeetingRecord(start_meeting_record);
    }

    int SRRtcEngineConferenceSdk::StopMeetingRecord(
            SRConferenceCtrlStopMeetingRecord &stop_meeting_record) {
        return m_pSRConferenceEngineControl->StopMeetingRecord(stop_meeting_record);
    }

    int SRRtcEngineConferenceSdk::StartMeetingLive(
            SRConferenceCtrlStartMeetingLive &start_meeting_live) {
        Log("SRSdkJni...StartMeetingLive(sdk11)");
        return m_pSRConferenceEngineControl->StartMeetingLive(start_meeting_live);
    }

    int SRRtcEngineConferenceSdk::StopMeetingLive(
            SRConferenceCtrlStopMeetingLive &stop_meeting_live) {
        return m_pSRConferenceEngineControl->StopMeetingLive(stop_meeting_live);
    }

    int SRRtcEngineConferenceSdk::ChangeLiveSetting(
            SRConferenceCtrlChangeLiveSetting &change_meeting_setting) {
        return m_pSRConferenceEngineControl->ChangeLiveSetting(change_meeting_setting);
    }
    /**************************************m_pSRRtcEngineSystemMessageInfo***************************/
    std::string SRRtcEngineConferenceSdk::GetApmInfoSDK() {
        return m_pSRRtcEngineSystemMessageInfo->GetApmInfo();
    }
    int SRRtcEngineConferenceSdk::SetUsrNotify(const SRUserSetParam &param) {
        return m_pSRRtcEngineSystemMessageInfo->SetUsrNotify(param);
    }

    int SRRtcEngineConferenceSdk::GetNetWorkStatusNotify(NetWorkStatus &status) {
        return m_pSRRtcEngineSystemMessageInfo->GetNetWorkStatusNotify(status);
    }

    /*******************************************ISRAudioDeviceManager********************************/
    int SRRtcEngineConferenceSdk::SetOutputDeviceVolume(int volume) {
        return m_pISRAudioDeviceManager->SetOutputDeviceVolume(volume);
    }

    int SRRtcEngineConferenceSdk::ResetAudioDevice() {
        return m_pISRAudioDeviceManager->ResetAudioDevice();
    }
}


