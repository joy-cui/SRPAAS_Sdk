LOCAL_PATH := $(call my-dir)
$(warning "3288")
include $(CLEAR_VARS)
LOCAL_MODULE :=libapm
LOCAL_SRC_FILES :=libapm.so
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE :=libcallserver
LOCAL_SRC_FILES :=libcallserver.so
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE :=libhwcodec_3288
LOCAL_SRC_FILES :=libhwcodec_3288.so
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE :=libmediacore
LOCAL_SRC_FILES :=libmediacore.so
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE :=libSRRtcEngine
LOCAL_SRC_FILES :=libSRRtcEngine.so
include $(PREBUILT_SHARED_LIBRARY)







