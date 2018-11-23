/*
*
* Copyright (c) 2018 by blindtiger. All rights reserved.
*
* The contents of this file are subject to the Mozilla Public License Version
* 2.0 (the "License"); you may not use this file except in compliance with
* the License. You may obtain a copy of the License at
* http://www.mozilla.org/MPL/
*
* Software distributed under the License is distributed on an "AS IS" basis,
* WITHOUT WARRANTY OF ANY KIND, either express or implied. SEe the License
* for the specific language governing rights and limitations under the
* License.
*
* The Initial Developer of the Original e is blindtiger.
*
*/

#ifndef _RTX_H_
#define _RTX_H_

#ifdef __cplusplus
/* Assume byte packing throughout */
extern "C" {
#endif	/* __cplusplus */

    typedef
        ULONG_PTR
        (NTAPI * PKIPI_ROUTINE)(
            __in ULONG_PTR Argument1,
            __in ULONG_PTR Argument2,
            __in ULONG_PTR Argument3
            );

    typedef struct _RTX {
        USHORT Platform;
        ULONG Processor;
        PPS_APC_ROUTINE ApcRoutine;
        PKSYSTEM_ROUTINE SystemRoutine;
        PUSER_THREAD_START_ROUTINE StartRoutine;
        PVOID StartContext;
        NTSTATUS ReturnedStatus;
        ULONG_PTR Result;
        KPROCESSOR_MODE Mode;
    } RTX, *PRTX;

    typedef struct _ATX {
        KAPC Apc;
        KEVENT Notify;
        RTX Rtx;
    } ATX, *PATX;

    VOID
        NTAPI
        CtxSpecialApc(
            __in PKAPC Apc,
            __in PKNORMAL_ROUTINE * NormalRoutine,
            __in PVOID * NormalContext,
            __in PVOID * SystemArgument1,
            __in PVOID * SystemArgument2
        );

    NTSTATUS
        NTAPI
        RemoteCall(
            __in HANDLE UniqueThread,
            __in USHORT Platform,
            __in_opt PUSER_THREAD_START_ROUTINE StartRoutine,
            __in_opt PVOID StartContext,
            __in KPROCESSOR_MODE Mode
        );

    ULONG_PTR
        NTAPI
        _IpiDispatcher(
            __in PPS_APC_ROUTINE ApcRoutine,
            __in PKSYSTEM_ROUTINE SystemRoutine,
            __in PUSER_THREAD_START_ROUTINE StartRoutine,
            __in PVOID StartContext
        );

    ULONG_PTR
        NTAPI
        IpiSingleCall(
            __in PPS_APC_ROUTINE ApcRoutine,
            __in PKSYSTEM_ROUTINE SystemRoutine,
            __in PUSER_THREAD_START_ROUTINE StartRoutine,
            __in PVOID StartContext
        );

    VOID
        NTAPI
        IpiGenericCall(
            __in PPS_APC_ROUTINE ApcRoutine,
            __in PKSYSTEM_ROUTINE SystemRoutine,
            __in PUSER_THREAD_START_ROUTINE StartRoutine,
            __in PVOID StartContext
        );

#ifdef __cplusplus
}
#endif	/* __cplusplus */

#endif // !_RTX_H_
