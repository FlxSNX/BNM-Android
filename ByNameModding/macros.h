#pragma once
#include <android/log.h>
#include <mega_obfuscator.hpp>

//! Write your sting obfuscator
#define OBFUSCATE_BNM(str) OBFUSCATE(str) // const char *
#define OBFUSCATES_BNM(str) OBFUSCATES(str) // std::string
#define BNMTAG OBFUSCATE_BNM("ByNameModding")

#ifdef BNM_INFO
#define LOGIBNM(...) ((void)__android_log_print(4,  BNMTAG, __VA_ARGS__))
#else
#define LOGIBNM(...)
#endif

#ifdef BNM_DEBUG
#define LOGDBNM(...) ((void)__android_log_print(3,  BNMTAG, __VA_ARGS__))
#else
#define LOGDBNM(...)
#endif

//! include your hooking software
#if defined(__ARM_ARCH_7A__) || defined(__i386__) // armv7 or x86
#include <Substrate/SubstrateHook.h>
#include <Substrate/CydiaSubstrate.h>
#elif defined(__aarch64__) //arm64-v8a
#include <And64InlineHook/And64InlineHook.hpp>
#endif
auto HOOK = [](auto ptr, auto newMethod, auto&& oldBytes) {
    if (ptr != 0){
#if defined(__aarch64__)
        A64HookFunction((void *)ptr, (void *) newMethod, (void **) &oldBytes);
#else
        MSHookFunction((void *)ptr, (void *) newMethod, (void **) &oldBytes);
#endif
    }
};