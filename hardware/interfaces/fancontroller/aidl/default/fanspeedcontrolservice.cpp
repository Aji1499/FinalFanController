#define LOG_TAG "FanController_hal_service"
#include <utils/Log.h>
#include <log/log.h>

#include <android-base/logging.h>
#include <android/binder_manager.h>
#include <android/binder_process.h>
#include <binder/ProcessState.h>
#include <binder/IServiceManager.h>
#include "FanSpeedControl.h"

using aidl::android::hardware::fancontroller::FanSpeedControl;

void logd(std::string msg) {
    std::cout << msg << std::endl;
    ALOGD("%s", msg.c_str());
}

void loge(std::string msg) {
    std::cout << msg << std::endl;
    ALOGE("%s", msg.c_str());
}

int main() {

    ABinderProcess_setThreadPoolMaxThreadCount(0);
    //   ABinderProcess_startThreadPool();

    ALOGD("Fancontroller Service main() Starts here");

    std::shared_ptr<FanSpeedControl> fanspeedcontrol = ndk::SharedRefBase::make<FanSpeedControl>();
    const std::string name =std::string()+ FanSpeedControl::descriptor + "/default";

    binder_status_t status = AServiceManager_addService(fanspeedcontrol->asBinder().get(), name.c_str());
    CHECK_EQ(status, STATUS_OK);

    logd("fancontrollerservice started sucessfully, status= "+std::to_string(status));

    ALOGD("IFancontroller service starts to join service pool");
    ABinderProcess_joinThreadPool();

    ALOGE("Failed to join Thread Pool");

    return EXIT_FAILURE;  // should not reached
}