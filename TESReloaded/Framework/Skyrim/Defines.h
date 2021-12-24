#pragma once

#define CommandPrefix "SR"

#define kReadSetting 0x00AFED60
#define kWriteSetting 0x00AFEB50
#define kLoadGame 0x0067B720

#define kNewMain				 0x0069BFE0
#define kInitializeRenderer		 0x00691030
#define kNewTES					 0x00435C10
#define kNewPlayerCharacter		 0x0074DB40
#define kNewSceneGraph			 0x0069F1F0
#define kNewMasterDataHandler	 0x0043DE50
#define kNewMenuInterfaceManager 0x00A5DE30 // Special case: this cannot be detoured because it is called in preinit and the plugin is not attached yet
#define kNewQueuedModelLoader	 0x00430470
#define kShadowSceneNode		 0x00000000
#define SetMenuManager			 MenuManager = *(MenuInterfaceManager**)0x012E3548

#define cloudSpeedLower general.cloudSpeedLower
#define cloudSpeedUpper general.cloudSpeedUpper
#define sunDamage general.sunDamage
#define sunGlare general.sunGlare
#define transDelta general.transDelta
#define windSpeed general.windSpeed
#define WeatherFogFarDay fogDistance.farDay
#define WeatherFogFarNight fogDistance.farNight
#define WeatherFogNearDay fogDistance.nearDay
#define WeatherFogNearNight fogDistance.nearNight