#include "SREngineDataCallback.h"
#include <android/log.h>
#include "Log.h"
#include "SRSdkJni.h"

SREngineDataCallback::SREngineDataCallback() :
        ISRRtcEngineDataEventCallback() {

}

/**
    * @brief onRecvStreamInfoStats         接收数据统计信息回调
    * @param stats                         统计信息
    */
void SREngineDataCallback::onRecvStreamInfoStats(const RecvStreamInfo &stats) {
    onRecvStreamInfoStatsCallBack_JNI(stats);
}

/**
 * @brief onSendStreamInfoStats         发送数据统计信息回调
 * @param stats                         统计信息
 */
void SREngineDataCallback::onSendStreamInfoStats(const SendStreamInfo &stats) {
    onSendStreamInfoStatsCallBack_JNI(stats);
}

/**
 * @brief OnActiveVoice     语音激励回调
 * @param voice_acives      音频能量值列表
 */
void SREngineDataCallback::OnActiveVoice(std::deque <SRVoiceActiveInfo> voice_acives) {
    OnActiveVoiceCallBack_JNI(voice_acives);
}

/**
 * @brief OnMicVolumeVoice  麦克风测试音量回调
 * @param voice_value       音频能量值
 */
void SREngineDataCallback::OnMicVolumeVoice(const int voice_value) {

}
