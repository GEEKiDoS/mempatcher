#pragma once

#include <winternl.h>

auto constexpr LDR_DLL_NOTIFICATION_REASON_LOADED = 1;
auto constexpr LDR_DLL_NOTIFICATION_REASON_UNLOADED = 2;

typedef struct _LDR_DLL_LOADED_NOTIFICATION_DATA
{
    ULONG Flags;
    PCUNICODE_STRING FullDllName;
    PCUNICODE_STRING BaseDllName;
    PVOID DllBase;
    ULONG SizeOfImage;
} LDR_DLL_LOADED_NOTIFICATION_DATA, *PLDR_DLL_LOADED_NOTIFICATION_DATA;

typedef struct _LDR_DLL_UNLOADED_NOTIFICATION_DATA
{
    ULONG Flags;
    PCUNICODE_STRING FullDllName;
    PCUNICODE_STRING BaseDllName;
    PVOID DllBase;
    ULONG SizeOfImage;
} LDR_DLL_UNLOADED_NOTIFICATION_DATA, *PLDR_DLL_UNLOADED_NOTIFICATION_DATA;

typedef union _LDR_DLL_NOTIFICATION_DATA
{
    LDR_DLL_LOADED_NOTIFICATION_DATA Loaded;
    LDR_DLL_UNLOADED_NOTIFICATION_DATA Unloaded;
} LDR_DLL_NOTIFICATION_DATA, *PLDR_DLL_NOTIFICATION_DATA;

typedef const _LDR_DLL_NOTIFICATION_DATA* PCLDR_DLL_NOTIFICATION_DATA;

typedef VOID (CALLBACK* PLDR_DLL_NOTIFICATION_FUNCTION)
(
    ULONG NotificationReason,
    PCLDR_DLL_NOTIFICATION_DATA NotificationData,
    PVOID Context
);

NTSTATUS NTAPI LdrRegisterDllNotification
(
    ULONG                          Flags,
    PLDR_DLL_NOTIFICATION_FUNCTION NotificationFunction,
    PVOID                          Context,
    PVOID                          *Cookie
);

NTSTATUS NTAPI LdrUnregisterDllNotification(
    PVOID Cookie
);