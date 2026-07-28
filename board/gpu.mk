# GPU
TARGET_BOARD_PLATFORM     := mrvl
#TARGET_BOARD_PLATFORM    := pxa1908
TARGET_BOARD_SOC          := pxa1908
TARGET_BOARD_PLATFORM_GPU := vivante-gc7000ul
ARCH_ARM_HAVE_TLS_REGISTER := true

# PXA1908 runs a 64-bit kernel with a 32-bit Android userspace.
# Oreo's libbinder needs to know to use the 32-bit binder IPC ABI.
TARGET_USES_64_BIT_BINDER := false
BINDER_IPC_32BIT          := true
