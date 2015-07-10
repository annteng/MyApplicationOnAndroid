LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := HelloWorldJni
LOCAL_SRC_FILES := jni_test.cpp ann_lib.cpp
LOCAL_LDLIBS := -L$(SYSROOT)/usr/lib -llog -lz
LOCAL_SHARED_LIBRARIES := libswresample libavformat libavcodec libswscale libavutil libavfilter
LOCAL_CPPFLAGS := -D__STDC_CONSTANT_MACROS
LOCAL_JNI_SHARED_LIBRARIES = libavformat libavcodec libswscale libavutil libswresample libavfilter
include $(BUILD_SHARED_LIBRARY)
#$(call import-add-path, /Users/annteng/ndk/android-ndk-r10d/sources/)
#$(call import-module,third_party/googletest)

$(call import-module,third_party/armtest)
