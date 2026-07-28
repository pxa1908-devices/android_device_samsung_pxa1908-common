/*
 * Shim for legacy Marvell PXA1908 vendor libs compiled against Oreo's libui.
 *
 * Oreo (android-8.0.0) changed/removed several GraphicBuffer and
 * GraphicBufferMapper ABI symbols that the Marvell gralloc/camera blobs
 * were linked against.  We re-export them here with the old signatures,
 * delegating to the new Oreo implementations.
 */

#include <ui/GraphicBuffer.h>
#include <ui/GraphicBufferMapper.h>
#include <sys/types.h>
#include <unistd.h>

/*
 * GraphicBufferMapper::lock  — Nougat 4-arg form
 * Old mangled: _ZN7android19GraphicBufferMapper4lockEPK13native_handleiRKNS_4RectEPPv
 * Oreo still has a 4-arg overload so delegate straight through.
 */
extern "C" android::status_t
_ZN7android19GraphicBufferMapper4lockEPK13native_handleiRKNS_4RectEPPv(
        android::GraphicBufferMapper* _this,
        buffer_handle_t handle,
        int usage,
        const android::Rect& bounds,
        void** vaddr)
{
    return _this->lock(handle, usage, bounds, vaddr);
}

/*
 * GraphicBuffer constructor — old 4-arg form (w, h, format, usage).
 * Old mangled: _ZN7android13GraphicBufferC1Ejjij
 * Oreo's constructor requires a 5th requestorName argument; supply a
 * default string to keep binary compatibility with old blobs.
 */
extern "C" android::GraphicBuffer*
_ZN7android13GraphicBufferC1Ejjij(
        uint32_t w,
        uint32_t h,
        android::PixelFormat reqFormat,
        uint32_t reqUsage)
{
    return new android::GraphicBuffer(w, h, reqFormat, reqUsage,
                                      "<legacy-pxa1908-shim>");
}

/*
 * androidGetTid — used by older Marvell logging code.
 */
extern "C" pid_t androidGetTid()
{
#if defined(HAVE_GETTID) || defined(__BIONIC__)
    return gettid();
#else
    return getpid();
#endif
}
