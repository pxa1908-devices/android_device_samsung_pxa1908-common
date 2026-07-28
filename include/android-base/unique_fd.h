/*
 * Copyright (C) 2015 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/*
 * Shim header for legacy Marvell PXA1908 vendor libs compiled against
 * android-8.0.0_r30 binder headers which require <android-base/unique_fd.h>.
 * This provides the minimal ScopedFd / unique_fd implementation so that
 * binder/Parcel.h compiles cleanly without needing the full libbase source.
 *
 * If system/core/libbase/include/android-base/unique_fd.h is reachable via
 * BOARD_GLOBAL_CPPFLAGS this header will not be used (it only fires when the
 * real header is not on the include path).
 */

#pragma once
#ifndef ANDROID_BASE_UNIQUE_FD_H
#define ANDROID_BASE_UNIQUE_FD_H

#include <unistd.h>   // for close()
#include <utility>    // for std::move

namespace android {
namespace base {

// Minimal unique_fd that satisfies the Oreo Parcel.h forward declaration.
// Does not support the full android::base::unique_fd<Closer> template;
// legacy Marvell binder code only needs the default close-on-destroy
// semantics which this provides.
struct unique_fd {
    unique_fd() : fd_(-1) {}
    explicit unique_fd(int fd) : fd_(fd) {}
    ~unique_fd() { if (fd_ != -1) ::close(fd_); }

    unique_fd(unique_fd&& other) : fd_(other.release()) {}
    unique_fd& operator=(unique_fd&& other) {
        reset(other.release());
        return *this;
    }

    unique_fd(const unique_fd&) = delete;
    unique_fd& operator=(const unique_fd&) = delete;

    int get() const { return fd_; }
    explicit operator bool() const { return fd_ != -1; }

    int release() {
        int tmp = fd_;
        fd_ = -1;
        return tmp;
    }

    bool reset(int fd = -1) {
        if (fd_ != -1) ::close(fd_);
        fd_ = fd;
        return fd_ != -1;
    }

private:
    int fd_;
};

}  // namespace base
}  // namespace android

#endif  // ANDROID_BASE_UNIQUE_FD_H
