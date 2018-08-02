#ifndef SRENGINEDEVICECALLBACK_H
#define SRENGINEDEVICECALLBACK_H

#include "ISRRtcEngine.h"

using namespace suirui::rtc;

/**
 * @brief The SREngineDeviceCallback class
 */
class SREngineDeviceCallback : public ISRRtcEngineDeviceEventCallback {
public:
    SREngineDeviceCallback();

public:
    /**
     * @brief OnCameraChange    摄像头设备热插拔回调
     * @param type
     */
    virtual void OnCameraChange(SR_DEVICE_CHANGE_TYPE type, const char *device_name);

    /**
     * @brief OnAudioChange     音频设备热插拔
     * @param type
     */
    virtual void OnAudioChange(SR_DEVICE_CHANGE_TYPE type, const char *device_name);

    /**
     * @brief OnNetwrokNotify   网络状态改变回调
     * @param status
     */
    virtual void OnNetwrokNotify(const int status);
};

#endif // SRENGINEDEVICECALLBACK_H
