//
// Modified by Laughing Muffin on 15/11/2023
//

#include <iostream>
#include <jni.h>
//==================================================================================================
#include "APKKiller.h"

#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, "KILLER", __VA_ARGS__)
//==================================================================================================
int RegisterFunctions(JNIEnv *env) {
    JNINativeMethod methods[] = {
            {"Start",         "(Landroid/content/Context;)V",                                      (void *) APKKill},
            {"processInvoke", "(Ljava/lang/reflect/Method;[Ljava/lang/Object;)Ljava/lang/Object;", (void *) processInvoke}
    };

    jclass clazz = env->FindClass("com/muffin/APKKiller");
    if (!clazz)
        return -1;

    if (env->RegisterNatives(clazz, methods, sizeof(methods) / sizeof(methods[0])) != 0)
        return -1;

    return 0;
}
//==================================================================================================
JNIEXPORT jint JNI_OnLoad(JavaVM *vm, void *reserved) {
    g_vm = vm;

    JNIEnv *env;
    if (vm->GetEnv(reinterpret_cast<void **>(&env), JNI_VERSION_1_6) != JNI_OK) {
        LOGI("Error retrieving env!");
        return -1;
    }

    if (RegisterFunctions(env) != 0) {
        LOGI("Error registering navives!");
        return -1;
    }

    LOGI("JNI_OnLoad!");

    return JNI_VERSION_1_6;
}
//==================================================================================================