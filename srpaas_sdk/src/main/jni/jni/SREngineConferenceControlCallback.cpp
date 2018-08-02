#include "SREngineConferenceControlCallback.h"
#include <android/log.h>
#include "Log.h"
#include "SRSdkJni.h"

SREngineConferenceControlCallback::SREngineConferenceControlCallback() :
        ISRRtcEngineConferenceControlEventCallback() { }

/**
    * 某个终端举手回调
    * @param [in] handup_stermid
    *           举手终端的termid
    * @param [in] is_handup
    *           是否举手
    */
void SREngineConferenceControlCallback::OnTermHandUp(const int handup_stermid,
                                                     const bool is_handup) {
    OnTermHandUpCallBack_JNI(handup_stermid, is_handup);
}

/**
* 新的主持人收到回调
* @param [in] chair_stermid
*           新的主持人的stermid
*/
void SREngineConferenceControlCallback::OnMasterTransfer(const int chair_stermid) {
    OnMasterTransferCallBack_JNI(chair_stermid);
}

/**
* 其它终端收到主持人的静音回调
* @param [in] ismute
*           是否静音
*/
void SREngineConferenceControlCallback::OnMuteAudioAllTermNotify(const bool ismute) {
    onMuteAudioAllTermNotifyCallBack_JNI(ismute);
}

/**
* 主持人指定会议室内其它人看某一个客户端的视频回调
* @param [in] lock_stermid
*           指定终端的sterm id
*/
void SREngineConferenceControlCallback::OnLockVideo(const int lock_stermid) {
    onLockOrUnLockVideoCallBack_JNI(lock_stermid, true);
}

/**
* 主持人解除指定会议室内其它人看某一个客户端的视频回调
* @param [in] unlock_stermid
*           指定终端的sterm id
*/
void SREngineConferenceControlCallback::OnUnLockVideo(const int unlock_stermid) {
    onLockOrUnLockVideoCallBack_JNI(unlock_stermid, false);
}

/**
* 主持人结束会议回调
* @param [in] chair_stermid
*           主持人的chair_stermid
* @param [in] chair_name
*           主持人的名字
*/
void SREngineConferenceControlCallback::OnIndChairEndConf(const int chair_stermid,
                                                          const char *chair_name) {
    OnIndChairEndConfCallBack_JNI(chair_stermid, chair_name);
}

/**
* 主持人结束共享回调
* @param [in] chair_stermid
*           主持人的chair_stermid
* @param [in] chair_name
*           主持人的名字
*/
void SREngineConferenceControlCallback::OnIndChairEndDataShare(const int chair_stermid,
                                                               const char *chair_name) {
    OnIndChairEndDataShareCallBack_JNI(chair_stermid, chair_name);
}

/**
* 修改终端名称
* @param [in] changeterid
*           要改变终端的termid
* @param [in] term_name
*           要改变的名称
*/
void SREngineConferenceControlCallback::OnTermChangeName(const int change_stermid,
                                                         const char *term_name) {
    OnTermChangeNameCallBack_JNI(change_stermid, term_name);
}

/**
  * 主持人发出强制静音，其他客户端收到回调
  * 自己要禁用自己的声音，不允许打开，只有向主持人发起请求handup
  @param [in] isforcemute
  *           是否强制静音 true 代表强制静音，false代表解除强制静音
  */
void SREngineConferenceControlCallback::OnConfForceMute(const bool isforcemute) {
    Log("SRSdkJni..OnConfForceMute....isok:%d", isforcemute);
    OnConfForceMuteCallBack_JNI(isforcemute);
}

/**
 * 获取会议的信息
 */
void SREngineConferenceControlCallback::OnRspConfStatus(const bool isok, ConfStatus &confstatus,
                                                        const SRConferenceAbnormal &error) {
    OnRspConfStatusCallBack_JNI(isok, confstatus, error);
}

/**
* 终端收主持人开启会议录制停止会议录制
* @param [in] recstate
*          0-停止录制,1-开始录制
*/
void SREngineConferenceControlCallback::OnIndTerCRSRecState(const int recstate,
                                                            const SRConferenceAbnormal &error) {
    Log("SRSdkJni..OnIndTerCRSRecState....recstate:%d", recstate);
    OnIndTerCRSRecStateCallBack_JNI(recstate, error);
}

/**
* 参会人变化同步更新到终端 增加
* @param [in] paticipants
*           参会人列表
*/
void SREngineConferenceControlCallback::OnUpdateAddPaticipants(std::list <TermInfo> &paticipants) {
    Log("SRSdkJni..OnUpdateAddPaticipants....");
    OnUpdateAddPaticipantsCallBack_JNI(paticipants);
}

/**
* 参会人变化同步更新到终端 删除
* @param [in] paticipants
*           参会人列表
*/
void SREngineConferenceControlCallback::OnUpdateDelPaticipants(std::list <TermInfo> &paticipants) {
    Log("SRSdkJni..OnUpdateDelPaticipants....");
    OnUpdateDelPaticipantsCallBack_JNI(paticipants);
}

/**
  * MC将该消息群发到其他所有在会终端(包含主持人) 哪个终端类型转变
  * @param [in] nspclterid
  *          特殊类型变化的终端stermid
  * @param [in] nspcltype
  *          终端要转变的类型,变化后的特殊类型,	0-普通终端类型,1-投屏终端类型
  */
void SREngineConferenceControlCallback::OnIndTerSpecialtypeTransfer(const int nspclterid,
                                                                    const int nspcltype) {
    OnIndTerSpecialtypeTransferCallBack_JNI(nspclterid, nspcltype);
}

/**
* 终端收主持人开启会议直播状态
* @param [in] livestate
*         直播会议的状态,0-停止直播,1-开始直播
* @param [in] error
*        livestate为0时表示停止原因,为空或者"default"为正常停止,其它为具体原因
*/
void SREngineConferenceControlCallback::OnIndTerCRSLiveState(const int livestate,
                                                             const std::string &liveplayurl,
                                                             const SRConferenceAbnormal &error) {
    OnIndTerCRSLiveStateCallBack_JNI(livestate, liveplayurl, error);
}

/**
* 终端收直播设置变更
* @param [in] new_setting
*          新的直播设置
*/
void SREngineConferenceControlCallback:: OnIndLiveSettingChanged(const LiveSetting & new_setting){
    OnIndLiveSettingChangedCallBack_JNI(new_setting);
}