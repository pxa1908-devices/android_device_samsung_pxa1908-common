LOCAL_PATH := $(call my-dir)

# ---------------------------------------------------------------------------
# libui_shim — re-export Nougat-era GraphicBuffer / GraphicBufferMapper
# symbols that legacy Marvell blobs are linked against.  Oreo changed the
# signatures, so we provide thin wrappers that forward to the new ABI.
# ---------------------------------------------------------------------------
include $(CLEAR_VARS)

LOCAL_SRC_FILES         := uishim.cpp
LOCAL_SHARED_LIBRARIES  := libui libbase
LOCAL_MODULE            := libui_shim
LOCAL_MODULE_TAGS       := optional
# 32-bit only — Marvell userspace is 32-bit on a 64-bit kernel
LOCAL_MULTILIB          := 32
LOCAL_CFLAGS            += -DBINDER_IPC_32BIT=1

include $(BUILD_SHARED_LIBRARY)

# ---------------------------------------------------------------------------
# libutils_shim — re-export String16 constructors removed in Oreo.
# ---------------------------------------------------------------------------
include $(CLEAR_VARS)

LOCAL_SRC_FILES         := utilsshim.cpp
LOCAL_SHARED_LIBRARIES  := libutils
LOCAL_MODULE            := libutils_shim
LOCAL_MODULE_TAGS       := optional
LOCAL_MULTILIB          := 32

include $(BUILD_SHARED_LIBRARY)

# ---------------------------------------------------------------------------
# libwvm_shim — re-export MediaBufferGroup ctor removed in Oreo.
# ---------------------------------------------------------------------------
include $(CLEAR_VARS)

LOCAL_SRC_FILES         := wvmshim.cpp
LOCAL_SHARED_LIBRARIES  := libmedia
LOCAL_MODULE            := libwvm_shim
LOCAL_MODULE_TAGS       := optional
LOCAL_MULTILIB          := 32

include $(BUILD_SHARED_LIBRARY)

# ---------------------------------------------------------------------------
# libbinder_shim — provides libbase symbols (unique_fd etc.) that
# Marvell libvndbnd / libbnd vendor libs need when linked against
# Oreo's binder headers.  Simply re-exports libbase + libbinder.
# ---------------------------------------------------------------------------
include $(CLEAR_VARS)

LOCAL_SRC_FILES         := bindershim.cpp
LOCAL_SHARED_LIBRARIES  := libbinder libbase libutils libcutils liblog
LOCAL_MODULE            := libbinder_shim
LOCAL_MODULE_TAGS       := optional
LOCAL_MULTILIB          := 32
LOCAL_CFLAGS            += -DBINDER_IPC_32BIT=1

include $(BUILD_SHARED_LIBRARY)
