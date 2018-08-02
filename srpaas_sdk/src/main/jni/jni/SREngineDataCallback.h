#ifndef SRENGINEDATACALLBACK_H
#define SRENGINEDATACALLBACK_H

#include "ISRRtcEngine.h"

using namespace suirui::rtc;
/**
 * 数据信息统计
 */
class SREngineDataCallback : public ISRRtcEngineDataEventCallback
{
public:
    SREngineDataCallback();

public:
    /**
     * @brief onRecvStreamInfoStats         接收数据统计信息回调
     * @param stats                         统计信息
     */
    virtual void onRecvStreamInfoStats(const RecvStreamInfo& stats);

    /**
     * @brief onSendStreamInfoStats         发送数据统计信息回调
     * @param stats                         统计信息
     */
    virtual void onSendStreamInfoStats(const SendStreamInfo& stats);

    /**
     * @brief OnActiveVoice     语音激励回调
     * @param voice_acives      音频能量值列表
     */
    virtual void OnActiveVoice(std::deque<SRVoiceActiveInfo> voice_acives);

    /**
     * @brief OnMicVolumeVoice  麦克风测试音量回调
     * @param voice_value       音频能量值
     */
    virtual void OnMicVolumeVoice(const int  voice_value);
};

#endif // SRENGINEDATACALLBACK_H
