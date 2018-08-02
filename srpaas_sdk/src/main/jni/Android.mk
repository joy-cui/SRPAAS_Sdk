
LOCAL_PATH:= $(call my-dir)


ifeq ($(PlatFormTypeBox),true)
include $(LOCAL_PATH)/prebuilt/3288/Android.mk


else
include $(LOCAL_PATH)/prebuilt/mobile/Android.mk

endif

include jni/jni/Android.mk

include $(CLEAR_VARS)




