#pragma once
#include "GameNi.h"

class INISettingCollection;
class ModInfo;
class Actor;
class ActorAnimData;
class MagicItem;
class MagicTarget;
class CombatController;
class SpellItem;
class EffectNode;
class DialoguePackage;
class BirthSign;
class AlchemyItem;
class ActiveEffect;
class ModelKF;
class Creature;
class SkinInfo;
class BoundObjectListHead;
class Character;
class WaterManager;
class WaterPlaneData;
class Script;
class EnchantmentItem;
class ScriptEventList;
class Menu;
class SleepWaitMenu;
class ExtraDataList;
class MediaSet;
class MediaLocationController;
class Tile;
class TileText;
class MovementHandler;
class LookHandler;
class SprintHandler;
class ReadyWeaponHandler;
class AutoMoveHandler;
class ToggleRunHandler;
class ActivateHandler;
class JumpHandler;
class ShoutHandler;
class AttackBlockHandler;
class RunHandler;
class SneakHandler;
class TogglePOVHandler;
class EffectSetting;
class ScrollItem;
class Hazard;
class NavMesh;
class NavMeshInfoMap;
class Projectile;
class MissileProjectile;
class ArrowProjectile;
class GrenadeProjectile;
class BeamProjectile;
class FlameProjectile;
class ConeProjectile;
class BarrierProjectile;
class IngredientItem;
class PlayerCamera;
class VMClassInfo;
class VMIdentifier;
class VMState;
class NativeFunction;

class TESSaveLoadGame;
class TESForm;
class TESObjectREFR;
class TESObjectCELL;
class TESObjectBOOK;
class TESObjectARMO;
class TESObjectANIO;
class TESObjectLAND;
class TESObjectACTI;
class TESObjectCONT;
class TESObjectDOOR;
class TESObjectMISC;
class TESObjectSTAT;
class TESObjectTREE;
class TESObjectARMA;
class TESFlora;
class TESFurniture;
class TESAmmo;
class TESPathGrid;
class TESTopic;
class TESTopicInfo;
class TESRegion;
class TESRegionList;
class TESClass;
class TESNPC;
class TESSound;
class TESHair;
class TESEyes;
class TESRace;
class TESLandTexture;
class TESFaction;
class TESCombatStyle;
class TESLoadScreen;
class TESEffectShader;
class TESRegionDataManager;
class TESPackageData;
class TESChildCell { public: virtual TESObjectCELL* GetChildCell(); }; assert(sizeof(TESChildCell) == 0x004);
class TESImageSpace;
class TESImageSpaceModifier;
class TESReputation;
class TESChallenge;
class TESRecipe;
class TESRecipeCategory;
class TESAmmoEffect;
class TESCasino;
class TESCaravanDeck;
class TESLoadScreenType;
class TESGrass;
class TESLevCharacter;
class TESKey;
class TESLevSpell;
class TESShout;
class TESWordOfPower;
class TESSoulGem;
class TESLevItem;

class BSBound;
class BSFogProperty;
class BSRenderedTexture;
class BSTempNodeManager;
class BSAnimGroupSequence;
class BSFile;
class BSGameSound;
class BSSoundInfo;
class BSIStream;

class BGSHeadPart;
class BGSEncounterZone;
class BGSCameraShot;
class BGSAcousticSpace;
class BGSRagdoll;
class BGSVoiceType;
class BGSImpactData;
class BGSImpactDataSet;
class BGSProjectile;
class BGSExplosion;
class BGSRadiationStage;
class BGSDehydrationStage;
class BGSHungerStage;
class BGSSleepDeprivationStage;
class BGSDebris;
class BGSBodyPartData;
class BGSNote;
class BGSListForm;
class BGSMenuIcon;
class BGSMessage;
class BGSLightingTemplate;
class BGSMusicType;
class BGSAddonNode;
class BGSKeyword;
class BGSLocationRefType;
class BGSAction;
class BGSTextureSet;
class BGSTalkingActivator;
class BGSApparatus;
class BGSEquipSlot;
class BGSRelationship;
class BGSScene;
class BGSAssociationType;
class BGSOutfit;
class BGSArtObject;
class BGSMaterialObject;
class BGSMovementType;
class BGSSoundDescriptorForm;
class BGSDualCastData;
class BGSSoundCategory;
class BGSSoundOutput;
class BGSCollisionLayer;
class BGSColorForm;
class BGSReverbParameters;
class BGSFootstep;
class BGSFootstepSet;
class BGSStoryManagerBranchNode;
class BGSStoryManagerQuestNode;
class BGSStoryManagerEventNode;
class BGSDialogueBranch;
class BGSMusicTrackFormWrapper;
class BGSCameraPath;
class BGSMaterialType;
class BGSLocation;
class BGSConstructibleObject;
class BGSHazard;
class BGSShaderParticleGeometryData;
class BGSReferenceEffect;
class BGSMovableStatic;
class BGSStaticCollection;
class BGSIdleMarker;
class BGSSkillPerkTreeNode;

static const void* RTTI_BSExtraData = (void*)0x0123C200;
static const void* RTTI_ExtraEditorID = (void*)0x0123C21C;
static const void* RTTI_ExtraSeenData = (void*)0x0123C238;
static const void* RTTI_ExtraHavok = (void*)0x0123C254;
static const void* RTTI_ExtraPrimitive = (void*)0x0123C56C;
static const void* RTTI_ExtraMagicLight = (void*)0x0123C58C;
static const void* RTTI_ExtraLock = (void*)0x0123C5C8;
static const void* RTTI_ExtraFromAlias = (void*)0x0123C5E0;
static const void* RTTI_ExtraTeleport = (void*)0x0123C600;
static const void* RTTI_ExtraTeleportName = (void*)0x0123C61C;
static const void* RTTI_ExtraOwnership = (void*)0x0123C63C;
static const void* RTTI_ExtraGlobal = (void*)0x0123C65C;
static const void* RTTI_ExtraRank = (void*)0x0123C678;
static const void* RTTI_ExtraCount = (void*)0x0123C690;
static const void* RTTI_ExtraWorn = (void*)0x0123C6AC;
static const void* RTTI_ExtraWornLeft = (void*)0x0123C6C4;
static const void* RTTI_ExtraCannotWear = (void*)0x0123C6E0;
static const void* RTTI_ExtraHealth = (void*)0x0123C700;
static const void* RTTI_ExtraHealthPerc = (void*)0x0123C71C;
static const void* RTTI_ExtraTimeLeft = (void*)0x0123C73C;
static const void* RTTI_ExtraCharge = (void*)0x0123C758;
static const void* RTTI_ExtraScale = (void*)0x0123C774;
static const void* RTTI_ExtraCachedScale = (void*)0x0123C790;
static const void* RTTI_ExtraHotkey = (void*)0x0123C7B0;
static const void* RTTI_ExtraLocation = (void*)0x0123C7CC;
static const void* RTTI_ExtraTresPassPackage = (void*)0x0123C7E8;
static const void* RTTI_ExtraLeveledItem = (void*)0x0123C80C;
static const void* RTTI_ExtraOutfitItem = (void*)0x0123C82C;
static const void* RTTI_ExtraRagDollData = (void*)0x0123C84C;
static const void* RTTI_ExtraEncounterZone = (void*)0x0123C86C;
static const void* RTTI_ExtraRandomTeleportMarker = (void*)0x0123C890;
static const void* RTTI_ExtraLocationRefType = (void*)0x0123C8B8;
static const void* RTTI_ExtraLeveledItemBase = (void*)0x0123C8DC;
static const void* RTTI_ExtraLevCreaModifier = (void*)0x0123C900;
static const void* RTTI_ExtraPoison = (void*)0x0123C924;
static const void* RTTI_ExtraEnchantment = (void*)0x0123C940;
static const void* RTTI_ExtraLastFinishedSequence = (void*)0x0123C960;
static const void* RTTI_ExtraEmittanceSource = (void*)0x0123C988;
static const void* RTTI_ExtraMultiBoundRef = (void*)0x0123C9AC;
static const void* RTTI_ExtraSavedHavokData = (void*)0x0123C9D0;
static const void* RTTI_ExtraRefractionProperty = (void*)0x0123C9F4;
static const void* RTTI_ExtraStartingWorldOrCell = (void*)0x0123CA1C;
static const void* RTTI_ExtraHasNoRumors = (void*)0x0123CA44;
static const void* RTTI_ExtraSound = (void*)0x0123CA64;
static const void* RTTI_ExtraCreatureAwakeSound = (void*)0x0123CA80;
static const void* RTTI_ExtraWeaponIdleSound = (void*)0x0123CAA8;
static const void* RTTI_ExtraWeaponAttackSound = (void*)0x0123CACC;
static const void* RTTI_ExtraActivateLoopSound = (void*)0x0123CAF4;
static const void* RTTI_ExtraCanTalkToPlayer = (void*)0x0123CB1C;
static const void* RTTI_ExtraObjectHealth = (void*)0x0123CB40;
static const void* RTTI_ExtraTerminalState = (void*)0x0123CB60;
static const void* RTTI_ExtraNavMeshPortal = (void*)0x0123CB84;
static const void* RTTI_ExtraModelSwap = (void*)0x0123CBA8;
static const void* RTTI_ExtraRadius = (void*)0x0123CBC8;
static const void* RTTI_ExtraAmmo = (void*)0x0123CBE4;
static const void* RTTI_ExtraCombatStyle = (void*)0x0123CBFC;
static const void* RTTI_ExtraPatrolRefData = (void*)0x0123CC1C;
static const void* RTTI_ExtraOcclusionPlaneRefData = (void*)0x0123CC40;
static const void* RTTI_ExtraPortalRefData = (void*)0x0123CC6C;
static const void* RTTI_ExtraRoomRefData = (void*)0x0123CC90;
static const void* RTTI_ExtraPackageData = (void*)0x0123CCB0;
static const void* RTTI_ExtraCollisionData = (void*)0x0123CCD0;
static const void* RTTI_ExtraIgnoredBySandbox = (void*)0x0123CCF4;
static const void* RTTI_ExtraLightData = (void*)0x0123CD18;
static const void* RTTI_ExtraSceneData = (void*)0x0123CD38;
static const void* RTTI_ExtraBadPosition = (void*)0x0123CD58;
static const void* RTTI_ExtraHeadTrackingWeight = (void*)0x0123CD78;
static const void* RTTI_ExtraFavorCost = (void*)0x0123CDA0;
static const void* RTTI_ExtraTextDisplayData = (void*)0x0123CDC0;
static const void* RTTI_ExtraAlphaCutoff = (void*)0x0123CDE4;
static const void* RTTI_ExtraUniqueID = (void*)0x0123CE04;
static const void* RTTI_ExtraFlags = (void*)0x0123CE20;
static const void* RTTI_ExtraRefrPath = (void*)0x0123CE3C;
static const void* RTTI_ExtraDecalGroup = (void*)0x0123CE58;
static const void* RTTI_ExtraCellWaterEnvMap = (void*)0x0123CE78;
static const void* RTTI_ExtraRegionList = (void*)0x0123CE9C;
static const void* RTTI_ExtraCellMusicType = (void*)0x0123CEBC;
static const void* RTTI_ExtraCellAcousticSpace = (void*)0x0123CEE0;
static const void* RTTI_ExtraCellSkyRegion = (void*)0x0123CF08;
static const void* RTTI_ExtraCellImageSpace = (void*)0x0123CF2C;
static const void* RTTI_ExtraCellWaterType = (void*)0x0123CF50;
static const void* RTTI_ExtraNorthRotation = (void*)0x0123CF74;
static const void* RTTI_ExtraDetachTime = (void*)0x0123CF98;
static const void* RTTI_ExtraGIDBuffer = (void*)0x0123CFB8;
static const void* RTTI_ExtraStartingPosition = (void*)0x0123D1D0;
static const void* RTTI_ExtraOriginalReference = (void*)0x0123D1F4;
static const void* RTTI_ExtraPackageStartLocation = (void*)0x0123D21C;
static const void* RTTI_ExtraReferenceHandle = (void*)0x0123D244;
static const void* RTTI_ExtraSpawnContainer = (void*)0x0123D268;
static const void* RTTI_ExtraMultiBound = (void*)0x0123D28C;
static const void* RTTI_ExtraRoom = (void*)0x0123D2AC;
static const void* RTTI_ExtraSavedAnimation = (void*)0x0123D2C4;
static const void* RTTI_ExtraHeadingTarget = (void*)0x0123D2E8;
static const void* RTTI_ExtraActorCause = (void*)0x0123D30C;
static const void* RTTI_ExtraHorse = (void*)0x0123D32C;
static const void* RTTI_ExtraForcedTarget = (void*)0x0123D348;
static const void* RTTI_ExtraForcedLandingMarker = (void*)0x0123D368;
static const void* RTTI_ExtraWaterData = (void*)0x0123D390;
static const void* RTTI_ExtraCell3D = (void*)0x0123D3B0;
static const void* RTTI_ExtraMissingLinkedRefIDs = (void*)0x0123D3F0;
static const void* RTTI_ExtraOpenCloseActivateRef = (void*)0x0123D418;
static const void* RTTI_ExtraEnableStateParent = (void*)0x0123D440;
static const void* RTTI_ExtraAttachRef = (void*)0x0123D468;
static const void* RTTI_ExtraAshPileRef = (void*)0x0123D488;
static const void* RTTI_ExtraItemDropper = (void*)0x0123D4A8;
static const void* RTTI_ExtraMissingRefIDs = (void*)0x0123D4C8;
static const void* RTTI_ExtraFollower = (void*)0x0123D4EC;
static const void* RTTI_ExtraEnableStateChildren = (void*)0x0123D508;
static const void* RTTI_ExtraAttachRefChildren = (void*)0x0123D530;
static const void* RTTI_ExtraActivateRef = (void*)0x0123D558;
static const void* RTTI_ExtraActivateRefChildren = (void*)0x0123D578;
static const void* RTTI_ExtraReflectedRefs = (void*)0x0123D5A0;
static const void* RTTI_ExtraReflectorRefs = (void*)0x0123D5C4;
static const void* RTTI_ExtraWaterLightRefs = (void*)0x0123D5E8;
static const void* RTTI_ExtraLitWaterRefs = (void*)0x0123D60C;
static const void* RTTI_ExtraDroppedItemList = (void*)0x0123D62C;
static const void* RTTI_ExtraFriendHits = (void*)0x0123D650;
static const void* RTTI_ExtraFactionChanges = (void*)0x0123D670;
static const void* RTTI_ExtraGuardedRefData = (void*)0x0123D694;
static const void* RTTI_ExtraAliasInstanceArray = (void*)0x0123D6B8;
static const void* RTTI_ExtraPromotedRef = (void*)0x0123D6E0;
static const void* RTTI_ExtraLargeRefOwnerCells = (void*)0x0123D700;
static const void* RTTI_ExtraScriptedAnimDependence = (void*)0x0123D728;
static const void* RTTI_ExtraLinkedRef = (void*)0x0123D754;
static const void* RTTI_ExtraLinkedRefChildren = (void*)0x0123D774;
static const void* RTTI_ExtraAttachedArrows3D = (void*)0x0123D79C;
static const void* RTTI_ExtraWaterCurrentZoneData = (void*)0x0123D858;
static const void* RTTI_ExtraLight = (void*)0x0123C5AC;
static const void* RTTI_ExtraLeveledCreature = (void*)0x0123DA04;
static const void* RTTI_ExtraMapMarker = (void*)0x0123DA28;
static const void* RTTI_ExtraAction = (void*)0x0123DA48;
static const void* RTTI_ExtraContainerChanges = (void*)0x0123DA64;
static const void* RTTI_ExtraLockList = (void*)0x0123DA88;
static const void* RTTI_ExtraSoul = (void*)0x0123DAA4;
static const void* RTTI_ExtraGhost = (void*)0x0123DABC;
static const void* RTTI_ExtraShouldWear = (void*)0x0123DAD8;
static const void* RTTI_ExtraInfoGeneralTopic = (void*)0x0123DAF8;
static const void* RTTI_ExtraPackage = (void*)0x0123DB1C;
static const void* RTTI_ExtraPlayerCrimeList = (void*)0x0123DB38;
static const void* RTTI_ExtraPersistentCell = (void*)0x0123DB5C;
static const void* RTTI_ExtraRunOncePacks = (void*)0x0123DB80;
static const void* RTTI_ExtraDistantData = (void*)0x0123DBA0;
static const void* RTTI_ExtraOcclusionShape = (void*)0x0123DBC0;
static const void* RTTI_ExtraPortal = (void*)0x0123DBE4;
static const void* RTTI_ExtraEditorRefMoveData = (void*)0x0123DC00;
static const void* RTTI_ExtraSayTopicInfoOnceADay = (void*)0x0123DC28;
static const void* RTTI_ExtraSayToTopicInfo = (void*)0x0123DC50;
static const void* RTTI_ExtraPatrolRefInUseData = (void*)0x0123DC74;
static const void* RTTI_ExtraFollowerSwimBreadcrumbs = (void*)0x0123DC9C;
static const void* RTTI_ExtraAnimNoteReceiver = (void*)0x0123DCC8;
static const void* RTTI_ExtraGroupConstraint = (void*)0x0123DCEC;
static const void* RTTI_ExtraRaceData = (void*)0x0123DD10;
static const void* RTTI_ExtraAnimGraphManager = (void*)0x0123DD2C;
static const void* RTTI_ExtraInteraction = (void*)0x0123DD50;
static const void* RTTI_ExtraDismemberedLimbs = (void*)0x0123DD70;
static const void* RTTI_ExtraCellGrassData = (void*)0x0123DD94;
static const void* RTTI_ExtraProcessMiddleLow = (void*)0x01244318;
static const void* RTTI_ExtraUsedMarkers = (void*)0x01245468;
static const void* RTTI_ExtraReservedMarkers = (void*)0x01245488;

static void* (__cdecl* RTDynamicCast)(void*, UInt32, const void*, const void*, UInt32) = (void* (__cdecl*)(void*, UInt32, const void*, const void*, UInt32))0x00F51DAE;

static const void* RTTIForExtraType[0xB4] = {
	NULL,						// 0x0
	RTTI_ExtraHavok,			// 0x1,
	RTTI_ExtraCell3D,			// 0x2,
	RTTI_ExtraCellWaterType,	// 0x3,
	RTTI_ExtraRegionList,		// 0x4,
	RTTI_ExtraSeenData,			// 0x5,
	RTTI_ExtraEditorID,			// 0x6,
	RTTI_ExtraCellMusicType,	// 0x7,
	RTTI_ExtraCellSkyRegion,	// 0x8,
	RTTI_ExtraProcessMiddleLow,	// 0x9,
	RTTI_ExtraDetachTime,		// 0xA,
	RTTI_ExtraPersistentCell,	// 0xB,
	NULL,						// 0xC,
	RTTI_ExtraAction,			// 0xD,
	RTTI_ExtraStartingPosition,	// 0xE,
	NULL,						// 0xF,
	RTTI_ExtraAnimGraphManager,	// 0x10,
	NULL,						// 0x11,
	RTTI_ExtraUsedMarkers,		// 0x12,
	RTTI_ExtraDistantData,		// 0x13,
	RTTI_ExtraRagDollData,		// 0x14,
	RTTI_ExtraContainerChanges,	// 0x15,
	RTTI_ExtraWorn,				// 0x16,
	RTTI_ExtraWornLeft,			// 0x17,
	RTTI_ExtraPackageStartLocation,	// 0x18,
	RTTI_ExtraPackage,			// 0x19,
	RTTI_ExtraTresPassPackage,	// 0x1A,
	RTTI_ExtraRunOncePacks,		// 0x1B,
	RTTI_ExtraReferenceHandle,	// 0x1C,
	RTTI_ExtraFollower,			// 0x1D,
	RTTI_ExtraLevCreaModifier,	// 0x1E,
	RTTI_ExtraGhost,			// 0x1F,
	RTTI_ExtraOriginalReference,	// 0x20,
	RTTI_ExtraOwnership,		// 0x21,
	RTTI_ExtraGlobal,			// 0x22,
	RTTI_ExtraRank,				// 0x23,
	RTTI_ExtraCount,			// 0x24,
	RTTI_ExtraHealth,			// 0x25,
	NULL,						// 0x26,
	RTTI_ExtraTimeLeft,			// 0x27,
	RTTI_ExtraCharge,			// 0x28,
	RTTI_ExtraLight,			// 0x29,
	RTTI_ExtraLock,				// 0x2A,
	RTTI_ExtraTeleport,			// 0x2B,
	RTTI_ExtraMapMarker,		// 0x2C,
	RTTI_ExtraLeveledCreature,	// 0x2D,
	RTTI_ExtraLeveledItem,		// 0x2E,
	RTTI_ExtraScale,			// 0x2F,
	NULL,						// 0x30,	was ExtraSeed, removed in 1.7.7.0
	NULL,						// 0x31,
	NULL,						// 0x32,
	NULL,						// 0x33,
	RTTI_ExtraPlayerCrimeList,	// 0x34,
	NULL,						// 0x35
	RTTI_ExtraEnableStateParent,	// 0x36,
	RTTI_ExtraEnableStateChildren,	// 0x37,
	RTTI_ExtraItemDropper,		// 0x38,
	RTTI_ExtraDroppedItemList,	// 0x39,
	RTTI_ExtraRandomTeleportMarker, // 0x3A,
	NULL,						// 0x3B
	RTTI_ExtraSavedHavokData,	// 0x3C,
	RTTI_ExtraCannotWear,		// 0x3D,
	RTTI_ExtraPoison,			// 0x3E,
	NULL,						// 0x3F
	RTTI_ExtraLastFinishedSequence,	// 0x40,
	RTTI_ExtraSavedAnimation,	// 0x41,
	RTTI_ExtraNorthRotation,	// 0x42,
	RTTI_ExtraSpawnContainer,	// 0x43,
	RTTI_ExtraFriendHits,		// 0x44,
	RTTI_ExtraHeadingTarget,	// 0x45,
	NULL,						// 0x46
	RTTI_ExtraRefractionProperty,	// 0x47,
	RTTI_ExtraStartingWorldOrCell,	// 0x48,
	RTTI_ExtraHotkey,			// 0x49,
	NULL,						// 0x4A
	RTTI_ExtraEditorRefMoveData,	// 0x4B,
	RTTI_ExtraInfoGeneralTopic,	// 0x4C,
	RTTI_ExtraHasNoRumors,		// 0x4D,
	RTTI_ExtraSound,			// 0x4E,
	RTTI_ExtraTerminalState,	// 0x4F,
	RTTI_ExtraLinkedRef,		// 0x50,
	RTTI_ExtraLinkedRefChildren,	// 0x51,
	RTTI_ExtraActivateRef,		// 0x52,
	RTTI_ExtraActivateRefChildren,	// 0x53,
	RTTI_ExtraCanTalkToPlayer,	// 0x54,
	RTTI_ExtraObjectHealth,		// 0x55,
	RTTI_ExtraCellImageSpace,	// 0x56,
	RTTI_ExtraNavMeshPortal,	// 0x57,
	RTTI_ExtraModelSwap,		// 0x58,
	RTTI_ExtraRadius,			// 0x59,
	NULL,						// 0x5A,
	RTTI_ExtraFactionChanges,	// 0x5B,
	RTTI_ExtraDismemberedLimbs,	// 0x5C,
	RTTI_ExtraActorCause,		// 0x5D,
	RTTI_ExtraMultiBound,		// 0x5E,
	NULL,						// 0x5F,	was ExtraMultiBoundData, removed in 1.7.7.0
	RTTI_ExtraMultiBoundRef,	// 0x60,
	RTTI_ExtraReflectedRefs,	// 0x61,
	RTTI_ExtraReflectorRefs,	// 0x62,
	RTTI_ExtraEmittanceSource,	// 0x63,
	NULL,						// 0x64,	was ExtraRadioData, removed in 1.7.7.0
	RTTI_ExtraCombatStyle,		// 0x65,
	NULL,						// 0x66,
	RTTI_ExtraPrimitive,		// 0x67,
	RTTI_ExtraOpenCloseActivateRef,	// 0x68,
	RTTI_ExtraAnimNoteReceiver,	// 0x69,
	RTTI_ExtraAmmo,				// 0x6A,
	RTTI_ExtraPatrolRefData,	// 0x6B,
	RTTI_ExtraPackageData,		// 0x6C,
	RTTI_ExtraOcclusionShape,	// 0x6D,
	RTTI_ExtraCollisionData,	// 0x6E,
	RTTI_ExtraSayTopicInfoOnceADay,	// 0x6F,
	RTTI_ExtraEncounterZone,	// 0x70,
	RTTI_ExtraSayToTopicInfo,		// 0x71,
	RTTI_ExtraOcclusionPlaneRefData,	// 0x72,
	RTTI_ExtraPortalRefData,	// 0x73,
	RTTI_ExtraPortal,			// 0x74,
	RTTI_ExtraRoom,				// 0x75,
	RTTI_ExtraHealthPerc,		// 0x76,
	RTTI_ExtraRoomRefData,		// 0x77,
	RTTI_ExtraGuardedRefData,	// 0x78,
	RTTI_ExtraCreatureAwakeSound,	// 0x79,
	NULL,						// 0x7A,
	RTTI_ExtraHorse,			// 0x7B,
	RTTI_ExtraIgnoredBySandbox,	// 0x7C,
	RTTI_ExtraCellAcousticSpace,	// 0x7D,
	RTTI_ExtraReservedMarkers,	// 0x7E,
	RTTI_ExtraWeaponIdleSound,	// 0x7F,
	RTTI_ExtraWaterLightRefs,	// 0x80,
	RTTI_ExtraLitWaterRefs,		// 0x81,
	RTTI_ExtraWeaponAttackSound,	// 0x82,
	RTTI_ExtraActivateLoopSound,	// 0x83,
	RTTI_ExtraPatrolRefInUseData,	// 0x84,
	RTTI_ExtraAshPileRef,		// 0x85,
	NULL,						// 0x86
	RTTI_ExtraFollowerSwimBreadcrumbs,	// 0x87,
	RTTI_ExtraAliasInstanceArray,	// 0x88,
	RTTI_ExtraLocation,			// 0x89,
	NULL,						// 0x8A,
	RTTI_ExtraLocationRefType,	// 0x8B,
	RTTI_ExtraPromotedRef,		// 0x8C,
	NULL,						// 0x8D,
	RTTI_ExtraOutfitItem,		// 0x8E,
	NULL,						// 0x8F,
	RTTI_ExtraLeveledItemBase,	// 0x90,
	RTTI_ExtraLightData,		// 0x91,
	RTTI_ExtraSceneData,		// 0x92,
	RTTI_ExtraBadPosition,		// 0x93,
	RTTI_ExtraHeadTrackingWeight,	// 0x94,
	RTTI_ExtraFromAlias,		// 0x95,
	RTTI_ExtraShouldWear,		// 0x96,
	RTTI_ExtraFavorCost,		// 0x97,
	RTTI_ExtraAttachedArrows3D,	// 0x98,
	RTTI_ExtraTextDisplayData,	// 0x99,
	RTTI_ExtraAlphaCutoff,		// 0x9A,
	RTTI_ExtraEnchantment,		// 0x9B,
	RTTI_ExtraSoul,				// 0x9C,
	RTTI_ExtraForcedTarget,		// 0x9D,
	NULL,						// 0x9E,
	RTTI_ExtraUniqueID,			// 0x9F,
	RTTI_ExtraFlags,			// 0xA0,
	RTTI_ExtraRefrPath,			// 0xA1,
	RTTI_ExtraDecalGroup,		// 0xA2,
	RTTI_ExtraLockList,			// 0xA3,
	RTTI_ExtraForcedLandingMarker,	// 0xA4,
	RTTI_ExtraLargeRefOwnerCells,	// 0xA5,
	RTTI_ExtraCellWaterEnvMap,	// 0xA6,
	RTTI_ExtraCellGrassData,	// 0xA7,
	RTTI_ExtraTeleportName,		// 0xA8,
	RTTI_ExtraInteraction,		// 0xA9,
	RTTI_ExtraWaterData,		// 0xAA,
	RTTI_ExtraWaterCurrentZoneData,	// 0xAB,
	RTTI_ExtraAttachRef,		// 0xAC,
	RTTI_ExtraAttachRefChildren,	// 0xAD,
	RTTI_ExtraGroupConstraint,	// 0xAE,
	RTTI_ExtraScriptedAnimDependence, // 0xAF,
	RTTI_ExtraCachedScale,		// 0xB0,
	RTTI_ExtraRaceData,			// 0xB1,
	RTTI_ExtraGIDBuffer,		// 0xB2,
	RTTI_ExtraMissingRefIDs,	// 0xB3
};

class CommandParam {
public:
	enum ParamType {
		kParamType_String			= 0x00,
		kParamType_Integer			= 0x01,
		kParamType_Float			= 0x02,
		kParamType_ObjectRef        = 0x04,
	};

	const char* typeStr;
	UInt32		typeID;		// ParamType
	UInt32		isOptional;
};
assert(sizeof(CommandParam) == 0x00C);

struct CommandArgs {
	CommandParam*	 paramInfo;		// 00
	void*			 arg1;			// 04
	TESObjectREFR*   thisObj;		// 08
	TESObjectREFR*	 Obj;			// 0C
	Script*			 scriptObj;		// 10
	ScriptEventList* eventList;		// 14
	double*			 result;		// 18
	UInt32*			 opcodeOffset;	// 1C
};
assert(sizeof(CommandArgs) == 0x020);

struct CommandInfo {
	const char*		longName;		// 00
	const char*		shortName;		// 04
	UInt32			opcode;			// 08
	const char*		helpText;		// 0C
	UInt16			needsParent;	// 10
	UInt16			numParams;		// 12
	CommandParam*	params;			// 14
	void*			execute;		// 18
	void*			parse;			// 1C
	void*			eval;			// 20
	UInt32			flags;			// 24
};
assert(sizeof(CommandInfo) == 0x028);

class CommandTable {
public:
	struct PatchLocation {
		UInt32	Ptr;
		UInt32	Offset;
		UInt32	Type;
	};

	std::vector<CommandInfo>	Commands;
	UInt32						BaseID;
	UInt32						CurID;
	bool						Patched;

	void Initialize() {

		BaseID = 0x1000;
		CurID = 0x1000;
		Commands.reserve(0x1480);
		for (const CommandInfo* Cmd = (CommandInfo*)0x0124E880; Cmd != (CommandInfo*)0x01255B30; ++Cmd) {
			Commands.push_back(*Cmd); CurID++;
		}

	};

	void Add(CommandInfo* Cmd) {

		Cmd->opcode = CurID; CurID++;
		Cmd->parse = (void*)0x00517F40;
		Commands.push_back(*Cmd);

	};

	void Patch(const PatchLocation* Patch, UInt32 Data) {

		for (; Patch->Ptr; ++Patch) {
			switch (Patch->Type) {
				case 0:
					SafeWrite32(Patch->Ptr, Data + Patch->Offset);
					break;
				case 1:
					SafeWrite16(Patch->Ptr, Data + Patch->Offset);
					break;
			}
		}

	}

	void Set() {

		const PatchLocation ScriptCommandsPatchStart[] = {
			{ 0x00516B0B, 0x00 },
			{ 0x00516CD4, 0x04 },
			{ 0x00516D6D, 0x08 },
			{ 0x00517D87, 0x00 },
			{ 0x0051B33F, 0x00 },
			{ 0x00542459, 0x0C },
			{ 0x00542471, 0x00 },
			{ 0x00542489, 0x04 },
			{ 0x005424A5, 0x0C },
			{ 0x005424BF, 0x04 },
			{ 0x005424DD, 0x00 },
			{ 0x005424FF, 0x00 },
			{ 0x0054251D, 0x04 },
			{ 0x00542543, 0x00 },
			{ 0x0054255A, 0x00 },
			{ 0x005EA479, 0x20 },
			{ 0x005EA485, 0x10 },
			{ 0x005EA54E, 0x12 },
			{ 0x005EA591, 0x12 },
			{ 0x005EA59D, 0x14 },
			{ 0x005EA5D8, 0x12 },
			{ 0x005EA5E5, 0x14 },
			{ 0x005EA646, 0x12 },
			{ 0x005EA652, 0x14 },
			{ 0x005EA680, 0x12 },
			{ 0x005EA6F1, 0x12 },
			{ 0x005EA723, 0x12 },
			{ 0x005EA72F, 0x14 },
			{ 0x005EA785, 0x12 },
			{ 0x005EA7C3, 0x12 },
			{ 0x005EA7CF, 0x14 },
			{ 0x005EA878, 0x12 },
			{ 0x005EA8A7, 0x14 },
			{ 0x005EA984, 0x12 },
			{ 0x005EA9A6, 0x14 },
			{ 0x005EAABE, 0x12 },
			{ 0x005EAB08, 0x12 },
			{ 0x005EAB18, 0x14 },
			{ 0x005EABB1, 0x14 },
			{ 0x006A2D0C, 0x12 },
			{ 0x006A2D39, 0x14 },
			{ 0 },
		};

		const PatchLocation ScriptCommandsPatchEnd[] = {
			{ 0x00516C12, 0x08 },
			{ 0x00516CFF, 0x04 },
			{ 0 },
		};

		const PatchLocation ScriptCommandsPatchMaxIdx[] = {
			{ 0x00502C10 + 0x0087 + 1,	0 },
			{ 0x00516AD0 + 0x0029 + 2,	(UInt32)(-0x1001) },
			{ 0x00516C10 + 0x0000 + 6,	0 },
			{ 0x00517C20 + 0x0156 + 1,	(UInt32)(-0x1001) },
			{ 0x0051ABE0 + 0x0751 + 2,	(UInt32)(-0x1001) },
			{ 0x005E98C0 + 0x000D + 2,	(UInt32)(-0x1001) },
			{ 0x005E98C0 + 0x001D + 1,	(UInt32)(-0x1001) },
			{ 0x005E98C0 + 0x0029 + 2,	(UInt32)(-0x1001) },
			{ 0 },
		};
		
		Patch(ScriptCommandsPatchStart, (UInt32)&Commands.front());
		Patch(ScriptCommandsPatchEnd, (UInt32)&Commands.back());
		Patch(ScriptCommandsPatchMaxIdx, Commands.size() + BaseID);
	};

};

template <typename T>
class TList {
public:
	struct Entry {
		T*		item;
		Entry*	next;

		T*		Item() const { return item; }
		Entry*	Next() const { return next; }
	};

	class Iterator {
	public:
		Entry* m_cur;

		Iterator() : m_cur(NULL) {}
		Iterator(Entry* entry) : m_cur(entry) {}
		Iterator operator ++ () { if (!End()) m_cur = m_cur->Next(); return *this; }
		bool End() { return m_cur == NULL; }
		const T* operator -> () { return (m_cur) ? m_cur->Item() : NULL; }
		const T* operator * () { return (m_cur) ? m_cur->Item() : NULL; }
		const Iterator& operator = (const Iterator& rhs) {
			m_cur = rhs.m_cur;
			return *this;
		}
		T* Get() { return (m_cur) ? m_cur->Item() : NULL; }
	};

	const Iterator Begin() const { return Iterator(const_cast<Entry*>(&First)); }

	Entry First;
};
assert(sizeof(TList<void>) == 0x008);

template <class T>
class TArray {
public:
	T*		data;
	UInt32	capacity;
	UInt32	count;
};
assert(sizeof(TArray<void>) == 0x00C);

class RGBA {
public:
	UInt8	r;
	UInt8	g;
	UInt8	b;
	UInt8	a;
};
assert(sizeof(RGBA) == 0x004);

class SimpleLock {
public:
	enum {
		kFastSpinThreshold = 10000
	};
	volatile SInt32	threadID;	// 00
	UInt32			lockCount;	// 04
};

class BSIntrusiveRefCounted {
public:
	volatile UInt32		m_refCount;		// 00
};
assert(sizeof(BSIntrusiveRefCounted) == 0x04);

template <typename T>
class BSTEventSink {
public:
	virtual ~BSTEventSink();
	virtual	UInt32	ReceiveEvent(T* evn, void* dispatcher); // pure virtual	EventResult	ReceiveEvent(T * evn, EventDispatcher<T> * dispatcher);
};
assert(sizeof(BSTEventSink<void>) == 0x04);

template <typename T>
class EventDispatcher {
public:
	SimpleLock					lock;				// 000
	TArray<BSTEventSink<T>*>	eventSinks;			// 008 TArray<SinkT*> typedef BSTEventSink<T> SinkT;
	TArray<BSTEventSink<T>*>	addBuffer;			// 014 TArray<SinkT*> typedef BSTEventSink<T> SinkT; - schedule for add
	TArray<BSTEventSink<T>*>	removeBuffer;		// 020 TArray<SinkT*> typedef BSTEventSink<T> SinkT; - schedule for remove
	UInt8						stateFlag;			// 02C - some internal state changed while sending
	UInt8						pad[3];
};
assert(sizeof(EventDispatcher<void>) == 0x30);

class BSString {
public:
	const char* m_data;		// 00
	UInt16		m_dataLen;  // 04
	UInt16		m_bufLen;	// 06
};
assert(sizeof(BSString) == 0x008);

class BSFixedString {
public:
	void	Create(const char* src) { ThisCall(0x00A511C0, this, src); }
	void	Dispose() { ThisCall(0x00A511B0, this); }
	void	Set(const char* src) { ThisCall(0x00A51210, this, src); }

	const char* m_data;		// 00

	bool operator == (const BSFixedString& lhs) const { return m_data == lhs.m_data; }
	bool operator < (const BSFixedString& lhs) const { return m_data < lhs.m_data; }

};
assert(sizeof(BSFixedString) == 0x04);

class InputEvent {
public:
	enum EventType {
		kEventType_Button = 0,
		kEventType_MouseMove,
		kEventType_Char,
		kEventType_Thumbstick,
		kEventType_DeviceConnect,
		kEventType_Kinect
	};

	virtual	~InputEvent();
	virtual bool			IsIDEvent();
	virtual BSFixedString*	GetControlID();

	UInt32			deviceType;	// 04
	UInt32			eventType;	// 08
	InputEvent*		next;		// 0C
};
assert(sizeof(InputEvent) == 0x10);

class ButtonEvent : public InputEvent {
public:
	BSFixedString	controlID;	// 10
	UInt32			keyMask;	// 14
	UInt32			flags;		// 18 (00000038 when ALT is pressed, 0000001D when STRG is pressed)
	float			timer;		// 1C (hold duration)
};
assert(sizeof(ButtonEvent) == 0x20);

class PlayerInputHandler {
public:
	virtual	~PlayerInputHandler();
	virtual void Unk_01();
	virtual void Unk_02();
	virtual void Unk_03();
	virtual void ManageButtonEvent(ButtonEvent* Arg1, int Arg2);

	UInt8		unk04;			// 04
	UInt8		pad04[3];
};
assert(sizeof(PlayerInputHandler) == 0x08);

class InputStringHolder {
public:
	static InputStringHolder*	Get() { return (InputStringHolder*)0x01B8FB00; }

	void*			unk00;				// 000
	BSFixedString	forward;			// 004 "Forward"
	BSFixedString	back;				// 008 "Back"
	BSFixedString	strafeLeft;			// 00C "Strafe Left"
	BSFixedString	strafeRight;		// 010 "Strafe Right"
	BSFixedString	move;				// 014 "Move"
	BSFixedString	look;				// 018 "Look"
	BSFixedString	activate;			// 01C "Activate"
	BSFixedString	leftAttack;			// 020 "Left Attack/Block"
	BSFixedString	rightAttack;		// 024 "Right Attack/Block"
	BSFixedString	dualAttack;			// 028 "Dual Attack"
	BSFixedString	forceRelease;		// 02C "ForceRelease"
	BSFixedString	pause;				// 030 "Pause"
	BSFixedString	readyWeapon;		// 034 "Ready Weapon"
	BSFixedString	togglePOV;			// 038 "Toggle POV"
	BSFixedString	jump;				// 03C "Jump"
	BSFixedString	journal;			// 040 "Journal"
	BSFixedString	sprint;				// 044 "Sprint"
	BSFixedString	sneak;				// 048 "Sneak"
	BSFixedString	shout;				// 04C "Shout"
	BSFixedString	kinectShout;		// 050 "KinectShout"
	BSFixedString	grab;				// 054 "Grab"
	BSFixedString	run;				// 058 "Run"
	BSFixedString	toggleRun;			// 05C "Toggle Always Run"
	BSFixedString	autoMove;			// 060 "Auto-Move"
	BSFixedString	quicksave;			// 064 "Quicksave"
	BSFixedString	quickload;			// 068 "Quickload"
	BSFixedString	newSave;			// 06C "NewSave"
	BSFixedString	inventory;			// 070 "Inventory"
	BSFixedString	stats;				// 074 "Stats"
	BSFixedString	map;				// 078 "Map"
	BSFixedString	screenshot;			// 07C "Screenshot"
	BSFixedString	multiScreenshot;	// 080 "Multi-Screenshot"
	BSFixedString	console;			// 084 "Console"
	BSFixedString	cameraPath;			// 088 "CameraPath"
	BSFixedString	tweenMenu;			// 08C "Tween Menu"
	BSFixedString	takeAll;			// 090 "Take All"
	BSFixedString	accept;				// 094 "Accept"
	BSFixedString	cancel;				// 098 "Cancel"
	BSFixedString	up;					// 09C "Up"
	BSFixedString	down;				// 0A0 "Down"
	BSFixedString	left;				// 0A4 "Left"
	BSFixedString	right;				// 0A8 "Right"
	BSFixedString	pageUp;				// 0AC "PageUp"
	BSFixedString	pageDown;			// 0B0 "PageDown"
	BSFixedString	pick;				// 0B4 "Pick"
	BSFixedString	pickNext;			// 0B8 "PickNext"
	BSFixedString	pickPrevious;		// 0BC "PickPrevious"
	BSFixedString	cursor;				// 0C0 "Cursor"
	BSFixedString	kinect;				// 0C4 "Kinect"
	BSFixedString	sprintStart;		// 0C8 "SprintStart"
	BSFixedString	sprintStop;			// 0CC "SprintStop"
	BSFixedString	sneakStart;			// 0D0 "sneakStart"
	BSFixedString	sneakStop;			// 0D4 "sneakStop"
	BSFixedString	blockStart;			// 0D8 "blockStart"
	BSFixedString	blockStop;			// 0DC "blockStop"
	BSFixedString	blockBash;			// 0E0 "blockBash"
	BSFixedString	attackStart;		// 0E4 "attackStart"
	BSFixedString	attackPowerStart;	// 0E8 "attackPowerStart"
	BSFixedString	reverseDirection;	// 0EC "reverseDirection"
	BSFixedString	unequip;			// 0F0 "Unequip"
	BSFixedString	zoomIn;				// 0F4 "Zoom In"
	BSFixedString	zoomOut;			// 0F8 "Zoom Out"
	BSFixedString	rotateItem;			// 0FC "RotateItem"
	BSFixedString	leftStick;			// 100 "Left Stick"
	BSFixedString	prevPage;			// 104 "PrevPage"
	BSFixedString	nextPage;			// 108 "NextPage"
	BSFixedString	prevSubPage;		// 10C "PrevSubPage"
	BSFixedString	nextSubPage;		// 110 "NextSubPage"
	BSFixedString	leftEquip;			// 114 "LeftEquip"
	BSFixedString	rightEquip;			// 118 "RightEquip"
	BSFixedString	toggleFavorite;		// 11C "ToggleFavorite"
	BSFixedString	favorites;			// 120 "Favorites"
	BSFixedString	hotkey1;			// 124 "Hotkey1"
	BSFixedString	hotkey2;			// 128 "Hotkey2"
	BSFixedString	hotkey3;			// 12C "Hotkey3"
	BSFixedString	hotkey4;			// 130 "Hotkey4"
	BSFixedString	hotkey5;			// 134 "Hotkey5"
	BSFixedString	hotkey6;			// 138 "Hotkey6"
	BSFixedString	hotkey7;			// 13C "Hotkey7"
	BSFixedString	hotkey8;			// 140 "Hotkey8"
	BSFixedString	quickInventory;		// 144 "Quick Inventory"
	BSFixedString	quickMagic;			// 148 "Quick Magic"
	BSFixedString	quickStats;			// 14C "Quick Stats"
	BSFixedString	quickMap;			// 150 "Quick Map"
	BSFixedString	toggleCursor;		// 154 "ToggleCursor"
	BSFixedString	wait;				// 158 "Wait"
	BSFixedString	click;				// 15C "Click"
	BSFixedString	mapLookMode;		// 160 "MapLookMode"
	BSFixedString	equip;				// 164 "Equip"
	BSFixedString	dropItem;			// 168 "DropItem"
	BSFixedString	rotate;				// 16C "Rotate"
	BSFixedString	nextFocus;			// 170 "NextFocus"
	BSFixedString	prevFocus;			// 174 "PreviousFocus"
	BSFixedString	setActiveQuest;		// 178 "SetActiveQuest"
	BSFixedString	placePlayerMarker;	// 17C "PlacePlayerMarker"
	BSFixedString	xButton;			// 180 "XButton"
	BSFixedString	yButton;			// 184 "YButton"
	BSFixedString	chargeItem;			// 188 "ChargeItem"
	UInt32			unk18C;				// 18C
	BSFixedString	playerPosition;		// 190 "PlayerPosition"
	BSFixedString	localMap;			// 194 "LocalMap"
	BSFixedString	localMapMoveMode;	// 198 "LocalMapMoveMode"
	BSFixedString	itemZoom;			// 19C "Item Zoom"
};
assert(sizeof(InputStringHolder) == 0x1A0);

class UIStringHolder {
public:
	static UIStringHolder* Get() { return (UIStringHolder*)0x01B33070; }

	void*			unk00;						// 000
	BSFixedString	faderData;					// 004 "FaderData"
	BSFixedString	hudData;					// 008 "HUDData"
	BSFixedString	hudCamData;					// 00C "HUDCamData"
	BSFixedString	floatingQuestMarkers;		// 010 "FloatingQuestMarkers"
	BSFixedString	consoleData;				// 014 "ConsoleData"
	BSFixedString	quantityData;				// 018 "QuantityData"
	BSFixedString	messageBoxData;				// 01C "MessageBoxData"
	BSFixedString	bsUIScaleformData;			// 020 "BSUIScaleformData"
	BSFixedString	bsUIMessageData;			// 024 "BSUIMessageData"
	BSFixedString	bsUIAnalogData;				// 028 "BSUIAnalogData"
	BSFixedString	inventoryUpdateData;		// 02C "InventoryUpdateData"
	BSFixedString	refHandleUIData;			// 030 "RefHandleUIData"
	BSFixedString	tesFormUIData;				// 034 "TESFormUIData"
	BSFixedString	loadingMenuData;			// 038 "LoadingMenuData"
	BSFixedString	kinectStateData;			// 03C "KinectStateChangeData"
	BSFixedString	kinectUserEventData;		// 040 "KinectUserEventData"
	BSFixedString	inventoryMenu;				// 044 "InventoryMenu"
	BSFixedString	console;					// 048 "Console"
	BSFixedString	dialogueMenu;				// 04C "Dialogue Menu"
	BSFixedString	hudMenu;					// 050 "HUD Menu"
	BSFixedString	mainMenu;					// 054 "Main Menu"
	BSFixedString	messageBoxMenu;				// 058 "MessageBoxMenu"
	BSFixedString	cursorMenu;					// 05C "Cursor Menu"
	BSFixedString	faderMenu;					// 060 "Fader Menu"
	BSFixedString	magicMenu;					// 064 "MagicMenu"
	BSFixedString	topMenu;					// 068 "Top Menu"
	BSFixedString	overlayMenu;				// 06C "Overlay Menu"
	BSFixedString	overlayInteractionMenu;		// 070 "Overlay Interaction Menu"
	BSFixedString	loadingMenu;				// 074 "Loading Menu"
	BSFixedString	tweenMenu;					// 078 "TweenMenu"
	BSFixedString	barterMenu;					// 07C "BarterMenu"
	BSFixedString	giftMenu;					// 080 "GiftMenu"
	BSFixedString	debugTextMenu;				// 084 "Debug Text Menu"
	BSFixedString	mapMenu;					// 088 "MapMenu"
	BSFixedString	lockpickingMenu;			// 08C "Lockpicking Menu"
	BSFixedString	quantityMenu;				// 090 "Quantity Menu"
	BSFixedString	statsMenu;					// 094 "StatsMenu"
	BSFixedString	containerMenu;				// 098 "ContainerMenu"
	BSFixedString	sleepWaitMenu;				// 09C "Sleep/Wait Menu"
	BSFixedString	levelUpMenu;				// 0A0 "LevelUp Menu"
	BSFixedString	journalMenu;				// 0A4 "Journal Menu"
	BSFixedString	bookMenu;					// 0A8 "Book Menu"
	BSFixedString	favoritesMenu;				// 0AC "FavoritesMenu"
	BSFixedString	raceSexMenu;				// 0B0 "RaceSex Menu"
	BSFixedString	craftingMenu;				// 0B4 "Crafting Menu"
	BSFixedString	trainingMenu;				// 0B8 "Training Menu"
	BSFixedString	mistMenu;					// 0BC "Mist Menu"
	BSFixedString	tutorialMenu;				// 0C0 "Tutorial Menu"
	BSFixedString	creditsMenu;				// 0C4 "Credits Menu"
	BSFixedString	titleSequenceMenu;			// 0C8 "TitleSequence Menu"
	BSFixedString	consoleNativeUIMenu;		// 0CC "Console Native UI Menu"
	BSFixedString	kinectMenu;					// 0D0 "Kinect Menu"
	BSFixedString	textWidget;					// 0D4 "TextWidget"
	BSFixedString	buttonBarWidget;			// 0D8 "ButtonBarWidget"
	BSFixedString	graphWidget;				// 0DC "GraphWidget"
	BSFixedString	textureWidget;				// 0E0 "TextureWidget"
	BSFixedString	uiMenuOK;					// 0E4 "UIMenuOK"
	BSFixedString	uiMenuCancel;				// 0E8 "UIMenuCancel"
	BSFixedString	showText;					// 0EC "Show Text"
	BSFixedString	hideText;					// 0F0 "Hide Text"
	BSFixedString	showList;					// 0F4 "Show List"
	BSFixedString	voiceReady;					// 0F8 "Voice Ready"
	BSFixedString	dmfoStr;					// 0FC "DMFOStr"
	BSFixedString	showJournal;				// 100 "Show Journal"
	BSFixedString	journalSettingsSaved;		// 104 "Journal Settings Saved"
	BSFixedString	closeMenu;					// 108 "CloseMenu"
	BSFixedString	closingAllMenus;			// 10C "Closing All Menus"
	BSFixedString	refreshMenu;				// 110 "RefreshMenu"
	BSFixedString	menuTextureDegradeEvent;	// 114 "Menu Texture Degrade Event"
	BSFixedString	diamondMarker;				// 118 "<img src='DiamondMarker' width='10' height='15' align='baseline' vspace='5'>"
};

class BSExtraData {
public:
	virtual ~BSExtraData();
	virtual UInt32 GetType();

	enum ExtraDataType {
		kExtraData_Havok					= 0x1,
		kExtraData_Cell3D					= 0x2,
		kExtraData_CellWaterType			= 0x3,
		kExtraData_RegionList				= 0x4,
		kExtraData_SeenData					= 0x5,
		kExtraData_EditorID					= 0x6,
		kExtraData_CellMusicType			= 0x7,
		kExtraData_CellSkyRegion			= 0x8,
		kExtraData_ProcessMiddleLow			= 0x9,
		kExtraData_DetachTime				= 0xA,
		kExtraData_PersistentCell			= 0xB,
		// ??								= 0xC,
		kExtraData_Action					= 0xD,
		kExtraData_StartingPosition			= 0xE,
		// ??								= 0xF,
		kExtraData_AnimGraphManager			= 0x10,
		// ??								= 0x11,
		kExtraData_UsedMarkers				= 0x12,
		kExtraData_DistantData				= 0x13,
		kExtraData_RagDollData				= 0x14,
		kExtraData_InventoryChanges			= 0x15,
		kExtraData_Worn						= 0x16,
		kExtraData_WornLeft					= 0x17,
		kExtraData_PackageStartLocation		= 0x18,
		kExtraData_Package					= 0x19,
		kExtraData_TresPassPackage			= 0x1A,
		kExtraData_RunOncePacks				= 0x1B,
		kExtraData_ReferenceHandle			= 0x1C,
		kExtraData_Follower					= 0x1D,
		kExtraData_LevCreaModifier			= 0x1E,
		kExtraData_Ghost					= 0x1F,
		kExtraData_OriginalReference		= 0x20,
		kExtraData_Ownership				= 0x21,
		kExtraData_Global					= 0x22,
		kExtraData_Rank						= 0x23,
		kExtraData_Count					= 0x24,
		kExtraData_Health					= 0x25,
		// ??								= 0x26,
		kExtraData_TimeLeft					= 0x27,
		kExtraData_Charge					= 0x28,
		kExtraData_Light					= 0x29,
		kExtraData_Lock						= 0x2A,
		kExtraData_Teleport					= 0x2B,
		kExtraData_MapMarker				= 0x2C,
		kExtraData_LeveledCreature			= 0x2D,
		kExtraData_LeveledItem				= 0x2E,
		kExtraData_Scale					= 0x2F,
		kExtraData_Seed						= 0x30,
		kExtraData_MagicCaster				= 0x31, // ExtraMagicLight??
		// ??								= 0x32, 
		// ??								= 0x33, 
		kExtraData_PlayerCrimeList			= 0x34,
		// ??								= 0x35,
		kExtraData_EnableStateParent		= 0x36,
		kExtraData_EnableStateChildren		= 0x37,
		kExtraData_ItemDropper				= 0x38,
		kExtraData_DroppedItemList			= 0x39,
		kExtraData_RandomTeleportMarker		= 0x3A,
		//??								= 0x3B
		kExtraData_SavedHavokData			= 0x3C,
		kExtraData_CannotWear				= 0x3D,
		kExtraData_Poison					= 0x3E,
		//??								= 0x3F
		kExtraData_LastFinishedSequence		= 0x40,
		kExtraData_SavedAnimation			= 0x41,
		kExtraData_NorthRotation			= 0x42,
		kExtraData_SpawnContainer			= 0x43,
		kExtraData_FriendHits				= 0x44,
		kExtraData_HeadingTarget			= 0x45,
		//??								= 0x46
		kExtraData_RefractionProperty		= 0x47,
		kExtraData_StartingWorldOrCell		= 0x48,
		kExtraData_Hotkey					= 0x49,
		//??								= 0x4A
		kExtraData_EditiorRefMoveData		= 0x4B,
		kExtraData_InfoGeneralTopic			= 0x4C,
		kExtraData_HasNoRumors				= 0x4D,
		kExtraData_Sound					= 0x4E,
		kExtraData_TerminalState			= 0x4F,
		kExtraData_LinkedRef				= 0x50,
		kExtraData_LinkedRefChildren		= 0x51,
		kExtraData_ActivateRef				= 0x52,
		kExtraData_ActivateRefChildren		= 0x53,
		kExtraData_CanTalkToPlayer			= 0x54,
		kExtraData_ObjectHealth				= 0x55,
		kExtraData_CellImageSpace			= 0x56,
		kExtraData_NavMeshPortal			= 0x57,
		kExtraData_ModelSwap				= 0x58,
		kExtraData_Radius					= 0x59,
		//??								= 0x5A,
		kExtraData_FactionChanges			= 0x5B,
		kExtraData_DismemberedLimbs			= 0x5C,
		kExtraData_ActorCause				= 0x5D,
		kExtraData_MultiBound				= 0x5E,
		kExtraData_MultiBoundData			= 0x5F,
		kExtraData_MultiBoundRef			= 0x60,
		kExtraData_ReflectedRefs			= 0x61,
		kExtraData_ReflectorRefs			= 0x62,
		kExtraData_EmittanceSource			= 0x63,
		kExtraData_RadioData				= 0x64,
		kExtraData_CombatStyle				= 0x65,
		//??								= 0x66,
		kExtraData_Primitive				= 0x67,
		kExtraData_OpenCloseActivateRef		= 0x68,
		kExtraData_AnimNoteReceiver			= 0x69,
		kExtraData_Ammo						= 0x6A,
		kExtraData_PatrolRefData			= 0x6B,
		kExtraData_PackageData				= 0x6C,
		kExtraData_OcclusionShape			= 0x6D,
		kExtraData_CollisionData			= 0x6E,
		kExtraData_SayTopicInfoOnceADay		= 0x6F,
		kExtraData_EncounterZone			= 0x70,
		kExtraData_SayTopicInfo				= 0x71,
		kExtraData_OcclusionPlaneRefData	= 0x72,
		kExtraData_PortalRefData			= 0x73,
		kExtraData_Portal					= 0x74,
		kExtraData_Room						= 0x75,
		kExtraData_HealthPerc				= 0x76,
		kExtraData_RoomRefData				= 0x77,
		kExtraData_GuardedRefData			= 0x78,
		kExtraData_CreatureAwakeSound		= 0x79,
		//??								= 0x7A,
		kExtraData_Horse					= 0x7B,
		kExtraData_IgnoredBySandbox			= 0x7C,
		kExtraData_CellAcousticSpace		= 0x7D,
		kExtraData_ReservedMarkers			= 0x7E,
		kExtraData_WeaponIdleSound			= 0x7F,
		kExtraData_WaterLightRefs			= 0x80,
		kExtraData_LitWaterRefs				= 0x81,
		kExtraData_WeaponAttackSound		= 0x82,
		kExtraData_ActivateLoopSound		= 0x83,
		kExtraData_PatrolRefInUseData		= 0x84,
		kExtraData_AshPileRef				= 0x85,
		//??								= 0x86
		kExtraData_FollowerSwimBreadcrumbs	= 0x87,
		kExtraData_AliasInstanceArray		= 0x88,
		kExtraData_Location					= 0x89,
		//??								= 0x8A,
		kExtraData_LocationRefType			= 0x8B,
		kExtraData_PromotedRef				= 0x8C,
		//??								= 0x8D,
		kExtraData_OutfitItem				= 0x8E,
		//??								= 0x8F,
		kExtraData_LeveledItemBase			= 0x90,
		kExtraData_LightData				= 0x91,
		kExtraData_SceneData				= 0x92,
		kExtraData_BadPosition				= 0x93,
		kExtraData_HeadTrackingWeight		= 0x94,
		kExtraData_FromAlias				= 0x95,
		kExtraData_ShouldWear				= 0x96,
		kExtraData_FavorCost				= 0x97,
		kExtraData_AttachedArrows3D			= 0x98,
		kExtraData_TextDisplayData			= 0x99,
		kExtraData_AlphaCutoff				= 0x9A,
		kExtraData_Enchantment				= 0x9B,
		kExtraData_Soul						= 0x9C,
		kExtraData_ForcedTarget				= 0x9D,
		//??								= 0x9E,
		kExtraData_UniqueID					= 0x9F,
		kExtraData_Flags					= 0xA0,
		kExtraData_RefrPath					= 0xA1,
		kExtraData_DecalGroup				= 0xA2,
		kExtraData_LockList					= 0xA3,
		kExtraData_ForcedLandingMarker		= 0xA4,
		kExtraData_LargeRefOwnerCells		= 0xA5,
		kExtraData_CellWaterEnvMap			= 0xA6,
		kExtraData_CellGrassData			= 0xA7,
		kExtraData_TeleportName				= 0xA8,
		kExtraData_Interaction				= 0xA9,
		kExtraData_WaterData				= 0xAA,
		kExtraData_WaterCurrentZoneData		= 0xAB,
		kExtraData_AttachRef				= 0xAC,
		kExtraData_AttachRefChildren		= 0xAD,
		kExtraData_GroupConstraint			= 0xAE,
		kExtraData_ScriptedAnimDependence	= 0xAF,
		kExtraData_CachedScale				= 0xB0,
		kExtraData_RaceData					= 0xB1,
		kExtraData_GIDBuffer				= 0xB2,
		kExtraData_MissingRefIDs			= 0xB3
	};

	BSExtraData*	next;		// 04	
};
assert(sizeof(BSExtraData) == 0x08);

class InventoryChanges : public BSExtraData {
public:
	class EntryData {
	public:
		bool	IsWorn(bool Left) { return ThisCall(0x00484E80, this, Left); }

		TESForm*				type;
		TList<ExtraDataList>*	extendData;
		SInt32					countDelta;
	};

	class Data {
	public:
		TList<EntryData>*	data;
		TESObjectREFR*		owner;
		float				totalWeight;	// of all items in inventory. cached, is -1 if needs to be recalculated
		float				armorWeight;	// weight of equipped armor. cached as above. Both take armor weight perks into account
	};

	Data*	data;			// 08
};
assert(sizeof(InventoryChanges) == 0x0C);

class ExtraDataList {
public:
	class PresenceBitfield {
	public:
		UInt8	bits[0x18];
	};

	BSExtraData*			GetExtraData(BSExtraData::ExtraDataType DataType) { return (BSExtraData*)ThisCall(0x0040A8A0, this, DataType); }
	bool					IsWorn(bool Left) { return (Left ? ThisCall(0x0040A760, this, BSExtraData::ExtraDataType::kExtraData_WornLeft) : ThisCall(0x0040A760, this, BSExtraData::ExtraDataType::kExtraData_Worn)); }
	bool					IsWorn() { return IsWorn(0) || IsWorn(1); }
	InventoryChanges::Data* GetInventoryChangesData() { return (InventoryChanges::Data*)ThisCall(0x0040C090, this); }

	BSExtraData*			m_data;				// 000
	PresenceBitfield*		m_presenceBitfield;	// 004 - if a bit is set, then the extralist should contain that extradata - bits are numbered starting from the lsb
};
assert(sizeof(ExtraDataList) == 0x08);

class MagicTarget {
public:
	virtual ~MagicTarget();
	virtual UInt8					Unk_01(int);
	virtual Character*				Unk_02();
	virtual UInt8					Unk_03();
	virtual bool					Unk_04();
	virtual int						Unk_05(int);
	virtual bool					Unk_06(); // pure   018
	virtual TList<ActiveEffect>*	GetActiveEffects(); // pure     01C
	virtual int						Unk_08(int);
	virtual void					Unk_09(int);
	virtual double					Unk_0A(int, int, int);
	virtual UInt8					Unk_0B(int, int, int);

	UInt32	unk04;		// 04
	UInt32	unk08;		// 08
};
assert(sizeof(MagicTarget) == 0xC);

class BaseFormComponent {
public:
	virtual ~BaseFormComponent();
	virtual void	Init();
	virtual void	ReleaseRefs();
	virtual void	CopyFromBase(BaseFormComponent* rhs);
};
assert(sizeof(BaseFormComponent) == 0x04);

class TESDescription : public BaseFormComponent {
public:
	UInt32	unk04;	// 04
	UInt32	unk08;	// 08 - init'd to FFFFFFFF
};
assert(sizeof(TESDescription) == 0x0C);

class TESModel : public BaseFormComponent {
public:
	virtual const char* GetModelName();
	virtual void		SetModelName(const char* name);
	virtual UInt32		Unk_06();

	BSFixedString	name;	// 04
	UInt32			unk08;	// 08
	UInt32			unk0C;	// 0C
	UInt16			unk10;	// 10
	UInt8			unk12;	// 12
	UInt8			unk13;	// 13
};
assert(sizeof(TESModel) == 0x14);

class TESTexture : public BaseFormComponent {
public:
	BSFixedString	ddsPath;		// 04
};
assert(sizeof(TESTexture) == 0x08);

class TESIcon : public TESTexture {};
assert(sizeof(TESIcon) == 0x08);

class TESFullName : public BaseFormComponent {
public:
	virtual UInt32		Unk_04(void);
	virtual const char* GetName(void);

	BSFixedString	name;	// 04
};
assert(sizeof(TESFullName) == 0x08);

class TESEnchantableForm : public BaseFormComponent {
public:
	virtual UInt16	Unk_04();		// return unk08

	EnchantmentItem*	enchantment;	// 04 - init'd to 0
	UInt16				unk08;			// 08 - init'd to 3
	UInt16				maxCharge;
};
assert(sizeof(TESEnchantableForm) == 0x0C);

class TESValueForm : public BaseFormComponent {
public:
	UInt32	value;
};
assert(sizeof(TESValueForm) == 0x008);

class TESWeightForm : public BaseFormComponent {
public:
	float	weight;
};
assert(sizeof(TESWeightForm) == 0x008);

class TESAttackDamageForm : public BaseFormComponent {
public:
	virtual UInt16	GetAttackDamage();

	UInt16	attackDamage;	// 04
	UInt8	pad06[2];		// 06
};
assert(sizeof(TESAttackDamageForm) == 0x8);

class BGSDestructibleObjectForm : public BaseFormComponent {
public:
	class Data {
	public:
		UInt32	unk00;		// 00
		UInt8	unk04;		// 04
		UInt8	unk05;		// 05
		UInt8	pad06[2];	// 06
		UInt32	unk08;		// 08
		UInt32	unk0C;		// 0C
		UInt32	unk10;		// 10 - object
	};

	Data*	data;	// 04
};
assert(sizeof(BGSDestructibleObjectForm) == 0x8);

class BGSEquipType : public BaseFormComponent {
public:
	virtual	BGSEquipSlot*	GetEquipSlot();
	virtual void			SetEquipSlot(BGSEquipSlot* type);

	BGSEquipType*	unk04;	// 04
};
assert(sizeof(BGSEquipType) == 0x8);

class BGSPreloadable : public BaseFormComponent {
public:
	virtual void	Unk_04();	// pure virtual
};
assert(sizeof(BGSPreloadable) == 0x4);

class BGSMessageIcon : public BaseFormComponent {
public:
	TESIcon		icon;	// 04
};
assert(sizeof(BGSMessageIcon) == 0xC);

class BGSPickupPutdownSounds : public BaseFormComponent {
public:
	BGSSoundDescriptorForm*		pickUp;		// 04
	BGSSoundDescriptorForm*		putDown;	// 08
};
assert(sizeof(BGSPickupPutdownSounds) == 0xC);

class BGSBlockBashData : public BaseFormComponent {
public:
	UInt32	unk04;	// 04
	UInt32	unk08;	// 08
};
assert(sizeof(BGSBlockBashData) == 0xC);

class BGSKeywordForm : public BaseFormComponent {
public:
	virtual bool	HasKeyword(BGSKeyword* keyword);
	virtual UInt32	GetDefaultKeyword();

	BGSKeyword**	keywords;		// 04
	UInt32			numKeywords;	// 08
};
assert(sizeof(BGSKeywordForm) == 0xC);

class TESModelTextureSwap : public TESModel {
public:
	class SwapInfo {
	public:
		BGSTextureSet*	textureSet;	// 00
		UInt32			unk04;		// 04 - index?
		BSFixedString	name;		// 08
	};

	SwapInfo*		swaps;	// 14
	UInt32			count;		// 18
};
assert(sizeof(TESModelTextureSwap) == 0x1C);

class TESForm : public BaseFormComponent {
public:
	enum FormType {
		kFormType_None = 0,			//	NONE
		kFormType_TES4,				//	TES4
		kFormType_Group,			//	GRUP	
		kFormType_GMST,				//	GMST
		kFormType_Keyword,			//	KYWD	BGSKeyword
		kFormType_LocationRef,		//	LCRT	BGSLocationRefType
		kFormType_Action,			//	AACT	BGSAction
		kFormType_TextureSet,		//	TXST	BGSTextureSet
		kFormType_MenuIcon,			//	MICN	BGSMenuIcon
		kFormType_Global,			//	GLOB	TESGlobal
		kFormType_Class,			//	CLAS	TESClass
		kFormType_Faction,			//	FACT	TESFaction
		kFormType_HeadPart,			//	HDPT	BGSHeadPart
		kFormType_Eyes,				//	EYES	TESEyes
		kFormType_Race,				//	RACE	TESRace
		kFormType_Sound,			//	SOUN	TESSound
		kFormType_AcousticSpace,	//	ASPC	BGSAcousticSpace
		kFormType_Skill,			//	SKIL	<missing>
		kFormType_EffectSetting,	//	MGEF	EffectSetting
		kFormType_Script,			//	SCPT	Script
		kFormType_LandTexture,		//	LTEX	TESLandTexture
		kFormType_Enchantment,		//	ENCH	EnchantmentItem
		kFormType_Spell,			//	SPEL	SpellItem
		kFormType_ScrollItem,		//	SCRL	ScrollItem
		kFormType_Activator,		//	ACTI	TESObjectACTI
		kFormType_TalkingActivator,	//	TACT	BGSTalkingActivator
		kFormType_Armor,			//	ARMO	TESObjectARMO
		kFormType_Book,				//	BOOK	TESObjectBOOK
		kFormType_Container,		//	CONT	TESObjectCONT
		kFormType_Door,				//	DOOR	TESObjectDOOR
		kFormType_Ingredient,		//	INGR	IngredientItem
		kFormType_Light,			//	LIGH	TESObjectLIGH
		kFormType_Misc,				//	TESObjectMISC
		kFormType_Apparatus,		//	APPA	BGSApparatus
		kFormType_Static,			//	STAT	TESObjectSTAT
		kFormType_StaticCollection,	//	BGSStaticCollection
		kFormType_MovableStatic,	//	MSTT	BGSMovableStatic
		kFormType_Grass,			//	GRAS	TESGrass
		kFormType_Tree,				//	TREE	TESObjectTREE
		kFormType_Flora,			//	FLOR	TESFlora
		kFormType_Furniture,		//	FURN	TESFurniture
		kFormType_Weapon,			//	WEAP	TESObjectWEAP
		kFormType_Ammo,				//	AMMO	TESAmmo
		kFormType_NPC,				//	NPC_	TESNPC
		kFormType_LeveledCharacter,	//	LVLN	TESLevCharacter
		kFormType_Key,				//	KEYM	TESKey
		kFormType_Potion,			//	ALCH	AlchemyItem
		kFormType_IdleMarker,		//	IDLM	BGSIdleMarker / BGSDefaultObjectManager? strange
		kFormType_Note,				//	NOTE	BGSNote
		kFormType_ConstructibleObject,	//	COBJ	BGSConstructibleObject
		kFormType_Projectile,		//	PROJ	BGSProjectile
		kFormType_Hazard,			//	HAZD	BGSHazard
		kFormType_SoulGem,			//	SLGM	TESSoulGem
		kFormType_LeveledItem,		//	LVLI	TESLevItem
		kFormType_Weather,			//	WTHR	TESWeather
		kFormType_Climate,			//	CLMT	TESClimate
		kFormType_SPGD,				//	SPGD	BGSShaderParticleGeometryData
		kFormType_ReferenceEffect,	//	RFCT	BGSReferenceEffect
		kFormType_Region,			//	REGN	TESRegion
		kFormType_NAVI,				//	NAVI	NavMeshInfoMap
		kFormType_Cell,				//	CELL	TESObjectCELL
		kFormType_REFR,				//	REFR	TESObjectREFR / Actor
		kFormType_Character,		//	ACHR	Character / PlayerCharacter
		kFormType_Missile,			//	PMIS	MissileProjectile
		kFormType_Arrow,			//	PARW	ArrowProjectile
		kFormType_Grenade,			//	PGRE	GrenadeProjectile
		kFormType_BeamProj,			//	PBEA	BeamProjectile
		kFormType_FlameProj,		//	PFLA	FlameProjectile
		kFormType_ConeProj,			//	PCON	ConeProjectile
		kFormType_BarrierProj,		//	PBAR	BarrierProjectile
		kFormType_PHZD,				//	PHZD	Hazard
		kFormType_WorldSpace,		//	WRLD	TESWorldSpace
		kFormType_Land,				//	LAND	TESObjectLAND
		kFormType_NAVM,				//	NAVM	NavMesh
		kFormType_TLOD,				//	TLOD	?
		kFormType_Topic,			//	DIAL	TESTopic
		kFormType_TopicInfo,		//	INFO	TESTopicInfo
		kFormType_Quest,			//	QUST	TESQuest
		kFormType_Idle,				//	IDLE	TESIdleForm
		kFormType_Package,			//	PACK	TESPackage
		kFormType_CombatStyle,		//	CSTY	TESCombatStyle
		kFormType_LoadScreen,		//	LSCR	TESLoadScreen
		kFormType_LeveledSpell,		//	LVSP	TESLevSpell
		kFormType_ANIO,				//	ANIO	TESObjectANIO
		kFormType_Water,			//	WATR	TESWaterForm
		kFormType_EffectShader,		//	EFSH	TESEffectShader
		kFormType_TOFT,				//	TOFT	?
		kFormType_Explosion,		//	EXPL	BGSExplosion
		kFormType_Debris,			//	DEBR	BGSDebris
		kFormType_ImageSpace,		//	IMGS	TESImageSpace
		kFormType_ImageSpaceMod,	//	IMAD	TESImageSpaceModifier
		kFormType_List,				//	FLST	BGSListForm
		kFormType_Perk,				//	PERK	BGSPerk
		kFormType_BodyPartData,		//	BPTD	BGSBodyPartData
		kFormType_AddonNode,		//	ADDN	BGSAddonNode
		kFormType_ActorValueInfo,	//	AVIF	ActorValueInfo
		kFormType_CameraShot,		//	CAMS	BGSCameraShot
		kFormType_CameraPath,		//	CPTH	BGSCameraPath
		kFormType_VoiceType,		//	VTYP	BGSVoiceType
		kFormType_MaterialType,		//	MATT	BGSMaterialType
		kFormType_ImpactData,		//	IPCT	BGSImpactData
		kFormType_ImpactDataSet,	//	IPDS	BGSImpactDataSet
		kFormType_ARMA,				//	ARMA	TESObjectARMA
		kFormType_EncounterZone,	//	ECZN	BGSEncounterZone
		kFormType_Location,			//	LCTN	BGSLocation
		kFormType_Message,			//	MESH	BGSMessage
		kFormType_Ragdoll,			//	RGDL	BGSRagdoll
		kFormType_DOBJ,				//	DOBJ	? (used for default objects, custom loader)
		kFormType_LightingTemplate,	//	LGTM	BGSLightingTemplate
		kFormType_MusicType,		//	MUSC	BGSMusicType
		kFormType_Footstep,			//	FSTP	BGSFootstep
		kFormType_FootstepSet,		//	FSTS	BGSFootstepSet
		kFormType_StoryBranchNode,	//	SMBN	BGSStoryManagerBranchNode
		kFormType_StoryQuestNode,	//	SMQN	BGSStoryManagerQuestNode
		kFormType_StoryEventNode,	//	SMEN	BGSStoryManagerEventNode
		kFormType_DialogueBranch,	//	DLBR	BGSDialogueBranch
		kFormType_MusicTrack,		//	MUST	BGSMusicTrackFormWrapper
		kFormType_DLVW,				//	DLVW	?
		kFormType_WordOfPower,		//	WOOP	TESWordOfPower
		kFormType_Shout,			//	SHOU	TESShout
		kFormType_EquipSlot,		//	EQUP	BGSEquipSlot
		kFormType_Relationship,		//	RELA	BGSRelationship
		kFormType_Scene,			//	SCEN	BGSScene
		kFormType_AssociationType,	//	ASTP	BGSAssociationType
		kFormType_Outfit,			//	OTFT	BGSOutfit
		kFormType_Art,				//	ARTO	BGSArtObject
		kFormType_Material,			//	MATO	BGSMaterialObject
		kFormType_MovementType,		//	MOVT	BGSMovementType
		kFormType_SoundDescriptor,	//	SNDR	BGSSoundDescriptorForm
		kFormType_DualCastData,		//	DUAL	BGSDualCastData
		kFormType_SoundCategory,	//	SNCT	BGSSoundCategory
		kFormType_SoundOutput,		//	SOPM	BGSSoundOutput
		kFormType_CollisionLayer,	//	COLL	BGSCollisionLayer
		kFormType_ColorForm,		//	CLFM	BGSColorForm
		kFormType_ReverbParam,		//	REVB	BGSReverbParameters

		kFormType_Unk87,
		kFormType_Alias,			//			BGSBaseAlias
		kFormType_ReferenceAlias,	//			BGSRefAlias
		kFormType_LocationAlias,	//			BGSLocAlias
		kFormType_ActiveMagicEffect,//			ActiveMagicEffect
	};

	enum {
		kFlagIsDeleted		= 0x20,
		kFlagPlayerKnows	= 0x40,
		kFlagUnk_0x800		= 0x800
	};

	virtual void			Unk_04();		// reset/init? would leak pointers if called on a live object
	virtual void			Unk_05();		// release pointers?
	virtual bool			LoadForm(UInt32 arg);
	virtual bool			Unk_07(UInt32 arg);
	virtual bool			Unk_08(UInt32 arg);	// calls LoadForm
	virtual TESForm*		Unk_09(UInt32 arg1, void * arg2);
	virtual bool			MarkChanged(UInt32 changed);	// mark as changed?
	virtual void			Unk_0B(UInt32 arg);
	virtual bool			Unk_0C(UInt32 arg);
	virtual void			Unk_0D(UInt32 arg);
	virtual void			Unk_0E(UInt32 arg);
	virtual void			Unk_0F(void * arg);
	virtual void			Unk_10(UInt32 arg);
	virtual void			Unk_11(UInt32 arg);
	virtual void			Unk_12(UInt32 arg);
	virtual void			InitItem();		// called once all dependent forms are loaded
	virtual void			Unk_14();
	virtual UInt32			GetFormType();
	virtual void			GetFormDesc(char * buf, UInt32 bufLen);
	virtual bool			GetFlag00000040();
	virtual bool			GetFlag00010000();
	virtual bool			IsPlayable();
	virtual bool			GetFlag00080000();
	virtual bool			GetFlag02000000();
	virtual bool			Unk_1B();
	virtual bool			GetFlag00000200();
	virtual bool			GetFlag00000100();
	virtual void			SetFlag00000200(bool set);
	virtual bool			Unk_20();
	virtual void			SetFlag00000020(bool set);
	virtual void			SetFlag00000002(bool set);
	virtual void			Unk_23();
	virtual void			Unk_24(UInt32 arg);
	virtual bool			Unk_25();
	virtual bool			Unk_26();
	virtual bool			Has3D();
	virtual bool			Unk_28();
	virtual UInt32			Unk_29();
	virtual UInt32			Unk_2A();
	virtual UInt32			Unk_2B();
	virtual const char*		GetFullName();
	virtual void			CopyFrom(TESForm * srcForm);
	virtual bool			Compare(TESForm * rhs);
	virtual void			Unk_2F(void * dst, UInt32 unk);
	virtual void			Unk_30();
	virtual void			Unk_31();
	virtual const char*		GetEditorName();
	virtual bool			SetEditorName(const char * str);
	virtual bool			Unk_34(UInt32 arg);
	virtual bool			Unk_35(UInt32 arg0, UInt32 arg1, UInt32 arg2, UInt32 arg3, UInt32 arg4);
	virtual void			SetID(UInt32 ID, UInt32 generateID);
	virtual const char*		Unk_37();
	virtual bool			Unk_38();

	void					GenerateID(UInt32 ID) { SetID(ID, 1); }

	void*	unk04;		// 04
	UInt32	flags;		// 08
	UInt32	formID;		// 0C
	UInt16	unk10;		// 10
	UInt8	formType;	// 12
	UInt8	pad13;		// 13
};
assert(sizeof(TESForm) == 0x14);

class TESPackage : public TESForm {
public:
	virtual bool	Unk_39(UInt32 arg0, UInt32 arg1, UInt32 arg2, UInt32 arg3);
	virtual bool	Unk_3A(UInt32 arg0, UInt32 arg1, UInt32 arg2, UInt32 arg3, UInt32 arg4);
	virtual bool	Unk_3B(UInt32 arg0, UInt32 arg1);
	virtual bool	Unk_3C(UInt32 arg0, UInt32 arg1);
	virtual bool	Unk_3D(UInt32 arg0);

	enum {
		kPackageType_Find = 0,
		kPackageType_Follow,
		kPackageType_Escort,
		kPackageType_Eat,
		kPackageType_Sleep,
		kPackageType_Wander,
		kPackageType_Travel,
		kPackageType_Accompany,
		kPackageType_UseItemAt,
		kPackageType_Ambush,
		kPackageType_FleeNotCombat,
		kPackageType_CastMagic,
		kPackageType_Sandbox,
		kPackageType_Patrol,
		kPackageType_Guard,
		kPackageType_Dialogue,
		kPackageType_UseWeapon,
		kPackageType_Find2,
		kPackageType_Package,
		kPackageType_PackageTemplate,
		kPackageType_Activate,
		kPackageType_Alarm,
		kPackageType_Flee,
		kPackageType_Trespass,
		kPackageType_Spectator,
		kPackageType_ReactToDead,
		kPackageType_GetUpFromChair,
		kPackageType_DoNothing,
		kPackageType_InGameDialogue,
		kPackageType_Surface,
		kPackageType_SearchForAttacker,
		kPackageType_AvoidPlayer,
		kPackageType_ReactToDestroyedObject,
		kPackageType_ReactToGrenadeOrMine,
		kPackageType_StealWarning,
		kPackageType_PickPocketWarning,
		kPackageType_MovementBlocked,
		kPackageType_Unk37,
		kPackageType_Unk38
	};

	// C
	struct Data30 {
		UInt8	unk00;		// 0
		UInt8	unk01;		// 1
		UInt8	unk02;		// 2
		UInt8	unk03;		// 3
		UInt8	unk04;		// 4
		UInt8	pad05[3];	// 5
		UInt32	unk08;		// 8
	};

	// 10
	struct Data {
		UInt32	unk00;	// 00
		UInt32	unk04;	// 04
		UInt32	unk08;	// 08
		UInt32	unk0C;	// 0C
	};

	UInt32	packageFlags;	// 14
	UInt8	type;			// 18 - see kPackageType_ enum
	UInt8	unk19;			// 19
	UInt8	unk1A;			// 1A
	UInt8	pad1B;			// 1B
	UInt16	unk1C;			// 1C
	UInt16	unk1E;			// 1E
	UInt32	unk20;			// 20
	void*	packageLocation;	// 24 PackageLocation*
	UInt32	unk28;			// 28
	UInt32	unk2C;			// 2C
	Data30	unk30;			// 30
	void*	unk3C;		// 3C - linked list
	UInt32	unk40;			// 40
	UInt32	unk44;			// 44
	Data	unk48;			// 48
	Data	unk58;			// 58
	Data	unk68;			// 68
	UInt32	unk78;			// 78
	UInt32	unk7C;			// 7C - incremented in dtor
};
assert(sizeof(TESPackage) == 0x80);

class TESWeather : public TESForm {
public:
	enum { kNumColorTypes = 17 };
	enum { kNumTimeOfDay = 4 };

	enum ColorTypes {
		eColor_SkyUpper = 0,
		eColor_Fog = 1,
		eColor_Unk = 2,
		eColor_Ambient = 3,
		eColor_Sunlight = 4,
		eColor_Sun = 5,
		eColor_Stars = 6,
		eColor_SkyLower = 7,
		eColor_Horizon = 8,
		eColor_Lighting = 9,
		eColor_CloudsLower = 10, // LODDiffuse
		eColor_CloudsUpper = 11, // LODAmbient 
		eColor_FogFar = 12,
		eColor_SkyStatics = 13,
		eColor_WaterMultiplier = 14,
		eColor_SunGlare = 15,
		eColor_MoonGlare = 16,
	};

	enum TimeOfDay {
		eTime_Sunrise = 0,
		eTime_Day = 1,
		eTime_Sunset = 2,
		eTime_Night = 3,
	};

	struct ColorData {
		RGBA colors[kNumTimeOfDay];
	};

	enum WeatherType {
		kType_None = 0,
		kType_Pleasant = 1,
		kType_Cloudy = 2,
		kType_Rainy = 4,
		kType_Snow = 8,
	};

	struct General {
		UInt8	windSpeed;
		UInt8	cloudSpeedLower;
		UInt8	cloudSpeedUpper;
		UInt8	transDelta;				// Div 1000
		UInt8	sunGlare;				// Div 256
		UInt8	sunDamage;				// Div 256
		UInt8	unk06;
		UInt8	unk07;
		UInt8	unk08;
		UInt8	unk09;
		UInt8	unk0A;
		UInt8	weatherType;
		UInt8	unk0C;
		UInt8	unk0D;
		UInt8	unk0E;
		UInt8	unk0F;
		UInt8	unk10;
		UInt8	windDirection;			// Div (256/360)
		UInt8	windDirRange;			// Div (256/180)
		UInt8	unk13;
	};

	struct FogDistance {
		float	nearDay;
		float	farDay;				// 10
		float	nearNight;			// 14
		float	farNight;			// 18
		float	powerDay;			// 1C
		float	powerNight;
		float	maxDay;
		float	maxNight;
	};

	struct CloudAlpha {
		float	time[kNumTimeOfDay];
	};
	
	struct LightingColor {
		UInt32	x[2];				// 00 - init'd to 00FFFFFF
		UInt32	y[2];
		UInt32	z[2];
		UInt32	specular;			// 18 - init'd to 0
		float	fresnelPower;		// 1C - init'd to 1
	};

	float			GetFogDayNear() { return fogDistance.nearDay; }
	float			GetFogDayFar() { return fogDistance.farDay; }
	float			GetFogNightNear() { return fogDistance.nearNight; }
	float			GetFogNightFar() { return fogDistance.farNight; }

	TESTexture		texture[0x20];					// 014 TESTexture1024
	UInt8			unk114[0x20];					// 114 - cleared to 0x7F
	UInt8			unk134[0x20];					// 134 - cleared to 0x7F
	UInt8			unk154[0x200];					// 154
	CloudAlpha		cloudAlpha[0x20];				// 354
	UInt32			unk554;							// 554
	General			general;						// 558
	FogDistance		fogDistance;					// 56C
	ColorData		colors[kNumColorTypes];			// 58C
	TList<UInt32>	unk69C;							// 69C TESAIForm::Data
	TArray<UInt32>	unk6A4;							// 6A4
	UInt32			pad6B0;							// 6B0 - not init'd
	TESImageSpace*	imageSpaces[kNumTimeOfDay];
	LightingColor	directionalAmbient[kNumTimeOfDay];	// 6C4
	TESModel		unk744;							// 744
	void*			particleShader;					// 758 BGSShaderParticleGeometryData*
	void*			referenceEffect;				// 75C BGSReferenceEffect*
};
assert(sizeof(TESWeather) == 0x760);

class TESWeatherEx : public TESWeather {
public:
	ColorData	colorsb[kNumColorTypes];
	char		EditorName[40];
};
assert(sizeof(TESWeatherEx) == 0x898);

class TESIdleForm : public TESForm {
public:
	enum AnimFlag { // From NV, to refactor
		kAnimFlag_groupIdle				= 0,
		kAnimFlag_groupMovement			= 1,
		kAnimFlag_groupLeftArm			= 2,
		kAnimFlag_groupLeftHand			= 3,
		kAnimFlag_groupLeftWeapon		= 4,
		kAnimFlag_groupLeftWeaponUp		= 5,
		kAnimFlag_groupLeftWeaponDown	= 6,
		kAnimFlag_SpecialIdle			= 7,
		kAnimFlag_groupWholeBody		= 20,
		kAnimFlag_groupUpperBody		= 20,
		kAnimFlag_flagUnknown			= 64,
		kAnimFlag_flagOptionallyReturnsAFile = 128,
	};

	void				SetFile(const char* Name) { fileName.Set(Name); }

	void*				unk14;			// 14 - linked list
	UInt8				loopMin;		// 18
	UInt8				loopMax;		// 19
	UInt8				animFlags;		// 1A
	UInt8				group;			// 1B
	UInt16				unk1C;			// 1C
	UInt8				pad1E[2];		// 1E
	UInt32				unk20;			// 20 - NiFormArray
	TESIdleForm*		relatedIdle1;	// 24
	TESIdleForm*		relatedIdle2;	// 28
	BSFixedString		fileName;		// 2C
	BSFixedString		animationEvent;	// 30
	BSString			editorId;		// 34
};
assert(sizeof(TESIdleForm) == 0x3C);

class TESClimate : public TESForm {
public:
	struct Data28 {
		UInt32	unk0;
		UInt32	unk4;
	};

	TESModel	nightSky;		// 14
	Data28		unk28;			// 28
	TESTexture	sun;			// 30
	TESTexture	sunGlare;		// 38
	UInt8		sunriseBegin;	// 40
	UInt8		sunriseEnd;		// 41
	UInt8		sunsetBegin;	// 42
	UInt8		sunsetEnd;		// 43
	UInt8		volatility;		// 44
	UInt8		moonInfo;		// 45
	UInt8		pad46[2];		// 46
};
assert(sizeof(TESClimate) == 0x48);

class TESWaterForm : public TESForm {
public:
	struct Data2C {
		UInt32	unk0;	// 0
		UInt32	unk4;	// 4
		UInt32	unk8;	// 8
		UInt32	unkC;	// C
	};

	struct Properties {
		float	unk00;		// 00 - init'd to .1
		float	unk04;		// 04 - init'd to 90
		float	unk08;		// 08 - init'd to .5
		float	unk0C;		// 0C - init'd to 1
		float	sunSpecularPower;
		float	reflectivityAmount;
		float	fresnelAmount;
		float	unk1C;		// 1C - init'd to 0
		float	fogNearAW;	// Above water fog near place distance
		float	fogFarAW;	// Above water fog far plane distance
		RGBA	shallowColor;
		RGBA	deepColor;
		RGBA	reflectionColor;
		UInt8	unk34;		// 34 - init'd to 0
		UInt8	pad35[3];	// 35
		float	unk38;		// 38 - init'd to 0.1
		float	unk3C;		// 3C - init'd to 0.6
		float	unk40;		// 40 - init'd to 0.985
		float	unk44;		// 44 - init'd to 2
		float	displacementStartingSize;
		float	displacementForce;
		float	displacementVelocity;
		float	displacementFalloff;
		float	displacementDampner;
		float	unk5C;		// 5C - init'd to .05
		float	noiseFalloff;
		float	noiseWindDirectionL1;
		float	noiseWindDirectionL2;
		float	noiseWindDirectionL3;
		float	noiseWindSpeedL1;
		float	noiseWindSpeedL2;
		float	noiseWindSpeedL3;
		float	unk7C;		// 7C - init'd to 300
		float	unk80;		// 80 - init'd to 300
		float	fogAmountAW; // Above water fog amount
		float	unk88;		// 88 - not init'd
		float	fogAmountUW; // Underwater water fog amount
		float	fogNearUW;	// Underwater fog near place distance
		float	fogFarUW;	// Underwater fog far plane distance
		float	refractionMagnitude;
		float	specularPower;
		float	unkA0;		// A0 - init'd to 1
		float	specularRadius;
		float	specularbrightness;
		float	noiseUVScaleL1;
		float	noiseUVScaleL2;
		float	noiseUVScaleL3;
		float	noiseAmplitudeScaleL1;
		float	noiseAmplitudeScaleL2;
		float	noiseAmplitudeScaleL3;
		float	reflectionMagnitude;
		float	sunSparkleMagnitude;
		float	sunSpecularMagnitude;
		float	depthReflections;
		float	depthRefractions;
		float	depthNormals;
		float	depthSpecularLight;
		float	sunSparklePower;
	};

	struct Data1C8 {
		UInt32	unk0;	// 0
		UInt32	unk4;	// 4
		UInt32	unk8;	// 8
	};

	void				RemoveUnderwaterFog() { properties.fogAmountUW = 0.0f; properties.fogNearUW = 9995.0f; properties.fogFarUW = 10000.0f; }
	RGBA*				GetShallowColor() { return &properties.shallowColor; }
	RGBA*				GetDeepColor() { return &properties.deepColor; }
	RGBA*				GetReflectionColor() { return &properties.reflectionColor; }

	TESFullName			fullName;		// 014
	TESAttackDamageForm	attackDamage;	// 01C
	UInt8				unk024;		// 024
	UInt8				pad025[3];	// 025
	UInt32				unk028;		// 028
	Data2C				unk02C;		// 02C
	Data2C				unk03C;		// 03C
	Data2C				unk04C;		// 04C
	TESTexture			unk05C;		// 05C
	TESTexture			unk064;		// 064
	TESTexture			unk06C;		// 06C
	UInt8				Density;	// 074
	UInt8				unk075;		// 075
	UInt8				pad076[2];	// 076
	UInt32				unk078;		// 078
	void*				SoundDescriptor; // 07C BGSSoundDescriptorForm*
	Properties			properties;	// 080
	UInt32				unk164[3];	// 164
	UInt32				unk170;		// 170
	UInt32				unk174;		// 174
	UInt32				unk178;		// 178
	UInt32				unk17C;		// 17C
	UInt32				unk180;		// 180
	float				unk184;		// 184
	float				unk188;		// 188
	float				unk18C;		// 18C
	float				unk190;		// 190
	UInt32				unk194;		// 194
	UInt32				unk198;		// 198
	UInt32				unk19C;		// 19C
	UInt32				unk1A0;		// 1A0
	TESObjectACTI*		Activator;	// 1A4
	UInt32				unk1A8;		// 1A8
	void*				unk1AC;	// 1AC - refcounted ptr
	UInt32				unk1B0;		// 1B0
	UInt8				unk1B4;		// 1B4
	UInt8				pad1B5[3];	// 1B5
	UInt32				unk1B8;		// 1B8
	Data1C8				unk1BC;		// 1BC
	Data1C8				unk1C8;		// 1C8
};
assert(sizeof(TESWaterForm) == 0x1D4);

class TESWorldSpace : public TESForm {
public:
	struct GeneralInfo {
		struct Entry {
			UInt8	pad00[8];	// 00 12C
			UInt32	unk08;		// 08 134
			UInt32	unk0C;		// 0C 138
			UInt32	unk10;		// 10 13C
			void*	unk14;		// 14 140
			char*	Name;		// 18 144
			UInt32	unk1C;		// 1C 148
		};
		Entry	unk00;
		Entry	unk20;
	};

	TESFullName				fullName;	// 14
	TESTexture				texture;	// 1C
	NiTMap <UInt32, TESObjectCELL*>* cellMap;	// 024
	UInt32					unk028;		// 028
	UInt32					unk02C;		// 02C
	UInt32					unk030;		// 030
	UInt8					worldSpaceFlags;	// 034
	UInt8					pad035;		// 035
	UInt16					unk036;		// 036
	UInt16					unk038;		// 038
	UInt16					unk03A;		// 03A
	UInt8					unk03C[0x20];	// 03C
	TArray<UInt32>			unk05C;		// 05C
	UInt32					unk068;		// 068
	UInt32					unk06C;		// 06C
	UInt8					unk070[0x20];		// 070
	void*					unk090;		// 090 - refcounted ptr
	TESObjectCELL*			cell;		// 094
	UInt32					unk098;		// 098
	UInt32					unk09C;		// 09C
	UInt32					unk0A0;		// 0A0
	UInt32					unk0A4;		// 0A4
	UInt32					unk0A8;		// 0A8
	UInt32					unk0AC;		// 0AC
	UInt32					unk0B0;		// 0B0
	UInt32					unk0B4;		// 0B4
	UInt32					unk0B8;		// 0B8
	UInt8					unk0BC[0x10];	// 0BC
	float					unk0CC;		// 0CC
	UInt32					unk0D0;		// 0D0
	UInt32					unk0D4;		// 0D4
	UInt32					unk0D8;		// 0D8
	UInt32					unk0DC;		// 0DC
	UInt32					unk0E0;		// 0E0
	UInt32					unk0E4;		// 0E4
	UInt32					unk0E8;		// 0E8
	UInt32					unk0EC;		// 0EC
	NiTMap <void*, void*>	unk0F0;	// 0F0 NiTMap <TESFile*, TESWorldSpace::OFFSET_DATA*>
	BSString				unk100;		// 100
	void*					unk108;		// 108
	UInt32					unk10C;		// 10C
	float					unk110;		// 110
	UInt32					unk114;		// 114
	UInt32					unk118;		// 118
	TESTexture				unk11C;		// 11C
	TESTexture				unk124;		// 124
	GeneralInfo				generalInfo; // 12C
	UInt32					unk16C;		// 16C
	UInt32					unk170;		// 170
};
assert(sizeof(TESWorldSpace) == 0x174);

class TESGlobal : public TESForm {
public:
	BSString	name;	// 14
	UInt8		type;	// 1C
	UInt8		pad[3];	// 1D
	float		data;	// 20
};
assert(sizeof(TESGlobal) == 0x24);

class TESRegion : public TESForm {
public:
	void*			dataEntries;	// 14 RegionDataEntryList*
	void*			areaEntries;	// 18 RegionAreaEntryList*
	TESWorldSpace*	worldSpace;		// 1C
	TESWeather*		weather;		// 20
	UInt32			unk24[3];		// 24
};
assert(sizeof(TESRegion) == 0x30);

class TESRegionEx : public TESRegion {
public:
	char		EditorName[40];
};
assert(sizeof(TESRegionEx) == 0x058);

class BGSStoryManagerTreeForm : public TESForm {
public:
	virtual UInt32	Unk_39();
	virtual UInt32	Unk_3A(UInt32 arg);
	virtual void*	Unk_3B();
	virtual void	Unk_3C();

	UInt32		unk14;	// 14
};

class TESQuest : public BGSStoryManagerTreeForm {
public:
	struct Data03C {
		UInt8	data[0x20];
	};

	struct Data05C {
		UInt8	data[0x20];
	};

	struct Data07C {
		UInt32	unk0;
		UInt16	flags;
		UInt8	priority;
		UInt8	type;
	};

	struct Objective {
		BSString	displayText;
		TESQuest*	owner;
		UInt32		unk08;
		UInt32		unk0C;
		UInt16		index;
		UInt16		unk12;
		UInt32		unk14;
	};

	struct Data088 {
		UInt32	unk0;
		UInt32	unk4;
	};

	struct Data0A0 {
		UInt8	data[0x1C];	// ### todo
	};

	TESFullName			fullName;	// 18
	TArray<UInt32>		unk020;		// 020
	UInt32				unk02C;		// 02C
	TArray<void*>		aliases;	// 030 TArray<BGSBaseAlias*>
	Data03C				unk03C;		// 03C
	Data05C				unk05C;		// 05C
	Data07C				unk07C;		// 07C
	UInt32				unk084;		// 084
	Data088				unk088;		// 088
	TList<Objective>	objectives;
	void*				unk098;		// 098 - linked list
	void*				unk09C;		// 09C - linked list
	Data0A0				unk0A0;		// 0A0
	void*				unk0BC;
	Data0A0				unk0C0;
	UInt32				unk0DC;
	TArray<UInt32>		unk0E0[6];	// 0E0
	TArray<UInt32>		unk128;		// 128
	void*				unk134;		// 134 - linked list
	UInt16				unk138;		// 138
	UInt8				unk13A;		// 13A
	UInt8				pad13B;		// 13B
	BSString			questID;	// 13C
	UInt32				unk144;		// 144
	UInt32				unk148;		// 148
	TArray<UInt32>		unk14C;		// 14C
};
assert(sizeof(TESQuest) == 0x158);

class TESObject : public TESForm {
public:
	virtual UInt32	Unk_39();
	virtual bool	Unk_3A();
	virtual UInt32	Unk_3B();
	virtual bool	Unk_3C();
	virtual void	Unk_3D(UInt32 arg);
	virtual UInt32	Unk_3E(UInt32 arg0, UInt32 arg1);
	virtual void	Unk_3F(void* arg);
	virtual bool	Unk_40();
	virtual bool	Unk_41();
	virtual void	Unk_42();
	virtual void	Unk_43(UInt32 arg0, UInt32 arg1);
	virtual UInt32	Unk_44();
	virtual UInt32	Unk_45();
	virtual void*	Unk_46();
};
assert(sizeof(TESObject) == 0x14);

class ActorValueInfo : public TESForm {
public:
	enum {
		kSkillUseMult = 0,
		kSkillOffsetMult,
		kSkillImproveMult,
		kSkillImproveOffset
	};

	TESFullName				fullName;		// 14
	TESDescription			description;	// 1C
	TESIcon					icon;			// 28
	const char*				name;			// 30 - second ctor argument
	BSFixedString			unk34;			// 34
	UInt32					unk38;			// 38
	UInt32					unk3C;			// 3C
	UInt32					unk40;			// 40
	UInt32					unk44;			// 44
	UInt32					unk48[0x0F];	// 48 - init'd to 0xA4
	UInt32					numSubTypes;	// 84
	const char*				subTypes[0x0A];	// 88 - init'd to 0
	float*					skillUsages;	// B0
	UInt32					unkB4;			// B4
	UInt32					unkB8;			// B8
	BGSSkillPerkTreeNode*	perkTree;			// BC - BGSSkillPerkTreeNode
	UInt8					padC0[8];	// C0 - ? not initialized
};
assert(sizeof(ActorValueInfo) == 0xC8);

class TESBoundObject : public TESObject {
public:
	struct Bound {
		UInt16	x;
		UInt16	y;
		UInt16	z;
	};

	virtual void	Unk_47(UInt32 arg);
	virtual UInt32	Unk_48(void);
	virtual UInt32	Unk_49(UInt32 arg);	// return Unk_3E(arg, 0); // model-related?
	virtual bool	Unk_4A();
	virtual bool	Unk_4B(void* arg0, BSString* dst);	// steal/take string
	virtual bool	Unk_4C(void* arg0, UInt8 arg1, UInt32 arg2, float arg3);
	virtual void	Unk_4D(UInt32 arg);
	virtual void	Unk_4E(UInt32 arg);
	virtual void	Unk_4F();
	virtual void	Unk_50();
	virtual void	Unk_51();

	Bound	bounds;		// 14
	Bound	bounds2;	// 1A
};
assert(sizeof(TESBoundObject) == 0x20);

class TESBoundAnimObject : public TESBoundObject {};
assert(sizeof(TESBoundAnimObject) == 0x20);

class TESSound : public TESBoundAnimObject {
public:

	void SetFile(const char* Name) {}

	BGSSoundDescriptorForm* descriptor;	// 20
};
assert(sizeof(TESSound) == 0x24);

class TESObjectLIGH : public TESBoundAnimObject {
public:

	struct Data78 {
		UInt32	unk00;	// 00
		UInt32	unk04;	// 04
		UInt32	unk08;	// 08
		UInt32	unk0C;	// 0C
		UInt32	unk10;	// 10
		float	unk14;	// 14 - 90
		float	unk18;	// 18 - .001
		UInt32	unk1C;	// 1C
		UInt32	unk20;	// 20
		UInt32	unk24;	// 24
	};

	struct DataA8 {
		UInt32	unk0;	// 0
		UInt32	unk4;	// 4
		UInt32	unk8;	// 8
	};

	TESFullName					fullName;		// 20
	TESModelTextureSwap			texSwap;		// 28
	TESIcon						icon;			// 44
	BGSMessageIcon				messageIcon;	// 4C
	TESWeightForm				weight;			// 58
	TESValueForm				value;			// 60
	BGSDestructibleObjectForm	destructible;	// 68
	BGSEquipType				equipType;		// 70
	Data78						unk78;			// 78
	float						unkA0;			// A0 - 1
	UInt32						unkA4;			// A4
	DataA8						unkA8;			// A8
};
assert(sizeof(TESObjectLIGH) == 0xB4);

class TESObjectWEAP : public TESBoundObject {
public:
	enum WeaponType {
		kType_HandToHandMelee = 0,
		kType_OneHandSword,
		kType_OneHandDagger,
		kType_OneHandAxe,
		kType_OneHandMace,
		kType_TwoHandSword,
		kType_TwoHandAxe,
		kType_Bow,
		kType_Staff,
		kType_CrossBow,
		kType_H2H,
		kType_1HS,
		kType_1HD,
		kType_1HA,
		kType_1HM,
		kType_2HS,
		kType_2HA,
		kType_Bow2,
		kType_Staff2,
		kType_CBow
	};

	struct GameData {
		enum Flags1 {
			kFlags_PlayerOnly = 0x01,
			kFlags_NPCUseAmmo = 0x02,
			kFlags_NoJamAfterReload = 0x04,
			kFlags_MinorCrime = 0x10,
			kFlags_NotUsedInNormalCombat = 0x40,
			kFlags_Unknown1 = 0x100,
			kFlags_LongBursts = 0x800,
			kFlags_NonHostile = 0x1000,
			kFlags_BoundWeapon = 0x2000,
		};

		enum Flags2 {
			kFlags_Hidebackpack = 0x01,
			kFlags_Automatic = 0x02,
			kFlags_CantDrop = 0x08,
			kFlags_EmbeddedWeapon = 0x20,
			kFlags_Unknown2 = 0x40,
			kFlags_NotPlayable = 0x80,
		};

		UInt32	unk00;			// 00
		float	speed;			// 04
		float	reach;			// 08
		float	minRange;		// 0C
		float	maxRange;		// 10
		float	animationMult;	// 14
		float	unk18;			// 18
		float	stagger;		// 1C
		UInt32	unk20;			// 20
		UInt32	skill;			// 24
		UInt32	resist;			// 28
		UInt16	flags1;			// 2C
		UInt8	vatsChance;		// 2E
		UInt8	unk2F;			// 2F
		UInt8	unk30;			// 30
		UInt8	type;			// 31
		UInt8	flags2;			// 32
		UInt8	unk33;			// 33
	};

	struct CritData {
		float		critMult;			// 00
		SpellItem*	critEffect;			// 04
		UInt16		critDamage;			// 08
		UInt8		effectOnDeath;		// 0A
		UInt8		pad0B;				// 0B
	};

	TESFullName					fullName;		// 020
	TESModelTextureSwap			texSwap;		// 028
	TESIcon						icon;			// 044
	TESEnchantableForm			enchantable;	// 04C
	TESValueForm				value;			// 058
	TESWeightForm				weight;			// 060
	TESAttackDamageForm			damage;			// 068
	BGSDestructibleObjectForm	destructible;	// 070
	BGSEquipType				equipType;		// 078
	BGSPreloadable				preloadable;	// 080
	BGSMessageIcon				messageIcon;	// 084
	BGSPickupPutdownSounds		pickupSounds;	// 090
	BGSBlockBashData			blockBash;		// 09C
	BGSKeywordForm				keyword;		// 0A8
	TESDescription				description;	// 0B4
	GameData					gameData;		// 0C0
	CritData					critData;		// 0F4
	TESForm*					scopeEffect;	// 100
	BGSSoundDescriptorForm*		attackSound;	// 104
	BGSSoundDescriptorForm*		attackSound2D;	// 108
	BGSSoundDescriptorForm*		attackLoopSound;// 10C
	BGSSoundDescriptorForm*		attackFailSound;// 110
	BGSSoundDescriptorForm*		idleSound;		// 114
	BGSSoundDescriptorForm*		equipSound;		// 118
	BGSSoundDescriptorForm*		unequipSound;	// 11C
	BGSImpactDataSet*			impactDataSet;	// 120
	TESObjectSTAT*				model;			// 124
	TESObjectWEAP*				templateForm;	// 128 - Non-weapon templates don't make sense here and would probably crash anyway so assume it
	BSFixedString				embeddedNode;	// 12C
	UInt32						pad130;			// 130
};
assert(sizeof(TESObjectWEAP) == 0x134);

class BGSPerkEntry {
public:
	virtual ~BGSPerkEntry();

	UInt8	rank;			// 04
	UInt8	priority;		// 05
	UInt16	type;			// 06
};
assert(sizeof(BGSPerkEntry) == 0x08);

class Condition {
public:
	enum ComparisonFlags {
		kComparisonFlag_And			 = 0x00,
		kComparisonFlag_Or			 = 0x01,
		kComparisonFlag_Equal		 = 0x00,
		kComparisonFlag_UseAliases	 = 0x02,
		kComparisonFlag_Global		 = 0x04,
		kComparisonFlag_UsePackData  = 0x08,
		kComparisonFlag_SwapTarget	 = 0x10,
		kComparisonFlag_NotEqual	 = 0x20,
		kComparisonFlag_Greater		 = 0x40,
		kComparisonFlag_GreaterEqual = 0x60,
		kComparisonFlag_Less		 = 0x80,
		kComparisonFlag_LessEqual	 = 0xA0
	};
	enum ReferenceTypes {
		kReferenceType_None = 0,
		kReferenceType_Target,
		kReferenceType_Reference,
		kReferenceType_CombatTarget,
		kReferenceType_LinkedRef,
		kReferenceType_Alias,
		kReferenceType_PackageData,
		kReferenceType_EventData
	};
	Condition*	next;					// 00
	UInt32		compareValue;			// 04
	UInt32		unk08;					// 08
	UInt32		unk0C;					// 0C - FFFFFFFF
	UInt16		functionId;				// 10
	UInt8		unk12;					// 12
	UInt8		unk13;					// 13
	UInt32		param1;					// 14
	UInt32		param2;					// 18
	UInt8		comparisonType;			// 1C
	UInt8		referenceType;			// 1D
};
assert(sizeof(Condition) == 0x20);

class BGSPerk : public TESForm {
public:
	struct PerkData {
		bool				isTrait;	// 00
		UInt8				minLevel;	// 01
		UInt8				numRanks;	// 02
		bool				isPlayable;	// 03
		bool				isHidden;	// 04
		UInt8				unk05;		// 05 todo: collapse to pad[3] after verifying isPlayable and isHidden
		UInt8				unk06;		// 06
		UInt8				unk07;		// 07
	};

	TESFullName				fullName;		// 14
	TESDescription			description;	// 1C
	TESIcon					icon;			// 28
	PerkData				data;			// 30
	Condition*				conditions;		// 38
	TArray<BGSPerkEntry*>	perkEntries;	// 3C
	BGSPerk*				nextPerk;		// 48
};
assert(sizeof(BGSPerk) == 0x4C);

class TESObjectREFRData {
public:
	UInt32	unk00;			// 00
	UInt32	unk04;			// 04
	UInt32	unk08;			// 08
	UInt32	unk0C;			// 0C
	float	waterHeight;	// 10
	UInt32	unk14;			// 14
	UInt32	unk18;			// 18
	UInt32	unk1C;			// 1C
	NiNode* node;			// 20
	// ... probably more
};
assert(sizeof(TESObjectREFRData) == 0x24);

class TESObjectCELL : public TESForm {
public:
	enum {
		kFlags0_Interior = 1 << 0,
		kFlags0_HasWater = 1 << 1,
	};

	struct ExteriorData {
		UInt32		unk00;	// 00
		UInt32		unk04;	// 04
		UInt32		unk08;	// 08
		UInt32		unk0C;	// 0C
		UInt32		unk10;	// 10
		UInt32		unk14;	// 14
		UInt8		unk18;	// 18
		UInt8		pad18[3];
	};

	struct LightingData {
		struct InteriorInnerData {
			UInt32		unk00;	// 00
			UInt32		unk04;	// 04
			UInt32		unk08;	// 08
			UInt32		unk0C;	// 0C
			UInt32		unk10;	// 10
			UInt32		unk14;	// 14
			UInt32		unk18;	// 18
			UInt32		unk1C;	// 1C
		};

		RGBA				ambient;	// 00
		RGBA				directional;// 04
		RGBA				fog;		// 08
		float				fogNear;	// 0C
		float				fogFar;		// 10
		UInt32				unk14;		// 14
		UInt32				unk18;		// 18
		UInt32				unk1C;		// 1C
		UInt32				unk20;		// 20
		UInt32				unk24;		// 24
		InteriorInnerData	interiorInnerData;	// 28
		UInt32				unk48;		// 48
		UInt32				unk4C;		// 4C
		UInt32				unk50;		// 50
		UInt32				unk54;		// 54
		UInt32				unk58;		// 58
		UInt32				unk5C;		// 5C
	};

	TESWaterForm*			GetWaterForm() { return (TESWaterForm*)ThisCall(0x004C0800, this); }

	TESFullName				fullName;		// 14
	UInt32					unk1C;			// 1C
	UInt32					unk20;			// 20
	UInt32					unk24;			// 24
	UInt32					unk28;			// 28
	UInt16					flags0;			// 2C flags0
	UInt16					unk2E;			// 2E
	UInt8					unk30;			// 30
	UInt8					unk31;			// 31
	UInt8					unk32;			// 32
	UInt8					pad33;			// 33
	ExtraDataList*			extraDataList;	// 34 - ExtraDataList: ExtraEditorID, ExtraCellImageSpace, ExtraCellMusicType, ExtraLocation, ExtraEncounterZone, ExtraCellAcousticSpace, ExtraSeenData, ExtraHavok
	UInt32					unk38;			// 38
	union {									// 3C
		ExteriorData*		exteriorData;
		LightingData*		lighting;		// if interior
	};
	UInt32					unk40;			// 40
	float					waterHeight;	// 44
	UInt32					unk48;			// 48
	TArray<TESObjectREFR*>	objectList;		// 4C
	TArray<UInt32>			unk58;			// 58
	TArray<UInt32>			unk64;			// 64
	TArray<UInt32>			unk70;			// 70
	UInt32					unk7C;			// 7C
	UInt32					unk80;			// 80
	TESWorldSpace*			worldSpace;		// 84
	UInt32					unk88;			// 88
	BGSLightingTemplate*	lightingTemplate;	// 8C
};
assert(sizeof(TESObjectCELL) == 0x90);

class TESObjectREFR : public TESForm {
public:
	virtual void	Unk_39();
	virtual void	Unk_3A();
	virtual void	Unk_3B();
	virtual void	Unk_3C();
	virtual void	Unk_3D();
	virtual void	Unk_3E();
	virtual void	Unk_3F();
	virtual void	Unk_40();
	virtual void	Unk_41();
	virtual void	Unk_42();
	virtual void	Unk_43();
	virtual void	Unk_44();
	virtual void	Unk_45();
	virtual void	Unk_46();
	virtual void	Unk_47();
	virtual void	Unk_48();
	virtual void	Unk_49();
	virtual void	Unk_4A();
	virtual void	Unk_4B();
	virtual void	Unk_4C();
	virtual void	Unk_4D();
	virtual void	Unk_4E();
	virtual void	Unk_4F();
	virtual void	Unk_50();
	virtual void	GetStartingPos(NiPoint3* pos);
	virtual void	Unk_52();
	virtual void	Unk_53();
	virtual void	Unk_54();
	virtual void	Unk_55();
	virtual void	Unk_56();
	virtual void	Unk_57();
	virtual void	Unk_58();
	virtual void	Unk_59();
	virtual void	Unk_5A();
	virtual void	GetMarkerPosition(NiPoint3* pos);
	virtual void	Unk_5C();
	virtual void	Unk_5D();
	virtual void	Unk_5E();
	virtual void	Unk_5F();
	virtual void	Unk_60();
	virtual void*	GetFaceGenNiNode(); //returns BSFaceGenNiNode*
	virtual void	Unk_62();
	virtual void*	GetFaceGenAnimationData(); //BSFaceGenAnimationData*
	virtual void	Unk_64();
	virtual void	Unk_65();
	virtual void	Unk_66();
	virtual void	Unk_67();
	virtual void	Unk_68();
	virtual void	Unk_69();
	virtual void	Unk_6A();
	virtual void 	Unk_6B();
	virtual void	Unk_6C();
	virtual void	SetNiNode(NiNode* root, UInt32 unk1); // NULL, 1?
	virtual void	Unk_6E();
	virtual NiNode* GetNiRootNode(UInt32 firstPerson);
	virtual NiNode* GetNiNode();	// Root of the skeleton (Get3D)
	virtual void	Unk_71();
	virtual void	Unk_72();
	virtual void	Unk_73();
	virtual void	Unk_74();
	virtual void	Unk_75();
	virtual void	Unk_76();
	virtual void	Unk_77();
	virtual void	Unk_78();
	virtual void	Unk_79();
	virtual void	Unk_7A();
	virtual void	Unk_7B();
	virtual void	Unk_7C();
	virtual void	Unk_7D();
	virtual void*	GetWeightModel(UInt32 weightModel); // 0 Small 1 Large, returns ActorWeightModel*
	virtual void	Unk_7F();
	virtual void	Unk_80();
	virtual void	Unk_81();
	virtual void	Unk_82();
	virtual void	Unk_83();
	virtual void	Unk_84();
	virtual void	Unk_85();
	virtual void	Unk_86();
	virtual void	Unk_87();
	virtual void	Unk_88();
	virtual void	ResetInventory(bool unk);
	virtual void	Unk_8A();
	virtual void	Unk_8B();
	virtual void	Unk_8C();
	virtual void	Unk_8D();
	virtual void	Unk_8E();
	virtual void	Unk_8F();
	virtual void	Unk_90();
	virtual void	Unk_91();
	virtual void	Unk_92();
	virtual void	Unk_93();
	virtual void	Unk_94();
	virtual void	Unk_95();
	virtual void	Unk_96();
	virtual void	Unk_97();
	virtual void	Unk_98();
	virtual bool	GetDead(UInt8 Arg1); // Arg1 = 1 for Actors
	virtual void	Unk_9A();
	virtual void	Unk_9B();

	NiRefObject			handleRefObject;	// 14
	BSTEventSink<void*>	animGraphEventSink;	// 1C BSTEventSink<BSAnimationGraphEvent>
	UInt32				animGraphHolder;	// 20 IAnimationGraphManagerHolder
	TESForm*			baseForm;			// 24
	NiPoint3			rot;				// 28
	NiPoint3			pos;				// 34
	TESObjectCELL*		parentCell;			// 40
	TESObjectREFRData*	renderData;			// 44
	ExtraDataList		extraDataList;		// 48
	UInt32				unk50;				// flags?
};
assert(sizeof(TESObjectREFR) == 0x54);

class ActorValuesOwner {
public:
	virtual ~ActorValuesOwner();
	virtual float	GetCurrent(UInt32 arg);
	virtual float	GetMaximum(UInt32 arg);
	virtual float	GetBase(UInt32 arg);
	virtual void	SetBase(UInt32 arg0, float arg1);
	virtual void	ModBase(UInt32 arg0, float arg1);
	virtual void	Unk_06(UInt32 arg0, UInt32 arg1, UInt32 arg2); // Force/Mod AV?
	virtual void	SetCurrent(UInt32 arg0, float arg1);
	virtual bool	Unk_08();
};
assert(sizeof(ActorValuesOwner) == 0x4);

class ActorState {
public:
	virtual ~ActorState();

	enum {
		kState_Running		= 0x40,
		kState_Walking		= 0x80,
		kState_Sprinting	= 0x100,
		kState_Sneaking		= 0x200,
		kState_Swimming		= 0x400
	};

	UInt32	flags04;
	UInt32	flags08;

	bool IsWeaponOut() { return (flags08 >> 5 & 7) >= 3; }
};
assert(sizeof(ActorState) == 0x0C);

class HighProcess {
public:
	struct Data30 {
		UInt32	unk00;	// 00
		UInt32	unk04;	// 04
		UInt32	unk08;	// 08
		UInt32	unk0C;	// 0C
		UInt32	unk10;	// 10
		UInt32	unk14;	// 14
		UInt32	unk18;	// 18 - (AggroRadius Violated - 14)
	};

	UInt32			unk00;	// 00
	UInt32			unk04;	// 04
	UInt32			unk08;	// 08
	UInt32			unk0C;	// 0C
	UInt32			unk10;	// 10
	UInt32			unk14;	// 14
	UInt32			unk18;	// 18
	UInt32			unk1C;	// 1C
	UInt32			unk20;	// 20
	UInt32			unk24;	// 24
	UInt32			unk28;	// 28
	float			unk2C;	// 2C
	Data30*			unk30;	// 30
	UInt32			unk34;	// 34
	UInt32			unk38;	// 38
	UInt32			unk3C;	// 3C
	float			unk40;	// 40
	UInt32			unk44;	// 44
	UInt32			unk48;	// 48
	UInt32			unk4C;	// 4C
	UInt32			unk50;	// 50
	UInt32			unk54;	// 54
	UInt32			unk58;	// 58
	UInt32			unk5C;	// 5C
	float			unk60;	// 60
	UInt32			unk64;	// 64
	UInt32			unk68;	// 68
	UInt32			unk6C;	// 6C
	UInt32			unk70;	// 70
	UInt32			unk74;	// 74
	UInt32			unk78;	// 78
	UInt32			unk7C;	// 7C
	UInt32			unk80;	// 80
	float			unk84;	// 84
	float			unk88;	// 88
	float			unk8C;	// 8C
	float			unk90;	// 90
	float			unk94;	// 94
	float			unk98;	// 98
	UInt32			unk9C;	// 9C
	UInt32			unkA0;	// A0
	UInt32			unkA4[11];	// A4 BSResponse<BSFixedStringCI, Actor, BSFixedStringCI, DoNothingUnhandledPolicy<BSFixedStringCI>>
	UInt32			unkD0;	// D0
	void*			unkD4;	// D4 - NiNode?
	void*			unkD8;	// D8 - NiNode?
	UInt32			unkDC;	// D8
	void*			unkE0;	// E0 - BSFaceGenNiNode?
	void*			unkE4;	// E4
	UInt32			unkE8;	// E8
	UInt32			unkEC;	// EC
	UInt32			unkF0;	// F0
	UInt32			unkF4;	// F4
	TList<ActiveEffect>* effectList;	// F8
	void*			unkFC;	// FC
	void*			unk100;	// 100
	void*			unk104;	// 104
	UInt32			unk108;	// 108
	UInt32			unk10C;	// 10C
	UInt32			unk110;	// 110
	UInt32			unk114;	// 114
	UInt32			unk118;	// 118
	UInt32			unk11C;	// 11C
	UInt32			unk120;	// 120
	UInt32			unk124;	// 124
	UInt32			unk128;	// 128
	UInt32			unk12C;	// 12C - FFFFFFFF
	UInt32			unk130;	// 130
	UInt32			unk134;	// 134 - FF7FFFFF
	UInt32			furnitureHandle;	// 138
	UInt32			unk13C;	// 13C
	UInt32			unk140;	// 140
	UInt32			unk144;	// 144
	TESIdleForm*	currentIdle;	// 148
	UInt32			unk14C; // 14C
	UInt32			unk150;	// 150
	UInt32			unk154;	// 154
	UInt32			unk158;	// 158
	void*			unk15C;	// 15C - hkCharacterProxy?
	void*			unk160;	// 160
	UInt32			unk164;	// 164
	UInt32			unk168;	// 168
	UInt32			unk16C;	// 16C
	UInt32			unk170;	// 170
	UInt32			unk174;	// 174
	void*			unk178;	// 178
	UInt32			unk17C;	// 17C
	UInt32			unk180;	// 180
	UInt32			unk184;	// 184
	UInt32			unk188;	// 188
	UInt32			unk18C;	// 18C
	UInt32			unk190;	// 190
	UInt32			unk194;	// 194
	UInt32			unk198;	// 198
	UInt32			unk19C;	// 19C
	UInt32			unk1A0;	// 1A0
	UInt32			unk1A4;	// 1A4
	float			unk1A8;	// 1A8
	UInt32			unk1AC;	// 1AC
	UInt32			unk1B0;	// 1B0
	float			actorAlpha;	// 1B4
	// More?...
};
assert(sizeof(HighProcess) == 0x1B8);

class ActorProcessManager {
public:
	enum EquippedHand {
		kEquippedHand_Left = 0,
		kEquippedHand_Right = 1
	};

	enum {
		kFlags_None = 0,
		kFlags_Unk01 = 1,
		kFlags_Unk02 = 2,
		kFlags_Unk03 = 4,
		kFlags_DrawHead = 8,
		kFlags_Mobile = 16,
		kFlags_Reset = 32
	};

	UInt32				unk00;						// 00
	HighProcess*		process;					// 04
	void*				unk08;						// 08
	TESPackage*			package;					// 0C
	UInt32				unk10[(0x54 - 0x10) >> 2];	// 10
	float				timeOfDeath;				// 54 - GetTimeDead = (GameDaysPassed*24) - timeOfDeath
	UInt32				unk58[(0x68 - 0x58) >> 2];	// 58
	TESForm*			equippedObject[2];			// 68
	UInt32				unk70[(0x98 - 0x70) >> 2];	// 70
	UInt8				unk98;						// 98
	UInt8				unk9A;						// 9A
	SInt8				unk9B;						// 9B
	UInt8				unk9C[(0xA0 - 0x9C)];		// 9C
};
assert(sizeof(ActorProcessManager) == 0xA0);

class EquipManager {
public:
	static EquipManager*	Get() { return (EquipManager*)0x01B2EC90; }
	void					EquipItem(TESForm* Form, UInt32 Quantity, ExtraDataList* List) { ThisCall(0x006EF3E0, this, Form, List, Quantity, NULL, true, false, false, NULL); }
	void					UnequipItem(TESForm* Form, UInt32 Quantity, ExtraDataList* List) { ThisCall(0x006EE560, this, Form, List, Quantity, NULL, false, false, true, false, NULL); }

	UInt8	Initialized;	// 00
	UInt8	pad00[3];
};
assert(sizeof(EquipManager) == 0x04);

class Actor : public TESObjectREFR {
public:
	enum ActorVal {
		kActorVal_Aggression = 0,
		kActorVal_Confidence,
		kActorVal_Energy,
		kActorVal_Morality,
		kActorVal_Mood,
		kActorVal_Assistance,		
		kActorVal_Health = 0x18,
		kActorVal_Magicka,
		kActorVal_Stamina,
	};

	virtual void Unk_9C();
	virtual void Unk_9D();
	virtual void Unk_9E();
	virtual void Unk_9F();
	virtual void Unk_A0();
	virtual void Unk_A1();
	virtual void Unk_A2();
	virtual void Unk_A3();
	virtual void Unk_A4();
	virtual void DrawSheatheWeapon(bool draw);
	virtual void Unk_A6();
	virtual void Unk_A7();
	virtual void Unk_A8();
	virtual void Unk_A9();
	virtual void Unk_AA();
	virtual void Unk_AB();
	virtual void Unk_AC();
	virtual void Unk_AD();
	virtual void Unk_AE();
	virtual void Unk_AF();
	virtual void Unk_B0();
	virtual void Unk_B1();
	virtual void Unk_B2();
	virtual void Unk_B3();
	virtual void Unk_B4();
	virtual void Unk_B5();
	virtual void Unk_B6();
	virtual void Unk_B7();
	virtual void Unk_B8();
	virtual void ServeSentence();
	virtual void Unk_BA();
	virtual void Unk_BB();
	virtual void Unk_BC();
	virtual void Unk_BD();
	virtual void Unk_BE();
	virtual void Unk_BF();
	virtual void Unk_C0();
	virtual void Unk_C1();
	virtual void Unk_C2();
	virtual void Unk_C3();
	virtual void Unk_C4();
	virtual void Unk_C5();
	virtual void Unk_C6();
	virtual void Unk_C7();
	virtual void Unk_C8();
	virtual void Unk_C9();
	virtual void Unk_CA();
	virtual void Unk_CB();
	virtual void Unk_CC();
	virtual void Unk_CD();
	virtual void Unk_CE();
	virtual void Unk_CF();
	virtual void Unk_D0();
	virtual void Unk_D1();
	virtual void Unk_D2();
	virtual void Unk_D3();
	virtual void Unk_D4();
	virtual void Unk_D5();
	virtual void Unk_D6();
	virtual void Unk_D7();
	virtual void Unk_D8();
	virtual void Unk_D9();
	virtual void Unk_DA();
	virtual void Unk_DB();
	virtual void Unk_DC();
	virtual void Unk_DD();
	virtual void Unk_DE();
	virtual void Unk_DF();
	virtual void Unk_E0();
	virtual void Unk_E1();
	virtual bool IsInCombat();
	virtual void Unk_E3();
	virtual void Unk_E4();
	virtual void Unk_E5();
	virtual void Unk_E6();
	virtual void Unk_E7();
	virtual void Unk_E8();
	virtual void Unk_E9();
	virtual void Unk_EA();
	virtual void Unk_EB();
	virtual void Unk_EC();
	virtual void Unk_ED();
	virtual void Unk_EE();
	virtual void Unk_EF();
	virtual void Unk_F0();
	virtual void Unk_F1();
	virtual void Unk_F2();
	virtual void Unk_F3();
	virtual void Unk_F4();
	virtual void Unk_F5();
	virtual void AdvanceSkill(UInt32 skillId, float points, UInt32 unk1, UInt32 unk2);
	virtual void Unk_F7();
	virtual void Unk_F8();
	virtual void VisitPerks(); // BGSPerk::FindPerkInRanksVisitor
	virtual void AddPerk(BGSPerk* perk, UInt32 unk1);
	virtual void RemovePerk(BGSPerk* perk);

	class SpellArray {
	public:
		enum {
			kLocalAlloc = 0x80000000,
		};

		UInt32		allocatedCount;	// 00 - upper bit is set when single-element optimization is used
		union {
			SpellItem** spells;		// 04
			SpellItem* singleSpell;	// 04 - used when kLocalAlloc is set
		};
		UInt32		spellCount;		// 08
	};

	enum Flags1 {
		kFlags_AIEnabled		= 0x02,
		kFlags_IsPlayerTeammate = 0x4000000
	};
	enum Flags2 {
		kFlags_CanDoFavor		= 0x80
	};

	UInt8					GetSitSleepState() { return actorState.flags04 >> 14 & 0xF; };
	float					GetBaseActorValue(ActorVal Code) { return avOwner.GetBase(Code); }
	float					GetActorValue(ActorVal Code) { return avOwner.GetCurrent(Code); }
	void					EquipItem(TESForm* Form, UInt32 Quantity, ExtraDataList* List) { EquipManager::Get()->EquipItem(Form, Quantity, List); }
	void					UnequipItem(TESForm* Form, UInt32 Quantity, ExtraDataList* List) { EquipManager::Get()->UnequipItem(Form, Quantity, List); }
	bool					IsFemale() { return false; }
	void					QueueNiNodeUpdate() { ThisCall(0x00730EE0, this, 0); }
	TESForm*				GetEquippedObject(ActorProcessManager::EquippedHand Hand) { return processManager->equippedObject[Hand]; }

	MagicTarget				magicTarget;					// 054
	ActorValuesOwner		avOwner;						// 060
	ActorState				actorState;						// 064
	UInt32					transformDeltaEvent;			// 070 .?AV?$BSTEventSink@VBSTransformDeltaEvent@@@@
	UInt32					characterMoveFinishEvent;		// 074 .?AV?$BSTEventSink@VbhkCharacterMoveFinishEvent@@@@
	UInt32					unk078;							// 078 IPostAnimationChannelUpdateFunctor
	UInt32					flags1;							// 07C
	UInt32					unk080;							// 080
	UInt32					unk084;							// 084
	ActorProcessManager*	processManager;					// 088
	UInt32					unk08C[(0x0FC - 0x08C) >> 2];	// 08C
	SpellArray				addedSpells;					// 0FC
	UInt32					unk108[(0x128 - 0x108) >> 2];	// 108
	TESForm*				equippedShout;					// 128
	UInt32					unk12C;							// 12C
	TESRace*				race;							// 130
	UInt32					unk134;							// 134
	UInt32					flags138;						// 138 Burgling house: flags138 >> 12 & 1
	UInt32					unk13C[(0x19C - 0x13C) >> 2];
};
assert(sizeof(Actor) == 0x19C);

class Character : public Actor {};
assert(sizeof(Character) == 0x19C);

class TESCameraState {
public:
	virtual	~TESCameraState();
	virtual void OnStateStart();
	virtual void OnStateEnd();
	virtual void OnUpdate(void* unk1);
	virtual void Unk_04();
	virtual void Unk_05();
	virtual void Unk_06();
	virtual void Unk_07();
	virtual void Unk_08();
	
	enum CameraState {
		kCameraState_FirstPerson = 0,
		kCameraState_AutoVanity,
		kCameraState_VATS,
		kCameraState_Free,
		kCameraState_IronSights,
		kCameraState_Furniture,
		kCameraState_Transition,
		kCameraState_TweenMenu,
		kCameraState_ThirdPerson1,
		kCameraState_ThirdPerson2,
		kCameraState_Horse,
		kCameraState_Bleedout,
		kCameraState_Dragon,
	};

	BSIntrusiveRefCounted	refCount;		// 04
	PlayerCamera*			camera;			// 08
	UInt32					stateId;		// 0C
};
assert(sizeof(TESCameraState) == 0x010);

class DragonCameraState : public TESCameraState {
public:
	PlayerInputHandler		inputHandler;		// 10
	NiNode*					cameraNode;			// 18
	NiNode*					controllerNode;		// 1C
	float					unk20[0x03];		// 20
	UInt32					unk2C[0x07];		// 2C
	float					unk48[0x03];		// 48
	UInt32					unk54[0x11];		// 54
	float					unk98[0x03];		// 98
	UInt32					unkA4[0x04];		// A4
	UInt8					unkB4[0x07];		// B4
	UInt8					padBB;
	// More
};
assert(sizeof(DragonCameraState) == 0x0BC);

class HorseCameraState : public TESCameraState {
public:
	PlayerInputHandler		inputHandler;		// 10
	NiNode*					cameraNode;			// 18
	NiNode*					controllerNode;		// 1C
	float					unk20[0x03];		// 20
	UInt32					unk2C[0x07];		// 2C
	float					unk48[0x03];		// 48
	UInt32					unk54[0x11];		// 54
	float					unk98[0x03];		// 98
	UInt32					unkA4[0x04];		// A4
	UInt8					unkB4[0x07];		// B4
	UInt8					padBB;
	// More
};
assert(sizeof(HorseCameraState) == 0x0BC);

class TweenMenuCameraState : public TESCameraState {
public:
	UInt32	unk10[0x0C];	// 10
};
assert(sizeof(TweenMenuCameraState) == 0x040);

class VATSCameraState : public TESCameraState {
public:
	UInt32	unk10[0x03];	// 10
};
assert(sizeof(VATSCameraState) == 0x01C);

class FreeCameraState : public TESCameraState {
public:
	PlayerInputHandler		inputHandler;		// 10
	NiPoint3				CameraPosition;		// 18
	UInt32					unk24[0x04];		// 24
	UInt16					unk34;				// 34
	UInt8					unk36;				// 36
	UInt8					unk37;				// 37
};
assert(sizeof(FreeCameraState) == 0x038);

class AutoVanityState : public TESCameraState { };
assert(sizeof(AutoVanityState) == 0x010);

class FurnitureCameraState : public TESCameraState {
public:
	UInt32	unk10;	// 10
	float	unk14;	// 14
	float	unk18;	// 18
	float	unk1C;	// 1C
	UInt32	unk20;	// 20
	UInt32	unk24;	// 24
	UInt32	unk28;	// 28
	UInt8	unk2C;	// 2C
	UInt8	unk2D;	// 2D
	UInt8	unk2E;	// 2E
	UInt8	pad2F;	// 2F
};
assert(sizeof(FurnitureCameraState) == 0x030);

class IronSightsState : public TESCameraState {
public:
	UInt32	unk10;	// 10
};
assert(sizeof(IronSightsState) == 0x014);

class FirstPersonState : public TESCameraState {
public:
	PlayerInputHandler		inputHandler;		// 10
	NiNode*					cameraNode;			// 18
	NiNode*					controllerNode;		// 1C
	UInt32					unk20;				// 20
	float					unk24;				// 24
	float					unk28;				// 28
	UInt32					unk2C[0x03];		// 2C
	UInt8					unk38[0x05];		// 38
	UInt8					pad3D;				// 3D
	UInt16					pad3E;				// 3E
};
assert(sizeof(FirstPersonState) == 0x040);

class ThirdPersonState : public TESCameraState {
public:
	virtual void Unk_09();
	virtual void Unk_0A();
	virtual void UpdateOverShoulder(bool IsWeaponOut);
	virtual void Unk_0C();
	virtual void PlayerToCamera(bool AllowVanityMode);
	virtual void Unk_0E();
	virtual void Unk_0F();

	PlayerInputHandler		inputHandler;				// 10
	NiNode*					cameraNode;					// 18
	NiNode*					controllerNode;				// 1C
	NiPoint3				CameraPosition;				// 20
	float					unk2C;						// 2C
	float					unk30;						// 30
	float					unk34;						// 34
	float					unk38;						// 38
	float					OverShoulderPosX;			// 3C
	float					OverShoulderPosY;			// 40
	float					OverShoulderPosZ;			// 44
	float					unk48;						// 48
	float					unk4C;						// 4C
	float					unk50;						// 50
	float					unk54;						// 54
	float					HeadDistance;				// 58
	float					unk5C;						// 5C
	UInt32					unk60;						// 60
	float					unk64;						// 64
	UInt32					unk68;						// 68
	float					unk6C;						// 6C
	NiPoint3				CameraPosition1;			// 70
	float					unk7C;						// 7C
	UInt32					unk80;						// 80
	UInt32					unk84;						// 84
	UInt32					unk88;						// 88
	UInt32					unk8C;						// 8C
	UInt32					unk90;						// 90
	UInt32					unk94;						// 94
	float					unkCameraOffsetX;			// 98
	float					unkCameraOffsetY;			// 9C
	float					unkCameraOffsetZ;			// A0
	UInt32					unkA4;						// A4
	UInt32					unkA8;						// A8
	float					CameraHeadRotZ;				// AC
	float					CameraHeadRotX;				// B0
	UInt8					unkCamMode;					// B4
	UInt8					unkB5;						// B5
	UInt8					unkB6;						// B6
	UInt8					unkB7;						// B7
	UInt8					AnimCamMode;				// B8
	UInt8					AllowCameraRotation;		// B9
	UInt8					TogglePOV;					// BA
	UInt8					padBA;
};
assert(sizeof(ThirdPersonState) == 0xBC);

class BleedoutCameraState : public TESCameraState {
public:
	PlayerInputHandler		inputHandler;		// 10
	NiNode*					cameraNode;			// 18
	NiNode*					controllerNode;		// 1C
	float					unk20[0x03];		// 20
	UInt32					unk2C[0x07];		// 2C
	float					unk48[0x03];		// 48
	UInt32					unk54[0x11];		// 54
	float					unk98[0x03];		// 98
	UInt32					unkA4[0x04];		// A4
	UInt8					unkB4[0x07];		// B4
	UInt8					padBB;
	// More
};
assert(sizeof(BleedoutCameraState) == 0xBC);

class PlayerCameraTransitionState : public TESCameraState {
public:
	UInt32	unk10[0x05];	// 10
	UInt8	unk24;			// 24
	UInt8	unk25;			// 25
	UInt16	pad26;
};
assert(sizeof(PlayerCameraTransitionState) == 0x28);

class TESCamera {
public:
	virtual ~TESCamera();
	virtual void	SetNode(NiNode* node);
	virtual void	Update();

	float			rotZ;			// 04
	float			rotX;			// 08
	NiPoint3		pos;			// 0C
	float			zoom;			// 18
	NiNode*			cameraNode;		// 1C - First child is usually NiCamera
	TESCameraState* cameraState;	// 20
	UInt8			unk24;			// 24
	UInt8			pad24[3];
};
assert(sizeof(TESCamera) == 0x28);

class PlayerCamera : public TESCamera {
public:	
	static PlayerCamera*			Get() { return (PlayerCamera*)0x01B399A0; }
	void							SetCameraState(TESCameraState* CameraState) { ThisCall(0x006533D0, this, CameraState); }
	void							UpdateOverShoulder(bool IsWeaponOut) { ThisCall(0x0083C7E0, this, IsWeaponOut); }

	UInt32							unk28;										// 28
	UInt32							unk2C;										// 2C
	UInt32							unk30[(0x6C - 0x30) >> 2];					// 30
	FirstPersonState*				firstPersonState;							// 6C
	AutoVanityState*				autoVanityState;							// 70
	VATSCameraState*				vatsCameraState;							// 74
	FreeCameraState*				freeCameraState;							// 78
	IronSightsState*				ironSightsState;							// 7C
	FurnitureCameraState*			furnitureCameraState;						// 80
	PlayerCameraTransitionState*	playerCameraTransitionState;				// 84
	TweenMenuCameraState*			tweenMenuCameraState;						// 88
	ThirdPersonState*				thirdPersonState1;							// 8C
	ThirdPersonState*				thirdPersonState2;							// 90
	HorseCameraState*				horseCameraState;							// 94
	BleedoutCameraState*			bleedoutCameraState;						// 98
	DragonCameraState*				dragonCameraState;							// 9C
	UInt32							unkA0;										// A0
	UInt32							unkA4;										// A4
	UInt32							unkA8;										// A8
	float							worldFoV;									// AC
	float							firstPersonFoV;								// B0
	UInt32							unkB4[(0xD0 - 0xB4) >> 2];					// B4
	UInt8							EnableAutoVanityMode;						// D0
	UInt8							unkD1;										// D1
	UInt8							AllowVanityMode;							// D2
	UInt8							unkD3;										// D3
	UInt8							unkD4;										// D4
	UInt8							unkD5;										// D5
	UInt8							padD5[2];
};
assert(sizeof(PlayerCamera) == 0xD8);

class PlayerSkills {
public:
	enum {
		kAdvanceableSkillOffset = 6,
		kNumAdvanceableSkills = 18
	};

	class StatData {
	public:
		struct LevelData {
			float level;		// 00
			float points;		// 04
			float pointsMax;	// 08
		};

		float		levelPoints;							// 00
		float		levelPointsMax;							// 04
		LevelData	levelData[kNumAdvanceableSkills];		// 08
		UInt32		legendaryLevel[kNumAdvanceableSkills];	// 90
	};

	StatData* data;		// 00
};
assert(sizeof(PlayerSkills) == 0x04);

class PlayerCharacter : public Character {
public:
	void				RestoreCamera() { ThisCall(0x00730EE0, this, 0); }
	void				SetFoV(SceneGraph* WorldSceneGraph, float* SettingWorldFoV, float* Setting1stPersonFoV, float FoV) { PlayerCamera* Camera = PlayerCamera::Get(); WorldSceneGraph->SetCameraFOV(FoV); Camera->worldFoV = Camera->firstPersonFoV = *SettingWorldFoV = *Setting1stPersonFoV = FoV; }
	float				GetFoV(bool IsSpecialView) { PlayerCamera* Camera = PlayerCamera::Get(); return (IsSpecialView ? Camera->firstPersonFoV : Camera->worldFoV); }
	bool				IsThirdPersonView(bool CameraMode, bool FirstPersonView) { return (!CameraMode ? PlayerCamera::Get()->cameraState->stateId == TESCameraState::CameraState::kCameraState_ThirdPerson2 : !FirstPersonView); }
	bool				IsVanityView() { return false; }
	bool				IsAiming() { return false; }
	TESWorldSpace*		GetWorldSpace() { return (parentCell != NULL ? parentCell->worldSpace : NULL); }
	TESRegion*			GetRegion() { return NULL; }
	void				UpdateInventory() {}
	bool				IsMoving() { return false; }
	bool				IsAlive() { return !GetDead(1); }

	UInt32				menuOpenCloseEvent;				// 19C .?AV?$BSTEventSink@VMenuOpenCloseEvent@@@@
	UInt32				menuModeChangeEvent;			// 1A0 .?AV?$BSTEventSink@VMenuModeChangeEvent@@@@
	UInt32				userEventEnabledEvent;			// 1A4 .?AV?$BSTEventSink@VUserEventEnabledEvent@@@@
	UInt32				actorCellEventSource[12];		// 1A8 .?AV?$BSTEventSource@UBGSActorCellEvent@@@@
	UInt32				actorDeathEventSource[12];		// 1D8 .?AV?$BSTEventSource@UBGSActorDeathEvent@@@@
	UInt32				positionPlayerEventSource[12];	// 208 .?AV?$BSTEventSource@UPositionPlayerEvent@@@@
	UInt32				pad238[(0x430 - 0x238) >> 2];	// 238
	UInt32				JailedState;					// 430
	UInt32				pad434[(0x490 - 0x434) >> 2];	// 434
	UInt32				unk490;							// 490 - Handle
	UInt32				pad494[(0x568 - 0x494) >> 2];	// 494
	UInt32				unk568;							// 568 - Handle
	UInt32				unk56C;							// 56C
	UInt32				unk570;							// 570
	UInt32				unk574;							// 574
	UInt32				unk578;							// 578
	UInt32				unk57C;							// 57C
	UInt32				unk580;							// 580
	UInt32				HoursToSleep;					// 584 (value is in seconds)
	UInt32				unk588;							// 588
	NiNode*				firstPersonNiNode;				// 58C
	UInt32				pad590[(0x5AC - 0x590) >> 2];
	UInt32				lastRiddenHorseHandle;			// 5AC - Handle
	UInt32				pad5B0[(0x614 - 0x5B0) >> 2];
	PlayerSkills*		skills;							// 614
	UInt32				targetHandle;					// 618
	UInt32				unk61C;							// 61C
	UInt32				unk620;							// 620
	UInt32				unk624;							// 624
	UInt32				unk628;							// 628
	UInt32				unk62C;							// 62C
	TArray<UInt32>		hostileHandles;					// 630
	UInt32				unk63C;							// 63C
	UInt32				unk640;							// 640
	TESForm*			tempPoison;						// 644
	UInt32				numTeammates;					// 648
	UInt32				pad64C[(0x6E0 - 0x64C) >> 2];
	UInt8				isAMurderer;					// 6E0
	UInt8				numPerkPoints;					// 6E1
	UInt8				flags6E2;						// 6E2
	UInt8				flags6E3;						// 6E3
	UInt32				unk6E4;							// 6E4
	TArray<void*>		tintMasks;						// 6E8		// These are the actual tints TArray<TintMask*>
	TArray<void*>*		overlayTintMasks;				// 6F4		// These apply when overlay head parts is enabled TArray<TintMask*>*
	UInt32				pad6F8[(0x724 - 0x6F8) >> 2];
	UInt8				unk724;							// 724
	UInt8				flags725;						// 725 IsPlayerSleeping: flags725 & 4
	UInt8				unk726;							// 726
	UInt8				unk727;							// 727
	UInt32				unk728;							// 728
};
assert(sizeof(PlayerCharacter) == 0x72C);

class PlayerControls {
public:
	virtual	~PlayerControls();
	virtual UInt32		Unk_01();

	static PlayerControls*	Get() { return (PlayerControls*)0x01B2EDF0; }
	bool					IsCamSwitchControlEnabled() { return ThisCall(0x00772A20, this); }

	struct Modes {
		UInt32			LeftRight;		// 00 Left: 0xBF800000 - Right: 0x3F800000
		UInt32			ForwardBack;	// 04 Forward: 0x3F800000 - Back: 0xBF800000
		UInt32			unk08;			// 08
		UInt32			unk0C;			// 0C
		UInt32			unk10;			// 10
		UInt32			unk14;			// 14
		UInt32			unk18;			// 18
		UInt32			unk1C;			// 1C
		UInt32			unk20;			// 20
		UInt8			AutoMove;		// 24
		UInt8			AlwaysRun;		// 25
		UInt8			unk26;			// 26
		UInt8			TogglePOV;		// 27
		UInt16			unk28;			// 28
		UInt8			unk2A;			// 2A
		UInt8			unk2B;			// 2B
		UInt8			unk2C;			// 2C
		UInt8			pad2A[3];
	};

	BSTEventSink<void*>	menuOpenCloseEvent;		// 004
	BSTEventSink<void*>	menuModeChangeEvent;	// 008
	BSTEventSink<void*>	furnitureEvent;			// 00C
	UInt32				pad010;					// 010
	Modes				modes;					// 014
	UInt32				unk044;					// 044
	UInt32				unk048;					// 048
	UInt32				unk04C;					// 04C
	UInt32				unk050;					// 050
	UInt32				unk054;					// 054
	UInt32				unk058;					// 058
	UInt32				unk05C;					// 05C
	UInt32				unk060;					// 060
	UInt32				unk064;					// 064
	UInt8				Processing;				// 068
	UInt8				pad068[3];
	UInt32				unk06C[(0x114 - 0x06C) >> 2];	// 06C
	UInt32				unk114;					// 114
	UInt32				unk118;					// 118
	UInt32				unk11C;					// 11C
	UInt32				unk120;					// 120
	UInt32				unk124;					// 124
	MovementHandler*	movementHandler;		// 128
	LookHandler*		lookHandler;			// 12C
	SprintHandler*		sprintHandler;			// 130
	ReadyWeaponHandler*	readyWeaponHandler;		// 134
	AutoMoveHandler*	autoMoveHandler;		// 138
	ToggleRunHandler*	toggleRunHandler;		// 13C
	ActivateHandler*	activateHandler;		// 140
	JumpHandler*		jumpHandler;			// 144
	ShoutHandler*		shoutHandler;			// 148
	AttackBlockHandler*	attackBlockHandler;		// 14C
	RunHandler*			runHandler;				// 150
	SneakHandler*		sneakHandler;			// 154
	TogglePOVHandler*	togglePOVHandler;		// 158
	UInt8				unk15C;					// 15C
	UInt8				pad15C[3];
};
assert(sizeof(PlayerControls) == 0x160);

class BSInputDevice {
public:
	virtual UInt32	Initialize();
	virtual	void	GetInput(float unk1);
	virtual	void	Unk_03();
	virtual bool	IsEnabled();
	virtual			~BSInputDevice();
	virtual void	Unk_06();
	
	enum {
		kDeviceType_Keyboard = 0,
		kDeviceType_Mouse,
		kDeviceType_Gamepad
	};

	UInt32			DeviceType;						// 04
	UInt32			unk008;							// 08
	UInt32			unk00C;							// 0C	
};
assert(sizeof(BSInputDevice) == 0x10);

class BSWin32KeyboardDevice : public BSInputDevice {
public:
	UInt32			unk010;							// 10
	UInt32			unk014;							// 14
	UInt32			unk018;							// 18
	UInt32			unk01C;							// 1C
	UInt32			unk020;							// 20
	UInt32			unk024;							// 24
	UInt32			unk028[(0x0F4 - 0x028) >> 2];	// 28 This (or part of this) is a class/struct
	UInt8			PreviousKeyState[0x100];		// F4
	UInt8			CurrentKeyState[0x100];			// 1F4
};
assert(sizeof(BSWin32KeyboardDevice) == 0x2F4);

class BSWin32MouseDevice : public BSInputDevice {
public:
	UInt32			unk010;							// 10
	UInt32			unk014;							// 14
	UInt32			unk018;							// 18
	UInt32			unk01C;							// 1C
	UInt32			unk020;							// 20
	UInt32			unk024;							// 24
	UInt32			unk028;							// 28
	UInt32			unk02C;							// 2C
	DIMOUSESTATE2	PreviousMouseState;				// 30
	DIMOUSESTATE2	CurrentMouseState;				// 44
	UInt32			unk058;							// 58
};
assert(sizeof(BSWin32MouseDevice) == 0x5C);

class BSWin32GamepadDevice : public BSInputDevice {};
assert(sizeof(BSWin32MouseDevice) == 0x5C);

class InputEventDispatcher : public EventDispatcher<InputEvent> {
public:
	UInt32					unk030;		// 030
	BSWin32KeyboardDevice*	keyboard;	// 034
	BSWin32MouseDevice*		mouse;		// 038
	BSWin32GamepadDevice*	gamepad;	// 03C
};
assert(sizeof(InputEventDispatcher) == 0x040);

class SkyObject {
public:
	virtual ~SkyObject();
	virtual void Unk_01();
	virtual void Unk_02();
	virtual void Unk_03();

	NiNode* RootNode;		// 04
};
assert(sizeof(SkyObject) == 0x08);

class Atmosphere : public SkyObject {
public:
	virtual void Unk_04();

	UInt32	unk08;	// 08
	UInt32	unk0C;	// 0C
	UInt32	unk10;	// 10
	UInt32	unk14;	// 14
	UInt32	unk18;	// 18
};
assert(sizeof(Atmosphere) == 0x1C);

class Stars : public SkyObject {
public:
	UInt32	unk08;	// 08
	UInt32	unk0C;	// 0C
};
assert(sizeof(Stars) == 0x10);

class Sun : public SkyObject {
public:
	NiAVObject*	SunBillboard;	// 08
	UInt32		unk0C;	// 0C
	UInt32		unk10;	// 10
	UInt32		unk14;	// 14
	UInt32		unk18;	// 18
	UInt32		unk1C;	// 1C
	UInt32		unk20;	// 20
	UInt32		unk24;	// 24
	UInt8		unk28;	// 28
	UInt8		pad29[3];	// 29
	UInt32		unk2C;	// 2C - BSShaderAccumulator
};
assert(sizeof(Sun) == 0x30);

class Clouds : public SkyObject {
public:
	UInt32	unk08[(0x38C - 0x08) >> 2];		// 08
};
assert(sizeof(Clouds) == 0x38C);

class Moon : public SkyObject {
public:
	UInt32	unk08;		// 08 - NiNode?
	UInt32	unk0C;		// 0C - NiNode?
	UInt32	unk10;		// 10 - NiNode?
	UInt32	unk14;		// 14 - NiNode?
	char*	unk18;		// 18 - Data/Textures/Sky/%s_full.dds
	UInt32	unk1C;		// 1C
	char*	unk20;		// 20 - Data/Textures/Sky/%s_three_wan.dds
	UInt32	unk24;		// 24
	char*	unk28;		// 28 - Data/Textures/Sky/%s_half_wan.dds
	UInt32	unk2C;		// 3C
	char*	unk30;		// 30 - Data/Textures/Sky/%s_one_wan.dds
	UInt32	unk34;		// 34
	UInt32	unk38;		// 38
	UInt32	unk3C;		// 3C
	char*	unk40;		// 40 - Data/Textures/Sky/%s_one_wax.dds
	UInt32	unk44;		// 44
	char*	unk48;		// 48 - Data/Textures/Sky/%s_half_wax.dds
	UInt32	unk4C;		// 4C
	char*	unk50;		// 50 - Data/Textures/Sky/%s_three_wax.dds
	UInt32	unk54;		// 54
	UInt32	unk58;		// 58
	UInt32	unk5C[(0x7C - 0x5C) >> 2];
};
assert(sizeof(Moon) == 0x7C);

class Precipitation : public SkyObject {
public:
	UInt32	unk08;	// 08
	float	unk0C;	// 0C
	float	unk10;	// 10
	float	unk14;	// 14
	float	unk18;	// 18
};
assert(sizeof(Precipitation) == 0x1C);

class Sky {
public:
	void ForceWeather(TESWeather* Weather) { ThisCall(0x006A3FB0, this, Weather, 0); }

	void**			_vtbl;				// 000
	void*			unk04;				// 04 - BSMultiBoundNode
	NiNode*			unk08;				// 08
	UInt32			unk0C;				// 0C
	UInt32			unk10;				// 10
	UInt32			unk14;				// 14
	UInt32			unk18;				// 18
	UInt32			unk1C;				// 1C
	UInt32			unk20;				// 20
	UInt32			unk24;				// 24
	TESClimate*		firstClimate;		// 28
	TESWeather*		firstWeather;		// 2C
	TESWeather*		secondWeather;		// 30
	UInt32			unk34;				// 34
	UInt32			unk38;				// 38
	TESRegion*		region;				// 3C
	Atmosphere*		atmosphere;			// 40
	Stars*			stars;				// 44
	Sun*			sun;				// 48
	Clouds*			clouds;				// 4C
	Moon*			masser;				// 50
	Moon*			secunda;			// 54
	Precipitation*	precipitation;		// 58
	float			unk5C[6];			// 5C
	UInt32			unk74[3];			// 74
	float			unk80[6];			// 80
	UInt32			unk98[6];			// 98
	float			unkB0[9];			// B0
	UInt32			unkD4[6];			// D4
	float			unkEC[9];			// EC
	UInt32			unk110[9];			// 110
	float			unk134;				// 134
	float			unk138;				// 138
	float			unk13C;				// 13C
	float			windSpeed;			// 140
	float			unk144;				// 144
	float			unk148;				// 148
	float			unk14C;				// 14C
	UInt32			unk150[3];			// 150
	float			unk15C;				// 15C
	float			unk160;				// 160
	float			unk164;				// 164
	float			unk168;				// 168
	float			weatherPercent;		// 16C
	UInt32			unk170;				// 170
	void*			unk174;				// 174
	UInt32			unk178[3];			// 178
	float			unk184;				// 184
	UInt32			unk188[6];			// 188
	float			unk1A0[(0x210 - 0x1A0) >> 2];	// 1A0
	void*			skyEffectController;			// 210
	UInt32			unk214[(0x238 - 0x214) >> 2];	// 214
};
assert(sizeof(Sky) == 0x238);

class GridArray {
public:
	virtual ~GridArray();
	virtual void Fn_01();
	virtual void Fn_02();
	virtual void Fn_03();
	virtual void Fn_04();
	virtual void Fn_05();
	virtual void Fn_06();
	virtual void Fn_07();
	virtual void Fn_08();
	virtual void Fn_09();
};
assert(sizeof(GridArray) == 0x04);

class GridCellArray : public GridArray {
public:
	UInt32			worldX;		// 04 worldspace x coordinate of cell at center of grid (player's cell)
	UInt32			worldY;		// 08 worldspace y
	UInt32			size;		// 0C grid is size^2, size = uGridsToLoad
	TESObjectCELL*	grid;		// 10 this is a pointer to a cell array dynamically alloc'ed [size^2]
	float			posX;		// 14 4096*worldX (exterior cells are 4096 square units)
	float			posY;		// 18 4096*worldY
	float			unk1C;		// 1C
	UInt8			unk20;		// 20
	UInt8			pad20[3];
};
assert(sizeof(GridCellArray) == 0x24);

class TES {
public:
	virtual ~TES();

	void				PurgeCells() {}
	float				GetWaterHeight(TESObjectREFR* Ref) { return ThisCallF(0x004D62D0, Ref); }

	UInt32				unk04;
	UInt32				unk08;
	UInt32				unk0C;
	UInt32				unk10;
	UInt32				unk14;
	UInt32				unk18;
	UInt32				unk1C;
	UInt32				unk20;
	UInt32				unk24;
	UInt32				unk28;
	UInt32				unk2C;
	UInt32				unk30;
	UInt32				unk34;
	UInt32				unk38;
	UInt32				unk3C;
	GridCellArray*		gridCellArray;		// 40
	NiNode*				objectLODRoot;		// 44
	NiNode*				landLOD;			// 48
	NiNode*				waterLOD;			// 4C
	BSTempNodeManager*	tempNodeManager;	// 50
	UInt32				unk54;
	UInt32				unk58;
	UInt32				unk5C;			// 7FFFFFFF
	UInt32				unk60;			// 7FFFFFFF
	UInt32				unk64;			// 7FFFFFFF
	UInt32				unk68;			// 7FFFFFFF
	TESObjectCELL*		currentCell;		// 6C
	TESObjectCELL**		interiorCellBuffer; // 70
	UInt32				unk74;
	UInt32				unk78;			// 0
	UInt32				unk7C;			// 0
	UInt32				unk80;			// 7FFFFFFF
	UInt32				unk84;			// 7FFFFFFF
	UInt32				unk88;
	UInt32				unk8C;
	UInt32				unk90;
	Sky*				sky;
	UInt32				imageSpaceModifier; // ImageSpaceModifierInstanceForm
	UInt32				unk9C;				// ImageSpaceModifierInstanceDOF ** ??
	UInt32				unkA0;
	UInt32				unkA4;
	UInt8				unkA8;
	UInt8				unkA9;
	UInt8				unkAA;
	UInt8				unkAB;
	UInt8				unkAC;
	UInt8				unkAD;
	UInt8				unkAE;
	UInt8				unkAF;
	UInt8				unkB0;
	UInt8				padB1[3];
	UInt32				unkB4;				// 4579A000
	UInt32				unkB8;				// 457D2000
	TESWorldSpace*		worldSpace;			// BC
	UInt32				npcs;				// TESNPC ** ??
	UInt32				unkC4;				// TESNPC next?
	UInt32				queuedFile;			// QueuedFile
	NiSourceTexture*	someTexture;
	UInt32				queuedFile1;		// QueuedFile
	UInt32				queuedFile2;
	UInt32				unkD8;				// BSFadeNode ** ??
	UInt32				unkDC;
	UInt32				navMeshInfoMap;		// NavMeshInfoMap
	void*				loadedAreaBound;	// E4 LoadedAreaBound*
};
assert(sizeof(TES) == 0xE8);

class Menu { // Wrapper class for compatibility with OR/NVR
public:
	enum MenuType {
		kMenuType_None = 0,			// for gamemode
		kMenuType_BigFour,			// F1 - F4 menus
		kMenuType_Any,
		kMenuType_Console,
		kMenuType_Main,

		kMenuType_Message = 0x3E9,
		kMenuType_Dialog = 0x3F1,
		kMenuType_Persuasion = 0x40A,
	};
};
assert(sizeof(Menu) == 0x01);

class IFormFactory {
public:
	virtual ~IFormFactory();
	virtual TESForm*	Create();
	virtual const char* GetName();
	virtual UInt32		GetTypeID();
	virtual const char* Unk_04();	// return NULL
	virtual UInt32		Unk_05();	// return 0x67
	virtual UInt32		Unk_06();	// return 9

	static IFormFactory* GetFactory(UInt8 FormType) { IFormFactory** FormFactory = (IFormFactory**)0x012E57B0; return FormFactory[FormType]; }
};

class ModList {
public:
	TList<ModInfo>	modInfoList;		// 00
	UInt32			loadedModCount;		// 08
	ModInfo*		loadedMods[0xFF];	// 0C
};
assert(sizeof(ModList) == 0x408);

class MasterDataHandler {
public:

	TESForm*							CreateForm(UInt8 FormType) { return IFormFactory::GetFactory(FormType)->Create(); }
	bool								AddData(TESForm* Form) { return true; }
	void								FillNames(std::vector<std::string>* List, UInt32 FormType) {
											List->clear();
											if (FormType == TESForm::FormType::kFormType_Weather) {
												for (UInt32 i = 0; i < weathers.count; i++) {
													TESWeatherEx* Weather = (TESWeatherEx*)weathers.data[i];
													List->push_back(Weather->EditorName);
												}
											}
										}

	UInt32								unk000;
	UInt32								unk004;
	TArray<void*>						unk008;
	TArray<void*>						unk014;
	TArray<void*>						unk020;
	TArray<void*>						unk02C;
	TArray<BGSKeyword*>					keywords;
	TArray<BGSLocationRefType*>			locRefTypes;
	TArray<BGSAction*>					actions;
	TArray<BGSTextureSet*>				textureSets;
	TArray<BGSMenuIcon*>				menuIcons;
	TArray<TESGlobal*>					globals;
	TArray<TESClass*>					classes;
	TArray<TESFaction*>					factions;
	TArray<BGSHeadPart*>				headParts;
	TArray<TESEyes*>					eyes;
	TArray<TESRace*>					races;
	TArray<TESSound*>					sounds;
	TArray<BGSAcousticSpace*>			acousticSpaces;
	TArray<void*>						unkSkills;
	TArray<EffectSetting*>				magicEffects;
	TArray<Script*>						scripts;
	TArray<TESLandTexture*>				landTextures;
	TArray<EnchantmentItem*>			enchantments;
	TArray<SpellItem*>					spellItems;
	TArray<ScrollItem*>					scrolls;
	TArray<TESObjectACTI*>				activators;
	TArray<BGSTalkingActivator*>		talkingActivators;
	TArray<TESObjectARMO*>				armors;
	TArray<TESObjectBOOK*>				books;
	TArray<TESObjectCONT*>				containers;
	TArray<TESObjectDOOR*>				doors;
	TArray<IngredientItem*>				ingredients;
	TArray<TESObjectLIGH*>				lights;
	TArray<TESObjectMISC*>				miscObjects;
	TArray<BGSApparatus*>				apparatuses;
	TArray<TESObjectSTAT*>				statics;
	TArray<BGSStaticCollection*>		staticCollections;
	TArray<BGSMovableStatic*>			movableStatics;
	TArray<TESGrass*>					grasses;
	TArray<TESObjectTREE*>				trees;
	TArray<TESFlora*>					flora;
	TArray<TESFurniture*>				furniture;
	TArray<TESObjectWEAP*>				weapons;
	TArray<TESAmmo*>					ammo;
	TArray<TESNPC*>						npcs;
	TArray<TESLevCharacter*>			levCharacters;
	TArray<TESKey*>						keys;
	TArray<AlchemyItem*>				potions;
	TArray<BGSIdleMarker*>				idleMarkers;
	TArray<BGSNote*>					notes;
	TArray<BGSConstructibleObject*>		constructibles;
	TArray<BGSProjectile*>				projectiles;
	TArray<BGSHazard*>					bgsHazards;
	TArray<TESSoulGem*>					soulGems;
	TArray<TESLevItem*>					levItems;
	TArray<TESWeather*>					weathers;
	TArray<TESClimate*>					climates;
	TArray<BGSShaderParticleGeometryData*>	shaderParticleGeometryData;
	TArray<BGSReferenceEffect*>			referenceEffects;
	TArray<TESRegion*>					regions;
	TArray<NavMeshInfoMap*>				navMeshInfoMaps;
	TArray<TESObjectCELL*>				cells;
	TArray<TESObjectREFR*>				refs;	// could be actors
	TArray<Character*>					characters;
	TArray<MissileProjectile*>			missleProjs;
	TArray<ArrowProjectile*>			arrowProjs;
	TArray<GrenadeProjectile*>			grenadeProjs;
	TArray<BeamProjectile*>				beamProjs;
	TArray<FlameProjectile*>			flameProjs;
	TArray<ConeProjectile*>				coneProjs;
	TArray<BarrierProjectile*>			barrierProjs;
	TArray<Hazard*>						hazards;
	TArray<TESWorldSpace*>				worldSpaces;
	TArray<TESObjectLAND*>				lands;
	TArray<NavMesh*>					navMeshes;
	TArray<void*>						unkTLOD;
	TArray<TESTopic*>					topics;
	TArray<TESTopicInfo*>				topicInfos;
	TArray<TESQuest*>					quests;
	TArray<TESIdleForm*>				idleForms;
	TArray<TESPackage*>					packages;
	TArray<TESCombatStyle*>				combatStyles;
	TArray<TESLoadScreen*>				loadScreens;
	TArray<TESLevSpell*>				levSpells;
	TArray<TESObjectANIO*>				anios;
	TArray<TESWaterForm*>				waterForms;
	TArray<TESEffectShader*>			effectShaders;
	TArray<void*>						unkTOFTs;
	TArray<BGSExplosion*>				explosions;
	TArray<BGSDebris*>					debris;
	TArray<TESImageSpace*>				imageSpaces;
	TArray<TESImageSpaceModifier*>		imageSpaceModifiers;
	TArray<BGSListForm*>				listForms;
	TArray<BGSPerk*>					perks;
	TArray<BGSBodyPartData*>			bodyPartData;
	TArray<BGSAddonNode*>				addonNodes;
	TArray<ActorValueInfo*>				actorValueInfos;
	TArray<BGSCameraShot*>				cameraShots;
	TArray<BGSCameraPath*>				cameraPaths;
	TArray<BGSVoiceType*>				voiceTypes;
	TArray<BGSMaterialType*>			materialTypes;
	TArray<BGSImpactData*>				impactData;
	TArray<BGSImpactDataSet*>			impactDataSets;
	TArray<TESObjectARMA*>				armorAddons;
	TArray<BGSEncounterZone*>			encounterZones;
	TArray<BGSLocation*>				locations;
	TArray<BGSMessage*>					messages;
	TArray<BGSRagdoll*>					ragdolls;
	TArray<void*>						unkDOBJs;
	TArray<BGSLightingTemplate*>		lightingTemplates;
	TArray<BGSMusicType*>				musicTypes;
	TArray<BGSFootstep*>				footsteps;
	TArray<BGSFootstepSet*>				footstepSets;
	TArray<BGSStoryManagerBranchNode*>	branchNodes;
	TArray<BGSStoryManagerQuestNode*>	questNodes;
	TArray<BGSStoryManagerEventNode*>	eventNodes;
	TArray<BGSDialogueBranch*>			dialogBranches;
	TArray<BGSMusicTrackFormWrapper*>	musicTrackFormWrappers;
	TArray<void*>						unkDLVWs;
	TArray<TESWordOfPower*>				wordOfPowers;
	TArray<TESShout*>					shouts;
	TArray<BGSEquipSlot*>				equipSlots;
	TArray<BGSRelationship*>			relationships;
	TArray<BGSScene*>					scenes;
	TArray<BGSAssociationType*>			associationTypes;
	TArray<BGSOutfit*>					outfits;
	TArray<BGSArtObject*>				artObjects;
	TArray<BGSMaterialObject*>			materialObjects;
	TArray<BGSMovementType*>			movementTypes;
	TArray<BGSSoundDescriptorForm*>		soundDescriptors;
	TArray<BGSDualCastData*>			dualCastData;
	TArray<BGSSoundCategory*>			soundCategories;
	TArray<BGSSoundOutput*>				soundOutputs;
	TArray<BGSCollisionLayer*>			collisonLayers;
	TArray<BGSColorForm*>				colors;
	TArray<BGSReverbParameters*>		reverbParams;
	UInt32								unks[0x0E];			// 03 Cell** 06 TESGlobal**		// 65C
	ModList								modList;			// 694
	UInt32								moreunks[100];		// A9C
};
assert(sizeof(MasterDataHandler) == 0xC2C);

class SoundControl {
public:
	void		Play(TESSound* Sound) {}
};
assert(sizeof(SoundControl) == 0x01);

class Main {
public:
	BSWin32KeyboardDevice*	GetInputKeyboard() { return (*(InputEventDispatcher**)0x01B2E724)->keyboard; }
	BSWin32MouseDevice*		GetInputMouse() { return (*(InputEventDispatcher**)0x01B2E724)->mouse; }
	SoundControl*			GetSound() { return NULL; }
	void					PurgeModels() {}

	UInt32			unk00;				// 00
	UInt32			unk04;				// 04
	UInt32			unk08;				// 08
	HWND			window;				// 0C
	HINSTANCE		procInstance;		// 10
	UInt32			mainThreadID;		// 14
	UInt32			mainThreadHandle;	// 18
	UInt32			unk1C;				// 1C
	UInt32			unk20;				// 20
	UInt32			unk24;				// 24
	UInt32			unk28[24];			// 28
	UInt32			unk88;				// 88
	UInt32			unk8C;				// 8C
	UInt32			unk90;				// 90
	UInt32			unk94;				// 94
	UInt32			unk98;				// 98
	UInt32			unk9C;				// 9C
	void*			accumulator0;		// A0 BSShaderAccumulator*
	void*			accumulator1;		// A4 BSShaderAccumulator*
	void*			accumulator2;		// A8 BSShaderAccumulator*
	void*			accumulator3;		// AC BSShaderAccumulator*
	void*			accumulator4;		// B0 BSShaderAccumulator*
	void*			accumulator5;		// B4 BSShaderAccumulator*
	void*			accumulator6;		// B8 BSShaderAccumulator*
	void*			accumulator7;		// BC BSShaderAccumulator*
	UInt32			unkC0;				// C0
	NiCamera*		camera;				// C4
	UInt32			unkC8;				// C8
	UInt32			unkCC;				// CC
	UInt32			unkD0;				// D0
	UInt32			unkD4;				// D4
	UInt32			unkD8;				// D8
	UInt32			unkDC;				// DC
	UInt32			unkE0;				// E0
	UInt32			unkE4;				// E4
	UInt32			unkE8;				// E8
	void*			cullingProcess0;	// EC BSGeometryListCullingProcess*
	void*			cullingProcess1;	// F0 BSGeometryListCullingProcess*
	void*			cullingProcess2;	// F4 BSGeometryListCullingProcess*
	UInt32			unkF8[12];			// F8
};
assert(sizeof(Main) == 0x128);

class MenuInterfaceManager {
public:
	bool IsActive(UInt32 MenuType) {
		if (MenuType == Menu::MenuType::kMenuType_None) return !(*(UInt8*)0x01B2E85F + *(UInt8*)0x01B2E85E);
		if (MenuType == Menu::MenuType::kMenuType_Console) return (bool)ThisCall(0x00A5CE90, this, &UIStringHolder::Get()->console);
		if (MenuType == Menu::MenuType::kMenuType_Main) return (bool)ThisCall(0x00A5CE90, this, &UIStringHolder::Get()->mainMenu);
		if (MenuType == Menu::MenuType::kMenuType_Dialog) return (bool)ThisCall(0x00A5CE90, this, &UIStringHolder::Get()->dialogueMenu);
		return false;
	};
	bool					ShowMessageBox(const char* Message, void* Callback, const char* Button0, const char* Button1 = NULL, const char* Button2 = NULL, const char* Button3 = NULL, const char* Button4 = NULL, const char* Button5 = NULL, const char* Button6 = NULL, const char* Button7 = NULL, const char* Button8 = NULL, const char* Button9 = NULL) { bool (__cdecl* ShowUIMessageBox)(const char*, void*, UInt32, UInt32, UInt32, ...) = (bool (__cdecl*)(const char*, void*, UInt32, UInt32, UInt32, ...))0x0087AC60; return ShowUIMessageBox(Message, Callback, 1, 25, 4, Button0, Button1, Button2, Button3, Button4, Button5, Button6, Button7, Button8, Button9, NULL); }
	void					ShowMessage(const char* Message) { void (__cdecl* ShowUIMessage)(const char*, const char*, bool) = (void (__cdecl*)(const char*, const char*, bool))0x008997A0; ShowUIMessage(Message, NULL, true); }
	UInt8					GetMessageBoxButton() { return -1; }
	void					SetCrosshair(bool Enabled) { }

	struct UnkData {
		UInt32		freqLow;	// 000 (= Frequency.LowPart)
		UInt32		freqHigh;	// 004 (= Frequency.HighPart)
		UInt32		unk_008;	// 008 (= 0)
		UInt32		unk_00C;	// 00C (= 0)
		UInt32		unk_010;	// 010 (= 0)
		UInt32		unk_014;	// 014 (= 0)
		UInt32		unk_018;	// 018 (= 0)
		UInt32		unk_01C;	// 018 (= frequency related)
		UInt32		unk_020;	// 020
		UInt32		unk_024;	// 024
		UInt32		unk_028;	// 028 (= 0)
		UInt32		unk_02C;	// 02C (= 0)
	};

	UInt32					unk_000;	// 000
	EventDispatcher<void*>	menuOpenCloseEventDispatcher;	// 004 EventDispatcher<MenuOpenCloseEvent>
	EventDispatcher<void*>	menuModeChangeEventDispatcher;	// 034 EventDispatcher<MenuModeChangeEvent>
	EventDispatcher<void*>	unk_064;						// 064 - New in 1.6.87.0 - Kinect related?
	TArray<UInt32>			menuStack;						// 094
	UInt32					unk_0A0;						// 0A0
	UInt32					menuTable[7];					// 0A4 typedef tHashSet<MenuTableItem, BSFixedString> MenuTable;
	UInt32					unk_0C0;						// 0C0 (= 0)
	UInt32					unk_0C4;						// 0C4 (= 0)
	UInt32					isActiveMenu;					// 0C8 (= 0)
	UInt32					unk_0CC;						// 0CC (= 0)
	UInt32					unk_0D0;						// 0D0 (= 0)
	UInt32					unk_0D4;						// 0D4 (= 0)
	UInt32					unk_0D8;						// 0D8 (= 0)
	UInt32					unk_0DC;						// 0DC (= 0)
	UInt32					unk_0E0;						// 0E0 (= 0)
	UInt32					unk_0E4;						// 0E4
	UnkData					unk_0E8;						// 0E8
	bool					unk_118;						// 118 (= 0)
	bool					unk_119;						// 119 (= 0)
	char					pad[2];
};
assert(sizeof(MenuInterfaceManager) == 0x11C);

class TimeGlobals {
public:
	UInt32		unk00;			// 00 virtual table?
	TESGlobal*	GameYear;		// 04
	TESGlobal*	GameMonth;		// 08
	TESGlobal*	GameDay;		// 0C
	TESGlobal*	GameHour;		// 10
	TESGlobal*	GameDaysPassed;	// 14
	TESGlobal*	TimeScale;		// 18

	static float GetGameTime() { TimeGlobals* Globals = (TimeGlobals*)0x012E5690; return Globals->GameHour->data * 60.0f * 60.0f; }
};
assert(sizeof(TimeGlobals) == 0x1C); // Static class, size could be larger

class QueuedModelLoader {
public:
	UInt32	Unk000[32]; // LockFreeMaps and other
};
assert(sizeof(QueuedModelLoader) == 0x80);

class GameSetting {
public:
	void*		vftbl;
	union {
		char*	pValue;
		int		iValue;
		float	fValue;
	};
	char*		Name;
};
assert(sizeof(GameSetting) == 0x0C);

class VMValue {
public:
	enum {
		kType_None =		0,
		kType_Identifier =	1,
		kType_String =		2,
		kType_Int =			3,
		kType_Float =		4,
		kType_Bool =		5,

		kType_Unk0B =		0x0B,
		kType_ArraysStart = 11,
		kType_StringArray =	12,
		kType_IntArray =	13,
		kType_FloatArray =	14,
		kType_BoolArray =	15,
		kType_ArraysEnd =   16,
	};

	struct ArrayData {
		volatile SInt32	refCount;	// 00
		UInt32			unk04;		// 04
		UInt32			len;		// 08
		UInt32			unk0C;		// 0C
		UInt32			unk10;		// 10
	};

	UInt32	type;	// 00
	union {
		SInt32			i;
		UInt32			u;
		float			f;
		bool			b;
		void*			p;
		ArrayData*		a;
		VMIdentifier*	id;
		BSFixedString	s;
	} data;			// 04
};
assert(sizeof(VMValue) == 0x08);

class VMArgList {
public:
	UInt32		GetOffset(VMState* state) { return ThisCall(0x00C3A620, this, state); }
	VMValue*	Get(VMState* state, UInt32 idx, UInt32 offset) { return (VMValue*)ThisCall(0x00C3AC40, this, state, idx, offset); }
};

class VMState {
public:
	VMArgList*	argList;	// 00
	UInt32		unk04;		// 04
	UInt32		unk08;		// 08
	UInt32		unk0C;		// 0C
	UInt32		unk10;		// 10
	UInt32		unk14;		// 14
	UInt32		unk18;		// 18
	UInt32		numArgs;	// 1C
};
assert(sizeof(VMState) == 0x20);

class VMUnlinkedClassList {
public:
	virtual ~VMUnlinkedClassList();
	virtual VMUnlinkedClassList*	Create();
	virtual void					SetUnk0C(void * arg);
	virtual bool					Link(BSFixedString* className);

	void*				unk04;		// 04 VMClassRegistry*
	void*				unk08;		// 08
	void*				unk0C;		// 0C - loader
	UInt8				unk10;		// 10
	UInt8				pad11[3];	// 11
	UInt32				unk14;		// 14
	UInt32				unk18;		// 18
	UInt32				unk1C;		// 1C
	void*				unk20;		// 20
	UInt32				unk24;		// 24
	UInt32				unk28;		// 28
	UInt32				unk2C;		// 2C
	void*				unk30;		// 30
	UInt32				unk34;		// 34
	UInt32				unk38;		// 38
	UInt32				unk3C;		// 3C
	void*				unk40;		// 40
	UInt32				unk44;		// 44
};
assert(sizeof(VMUnlinkedClassList) == 0x48);

class VMClassRegistry {
public:
	virtual ~VMClassRegistry();
	virtual void	Unk_01();
	virtual void	PrintToDebugLog(const char* text, UInt32 stackId, UInt32 logLevel);
	virtual void	Unk_03();
	virtual void	Unk_04();
	virtual void	Unk_05();
	virtual void	Unk_06();
	virtual void	Unk_07();
	virtual void	RegisterForm(UInt32 typeID, const char* papyrusClassName);
	virtual void	Unk_09();
	virtual bool	GetFormTypeClass(UInt32 formType, VMClassInfo** outClass);
	virtual void	Unk_0B();
	virtual void	Unk_0C();
	virtual bool	Unk_0D(BSFixedString* className, UInt32* unk);
	virtual void	Unk_0E();
	virtual void	Unk_0F();
	virtual void	Unk_10();
	virtual void	Unk_11();
	virtual void	Unk_NewIn16_11();	// ### added in 1.6.86, further indices are off by one
	virtual void	Unk_12();
	virtual bool	Unk_13(BSFixedString* className, VMIdentifier** identifier);
	virtual bool	CreateArray(VMValue* value, UInt32 size, void** unk1); // CreateArray(VMValue* value, UInt32 size, VMValue::ArrayData** unk1);
	virtual void	Unk_15();
	virtual void	RegisterFunction(NativeFunction* fn);
	virtual void	SetFunctionFlagsEx(const char* className, UInt32 unk0, const char* fnName, UInt32 flags);
	virtual void	SetFunctionFlags(const char* className, const char* fnName, UInt32 flags);
	virtual void	VisitScripts(UInt64 handle, void* functor); // VisitScripts(UInt64 handle, IForEachScriptObjectFunctor* functor);
	virtual bool	Unk_1A(UInt64 handle, const char * className, VMIdentifier** identifier);
	virtual void	Unk_1B();
	virtual void	Unk_1C();
	virtual void	Unk_1D();
	virtual void	Unk_1E();
	virtual void	Unk_1F();
	virtual void	Unk_20();
	virtual bool	ExtractValue(UInt64 handle, BSFixedString* className, SInt32 variableIndex, VMValue* out);	// unk probably script context object?
	virtual void	QueueEvent(UInt64 handle, BSFixedString* eventName, void* args); //QueueEvent(UInt64 handle, BSFixedString* eventName, NativeFunctionArguments* args);
	virtual void	Unk_23();
	virtual void	Unk_24();
	virtual void	Unk_25();
	virtual void	Unk_26();
	virtual void	Unk_27();
	virtual void	Unk_28();
	virtual void	ResumeStack(UInt32 stackId, VMValue* result);
	virtual void	Unk_2A();
	virtual void*	GetHandlePolicy();
	virtual void	Unk_2C();
	virtual void*	GetObjectBindPolicy();
	virtual void	Unk_2E();
	virtual void	Unk_2F();
	virtual void	Unk_30();
	virtual void	Unk_31();
	virtual void	Unk_32();
	virtual void	Unk_33();

	UInt32				unk0004;			// 0004 - refcount?
	void**				vtbl0008;			// 0008
	void**				vtbl000C;			// 000C
	void**				vtbl0010;			// 0010
	UInt32				unk0014[22];		// 0014
	VMUnlinkedClassList	unlinkedClassList;	// 006C
	UInt32				unk00B4[4673];		// 00B4
	SimpleLock			stackLock;			// 49B8
	UInt32				unk49C0;			// 49C0
	UInt32				allStacks[7];		// 49C4 typedef tHashSet<VMStackTableItem,UInt32> StackTableT;
	UInt32				unk49E0;			// 49E0
	UInt32				waitingStacks[7];	// 49E4 typedef tHashSet<VMStackTableItem,UInt32> StackTableT;
	UInt32				unk4A00[65];		// 4A00
};
assert(sizeof(VMClassRegistry) == 0x4B04);

class NativeFunction {
public:
	NativeFunction(const char* functionName, const char* className, UInt32 numParams) { ThisCall(0x00C46C00, this, functionName, className, true, numParams); m_isLatent = true;  }
	virtual ~NativeFunction() { ThisCall(0x00C46AD0, this); }
	virtual BSFixedString*	GetFunctionName() { return &m_fnName; }
	virtual BSFixedString*	GetFunctionClassName() { return &m_className; }
	virtual BSFixedString*	GetStr10() { return &unk10; }
	virtual UInt32*			GetReturnType(UInt32* dst) { *dst = m_retnType; return dst; }
	virtual UInt32			GetNumParams() { return m_params.unk06; }
	virtual UInt32*			GetParam(UInt32 idx, BSFixedString* nameOut, UInt32* typeOut) { return (UInt32*)ThisCall(0x00C46F50, this, idx, nameOut, typeOut); }
	virtual UInt32			GetNumParams2() { return m_params.unk06; }
	virtual bool			IsNative() { return true; }
	virtual UInt8			GetUnk20() { return unk20; }
	virtual bool			Unk_0A() { return false; }
	virtual UInt32			Unk_0B() { return 0; }
	virtual UInt32			GetUnk24() { return unk24; }
	virtual BSFixedString*	GetStr28() { return &unk28; }
	virtual void			Unk_0E(UInt32 unk) { }
	virtual UInt32			Invoke(UInt32 unk0, UInt32 unk1, VMClassRegistry* registry, UInt32 unk3) { return ThisCall(0x00C46CB0, this, unk0, unk1, registry, unk3); }
	virtual BSFixedString*	Unk_10() { return (BSFixedString*)ThisCall(0x00C46B10, this); }
	virtual bool			Unk_11(UInt32 unk0, UInt32* unk1) { *unk1 = 0; return false; }
	virtual bool			Unk_12(UInt32 idx, UInt32 out) { return (bool)ThisCall(0x00C46F60, this, idx, out); }
	virtual UInt8			GetUnk21() { return unk21; }
	virtual void			SetUnk21(UInt8 arg) { unk21 = arg; }
	virtual bool			HasCallback() { return m_callback != NULL; }
	virtual bool			Run(VMValue* baseValue, VMClassRegistry* registry, UInt32 arg2, VMValue* resultValue, VMState* state) = 0;

	struct ParameterInfo {
		class Entry {
		public:
			BSFixedString	name;			// 00
			union {
				UInt32			type;		// 04 - shared with VMValue::type
				VMClassInfo*	typePtr;	// 04
			};
		};
		Entry*	data;		// 00 length = numParams + unk06
		UInt16	numParams;	// 04
		UInt16	unk06;		// 06
	};
	template <typename T> UInt32 GetVMTypeID();
	template <> UInt32 GetVMTypeID <void>() { return VMValue::kType_None; }
	template <> UInt32 GetVMTypeID <int>() { return VMValue::kType_Int; }
	template <> UInt32 GetVMTypeID <float>() { return VMValue::kType_Float; }
	template <> UInt32 GetVMTypeID <bool>() { return VMValue::kType_Bool; }
	template <> UInt32 GetVMTypeID <BSFixedString>() { return VMValue::kType_String; }

	template <typename T> void UnpackValue(T* dst, VMValue* src);
	template <> void UnpackValue <int>(int* dst, VMValue* src) { *dst = src->data.i; }
	template <> void UnpackValue <float>(float* dst, VMValue* src) { *dst = src->data.f; }
	template <> void UnpackValue <bool>(bool* dst, VMValue* src) { *dst = src->data.b; }
	template <> void UnpackValue <BSFixedString>(BSFixedString* dst, VMValue* src) { *dst = src->data.s; }

	BSIntrusiveRefCounted	refCount;		// 04
	BSFixedString			m_fnName;		// 08
	BSFixedString			m_className;	// 0C
	BSFixedString			unk10;			// 10
	UInt32					m_retnType;		// 14 - return type
	ParameterInfo			m_params;		// 18
	UInt8					unk20;			// 20 - related to extra entries in m_params
	UInt8					unk21;			// 21
	UInt8					m_isLatent;		// 22
	UInt8					pad23;			// 23
	UInt32					unk24;			// 24
	BSFixedString			unk28;			// 28
	void*					m_callback;		// 2C
};
assert(sizeof(NativeFunction) == 0x30);

template <typename T1, typename T2, typename T3, typename T4, typename T5>
class PapyrusFunction5 : public NativeFunction {
public:
	typedef bool (*CallbackType)(void* Base, T1 Arg1, T2 Arg2, T3 Arg3, T4 Arg4, T5 Arg5);

	PapyrusFunction5(const char* functionName, const char* className, void* callback, VMClassRegistry* registry) : NativeFunction(functionName, className, 5) {
		m_callback = callback;
		m_retnType = VMValue::kType_Bool;
		m_params.data[0].type = GetVMTypeID <T1>();
		m_params.data[1].type = GetVMTypeID <T2>();
		m_params.data[2].type = GetVMTypeID <T3>();
		m_params.data[3].type = GetVMTypeID <T4>();
		m_params.data[4].type = GetVMTypeID <T5>();
	}

	virtual bool Run(VMValue* baseValue, VMClassRegistry* registry, UInt32 arg2, VMValue* resultValue, VMState* state) {
		T1 Arg1;
		T2 Arg2;
		T3 Arg3;
		T4 Arg4;
		T5 Arg5;
		bool result = false;
		UInt32 Offset = state->argList->GetOffset(state);

		UnpackValue(&Arg1, state->argList->Get(state, 0, Offset));
		UnpackValue(&Arg2, state->argList->Get(state, 0, Offset));
		UnpackValue(&Arg3, state->argList->Get(state, 0, Offset));
		UnpackValue(&Arg4, state->argList->Get(state, 0, Offset));
		UnpackValue(&Arg5, state->argList->Get(state, 0, Offset));
		result = ((CallbackType)m_callback)(NULL, Arg1, Arg2, Arg3, Arg4, Arg5);
		resultValue->type = VMValue::kType_Bool;
		resultValue->data.b = result;
		return true;
	}

};

template <typename T1, typename T2, typename T3, typename T4>
class PapyrusFunction4 : public NativeFunction {
public:
	typedef bool (*CallbackType)(void* Base, T1 Arg1, T2 Arg2, T3 Arg3, T4 Arg4);

	PapyrusFunction4(const char* functionName, const char* className, void* callback, VMClassRegistry* registry) : NativeFunction(functionName, className, 4) {
		m_callback = callback;
		m_retnType = VMValue::kType_Bool;
		m_params.data[0].type = GetVMTypeID <T1>();
		m_params.data[1].type = GetVMTypeID <T2>();
		m_params.data[2].type = GetVMTypeID <T3>();
		m_params.data[3].type = GetVMTypeID <T4>();
	}

	virtual bool Run(VMValue* baseValue, VMClassRegistry* registry, UInt32 arg2, VMValue* resultValue, VMState* state) {
		T1 Arg1;
		T2 Arg2;
		T3 Arg3;
		T4 Arg4;
		bool result = false;
		UInt32 Offset = state->argList->GetOffset(state);

		UnpackValue(&Arg1, state->argList->Get(state, 0, Offset));
		UnpackValue(&Arg2, state->argList->Get(state, 0, Offset));
		UnpackValue(&Arg3, state->argList->Get(state, 0, Offset));
		UnpackValue(&Arg4, state->argList->Get(state, 0, Offset));
		result = ((CallbackType)m_callback)(NULL, Arg1, Arg2, Arg3, Arg4);
		resultValue->type = VMValue::kType_Bool;
		resultValue->data.b = result;
		return true;
	}

};

template <typename T1, typename T2, typename T3>
class PapyrusFunction3 : public NativeFunction {
public:
	typedef bool (*CallbackType)(void* Base, T1 Arg1, T2 Arg2, T3 Arg3);

	PapyrusFunction3(const char* functionName, const char* className, void* callback, VMClassRegistry* registry) : NativeFunction(functionName, className, 3) {
		m_callback = callback;
		m_retnType = VMValue::kType_Bool;
		m_params.data[0].type = GetVMTypeID <T1>();
		m_params.data[1].type = GetVMTypeID <T2>();
		m_params.data[2].type = GetVMTypeID <T3>();
	}

	virtual bool Run(VMValue* baseValue, VMClassRegistry* registry, UInt32 arg2, VMValue* resultValue, VMState* state) {
		T1 Arg1;
		T2 Arg2;
		T3 Arg3;
		bool result = false;
		UInt32 Offset = state->argList->GetOffset(state);

		UnpackValue(&Arg1, state->argList->Get(state, 0, Offset));
		UnpackValue(&Arg2, state->argList->Get(state, 0, Offset));
		UnpackValue(&Arg3, state->argList->Get(state, 0, Offset));
		result = ((CallbackType)m_callback)(NULL, Arg1, Arg2, Arg3);
		resultValue->type = VMValue::kType_Bool;
		resultValue->data.b = result;
		return true;
	}

};

template <typename T1, typename T2>
class PapyrusFunction2 : public NativeFunction {
public:
	typedef bool (*CallbackType)(void* Base, T1 Arg1, T2 Arg2);

	PapyrusFunction2(const char* functionName, const char* className, void* callback, VMClassRegistry* registry) : NativeFunction(functionName, className, 2) {
		m_callback = callback;
		m_retnType = VMValue::kType_Bool;
		m_params.data[0].type = GetVMTypeID <T1>();
		m_params.data[1].type = GetVMTypeID <T2>();
	}

	virtual bool Run(VMValue* baseValue, VMClassRegistry* registry, UInt32 arg2, VMValue* resultValue, VMState* state) {
		T1 Arg1;
		T2 Arg2;
		bool result = false;
		UInt32 Offset = state->argList->GetOffset(state);

		UnpackValue(&Arg1, state->argList->Get(state, 0, Offset));
		UnpackValue(&Arg2, state->argList->Get(state, 0, Offset));
		result = ((CallbackType)m_callback)(NULL, Arg1, Arg2);
		resultValue->type = VMValue::kType_Bool;
		resultValue->data.b = result;
		return true;
	}

};

template <typename T1>
class PapyrusFunction1 : public NativeFunction {
public:
	typedef bool (*CallbackType)(void* Base, T1 Arg1);

	PapyrusFunction1(const char* functionName, const char* className, void* callback, VMClassRegistry* registry) : NativeFunction(functionName, className, 1) {
		m_callback = callback;
		m_retnType = VMValue::kType_Bool;
		m_params.data[0].type = GetVMTypeID <T1>();
	}

	virtual bool Run(VMValue* baseValue, VMClassRegistry* registry, UInt32 arg2, VMValue* resultValue, VMState* state) {
		T1 Arg1;
		bool result = false;
		UInt32 Offset = state->argList->GetOffset(state);

		UnpackValue(&Arg1, state->argList->Get(state, 0, Offset));
		result = ((CallbackType)m_callback)(NULL, Arg1);
		resultValue->type = VMValue::kType_Bool;
		resultValue->data.b = result;
		return true;
	}

};

class PapyrusFunction0 : public NativeFunction {
public:
	typedef bool (*CallbackType)(void* Base);

	PapyrusFunction0(const char* functionName, const char* className, void* callback, VMClassRegistry* registry) : NativeFunction(functionName, className, 0) {
		m_callback = callback;
		m_retnType = VMValue::kType_Bool;
	}

	virtual bool Run(VMValue* baseValue, VMClassRegistry* registry, UInt32 arg2, VMValue* resultValue, VMState* state) {
		bool result = false;
		
		result = ((CallbackType)m_callback)(NULL);
		resultValue->type = VMValue::kType_Bool;
		resultValue->data.b = result;
		return true;
	}

};

static void* (__cdecl* MemoryAlloc)(size_t) = (void* (__cdecl*)(size_t))0x004017F0;
static bool  (__cdecl* ExtractArgs)(CommandParam*, void*, UInt32*, TESObjectREFR*, TESObjectREFR*, Script*, ScriptEventList*, ...) = (bool (__cdecl*)(CommandParam*, void*, UInt32*, TESObjectREFR*, TESObjectREFR*, Script*, ScriptEventList*, ...))0x00514830;
static void  (* PrintToConsole)(const char*, ...) = (void (*)(const char*, ...))0x00848820;