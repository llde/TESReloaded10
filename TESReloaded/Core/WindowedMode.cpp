#include "WindowedMode.h"

#if defined(OBLIVION)
#define kRectStyle 0x0040E7C0
#define kWindowStyle 0x0040E805
#elif defined(SKYRIM)
#define kRectStyle 0x0069D832
#define kWindowStyle 0x0069D877
#endif

void SetWindowedMode(UInt8 Fullscreen) {

	if (!Fullscreen) {
		#if defined(SKYRIM)
		SafeWrite32(0x012CF5F8, 0);
		SafeWrite32(0x012CF604, 0);
		#endif

		SafeWrite32(kRectStyle, WS_POPUP);
		SafeWrite32(kWindowStyle, WS_POPUP | WS_VISIBLE);
	}

}

