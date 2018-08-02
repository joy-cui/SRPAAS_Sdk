LOCAL_PATH := $(call my-dir)
$(warning "jni")

include $(CLEAR_VARS)
LOCAL_PROGUARD_FLAGS := -include $(LOCAL_PATH)/proguard.flags


LOCAL_MODULE := libSRSdkJNI



IN_NDK := true


MY_INCLUDES := \
    $(LOCAL_PATH)/ \
    

LOCAL_SRC_FILES := \
       Log.cpp\
       SREngineConferenceCallback.cpp \
       SREngineConferenceControlCallback.cpp \
       SREngineDataCallback.cpp \
       SREngineDeviceCallback.cpp \
       SRRtcEngineConferenceSdk.cpp \
       SRSdkJni.cpp \



        
       
LOCAL_C_INCLUDES += \
	$(MY_INCLUDES)       
    
#-DLOG_JNI

LOCAL_CPPFLAGS +=-DLOG_JNI   -DRAYCOM_ANDROID  -DANDROID


LOCAL_CFLAGS := -D__STDC_CONSTANT_MACROS -Wl,-Map=test.map -g
          
              

ifeq ($(IN_NDK),true)	
LOCAL_LDLIBS += -llog 
else
LOCAL_PRELINK_MODULE := false
#LOCAL_SHARED_LIBRARIES += libcutils   libandroid_runtime  libnativehelper libOpenSLES
endif


ifeq ($(PlatFormTypeBox),true)
LOCAL_SHARED_LIBRARIES += libapm libcallserver  libhwcodec_3288   libmediacore libSRRtcEngine
else
LOCAL_SHARED_LIBRARIES += libapm libcallserver   libmediacore libSRRtcEngine
endif

#LOCAL_STATIC_LIBRARIES :=libstlport_static

include $(BUILD_SHARED_LIBRARY)
#include $(BUILD_STATIC_LIBRARY)
