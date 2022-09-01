#pragma once
extern bool Served;

extern void(__cdecl* ShowSleepWaitMenu)(bool);
void __cdecl ShowSleepWaitMenuHook(bool IsSleeping);