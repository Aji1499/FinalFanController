#define LOG_TAG "FanController_hal"

#include <utils/Log.h>
#include <iostream>
#include <fstream>
#include "FanSpeedControl.h"

namespace aidl {
    namespace android {
        namespace hardware {
            namespace fancontroller {
                ndk::ScopedAStatus FanSpeedControl::turnFanOn(bool* _aidl_return ) {
                    if(!fanOn){
                        fanOn = true;//turn on the fan
                        *_aidl_return = true;//return value on success
                        ALOGD("turnFanOn() : Fan turned ON");//log statement
                        return ndk::ScopedAStatus::ok();//return status
                    }
                    else{
                    *_aidl_return = false;//return value on failure
                    ALOGE("turnFanOn() : Fan is already ON");//log statement
                    return ndk::ScopedAStatus::ok();//return status
                    }
                }
                ndk::ScopedAStatus FanSpeedControl::turnFanOff(bool* _aidl_return) {
                    if(fanOn){
                        fanOn = false;//turn off the fan
                        *_aidl_return = true;//return value on success
                        ALOGD("turnFanOff() : Fan turned OFF");//log statement
                        return ndk::ScopedAStatus::ok();//return status
                    }
                    *_aidl_return = false;//return value on failure
                    ALOGE("turnFanOff() : Fan is already OFF");//log statement
                    return ndk::ScopedAStatus::ok();//return status
                }
                ndk::ScopedAStatus FanSpeedControl::isFanOn(bool* _aidl_return) {
                    if (fanOn){
                        *_aidl_return = true;//return value on success
                        ALOGD("isFanOn() : Fan is ON");
                        return ndk::ScopedAStatus::ok();//return status
                    }
                    *_aidl_return = false;//return value on failure
                    ALOGD("isFanOn() : Fan is OFF");//log statement
                    return ndk::ScopedAStatus::ok();//return status
                }
                ndk::ScopedAStatus FanSpeedControl::increaseFanSpeed(bool* _aidl_return){
                    if(fanSpeed <5){
                        fanSpeed++;//increase fan speed
                        *_aidl_return = true;//return value on success
                        ALOGD("increaseFanSpeed() : Increased Fan Speed");//log statement
                    }else{
                    *_aidl_return = false;//return value on failure
                    ALOGE("increaseFanSpeed() : Fan Speed is already at maximum");//log statement
                    }                    
                    return ndk::ScopedAStatus::ok();//return status
                }
                ndk::ScopedAStatus FanSpeedControl::decreaseFanSpeed(bool* _aidl_return) {  
                   if(fanSpeed > 1){
                        fanSpeed--;//decrease fan speed
                        *_aidl_return = true;//return value on success
                        ALOGD("decreaseFanSpeed() : Decreased Fan Speed");//log statement
                        return ndk::ScopedAStatus::ok();//return status
                    }
                    *_aidl_return = false;//return value on failure
                    ALOGE("decreaseFanSpeed() : Fan Speed is already at minimum");//log statement
                    return ndk::ScopedAStatus::ok();//return status
                }
                ndk::ScopedAStatus FanSpeedControl::getFanSpeed(int32_t* _aidl_return) {
                    if(fanOn){
                        *_aidl_return = fanSpeed;//return value on success
                        ALOGD("getFanSpeed() : Fan speed returned successfully = %d", fanSpeed);
                        return ndk::ScopedAStatus::ok();//return status
                    }
                    *_aidl_return = 0;//return value on failure
                    ALOGE("getFanSpeed() : Fan is off, Fanspeed = 0");//log statement
                    return ndk::ScopedAStatus::ok();//return status
                }
            }
        }
    }
}