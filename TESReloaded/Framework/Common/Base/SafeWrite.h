#pragma once

void SafeWrite8(UInt32 addr, UInt32 data);
void SafeWrite16(UInt32 addr, UInt32 data);
void SafeWrite32(UInt32 addr, UInt32 data);
void SafeWriteJump(UInt32 jumpSrc, UInt32 jumpTgt);
void SafeWriteCall(UInt32 jumpSrc, UInt32 jumpTgt);