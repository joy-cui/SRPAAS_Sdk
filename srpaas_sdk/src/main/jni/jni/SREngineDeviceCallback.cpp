#include "SREngineDeviceCallback.h"
#include <android/log.h>
#include "Log.h"
#include "SRSdkJni.h"

SREngineDeviceCallback::SREngineDeviceCallback() :
        ISRRtcEngineDeviceEventCallback() {

}

/**
     * @brief OnCameraChange    摄像头设备热插拔回调
     * @param type
     */
void SREngineDeviceCallback::OnCameraChange(SR_DEVICE_CHANGE_TYPE type, const char *device_name) {

}

/**
  * @brief OnAudioChange     音频设备热插拔
  * @param type
  */
void SREngineDeviceCallback::OnAudioChange(SR_DEVICE_CHANGE_TYPE type, const char *device_name) {

}

/**
  * @brief OnNetwrokNotify   网络状态改变回调
  * @param status
  */
void SREngineDeviceCallback::OnNetwrokNotify(const int status) {
    OnNetwrokNotify_JNI(status);
}
