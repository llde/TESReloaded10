#pragma once

#include "GameNi.h"
#include "GameHavok.h"

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

class CommandTable {	// Only for Skyrim. SR auto-patches the command table because it is no more supported by SKSE due to the use of Papyrus
public:
	struct PatchLocation {
		UInt32	Ptr;
		UInt32	Offset;
		UInt32	Type;
	};

	std::vector<CommandInfo>	Commands;
	UInt32						BaseID;	// should be the same as Commands[0].opcode when the table is filled
	UInt32						CurID;
	bool						Patched;

	void Initialize() {

		this->BaseID = 0x1000;
		this->CurID = 0x1000;
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

class RGBA {
public:
	UInt8	r;
	UInt8	g;
	UInt8	b;
	UInt8	a;
};
assert(sizeof(RGBA) == 0x004);

#if defined(OBLIVION)
class BSString {
public:
	bool Set(const char* src) { return ThisCall(0x004028D0, this, src, 0); }

	const char* m_data;		// 00
	UInt16		m_dataLen;  // 04
	UInt16		m_bufLen;	// 06
};
assert(sizeof(BSString) == 0x008);

class BSExtraData {
public:
	enum ExtraDataType {
		kExtraData_Havok = 0x02,
		kExtraData_Cell3D = 0x03,
		kExtraData_WaterHeight = 0x04,
		kExtraData_CellWaterType = 0x05,
		kExtraData_RegionList = 0x08,
		kExtraData_SeenData = 0x09,
		kExtraData_EditorID = 0x0A,
		kExtraData_CellMusicType = 0x0B,
		kExtraData_CellClimate = 0x0C,
		kExtraData_ProcessMiddleLow = 0x0D,
		kExtraData_EditorCommonDialogData = 0x0E,
		kExtraData_CellCanopyShadowMask = 0x0F,
		kExtraData_DetachTime = 0x10,
		kExtraData_PersistentCell = 0x11,
		kExtraData_Script = 0x12,
		kExtraData_Action = 0x13,
		kExtraData_StartingPosition = 0x14,
		kExtraData_Anim = 0x15,

		kExtraData_UsedMarkers = 0x17,
		kExtraData_DistantData = 0x18,
		kExtraData_RagDollData = 0x19,
		kExtraData_InventoryChanges = 0x1A,
		kExtraData_Worn = 0x1B,
		kExtraData_WornLeft = 0x1C,

		kExtraData_StartLocation = 0x1E,
		kExtraData_Package = 0x1F,
		kExtraData_TresPassPackage = 0x20,
		kExtraData_RunOncePacks = 0x21,
		kExtraData_ReferencePointer = 0x22,
		kExtraData_Follower = 0x23,
		kExtraData_LevCreaModifier = 0x24,
		kExtraData_Ghost = 0x25,
		kExtraData_OriginalReference = 0x26,
		kExtraData_Ownership = 0x27,
		kExtraData_Global = 0x28,
		kExtraData_Rank = 0x29,
		kExtraData_Count = 0x2A,
		kExtraData_Health = 0x2B,
		kExtraData_Uses = 0x2C,
		kExtraData_TimeLeft = 0x2D,
		kExtraData_Charge = 0x2E,
		kExtraData_Soul = 0x2F,
		kExtraData_Light = 0x30,
		kExtraData_Lock = 0x31,
		kExtraData_Teleport = 0x32,
		kExtraData_MapMarker = 0x33,

		kExtraData_LeveledCreature = 0x35,
		kExtraData_LeveledItem = 0x36,
		kExtraData_Scale = 0x37,
		kExtraData_Seed = 0x38,
		kExtraData_NonActorMagicCaster = 0x39,

		kExtraData_CrimeGold = 0x3D,
		kExtraData_OblivionEntry = 0x3E,
		kExtraData_EnableStateParent = 0x3F,
		kExtraData_EnableStateChildren = 0x40,
		kExtraData_ItemDropper = 0x41,
		kExtraData_DroppedItemList = 0x42,
		kExtraData_RandomTeleportMarker = 0x43,
		kExtraData_MerchantContainer = 0x44,

		kExtraData_PersuasionPercent = 0x46,
		kExtraData_CannotWear = 0x47,
		kExtraData_Poison = 0x48,

		kExtraData_LastFinishedSequence = 0x4A,
		kExtraData_SavedMovementData = 0x4B,
		kExtraData_NorthRotation = 0x4C,
		kExtraData_XTarget = 0x4D,
		kExtraData_FriendHitList = 0x4E,
		kExtraData_HeadingTarget = 0x4F,
		kExtraData_BoundArmor = 0x50,
		kExtraData_RefractionProperty = 0x51,
		kExtraData_InvestmentGold = 0x52,
		kExtraData_StartingWorldOrCell = 0x53,

		kExtraData_QuickKey = 0x55,

		kExtraData_EditorRefMoveData = 0x57,
		kExtraData_TravelHorse = 0x58,
		kExtraData_InfoGeneralTopic = 0x59,
		kExtraData_HasNoRumors = 0x5A,
		kExtraData_ExtraSound = 0x5B,
		kExtraData_HaggleAmount = 0x5C,
	};

	virtual bool	Compare(BSExtraData* compareWith);	// compare type, data, return true if not equal

	UInt8			type;		// 004
	UInt8			pad[3];		// 005
	BSExtraData*	next;		// 008
};
assert(sizeof(BSExtraData) == 0x0C);

class InventoryChanges : public BSExtraData {
public:
	class EntryData {
	public:
		bool	IsWorn(bool Left) { return (UInt8)ThisCall(0x00484E80, this, Left) == 1; }

		TList<ExtraDataList>*	extendData;
		SInt32					countDelta;
		TESForm*				type;
	};

	class Data {
	public:
		TList<EntryData>*	data;
		TESObjectREFR*		owner;
		float				totalWeight;	// of all items in inventory. cached, is -1 if needs to be recalculated
		float				armorWeight;	// weight of equipped armor. cached as above. Both take armor weight perks into account
	};

	Data*	data;			// 00C
};
assert(sizeof(InventoryChanges) == 0x10);

class ExtraHavok : public BSExtraData {
public:
	bhkRefObject*	world;	// 00C bhkWorld
	UInt32			unk10;	// 010
};
assert(sizeof(ExtraHavok) == 0x014);

class ExtraDataList {
public:
	virtual	void			Destroy(bool bNoDealloc);	// removes and frees all of m_data
	
	BSExtraData*			GetExtraData(BSExtraData::ExtraDataType DataType) { return (BSExtraData*)ThisCall(0x0041E210, this, DataType); }
	bool					IsWorn(bool Left) { return (UInt8)ThisCall(0x0041DF10, this, Left) == 1; }
	bool					IsWorn() { return IsWorn(0) || IsWorn(1); }
	void					SetWorn(bool Status, bool Left) { ThisCall(0x0041F200, this, Status, Left); }
	InventoryChanges::Data*	GetInventoryChangesData() { return (InventoryChanges::Data*)ThisCall(0x0041E6F0, this); }

	BSExtraData*			m_data;					// 004
	UInt8					m_presenceBitfield[12];	// 008 - if a bit is set, then the extralist should contain that extradata - bits are numbered starting from the lsb
};
assert(sizeof(ExtraDataList) == 0x14);

class MagicCaster {
public:
	virtual void			Unk_00(UInt32 arg0, UInt32 arg1);
	virtual void			Unk_01(UInt32 arg0, UInt32 arg1, UInt32 arg2);
	virtual void			Unk_02(UInt32 arg0, UInt32 arg1, UInt32 arg2);
	virtual void			Unk_03();
	virtual void			Unk_04();
	virtual void			Unk_05();
	virtual void			Unk_06();
	virtual bool			Unk_07(MagicItem* magicItem, float* arg1, UInt32* outMagicItemType, UInt32 arg3);
	virtual TESObjectREFR*	GetParentRefr();
	virtual NiNode*			GetMagicNode();	// looks up "magicnode" node in caster's NiNode
	virtual void			Unk_0A();
	virtual float			GetSpellEffectiveness(float arg0, float arg1);	// seen (0, 0)
	virtual MagicItem*		GetQueuedMagicItem();		// calls through to MiddleHighProcess
	virtual void			Unk_0D();
	virtual void			Unk_0E();
	virtual void			Unk_0F();
	virtual void			Unk_10(MagicItem* magicItem, UInt32 mgefCode, UInt32 unk2);	// activate effect?

	enum {
		kState_Inactive = 0,
		kState_Aim = 1,
		kState_Cast = 2,
		kState_FindTargets = 4,
		// these seem to be considered "errors" by the game
		kState_SpellDisabled = 5,
		kState_AlreadyCasting = 6,
		kState_CannotCast = 7
	};

	NiNode* magicNode;		// 004 cached during casting anim
	UInt32	state;			// 008
};
assert(sizeof(MagicCaster) == 0x0C);

class MagicTarget {
public:
	virtual void			Destructor();
	virtual	TESObjectREFR*	GetParent();
	virtual EffectNode*		GetEffectList();

	UInt8	unk04;			// 004
	UInt8	pad05[3];
};
assert(sizeof(MagicTarget) == 0x08);

class ActorValues {
public:
	struct Entry {
		UInt32		avCode;
		float		value;
	};

	TList<Entry>	avList;			// 00
	Entry*			magicka;		// 08
	Entry*			fatigue;		// 0C
	Entry**			avArray;		// 10 array of more AV modifiers, size 0x12?
};
assert(sizeof(ActorValues) == 0x14);

class BaseFormComponent {
public:
	virtual void	Destructor();	// 00
	virtual void	Unk_01();
	virtual void	CopyFromBase(BaseFormComponent* component);
	virtual bool	CompareWithBase(BaseFormComponent* src);
};
assert(sizeof(BaseFormComponent) == 0x004);

class TESDescription : public BaseFormComponent {
public:
	virtual const char* GetText(TESForm* parentForm, UInt32 recordCode);

	UInt32	formDiskOffset;	// 04
};
assert(sizeof(TESDescription) == 0x008);

class TESModel : public BaseFormComponent {
public:
	virtual void			Unk_04();
	virtual const char*		GetModelPath();
	virtual void			SetModelPath(const char* path);

	BSString	nifPath;	// 004
	float		editorSize;	// 00C 'size' field in editor, from MODB subrecord. Only present for objects defined in Oblivion.esm?
	UInt8		unk10;		// 010
	UInt8		pad11[3];
	void*		unk14;		// 014
};
assert(sizeof(TESModel) == 0x018);

class TESModelAnim : public TESModel {};
assert(sizeof(TESModelAnim) == 0x018);

class TESScriptableForm : public BaseFormComponent {
public:
	Script* script;		// 004
	UInt8	unk1;		// 008
	UInt8	pad[3];		// 009
};
assert(sizeof(TESScriptableForm) == 0x00C);

class TESEnchantableForm : public BaseFormComponent {
public:
	EnchantmentItem* enchantItem;	// 04
	UInt16			 enchantment;	// 08
	UInt16			 unk1;			// 0A
	UInt32			 unk2;			// 0C
};
assert(sizeof(TESEnchantableForm) == 0x010);

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

class TESHealthForm : public BaseFormComponent {
public:
	UInt32	health;
};
assert(sizeof(TESHealthForm) == 0x008);

class TESAttackDamageForm : public BaseFormComponent {
public:
	UInt16	damage;
	UInt16	unk0;	// bitmask? perhaps 2 UInt8s?
};
assert(sizeof(TESAttackDamageForm) == 0x008);

class TESForm : public BaseFormComponent {
public:
	enum FormType {
		kFormType_None = 0,
		kFormType_TES4,
		kFormType_Group,
		kFormType_GMST,
		kFormType_Global,
		kFormType_Class,
		kFormType_Faction,
		kFormType_Hair,
		kFormType_Eyes,
		kFormType_Race,
		kFormType_Sound,
		kFormType_Skill,
		kFormType_Effect,
		kFormType_Script,
		kFormType_LandTexture,
		kFormType_Enchantment,
		kFormType_Spell,		// 10
		kFormType_BirthSign,
		kFormType_Activator,
		kFormType_Apparatus,
		kFormType_Armor,
		kFormType_Book,
		kFormType_Clothing,
		kFormType_Container,
		kFormType_Door,
		kFormType_Ingredient,
		kFormType_Light,
		kFormType_Misc,
		kFormType_Stat,	// ???
		kFormType_Grass,
		kFormType_Tree,
		kFormType_Flora,
		kFormType_Furniture,	// 20
		kFormType_Weapon,
		kFormType_Ammo,
		kFormType_NPC,
		kFormType_Creature,
		kFormType_LeveledCreature,
		kFormType_SoulGem,
		kFormType_Key,
		kFormType_AlchemyItem,
		kFormType_SubSpace,
		kFormType_SigilStone,
		kFormType_LeveledItem,
		kFormType_SNDG,
		kFormType_Weather,
		kFormType_Climate,
		kFormType_Region,
		kFormType_Cell,			// 30
		kFormType_REFR,
		kFormType_ACHR,
		kFormType_ACRE,
		kFormType_PathGrid,
		kFormType_WorldSpace,
		kFormType_Land,
		kFormType_TLOD,	// tile low lod?
		kFormType_Road,
		kFormType_Dialog,
		kFormType_DialogInfo,
		kFormType_Quest,
		kFormType_Idle,
		kFormType_Package,
		kFormType_CombatStyle,
		kFormType_LoadScreen,
		kFormType_LeveledSpell,	// 40
		kFormType_ANIO,
		kFormType_Water,
		kFormType_EffectShader,
		kFormType_TOFT
	};

	enum FormFlags {
		kFormFlags_FromMaster			= 0x00000001,   // form is from an esm file
		kFormFlags_FromActiveFile		= 0x00000002,   // form is overriden by active mod or save file
		kFormFlags_Loaded				= 0x00000004,   // ?? (from OBSE ModEntry defininition)
		kFormFlags_Linked				= 0x00000008,   // set after formids have been resolved into TESForm*
		kFormFlags_Deleted				= 0x00000020,   // set on deletion, not saved in CS, probably game as well
		kFormFlags_BorderRegion			= 0x00000040,   // ?? (from TES4Edit)
		kFormFlags_TurnOffFire			= 0x00000080,   // ?? (from TES4Edit)
		kFormFlags_NotCastShadows		= 0x00000200,   // ?? (from TES4Edit)
		kFormFlags_QuestItem			= 0x00000400,   // aka Quest Item, Persistent Reference, Essenstial Actor
		kFormFlags_InitiallyDisabled	= 0x00000800,   // ?? (from TES4Edit)
		kFormFlags_Ignored				= 0x00001000,   // record is not loaded by CS, perhaps game as well
		kFormFlags_Harvested			= 0x00002000,	// 
		kFormFlags_Temporary			= 0x00004000,   // not saved in CS, probably game as well
		kFormFlags_VisibleWhenDistant	= 0x00008000,   // ?? (from TES4Edit)
		kFormFlags_OffLimits			= 0x00020000,   // ?? (from TES4Edit) //Theory: Offlimits for TESObjectCELL
		kFormFlags_Compressed			= 0x00040000,   // ?? (from TES4Edit)
		kFormFlags_CantWait				= 0x00080000,   // ?? (from TES4Edit) //For TESObjectCELL can't wait. Unkown for others TESForm
		kFormFlags_IgnoresFriendlyHits	= 0x00100000,
	};

	enum {
		kModified_FormFlags = 0x00000001,
		kModified_GoldValue = 0x08,
		kModified_Name = 0x80
	};

	virtual void	Destroy(bool Dealloc);
	virtual void	Unk_05();	// destroy form components
	virtual void	Unk_06();	// call unk01 on form components
	virtual bool	LoadForm(ModInfo* modInfo);
	virtual void	Unk_08();	// calls load form
	virtual void	Unk_09();	// save form
	virtual void	Unk_0A();	// calls save form
	virtual void	Unk_0B();
	virtual void	Unk_0C();
	virtual void	Unk_0D();
	virtual void	Unk_0E();
	virtual void	Unk_0F();
	virtual void	MarkAsModified(UInt32 mask);	// 10
	virtual void	ClearModified(UInt32 mask);
	virtual void	Unk_12();
	virtual UInt32	GetSaveSize(UInt32 modifiedMask);
	virtual void	SaveGame(UInt32 modifiedMask);	// output buffer not passed as param, accessed indirectly via g_createdBaseObjList
	virtual void	LoadGame(UInt32 modifiedMask, UInt32 unk);
	virtual void	Unk_16();	// post-load fixup (convert refids in to pointers, etc)
	virtual void	Unk_17();
	virtual void	Unk_18();
	virtual void	Unk_19();
	virtual void	Unk_1A();
	virtual void	DoPostFixup();	// initialize form after other forms loaded
	virtual void	Unk_1C();
	virtual void	GetDescription(BSString* dst);
	virtual void	Unk_1E();
	virtual void	Unk_1F();
	virtual void	Unk_20();	// 20
	virtual void	Unk_21();
	virtual void	Unk_22();
	virtual void	Unk_23();
	virtual void	Unk_24(UInt8 arg);
	virtual void	SetQuestItem(bool isQuestItem);
	virtual void	Unk_26();
	virtual void	Unk_27();
	virtual void	Unk_28();
	virtual bool	Unk_29();
	virtual bool	Unk_2A();	// return true if the form is a reference?
	virtual bool	Unk_2B();
	virtual void	Unk_2C();
	virtual void	CopyFrom(TESForm* form);
	virtual bool	Compare(TESForm* form);
	virtual void	Unk_2F();
	virtual void	Unk_30();	// 30
	virtual void	Unk_31();
	virtual void	Unk_32();
	virtual bool	Unk_33(TESObjectREFR* refr0, TESObjectREFR* refr1, UInt32 unk2); // related to activate, refr1 is activating refr, refr0 is a reference to this TESForm being activated, seen unk2 == 0
	virtual char*	GetName();	// not sure which objects this works on, doesn't seem to work on player or random objects
	virtual char*	GetEditorName(); // returns nothing at runtime (return the editorname for TESObjectCELL)
	virtual bool	SetEditorName(const char* name);

	void			GenerateID(UInt32 ID) { ThisCall(0x0046C300, this, ID, 1); }

	UInt8				formType;				// 004
	UInt8				pad005[3];				// 005
	UInt32				flags;					// 008
	UInt32				refID;					// 00C
	TList<ModInfo>		modRefList;				// 010
};
assert(sizeof(TESForm) == 0x018);

class TESPackage : public TESForm {
public:
	enum {
		kPackageFlag_OffersServices			= 1 << 0,
		kPackageFlag_MustReachLocation		= 1 << 1,
		kPackageFlag_MustComplete			= 1 << 2,
		kPackageFlag_LockDoorsAtStart		= 1 << 3,
		kPackageFlag_LockDoorsAtEnd			= 1 << 4,
		kPackageFlag_LockDoorsAtLocation	= 1 << 5,
		kPackageFlag_UnlockDoorsAtStart		= 1 << 6,
		kPackageFlag_UnlockDoorsAtEnd		= 1 << 7,
		kPackageFlag_UnlockDoorsAtLocation	= 1 << 8,
		kPackageFlag_ContinueIfPCNear		= 1 << 9,
		kPackageFlag_OncePerDay				= 1 << 10,
		kPackageFlag_Unk11					= 1 << 11,
		kPackageFlag_SkipFalloutBehavior	= 1 << 12,
		kPackageFlag_AlwaysRun				= 1 << 13,
		kPackageFlag_Unk14					= 1 << 14,
		kPackageFlag_Unk15					= 1 << 15,
		kPackageFlag_Unk16					= 1 << 16,
		kPackageFlag_AlwaysSneak			= 1 << 17,
		kPackageFlag_AllowSwimming			= 1 << 18,
		kPackageFlag_AllowFalls				= 1 << 19,
		kPackageFlag_ArmorUnequipped		= 1 << 20,
		kPackageFlag_WeaponsUnequipped		= 1 << 21,
		kPackageFlag_DefensiveCombat		= 1 << 22,
		kPackageFlag_UseHorse				= 1 << 23,
		kPackageFlag_NoIdleAnims			= 1 << 24,
		kPackageFlag_Unk25					= 1 << 25,
		kPackageFlag_Unk26					= 1 << 26,
		kPackageFlag_Unk27					= 1 << 27,
		kPackageFlag_Unk28					= 1 << 28,
		kPackageFlag_Unk29					= 1 << 29,
		kPackageFlag_Unk30					= 1 << 30,
		kPackageFlag_Unk31					= 1 << 31,
	};

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
		kPackageType_CombatController,	// Actor::GetCombatController returns package only if type matches this
		kPackType_Unk0D,				// also related to dynamic combat packages?
		kPackType_MAX
	};

	struct Time {
		enum {
			kDay_Any = 0,
			kTime_Any = 0xFF,
		};

		enum {
			kMonth_January = 0,
			kMonth_February,
			kMonth_March,
			kMonth_April,
			kMonth_May,
			kMonth_June,
			kMonth_July,
			kMonth_August,
			kMonth_September,
			kMonth_October,
			kMonth_November,
			kMonth_December,
			kMonth_Spring,	// march, april, may
			kMonth_Summer,	// june, july, august
			kMonth_Fall,	// september, august, november
			kMonth_Winter,	// december, january, february
			kMonth_Any = 0xFF,
		};

		enum {
			kWeekday_Sundas = 0,
			kWeekday_Morndas,
			kWeekday_Tirdas,
			kWeekday_Middas,
			kWeekday_Turdas,
			kWeekday_Fredas,
			kWeekday_Loredas,
			kWeekday_Weekdays,
			kWeekday_Weekends,
			kWeekday_MWF,
			kWeekday_TT,
			kWeekday_Any = 0xFF
		};

		UInt8	month;
		UInt8	weekDay;
		UInt8	date;
		UInt8	time;
		UInt32	duration;
	};

	union ObjectType {
		TESForm*		form;
		TESObjectREFR*	refr;
		UInt32			objectCode;
	};

	// order only somewhat related to kFormType_XXX (values off by 17, 20, or 21)
	enum {
		kObjectType_Activator = 0x01,
		kObjectType_Apparatus,
		kObjectType_Armor,
		kObjectType_Book,
		kObjectType_Clothing,
		kObjectType_Container,
		kObjectType_Door,
		kObjectType_Ingredient,
		kObjectType_Light,
		kObjectType_Misc,
		kObjectType_Flora,
		kObjectType_Furniture,
		kObjectType_WeaponAny,
		kObjectType_Ammo,
		kObjectType_NPC,
		kObjectType_Creature,		// 10
		kObjectType_Soulgem,
		kObjectType_Key,
		kObjectType_Alchemy,
		kObjectType_Food,
		kObjectType_CombatWearable,
		kObjectType_Wearable,
		kObjectType_WeaponNone,
		kObjectType_WeaponMelee,
		kObjectType_WeaponRanged,
		kObjectType_SpellsAny,
		kObjectType_SpellsTarget,
		kObjectType_SpellsTouch,
		kObjectType_SpellsSelf,
		kObjectType_SpellsAlteration,
		kObjectType_SpellsConjuration,
		kObjectType_SpellsDestruction,	// 20
		kObjectType_SpellsIllusion,
		kObjectType_SpellsMysticism,
		kObjectType_SpellsRestoration,
		kObjectType_Max = 0x24,
	};

	struct LocationData {
		enum {
			kPackLocation_NearReference = 0,
			kPackLocation_InCell = 1,
			kPackLocation_CurrentLocation = 2,
			kPackLocation_EditorLocation = 3,
			kPackLocation_ObjectID = 4,
			kPackLocation_ObjectType = 5,
			kPackLocation_Max,
		};

		UInt8		locationType;
		UInt8		pad[3];
		UInt32		radius;
		ObjectType  object;
	};

	enum {
		kTargetType_Refr = 0,
		kTargetType_BaseObject = 1,
		kTargetType_TypeCode = 2,
	};

	struct TargetData {
		UInt8		targetType;
		UInt8		pad[3];
		ObjectType	target;
		UInt32		count;
	};

	enum eProcedure {			// UInt32
		kProcedure_TRAVEL = 0,
		kProcedure_WANDER,
		kProcedure_ACTIVATE,
		kProcedure_AQUIRE,	// sic
		kProcedure_SLEEP,
		kProcedure_EAT,
		kProcedure_FOLLOW,
		kProcedure_ESCORT,
		kProcedure_ALARM,
		kProcedure_COMBAT,
		kProcedure_FLEE,
		kProcedure_YIELD,
		kProcedure_DIALOGUE,
		kProcedure_WAIT,
		kProcedure_TRAVEL_TARGET,
		kProcedure_PURSUE,
		kProcedure_GREET,					// 0x10
		kProcedure_CREATE_FOLLOW,
		kProcedure_OBSERVE_COMBAT,
		kProcedure_OBSERVE_DIALOGUE,
		kProcedure_GREET_DEAD,
		kProcedure_WARN,
		kProcedure_GET_UP,
		kProcedure_MOUNT_HORSE,
		kProcedure_DISMOUNT_HORSE,
		kProcedure_DO_NOTHING,
		kProcedure_CAST_SPELL,
		kProcedure_AIM,
		kProcedure_NOTIFY,
		kProcedure_ACCOMPANY,
		kProcedure_USE_ITEM_AT,
		kProcedure_FEED,
		kProcedure_AMBUSH_WAIT,				// 0x20
		kProcedure_SURFACE,
		kProcedure_WAIT_FOR_SPELL,
		kProcedure_CHOOSE_CAST,
		kProcedure_FLEE_NON_COMBAT,
		kProcedure_REMOVE_WORN_ITEMS,
		kProcedure_SEARCH,
		kProcedure_CLEAR_MOUNT_POSITION,
		kProcedure_SUMMON_CREATURE_DEFEND,
		kProcedure_MOVEMENT_BLOCKED,
		kProcedure_UNEQUIP_ARMOR,
		kProcedure_DONE,					// 0x2B

		kProcedure_MAX						// 0x2C
	};

	UInt32			procedureArrayIndex;	// 018 index into array of array of eProcedure terminated by 0x2C (-1 if no procedure array exists for package type)
	UInt32			packageFlags;			// 01C
	UInt8			type;					// 020
	UInt8			pad021[3];				// 021
	LocationData*	location;				// 024
	TargetData*		target;					// 028
	Time			time;					// 02C
	TList<void*>	conditions;				// 034 ConditionEntry
};
assert(sizeof(TESPackage) == 0x3C);

class TESIdleForm : public TESForm {
public:
	enum AnimFlag {
		kAnimFlag_LowerBody = 0,
		kAnimFlag_LeftArm,
		kAnimFlag_LeftHand,
		kAnimFlag_RightArm,
		kAnimFlag_SpecialIdle,
		kAnimFlag_WholeBody,
		kAnimFlag_UpperBody,
		kAnimFlag_MustReturnFile = 0x7F
	};

	void			SetFile(const char* Name) { animModel.nifPath.Set(Name); }

	TESModelAnim	animModel;		// 18

	TList<void*>	conditions;		// 30 Condition List
	UInt32			animFlags;		// 38
	NiFormArray*	children;		// 3C
	TESIdleForm*	parent;			// 40
	TESIdleForm*	previous;		// 44
};
assert(sizeof(TESIdleForm) == 0x48);

class TESTexture : public BaseFormComponent {
public:
	BSString	ddsPath;		// 04
};
assert(sizeof(TESTexture) == 0x0C);

class TESIcon : public TESTexture { };
assert(sizeof(TESIcon) == 0x0C);

class TESFullName : public BaseFormComponent {
public:
	BSString	name;		// 004
};
assert(sizeof(TESFullName) == 0x0C);

class TESWeather : public TESForm {
public:
	enum { kNumColorTypes = 10 };
	enum { kNumTimeOfDay = 4 };

	struct FogInfo {
		float nearFog;
		float farFog;
	};

	enum {
		eHDR_EyeAdpat = 0,
		eHDR_BlurRadius,
		eHDR_BlurPasses,
		eHDR_EmissiveMult,
		eHDR_TargetLUM,
		eHDR_UpperLUMClamp,
		eHDR_BrightScale,
		eHDR_BrightClamp,
		eHDR_LUMRampNoTex,
		eHDR_LUMRampMin,
		eHDR_LUMRampMax,
		eHDR_SunlightDimmer,
		eHDR_GrassDimmer,
		eHDR_TreeDimmer,
		eHDR_Last = eHDR_TreeDimmer,
	};

	enum {
		eColor_SkyUpper = 0,
		eColor_Fog,
		eColor_CloudsLower,
		eColor_Ambient,
		eColor_Sunlight,
		eColor_Sun,
		eColor_Stars,
		eColor_SkyLower,
		eColor_Horizon,
		eColor_CloudsUpper,
		eColor_Lighting,
	};

	enum {
		eTime_Sunrise = 0,
		eTime_Day,
		eTime_Sunset,
		eTime_Night,
	};

	enum WeatherType {
		kType_None = 0,
		kType_Pleasant = 1,
		kType_Cloudy = 2,
		kType_Rainy = 4,
		kType_Snow = 8,
	};

	struct ColorData {
		RGBA colors[4];
	};

	struct SoundData {
		UInt32 ID;
		UInt32 count;
	};

	float			GetFogDayNear() { return fogDay.nearFog; }
	float			GetFogDayFar() { return fogDay.farFog; }
	float			GetFogNightNear() { return fogNight.nearFog; }
	float			GetFogNightFar() { return fogNight.farFog; }

	TESTexture			textureLayers[2];			// 018
	TESModel			model;						// 030
	UInt8				windSpeed;					// 048
	UInt8				cloudSpeedLower;			// 049
	UInt8				cloudSpeedUpper;			// 04A
	UInt8				transDelta;					// 04B
	UInt8				sunGlare;					// 04C
	UInt8				sunDamage;					// 04D
	UInt8				precipitationBeginFadeIn;	// 04E
	UInt8				precipitationEndFadeOut;	// 04F
	UInt8				lightningBeginFadeIn;		// 050
	UInt8				lightningEndFadeOut;		// 051
	UInt8				lightningFrequency;			// 052
	UInt8				weatherType;				// 053
	RGBA				lightningColor;				// 054
	FogInfo				fogDay;						// 058
	FogInfo				fogNight;					// 060
	ColorData			colors[10];					// 068
	TList<SoundData>	sounds;						// 108
	float				hdrInfo[14];				// 110
};
assert(sizeof(TESWeather) == 0x148);

class TESWeatherEx : public TESWeather {
public:
	ColorData	colorsb[TESWeather::kNumColorTypes];
	char		EditorName[40];
};
assert(sizeof(TESWeatherEx) == 0x210);

class TESClimate : public TESForm {
public:
	enum {
		kClimate_Masser = 0x80,
		kClimate_Secunda = 0x40,
		kClimate_PhaseLengthMask = 0x3F,
	};

	struct WeatherType {
		TESWeather* weather;
		UInt32		chance;
	};

	TESModel			nightSky;		// 018
	TList<WeatherType>	weatherTypes;	// 030
	TESTexture			sun;			// 038
	TESTexture			sunGlare;		// 044
	UInt8				sunriseBegin;	// 050
	UInt8				sunriseEnd;		// these are the number of 10 minute increments past midnight
	UInt8				sunsetBegin;	// 6 increments per hour
	UInt8				sunsetEnd;
	UInt8				volatility;		// 054
	UInt8				phaseLength;
	UInt8				pad[2];
};
assert(sizeof(TESClimate) == 0x058);

class TESWaterForm : public TESForm {
public:
	enum WaterVal {								// use to index into simValues array
		kWaterVal_WindVelocity = 0,
		kWaterVal_WindDirection,
		kWaterVal_WaveAmplitude,
		kWaterVal_WaveFrequency,
		kWaterVal_SunPower,
		kWaterVal_Reflectivity,
		kWaterVal_FresnelAmount,
		kWaterVal_ScrollX,
		kWaterVal_ScrollY,
		kWaterVal_FogDistNear,
		kWaterVal_FogDistFar,
	};

	enum WaterType {
		kWaterType_Blood,
		kWaterType_Lava,
		kWaterType_Normal,
	};
	
	UInt32				GetWaterType() { return waterType; };
	void				RemoveUnderwaterFog() { waterSimVals[TESWaterForm::kWaterVal_FogDistNear] = 163830.0f; waterSimVals[TESWaterForm::kWaterVal_FogDistFar] = 163835.0f; };

	TESAttackDamageForm	damageForm;				// 18
	TESTexture			texture;				// 20
	UInt8				opacity;				// 2C
	UInt8				waterType;				// 2D
	UInt8				pad2E[2];
	UInt32				unk30;					// 30
	UInt16				unk34;					// 34
	UInt16				unk36;
	TESSound*			loopSound;				// 38
	float				waterSimVals[11];		// 3C
	UInt8				shallowColorR;			// 68
	UInt8				shallowColorG;
	UInt8				shallowColorB;
	UInt8				shallowColorA;
	UInt8				deepColorR;				// 6C
	UInt8				deepColorG;
	UInt8				deepColorB;
	UInt8				deepColorA;
	UInt8				reflectColorR;			// 70
	UInt8				reflectColorG;
	UInt8				reflectColorB;
	UInt8				reflectColorA;
	UInt32				textureBlend;			// 74
	float				rainSimVals[5];			// 78
	float				displacementSimVals[5];	// 8C
	UInt32				unkA0[3];				// A0 look like pointers to day/night/underwater water forms
};
assert(sizeof(TESWaterForm) == 0x0AC);

class TESWorldSpace : public TESForm {
public:
	enum {
		// "Can't Wait" flag does not appear to be saved by editor
		kFlag_SmallWorld	= 1 << 0,
		kFlag_NoFastTravel	= 1 << 1,
		kFlag_OblivionWorld = 1 << 2,
		kFlag_NoLODWater	= 1 << 4,
	};

	TESFullName						fullName;			// 018
	TESTexture						texture;			// 024
	NiTMap<UInt32, TESObjectCELL>*  cellMap;			// 030 - key is coordinates of cell: (x << 16 + y)
	TESObjectCELL*					unk034;				// 034
	NiTMap<UInt32, void>			map;				// 038
	TESWorldSpace*					worldSpace048;		// 048
	UInt32							unk04C[(0x58 - 0x4C) >> 2];	// 04C
	TESClimate*						climate;			// 058
	UInt32							worldFlags;			// 05C
	UInt32							unk060;				// 060
	NiTMap<UInt32, void>			map064;				// 064
	Character*						character;			// 074
	void*							ptr078;				// 078
	TESWorldSpace*					parentWorldspace;	// 07C
	UInt32							unk080[(0xC0 - 0x80) >> 2];	// 080
	BSString						editorID;			// 0C0
	NiTMap<UInt32, void>			map0C8;				// 0C8
	UInt32							unk0D8[(0xE0 - 0xD8) >> 2];	// 0D8
};
assert(sizeof(TESWorldSpace) == 0x0E0);

class TESGlobal : public TESForm {
public:
	BSString	name;		// 018
	UInt8		type;		// 020
	UInt8		pad21[3];	// 021
	float		data;		// 024
};
assert(sizeof(TESGlobal) == 0x028);

class TESSkill : public TESForm {
public:
	enum {
		kSkill_Armorer = 0x0C,
		kSkill_Athletics,
		kSkill_Blade,
		kSkill_Block,
		kSkill_Blunt,		// 10
		kSkill_HandToHand,
		kSkill_HeavyArmor,
		kSkill_Alchemy,
		kSkill_Alteration,
		kSkill_Conjuration,
		kSkill_Destruction,
		kSkill_Illusion,
		kSkill_Mysticism,	// 18
		kSkill_Restoration,
		kSkill_Acrobatics,
		kSkill_LightArmor,
		kSkill_Marksman,
		kSkill_Mercantile,
		kSkill_Security,
		kSkill_Sneak,
		kSkill_Speechcraft,	// 20
	};

	TESDescription	description;	// 018
	TESTexture		texture;		// 020
	UInt32			skill;			// 02C
	UInt32			attribute;		// 030
	UInt32			specialization;	// 034
	float			useValue0;		// 038 - amount to learn on successful action
	float			useValue1;		// 03C - action is different for each skill
	TESDescription	levelQuote[4];	// 040

};
assert(sizeof(TESSkill) == 0x060);

class TESRegion : public TESForm {
public:
	void*			unk018;			// 018
	void*			unk01C;			// 01C
	TESWorldSpace*  worldSpace;		// 020
	TESWeather*		weather;		// 024
	float			unk028;			// 028
};
assert(sizeof(TESRegion) == 0x02C);

class TESRegionEx : public TESRegion {
public:
	char		EditorName[40];		// 2C
};
assert(sizeof(TESRegionEx) == 0x054);

class Script : public TESForm {
public:
	enum {
		eType_Object = 0,
		eType_Quest = 1,
		eType_Magic = 0x100,
	};
	enum {
		eVarType_FloatOrRef,
		eVarType_Integer,
	};

	struct ScriptInfo {
		UInt32	unk0;		// 00
		UInt32	numRefs;	// 04
		UInt32	dataLength;	// 08
		UInt32	varCount;	// 0C
		UInt32	type;		// 10
	};

	struct RefVariable {
		BSString	name;		// variable name/editorID (not used at run-time)
		TESForm*	form;
		UInt32		varIdx;		// always zero in editor
	};

	struct VariableInfo {
		UInt32			idx;		// 00
		UInt32			pad04;		// 04
		double			data;		// 08
		UInt8			type;		// 10
		UInt8			pad11[3];	// 11
		UInt32			unk14;		// 14
		BSString		name;		// 18
	};

	ScriptInfo				info;					// 018
	char*					text;					// 02C
	void*					data;					// 030
	UInt32					unk34;					// 034
	float					questDelayTimeCounter;	// 038 - init'd to fQuestDelayTime, decremented by frametime each frame
	float					secondsPassed;			// 03C - only if you've modified fQuestDelayTime
	TList<RefVariable>		refList;				// 040 - ref variables and immediates
	TList<VariableInfo>		varList;				// 048 - local variable list
};
assert(sizeof(Script) == 0x50);

class TESQuest : public TESForm {
public:
	bool IsActive() { return (questFlags & kQuestFlag_Active) ? true : false; }

	enum {
		kModified_QuestFlags	= 0x00000004,
		kModified_QuestStage	= 0x10000000,
		kModified_QuestScript	= 0x08000000,
	};

	enum {
		kQuestFlag_Active		= 1 << 0,
		kQuestFlag_Completed	= 1 << 1,
		kQuestFlag_RepeatConv	= 1 << 2,
		kQuestFlag_RepeatStages = 1 << 3,
	};

	class QuestStageItem {
	public:
		class LogDate {
		public:
			UInt16	dayOfYear;
			UInt16	year;
		};

		UInt32			unk00;			// 00
		TList<void*>	conditions;		// 04
		Script			resultScript;	// 0C
		UInt32			unk5C;			// 5C disk offset to log text records? consistent within a single quest
		UInt8			index;			// 60 sequential
		UInt8			unk61;			// 61 previously 'hasLogText', which is incorrect
		UInt8			unk62[2];		// 62 pad?
		LogDate*		logDate;		// 64 alloc'ed when added to log. (Why use a 32-bit pointer to a 32-bit structure?)
		TESQuest*		owningQuest;	// 68
	};

	class StageEntry {
	public:
		enum {
			kFlag_CompleteQuest = 1 << 0,
		};

		UInt8					index;	// as defined in CS, not necessarily sequential
		UInt8					flags;
		UInt8					pad[2];
		TList<QuestStageItem>	itemList;
	};

	class TargetEntry {
	public:
		UInt32			unk00;			// 00 flags?
		TList<void*>	conditions;		// 04
		TESObjectREFR*	target;			// 0C
		TESObjectREFR*	doorRef;		// 10 door leading to this target if in another cell
										// possibly 1 more 32-bit member
	};

	TESScriptableForm	scriptable;			// 018
	TESIcon				icon;				// 024
	TESFullName			fullName;			// 030
	UInt8				questFlags;			// 03C
	UInt8				priority;			// 03D
	UInt8				pad0[2];			// 03E
	TList<StageEntry>	stageList;			// 040
	TList<TargetEntry>	targetList;			// 048
	UInt32				unk50;				// 050
	UInt32				unk54;				// 054
	ScriptEventList*	scriptEventList;	// 058
	UInt8				stageIndex;			// 05C
	UInt8				pad1[3];			// 05D
	BSString			editorName;			// 060
};
assert(sizeof(TESQuest) == 0x068);

class TESObject : public TESForm {
public:
	virtual void	Unk_37();
	virtual void	Unk_38();
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
};
assert(sizeof(TESObject) == 0x018);

class TESBoundObject : public TESObject {
public:
	virtual void	Unk_45();
	virtual void	Unk_46();
	virtual void	Unk_47();

	BoundObjectListHead* head;	// 018
	TESBoundObject*		 prev;	// 01C
	TESBoundObject*		 next;	// 020

};
assert(sizeof(TESBoundObject) == 0x024);

class TESBoundAnimObject : public TESBoundObject {};
assert(sizeof(TESBoundAnimObject) == 0x24);

class TESSoundFile : public BaseFormComponent {
public:
	BSString	fileName;	// 004
	BSString	editorID;	// 00C
};
assert(sizeof(TESSoundFile) == 0x014);

class TESSound : public TESBoundAnimObject {
public:
	enum SoundFlags {
		kFlag_RandomFrequencyShift  = 1,
		//...
		kFlag_Loop					= 1 << 4,
		kFlag_MenuSound				= 1 << 5,
		kFlag_2D					= 1 << 6,
		//...
	};
	
	void			SetFile(const char* Name) { soundFile.fileName.Set(Name); }

	TESSoundFile	soundFile;			// 024
	UInt8			minAttenuation;		// 038 not taken directly from CS
	UInt8			maxAttenuation;		// 039 likewise. Different ratios for each
	UInt8			frequencyAdjust;	// 03A
	UInt8			unk9;				// 03B
	UInt32			soundFlags;			// 03C
	UInt16			staticAttenuation;	// 040 - CS value * -100
	UInt16			unk12;				// 042 related to start/end times
};
assert(sizeof(TESSound) == 0x44);

class TESObjectLIGH : public TESBoundAnimObject {
public:
	enum LightFlags {
		kLightFlags_Dynamic =		0x001,
		kLightFlags_CanCarry =		0x002,
		kLightFlags_Negative =		0x004,
		kLightFlags_Flicker =		0x008,
		kLightFlags_OffByDefault =	0x020,
		kLightFlags_FlickerSlow =	0x040,
		kLightFlags_Pulse =			0x080,
		kLightFlags_PulseSlow =		0x100,
		kLightFlags_SpotLight =		0x200,
		kLightFlags_SpotShadow =	0x400,
	};

	TESFullName			fullName;	// 024
	TESModel			model;		// 030
	TESIcon				icon;		// 048
	TESScriptableForm	scriptable;	// 054
	TESWeightForm		weight;		// 060
	TESValueForm		value;		// 068
	UInt32				time;		// 070
	UInt32				radius;		// 074
	RGBA				colorRGB;	// 078
	UInt32				lightFlags;	// 07C
	float				fallOff;	// 080
	float				FOV;		// 084
	float				fade;		// 088
	TESSound*			loopSound;	// 08C
};
assert(sizeof(TESObjectLIGH) == 0x90);

class TESObjectWEAP : public TESBoundObject {
public:
	enum WeaponType {
		kWeapType_BladeOneHand = 0,
		kWeapType_BladeTwoHand,
		kWeapType_BluntOneHand,
		kWeapType_BluntTwoHand,
		kWeapType_Staff,
		kWeapType_Bow,
	};

	TESFullName			fullName;		// 024
	TESModel			model;			// 030
	TESIcon				icon;			// 048
	TESScriptableForm	scriptable;		// 054
	TESEnchantableForm	enchantable;	// 060
	TESValueForm		value;			// 070
	TESWeightForm		weight;			// 078
	TESHealthForm		health;			// 080
	TESAttackDamageForm	attackDmg;		// 088
	UInt32				weaponType;		// 090
	float				speed;			// 094
	float				reach;			// 098
	UInt32				ignoreNormalWeaponResist;	// 09C
};

class TESObjectCELL : public TESForm {
public:
	enum {
		kModified_DetachTime	= 0x08000000,
		kModified_CellFlags		= 0x00000008,
		kModified_SeenData		= 0x10000000,
		kModified_FullName		= 0x00000010,
		kModified_Ownership		= 0x00000020,
		kModified_Pathgrid		= 0x01000000,
	};
	enum {
		kFlags0_Interior			= 1 << 0,
		kFlags0_HasWater			= 1 << 1,
		kFlags0_Unk2				= 1 << 2,
		kFlags0_ForceHideLand		= 1 << 3,	// shared bit - for exterior
		kFlags0_OblivionInterior	= 1 << 3,	// shared bit - for interior
		kFlags0_Unk4				= 1 << 4,
		kFlags0_Public				= 1 << 5,
		kFlags0_HandChanged			= 1 << 6,
		kFlags0_BehaveLikeExterior	= 1 << 7,
	};

	struct CellCoordinates {
		SInt32	x;
		SInt32	y;
	};
	struct LightingData {
		RGBA		ambient;
		RGBA		directional;
		RGBA		fog;
		float		fogNear;
		float		fogFar;
		UInt32		rotXY;
		UInt32		rotZ;
		float		directionalFade;
		float		fogClipDistance;
	};

	float			GetWaterHeight() { return ThisCallF(0x004CACE0, this); }
	hkWorld*		GetHavokWorld() {
						ExtraHavok* extraHavok = (ExtraHavok*)extraDataList.GetExtraData(BSExtraData::ExtraDataType::kExtraData_Havok);
						return extraHavok && extraHavok->world ? (hkWorld*)extraHavok->world->hkObject : (hkWorld*)(*((bhkRefObject**)0x00B35C24))->hkObject;
					}

	TESFullName			 fullName;		// 018
	UInt8				 flags0;		// 024
	UInt8				 flags1;		// 025
	UInt8				 flags2;		// 026
	UInt8				 pad27;			// 027
	ExtraDataList		 extraDataList;	// 028 includes ExtraEditorID
	union {
		CellCoordinates* coords;		// if exterior
		LightingData*	 lighting;		// if interior
	};									// 3C
	TESObjectLAND*		 land;			// 040
	TESPathGrid*		 pathGrid;		// 044
	TList<TESObjectREFR> objectList;	// 048
	TESWorldSpace*		 worldSpace;	// 050
	NiNode*				 niNode;		// 054
};
assert(sizeof(TESObjectCELL) == 0x058);

class BaseProcess {
public:
	enum {
		kMovementFlag_Sneaking = 0x00000400,	// overridden by kMovementFlag_Swimming
		kMovementFlag_Swimming = 0x00000800
	};

	virtual void	Destructor();
	virtual void	Copy(BaseProcess* SourceProcess);
	virtual UInt32	GetProcessLevel();	// 0 - high, 3 - low
	virtual void	Unk_03(Actor* Act, UInt32 Arg1);
	virtual void	ManagePackProcedure(Actor* Act);
	virtual void	Unk_05(UInt32 arg0, UInt32 arg1);
	virtual bool	Unk_06(UInt32 arg0, UInt32 arg1);
	virtual void	SetCurHour(float Hour);
	virtual void	Unk_08();
	virtual bool	Unk_09();
	virtual float	GetCurHour();
	virtual UInt32	GetCurPackedDate();
	virtual void	SetCurPackedDate(UInt32 arg0);
	virtual UInt32	GetCurDay();
	virtual UInt32	GetCurMonth();
	virtual UInt32	GetCurYear();
	virtual void	Unk_10(UInt32 arg0);
	virtual UInt32	Unk_11();
	virtual void	Unk_12(UInt32 arg0);
	virtual void	Unk_13();
	virtual UInt32	Unk_14();
	virtual void	Unk_15(UInt32 arg0);
	virtual void	Unk_16(UInt32 arg0, UInt32 arg1);
	virtual void	Unk_17();
	virtual void	Unk_18(UInt32 arg0);
	virtual bool	Unk_19();
	virtual void	Unk_1A(UInt32 arg0);
	virtual bool	Unk_1B(UInt32 arg0, UInt32 arg1);
	virtual void	Unk_1C(UInt32 arg0, UInt32 arg1, UInt32 arg2);
	virtual UInt32	Unk_1D(UInt32 arg0);
	virtual UInt32	Unk_1E(UInt32 arg0);
	virtual float	Unk_1F(UInt32 arg0);
	virtual void	Unk_20(UInt32 arg0, UInt32 arg1);
	virtual void	Unk_21(UInt32 arg0, UInt32 arg1, UInt32 arg2);
	virtual bool	Unk_22();
	virtual void	Unk_23(UInt32 arg0);
	virtual void	Unk_24(UInt32 arg0);
	virtual void	Unk_25();
	virtual void	UpdateUnk088();
	virtual float	GetUnk088();
	virtual void	SetUnk088(float arg0);
	virtual void	Unk_29();
	virtual void*	SetDetected(Actor* detectedActor, UInt8 detectionState, bool hasLOS, SInt32 detectionLevel);
	virtual bool	Unk_2B();
	virtual void	Unk_2C(UInt32 arg0);

	virtual void	Unk_2C_1();	// added in 1.2 patch, all following virtuals must be shifted +1

	virtual void							Unk_2D(UInt32 arg0);
	virtual void							Unk_2E(UInt32 arg0);
	virtual bool							Unk_2F();
	virtual void							Unk_30(UInt32 arg0);
	virtual bool							Unk_31();
	virtual TESObjectREFR*					GetUnk02C();
	virtual void							SetUnk02C(TESObjectREFR* obj);
	virtual UInt32							Unk_34();
	virtual void							Unk_35(UInt32 arg0);
	virtual void							Unk_36(UInt32 arg0);
	virtual UInt32							Unk_37();
	virtual void							Unk_38(UInt32 arg0);
	virtual UInt32							Unk_39(UInt32 arg0);
	virtual UInt32							Unk_3A(UInt32 arg0);
	virtual InventoryChanges::EntryData*	GetEquippedWeaponData(bool arg0);
	virtual UInt32							Unk_3C(UInt32 arg0);
	virtual InventoryChanges::EntryData*	GetEquippedAmmoData(bool arg0);
	virtual UInt32							Unk_3E();
	virtual void							Unk_3F(UInt32 arg0);
	virtual bool							Unk_40(UInt32 arg0, UInt32 arg1);
	virtual bool							Unk_41(UInt32 arg0);
	virtual bool							Unk_42(UInt32 arg0);
	virtual bool							Unk_43(UInt32 arg0);
	virtual bool							Unk_44(UInt32 arg0);
	virtual UInt32							Unk_45(UInt32 arg0);
	virtual UInt32							Unk_46(UInt32 arg0);
	virtual UInt32							Unk_47(UInt32 arg0);
	virtual UInt32							Unk_48(UInt32 arg0);
	virtual UInt32							Unk_49(UInt32 arg0);
	virtual UInt32							Unk_4A(UInt32 arg0);
	virtual UInt32							Unk_4B(UInt32 arg0);
	virtual UInt32							Unk_4C(UInt32 arg0);
	virtual bool							Unk_4D();
	virtual bool							Unk_4E();
	virtual UInt8							GetUnk084();
	virtual void							SetUnk084(UInt8 arg0);
	virtual bool							GetUnk01E();
	virtual void							SetUnk01E(UInt32 arg0);
	virtual void							Unk_53(UInt32 arg0, UInt32 arg1, UInt32 arg2, UInt32 arg3);
	virtual void							SetUnk024(UInt32 arg);
	virtual void							Unk_55();
	virtual void							Unk_56();
	virtual void							Unk_57();
	virtual void							GetUnk028(float arg);
	virtual float							SetUnk028();
	virtual void							Unk_5A();
	virtual void							Unk_5B();
	virtual void							Unk_5C();
	virtual void							SetCurrentPackage(TESPackage* Package);
	virtual TESPackage::eProcedure			SetCurrentPackProcedure(TESPackage::eProcedure PackProcedure);
	virtual TESPackage::eProcedure			GetCurrentPackProcedure();
	virtual TESPackage*						GetCurrentPackage();	// returns MiddleHighProcess::pkg0C0 if not NULL, else BaseProcess::package
	virtual void							Unk_61(UInt32 arg0);			// marks ScriptEventList::kEvent_OnPackageDone
	virtual bhkCharacterProxy**				GetCharProxy(bhkCharacterProxy** characterProxy);	// increfs and returns the proxy (or sets to NULL)
	virtual void							Unk_63(void* obj);
	virtual void							Unk_64();
	virtual void							Unk_65();
	virtual void							Unk_66();
	virtual void							Unk_67();
	virtual void							Unk_68();
	virtual void							Unk_69();
	virtual void							Unk_6A();
	virtual void							Unk_6B();
	virtual void	Unk_6C();
	virtual void	Unk_6D();
	virtual void	Unk_6E();
	virtual void	Unk_6F();
	virtual void	Unk_70();
	virtual bool	GetLOS(UInt32 arg0, TESObjectREFR* target);	// arg0 unused
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
	virtual void	Unk_7E();
	virtual void	Unk_7F();
	virtual void	Unk_80();
	virtual void	Unk_81();
	virtual void	Unk_82();
	virtual UInt8	GetIsAlerted();
	virtual void	SetIsAlerted(UInt8 IsAlerted);
	virtual void	Unk_85();
	virtual void	Unk_86();
	virtual void	Unk_87();
	virtual void	Unk_88();
	virtual void	Unk_89();
	virtual void	Unk_8A();
	virtual void	Unk_8B();
	virtual void	Unk_8C();
	virtual void	Unk_8D();
	virtual void	Unk_8E();
	virtual void	Unk_8F();
	virtual void	Unk_90();
	virtual UInt8	GetUnk020();
	virtual void	SetUnk020(UInt8 arg);
	virtual void	Unk_93();
	virtual void	Unk_94();
	virtual void	Unk_95();
	virtual void	Unk_96();
	virtual void	Unk_97();
	virtual void	Unk_98();
	virtual void	Unk_99();
	virtual void	Unk_9A();
	virtual void	Unk_9B();
	virtual void	Unk_9C();
	virtual void	Unk_9D();
	virtual void	Unk_9E();
	virtual void	Unk_9F();
	virtual void	Unk_A0();
	virtual void	Unk_A1();
	virtual void	Unk_A2();
	virtual void	Unk_A3();
	virtual void	Unk_A4();
	virtual void	Unk_A5();
	virtual void	Unk_A6();
	virtual void	Unk_A7();
	virtual void	Unk_A8();
	virtual void	Unk_A9();
	virtual MagicItem*				GetQueuedMagicItem();	// returns MiddleHighProcess+144
	virtual void					Unk_AB();
	virtual void					Unk_AC();
	virtual void					Unk_AD();
	virtual void					Unk_AE();
	virtual UInt32					GetMovementFlags();
	virtual void					Unk_B0();
	virtual void					Unk_B1();
	virtual void					Unk_B2();
	virtual SInt16					GetCurrentAction();
	virtual BSAnimGroupSequence*	GetCurrentActionAnimSequence();
	virtual SInt16					SetCurrentAction(SInt16 action, BSAnimGroupSequence* sequence);
	virtual void					Unk_B6();
	virtual void					Unk_B7();
	virtual UInt8					GetKnockedState();
	virtual UInt8					SetKnockedState(UInt8 KnockedState);
	virtual void					Unk_BA();
	virtual void					Unk_BB();
	virtual void					KnockbackActor(Actor* target, float arg1, float arg2, float arg3, float arg4); // arg3 is a multiplier, arg4 appears to be base force to apply
	virtual void					Unk_BD();
	virtual UInt8					GetCombatMode();
	virtual UInt8					SetCombatMode(UInt8 CombatMode);
	virtual UInt8					GetWeaponOut();
	virtual UInt8					SetWeaponOut(UInt8 WeaponOut);
	virtual void					Unk_C2();
	virtual void*					Unk_C3();	// returns some pointer
	virtual void					Unk_C4();
	virtual void					Unk_C5();
	virtual void					SetUnk16C(UInt8 arg);
	virtual UInt8					GetUnk16C();
	virtual float					GetUnk0F8();
	virtual void					SetUnk0F8(float arg);
	virtual void					Unk_CA();
	virtual void					Unk_CB();
	virtual void					Unk_CC();
	virtual void					Unk_CD();
	virtual void					Unk_CE();
	virtual void					Unk_CF();
	virtual void					Unk_D0();
	virtual void					Unk_D1();
	virtual void					Unk_D2();
	virtual void					Unk_D3();
	virtual void					Unk_D4();
	virtual void					Unk_D5();
	virtual void					Unk_D6();
	virtual void					Unk_D7();
	virtual void					Unk_D8();
	virtual void					Unk_D9();
	virtual UInt8					GetSitSleepState();
	virtual void					Unk_DB();
	virtual void					Unk_DC();
	virtual TESObjectREFR*			GetFurniture();
	virtual void					Unk_DE();
	virtual void					Unk_DF();
	virtual void					Unk_E0();
	virtual void					Unk_E1();
	virtual void	Unk_E2();
	virtual UInt8	GetUnk01C();
	virtual void	SetUnk01C(UInt8 arg);
	virtual UInt8	GetUnk180();
	virtual void	SetUnk180(UInt8 arg);
	virtual void	Unk_E7();
	virtual void	Unk_E8();
	virtual void	Unk_E9();
	virtual float	GetLightAmount(Actor* actor, UInt32 unk1);
	virtual void	Unk_EB();
	virtual void*	GetDetectionState(Actor* target);	// returns HighProcess::DetectionList::Data *
	virtual void	Unk_ED();
	virtual void	Unk_EE();
	virtual void	Unk_EF();
	virtual void	Unk_F0();
	virtual void	Unk_F1();
	virtual void	Unk_F2();
	virtual void	Unk_F3();
	virtual void	Unk_F4();
	virtual void	Unk_F5();
	virtual void	Unk_F6();
	virtual void	Unk_F7();
	virtual void	Unk_F8();
	virtual void	Unk_F9();
	virtual void	Unk_FA();
	virtual void	Unk_FB();
	virtual void	Unk_FC();
	virtual void	Unk_FD();
	virtual void	Unk_FE();
	virtual void	Unk_FF();
	virtual void	Unk_100();
	virtual void	Unk_101();
	virtual void	CreatePath();
	virtual void	GetCurrentPath();
	virtual void	Unk_104();
	virtual void	Unk_105();
	virtual void	Unk_106();
	virtual void	Unk_107();
	virtual void	Unk_108();
	virtual void	Unk_109();
	virtual void	Unk_10A();
	virtual void	Unk_10B();
	virtual void	Unk_10C();
	virtual void	Unk_10D();
	virtual void	Unk_10E();
	virtual void	Unk_10F();
	virtual void	Unk_110();
	virtual void	Unk_111();
	virtual void	Unk_112();
	virtual void	Unk_113();
	virtual void	Unk_114();
	virtual void	Unk_115();
	virtual void	Unk_116();
	virtual void	Unk_117();
	virtual void	Unk_118();
	virtual void	Unk_119();
	virtual void	Unk_11A();
	virtual void	Unk_11B();
	virtual void	Unk_11C();
	virtual void	Unk_11D();
	virtual void	Unk_11E();
	virtual void	Unk_11F();
	virtual void	Unk_120();
	virtual void	Unk_121();
	virtual void	Unk_122();
	virtual void	Unk_123();
	virtual void	Unk_124();
	virtual void	Unk_125();
	virtual void	Unk_126();
	virtual void	Unk_127();
	virtual void	Unk_128();
	virtual void	Unk_129();
	virtual void	Unk_12A();
	virtual void	Unk_12B();
	virtual void	Unk_12C();
	virtual void	Unk_12D();
	virtual void	Unk_12E();
	virtual void	Unk_12F();
	virtual void	Unk_130();
	virtual void	Unk_131();
	virtual void	Unk_132();
	virtual void			Unk_133();
	virtual const char*		Unk_134();
	virtual void			Unk_135();
	virtual void	Unk_136();
	virtual void	Unk_137();
	virtual void	Unk_138();
	virtual void	Unk_139();
	virtual void	Unk_13A();
	virtual float	GetUnk08C();
	virtual void	SetUnk08C(float arg);
	virtual void	Unk_13D();
	virtual void	Unk_13E();
	virtual void	Unk_13F();
	virtual void	Unk_140();

	TESPackage::eProcedure	editorPackProcedure;	// 004
	TESPackage*				editorPackage;			// 008
};
assert(sizeof(BaseProcess) == 0x0C);

class LowProcess : public BaseProcess {
public:
	virtual void	Unk_141();
	virtual void	Unk_142();
	virtual void	Unk_143();
	virtual void	Unk_144();
	virtual void	Alarm(Actor* Act);
	virtual void	Unk_146();
	virtual void	Unk_147();
	virtual void	Unk_148();
	virtual void	Unk_149();
	virtual void	Unk_14A();
	virtual void	Unk_14B();
	virtual void	Unk_14C();
	virtual void	Unk_14D();
	virtual void	Unk_14E();
	virtual void	Unk_14F();
	virtual void	Unk_150();
	virtual void	Unk_151();
	virtual void	Unk_152();
	virtual void	Unk_153();
	virtual void	Unk_154();
	virtual void	Unk_155();
	virtual void	Unk_156();
	virtual UInt8	MountHorse(Actor* Act);				// 560
	virtual UInt8	DismountHorse(Actor* Act);			// 564
	virtual void	Unk_159();

	float			unk00C;				// 00C - initialized to -1
	float			unk010;				// 010
	float			curHour;			// 014 - initialized to -1
	UInt32			curPackedDate;		// 018 - (year << 13) | (month << 9) | day
	UInt8			unk01C;				// 01C
	UInt8			unk01D;				// 01D
	UInt8			unk01E;				// 01E
	UInt8			IsAlerted;			// 01F
	UInt8			unk020;				// 020
	UInt8			pad021[3];			// 021
	TESForm*		usedItem;			// 024 for idles like reading book, making potions, etc
	float			unk028;				// 028
	Actor*			Follow;				// 02C
	TESObjectREFR*	unk030;	// 030 seen XMarkerHeading refs here
	void*			pathing;			// 034
	UInt32			unk038;				// 038
	UInt32			unk03C;				// 03C
	UInt32			unk040;				// 040
	UInt32			unk044;				// 044
	UInt32			unk048;				// 048
	UInt32			unk04C;				// 04C
	UInt32			unk050;				// 050
	UInt32			unk054;				// 054
	UInt32			unk058;				// 058
	UInt32			unk05C;				// 05C
	UInt32			unk060;				// 060
	UInt32			unk064;				// 064
	UInt32			unk068;				// 068
	UInt32			unk06C;				// 06C
	ActorValues		avDamageModifiers;	// 070
	UInt8			unk084;				// 084
	UInt8			pad085[3];			// 085
	float			unk088;				// 088 - counter in seconds
	float			unk08C;				// 08C
};
assert(sizeof(LowProcess) == 0x90);

class MiddleLowProcess : public LowProcess {
public:
	virtual void	Unk_15A();

	UInt32			unk090;				// 090
	ActorValues		maxAVModifiers;		// 094
};
assert(sizeof(MiddleLowProcess) == 0xA8);

class MiddleHighProcess : public MiddleLowProcess {
public:
	virtual void	Unk_15B();
	virtual void	Unk_15C();
	virtual void	Unk_15D();
	virtual void	Unk_15E();
	virtual void	Unk_15F();
	virtual void	Dialogue(Actor* Act);
	virtual void	RemoveWornItems(Actor* Act, UInt8 Arg2, int Arg3);
	virtual void	Travel(Actor* Act, UInt8 Arg2, float Arg3, int Arg4 = 0);
	virtual void	Unk_163();
	virtual void	Unk_164();

	struct Unk128 {
		UInt32	unk0;	// 0
		UInt32	unk4;	// 4
		UInt32	unk8;	// 8
		UInt16	unkC;	// C
		UInt8	unkE;	// E
		UInt8	padF;	// F
	};

	struct EffectListNode {
		ActiveEffect*	effect;		// 0
		EffectListNode* next;		// 4
	};

	UInt32							unk0A8;					// 0A8
	UInt32							unk0AC;					// 0AC
	UInt32							unk0B0;					// 0B0
	UInt32							unk0B4;					// 0B4
	UInt32							unk0B8;					// 0B8
	float							unk0BC;					// 0BC
	TESPackage*						currentPackage;			// 0C0 if null, editorPackage applies
	UInt32							unk0C4;					// 0C4
	UInt8							unk0C8;					// 0C8
	UInt8							pad0C9[3];				// 0C9
	TESPackage::eProcedure			currentPackProcedure;	// 0CC
	UInt8							unk0D0;					// 0D0
	UInt8							pad0D0[15];				// 0D1 - never initialized
	UInt32							unk0E0;					// 0E0
	InventoryChanges::EntryData*	equippedWeaponData;		// 0E4
	InventoryChanges::EntryData*	equippedLightData;		// 0E8
	InventoryChanges::EntryData*	equippedAmmoData;		// 0EC
	InventoryChanges::EntryData*	equippedShieldData;		// 0F0
	UInt8							unk0F4;					// 0F4
	UInt8							unk0F5;					// 0F5
	UInt8							pad0F6[2];				// 0F6
	float							unk0F8;					// 0F8
	NiNode*							WeaponNode;				// 0FC
	NiNode*							TorchNode;				// 100
	NiNode*							LForearmTwistNode;		// 104
	NiNode*							SideWeaponNode;			// 108
	NiNode*							QuiverNode;				// 10C
	NiNode*							unk110;					// 110
	UInt8							CombatMode;				// 114
	UInt8							WeaponState;			// 115
	UInt8				pad116[2];	// 116
	bhkCharacterProxy*	charProxy;	// 118 - seen bhkCharacterProxy
	UInt8				KnockedState;	// 11C
	UInt8				SitSleepState;	// 11D
	UInt8				pad11E;		// 11E
	UInt8				pad11F;		// 11F
	TESObjectREFR*		Furniture;	// 120
	UInt8				unk124;		// 124 - init'd to 0x7F
	Unk128				unk128;		// 128
	UInt16				unk138;		// 138
	UInt8				pad13A[2];	// 13A
	UInt32				unk13C;		// 13C
	UInt32				unk140;		// 140
	MagicItem*			queuedMagicItem;	// 144 set before calling sub_69AF30 after Addspell cmd, unset upon return
	UInt32				unk148;		// 148
	UInt8				unk14C;		// 14C looks like true if casting, or possibly a casting state
	UInt8				pad14D[3];	// 14D
	UInt32				unk150;		// 150
	float				actorAlpha;	// 154 valid values 0-1
	float				unk158;		// 158
	NiExtraData*		unk15C;		// 15C seen BSFaceGenAnimationData*, reset when modifying character face
	UInt8				unk160;		// 160
	UInt8				unk161;		// 161
	UInt8				pad162[2];	// 162
	UInt32				unk164;		// 164
	UInt8				unk168;		// 168
	UInt8				unk169;		// 169
	UInt8				unk16A;		// 16A
	UInt8				unk16B;		// 16B
	UInt8				unk16C;		// 16C
	UInt8				unk16D;		// 16D
	UInt8				pad16E[2];	// 16E
	UInt32				unk170;		// 170
	EffectListNode*		effectList;	// 174
	UInt32				unk178;		// 178
	ActorAnimData*		animData;	// 17C
	UInt8				unk180;		// 180
	UInt8				pad181[3];	// 181
	NiObject*			unk184;	// 184 - seen BSShaderPPLightingProperty
	BSBound*			boundingBox;	// 188
};
assert(sizeof(MiddleHighProcess) == 0x18C);

class HighProcess : public MiddleHighProcess {
public:
	enum {
		kActionType_Default = 0,
		kActionType_Action,
		kActionType_Script,
		kActionType_Combat,
		kActionType_Dialog,
		kActionType_Max
	};

	enum {
		kDetectionState_Lost = 0,
		kDetectionState_Unseen,
		kDetectionState_Noticed,
		kDetectionState_Seen,
		kDetectionState_Max
	};

	struct DetectionList {
		struct Data {
			Actor*			actor;
			UInt8			detectionState;
			UInt8			pad04[3];
			UInt8			hasLOS;
			UInt8			pad08[3];
			SInt32			detectionLevel;
		};

		Data* data;
		DetectionList* next;

		Data* Info() const { return data; }
		DetectionList* Next() const { return next; }
	};

	// this appears to be a common linked list class
	struct Node190 {
		void* data;
		Node190* next;
	};

	struct Unk1BC {
		UInt32	unk0;
		UInt32	unk4;
		UInt32	unk8;
		UInt32	unkC;
	};

	struct Unk20C {
		UInt32	unk0;
		UInt32	unk4;
		UInt32	unk8;
	};

	struct Unk27C {
		UInt32	unk0;
		UInt32	unk4;
		UInt32	unk8;
	};

	enum AnimAction {
		kAnimAction_None = -1,
		kAnimAction_EquipWeapon,
		kAnimAction_UnequipWeapon,
		kAnimAction_Attack,
		kAnimAction_AttackFollowThrough,
		kAnimAction_AttackBow,
		kAnimAction_AttackBowArrowAttached,
		kAnimAction_Block,
		kAnimAction_Recoil,
		kAnimAction_Stagger,
		kAnimAction_Dodge,
		kAnimAction_LowerBodyAnim,
		kAnimAction_SpecialIdle,
		kAnimAction_ScriptAnimation,
	};

	enum {
		kMovement_Forward = 0x0001,
		kMovement_Backward = 0x0002,
		kMovement_Left = 0x0004,
		kMovement_Right = 0x0008,
		kMovement_TurnLeft = 0x0010,
		kMovement_TurnRight = 0x0020,
		kMovement_Walk = 0x0100,
		kMovement_Run = 0x0200,
		kMovement_Sneak = 0x0400,	// overridden by kMovementFlag_Swimming
		kMovement_Swim = 0x0800,
		kMovement_Jump = 0x1000, //Jump and above appear not to be used.
		kMovement_Fly = 0x2000,
		kMovement_Fall = 0x4000,
		kMovement_Slide = 0x8000,
	};
	
	enum SitSleep {
		kSitSleep_None = 0,
		kSitSleep_SittingIn = 3,
		kSitSleep_Sitting = 4,
		kSitSleep_SittingOut = 5,
		kSitSleep_SleepingIn = 8,
		kSitSleep_Sleeping = 9,
		kSitSleep_SleepingOut = 10,
	};

	void					PlaySoundITMTorchHeldLP(Actor* Act) { ThisCall(0x00633540, this, Act); }
	void					StopSoundITMTorchHeldLP() { ThisCall(0x006334D0, this, 1); }

	DetectionList*			detectionList;	// 18C
	Node190					unk190;		// 190
	UInt32					unk198;		// 198
	float					unk19C;		// 19C - idle chatter comment timer
	UInt8					unk1A0;		// 1A0
	UInt8					pad1A1[3];	// 1A1
	UInt32					unk1A4;		// 1A4
	UInt32					unk1A8;		// 1A8
	UInt32					unk1AC;		// 1AC
	UInt32					unk1B0;		// 1B0 - uninitialized
	UInt32					unk1B4;		// 1B4 - uninitialized
	UInt32					unk1B8;		// 1B8
	Unk1BC					unk1BC;		// 1BC
	UInt32					unk1CC;		// 1CC - uninitialized
	UInt8					unk1D0;		// 1D0
	UInt8					unk1D1;		// 1D1
	UInt32					unk1D4;		// 1D4
	UInt32					unk1D8;		// 1D8
	UInt32					unk1DC;		// 1DC
	UInt32					unk1E0;		// 1E0
	UInt8					unk1E4;		// 1E4
	UInt8					pad1E5[3];	// 1E5
	UInt32					unk1E8;		// 1E8
	void*					LODController;		// 1EC NiBSBoneLODController
	UInt32					unk1F0;								// 1F0
	SInt16					currentAction;		// 1F4
	UInt8					pad1F6[2];			// 1F6
	BSAnimGroupSequence*	currentActionAnim;	// 1F8
	UInt16					movementFlags;						// 1FC
	UInt8					pad1FE[2];	// 1FE
	UInt32					unk200;		// 200
	float					unk204;		// 204
	UInt16					unk208;		// 208
	UInt8					pad20A[2];	// 20A
	Unk20C					unk20C;		// 20C
	UInt32					unk218;		// 218
	float					unk21C;		// 21C
	UInt32					unk220;		// 220
	UInt32					lightSound; // 224 TESGameSound* (ITMTorchHeldLP sound). It is set/removed when equipping/unequipping torch.
	UInt8					unk228;		// 228
	UInt8					pad229[3];	// 229
	float					unk22C;		// 22C
	float					unk230;		// 230 - initialized to ((rand() % 5000) * .001) + 10
	UInt32					unk234;		// 234 - not initialized
	float					swimBreath;	// 238 - initialized to 0x41A00000
	UInt8					unk23C;		// 23C
	UInt8					unk23D[3];	// 23D
	UInt32					unk240;		// 240
	UInt8					unk244;		// 244
	UInt8					unk245[3];	// 245
	float					unk248;		// 248
	UInt8					unk24C;		// 24C
	UInt8					pad24D[3];	// 24D
	UInt32					unk250;		// 250
	UInt32					unk254;		// 254
	UInt32					unk258;		// 258
	UInt8					unk25C;		// 25C
	UInt8					unk25D;		// 25D
	UInt8					pad25E[2];	// 25E
	float					unk260;		// 260
	UInt32					unk264;		// 264
	NiObject*				unk268;	// 268 - decref'able pointer
	float					unk26C;		// 26C
	UInt32					unk270;		// 270
	UInt32					unk274;		// 274
	UInt8					unk278;		// 278
	UInt8					pad279[3];	// 279
	Unk27C					unk27C;		// 27C
	UInt32					unk288;		// 288
	UInt32					unk28C;		// 28C
	UInt8					unk290;		// 290
	UInt8					pad291[3];	// 291
	float					unk294;		// 294
	UInt32					unk298;		// 298
	UInt32					unk29C;		// 29C
	UInt32					unk2A0;		// 2A0
	UInt32					unk2A4;		// 2A4
	UInt8					unk2A8;		// 2A8
	UInt8					unk2A9;		// 2A9
	UInt8					pad2AA[2];	// 2AA
	float					unk2AC;		// 2AC
	float					unk2B0;		// 2B0
	UInt32					unk2B4;		// 2B4
	UInt8					unk2B8;		// 2B8
	UInt8					unk2B9;		// 2B9
	UInt8					pad2BA[2];	// 2BA
	UInt32					unk2BC;		// 2BC
	float					unk2C0;		// 2C0
	TESObjectREFR*			unk2C4;	// 2C4
	TESObjectREFR*			actionTarget[kActionType_Max];	// 2C8
	UInt8					actionActive[kActionType_Max];		// 2DC - true if the specified action is running
	UInt8					pad2E1[3];	// 2E1
	TESObjectREFR*			unk2E4;	// 2E4
	UInt8					unk2E8;		// 2E8
	UInt8					pad2E9[3];	// 2E9
};
assert(sizeof(HighProcess) == 0x2EC);

class HighProcessEx : public HighProcess {
public:
	enum State {
		StateNone,
		In,
		Out,
	};
	
	enum ObjectType {
		ObjectTypeNone,
		Weapon,
		Shield,
		Light,
	};

	InventoryChanges::EntryData*	EquippedLeftWeaponData;
	NiNode*							LeftWeaponObject;		// This should be storage extending the SkinInfo class, but the SkinInfo is saved in the savegame so i avoid to touch it for compatibility
	NiNode*							LeftWeaponObjectFirst;	// Same as above
	UInt8							OnProcessNew;
	UInt8							OnBackActionState;
	UInt8							OnBackState;
	UInt8							EquippingType;
	UInt8							LeftEquippingState;
	UInt8							LeftAnimState;
	UInt8							OnBeltActionState;
	UInt8							OnBeltState;
};
assert(sizeof(HighProcessEx) == 0x300);

class TESObjectREFR : public TESForm {
public:
	enum {
		kChanged_IsEmpty				= 0x00010000,
		kChanged_Inventory				= 0x08000000,
		kChanged_Animation				= 0x02000000,
		kChanged_Move					= 0x00000004,
		kChanged_HavokMove				= 0x00000008,
		kChanged_MapMarkerFlags			= 0x00000400,
		kChanged_HadHavokMoveFlag		= 0x00000800,
		kChanged_Scale					= 0x00000010,
		kChanged_DoorOpenDefaultState	= 0x00040000,
		kChanged_DoorOpenState			= 0x00080000,
		kChanged_DoorExtraTeleport		= 0x00100000,
		kChanged_ExtraOwner				= 0x00000080,
	};

	enum {
		kFlags_Persistent	= 0x00000400,
		kFlags_Disabled		= 0x00000800,
		kFlags_Unk00000002	= 0x00000002,
		kFlags_Deleted		= 0x00000020,
		kFlags_Unk128		= 0x80000000,
		kFlags_Temporary	= 0x00004000,
		kFlags_Taken		= kFlags_Deleted | kFlags_Unk00000002
	};

	virtual void			Unk_37();
	virtual void			Unk_38();	// 38
	virtual void			Unk_39();
	virtual void			Unk_3A();
	virtual float			GetScale();
	virtual void			GetStartingAngle(float* pos);
	virtual void			GetStartingPos(float* pos);
	virtual void			Unk_3E();
	virtual void			Unk_3F();
	virtual void			RemoveItem(TESForm* toRemove, ExtraDataList* extraList, int Quantity, UInt8 unk4, UInt8 unk5, TESObjectREFR* destRef, float* unk7, float* unk8, UInt8 unk9, UInt8 unk10);	// 40
	virtual void			Unk_41();
	virtual UInt8			Equip(TESForm* toEquip, int Quantity, ExtraDataList* extraList, UInt32 unk4);
	virtual UInt8			Unequip(TESForm* toUnequip, int Quantity, ExtraDataList* extraList);
	virtual void			Unk_44();
	virtual void			AddItem(TESForm* toAdd, ExtraDataList* extraList, int Quantity);
	virtual void			Unk_46();
	virtual void			Unk_47();
	virtual void			Unk_48();
	virtual MagicTarget*	GetMagicTarget();
	virtual void			Unk_4A();
	virtual void			Unk_4B();
	virtual void			Unk_4C();
	virtual void			Unk_4D();
	virtual void			Unk_4E();
	virtual void			Unk_4F();
	virtual void			Unk_50();	// 50
	virtual void			Unk_51();
	virtual void			Unk_52();			// inits animation-related data, and more
	virtual NiNode*			GenerateNiNode();
	virtual void			Set3D(NiNode* niNode);
	virtual NiNode*			GetNiNode();
	virtual void			Unk_56();
	virtual void			Unk_57(UInt32 arg0);
	virtual void			Unk_58();
	virtual ActorAnimData*	GetActorAnimData();
	virtual void			Unk_5A();
	virtual void			Unk_5B();
	virtual TESForm*		GetBaseForm();	// returns type this object references
	virtual NiPoint3*		GetPos();
	virtual void			Unk_5E();
	virtual void			Unk_5F();
	virtual UInt32			Unk_60(UInt32 Arg1);	// gets something from the ridden creature or actor
	virtual void			Unk_61();
	virtual void			Unk_62();
	virtual UInt8			GetSitSleepState(); // calls the Process::GetSitSleepState
	virtual bool			IsActor();
	virtual void			ChangeCell(TESObjectCELL* newCell);
	virtual UInt8			GetDead(UInt8 Arg1);
	virtual UInt8			GetKnockedState(); // calls the Process::GetKnockedState
	virtual void			Unk_68();
	virtual void			Unk_69();
	
	InventoryChanges::EntryData*	GetInventoryItem(UInt32 Index) { return (InventoryChanges::EntryData*)ThisCall(0x004D88F0, this, Index, 0); }

	TESChildCell		childCell;		// 018
	TESForm*			baseForm;		// 01C
	NiPoint3			rot;			// 020
	NiPoint3			pos;			// 02C
	float				scale;			// 038 
	NiNode*				niNode;			// 03C
	TESObjectCELL*		parentCell;		// 040
	ExtraDataList		extraDataList;	// 044
};
assert(sizeof(TESObjectREFR) == 0x058);

class MobileObject : public TESObjectREFR {
public:
	virtual void	Unk_6A();	// 6A
	virtual void	Unk_6B();
	virtual void	Unk_6C();
	virtual void	Move();
	virtual void	Jump();
	virtual void	Unk_6F();
	virtual void	Unk_70();	// 70
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
	virtual float	GetJumpScale();
	virtual void	Unk_7E();
	virtual void	Unk_7F();
	virtual void	Unk_80();	// 80
	virtual SInt32	GetFame();

	BaseProcess*	process;			// 058
};
assert(sizeof(MobileObject) == 0x05C);

class Actor : public MobileObject {
public:
	enum ActorVal {
		kActorVal_Strength = 0,		// 0x00
		kActorVal_Intelligence,
		kActorVal_Willpower,
		kActorVal_Agility,
		kActorVal_Speed,
		kActorVal_Endurance,		//0x05
		kActorVal_Personality,
		kActorVal_Luck,
		kActorVal_Health,
		kActorVal_Magicka,
		kActorVal_Stamina,			// 0x0a
		kActorVal_Encumbrance,
		kActorVal_Armorer,
		kActorVal_Athletics,
		kActorVal_Blade,
		kActorVal_Block,			// 0x0f
		kActorVal_Blunt,			// 0x10
		kActorVal_HandToHand,
		kActorVal_HeavyArmor,
		kActorVal_Alchemy,
		kActorVal_Alteration,
		kActorVal_Conjuration,		// 0x15
		kActorVal_Destruction,
		kActorVal_Illusion,
		kActorVal_Mysticism,
		kActorVal_Restoration,
		kActorVal_Acrobatics,		// 0x1a
		kActorVal_LightArmor,
		kActorVal_Marksman,
		kActorVal_Mercantile,
		kActorVal_Security,
		kActorVal_Sneak,			// 0x1f
		kActorVal_Speechcraft,		// 0x20
		kActorVal_Aggression,
		kActorVal_Confidence,
		kActorVal_Energy,
		kActorVal_Responsibility,
		kActorVal_Bounty,			// 0x25
		kActorVal_Fame,
		kActorVal_Infamy,
		kActorVal_MagickaMultiplier,
		kActorVal_NightEyeBonus,
		kActorVal_AttackBonus,		// 0x2a
		kActorVal_DefendBonus,
		kActorVal_CastingPenalty,
		kActorVal_Blindness,
		kActorVal_Chameleon,
		kActorVal_Invisibility,		// 0x2f
		kActorVal_Paralysis,		// 0x30
		kActorVal_Silence,
		kActorVal_Confusion,
		kActorVal_DetectItemRange,
		kActorVal_SpellAbsorbChance,
		kActorVal_SpellReflectChance,// 0x35
		kActorVal_SwimSpeedMultiplier,
		kActorVal_WaterBreathing,
		kActorVal_WaterWalking,
		kActorVal_StuntedMagicka,
		kActorVal_DetectLifeRange,	// 0x3a
		kActorVal_ReflectDamage,
		kActorVal_Telekinesis,
		kActorVal_ResistFire,
		kActorVal_ResistFrost,
		kActorVal_ResistDisease,	// 0x3f
		kActorVal_ResistMagic,		// 0x40
		kActorVal_ResistNormalWeapons,
		kActorVal_ResistParalysis,
		kActorVal_ResistPoison,
		kActorVal_ResistShock,
		kActorVal_Vampirism,		// 0x45
		kActorVal_Darkness,
		kActorVal_ResistWaterDamage,
		kActorVal_OblivionMax,
	};

	enum LifeState {
		kLifeState_Alive,
		kLifeState_Dying,
		kLifeState_Dead,
		kLifeState_Unconscious,
		kLifeState_Unk4,
		kLifeState_Restrained,
		kLifeState_UnconsciousEssential,
	};

	virtual SInt32	GetInfamy();
	virtual void	Resurrect(UInt8 Unk1, UInt8 Unk2, UInt8 Unk3);
	virtual void	Unk_84();
	virtual void	Unk_85();
	virtual void	Unk_86();
	virtual void	Unk_87();
	virtual void	ApplyDamage(float damage, float arg1, Actor* attacker);
	virtual void	Unk_89();
	virtual void	ProcessControls();
	virtual void	Unk_8B();
	virtual void	SetPackageDismount();
	virtual void	Unk_8D();
	virtual void	Unk_8E();
	virtual void	Unk_8F();
	virtual void	OnAlarmAttack(Actor* attackVictim, UInt32 arg1);	// 90 tries to send alarm when 'this' attacks victim
	virtual void	Unk_91();
	virtual void	Unk_92();	// SendTrespassAlarm
	virtual void	Unk_93();
	virtual void	Unk_94();
	virtual void	Unk_95();
	virtual void	Unk_96();
	virtual void	Unk_97();
	virtual bool	GetVampireHasFed();
	virtual void	SetVampireHasFed(bool bFed);
	virtual void	GetBirthSign();
	virtual void	Unk_9B();
	virtual void	Unk_9C();
	virtual void	Unk_9D();
	virtual void	Unk_9E();
	virtual void	Unk_9F();
	virtual void	Unk_A0();	// A0
	virtual UInt32	GetActorValue(UInt32 avCode);								// current, cumulative value
	virtual float	GetAV_F(UInt32 avCode);
	virtual void	SetAV_F(UInt32 avCode, float val);							// base value
	virtual void	SetActorValue(UInt32 avCode, UInt32 val);
	virtual void	ModMaxAV_F(UInt32 avCode, float amt, Actor* arg2);
	virtual void	ModMaxAV(UInt32 avCode, SInt32 amt, Actor* arg2);
	virtual void	ApplyScriptAVMod_F(UInt32 avCode, float amt, UInt32 arg2);	// script cmds Mod/ForceAV
	virtual void	ApplyScriptAVMod(UInt32 avCode, SInt32 amt, Actor* arg2);
	virtual void	DamageAV_F(UInt32 avCode, float amt, Actor* arg2);			// modifier <= 0, console ModAV cmd, damage health, etc
	virtual void	DamageAV(UInt32 value, UInt32 amount, UInt32 unk);
	virtual void	ModBaseAV_F(UInt32 avCode, float amt);
	virtual void	ModBaseAV(UInt32 avCode, SInt32 amt);
	virtual void	Unk_AD();
	virtual void	Unk_AE();
	virtual void	Unk_AF();
	virtual void	Unk_B0();	// B0
	virtual void	Unk_B1();
	virtual void	Unk_B2();
	virtual void	Unk_B3(TESObjectREFR* activatedRefr, UInt32 quantity); // called after Activate by TESForm::Unk33()
	virtual void	Unk_B4();
	virtual void	Unk_B5();
	virtual void	Unk_B6();
	virtual void	Unk_B7();	// AddSpell?
	virtual void	Unk_B8();	// RemoveSpell?
	virtual void	Unk_B9();
	virtual void	Unk_BA();
	virtual void	Unk_BB();
	virtual void	Unk_BC();
	virtual void	Unk_BD();
	virtual void	Unk_BE();
	virtual void	Unk_BF();
	virtual void	Unk_C0();	// C0
	virtual void	Unk_C1();
	virtual void	Unk_C2();
	virtual void	Unk_C3();
	virtual void	ManageAlarm();
	virtual void	Unk_C5();
	virtual void	Unk_C6();
	virtual void	Unk_C7();
	virtual void	AddPackageWakeUp();
	virtual void	Unk_C9();
	virtual void	Unk_CA();
	virtual void	Unk_CB();
	virtual CombatController* GetCombatController();
	virtual bool	IsInCombat(bool unk);
	virtual TESForm* GetCombatTarget();
	virtual void	Unk_CF();
	virtual void	Unk_D0();	// D0
	virtual void	Unk_D1();
	virtual void	Unk_D2();
	virtual void	Unk_D3();
	virtual bool	IsYielding();
	virtual void	Unk_D5();
	virtual void	Unk_D6();
	virtual void	Unk_D7();
	virtual void	Unk_D8();
	virtual void	Unk_D9();
	virtual void	Unk_DA();
	virtual void	Unk_DB();
	virtual void	Unk_DC();
	virtual void	Unk_DD();
	virtual void	Unk_DE();
	virtual void	Unk_DF();
	virtual Creature* GetMountedHorse();	// E0 returns this->horseOrRider, only for Character
	virtual void	Unk_E1();
	virtual void	Unk_E2();
	virtual void	Unk_E3();
	virtual void	Unk_E4();
	virtual void	Unk_E5();
	virtual void	Unk_E6();
	virtual void	ModExperience(UInt32 actorValue, UInt32 scaleIndex, float baseDelta);
	virtual void	Unk_E8();
	virtual void	Unk_E9();
	virtual void	Unk_EA();
	virtual void	AttackHandling(UInt32 unused, TESObjectREFR* arrowRef, TESObjectREFR* target);	// args all null for melee attacks
	virtual void	Unk_EC();
	virtual void	Unk_ED();	// something with blocking
	virtual void	OnHealthDamage(Actor* attacker, float damage);

	UInt32			GetBaseActorValue(ActorVal Code) { return ThisCall(0x005F1910, this, Code); }
	void			EquipItem(TESForm* Form, UInt32 Quantity, ExtraDataList* List) { ThisCall(0x005FAEA0, this, Form, Quantity, List, 0, false); }
	void			UnequipItem(TESForm* Form, UInt32 Quantity, ExtraDataList* List) { ThisCall(0x005F2E70, this, Form, Quantity, List, 0, false, 0); }
	bool			IsFemale() { return ThisCall(0x005E1DF0, this); }

	MagicCaster		magicCaster;					// 05C
	MagicTarget		magicTarget;					// 068
	UInt32			unk070;							// 070
	UInt32			unk074;							// 074
	UInt8			unk078;							// 078
	UInt8			pad078[3];						// 079
	Actor*			unk07C;							// 07C
	UInt32			unk080;							// 080
	float			unk084;							// 084
	ActorValues		avModifiers;					// 088
	UInt32			greaterPowerList[2];			// 09C PowerListEntry
	UInt32			unk0A4;							// 0A4
	UInt32			unk0A8;							// 0A8
	float			unk0AC;							// 0AC
	UInt32			lifeState;						// 0B0
	UInt32			unk0B4;							// 0B4
	UInt32			unk0B8;							// 0B8
	float			unk0BC;							// 0BC
	UInt8			unk0C0;							// 0C0
	UInt8			pad0C0[3];						// 0C1
	UInt32			unk0C4;							// 0C4
	UInt8			unk0C8;							// 0C8
	UInt8			unk0C9;							// 0C9
	UInt8			unk0CA;							// 0CA
	UInt8			pad0C8;							// 0CB
	TESObjectREFR*	unk0CC;							// 0CC
	UInt32			unk0D0;							// 0D0
	Actor*			horseOrRider;					// 0D4 For Character, currently ridden horse; For horse (Creature), currently riding Character
	UInt8			unk0D8;							// 0D8
	UInt8			pad0D8[3];						// 0D9
	float			unk0DC;							// 0DC
	UInt32			unk0E0;							// 0E0
	Actor*			unk0E4;							// 0E4
	UInt32			unk0E8;							// 0E8
	UInt32			unk0EC;							// 0EC
	UInt32			unk0F0;							// 0F0
	float			unk0F4;							// 0F4
	UInt32			unk0F8;							// 0F8
	UInt8			unk0FC;							// 0FC
	UInt8			unk0FD;							// 0FD //It is set to 0 when Process::GetCurDay == TimeGlobals::GetDay
	UInt8			pad0FC[2];						// 0FE
	float			unk100;							// 100
};
assert(sizeof(Actor) == 0x104);

class Creature : public Actor {
public:
	UInt32		unk104;				// 104
};
assert(sizeof(Creature) == 0x108);

class Character : public Actor {
public:
	SkinInfo*	ActorSkinInfo;						// 104
	UInt32		unk108;								// 108
};
assert(sizeof(Character) == 0x10C);

class PlayerCharacter : public Character {
public:
	enum {
		kMiscStat_DaysInPrison = 0,
		kMiscStat_DaysPassed,
		kMiscStat_SkillIncreases,
		kMiscStat_TrainingSessions,
		kMiscStat_LargestBounty,
		kMiscStat_CreaturesKilled,
		kMiscStat_PeopleKilled,
		kMiscStat_PlacesDiscovered,
		kMiscStat_LocksPicked,
		kMiscStat_LockpicksBroken,
		kMiscStat_SoulsTrapped,	// 10
		kMiscStat_IngredientsEaten,
		kMiscStat_PotionsMade,
		kMiscStat_OblivionGatesShut,
		kMiscStat_HorsesOwned,
		kMiscStat_HousesOwned,
		kMiscStat_StoresInvestedIn,
		kMiscStat_BooksRead,
		kMiscStat_SkillBooksRead,
		kMiscStat_ArtifactsFound,
		kMiscStat_HoursSlept,	// 20
		kMiscStat_HoursWaited,
		kMiscStat_DaysAsAVampire,
		kMiscStat_LastDayAsAVampire,
		kMiscStat_PeopleFedOn,
		kMiscStat_JokesTold,
		kMiscStat_DiseasesContracted,
		kMiscStat_NirnrootsFound,
		kMiscStat_ItemsStolen,
		kMiscStat_ItemsPickpocketed,
		kMiscStat_Trespasses,	// 30
		kMiscStat_Assaults,
		kMiscStat_Murders,
		kMiscStat_HorsesStolen,
		kMiscStat_Max			// 34
	};

	struct TopicList {
		TESTopic* topic;
		TopicList* next;
	};

	struct Unk5B0 {
		float unk[21];
	};
	
	bool			IsAiming() { SInt16 CurrentAction = ((HighProcess*)process)->currentAction; return (CurrentAction == HighProcess::kAnimAction_AttackBow || CurrentAction == HighProcess::kAnimAction_AttackBowArrowAttached); }
	TESWorldSpace*  GetWorldSpace() { return (parentCell != NULL ? parentCell->worldSpace : NULL); }
	TESRegion*		GetRegion() { return currentRegion; }
	void			UpdateInventory() { void (*UpdateInventoryMenu)() = (void(*)())0x005AADC0; ThisCall(0x00668CC0, this); ThisCall(0x006575B0, this->process, this, 1, 0, 0); ThisCall(0x0060E260, this); UpdateInventoryMenu(); }
	bool			IsMoving() { return (process->GetMovementFlags() & 0x800); }
	bool			IsAlive() { return !GetDead(0); }

	UInt8			unk10C;										// 10C
	UInt8			pad10D[3];									// 10D
	UInt32			unk110;										// 110
	UInt8			unk114;										// 114
	UInt8			unk115;										// 115
	UInt8			isInSEWorld;								// 116
	UInt8			unk117;										// 117
	DialoguePackage* dialoguePackage;							// 118
	UInt32			unk11C;										// 11C
	UInt32			unk120;										// 120
	UInt32			unk124;										// 124
	UInt32			unk128;										// 128
	UInt8			isMovingToNewSpace;							// 12C
	UInt8			pad12C[3];
	float			skillExp[21];								// 130	current experience for each skill
	UInt32			majorSkillAdvances;							// 184
	UInt32			skillAdv[21];								// 188 number of advances for each skill
	UInt8			bCanLevelUp;								// 1DC
	UInt8			unk1DD[3];									// 1DD
	Creature*		lastRiddenHorse;							// 1E0
	UInt32			unk1E4;										// 1E4
	UInt32			unk1E8;										// 1E8
	UInt32			unk1EC;										// 1EC
	UInt32			unk1F0;										// 1F0
	UInt32			unk1F4;										// 1F4
	UInt32			unk1F8;										// 1F8
	UInt32			unk1FC;										// 1FC
	UInt32			unk200;										// 200
	float			maxAVModifiers[kActorVal_OblivionMax];		// 204
	float			scriptAVModifiers[kActorVal_OblivionMax];	// 324
	float			unk444;							// 444
	float			unk448;							// 448
	float			unk44C;							// 44C
	UInt32			unk450[(0x570 - 0x450) >> 2];	// 450
	TESObjectREFR*	lastActivatedLoadDoor;			// 570 - most recently activated load door
	UInt32			unk574;							// 574
	UInt32			unk578;							// 578
	UInt32			unk57CState;					// 57C
	UInt32			unk580;							// 580
	UInt32			unk584;							// 584
	UInt8			isThirdPerson;					// 588
	UInt8			DisableFading;					// 589
	UInt8			unk58A;							// 58A
	UInt8			AlwaysRun;						// 58B
	UInt8			AutoMove;						// 58C
	UInt8			pad58D[3];						// 58D
	UInt32			HoursToSleep;					// 590
	UInt8			isSleeping;						// 594
	UInt8			pad594[3];
	float			worldFoV;						// 598
	float			unk59C;							// 59C
	float			unk5A0;							// 5A0
	float			unk5A4;							// 5A4
	UInt32			unk5A8;							// 5A8
	UInt32			unk5AC;							// 5AC
	Unk5B0*			unk5B0;							// 5B0 - freed when running SetInCharGen 0
	UInt8**			attributeBonuses;				// 5B4
	UInt16			unk5B8;							// 5B8
	UInt8			unk5BA;							// 5BA
	UInt8			unk5BB;							// 5BB
	UInt32			trainingSessionsUsed;			// 5BC reset on level-up
	UInt8			unk5C0;							// 5C0
	UInt8			pad5C0[3];
	TESObjectREFR*	ObjectToActivate;				// 5C4
	SkinInfo*		firstPersonSkinInfo;			// 5C8
	ActorAnimData*	firstPersonAnimData;			// 5CC
	NiNode*			firstPersonNiNode;				// 5D0
	float			firstPersonNiNodeTranslateZ;	// 5D4
	NiNode*			inventoryPC;					// 5D8
	ActorAnimData*	defaultAnimData;				// 5DC
	UInt32			unk5E0;							// 5E0
	TESTopic*		unk5E4;							// 5E4
	UInt32			unk5E8;							// 5E8
	UInt32			unk5EC;							// 5EC
	UInt32			unk5F0;							// 5F0
	TESQuest*		activeQuest;					// 5F4
	UInt32			unk5F8;							// 5F8
	UInt32			unk5FC;							// 5FC
	UInt32			unk600;							// 600
	UInt32			unk604;							// 604
	UInt32			JailedState;					// 608
	UInt32			unk60C;							// 60C
	UInt8			unk610;							// 610
	UInt8			isAMurderer;					// 611
	UInt8			pad612[2];						// 612
	UInt32			AmountStolenSold;				// 614
	float			unk618;							// 618
	float			unk61C;							// 61C
	UInt32			unk620;							// 620
	MagicItem*		activeMagicItem;				// 624
	TESObjectBOOK*	book;							// 628
	UInt32			unk62C;							// 62C
	UInt32			unk630;							// 630
	UInt32			unk634;							// 634
	UInt32			unk638;							// 638
	UInt32			unk63C;							// 63C
	float			unk640;							// 640
	BirthSign*		birthSign;						// 644
	UInt32			unk648[(0x650 - 0x648) >> 2];	// 648
	TESClass*		wtfClass;						// 650 - this is not the player class! use OBLIVION_CAST(this, TESForm, TESNPC)->npcClass
	UInt32			unk654;							// 654
	UInt32			miscStats[kMiscStat_Max];		// 658
	AlchemyItem*	alchemyItem;					// 6E0
	UInt8			bVampireHasFed; 				// 6E4 returned by vtbl+260, set by vtbl+264
	UInt8			isInCharGen;					// 6E5
	UInt8			pad6E6[2];						// 6E6
	TESRegion*		currentRegion;					// 6E8
	UInt32			unk6EC;							// 6EC
	UInt32			unk6F0;							// 6F0
	UInt32			unk6F4;							// 6F4
	UInt32			unk6F8;							// 6F8
	UInt32			unk6FC;							// 6FC
	UInt32			unk700;							// 700
	UInt32			unk704;							// 704
	UInt32			unk708;							// 708
	UInt32			unk70C;							// 70C
	UInt32			TickCount;						// 710
	UInt32			unk714;							// 714
	UInt32			unk718;							// 718
	UInt8			isTravelPackage;				// 71C
	UInt8			isWakeUpPackage;				// 71D
	UInt8			pad71E[2];
	UInt32			unk720;							// 720
	UInt32			unk724;							// 724
	UInt32			unk728;							// 728
	UInt32			unk72C;							// 72C
	UInt32			unk730;							// 730
	float			gameDifficultyLevel;			// 734 ranges from -1 to 1
	UInt32			unk738;							// 738
	UInt32			unk73C;							// 73C
	UInt32			unk740;							// 740
	UInt32			unk744;							// 744
	UInt8			isFlyCam;						// 748
	UInt8			pad748[3];						// 749
	float			FlyCamRotZ;						// 74C
	float			FlyCamRotX;						// 750
	float			FlyCamPosX;						// 754
	float			FlyCamPosY;						// 758
	float			FlyCamPosZ;						// 75C
	UInt32			unk760[(0x7A4 - 0x760) >> 2];	// 760
	float			requiredSkillExp[21];			// 7A4 total amt of exp needed to increase each skill
	UInt32			unk7F8;							// 7F8
	float			unk7FC;							// 7FC
	float			unk800;							// 800
};
assert(sizeof(PlayerCharacter) == 0x804);

class PlayerCharacterEx : public PlayerCharacter {
public:
	NiPoint3	ReticleOffset;
};
assert(sizeof(PlayerCharacterEx) == 0x810);

class SkinInfo {
public:
	NiNode*			Bip01Node;				// 000
	UInt32			unk004;
	NiNode*			HeadNode;				// 008
	UInt32			unk00C;
	NiNode*			Finger1Node;			// 010
	UInt32			unk014;
	NiNode*			LFinger1Node;			// 018
	UInt32			unk01C;
	NiNode*			WeaponNode;				// 020
	UInt32			unk024;
	NiNode*			BackWeaponNode;			// 028
	UInt32			unk02C;
	NiNode*			SideWeaponNode;			// 030
	UInt32			unk034;
	NiNode*			QuiverNode;				// 038
	UInt32			unk03C;
	NiNode*			LForearmTwistNode;		// 040
	UInt32			unk044;
	NiNode*			TorchNode;				// 048
	UInt32			unk04C;
	UInt32			unk050;
	Actor*			Actor054;				// 054
	UInt32			unk058;
	TESForm*		unk05C;
	TESModel*		unk060;
	NiNode*			unk064;
	UInt32			unk068;
	TESForm*		UpperBodyForm;			// 06C
	TESModel*		UpperBodyModel;			// 070
	NiNode*			UpperBodyObject;		// 074
	UInt32			unk078;
	TESForm*		LowerBodyForm;			// 07C
	TESModel*		LowerBodyModel;			// 080
	NiNode*			LowerBodyObject;		// 084
	UInt32			unk088;
	TESForm*		HandForm;				// 08C
	TESModel*		HandModel;				// 090
	NiNode*			HandObject;				// 094
	UInt32			unk098;
	TESForm*		FootForm;				// 09C
	TESModel*		FootModel;				// 0A0
	NiNode*			FootObject;				// 0A4
	UInt32			unk0A8;
	UInt32			unk0AC;
	UInt32			unk0B0;
	NiNode*			unk0B4;
	UInt32			unk0B8;
	UInt32			unk0BC;
	UInt32			unk0C0;
	NiNode*			unk0C4;
	UInt32			unk0C8;
	UInt32			unk0CC;
	UInt32			unk0D0;
	NiNode*			unk0D4;
	UInt32			unk0D8;
	TESObjectWEAP*	WeaponForm;				// 0DC
	TESModel*		WeaponModel;			// 0E0
	NiNode*			WeaponObject;			// 0E4
	UInt32			unk0E8;
	TESForm*		unk0EC;
	TESModel*		unk0F0;
	NiNode*			unk0F4;
	UInt32			unk0F8;
	TESForm*		unk0FC;
	TESModel*		unk100;
	NiNode*			unk104;
	UInt32			unk108;
	TESForm*		AmmoForm;				// 10C
	TESModel*		AmmoModel;				// 110
	NiNode*			AmmoObject;				// 114
	UInt32			unk118;
	TESObjectARMO*	ShieldForm;				// 11C
	TESModel*		ShieldModel;			// 120
	NiNode*			ShieldObject;			// 124
	UInt32			unk128;
	TESObjectLIGH*	LightForm;				// 12C
	TESModel*		LightModel;				// 130
	NiNode*			LightObject;			// 134
	UInt32			unk138;
	UInt32			unk13C;
	UInt32			unk140;
	UInt32			unk144;
	UInt32			unk148;
	UInt32			unk14C;
	Actor*			Actor150;				// 150
};
assert(sizeof(SkinInfo) == 0x154);

class AnimSequenceBase {
public:
	virtual void					Destructor(UInt8 Arg);
	virtual void					AddAnimGroupSequence(BSAnimGroupSequence* AnimGroupSequence);
	virtual void					Unk_02();
	virtual UInt8					IsSingle();
	virtual BSAnimGroupSequence*	GetAnimGroupSequence(int Index); // Index is not used if Single (returns the anim); Index = -1 returns a random anim in the NiTList<BSAnimGroupSequence>* for Multiple
	virtual void					Unk_05();
};
assert(sizeof(AnimSequenceBase) == 0x004);

class AnimSequenceSingle : public AnimSequenceBase {
public:
	BSAnimGroupSequence*	Anim;		// 04
};
assert(sizeof(AnimSequenceSingle) == 0x008);

class AnimSequenceSingleEx : public AnimSequenceSingle {
public:
	BSAnimGroupSequence*	ORAnim;		// 0C
};
assert(sizeof(AnimSequenceSingleEx) == 0x00C);

class AnimSequenceMultiple : public AnimSequenceBase {
public:
	NiTList<BSAnimGroupSequence>* Anims;	// 04
};
assert(sizeof(AnimSequenceMultiple) == 0x008);

class AnimSequenceMultipleEx : public AnimSequenceMultiple {
public:
	BSAnimGroupSequence*	ORAnim;		// 0C
};
assert(sizeof(AnimSequenceMultipleEx) == 0x00C);

class ActorAnimData {
public:
	void						QueueIdle(TESIdleForm* Idle, Actor* Act, UInt32 Flags) { ThisCall(0x00477DB0, this, Idle, Act, Flags, 3); }

	UInt32						unk00;					//00 no virtual table
	NiNode*						RootNode;				//04 seen BSFadeNode for 3rd Person, NiNode for 1st
	NiNode*						AccumNode;				//08
	UInt32						unk0C;					//0C
	UInt32						unk10;					//10
	UInt32						unk14;					//14
	UInt32						unk18;					//18
	UInt32						unk1C;					//1C
	UInt32						unk20;					//20
	NiNode*						nBip01;					//24
	NiNode*						nLForearm;				//28
	NiNode*						nTorch;					//2C
	NiNode*						nWeapon;				//30
	NiNode*						nHead;					//34
	float						unk38;					//38
	UInt16						animsMapKey[5];			//3C
	UInt16						unk44;					//44
	int							unk48State[5];			//48
	UInt32						unk5C;					//5C
	UInt32						unk60;					//60
	UInt32						unk64;					//64
	UInt32						unk68;					//68
	UInt32						unk6C;					//6C
	UInt32						unk70;					//70
	UInt32						unk74;					//74
	UInt16						unk78;					//78
	UInt8						pad78[2];
	UInt32						unk7C;					//7C
	UInt32						unk80;					//80
	UInt32						unk84;					//84
	UInt32						unk88;					//88
	UInt32						unk8C;					//8C
	UInt8						unk90;					//90
	UInt8						pad90[3];
	float						unk94;					//94
	NiControllerManager*		manager;				//98
	NiTMap<UInt32, AnimSequenceBase>*	animsMap;		//9C
	BSAnimGroupSequence*		animSequences[5];		//A0
	ModelKF*					modelB4;				//B4
	ModelKF*					modelB8;				//B8
	float						unkBC;					//BC
	float						unkC0;					//C0
	UInt8						unkC4;					//C4
	UInt8						padC4[2];
	UInt32						unkC8[3];				//C8
	UInt32						unkD4;					//D4
	void*						unkD8;					//D8 looks like struct with idle anim transform data
};
assert(sizeof(ActorAnimData) == 0xDC);

class ActorAnimDataEx : public ActorAnimData {
public:
	NiTList<BSAnimGroupSequence>*	ORAnims;	// DC
};
assert(sizeof(ActorAnimDataEx) == 0xE0);

class TESAnimGroup : public NiRefObject {
public:
	enum AnimGroup {
		kAnimGroup_Idle = 0,
		kAnimGroup_DynamicIdle,
		kAnimGroup_SpecialIdle,
		kAnimGroup_Forward,
		kAnimGroup_Backward,
		kAnimGroup_Left,
		kAnimGroup_Right,
		kAnimGroup_FastForward,
		kAnimGroup_FastBackward,
		kAnimGroup_FastLeft,
		kAnimGroup_FastRight,
		kAnimGroup_DodgeForward,
		kAnimGroup_DodgeBack,
		kAnimGroup_DodgeLeft,
		kAnimGroup_DodgeRight,
		kAnimGroup_TurnLeft,
		kAnimGroup_TurnRight,
		kAnimGroup_Equip,
		kAnimGroup_Unequip,
		kAnimGroup_AttackBow,
		kAnimGroup_AttackLeft,
		kAnimGroup_AttackRight,
		kAnimGroup_AttackPower,
		kAnimGroup_AttackForwardPower,
		kAnimGroup_AttackBackPower,
		kAnimGroup_AttackLeftPower,
		kAnimGroup_AttackRightPower,
		kAnimGroup_BlockIdle,
		kAnimGroup_BlockHit,
		kAnimGroup_BlockAttack,
		kAnimGroup_Recoil,
		kAnimGroup_Stagger,
		kAnimGroup_Death,
		kAnimGroup_TorchIdle,
		kAnimGroup_CastSelf,
		kAnimGroup_CastTouch,
		kAnimGroup_CastTarget,
		kAnimGroup_CastSelfAlt,
		kAnimGroup_CastTouchAlt,
		kAnimGroup_CastTargetAlt,
		kAnimGroup_JumpStart,
		kAnimGroup_JumpLoop,
		kAnimGroup_JumpLand,
		kAnimGroup_Max,
	};

	UInt8		animGroup;		//008 This value is used with the animType (as UInt16) as key for the ActorAnimData NiTPointerMap<AnimSequenceBase>*
	UInt8		animType;		//009
	UInt8		animOR;			//00A Oblivion doesn't use this. Used by Oblivion Reloaded.
	UInt8		pad008;			//00B
	UInt32		numFrames;		//00C count of group frames (Start, Detach, Attack, End, etc)
	float**		frameData;		//010 pointer to float array of group frame times (size numFrames)
	UInt32		unk014;			//014
	UInt32		unk018;			//018
	UInt32		unk01C;			//01C
	UInt8		unk020;			//020
	UInt8		unk021;
	UInt8		pad022[2];
	UInt32		unk024;			//024
	void*		unk028;			//028
};
assert(sizeof(TESAnimGroup) == 0x02C);

class SkyObject {
public:
	virtual NiNode* GetObjectNode();						
	virtual void	Initialize(UInt32 u1);			
	virtual void	func_03(UInt32 u1, UInt32 u2);	

	NiNode*			RootNode;						// 04	
};
assert(sizeof(SkyObject) == 0x008);

class Sun : public SkyObject {
public:
	NiBillboardNode*	SunBillboard;			// 08
	NiBillboardNode*	SunGlareBillboard;		// 0C
	NiGeometry*			SunGeometry;			// 10 NiTriShape*
	NiGeometry*			SunGlareGeometry;		// 14 NiTriShape*
	NiTArray<NiPick*>*	SunPickList;			// 18 NiPick::Record
	NiDirectionalLight* SunDirLight;			// 1C
	float				unk20;					// 20
	UInt8				unk24;					// 24
	UInt8				pad25[3];				// 25
};
assert(sizeof(Sun) == 0x028);

class Atmosphere : public SkyObject {
public:
	NiAVObject*		Mesh;					// 08
	BSFogProperty*	fogProperty;			// 0C
	UInt32			unk10;					// 10
	NiNode*			Quad;					// 14
	UInt8			unk18;					// 18
	UInt8			pad18[3];

};
assert(sizeof(Atmosphere) == 0x01C);

class Stars : public SkyObject {
public:
	UInt32			unk08;					// 08
	float			unk0C;					// 0C
};
assert(sizeof(Stars) == 0x010);

class Clouds : public SkyObject {
public:
	UInt32			unk08;					// 08
	UInt32			unk0C;					// 0C
	UInt32			unk10;					// 10
	UInt32			unk14;					// 14
};
assert(sizeof(Clouds) == 0x018);

class Moon : public SkyObject {
public:
	NiNode*			MoonNode;				// 08
	NiNode*			ShadowNode;				// 0C
	NiTriShape*		MoonMesh;				// 10
	NiTriShape*		ShadowMesh;				// 14
	char*			texture_full;			// 18
	UInt32			unk1C;					// 1C
	char*			texture_three_wan;		// 20
	UInt32			unk24;					// 24
	char*			texture_half_wan;		// 28
	UInt32			unk2C;					// 2C
	char*			texture_one_wan;		// 30
	UInt32			unk34;					// 34
	UInt32			unk38;					// 38
	UInt32			unk3C;					// 3C
	char*			texture_one_wax;		// 40
	UInt32			unk44;					// 44
	char*			texture_half_wax;		// 48
	UInt32			unk4C;					// 4C
	char*			texture_three_wax;		// 50
	UInt32			unk54;					// 54
	float			unk58;					// 58
	float			unk5C;					// 5C
	float			unk60;					// 60
	float			unk64;					// 64
	float			unk68;					// 68
	UInt32			unk6C;					// 6C
	UInt32			unk70;					// 70
	float			unk74;					// 74
	float			unk78;					// 78
};
assert(sizeof(Moon) == 0x07C);

class Precipitation {
public:
	void**			_vtbl;					// 00
	NiNode*			CurrentNode;			// 04
	NiNode*			LastNode;				// 08
	NiNode*			WeatherNode;			// 0C
	float			unk10;					// 10
	TESModel*		Model;					// 14
};
assert(sizeof(Precipitation) == 0x018);

class Sky {
public:
	void ForceWeather(TESWeather* Weather) { ThisCall(0x00542260, this, Weather, 0); }

	void**			_vtbl;							// 000
	NiNode*			nodeSkyRoot;					// 004
	NiNode*			nodeMoonsRoot;					// 008
	TESClimate*		firstClimate;					// 00C
	TESWeather*		firstWeather;					// 010
	TESWeather*		secondWeather;					// 014 Previous weather when in transition
	TESWeather*		weather018;						// 018
	TESWeather*		weatherOverride;				// 01C
	Atmosphere*		atmosphere;						// 020
	Stars*			stars;							// 024
	Sun*			sun;							// 028
	Clouds*			clouds;							// 02C
	Moon*			masserMoon;						// 030
	Moon*			secundaMoon;					// 034
	Precipitation*	precipitation;					// 038
	UInt32			unk03C[(0x0B4 - 0x03C) >> 2];	// 03C
	float			unk0B4;							// 0B4
	float			unk0B8;							// 0B8
	float			unk0BC;							// 0BC
	float			windSpeed;						// 0C0
	float			unk0C4;							// 0C4
	float			unk0C8;							// 0C8
	float			unk0CC;							// 0CC
	float			unk0D0;							// 0D0
	float			unk0D4;							// 0D4
	float			weatherPercent;					// 0D8
	UInt32			unk0DC;							// 0DC
	UInt32			unk0E0;							// 0E0
	float			unk0E4;							// 0E4
	UInt32			unk0E8;							// 0E8
	UInt32			unk0EC;							// 0EC
	float			unk0F0;							// 0F0
	float			unk0F4;							// 0F4
	UInt32			unk0F8;							// 0F8
	UInt32			Flags0FC;						// 0FC
	UInt8			unk100;							// 100
	UInt8			unk101[3];						// 101
};
assert(sizeof(Sky) == 0x104);

class GridArray {
public:
	virtual void Fn_00();
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
assert(sizeof(GridArray) == 0x004);

class GridDistantArray : public GridArray {
public:
	struct DistantGridEntry {
		UInt32			unk00;
		UInt32			unk04;
		UInt32			unk08;
		UInt32			unk0C;
	};

	UInt32				unk04;		// 04
	UInt32				unk08;		// 08
	UInt32				size;		// 0C grid is size^2, size = uGridsToLoad + 2 * uGridDistantCount
	DistantGridEntry*	grid;		// 10 dynamically alloc'ed array of GridEntry[size^2]
};
assert(sizeof(GridDistantArray) == 0x014);

class GridCellArray : public GridArray {
public:
	class CellInfo {
	public:
		WaterPlaneData* waterData;
		NiNode*			niNode;
		// ...
	};

	class GridEntry {
	public:
		TESObjectCELL*	cell;
		CellInfo*		info;
	};

	TESObjectCELL*		GetCell(UInt32 x, UInt32 y) { return ((GridEntry*)ThisCall(0x00482150, this, x, y))->cell; }
	TESObjectCELL*		GetCell(UInt32 Index) { return gridEntry[Index].cell; }

	UInt32				worldX;		// 04 worldspace x coordinate of that cell at that center of grid (player's cell)
	UInt32				worldY;		// 08 worldspace y coordinate of that cell at that center of grid (player's cell)
	UInt32				size;		// 0C grid is size^2, size = uGridsToLoad
	GridEntry*			gridEntry;	// 10 dynamically alloc'ed array of GridEntry[size^2]
	float				posX;		// 14 4096*worldX (exterior cells are 4096 square units)
	float				posY;		// 18 4096*worldY
	float				unk1C;		// 1C
	UInt8				unk20;		// 20
	UInt8				pad20[3];
	BSRenderedTexture*	canopyShadowMap;		// 24
};
assert(sizeof(GridCellArray) == 0x028);

class WaterManager {
public:
	NiCamera*			Camera;					// 000
	BSRenderedTexture*	ReflectionMap;			// 004
	BSRenderedTexture*	BaseHeightMap;			// 008
	BSRenderedTexture*	DisplacementMap;		// 00C
	BSRenderedTexture*	HeightMap;				// 010
	BSRenderedTexture*	BaseDisplacementMap;	// 014
	float				unk18;					// 018
	UInt32				unk1C;					// 01C
	TESWaterForm*		WaterForm1;				// 020
	TESWaterForm*		WaterForm2;				// 024
	UInt8				unk28;					// 028
	UInt8				unk29;					// 029
	UInt8				unk2A;					// 02A
	UInt8				unk2B;					// 02B
	float				unk2C;					// 02C
	UInt32				unk30;					// 030
	UInt32				unk34;					// 034
	UInt32				unk38;					// 038
	UInt32				unk3C;					// 03C
	UInt32				unk40;					// 040
	float				WaterHeight;			// 044
};
assert(sizeof(WaterManager) == 0x048);

class TES {
public:
	virtual void Unk_00(UInt32 arg0, UInt32 arg1, UInt32 arg2, UInt32 arg3, TESWorldSpace* worldSpace);

	struct Unk8C {
		TESNPC* npc;
		UInt32	unk4;	// size?
	};
	
	void				PurgeCells() { ThisCall(0x00442630, this, 1, 0); ThisCall(0x0043FC20, this, 0); }
	float				GetWaterHeight(TESObjectREFR* Ref) { return Ref->parentCell->GetWaterHeight(); }
	float				GetTerrainHeight(NiPoint3* Pos) { float Height; ThisCall(0x00440590, this, Pos, &Height); return Height; }
	NiNode*				CastRay(bhkWorldRayCastData* WorldRayCastData) { return (NiNode*)ThisCall(0x00446A10, this, WorldRayCastData); }

	GridDistantArray*	gridDistantArray;		// 04
	GridCellArray*		gridCellArray;			// 08
	NiNode*				ObjectLODRoot;			// 0C
	NiNode*				LandLOD;				// 10
	BSTempNodeManager*	tempNodeManager;		// 14
	NiDirectionalLight* niDirectionalLight;		// 18
	BSFogProperty*		fogProperty;			// 1C
	int					extXCoord;				// 20
	int					extYCoord;				// 24
	int					unk28;					// 28
	int					unk2C;					// 2C
	TESObjectCELL*		currentExteriorCell;	// 30
	TESObjectCELL*		currentInteriorCell;	// 34
	TESObjectCELL**		interiorCellBufferArray;// 38
	TESObjectCELL**		exteriorCellBufferArray;// 3C
	UInt32				unk40;					// 40
	UInt32				unk44;					// 44
	UInt32				unk48;					// 48 seen 0x7FFFFFFF; seen caching unk20 in editor
	UInt32				unk4C;					// 4C seen 0x7FFFFFFF; seen caching unk24 in editor
	UInt8				unk50;					// 50
	UInt8				unk51;					// 51
	UInt8				unk52;					// 52
	UInt8				CellBorders;			// 53
	WaterManager*		waterManager;			// 54
	WaterPlaneData*		waterNodeData;			// 58
	Sky*				sky;					// 5C
	UInt32				unk60;					// 60
	UInt32				unk64;					// 64
	UInt32				unk68;					// 68
	float				unk6C;					// 6C
	float				unk70;					// 70
	TESWorldSpace*		currentWorldSpace;		// 74
	UInt32				unk78;					// 78
	UInt32				unk7C;					// 7C
	UInt32				unk80;					// 80
	UInt32				unk84;					// 84
	UInt32				unk88;					// 88
	TList<Unk8C>		list8C;					// 8C
	NiSourceTexture*	bloodDecals[3];			// 94 blood.dds, lichblood.dds, whillothewispblood.dds
	TList<void*>		listA0;					// A0 data is some struct containing NiNode*
	UInt8				unkA8;					// A8
	UInt8				unkA9;					// A9
	UInt8				padA8[2];
};
assert(sizeof(TES) == 0x0AC);

class TESGameSound {
public:
	enum {
		kType_Voice = 1 << 2,
		kType_Footstep = 1 << 3,
	};

	UInt8			typeFlags;	// 00	for calculating volume based on OSSoundGlobals::foot/voice/effectVolume
	UInt8			unk01;
	UInt8			unk02[2];
	UInt32			unk04[2];	// 04
	UInt32			hashKey;	// 0C
	UInt32			unk10[4];	// 10
	float			x;			// 20
	float			y;			// 24
	float			z;			// 28
	UInt32			unk2C[4];	// 2C
	float			unk3C;		// 3C
	UInt32			unk40[3];	// 40
	const char*		name;		// 4C
	UInt32			unk50;		// 50
	UInt32			unk54;		// 54
};
assert(sizeof(TESGameSound) == 0x058);

class BSAnimGroupSequence : public NiControllerSequence {
public:
	TESAnimGroup*	animGroup;	//068
};
assert(sizeof(BSAnimGroupSequence) == 0x06C);

class Tile {
public:
	enum TileValue {
		//...

		kTileValue_visible = 0x00000FA1,
		kTileValue_class,
		kTileValue_listclip,
		kTileValue_clipwindow,
		kTileValue_stackingtype,
		kTileValue_locus,
		kTileValue_alpha,
		kTileValue_id,
		kTileValue_disablefade,
		kTileValue_listindex,
		kTileValue_depth,
		kTileValue_y,
		kTileValue_x,
		kTileValue_user0,
		kTileValue_user1,
		kTileValue_user2,
		kTileValue_user3,
		kTileValue_user4,
		kTileValue_user5,
		kTileValue_user6,
		kTileValue_user7,
		kTileValue_user8,
		kTileValue_user9,
		kTileValue_user10,
		kTileValue_user11,
		kTileValue_user12,
		kTileValue_user13,
		kTileValue_user14,
		kTileValue_user15,
		kTileValue_user16,
		kTileValue_user17,
		kTileValue_user18,
		kTileValue_user19,
		kTileValue_user20,
		kTileValue_user21,
		kTileValue_user22,
		kTileValue_user23,
		kTileValue_user24,
		kTileValue_user25,
		kTileValue_clips,
		kTileValue_target,
		kTileValue_height,
		kTileValue_width,
		kTileValue_red,
		kTileValue_green,
		kTileValue_blue,
		kTileValue_tile,
		kTileValue_childcount,
		kTileValue_child_count = kTileValue_childcount,
		kTileValue_justify,
		kTileValue_zoom,
		kTileValue_font,
		kTileValue_wrapwidth,
		kTileValue_wraplimit,
		kTileValue_wraplines,
		kTileValue_pagenum,
		kTileValue_ishtml,
		kTileValue_cropoffsety,
		kTileValue_cropy = kTileValue_cropoffsety,
		kTileValue_cropoffsetx,
		kTileValue_cropx = kTileValue_cropoffsetx,
		kTileValue_menufade,
		kTileValue_explorefade,
		kTileValue_mouseover,
		kTileValue_string,
		kTileValue_shiftclicked,
		kTileValue_focusinset,
		kTileValue_clicked,
		kTileValue_clickcountbefore,
		kTileValue_clickcountafter,
		kTileValue_clickedfunc,
		kTileValue_clicksound,
		kTileValue_filename,

		//...

		kTileValue_xdefault = 0x00000FF0,
		kTileValue_xup,
		kTileValue_xdown,
		kTileValue_xleft,
		kTileValue_xright,
		kTileValue_xscroll,
		kTileValue_xlist,
		kTileValue_xbuttona,
		kTileValue_xbuttonb,
		kTileValue_xbuttonx,
		kTileValue_xbuttony,
		kTileValue_xbuttonlt,
		kTileValue_xbuttonrt,
		kTileValue_xbuttonlb,
		kTileValue_xbuttonrb,

		//...
	};

	virtual void		Destructor();
	virtual void		Unk_01(UInt32 unk0, const char* str, UInt32 unk2);
	virtual NiNode*		Unk_02();
	virtual UInt32		GetTypeID();
	virtual const char* GetType();
	virtual UInt32		UpdateField(UInt32 valueID, float floatValue, const char* strValue);
	virtual void		Unk_06();

	struct Value {
		union Operand {
			Value* ref;
			float* immediate;
		};

		struct Expression {
			Expression* prev;
			Expression* next;
			Operand		operand;	// how does it tell if it's ref or immediate?
			UInt16		opcode;		// i.e. 7D1 "copy", 7D2 "add", etc
			UInt16		unkE;
			Value*		src;
		};

		// linked list of compiled xml expression. Preliminary!
		struct ExpressionList {
			Expression* info;
			ExpressionList* next;
		};

		Tile*			parentTile;	// 00 - Tile * back to owning tile
		float			num;		// 04
		BSString		str;		// 08
		ExpressionList	exprList;	// 10
		UInt16			id;			// 18
		UInt8			bIsNum;		// 1A 0 = string, 1 = number
		UInt8			pad1B;		// 1B
	};
	
	Tile::Value* Tile::GetValueByType(UInt32 valueType) {

		for (NiTList<Value>::Entry* node = valueList.start; node; node = node->next) {
			if (node->data && node->data->id == valueType) return node->data;
		}
		return NULL;

	}

	bool Tile::GetFloatValue(UInt32 valueType, float* out) {

		Value* val = GetValueByType(valueType);

		if (val) {
			*out = val->num;
			return true;
		}
		return false;

	}

	UInt8			unk04;		// 04 - 0 = base tile
	UInt8			unk05;		// 05 - looks like bool, possibly bModified? Seems only used for x, y, width, height changed
	UInt8			unk06;		// 06
	UInt8			pad07;		// 07
	BSString		name;		// 08
	Tile*			parent;		// 10
	NiTList<Value>	valueList;	// 14
	UInt32			unk24;		// 24	// NiNode *
	void*			unk28;		// 28
	UInt32			flags;		// 2C
	NiTList<Tile>	childList;	// 30
};
assert(sizeof(Tile) == 0x040);

class TileRect : public Tile {
public:
	enum {
		kID = 0x0385
	};

	UInt32	unk40;	// 40
};
assert(sizeof(TileRect) == 0x044);

class TileMenu : public TileRect {
public:
	Menu*	menu;	// 44
};
assert(sizeof(TileMenu) == 0x048);

class Menu {
public:
	enum MenuType {
		kMenuType_None = 0,			// for gamemode
		kMenuType_BigFour,			// F1 - F4 menus
		kMenuType_Any,
		kMenuType_Console,

		kMenuType_Message = 0x3E9,
		kMenuType_Inventory,
		kMenuType_Stats,
		kMenuType_HUDMain,
		kMenuType_HUDInfo,
		kMenuType_HUDReticle,
		kMenuType_Loading,
		kMenuType_Container,
		kMenuType_Dialog,
		kMenuType_HUDSubtitle,
		kMenuType_Generic,
		kMenuType_SleepWait,
		kMenuType_Pause,
		kMenuType_LockPick,
		kMenuType_Options,
		kMenuType_Quantity,
		kMenuType_Audio,
		kMenuType_Video,
		kMenuType_VideoDisplay,
		kMenuType_Gameplay,
		kMenuType_Controls,
		kMenuType_Magic,
		kMenuType_Map,
		kMenuType_MagicPopup,
		kMenuType_Negotiate,
		kMenuType_Book,
		kMenuType_LevelUp,
		kMenuType_Training,
		kMenuType_BirthSign,
		kMenuType_Class,
		kMenuType_unk407,
		kMenuType_Skills,
		kMenuType_unk409,
		kMenuType_Persuasion,
		kMenuType_Repair,
		kMenuType_RaceSex,
		kMenuType_SpellPurchase,
		kMenuType_Load,
		kMenuType_Save,
		kMenuType_Alchemy,
		kMenuType_Spellmaking,
		kMenuType_Enchantment,
		kMenuType_EffectSetting,
		kMenuType_Main,
		kMenuType_Breath,
		kMenuType_QuickKeys,
		kMenuType_Credits,
		kMenuType_SigilStone,
		kMenuType_Recharge,
		kMenuType_unk41A,
		kMenuType_TextEdit,

		kMenuType_Max
	};

	virtual void	Destructor(bool arg0);		// pass false to free memory
	virtual void	SetField(UInt32 idx, Tile* value);
	virtual void	Unk_02(UInt32 arg0, UInt32 arg1);	// show menu?
	virtual void	HandleClick(UInt32 buttonID, Tile* clickedButton); // buttonID = <id> trait defined in XML
	virtual void	HandleMouseover(UInt32 arg0, Tile* activeTile);	//called on mouseover, activeTile is moused-over Tile
	virtual void	Unk_05(UInt32 arg0, UInt32 arg1);
	virtual void	Unk_06(UInt32 arg0, UInt32 arg1, UInt32 arg2);
	virtual void	Unk_07(UInt32 arg0, UInt32 arg1, UInt32 arg2);
	virtual void	Unk_08(UInt32 arg0, UInt32 arg1);
	virtual void	Unk_09(UInt32 arg0, UInt32 arg1);
	virtual void	Unk_0A(UInt32 arg0, UInt32 arg1);
	virtual void	Unk_0B(void);
	virtual bool	HandleKeyboardInput(char inputChar);	//for keyboard shortcuts, return true if handled
	virtual UInt32	GetID();
	virtual bool	Unk_0E(UInt32 arg0, UInt32 arg1);

	TileMenu* tile;			// 04
	UInt32	  unk08;		// 08
	UInt32	  unk0C;		// 0C
	UInt32	  unk10;		// 10
	UInt32	  unk14;		// 14
	UInt32	  unk18;		// 18
	UInt32	  unk1C;		// 1C - initialized to 1
	UInt32	  id;			// 20 - uninitialized
	UInt32	  unk24;		// 24 - initialized to 4, is 8 if enabled?
};
assert(sizeof(Menu) == 0x028);

class ModInfo {
public:
	enum {
		kFlag_IsMaster = 1 << 0,
		kFlag_Loaded = 1 << 2,
		kFlag_Active = 1 << 3
	};

	template <typename tData> struct Node {
		tData*		 data;
		Node<tData>* next;
	};

	struct ChunkInfo {
		UInt32	type;		// e.g. 'GRUP', 'GLOB', etc
		UInt32	length;
	};

	struct FormInfo {	// ###TODO double check this, see 46B910 (TESForm virtual func, accepts Unk23C* as arg)
		ChunkInfo	chunkInfo;
		UInt32		flags;
		UInt32		formID;
		UInt32		unk10;
	};

	struct SizeInfo	{ // as seen in the editor
		UInt32		fileSizeLow;			// WIN32_FIND_DATA::nFileSizeLow 
		UInt32		fileSizeHigh;			// WIN32_FIND_DATA::nFileSizeHigh
	};

	UInt32			unk000;							// 000 appears to indicate status of file (open, closed, etc) 2, 9, 0C do stuff
	UInt32			unk004;							// 004
	UInt32			unk008;							// 008
	UInt32			unk00C;							// 00C
	BSFile*			bsFile;							// 010
	UInt32			unk014;							// 014
	UInt32			unk018;							// 018
	char			name[0x104];					// 01C
	char			filepath[0x104];				// 120 relative to "Oblivion\"
	UInt32			unk224;							// 224
	UInt32			unk228;							// 228 init to *(0xB055CC), seen 0x2800
	UInt32			unk22C[(0x23C - 0x22C) >> 2];	// 22C
	FormInfo		formInfo;						// 23C
	UInt32			chunkType250;					// 250
	UInt32			unk254[(0x3D0 - 0x254) >> 2];	// 254
	UInt32			version;						// 3D0 plugin version (0.8/1.0)
	UInt32			formCount;						// 3D4 record/form count
	UInt32			nextFormID;						// 3D8 used by TESFile::sub_486BF0 in the editor
	UInt32			flags;							// 3DC
	Node<char>		masterList;						// 3E0 linked list of .esm dependencies
	Node<SizeInfo>	masterSizeInfo;					// 3E8 linked list of file size info for above list
	UInt32			idx;							// 3F0
	void*			unk3F4;							// 3F4
	UInt32			unk3F8;							// 3F8
	UInt32			unk3FC;							// 3FC
	UInt8			unk400;							// 400 init to -1
	UInt8			pad401[3];
	BSString		authorName;						// 404
	BSString		modDescription;					// 40C
	UInt32			unk414;							// 414
	UInt32			unk418;							// 418
};
assert(sizeof(ModInfo) == 0x41C);

class ModList {
public:
	TList<ModInfo>		modInfoList;		// 00
	UInt32				loadedModCount;		// 08
	ModInfo*			loadedMods[0xFF];	// 0C
};
assert(sizeof(ModList) == 0x408);

class MasterDataHandler {
public:
	TESForm*				CreateForm(UInt8 FormType) { TESForm* (__cdecl* CreateForm)(UInt8) = (TESForm* (__cdecl*)(UInt8))0x00447DF0; return CreateForm(FormType); }
	bool					AddData(TESForm* Form) { return ThisCall(0x0044D950, this, Form); }
	void					FillNames(std::vector<std::string>* List, UInt32 FormType) {
								List->clear();
								if (FormType == TESForm::FormType::kFormType_Weather) {
									for (TList<TESWeather>::Iterator Itr = weathers.Begin(); !Itr.End() && Itr.Get(); ++Itr) {
										TESWeatherEx* Weather = (TESWeatherEx*)Itr.Get();
										List->push_back(Weather->EditorName);
									}
								}
							}
	TESForm*				GetFormByName(const char* EditorName, UInt32 FormType) {
								TESForm* Form = NULL;

								if (FormType == TESForm::FormType::kFormType_Weather) {
									for (TList<TESWeather>::Iterator Itr = weathers.Begin(); !Itr.End() && Itr.Get(); ++Itr) {
										TESWeatherEx* Weather = (TESWeatherEx*)Itr.Get();
										if (!strcmp(EditorName, Weather->EditorName)) {
											Form = Weather;
											break;
										}
									}
								}
								return Form;
							}

	struct Unk8B8 {											// as seen in the editor
		UInt32				unk00;							// 00
		UInt32				unk04;							// 04
		UInt32				unk08;							// 08 initialized to (numLoadedMods << 24) | 0x800 during plugin load
		ModInfo*			activeFile;						// 0C active plugin
	};

	BoundObjectListHead*	boundObjects;					// 000
	TList<TESPackage>		packages;						// 004
	TList<TESWorldSpace>	worldSpaces;					// 00C
	TList<TESClimate>		climates;						// 014
	TList<TESWeather>		weathers;						// 01C
	TList<EnchantmentItem>	enchantmentItems;				// 024
	TList<SpellItem>		spellitems;						// 02C
	TList<TESHair>			hairs;							// 034
	TList<TESEyes>			eyes;							// 03C
	TList<TESRace>			races;							// 044
	TList<TESLandTexture>	landTextures;					// 04C
	TList<TESClass>			classes;						// 054
	TList<TESFaction>		factions;						// 05C
	TList<Script>			scripts;						// 064
	TList<TESSound>			sounds;							// 06C
	TList<TESGlobal>		globals;						// 074
	TList<TESTopic>			topics;							// 07C
	TList<TESQuest>			quests;							// 084
	TList<BirthSign>		birthsigns;						// 08C
	TList<TESCombatStyle>	combatStyles;					// 094
	TList<TESLoadScreen>	loadScreens;					// 09C
	TList<TESWaterForm>		waterForms;						// 0A4
	TList<TESEffectShader>	effectShaders;					// 0AC
	TList<TESObjectANIO>	objectAnios;					// 0B4
	TESRegionList*			regionList;						// 0BC
	NiTLargeArray<TESObjectCELL*>	cellArray;				// 0C0
	TESSkill				skills[0x15];					// 0D8
	Unk8B8					unk8B8;							// 8B8
	ModList					modList;						// 8C8
	UInt32					unkCD0[(0xCD8 - 0xCD0) >> 2];	// CD0
	TESRegionDataManager*	regionDataManager;				// CD8
	UInt32					unkCDC;							// CDC
};
assert(sizeof(MasterDataHandler) == 0xCE0);

class InputControl {
public:
	enum {
		kFlag_HasJoysticks = 1 << 0,
		kFlag_HasMouse = 1 << 1,
		kFlag_HasKeyboard = 1 << 2,
		kFlag_BackgroundMouse = 1 << 3,
	};
	enum {
		kMaxDevices = 8,
	};

	struct Joystick {
		UInt32	unk000[0x244 >> 2];
	};

	struct JoystickObjectsInfo {
		enum {
			kHasXAxis = 1 << 0,
			kHasYAxis = 1 << 1,
			kHasZAxis = 1 << 2,
			kHasXRotAxis = 1 << 3,
			kHasYRotAxis = 1 << 4,
			kHasZRotAxis = 1 << 5
		};
		UInt32	axis;
		UInt32	buttons;
	};

	struct Unk1AF4 {
		UInt32	bufLen;
		UInt8	unk04[0x2C - 4];
	};

	UInt32				 flags;										// 0000
	IDirectInput8*		 dinputInterface;							// 0004
	IDirectInputDevice8* joystickInterfaces[kMaxDevices];			// 0008 - format is c_dfDIJoystick
	IDirectInputDevice8* keyboardInterface;							// 0028 - format is c_dfDIKeyboard
	IDirectInputDevice8* mouseInterface;							// 002C - format is c_dfDIMouse2
	UInt32				 unk0030[0x140];							// 0030
	Joystick			 devices[kMaxDevices];						// 0530
	DIDEVCAPS			 devCaps[kMaxDevices];						// 1750
	JoystickObjectsInfo	 devInfo[kMaxDevices];						// 18B0
	UInt32				 numJoysticks;								// 18F0
	UInt8				 CurrentKeyState[0x100];					// 18F4
	UInt8				 PreviousKeyState[0x100];					// 19F4
	Unk1AF4				 unk1AF4;									// 1AF4
	DIMOUSESTATE2		 CurrentMouseState;							// 1B20
	DIMOUSESTATE2		 PreviousMouseState;						// 1B34
	UInt32				 oldMouseButtonSwap;						// 1B48 - state of SwapMouseButton when program launched
	UInt32				 doubleClickTime;							// 1B4C - GetDoubleClickTime
	UInt32				 unk1B50[(0x1B7C - 0x1B50) >> 2];			// 1B50
	UInt8				 unk1B7C;									// 1B7C
	UInt8				 unk1B7D;									// 1B7D
	UInt8				 KeyboardInputControls[29];					// 1B7E
	UInt8				 MouseInputControls[29];					// 1B9B
	UInt8				 JoystickInputControls[29];					// 1BB8
	UInt8				 AlwaysRunControl;							// 1BD5
	UInt8				 pad1BD6;									// 1BD6
	UInt8				 pad1BD7;									// 1BD7
};
assert(sizeof(InputControl) == 0x1BD8);

class SoundControl {
public:
	enum {
		kFlags_HasDSound = 1 << 0,
		kFlags_HasHardware3D = 1 << 2,
	};

	void					Play(TESSound* Sound) { TESGameSound* GameSound = (TESGameSound*)ThisCall(0x006AE0A0, this, Sound->refID, 0x101, 0); ThisCall(0x006B7190, GameSound, 0); ThisCall(0x006B73E0, GameSound); }
	
	UInt32					unk000;						// 000
	UInt32					unk004;						// 004
	IDirectSound8*			dsoundInterface;			// 008
	IDirectSoundBuffer8*	primaryBufferInterface;		// 00C
	DSCAPS					soundCaps;					// 010
	UInt32					unk070;						// 070
	UInt32					unk074;						// 074
	IDirectSound3DListener* listenerInterface;			// 078
	UInt32					unk07C;						// 07C
	float					PlayerPosX;					// 080
	float					PlayerPosY;					// 084
	float					PlayerPosZ;					// 088
	UInt32					unk08C[(0x0A4 - 0x08C) >> 2];	// 08C
	UInt8					unk0A4;						// 0A4
	UInt8					unk0A5;						// 0A5
	UInt8					unk0A6;						// 0A6
	UInt8					pad0A7;						// 0A7
	UInt32					unk0A8;						// 0A8
	UInt32					flags;						// 0AC - flags?
	UInt32					unk0B0;						// 0B0
	UInt32					unk0B4;						// 0B4
	float					masterVolume;				// 0B8
	float					footVolume;					// 0BC
	float					voiceVolume;				// 0C0
	float					effectsVolume;				// 0C4
	UInt32					unk0C8;						// 0C8 - time
	UInt32					unk0CC;						// 0CC - time
	UInt32					unk0D0;						// 0D0 - time
	UInt32					unk0D4[(0x0DC - 0x0D4) >> 2];	// 0D4
	UInt32					unk0DC;						// 0DC
	UInt32					unk0E0[(0x2F0 - 0x0E0) >> 2];	// 0E0
	float					musicVolume;				// 2F0
	float					unk2F4;						// 2F4
	float					musicVolume2;				// 2F8
	UInt32					unk2FC;						// 2FC
	NiTMap<UInt32, TESGameSound>*	gameSoundMap;				// 300
	NiTMap<UInt32, NiAVObject>*		niObjectMap;				// 304
	NiTList<void>*			soundMessageMap;			// 308 - AudioManager::SoundMessage *
	UInt32					unk30C[(0x320 - 0x30C) >> 2];	// 30C
	NiTList<UInt32>*		soundMessageList;			// 320
	UInt32					unk324;						// 324
};
assert(sizeof(SoundControl) == 0x328);

class Main {
public:
	InputControl*	GetInputKeyboard() { return input; }
	InputControl*	GetInputMouse() { return input; }
	SoundControl*	GetSound() { return sound; }
	void			PurgeModels() { ThisCall(0x00404C60, this, 1); }

	UInt8			quitGame;			// 00
	UInt8			exitToMainMenu;		// 01
	UInt8			unk02;				// 02
	UInt8			unk03;				// 03
	UInt8			unk04;				// 04
	UInt8			pad05[3];			// 05
	HWND			window;				// 08
	HINSTANCE		procInstance;		// 0C
	UInt32			mainThreadID;		// 10
	HANDLE			mainThreadHandle;	// 14
	UInt32			unk18;				// 18
	UInt32			unk1C;				// 1C
	InputControl*	input;				// 20
	SoundControl*	sound;				// 24
};
assert(sizeof(Main) == 0x028);

class MenuInterfaceManager {
public:
	bool			IsActive(UInt32 MenuType) { return activeMenuType == MenuType; }
	bool			ShowMessageBox(const char* Message, void* Callback, const char* Button0, const char* Button1 = NULL, const char* Button2 = NULL, const char* Button3 = NULL, const char* Button4 = NULL, const char* Button5 = NULL, const char* Button6 = NULL, const char* Button7 = NULL, const char* Button8 = NULL, const char* Button9 = NULL) { bool (__cdecl* ShowUIMessageBox)(const char*, void*, UInt32, const char*, ...) = (bool (__cdecl*)(const char*, void*, UInt32, const char*, ...))0x00579C10; return ShowUIMessageBox(Message, Callback, 1, Button0, Button1, Button2, Button3, Button4, Button5, Button6, Button7, Button8, Button9, NULL); }
	void			ShowMessage(const char* Message) { void (__cdecl* ShowUIMessage)(const char*, UInt32, UInt32, float) = (void (__cdecl*)(const char*, UInt32, UInt32, float))0x0057ACC0; ShowUIMessage(Message, NULL, 1, 2.0f); }
	UInt8			GetMessageBoxButton() { UInt8 B = msgBoxButton; msgBoxButton = -1; return B; }
	void			SetCrosshair(bool Enabled) { void (__cdecl* SetCrossHair)(UInt32) = (void (__cdecl*)(UInt32))0x00578CF0; SetCrossHair(Enabled); }

	SceneGraph*		MenuRoot;						// 000
	SceneGraph*		MenuRoot3D;						// 004
	UInt8			unk008;							// 008
	UInt8			pad008[3];
	UInt32			unk00C;							// 00C
	UInt32			unk010;							// 010
	UInt32			unk014;							// 014
	void*			unk018;							// 018 NiDirectionalLight *
	Tile*			cursor;							// 01C
	UInt32			unk020[(0x050 - 0x020) >> 2];	// 020
	bool			debugTextOn;					// 050
	UInt8			unk051[3];
	NiNode*			unk054[(0x064 - 0x054) >> 2];	// 054
	NiNode*			unk064;							// 064 ShadowSceneNode *
	Tile*			menuRoot;						// 068
	Tile*			strings;						// 06C
	NiNode*			unk070;							// 070
	UInt32			unk074;							// 074
	void*			unk078;							// 078 NiAlphaProperty*
	UInt32			unk07C;							// 07C
	Tile*			hudReticule;					// 080
	UInt32			unk084;							// 084
	Tile*			altActiveTile;					// 088 appears to be active tile when activeTile is null and keyboard navigation used
	UInt32			unk08C;							// 08C
	UInt32			unk090;							// 090
	UInt32			unk094;							// 094
	Tile*			activeTile;						// 098 - moused-over tile
	Menu*			activeMenu;						// 09C - menu over which the mouse cursor is placed
	UInt32			unk0A0;							// 0A0
	UInt32			unk0A4;							// 0A4
	UInt32			unk0A8;							// 0A8
	UInt32			unk0AC;							// 0AC
	UInt8			msgBoxButton;					// 0B0
	UInt8			unk0B1[3];						// 0B1
	void*			unk0B4;							// 0B4 - stores callback for ShowMessageBox() (anything else?)
	UInt32			unk0B8;							// 0B8	
	TESObjectREFR*	debugSelection;					// 0BC
	UInt32			unk0C0[(0x0E0 - 0x0C0) >> 2];	// 0C0
	UInt32			activeMenuType;					// 0E0
	UInt32			unk0E4[(0x134 - 0x0E4) >> 2];	// 0E4
};
assert(sizeof(MenuInterfaceManager) == 0x134);

class TimeGlobals {
public:
	TESGlobal* GameYear;		// 00
	TESGlobal* GameMonth;		// 04
	TESGlobal* GameDay;			// 08
	TESGlobal* GameHour;		// 0C
	TESGlobal* GameDaysPassed;	// 10
	TESGlobal* TimeScale;		// 14

	static float GetGameTime() { TimeGlobals* Globals = (TimeGlobals*)0x00B332E0; return Globals->GameHour->data * 60.0f * 60.0f; }

};
assert(sizeof(TimeGlobals) == 0x018); // Static class, size could be larger

class QueuedModelLoader {
public:
	void RemoveModel(const char* WeaponModelPath) { ThisCall(0x004384E0, this, WeaponModelPath, 1, 1); }

	UInt32	Unk000[7]; // LockFreeMaps for models

};
assert(sizeof(QueuedModelLoader) == 0x01C);

class GameSetting {
public:
	union {
		char*	pValue;
		int		iValue;
		float	fValue;
	};
	char*		Name;
};
assert(sizeof(GameSetting) == 0x08);

static const void*	VFTNiNode				= (void*)0x00A7E38C;
static const void*	VFTBSFadeNode			= (void*)0x00A3F944;
static const void*	VFTBSFaceGenNiNode		= (void*)0x00A64F5C;
static const void*	VFTBSTreeNode			= (void*)0x00A65854;
static const void*	VFTNiTriShape			= (void*)0x00A7ED5C;
static const void*	VFTNiTriStrips			= (void*)0x00A7F27C;
static const void*	VFTbhkCollisionObject	= (void*)0x00A55FCC;

static float*		LocalGrassWindMagnitudeMax	= (float*)0x00B46068;
static float*		LocalGrassWindMagnitudeMin	= (float*)0x00B46064;
static UInt8*		LocalWaterHiRes				= (UInt8*)0x00B45FD0;

static void* (__cdecl* MemoryAlloc)(size_t) = (void* (__cdecl*)(size_t))0x00401F00;
static void  (__cdecl* MemoryDealloc)(void*) = (void (__cdecl*)(void*))0x00401F20;
static bool  (__cdecl* ExtractArgs)(CommandParam*, void*, UInt32*, TESObjectREFR*, TESObjectREFR*, Script*, ScriptEventList*, ...) = (bool (__cdecl*)(CommandParam*, void*, UInt32*, TESObjectREFR*, TESObjectREFR*, Script*, ScriptEventList*, ...))0x004FAE80;
static void  (__cdecl* CreateGrass)(TESObjectCELL*, NiNode*, float, float, float, float, float, int, float, float, float) = (void (__cdecl*)(TESObjectCELL*, NiNode*, float, float, float, float, float, int, float, float, float))0x004EB3F0;
static void  (* PrintToConsole)(const char*, ...) = (void (*)(const char*, ...))0x00579B60;
static ShaderDefinition* (__cdecl* GetShaderDefinition)(UInt32) = (ShaderDefinition* (__cdecl*)(UInt32))0x007B4290;
static char* (__cdecl* GetPassDescription)(UInt32) = (char* (__cdecl*)(UInt32))0x007B4920;
static void  (__cdecl* BeginRendering)(UInt32, NiRenderTargetGroup*) = (void (__cdecl*)(UInt32, NiRenderTargetGroup*))0x007D7280;
static void  (* EndRendering)() = (void (*)())0x007D72D0;
#elif defined(SKYRIM)
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

class ExtraHavok : public BSExtraData {
public:
	bhkWorld*		world;	// 008
	UInt32			unk10;	// 00C
};
assert(sizeof(ExtraHavok) == 0x010);

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

	struct ColorType {
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
	ColorType		colors[kNumColorTypes];			// 58C
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
		UInt8	shallowColorR;
		UInt8	shallowColorG;
		UInt8	shallowColorB;
		UInt8	shallowColorA;
		UInt8	deepColorR;
		UInt8	deepColorG;
		UInt8	deepColorB;
		UInt8	deepColorA;
		UInt8	reflectionColorR;
		UInt8	reflectionColorG;
		UInt8	reflectionColorB;
		UInt8	reflectionColorA;
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
	ExtraHavok*				GetExtraHavok() { return (ExtraHavok*)extraDataList->GetExtraData(BSExtraData::ExtraDataType::kExtraData_Havok); }

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

static float* LocalGrassWindMagnitudeMax = (float*)0x00000000;
static float* LocalGrassWindMagnitudeMin = (float*)0x00000000;

static void* (__cdecl* MemoryAlloc)(size_t) = (void* (__cdecl*)(size_t))0x004017F0;
static bool  (__cdecl* ExtractArgs)(CommandParam*, void*, UInt32*, TESObjectREFR*, TESObjectREFR*, Script*, ScriptEventList*, ...) = (bool (__cdecl*)(CommandParam*, void*, UInt32*, TESObjectREFR*, TESObjectREFR*, Script*, ScriptEventList*, ...))0x00514830;
static void  (* PrintToConsole)(const char*, ...) = (void (*)(const char*, ...))0x00848820;
#endif

extern Main*					Global;
extern TES*						Tes;
extern PlayerCharacter*			Player;
extern SceneGraph*				WorldSceneGraph;
extern MasterDataHandler*		DataHandler;
extern MenuInterfaceManager*	MenuManager;
extern QueuedModelLoader*		ModelLoader;
extern ShadowSceneNode*			SceneNode;

void CreateGameInitializationHook();