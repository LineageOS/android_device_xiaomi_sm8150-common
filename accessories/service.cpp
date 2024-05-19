/*
 * SPDX-FileCopyrightText: 2026 The LineageOS Project
 * SPDX-License-Identifier: Apache-2.0
 */

#include <XiaomiAccessories.h>

#include <android-base/logging.h>
#include <android/binder_manager.h>
#include <android/binder_process.h>
#include "MiPad5Keyboard.h"

using aidl::vendor::lineage::accessories::MiPad5Keyboard;
using aidl::vendor::lineage::accessories::XiaomiAccessories;

class Sm8150Accessories : public XiaomiAccessories {
  public:
    Sm8150Accessories() { addAccessory(::ndk::SharedRefBase::make<MiPad5Keyboard>()); }
};

int main() {
    ABinderProcess_setThreadPoolMaxThreadCount(0);
    std::shared_ptr<Sm8150Accessories> hal = ::ndk::SharedRefBase::make<Sm8150Accessories>();

    const std::string instance = std::string(Sm8150Accessories::descriptor) + "/default";
    binder_status_t status = AServiceManager_addService(hal->asBinder().get(), instance.c_str());
    CHECK_EQ(status, STATUS_OK);

    ABinderProcess_joinThreadPool();
    return EXIT_FAILURE;  // should not reach
}
