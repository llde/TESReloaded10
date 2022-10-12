#pragma once

class DetectorWindow;
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
class InventoryMenu;
class ExtraDataList;
class Tile;

class TESSaveLoadGame;
class TESForm;
class TESObjectREFR;
class TESObjectCELL;
class TESObjectBOOK;
class TESObjectARMO;
class TESObjectANIO;
class TESObjectLAND;
class TESPathGrid;
class TESTopic;
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

class BSBound;
class BSFogProperty;
class BSRenderedTexture;
class BSTempNodeManager;
class BSAnimGroupSequence;
class BSFile;


static void* (__cdecl* RTDynamicCast)(void*, UInt32, const void*, const void*, UInt32) = (void* (__cdecl*)(void*, UInt32, const void*, const void*, UInt32))0x009832E6;
static const void * RTTI_TESForm = (void *)0xB02F9C;
static const void * RTTI_TESFullName = (void *)0xB03298;

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

class CommandArgs {
public:
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

class CommandInfo {
public:
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

class BSString {
public:
	bool Set(const char* src) { return ThisCall(0x004028D0, this, src, 0); }

	const char* m_data;		// 00
	UInt16		m_dataLen;  // 04
	UInt16		m_bufLen;	// 06
};
assert(sizeof(BSString) == 0x008);

class BSFixedString {
public:
	const char* m_data;		// 00

	bool operator == (const BSFixedString& lhs) const { return m_data == lhs.m_data; }
	bool operator < (const BSFixedString& lhs) const { return m_data < lhs.m_data; }
};
assert(sizeof(BSFixedString) == 0x04);

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


class ExtraRefractionProperty : public BSExtraData
{
public:
	float		refractionAmount;		// range of 0-1
};
assert(sizeof(ExtraRefractionProperty) == 0x010);

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
		RGBA colors[kNumTimeOfDay];
	};

	struct SoundData {
		UInt32 ID;
		UInt32 count;
	};

	float			GetFogDayNear() { return fogDay.nearFog; }
	float			GetFogDayFar() { return fogDay.farFog; }
	float			GetFogNightNear() { return fogNight.nearFog; }
	float			GetFogNightFar() { return fogNight.farFog; }
	UInt8			GetSunGlare() { return sunGlare; }
	UInt8			GetTransDelta() { return transDelta; }
	UInt8			GetWindSpeed() { return windSpeed; }
	UInt8			GetWeatherType() { return weatherType; }
	UInt8			GetSunDamage() { return sunDamage; }
	UInt8			GetCloudSpeedLower() { return cloudSpeedLower; }
	UInt8			GetCloudSpeedUpper() { return cloudSpeedUpper; }
	float			GetHDR(int Index) { return hdrInfo[Index]; }
	void			SetFogDayNear(float Value) { fogDay.nearFog = Value; }
	void			SetFogDayFar(float Value) { fogDay.farFog = Value; }
	void			SetFogNightNear(float Value) { fogNight.nearFog = Value; }
	void			SetFogNightFar(float Value) { fogNight.farFog = Value; }
	void			SetSunGlare(UInt8 Value) { sunGlare = Value; }
	void			SetTransDelta(UInt8 Value) { transDelta = Value; }
	void			SetWindSpeed(UInt8 Value) { windSpeed = Value; }
	void			SetWeatherType(UInt8 Value) { weatherType = Value; }
	void			SetSunDamage(UInt8 Value) { sunDamage = Value; }
	void			SetCloudSpeedLower(UInt8 Value) { cloudSpeedLower = Value; }
	void			SetCloudSpeedUpper(UInt8 Value) { cloudSpeedUpper = Value; }

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
	ColorData	colorsb[kNumColorTypes];
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
	
	UInt32				GetWaterType() { return waterType; }
	void				RemoveUnderwaterFog() { waterSimVals[TESWaterForm::kWaterVal_FogDistNear] = 163830.0f; waterSimVals[TESWaterForm::kWaterVal_FogDistFar] = 163835.0f; }
	RGBA*				GetShallowColor() { return &shallowColor; }
	RGBA*				GetDeepColor() { return &deepColor; }
	RGBA*				GetReflectionColor() { return &reflectionColor; }

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
	RGBA				shallowColor;			// 68
	RGBA				deepColor;				// 6C
	RGBA				reflectionColor;		// 70
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
	TESWaterForm*                   WaterForm;           // 080
	UInt32							unk080[15];	// 084
	BSString						editorID;			// 0C0
	NiTMap<UInt32, void>			map0C8;				// 0C8
	UInt32							unk0D8[2];	// 0D8
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
	NiNode*			GetNode() { return niNode; }
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
	
	NiNode*							GetNode() { return niNode; }
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
	bool			IsFirstPerson() { return !isThirdPerson; }
	bool			IsVanity() { return *(bool*)0x00B3BB04; }
	void			SetFoV(float FoV) { float* SettingWorldFoV = (float*)0x00B0313C; float* Setting1stPersonFoV = (float*)0x00B0313C; worldFoV = *SettingWorldFoV = *Setting1stPersonFoV = FoV; }
	float			GetFoV(bool IsSpecialView) { return worldFoV; }
	void			ResetCamera() { ThisCall(0x0066C600, this); }
	void			ToggleCamera() { ThisCall(0x0066C580, this, 1); }

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
	BSRenderedTexture*	ReflectionMap;			// 004 //Reflection Texture
	BSRenderedTexture*	BaseHeightMap;			// 008
	BSRenderedTexture*	DisplacementMap;		// 00C
	BSRenderedTexture*	HeightMap;				// 010   //Full HeightMap/NormalMap
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
	TESWaterForm*		GetWaterForm() { return waterManager->WaterForm1; }
	float				GetTerrainHeight(NiPoint3* Pos) { float Height; ThisCall(0x00440590, this, Pos, &Height); return Height; }
	NiNode*				CastRay(bhkWorldRayCastData* WorldRayCastData) { return (NiNode*)ThisCall(0x00446A10, this, WorldRayCastData); }

	GridDistantArray*	gridDistantArray;		// 04
	GridCellArray*		gridCellArray;			// 08
	NiNode*				ObjectLODRoot;			// 0C
	NiNode*				landLOD;				// 10
	BSTempNodeManager*	tempNodeManager;		// 14
	NiDirectionalLight* directionalLight;		// 18
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

class MainDataHandler {
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
assert(sizeof(MainDataHandler) == 0xCE0);

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
	bool			OnKeyDown(UInt16 KeyCode) { if (KeyCode >= 256) return OnMouseDown(KeyCode - 256); if (KeyCode != 255 && input->CurrentKeyState[KeyCode] && !input->PreviousKeyState[KeyCode]) return true; return false; }
	bool			OnKeyPressed(UInt16 KeyCode) { if (KeyCode >= 256) return OnMousePressed(KeyCode - 256); if (KeyCode != 255 && input->CurrentKeyState[KeyCode] && input->PreviousKeyState[KeyCode]) return true; return false; }
	bool			OnKeyUp(UInt16 KeyCode) { if (KeyCode >= 256) return OnMouseUp(KeyCode - 256); if (KeyCode != 255 && !input->CurrentKeyState[KeyCode] && input->PreviousKeyState[KeyCode]) return true; return false; }
	bool			OnMouseDown(UInt8 ButtonIndex) { if (ButtonIndex != 255 && input->CurrentMouseState.rgbButtons[ButtonIndex] && !input->PreviousMouseState.rgbButtons[ButtonIndex]) return true; return false; }
	bool			OnMousePressed(UInt8 ButtonIndex) { if (ButtonIndex != 255 && input->CurrentMouseState.rgbButtons[ButtonIndex] && input->PreviousMouseState.rgbButtons[ButtonIndex]) return true; return false; }
	bool			OnMouseUp(UInt8 ButtonIndex) { if (ButtonIndex != 255 && !input->CurrentMouseState.rgbButtons[ButtonIndex] && input->PreviousMouseState.rgbButtons[ButtonIndex]) return true; return false; }
	bool			OnControlDown(UInt16 ControlID) { return OnKeyDown(input->KeyboardInputControls[ControlID]) + OnMouseDown(input->MouseInputControls[ControlID]); }
	bool			OnControlPressed(UInt16 ControlID) { return OnKeyPressed(input->KeyboardInputControls[ControlID]) + OnMousePressed(input->MouseInputControls[ControlID]); }
	bool			OnControlUp(UInt16 ControlID) { return OnKeyUp(input->KeyboardInputControls[ControlID]) + OnMouseUp(input->MouseInputControls[ControlID]); }
	void			SetControlState(UInt8 ControlID, UInt8 CurrentState, UInt8 PreviousState) {
						UInt16 Source = input->KeyboardInputControls[ControlID];
						if (Source != 255) {
							input->CurrentKeyState[Source] = CurrentState;
							input->PreviousKeyState[Source] = PreviousState;
						}
						Source = input->MouseInputControls[ControlID];
						if (Source != 255) {
							input->CurrentMouseState.rgbButtons[Source] = CurrentState;
							input->PreviousMouseState.rgbButtons[Source] = PreviousState;
						}
					}
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

namespace Pointers {
	namespace Generic {
		static float*			  MPF					= (float*)0x00B33E94;
		static BSRenderedTexture* MenuRenderedTexture	= *(BSRenderedTexture**)0x00B333E8;
		static NiPoint3*		  CameraWorldTranslate	= (NiPoint3*)0x00B3F92C;
		static NiPoint3*		  CameraLocation		= (NiPoint3*)0x00B3F9A8;
		static NiNode**			  DetectorWindowNode	= (NiNode**)0x00B42CF4;
	}
	namespace Functions {
		static void* (__cdecl* MemoryAlloc)(size_t) = (void* (__cdecl*)(size_t))0x00401F00;
		static void  (__cdecl* MemoryDealloc)(void*) = (void (__cdecl*)(void*))0x00401F20;
		static bool  (__cdecl* ExtractArgs)(CommandParam*, void*, UInt32*, TESObjectREFR*, TESObjectREFR*, Script*, ScriptEventList*, ...) = (bool (__cdecl*)(CommandParam*, void*, UInt32*, TESObjectREFR*, TESObjectREFR*, Script*, ScriptEventList*, ...))0x004FAE80;
		static void  (__cdecl* CreateGrass)(TESObjectCELL*, NiNode*, float, float, float, float, float, int, float, float, float) = (void (__cdecl*)(TESObjectCELL*, NiNode*, float, float, float, float, float, int, float, float, float))0x004EB3F0;
		static void  (* PrintToConsole)(const char*, ...) = (void (*)(const char*, ...))0x00579B60;
		static char* (__cdecl* GetPassDescription)(UInt32) = (char* (__cdecl*)(UInt32))0x007B4920;
		static void  (__cdecl* BeginRendering)(UInt32, NiRenderTargetGroup*) = (void (__cdecl*)(UInt32, NiRenderTargetGroup*))0x007D7280;
		static void  (* EndRendering)() = (void (*)())0x007D72D0;
	}
	namespace VirtualTables {
		static const void* NiNode				= (void*)0x00A7E38C;
		static const void* BSFadeNode			= (void*)0x00A3F944;
		static const void* BSFaceGenNiNode		= (void*)0x00A64F5C;
		static const void* BSTreeNode			= (void*)0x00A65854;
		static const void* NiTriShape			= (void*)0x00A7ED5C;
		static const void* NiTriStrips			= (void*)0x00A7F27C;
		static const void* bhkCollisionObject	= (void*)0x00A55FCC;
		static const void* BSMultiBoundNode     = (void*)0x00000000;  //Not present
	}
	namespace Settings {
		static UInt32* GridsToLoad				= (UInt32*)0x00B06A2C;
		static UInt32* MinGrassSize				= (UInt32*)0x00B09B20;
		static float*  GrassStartFadeDistance	= (float*)0x00B09B10;
		static float*  GrassEndDistance			= (float*)0x00B09B18;
		static float*  GrassWindMagnitudeMin	= (float*)0x00B09B28;
		static float*  GrassWindMagnitudeMax	= (float*)0x00B09B30;
		static float*  TexturePctThreshold		= (float*)0x00B08B6C;
		static UInt32* MultiSample				= (UInt32*)0x00B06D0C;
		static UInt8*  HDR						= (UInt8*)0x00B06DE4;
	}
	namespace ShaderParams {
		static float* GrassWindMagnitudeMax	= (float*)0x00B46068;
		static float* GrassWindMagnitudeMin	= (float*)0x00B46064;
		static UInt8* WaterHighResolution	= (UInt8*)0x00B45FD0;
		static float* RockParams			= (float*)0x00B46778;
		static float* RustleParams			= (float*)0x00B46788;
		static float* WindMatrixes			= (float*)0x00B467B8;
	}
}
