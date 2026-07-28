/*
 * libbinder_shim — Oreo binder compatibility for legacy Marvell PXA1908.
 *
 * libvndbnd (hardware/marvell/vendor-libs/pxa1908/binder/) was compiled
 * against a pre-Oreo libbinder and does not link libbase.  On Oreo,
 * binder/Parcel.h pulls in <android-base/unique_fd.h> which lives in
 * libbase.  Linking libvndbnd against this shim (via LD_SHIM_LIBS or
 * direct LOCAL_SHARED_LIBRARIES) pulls libbase into its symbol resolution
 * scope without requiring changes to the Marvell hardware tree.
 *
 * This file intentionally contains no source-level symbols; all work is
 * done by the shared library dependencies declared in Android.mk.
 */

// Deliberate empty translation unit — symbols come from LOCAL_SHARED_LIBRARIES.
