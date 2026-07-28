LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE_TAGS := optional

# Added base/include and core/include for Oreo libbase compatibility
LOCAL_C_INCLUDES := \
    system/core/init \
    system/core/base/include \
    system/core/include

# Added -Wno-error to prevent legacy warnings from stopping the build
LOCAL_CFLAGS := -Wall -Wno-error -DANDROID_TARGET=\"$(TARGET_BOARD_PLATFORM)\"

LOCAL_SRC_FILES := init_pxa1908.cpp

ifneq ($(TARGET_LIBINIT_PXA1908_DEFINES_FILE),)
  LOCAL_SRC_FILES += ../../../../$(TARGET_LIBINIT_PXA1908_DEFINES_FILE)
endif

LOCAL_MODULE := libinit_pxa1908

# Link libbase so android-base dependencies are resolved
LOCAL_STATIC_LIBRARIES += libbase

include $(BUILD_STATIC_LIBRARY)
