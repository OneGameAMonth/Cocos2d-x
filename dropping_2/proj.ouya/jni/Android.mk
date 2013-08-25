LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := dropping_2_shared

LOCAL_MODULE_FILENAME := libhellocpp

LOCAL_SRC_FILES := ../../Classes/Interface.cpp \
                   ../../Classes/GameScene.cpp \
                   hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/Game/Block.cpp \
                   ../../Classes/Game/Bomb.cpp \
                   ../../Classes/Game/Coin.cpp \
                   ../../Classes/Game/Earth.cpp \
                   ../../Classes/Game/Parachute.cpp \
                   ../../Classes/Game/Water.cpp  

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes $(LOCAL_PATH)/../../Classes/Game

LOCAL_CPPFLAGS += -fno-rtti -fno-exceptions -std=gnu++11 -fexceptions -pthread

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,cocos2dx)

