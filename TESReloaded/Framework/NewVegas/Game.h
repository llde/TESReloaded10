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
class TileText;
class Projectile;
class MediaSet;
class MediaLocationController;

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

template <typename T>
class TArray {
public:
	void**	_vtbl;		// 00
	T*		data;		// 04
	UInt32	capacity;	// 08
	UInt32	count;		// 0C
};
assert(sizeof(TArray<void>) == 0x10);

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
	bool Set(const char* src) { return ThisCall(0x004037F0, this, src, 0); }

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
		kExtraData_Havok = 0x01,
		kExtraData_Cell3D = 0x02,
		kExtraData_CellWaterType = 0x03,
		kExtraData_RegionList = 0x04,
		kExtraData_SeenData = 0x05,
		kExtraData_CellMusicType = 0x07,
		kExtraData_CellClimate = 0x08,
		kExtraData_ProcessMiddleLow = 0x09,
		kExtraData_CellCanopyShadowMask = 0x0A,
		kExtraData_DetachTime = 0x0B,
		kExtraData_PersistentCell = 0x0C,
		kExtraData_Script = 0x0D,
		kExtraData_Action = 0x0E,
		kExtraData_StartingPosition = 0x0F,
		kExtraData_Anim = 0x10,
		kExtraData_UsedMarkers = 0x12,
		kExtraData_DistantData = 0x13,
		kExtraData_RagdollData = 0x14,
		kExtraData_InventoryChanges = 0x15,
		kExtraData_Worn = 0x16,
		kExtraData_WornLeft = 0x17,
		kExtraData_PackageStartLocation = 0x18,
		kExtraData_Package = 0x19,
		kExtraData_TrespassPackage = 0x1A,
		kExtraData_RunOncePacks = 0x1B,
		kExtraData_ReferencePointer = 0x1C,
		kExtraData_Follower = 0x1D,
		kExtraData_LevCreaModifier = 0x1E,
		kExtraData_Ghost = 0x1F,
		kExtraData_OriginalReference = 0x20,
		kExtraData_Ownership = 0x21,
		kExtraData_Global = 0x22,
		kExtraData_Rank = 0x23,
		kExtraData_Count = 0x24,
		kExtraData_Health = 0x25,
		kExtraData_Uses = 0x26,
		kExtraData_TimeLeft = 0x27,
		kExtraData_Charge = 0x28,
		kExtraData_Light = 0x29,
		kExtraData_Lock = 0x2A,
		kExtraData_Teleport = 0x2B,
		kExtraData_MapMarker = 0x2C,
		kExtraData_LeveledCreature = 0x2E,
		kExtraData_LeveledItem = 0x2F,
		kExtraData_Scale = 0x30,
		kExtraData_Seed = 0x31,
		kExtraData_NonActorMagicCaster = 0x32,
		kExtraData_NonActorMagicTarget = 0x33,
		kExtraData_PlayerCrimeList = 0x35,
		kExtraData_EnableStateParent = 0x37,
		kExtraData_EnableStateChildren = 0x38,
		kExtraData_ItemDropper = 0x39,
		kExtraData_DroppedItemList = 0x3A,
		kExtraData_RandomTeleportMarker = 0x3B,
		kExtraData_MerchantContainer = 0x3C,
		kExtraData_SavedHavokData = 0x3D,
		kExtraData_CannotWear = 0x3E,
		kExtraData_Poison = 0x3F,
		kExtraData_Unk040 = 0x40,	// referenced during LoadFormInModule (in oposition to kExtraData_Light)
		kExtraData_LastFinishedSequence = 0x41,
		kExtraData_SavedAnimation = 0x42,
		kExtraData_NorthRotation = 0x43,
		kExtraData_XTarget = 0x44,
		kExtraData_FriendHits = 0x45,
		kExtraData_HeadingTarget = 0x46,
		kExtraData_RefractionProperty = 0x48,
		kExtraData_StartingWorldOrCell = 0x49,
		kExtraData_Hotkey = 0x4A,
		kExtraData_EditorRefMovedData = 0x4C,
		kExtraData_InfoGeneralTopic = 0x4D,
		kExtraData_HasNoRumors = 0x4E,
		kExtraData_Sound = 0x4F,
		kExtraData_TerminalState = 0x50,
		kExtraData_LinkedRef = 0x51,
		kExtraData_LinkedRefChildren = 0x52,
		kExtraData_ActivateRef = 0x53,
		kExtraData_ActivateRefChildren = 0x54,
		kExtraData_TalkingActor = 0x55,
		kExtraData_ObjectHealth = 0x56,
		kExtraData_DecalRefs = 0x57,
		kExtraData_CellImageSpace = 0x59,
		kExtraData_NavMeshPortal = 0x5A,
		kExtraData_ModelSwap = 0x5B,
		kExtraData_Radius = 0x5C,
		kExtraData_Radiation = 0x5D,
		kExtraData_FactionChanges = 0x5E,
		kExtraData_DismemberedLimbs = 0x5F,
		kExtraData_MultiBound = 0x61,
		kExtraData_MultiBoundData = 0x62,
		kExtraData_MultiBoundRef = 0x63,
		kExtraData_ReflectedRefs = 0x65,
		kExtraData_ReflectorRefs = 0x66,
		kExtraData_EmittanceSource = 0x67,
		kExtraData_RadioData = 0x68,
		kExtraData_CombatStyle = 0x69,
		kExtraData_Primitive = 0x6B,
		kExtraData_OpenCloseActivateRef = 0x6C,
		kExtraData_AnimNoteReciever = 0x6D,
		kExtraData_Ammo = 0x6E,
		kExtraData_PatrolRefData = 0x6F,
		kExtraData_PackageData = 0x70,
		kExtraData_OcclusionPlane = 0x71,
		kExtraData_CollisionData = 0x72,
		kExtraData_SayTopicInfoOnceADay = 0x73,
		kExtraData_EncounterZone = 0x74,
		kExtraData_SayToTopicInfo = 0x75,
		kExtraData_OcclusionPlaneRefData = 0x76,
		kExtraData_PortalRefData = 0x77,
		kExtraData_Portal = 0x78,
		kExtraData_Room = 0x79,
		kExtraData_HealthPerc = 0x7A,
		kExtraData_RoomRefData = 0x7B,
		kExtraData_GuardedRefData = 0x7C,
		kExtraData_CreatureAwakeSound = 0x7D,
		kExtraData_WaterZoneMap = 0x7E,
		kExtraData_IgnoredBySandbox = 0x80,
		kExtraData_CellAcousticSpace = 0x81,
		kExtraData_ReservedMarkers = 0x82,
		kExtraData_WeaponIdleSound = 0x83,
		kExtraData_WaterLightRefs = 0x84,
		kExtraData_LitWaterRefs = 0x85,
		kExtraData_WeaponAttackSound = 0x86,
		kExtraData_ActivateLoopSound = 0x87,
		kExtraData_PatrolRefInUseData = 0x88,
		kExtraData_AshPileRef = 0x89,
		kExtraData_CreatureMovementSound = 0x8A,
		kExtraData_FollowerSwimBreadcrumbs = 0x8B,
		//										= 0x8C,
		kExtraData_WeaponModFlags = 0x8D,
		//
		kExtraData_0x90 = 0x90,	// referenced in LoadGame but no data
		kExtraData_0x91 = 0x91,	// referenced in LoadGame but no data
		kExtraData_SpecialRenderFlags = 0x92
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
assert(sizeof(ExtraRefractionProperty) == 0x010);  //TODO check
//
class ExtraDataList {
public:
	virtual	void				Destroy(bool bNoDealloc);	// removes and frees all of m_data

	BSExtraData*				GetExtraData(BSExtraData::ExtraDataType DataType) { return (BSExtraData*)ThisCall(0x00410220, this, DataType); }
	bool						IsWorn(bool Left) { return (UInt8)ThisCall(0x00418AB0, this, Left) == 1; }
	bool						IsWorn() { return IsWorn(0) || IsWorn(1); }
	InventoryChanges::Data*		GetInventoryChangesData() { return (InventoryChanges::Data*)ThisCall(0x00418520, this); }

	BSExtraData*				m_data;						// 004
	UInt8						m_presenceBitfield[0x15];	// 008 - if a bit is set, then the extralist should contain that extradata - bits are numbered starting from the lsb
	UInt8						pad[3];
};
assert(sizeof(ExtraDataList) == 0x20);

class MagicCaster {
public:
	virtual void			Unk_00();
	virtual void			Unk_01();
	virtual void			Unk_02();
	virtual void			CastSpell(MagicItem* spell, bool arg2, MagicTarget* magicTarget, float arg4, bool arg5);
	virtual void			Unk_04();
	virtual void			Unk_05();
	virtual void			Unk_06();
	virtual void			Unk_07();
	virtual void			Unk_08();
	virtual void			Unk_09();
	virtual void			Unk_0A();
	virtual TESObjectREFR*	GetParent();
	virtual void			Unk_0C();
	virtual void			Unk_0D();
	virtual void			Unk_0E();
	virtual void			Unk_0F();
	virtual void			Unk_10(MagicItem* spell);
	virtual void			Unk_11();
	virtual void			Unk_12(MagicTarget* magicTarget);
	virtual void			Unk_13();

	UInt32	unk04[2];	// 04
};
assert(sizeof(MagicCaster) == 0xC);

class MagicTarget {
public:
	virtual bool			ApplyEffect(MagicCaster* magicCaster, MagicItem* magicItem, ActiveEffect* activeEffect, bool arg4);
	virtual TESObjectREFR*	GetParent();
	virtual void*			GetEffectList(); //ActiveEffectList*
	virtual void			Unk_03();
	virtual void			Unk_04();
	virtual void			Unk_05();
	virtual void			Unk_06();
	virtual void			Unk_07();
	virtual void			Unk_08();
	virtual float			Unk_09(MagicCaster* magicCaster, MagicItem* magicItem, ActiveEffect* activeEffect);
	virtual void			Unk_0A();
	virtual void			Unk_0B();

	UInt32	unk04[3];	// 04
};
assert(sizeof(MagicTarget) == 0x10);

class BaseFormComponent {
public:
	virtual void	Init();
	virtual void	Free();
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
	enum {
		kFacegenFlag_Head		= 0x01,
		kFacegenFlag_Torso		= 0x02,
		kFacegenFlag_RightHand	= 0x04,
		kFacegenFlag_LeftHand	= 0x08,
	};

	virtual void*	Destroy(bool noDealloc);	// 04
	virtual char*	GetModelPath(void);
	virtual void	SetModelPath(char* path);	// 06

	BSString	nifPath;		// 04
	UInt32		unk0C;			// 0C	referenced when saving Texture Hashes, init'd as a byte or is it a pointer to a structure starting with a byte followed by a pointer to some allocated data ?
	void*		unk10;			// 10
	UInt8		facegenFlags;	// 14
	UInt8		pad15[3];		// 15
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

class BGSAmmoForm : public BaseFormComponent {
public:
	TESForm* ammo; // 04	either TESAmmo or BGSListForm
};
assert(sizeof(BGSAmmoForm) == 0x008);

class BGSClipRoundsForm : public BaseFormComponent {
public:
	UInt8	clipRounds;
	UInt8	padding[3];
};
assert(sizeof(BGSClipRoundsForm) == 0x008);

class BGSDestructibleObjectForm : public BaseFormComponent {
public:
	void*	data;			// 04 DestructibleData*
};
assert(sizeof(BGSDestructibleObjectForm) == 0x08);

class BGSRepairItemList : public BaseFormComponent {
public:
	void*	listForm;	// 04 BGSListForm*
};
assert(sizeof(BGSRepairItemList) == 0x08);

class BGSEquipType : public BaseFormComponent {
public:
	UInt32	equipType;	// 04
};
assert(sizeof(BGSEquipType) == 0x08);

class BGSPreloadable : public BaseFormComponent {
public:
	virtual void	Fn_04();
};
assert(sizeof(BGSPreloadable) == 0x04);

class BGSMessageIcon : public BaseFormComponent {
public:
	UInt32	icon[3];		// 004 TESIcon class
};
assert(sizeof(BGSMessageIcon) == 0x10);

class BGSBipedModelList : public BaseFormComponent {
public:
	void*	models;		// 004 BGSListForm*
};
assert(sizeof(BGSBipedModelList) == 0x08);

class BGSPickupPutdownSounds : public BaseFormComponent {
public:
	TESSound* pickupSound;		// 004
	TESSound* putdownSound;		// 008
};
assert(sizeof(BGSPickupPutdownSounds) == 0x0C);

class TESModelTextureSwap : public TESModel {
public:
	virtual void*	Destroy(bool noDealloc);
	virtual char*	GetPath();
	virtual void	SetPath(char* path);
	virtual void*	Unk_07();
	
	class Texture {
	public:
		UInt32	textureID;			// 00
		UInt32	index3D;			// 04
		char	textureName[0x80];	// 08
	};

	TList<Texture>	textureList;	// 018
};
assert(sizeof(TESModelTextureSwap) == 0x020);

class TESForm : public BaseFormComponent {
public:
	enum FormType {
		kFormType_None = 0,					// 00
		kFormType_TES4,
		kFormType_Group,
		kFormType_GMST,
		kFormType_TextureSet,
		kFormType_MenuIcon,
		kFormType_Global,
		kFormType_Class,
		kFormType_Faction,					// 08
		kFormType_HeadPart,
		kFormType_Hair,
		kFormType_Eyes,
		kFormType_Race,
		kFormType_Sound,
		kFormType_AcousticSpace,
		kFormType_Skill,
		kFormType_Effect,					// 10
		kFormType_Script,
		kFormType_LandTexture,
		kFormType_Enchantment,
		kFormType_Spell,
		kFormType_Activator,
		kFormType_TalkingActivator,
		kFormType_Terminal,
		kFormType_Armor,					// 18	inv object
		kFormType_Book,						// 19	inv object
		kFormType_Clothing,					// 1A	inv object
		kFormType_Container,
		kFormType_Door,
		kFormType_Ingredient,				// 1D	inv object
		kFormType_Light,					// 1E	inv object
		kFormType_Misc,						// 1F	inv object
		kFormType_Stat,					// 20
		kFormType_StaticCollection,
		kFormType_MoveableStatic,
		kFormType_PlaceableWater,
		kFormType_Grass,
		kFormType_Tree,
		kFormType_Flora,
		kFormType_Furniture,
		kFormType_Weapon,					// 28	inv object
		kFormType_Ammo,						// 29	inv object
		kFormType_NPC,						// 2A
		kFormType_Creature,					// 2B
		kFormType_LeveledCreature,			// 2C
		kFormType_LeveledCharacter,			// 2D
		kFormType_Key,						// 2E	inv object
		kFormType_AlchemyItem,				// 2F	inv object
		kFormType_IdleMarker,				// 30
		kFormType_Note,						// 31	inv object
		kFormType_ConstructibleObject,		// 32	inv object
		kFormType_Projectile,
		kFormType_LeveledItem,				// 34	inv object
		kFormType_Weather,
		kFormType_Climate,
		kFormType_Region,
		kFormType_NAVI,						// 38
		kFormType_Cell,
		kFormType_REFR,						// 3A
		kFormType_ACHR,						// 3B
		kFormType_ACRE,						// 3C
		kFormType_PMIS,						// 3D
		kFormType_PGRE,						// 3E
		kFormType_PBEA,						// 3F
		kFormType_PFLA,						// 40
		kFormType_WorldSpace,
		kFormType_Land,
		kFormType_NavMesh,
		kFormType_TLOD,
		kFormType_DIAL,
		kFormType_INFO,
		kFormType_Quest,
		kFormType_Idle,						// 48
		kFormType_Package,
		kFormType_CombatStyle,
		kFormType_LoadScreen,
		kFormType_LeveledSpell,
		kFormType_ANIO,
		kFormType_Water,
		kFormType_EffectShader,
		kFormType_TOFT,						// 50	table of Offset (see OffsetData in Worldspace)
		kFormType_Explosion,
		kFormType_Debris,
		kFormType_ImageSpace,
		kFormType_ImageSpaceModifier,
		kFormType_ListForm,					// 55
		kFormType_Perk,
		kFormType_BodyPartData,
		kFormType_AddonNode,				// 58
		kFormType_ActorValueInfo,
		kFormType_RadiationStage,
		kFormType_CameraShot,
		kFormType_CameraPath,
		kFormType_VoiceType,
		kFormType_ImpactData,
		kFormType_ImpactDataSet,
		kFormType_ARMA,						// 60
		kFormType_EncounterZone,
		kFormType_Message,
		kFormType_Ragdoll,
		kFormType_DOBJ,
		kFormType_LightingTemplate,
		kFormType_SoundFile,
		kFormType_ItemMod,					// 67	inv object
		kFormType_Reputation,				// 68
		kFormType_PCBE,						// 69 Continuous Beam
		kFormType_Recipe,
		kFormType_RecipeCategory,
		kFormType_CasinoChip,				// 6C	inv object
		kFormType_Casino,
		kFormType_LoadScreenType,
		kFormType_MediaSet,
		kFormType_MediaLocationController,	// 70
		kFormType_Challenge,
		kFormType_AmmoEffect,
		kFormType_CaravanCard,				// 73	inv object
		kFormType_CaravanMoney,				// 74	inv object
		kFormType_CaravanDeck,
		kFormType_DehydrationStages,
		kFormType_HungerStages,
		kFormType_SleepDeprivationStages,	// 78

		kFormType_Apparatus = 254, // for compatibility
	};
	
	enum FormFlags {
		kFormFlags_Initialized		= 0x00000008,
		kFormFlags_NotCastShadows	= 0x00000200,
		kFormFlags_QuestItem		= 0x00000400,
		kFormFlags_IsPermanent		= 0x00000800,
		kFormFlags_DontSaveForm		= 0x00004000,
		kFormFlags_Compressed		= 0x00040000,
	};

	virtual void*		Destroy(bool noDealloc);			// func_00C in GECK ?? I think ??
	virtual void		Unk_05();						// Might be set default value (called from constructor)
	virtual void		Unk_06();						// Might be clear values
	virtual bool		Unk_07();
	virtual bool		LoadForm(ModInfo* modInfo);		// func_010 in GECK
	virtual bool		Unk_09(void* arg);					// points to LoadForm on TESForm
	virtual bool		AppendForm(ModInfo* modInfo);		// (ie SaveForm + append to modInfo)
	virtual void		SaveForm(void);						// saves in same format as in .esp	//	func_013 in GECK
	virtual bool		LoadForm2(ModInfo* modInfo);		// just calls LoadForm
	virtual void		WriteFormInfo(ModInfo* modInfo);	// does some saving stuff, then calls Fn0A
	virtual bool		Unk_0E(void* arg);					// prepares a GRUP formInfo
	virtual bool		Sort(TESForm* form);				// returns if the argument is "greater or equal" to this form
	virtual TESForm*	CreateForm(void* arg0, void* mapToAddTo);	// makes a new form, 
	virtual void		Unk_11(void* arg);
	virtual void		MarkAsModified(UInt32 changedFlags);		// enable changed flag?
	virtual void		MarkAsUnmodified(UInt32 changedFlags);		// disable changed flag?
	virtual UInt32		GetSaveSize(UInt32 changedFlags);	// bytes taken by the delta flags for this form, UNRELIABLE, not (always) overriden
	virtual void		Unk_15(void* arg);					// collect referenced forms?
	virtual void		SaveGame(UInt32 changedFlags);		// Used as part of CopyFromBase with LoadGame.
	virtual void		LoadGame(void* arg);				// load from BGSLoadFormBuffer arg
	virtual void		LoadGame2(UInt32 changedFlags);		// load from TESSaveLoadGame
	virtual void		Unk_19(void* arg);
	virtual void		Unk_1A(void* arg0, void* arg1);
	virtual void		Unk_1B(void* arg0, void* arg1);
	virtual void		Revert(UInt32 changedFlags);		// reset changes in form
	virtual void		Unk_1D(void* arg);
	virtual void		Unk_1E(void* arg);
	virtual bool		Unk_1F(void* arg);
	virtual void		Unk_20(void* arg);
	virtual void		Unk_21(void* arg);
	virtual void		InitItem();
	virtual UInt32		GetTypeID();
	virtual void		GetDebugName(BSString* dst);
	virtual bool		IsQuestItem();
	virtual bool		Unk_26();		// 00000040
	virtual bool		Unk_27();		// 00010000
	virtual bool		Unk_28();		// 00010000
	virtual bool		Unk_29();		// 00020000
	virtual bool		Unk_2A();		// 00020000
	virtual bool		Unk_2B();		// 00080000
	virtual bool		Unk_2C();		// 02000000
	virtual bool		Unk_2D();		// 40000000
	virtual bool		Unk_2E();		// 00000200
	virtual void		Unk_2F(bool set);	// 00000200
	virtual bool		Unk_30();		// returns false
	virtual void		Unk_31(bool set);	// 00000020 then calls Fn12 MarkAsModified
	virtual void		Unk_32(bool set);	// 00000002 with a lot of housekeeping
	virtual void		SetQuestItem(bool set);	// 00000400 then calls Fn12 MarkAsModified
	virtual void		Unk_34(bool set);	// 00000040 then calls Fn12 MarkAsModified
	virtual void		Unk_35(bool set);	// 00010000 then calls Fn12 MarkAsModified
	virtual void		Unk_36(bool set);	// 00020000
	virtual void		Unk_37();		// write esp format
	virtual void		readOBNDSubRecord(ModInfo* modInfo);	// read esp format
	virtual bool		Unk_39();
	virtual bool		Unk_3A();
	virtual bool		Unk_3B();
	virtual bool		Unk_3C();	// is REFR
	virtual bool		Unk_3D();
	virtual bool		Unk_3E();
	virtual bool		Unk_3F();	// returnTrue for refr whose baseForm is a TESActorBase
	virtual bool		IsActor();
	virtual UInt32		Unk_41();
	virtual void		CopyFrom(const TESForm* form);
	virtual bool		Compare(TESForm* form);
	virtual bool		CheckFormGRUP(void* arg);	// Checks the group is valid for the form
	virtual void		InitFormGRUP(void* dst, void* arg1);	// Fills the groupInfo with info valid for the form
	virtual bool		Unk_46();
	virtual bool		Unk_47();
	virtual bool		Unk_48(UInt32 formType);	// returns if the same FormType is passed in
	virtual bool		Unk_49(void* arg0, void* arg1, void* arg2, void* arg3, void* arg4);	// looks to be func33 in Oblivion
	virtual void		SetID(UInt32 ID, bool generateID);
	virtual const char* GetName();	// not sure which objects this works on, doesn't seem to work on player or random objects
	virtual const char* GetEditorName(); // returns nothing at runtime (return the editorname for TESObjectCELL)
	virtual bool		SetEditorName(const char* name);

	enum {
		kModified_FormFlags = 0x00000001,
		kModified_GoldValue = 0x08,
		kModified_Name		= 0x80
	};

	void				GenerateID(UInt32 ID) { SetID(ID, 1); }

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
		kPackageFlag_OffersServices =			1 << 0,
		kPackageFlag_MustReachLocation =		1 << 1,
		kPackageFlag_MustComplete =				1 << 2,
		kPackageFlag_LockDoorsAtStart =			1 << 3,
		kPackageFlag_LockDoorsAtEnd =			1 << 4, 	// set by CHANGE_PACKAGE_WAITING ?
		kPackageFlag_LockDoorsAtLocation =		1 << 5,
		kPackageFlag_UnlockDoorsAtStart =		1 << 6,
		kPackageFlag_UnlockDoorsAtEnd =			1 << 7,
		kPackageFlag_UnlockDoorsAtLocation =	1 << 8,
		kPackageFlag_ContinueIfPCNear =			1 << 9,
		kPackageFlag_OncePerDay =				1 << 10,
		kPackageFlag_Unk11 =					1 << 11,
		kPackageFlag_SkipFalloutBehavior =		1 << 12,
		kPackageFlag_AlwaysRun =				1 << 13,
		kPackageFlag_Unk14 =					1 << 14,
		kPackageFlag_NeverRun =					1 << 15,	// Save only ?
		kPackageFlag_Unk16 =					1 << 16,
		kPackageFlag_AlwaysSneak =				1 << 17,
		kPackageFlag_AllowSwimming =			1 << 18,
		kPackageFlag_AllowFalls =				1 << 19,
		kPackageFlag_ArmorUnequipped =			1 << 20,
		kPackageFlag_WeaponsUnequipped =		1 << 21,
		kPackageFlag_DefensiveCombat =			1 << 22,
		kPackageFlag_WeaponsDrawn =				1 << 23,
		kPackageFlag_NoIdleAnims =				1 << 24,
		kPackageFlag_PretendInCombat =			1 << 25,
		kPackageFlag_ContinueDuringCombat =		1 << 26,
		kPackageFlag_NoCombatAlert =			1 << 27,
		kPackageFlag_NoWarnAttackBehavior =		1 << 28,
		kPackageFlag_Unk29 =					1 << 29,
		kPackageFlag_Unk30 =					1 << 30,
		kPackageFlag_Unk31 =					1 << 31
	};

	enum {	// From OBSE and FNVEdit. Runtimes has 0x24 types!
		kPackageType_Find =	0,		// 00
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
		kPackageType_Unk11,
		kPackageType_Sandbox,
		kPackageType_Patrol,
		kPackageType_Guard,
		kPackageType_Dialogue,
		kPackageType_UseWeapon,			// 10

		// unless shown otherwise kPackageType_CombatController,	// Actor::GetCombatController returns package only if type matches this
		// start conversation can lead to a package of type 1C, which is recorded in PlayerCharacter::Unk0224

		kPackType_MAX
	};

	// 8
	struct PackageTime {
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
			kMonth_Autumn,	// september, august, november (in Geck)
			kMonth_Winter,	// december, january, february

			kMonth_Any = 0xFF,
		};

		enum {
			kWeekday_Sundays = 0,
			kWeekday_Morndays,
			kWeekday_Tuesdays,
			kWeekday_Wednesdays,
			kWeekday_Thursdays,
			kWeekday_Frydays,
			kWeekday_Saturdays,
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
		kObjectType_None	=	0,
		kObjectType_Activators,
		kObjectType_Armor,
		kObjectType_Books,
		kObjectType_Clothing,
		kObjectType_Containers,
		kObjectType_Doors,
		kObjectType_Ingredients,
		kObjectType_Lights,
		kObjectType_Misc,
		kObjectType_Flora,
		kObjectType_Furniture,
		kObjectType_WeaponsAny,
		kObjectType_Ammo,
		kObjectType_NPCs,
		kObjectType_Creatures,
		kObjectType_Keys,				//	10
		kObjectType_Alchemy,
		kObjectType_Food,
		kObjectType_AllCombatWearable,
		kObjectType_AllWearable,
		kObjectType_WeaponsRanged,
		kObjectType_WeaponsMelee,
		kObjectType_WeaponsNone,
		kObjectType_ActorEffectAny,
		kObjectType_ActorEffectRangeTarget,
		kObjectType_ActorEffectRangeTouch,
		kObjectType_ActorEffectRangeSelf,
		kObjectType_ActorsAny,

		kObjectType_Max,						//	1E
	};

	class LocationData {
	public:
		enum {
			kPackLocation_NearReference		= 0,
			kPackLocation_InCell			= 1,
			kPackLocation_CurrentLocation	= 2,
			kPackLocation_EditorLocation	= 3,
			kPackLocation_ObjectID			= 4,
			kPackLocation_ObjectType		= 5,
			kPackLocation_LinkedReference	= 6,

			kPackLocation_Max,
		};

		UInt8		locationType;	// 000
		UInt8		pad[3];
		UInt32		radius;			// 004
		ObjectType  object;			// 008
	};

	enum {
		kTargetType_Refr		= 0,
		kTargetType_BaseObject	= 1,
		kTargetType_TypeCode	= 2,
		
		kTargetType_Max	= 3,
	};

	class TargetData {
	public:
		UInt8		targetType;	// 00
		UInt8		pad[3];		// 01
		ObjectType	target;		// 04
		UInt32		count;		// 08 can be distance too
		float		unk0C;		// 0C
	};

	enum eProcedure {			// UInt32	// Checked the Geck Wiki. Not consistent with s_procNames (which has a diffferent order and 0x37 procedures)
		kProcedure_TRAVEL = 0,
		kProcedure_ACTIVATE,
		kProcedure_ACQUIRE,
		kProcedure_WAIT,
		kProcedure_DIALOGUE,
		kProcedure_GREET,
		kProcedure_GREET_DEAD,
		kProcedure_WANDER,
		kProcedure_SLEEP,
		kProcedure_OBSERVE_COMBAT,
		kProcedure_EAT,
		kProcedure_FOLLOW,
		kProcedure_ESCORT,
		kProcedure_COMBAT,
		kProcedure_ALARM,
		kProcedure_PURSUE,
		kProcedure_FLEE,					// 0x10
		kProcedure_DONE,
		kProcedure_YELD,
		kProcedure_TRAVEL_TARGET,
		kProcedure_CREATE_FOLLOW,
		kProcedure_GET_UP,
		kProcedure_MOUNT_HORSE,
		kProcedure_DISMOUNT_HORSE,
		kProcedure_DO_NOTHING,
		kProcedure_UNK019,
		kProcedure_UNK01A,
		kProcedure_ACCOMPANY,
		kProcedure_USE_ITEM_AT,
		kProcedure_SANDMAN,
		kProcedure_WAIT_AMBUSH,
		kProcedure_SURFACE,					// 0x20
		kProcedure_WAIT_FOR_SPELL,
		kProcedure_CHOOSE_CAST,
		kProcedure_FLEE_NON_COMBAT,
		kProcedure_REMOVE_WORN_ITEMS,
		kProcedure_SEARCH,
		kProcedure_CLEAR_MOUNT_POSITION,
		kProcedure_SUMMON_CREATURE_DEFEND,
		kProcedure_AVOID_AREA,
		kProcedure_UNEQUIP_ARMOR,
		kProcedure_PATROL,
		kProcedure_USE_WEAPON,
		kProcedure_DIALOGUE_ACTIVATE,
		kProcedure_GUARD,
		kProcedure_SANDBOX,
		kProcedure_USE_IDLE_MARKER,
		kProcedure_TAKE_BACK_ITEM,
		kProcedure_SITTING,					// 0x30
		kProcedure_MOVEMENT_BLOCKED,
		kProcedure_CANIBAL_FEED,			// 0x32

		kProcedure_MAX						// 0x33
	};

	// In DialoguePackage, there are 0x58 virtual functions (including 0x4E from TESForm)

	UInt32				procedureArrayIndex;	// 018 index into array of array of eProcedure terminated by 0x2C. -1 if no procedure array exists for package type.
	UInt32				packageFlags;		// 01C
	UInt8				type;				// 020
	UInt8				pad021[1];			// 021
	UInt16				behaviorFlags;		// O22
	UInt32				specificFlags;		// 024
	TESPackageData*		packageData;		// 028
	LocationData*		location;			// 02C
	TargetData*			target;				// 030	target ?
	UInt32				unk034;				// 034	idles
	PackageTime			time;				// 038
	UInt32				unk040[(0x80 - 0x40) >> 2];		// 040	040 is a tList of Condition, 7C is an Interlocked counter
};
assert(sizeof(TESPackage) == 0x80);

class PackageInfo {
public:
	TESPackage*		package;		// 00
	TESPackageData*	packageData;	// 04
	TESObjectREFR*	targetRef;		// 08
	UInt32			unk0C;			// 0C	Initialized to 0FFFFFFFFh, set to 0 on start
	float			unk10;			// 10	Initialized to -1.0	. Set to GameHour on start so some time
	UInt32			flags;			// 14	Flags, bit0 would be not created and initialized
};
assert(sizeof(PackageInfo) == 0x18);

class TESIdleForm : public TESForm {
public:
	enum AnimFlag {
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

	void				SetFile(const char* Name) { animModel.nifPath.Set(Name); }

	TESModelAnim		animModel;		// 018
	TList<void*>		conditions;		// 030 Condition list
	UInt8				animFlags;		// 038	animation group and other flags
	UInt8				loopMin;		// 039
	UInt8				loopMax;		// 03A
	UInt8				fil03B;			// 03B
	UInt16				replayDelay;	// 03C
	UInt8				flags;			// 03E	bit0 is No attacking
	UInt8				fil03F;			// 03F
	UInt32				unk040;			// 040	NiFormArray, contains all idle anims in path if eIFgf_flagUnknown is set
	TESIdleForm*		parent;			// 044
	TESIdleForm*		previous;		// 048
	BSString			str04C;			// 04C
};
assert(sizeof(TESIdleForm) == 0x54);

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

	enum {
		eColor_SkyUpper = 0,
		eColor_Fog = 1,
		eColor_CloudsLower = 2,
		eColor_Ambient = 3,
		eColor_Sunlight = 4,
		eColor_Sun = 5,
		eColor_Stars = 6,
		eColor_SkyLower = 7,
		eColor_Horizon = 8,
		eColor_CloudsUpper = 9,
		eColor_Lighting = 10,
	};

	enum {
		eTime_Sunrise = 0,
		eTime_Day = 1,
		eTime_Sunset = 2,
		eTime_Night = 3,
		eTime_Midnight = 4,
		eTime_HighNoon = 5,
	};

	enum WeatherType {
		kType_None = 0,
		kType_Pleasant = 1,
		kType_Cloudy = 2,
		kType_Rainy = 4,
		kType_Snow = 8,
	};

	struct ColorData {
		RGBA colors[6];
	};

	struct FogInfo {
		float nearFog;
		float farFog;
		float power;
	};

	struct SoundData {
		UInt32 ID;		// refID of TESSound
		UInt32 type;	// 0 - Default; 1 - Precip; 2 - Wind; 3 - Thunder
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

	UInt32					unk018;						// 018
	void*					imageSpaceMods[6];			// 01C TESImageSpaceModifier*
	TESTexture				textureLayers[4];			// 034
	UInt8					cloudSpeed[4];				// 064
	UInt32					cloudColor[4][6];			// 068
	TESModel				model;						// 0C8
	UInt8					windSpeed;					// 0E0
	UInt8					cloudSpeedLower;			// 0E1
	UInt8					cloudSpeedUpper;			// 0E2
	UInt8					transDelta;					// 0E3
	UInt8					sunGlare;					// 0E4
	UInt8					sunDamage;					// 0E5
	UInt8					precipitationBeginFadeIn;	// 0E6
	UInt8					precipitationEndFadeOut;	// 0E7
	UInt8					lightningBeginFadeIn;		// 0E8
	UInt8					lightningEndFadeOut;		// 0E9
	UInt8					lightningFrequency;			// 0EA
	UInt8					weatherType;				// 0EB
	DWORD					lightningColor;				// 0EC color in hex
	FogInfo					fogDay;						// 0F0
	FogInfo					fogNight;					// 0FC
	ColorData				colors[10];					// 108
	TList<SoundData>		sounds;						// 1F8
	float					hdrInfo[14];				// 200 for the compatibility with OR (to review)
	UInt32					unk238[77];					// 238
};
assert(sizeof(TESWeather) == 0x36C);

class TESWeatherEx : public TESWeather {
public:
	ColorData	colorsb[TESWeather::kNumColorTypes];
	char		EditorName[40];
};
assert(sizeof(TESWeatherEx) == 0x484);

class TESClimate : public TESForm {
public:
	class WeatherType {
	public:
		TESWeather* weather;
		UInt32		chance;
		void*		global; //TESGlobal*
	};

	TESModel			nightSky;			// 18
	TList<WeatherType>	weatherTypes;		// 30
	TESTexture			sun;				// 38
	TESTexture			sunGlare;			// 44
	UInt8				sunriseBegin;		// 50
	UInt8				sunriseEnd;			// 51
	UInt8				sunsetBegin;		// 52
	UInt8				sunsetEnd;			// 53
	UInt8				volatility;			// 54
	UInt8				phaseLength;		// 55
	UInt8				pad56[2];			// 56
};
assert(sizeof(TESClimate) == 0x58);

class TESWaterForm : public TESForm {
public:
	enum WaterType {
		kWaterType_Blood,
		kWaterType_Lava,
		kWaterType_Normal,
	};

	struct Data34 {
		UInt32	unk0;	// 0
		UInt32	unk4;	// 4
		UInt32	unk8;	// 8
		UInt32	unkC;	// C
	};

	// E4 (to adjust....copied from Skyrim)
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

	UInt32					GetWaterType() { return kWaterType_Normal; };
	void					RemoveUnderwaterFog() { properties.fogAmountUW = 0.0f; properties.fogNearUW = 9995.0f; properties.fogFarUW = 10000.0f; }
	RGBA*					GetShallowColor() { return &properties.shallowColor; }
	RGBA*					GetDeepColor() { return &properties.deepColor; }

	TESFullName				fullName;		// 018
	TESAttackDamageForm		attackDamage;	// 024
	UInt32					unk02C;			// 02C
	UInt32					unk030;			// 030
	Data34					unk034;			// 034
	Data34					unk044;			// 044
	Data34					unk054;			// 054
	TESTexture				unk064;			// 064
	UInt32					unk070;			// 070
	Data34					unk074;			// 074
	Properties				properties;		// 084
	UInt32					unk168[11];		// 168
};
assert(sizeof(TESWaterForm) == 0x194);

class TESWorldSpace : public TESForm {
public:
	struct CoordXY {
		float	X;	// 000
		float	Y;	// 004
	};

	struct DCoordXY {
		SInt32	X;	// 000
		SInt32	Y;	// 004
	};

	struct WCoordXY {
		SInt16	X;	// 000
		SInt16	Y;	// 002
	};

	struct OffsetData {
		UInt32**	unk000;	// 000 array of UInt32 stored in OFST record (indexed by relative CellXY).
		CoordXY		min;		// 004 NAM0
		CoordXY		max;		// 00C NAM9
		UInt32		fileOffset;	// 014 TESWorldspace file offset in modInfo
	};

	struct MapData {
		DCoordXY	usableDimensions;
		WCoordXY	cellNWCoordinates;
		WCoordXY	cellSECoordinates;
	};

	class LODData {
	public:
		class LODNode {
		public:
			LODData*		parent;			// 00
			UInt32			lodLevel;		// 04
			UInt32			cellXY;			// 08
			UInt8			byte0C;			// 0C
			UInt8			byte0D;			// 0D
			UInt8			byte0E;			// 0E
			UInt8			byte0F;			// 0F
			UInt32			ukn10;			// 10
			void*			object;			// 14
			UInt32			ukn18;			// 18
			UInt32			ukn1C;			// 1C
			LODNode*		linked[4];		// 20
			UInt32			unk30;			// 30
			float			flt34;			// 34
			float			flt38;			// 38
			float			flt3C;			// 3C
			float			flt40;			// 40
			float			flt44;			// 44
			float			flt48;			// 48
			float			flt4C;			// 4C
			UInt32			unk50;			// 50
			UInt32			ukn54;			// 54
			UInt32			ukn58;			// 58
			UInt8			byte5C;			// 5C
			UInt8			byte5D;			// 5D
			UInt8			byte5E;			// 5E
			UInt8			byte5F;			// 5F
		};

		TESWorldSpace*		world;		// 00
		LODNode*			lodNode;	// 04
		NiNode*				node08;		// 08
		NiNode*				node0C;		// 0C
		UInt32				coordNW;	// 10
		UInt32				coordSE;	// 14
		UInt32				ukn18;		// 18
		UInt32				ukn1C;		// 1C
		UInt32				ukn20;		// 20
		UInt32				lodLevel;	// 24
		UInt8				byte28;		// 28
		UInt8				byte29;		// 29
		UInt8				byte2A;		// 2A
		UInt8				byte2B;		// 2B
		UInt32				array2C[0x10];	// 2C BSSimpleArray<TESObjectREFR>
	};

	class ImpactData {
	public:
		enum MaterialType {
		  eMT_Stone = 0,
		  eMT_Dirt,
		  eMT_Grass,
		  eMT_Glass,
		  eMT_Metal,
		  eMT_Wood,
		  eMT_Organic,
		  eMT_Cloth,
		  eMT_Water,
		  eMT_HollowMetal,
		  eMT_OrganicBug,
		  eMT_OrganicGlow,

		  eMT_Max
		};

		NiTMap<BGSImpactData*, BGSImpactData*>	impactImpactMap[eMT_Max];	// 000
		char									footstepMaterials[0x12C];	// 030
	};

	TESFullName				fullName;			// 018 confirmed
	TESTexture				texture;			// 024 confirmed ICON
	NiTMap<UInt32, TESObjectCELL>*	cellMap;			// 030 confirmed
	TESObjectCELL*			cell;				// 034 should be the Permanent cell
	UInt32					unk038;				// 038
	LODData*				lodData;			// 03C looks to be the LOD data (That is what is returned when checking the parent "Use LOD data" flag)
	TESClimate*				climate;			// 040 confirmed CNAM
	void*					imageSpace;		// 044 confirmed INAM TESImageSpace*
	ImpactData*				impacts;			// 048 confirmed
	UInt8					flags;				// 04C confirmed DATA
	UInt8					unk04D;				// 04D filler
	UInt16					parentFlags;		// 04E init'd to FF if has a parent. 5 is use ImageSpace, 4 is use parent climate, 3 is use parent Water, 1 is use parent LOD data, 0 is use parent LAND data
	NiTMap<UInt32, void*>	pointerMap;			// 050 confirmed NiTPointerMap<BSSimpleList<TESObjectREFR>>
	TList<void*>			lst060;				// 060
	TList<void*>			lst068;				// 068 confirmed as tList
	TESWorldSpace*			parent;				// 070 confirmed
	TESWaterForm*			waterFormFirst;		// 074 confirmed NAM2
	TESWaterForm*			waterFormLast;		// 078 confirmed NAM3 LOD Water type for xEdit
	float					waterHeight;		// 07C confirmed NAM4
	MapData					mapData;			// 080 confirmed MNAM
	float					worldMapScale;		// 090 confirmed ONAM for three floats
	float					worldMapCellX;		// 094 confirmed
	float					worldMapCellY;		// 098 confirmed
	void*					music;				// 09C confirmed ZNAM BGSMusicType*
	CoordXY					min;				// 0A0 confirmed NAM0 min of all Offset_Data.min
	CoordXY					max;				// 0A8 confirmed NAM9 max of all Offset_data.max
	NiTMap<ModInfo*, OffsetData*> offsetMap;			// 0B0 guarded by an isESM NiTMapBase<ModInfo *,TESWorldSpace::Offset_Data *>
	BSString				str0C0;				// 0C0
	float					defaultLandHeight;	// 0C8 confirmed DNAM for the two
	float					defaultWaterHeight;	// 0CC
	void*					encounterZone;		// 0D0 confirmed BGSEncounterZone*
	TESTexture				canopyShadow;		// 0D4 confirmed NNAM
	TESTexture				waterNoiseTexture;	// 0E0 confirmed XNAM
};
assert(sizeof(TESWorldSpace) == 0xEC);

class TESGlobal : public TESForm {
public:
	BSString	name;		// 018
	UInt8		type;		// 020
	UInt8		pad21[3];	// 021
	float		data;		// 024
};
assert(sizeof(TESGlobal) == 0x028);

class TESRegion : public TESForm {
public:
	void*			dataEntries;	// 18 RegionDataEntryList*
	void*			areaEntries;	// 1C RegionAreaEntryList*
	TESWorldSpace*	worldSpace;		// 20
	TESWeather*		weather;		// 24
	UInt32			unk28[4];		// 28
};
assert(sizeof(TESRegion) == 0x38);

class TESRegionEx : public TESRegion {
public:
	char		EditorName[40];		// 38
};
assert(sizeof(TESRegionEx) == 0x060);

class TESRegionList {
public:
	void**			_vtbl;		// 000
	TList<TESRegion> list;		// 004
};
assert(sizeof(TESRegionList) == 0x0C);

class TESQuest : public TESForm {
public:
	virtual char*	GetQuestName() const;			// 4E

	class QuestStageItem;

	class StageEntry { // From Oblivion
	public:
		enum {
			kFlag_CompleteQuest = 1 << 0,
		};

		UInt8					index;	// as defined in CS, not necessarily sequential
		UInt8					flags;
		UInt8					pad[2];
		TList<QuestStageItem>	itemList;
	};

	union LocalVarOrObj {
		void*	objective;		// BGSQuestObjective*
		void*	varInfoIndex;	// VariableInfo*
	};
	
	TESScriptableForm			scriptable;				// 018
	TESIcon						icon;					// 024
	TESFullName					fullName;				// 030
	UInt8						flags;					// 03C
	UInt8						priority;				// 03D
	UInt8						pad03E[2];				// 03E
	float						questDelayTime;			// 040
	TList<StageEntry>			stageList;				// 044
	TList<LocalVarOrObj>		VarOrObjectives;		// 04C
	TList<void*>				conditions;				// 054 TList<Condition*>
	ScriptEventList*			scriptEventList;		// 05C
	UInt8						currentStage;			// 060
	UInt8						pad061[3];				// 061
	BSString					editorName;				// 064
};
assert(sizeof(TESQuest) == 0x6C);

class TESObject : public TESForm {
public:
	virtual UInt32	Unk_4E();
	virtual bool	Unk_4F();
	virtual UInt32	Unk_50();
	virtual bool	Unk_51();
	virtual void	Unk_52(void* arg);
	virtual NiNode* Unk_53(TESObjectREFR* refr, void* arg1);
	virtual void	Unk_54(void* arg);
	virtual bool	IsInternal();
	virtual bool	IsInternalMarker();
	virtual void	Unk_57();
	virtual bool	Unk_58();	// BoundObject: Calls Unk_5F on the object model
	virtual bool	Unk_59(void* arg);
	virtual void	Unk_5A(void* arg0, void* arg1);
	virtual UInt32	Unk_5B();
	virtual UInt32	Unk_5C();
	virtual bool	Unk_5D(TESObjectREFR* refr);	// if false, no NiNode gets returned by Unk_53, true for NPC
};
assert(sizeof(TESObject) == 0x018);

class TESBoundObject : public TESObject {
public:
	virtual NiNode* CreateNiNode(TESObjectREFR* refr);	// calls Fn53, for NPC calls ReadBones, for LevelledActor level them if necessary
	virtual bool	Unk_5F(void);

	BoundObjectListHead*	head;		// 018
	TESBoundObject*			prev;		// 01C
	TESBoundObject*			next;		// 020
	SInt16					bounds[6];	// 024
};
assert(sizeof(TESBoundObject) == 0x030);

class TESBoundAnimObject : public TESBoundObject {};
assert(sizeof(TESBoundAnimObject) == 0x30);

class TESSoundFile : public BaseFormComponent {
public:
	virtual void	Set(const char* str);
	BSString		fileName;	// 04
};
assert(sizeof(TESSoundFile) == 0x0C);

class TESSound : public TESBoundAnimObject {
public:
	enum SoundFlags {
		kFlag_RandomFrequencyShift	= 1,
		kFlag_PlayAtRandom			= 2,
		kFlag_EnvironmentIgnored	= 4,
		kFlag_RandomLocation		= 8,
		kFlag_Loop					= 16,
		kFlag_MenuSound				= 32,
		kFlag_2D					= 64,
		kFlag_360LFE				= 128,
		kFlag_DialogueSound			= 256,
		kFlag_EnvelopeFast			= 512,
		kFlag_EnvelopeSlow			= 1024,
		kFlag_2DRadius				= 2048,
		kFlag_MuteWhenSubmerged		= 4096,
		kFlag_StartAtRandomPosition = 8192,
	};

	void			SetFile(const char* Name) { soundFile.fileName.Set(Name); }

	TESSoundFile	soundFile;				// 30

	UInt32			unk3C;					// 3C
	UInt16			unk40;					// 40
	UInt16			unk42;					// 42
	UInt8			minAttenuationDist;		// 44
	UInt8			maxAttenuationDist;		// 45
	SInt16			frequencyAdj;			// 46
	UInt32			soundFlags;				// 48
	UInt16			staticAttenuation;		// 4C
	UInt8			endsAt;					// 4E
	UInt8			startsAt;				// 4F
	UInt16			attenuationCurve[5];	// 50
	UInt16			reverbAttenuation;		// 5A
	UInt32			priority;				// 5C
	UInt32			unk60;					// 60
	UInt32			unk64;					// 64
};
assert(sizeof(TESSound) == 0x68);

class TESObjectSTAT : public TESBoundObject {
public:
	TESModelTextureSwap		model;		// 30
	UInt32					unk50[2];	// 50
};
assert(sizeof(TESObjectSTAT) == 0x058);

class TESObjectIMOD : public TESBoundObject {
public:
	TESFullName					name;				// 030
	TESModelTextureSwap			model;				// 03C
	TESIcon						icon;				// 05C
	TESScriptableForm			scriptForm;			// 068
	TESDescription				description;		// 074
	TESValueForm				value;				// 07C
	TESWeightForm				weight;				// 084
	BGSDestructibleObjectForm	destructible;		// 08C
	BGSMessageIcon				messageIcon;		// 094
	BGSPickupPutdownSounds		pickupPutdownSounds;// 0A4
};
assert(sizeof(TESObjectIMOD) == 0x0B0);

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
		kLightFlags_SpotShadow =	0x400
	};

	TESFullName					fullName;		// 030
	TESModelTextureSwap			modelSwap;		// 03C
	TESIcon						icon;			// 05C
	BGSMessageIcon				messageIcon;	// 068
	TESScriptableForm			scriptable;		// 078
	TESWeightForm				weight;			// 084
	TESValueForm				value;			// 08C
	BGSDestructibleObjectForm	destructible;	// 094
	SInt32						time;			// 09C
	UInt32						radius;			// 0A0
	UInt8						red;			// 0A4
	UInt8						green;			// 0A5
	UInt8						blue;			// 0A6
	UInt8						padA7;			// 0A7
	UInt32						lightFlags;		// 0A8
	float						falloffExp;		// 0AC
	float						FOV;			// 0B0
	float						fadeValue;		// 0B4
	TESSound					*sound;			// 0B8
	UInt32						padBC[3];		// 0BC
};
assert(sizeof(TESObjectLIGH) == 0x0C8);

class TESObjectWEAP : public TESBoundObject {
public:
	enum WeaponType {
		kWeapType_HandToHandMelee = 0,
		kWeapType_OneHandMelee,
		kWeapType_TwoHandMelee,
		kWeapType_OneHandPistol,
		kWeapType_OneHandPistolEnergy,
		kWeapType_TwoHandRifle,
		kWeapType_TwoHandAutomatic,
		kWeapType_TwoHandRifleEnergy,
		kWeapType_TwoHandHandle,
		kWeapType_TwoHandLauncher,
		kWeapType_OneHandGrenade,
		kWeapType_OneHandMine,
		kWeapType_OneHandLunchboxMine,
		kWeapType_OneHandThrown,
		kWeapType_Last	// During animation analysis, player weapon can be classified as 0x0C = last
	};

	enum EWeaponSounds {
		kWeapSound_Shoot3D = 0,
		kWeapSound_Shoot2D,
		kWeapSound_Shoot3DLooping,
		kWeapSound_NoAmmo,
		kWeapSound_Swing = kWeapSound_NoAmmo,
		kWeapSound_Block,
		kWeapSound_Idle,
		kWeapSound_Equip,
		kWeapSound_Unequip
	};

	enum EHandGrip {
		eHandGrip_Default = 0xFF,
		eHandGrip_1 = 0xE6,
		eHandGrip_2 = 0xE7,
		eHandGrip_3 = 0xE8,
		eHandGrip_4 = 0xE9,
		eHandGrip_5 = 0xEA,
		eHandGrip_6 = 0xEB,
		eHandGrip_Count = 7,
	};

	enum EAttackAnimations {
		eAttackAnim_Default = 0xff,	// 11111111
		eAttackAnim_Attack3 = 0x26,	// 00100110
		eAttackAnim_Attack4 = 0x2c, // 00101100
		eAttackAnim_Attack5 = 0x32,	// 00110010
		eAttackAnim_Attack6 = 0x38, // 
		eAttackAnim_Attack7 = 0x3e,
		eAttackAnim_Attack8 = 0x44,
		eAttackAnim_AttackLeft = 0x1a,
		eAttackAnim_AttackLoop = 0x4a,
		eAttackAnim_AttackRight = 0x20,
		eAttackAnim_AttackSpin = 0x50,
		eAttackAnim_AttackSpin2 = 0x56,
		eAttackAnim_AttackThrow = 0x6d,
		eAttackAnim_AttackThrow2 = 0x73,
		eAttackAnim_AttackThrow3 = 0x79,
		eAttackAnim_AttackThrow4 = 0x7F,
		eAttackAnim_AttackThrow5 = 0x85,
		eAttackAnim_PlaceMine = 0x61,
		eAttackAnim_PlaceMine2 = 0x67,
		eAttackAnim_Count = 19,
	};

	enum ReloadAnim {
		eReload_A = 0,
		eReload_B,
		eReload_C,
		eReload_D,
		eReload_E,
		eReload_F,
		eReload_G,
		eReload_H,
		eReload_I,
		eReload_J,
		eReload_K,
		eReload_L,
		eReload_M,
		eReload_N,
		eReload_O,
		eReload_P,
		eReload_Q,
		eReload_R,
		eReload_S,
		eReload_W,
		eReload_X,
		eReload_Y,
		eReload_Z,
		eReload_Count,
	};

	enum EWeaponFlags1 {
		eFlag_IgnoresNormalWeapResist = 0x1,
		eFlag_IsAutomatic = 0x2,
		eFlag_HasScope = 0x4,
		eFlag_CantDrop = 0x8,
		eFlag_HideBackpack = 0x10,
		eFlag_EmbeddedWeapon = 0x20,
		eFlag_No1stPersonISAnims = 0x40,
		Eflag_NonPlayable = 0x80
	};

	enum EWeaponFlags2 {
		eFlag_PlayerOnly = 0x1,
		eFlag_NPCsUseAmmo = 0x2,
		eFlag_NoJamAfterReload = 0x4,
		eFlag_ActionPointOverride = 0x8,
		eFlag_MinorCrime = 0x10,
		eFlag_FixedRange = 0x20,
		eFlag_NotUsedNormalCombat = 0x40,
		eFlag_DamageToWeaponOverride = 0x80,
		eFlag_No3rdPersonISAnims = 0x100,
		eFlag_BurstShot = 0x200,
		eFlag_RumbleAlternate = 0x400,
		eFlag_LongBurst = 0x800,
	};

	enum EEmbedWeapAV {
		eEmbedAV_Perception = 0,
		eEmbedAV_Endurance,
		eEmbedAV_LeftAttack,
		eEmbedAV_RightAttack,
		eEmbedAV_LeftMobility,
		eEmbedAV_RightMobility,
		eEmbedAV_Brain,
	};

	enum EOnHit {
		eOnHit_Normal = 0,
		eOnHit_DismemberOnly,
		eOnHit_ExplodeOnly,
		eOnHit_NoDismemberOrExplode,
	};

	enum ERumblePattern {
		eRumblePattern_Constant = 0,
		eRumblePattern_Square,
		eRumblePattern_Triangle,
		eRumblePattern_Sawtooth
	};

	enum ECritDamageFlags {
		eCritDamage_OnDeath = 0x1
	};

	enum {
		kWeaponModEffect_None = 0,
		kWeaponModEffect_IncreaseDamage,
		kWeaponModEffect_IncreaseClipCapacity,
		kWeaponModEffect_DecreaseSpread,
		kWeaponModEffect_DecreaseWeight,
		kWeaponModEffect_Unused05,
		kWeaponModEffect_RegenerateAmmo,
		kWeaponModEffect_DecreaseEquipTime,
		kWeaponModEffect_IncreaseRateOfFire,		// 8
		kWeaponModEffect_IncreaseProjectileSpeed,
		kWeaponModEffect_IncreaseMaxCondition,
		kWeaponModEffect_Silence,
		kWeaponModEffect_SplitBeam,
		kWeaponModEffect_VATSBonus,
		kWeaponModEffect_IncreaseZoom,				// 14
	};

	// bases
	TESFullName					fullName;			// 030
	TESModelTextureSwap			textureSwap;		// 03C
	TESIcon						icon;				// 05C
	TESScriptableForm			scritpable;			// 068
	TESEnchantableForm			enchantable;		// 074
	TESValueForm				value;				// 084
	TESWeightForm				weight;				// 08C
	TESHealthForm				health;				// 094
	TESAttackDamageForm			attackDmg;			// 09C
	BGSAmmoForm					ammo;				// 0A4
	BGSClipRoundsForm			clipRounds;			// 0AC
	BGSDestructibleObjectForm	destructible;		// 0B4
	BGSRepairItemList			repairItemList;		// 0BC
	BGSEquipType				equipType;			// 0C4
	BGSPreloadable				preloadable;		// 0CC
	BGSMessageIcon				messageIcon;		// 0D0
	BGSBipedModelList			bipedModelList;		// 0E0
	BGSPickupPutdownSounds		pickupPutdownSounds;// 0E8

	UInt8				weaponType;			// 0F4
	UInt8				pad[3];
	float				animMult;			// 0F8
	float				reach;				// 0FC
	UInt8				weaponFlags1;		// 100
	UInt8				handGrip;			// 101
	UInt8				ammoUse;			// 102
	UInt8				reloadAnim;			// 103
	float				minSpread;			// 104
	float				spread;				// 108
	UInt32				unk10C;				// 10C
	float				sightFOV;			// 110
	UInt32				unk114;				// 114
	void*				projectile;			// 118 BGSProjectile*
	UInt8				baseVATSChance;		// 11C
	UInt8				attackAnim;			// 11D
	UInt8				numProjectiles;		// 11E
	UInt8				embedWeaponAV;		// 11F
	float				minRange;			// 120
	float				maxRange;			// 124
	UInt32				onHit;				// 128
	UInt32				weaponFlags2;		// 12C
	float				animAttackMult;		// 130
	float				fireRate;			// 134
	float				AP;					// 138
	float				rumbleLeftMotor;	// 13C
	float				rumbleRightMotor;	// 140
	float				rumbleDuration;		// 144
	float				damageToWeaponMult;	// 148
	float				animShotsPerSec;	// 14C
	float				animReloadTime;		// 150
	float				animJamTime;		// 154		
	float				aimArc;				// 158
	UInt32				weaponSkill;		// 15C - actor value
	UInt32				rumblePattern;		// 160 - reload anim?
	float				rumbleWavelength;	// 164
	float				limbDamageMult;		// 168
	UInt32				resistType;			// 16c - actor value
	float				sightUsage;			// 170
	float				semiAutoFireDelayMin;	// 174
	float				semiAutoFireDelayMax;	// 178
	UInt32				unk17C;				// 17C - 0-0x10: 0x8:str req 0x10: - skill req  - 0xb:kill impulse B158 - mod 1 val B15C - Mod 2 val Effects: 0x1: e(zoom) 0x2: a 0x3:0 0x4-6: Values c-e Mod Effects Val2:1-3 
	UInt32				effectMods[3];		// 180
	float				value1Mod[3];		// 18C
	UInt32				powerAttackAnimOverride;	// 198
	UInt32				strRequired;		// 19C
	UInt8				pad1A0;				// 1A0
	UInt8				modReloadAnim;		// 1A1
	UInt8				pad1A2[2];			// 1A2
	float				regenRate;			// 1A4
	float				killImpulse;		// 1A8
	float				value2Mod[3];		// 1AC
	float				impulseDist;		// 1B8
	UInt32				skillRequirement;	// 1BC
	UInt16				criticalDamage;		// 1C0
	UInt8				unk1C2[2];			// 1C2
	float				criticalPercent;	// 1C4
	UInt8				critDamageFlags;	// 1C8
	UInt8				pad1C9[3];			// 1C9
	SpellItem*			 criticalEffect;	// 1CC
	TESModel			shellCasingModel;	// 1DO
	TESModel			targetNIF;			// 1E8 - target NIF
	TESModel			model200;			// 200 - could be a texture swap
	UInt32				unk218;				// 218
	TESSound*			sounds[12];			// 21C
	void*				impactDataSet;		// 24C BGSImpactDataSet*
	TESObjectSTAT*		worldStatic;		// 250
	TESObjectSTAT*		mod1Static;			// 254
	TESObjectSTAT*		mod2Static;			// 258
	TESObjectSTAT*		mod3Static;			// 25C
	TESObjectSTAT*		mod12Static;		// 260
	TESObjectSTAT*		mod13Static;		// 264
	TESObjectSTAT*		mod23Static;		// 268
	TESObjectSTAT*		mod123Static;		// 26C
	TESModelTextureSwap	textureMod1;		// 270 Mod 1
	TESModelTextureSwap	textureMod2;		// 290 Mod 2
	TESModelTextureSwap	textureMod3;		// 2B0 Mod 3
	TESModelTextureSwap	textureMod12;		// 2D0 Mod 1-2
	TESModelTextureSwap	textureMod13;		// 2F0 Model 1-3
	TESModelTextureSwap	textureMod23;		// 310 Model 2-3
	TESModelTextureSwap	textureMod123;		// 330 Model 1-2-3
	TESObjectIMOD*		itemMod[3];			// 350
	BSString			embeddedNodeName;	// 35C
	UInt32				soundLevel;			// 364
	UInt32				unk368;				// 368
	UInt32				unk36C;				// 36C
	SpellItem*			VATSEffect;			// 370
	UInt32				unk374;				// 374
	UInt32				unk378;				// 378
	UInt32				unk37C;				// 37C
	UInt32				recharge;			// 380 maybe recharge
	UInt32				unk384;				// 384
};
assert(sizeof(TESObjectWEAP) == 0x388);

class BGSPerkEntry {
public:
	virtual void	Fn_00();
	virtual void	Fn_01();
	virtual void	Fn_02();
	virtual void	Fn_03();
	virtual void	Fn_04();
	virtual void	Fn_05();
	virtual void	Fn_06();
	virtual void	Fn_07();
	virtual void	Fn_08();
	virtual void	Fn_09();
	virtual void	Fn_0A();
	virtual void	Fn_0B();
	virtual void	Fn_0C();
	virtual void	Fn_0D();

	UInt8				rank;				// 04 +1 for value shown in GECK
	UInt8				priority;			// 05
	UInt16				type;				// 06 (Quest: 0xC24, Ability: 0xB27, Entry Point: 0xD16)
};
assert(sizeof(BGSPerkEntry) == 0x08);

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

	TESFullName				fullName;			// 18
	TESDescription			description;		// 24
	TESIcon					icon;				// 2C
	PerkData				data;				// 38
	TList<void*>			conditions;			// 40 Condition List
	TList<BGSPerkEntry>		entries;			// 48
};
assert(sizeof(BGSPerk) == 0x50);

class TESObjectREFRData {
public:
	UInt32	unk00;
	UInt32	unk04;
	float	waterHeight;
	float	unk0C;
	UInt32	unk10;		// flags most likely
	NiNode* niNode;
	// possibly more, need to find alloc
};
assert(sizeof(TESObjectREFRData) == 0x18);

class TESObjectCELL : public TESForm {
public:
	enum {
		kFlags0_Interior					= 1 << 0,
		kFlags0_HasWater					= 1 << 1,
		kFlags0_InvertFastTravelBehavior	= 1 << 2,
		kFlags0_PublicPlace					= 1 << 5,
		kFlags0_HandChanged					= 1 << 6,
		kFlags0_BehaveLikeExterior			= 1 << 7,
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
		int			directionalRotXY;
		int			directionalRotZ;
		float		directionalFade;
		float		fogClipDist;
		float		fogPower;
		UINT*		getValuesFrom;
	};
	
	struct StructC4 {
		NiNode*								niNode;		// 00
		TList<TESObjectREFR>				list04;		// 04
		NiTMap<TESObjectREFR*, NiNode*>		map0C;		// 0C
		NiTMap<TESForm*, TESObjectREFR*>	map1C;		// 1C
		NiTMap<TESObjectREFR*, NiNode*>		map2C;		// 2C
		NiTMap<TESObjectREFR*, NiNode*>		map3C;		// 3C
		TList<TESObjectREFR>				list4C;		// 4C
		TList<void>							list54;		// 54
		TList<TESObjectREFR>				list5C;		// 5C
	};
	
	TESWaterForm*			GetWaterForm() { return (TESWaterForm*)ThisCall(0x00547770, this); }
	float					GetWaterHeight() { return ThisCallF(0x005471E0, this); }
	ExtraHavok*				GetExtraHavok() { return (ExtraHavok*)extraDataList.GetExtraData(BSExtraData::ExtraDataType::kExtraData_Havok); }
	NiNode*					GetNode() { return structC4->niNode; }

	TESFullName				fullName;			// 018	// 030 in GECK
	UInt8					flags0;				// 024
	UInt8					flags1;				// 025
	UInt8					flags2;				// 026	// 5 or 6 would mean cell is loaded, name based on OBSE
	UInt8					unk027;				// 027
	ExtraDataList			extraDataList;		// 028
	union {										// 048
		CellCoordinates*	coords;				// if exterior
		LightingData*		lighting;			// if interior
	};
	TESObjectLAND*			land;				// 04C
	float					waterHeight;		// 050
	UInt32					unk54;				// 054
	TESTexture				noiseTexture;		// 058
	void*					navMeshArray;		// 064 BSSimpleArray<NavMesh>
	UInt32					unk68[15];			// 068	80 is CellRefLock semaphore
	UInt32					actorCount;			// 0A4
	UInt16					countVWD;			// 0A8
	UInt16					unk0AA;				// 0AA
	TList<TESObjectREFR>	objectList;			// 0AC
	NiNode*					niNode0B4;			// 0B4
	NiNode*					niNode0B8;			// 0B8
	UInt32					unk0BC;				// 0BC
	TESWorldSpace*			worldSpace;			// 0C0
	StructC4*				structC4;			// 0C4
	float					unk0C8;				// 0C8
	UInt32					unk0CC;				// 0CC
	UInt32					unk0D0;				// 0D0
	void*					portalGraph;		// 0D4 BSPortalGraph*
	BGSLightingTemplate*	lightingTemplate;	// 0D8
	UInt32					unk0DC;				// 0DC
};
assert(sizeof(TESObjectCELL) == 0xE0);

struct ActorHitInfo {
	TESObjectREFR*		source;			// 00
	Actor*				target;			// 04
	Projectile*			projectile;		// 08
	UInt32				unk0C;			// 0C
	SInt32				hitLocation;	// 10
	float				healthDmg;		// 14
	float				unk18;			// 18
	float				unk1C;			// 1C
	float				limbDmg;		// 20
	float				unk24;			// 24
	float				unk28;			// 28
	float				unk2C;			// 2C
	TESObjectWEAP*		weapon;			// 30
	float				healthPerc;		// 34
	UInt32				unk38[8];		// 38
	UInt32				flags;			// 58
	float				unk5C;			// 5C
	UInt32				unk60;			// 60
};
assert(sizeof(ActorHitInfo) == 0x064);

class BaseProcess {
public:
	virtual void	FreeThis(bool noDealloc);
	virtual void	Unk_01();
	virtual void	Unk_02();
	virtual void	Unk_03();
	virtual void	Unk_04();
	virtual void	Unk_05();
	virtual void	Unk_06();
	virtual void	Unk_07();
	virtual void	Unk_08();
	virtual void	Unk_09();
	virtual void	Unk_0A();
	virtual void	Unk_0B();
	virtual void	Unk_0C();
	virtual void	Unk_0D();
	virtual void	Unk_0E();
	virtual void	Unk_0F();
	virtual void	Unk_10();
	virtual void	Unk_11();
	virtual void	Unk_12();
	virtual void	Unk_13();
	virtual void	Unk_14();
	virtual void	Unk_15();
	virtual void	Unk_16();
	virtual void	Unk_17();
	virtual void	Unk_18();
	virtual void	Unk_19();
	virtual void	Unk_1A();
	virtual void	Unk_1B();
	virtual void	Unk_1C();
	virtual void	Unk_1D();
	virtual void	Unk_1E();
	virtual void	Unk_1F();
	virtual void	Unk_20();
	virtual void	Unk_21();
	virtual void	Unk_22();
	virtual void	Unk_23();
	virtual void	Unk_24();
	virtual void	Unk_25();
	virtual void	Unk_26();
	virtual void	Unk_27();
	virtual void	Unk_28();
	virtual void	Unk_29();
	virtual void	Unk_2A();
	virtual void	Unk_2B();
	virtual void	Unk_2C();
	virtual void	Unk_2D();
	virtual void	Unk_2E();
	virtual void	Unk_2F();
	virtual void	Unk_30();
	virtual void	Unk_31();
	virtual void	Unk_32();
	virtual void	Unk_33();
	virtual void	Unk_34();
	virtual void	Unk_35();
	virtual void	Unk_36();
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
	virtual void	Unk_45();
	virtual void	Unk_46();
	virtual void	Unk_47();
	virtual void	Unk_48();
	virtual void	Unk_49();
	virtual TESForm* GetLowProcess40();
	virtual void	Unk_4B();
	virtual void	Unk_4C();
	virtual void	Unk_4D();
	virtual void	Unk_4E();
	virtual void	Unk_4F();
	virtual void	Unk_50();
	virtual void	Unk_51();
	virtual InventoryChanges::EntryData* GetWeaponInfo();
	virtual InventoryChanges::EntryData* GetAmmoInfo();
	virtual void	Unk_54();
	virtual void	Unk_55();
	virtual void	Unk_56();
	virtual void	Unk_57();
	virtual void	Unk_58();
	virtual void	Unk_59();
	virtual void	Unk_5A();
	virtual void	Unk_5B();
	virtual void	Unk_5C();
	virtual void	Unk_5D();	// Called by 5E with count itemExtraList item
	virtual void	Unk_5E();	// EquipItem and UnEquipItem doEquip item count itemExtraList bytes = [equipArgC lockUnequip unk unEquipArcC lockEquip arg14 ] (arg as from Actor::(Un)EquipItem)
	virtual void	Unk_5F();
	virtual void	Unk_60();
	virtual void	Unk_61();
	virtual void	Unk_62();
	virtual void	Unk_63();
	virtual void	Unk_64();
	virtual void	Unk_65();
	virtual void	Unk_66();
	virtual void	Unk_67();
	virtual void	Unk_68();
	virtual void	Unk_69();
	virtual void	Unk_6A();
	virtual void	Unk_6B();
	virtual void	Unk_6C();
	virtual void	Unk_6D();
	virtual void	Unk_6E();
	virtual void	Unk_6F();
	virtual void	Unk_70();
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
	virtual void	Unk_7E();
	virtual void	Unk_7F();
	virtual void	Unk_80();
	virtual void	Unk_81();
	virtual void	Unk_82();
	virtual TESPackage* GetInterruptPackage();
	virtual void	SetInterruptPackage(TESPackage* package, Actor* onActor);
	virtual void	StopInterruptPackage();
	virtual void	Unk_86();	// 086 - SetInterruptPackageTargetRef
	virtual void	Unk_87();	// 087 - SetInterruptPackageTargetRef
	virtual void	Unk_88();	// 088 - IncreaseInterruptPackageUnk00C
	virtual void	Unk_89();
	virtual void	Unk_8A();
	virtual TESPackage* GetStablePackage();
	virtual void	SetStablePackage(TESPackage* package, Actor* onActor);
	virtual void	StopStablePackage();
	virtual void	Unk_8E();
	virtual void	Unk_8F();
	virtual void	Unk_90();
	virtual void	Unk_91();
	virtual void	Unk_92();	// Only HighProcess, get Unk0454
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
	virtual TESPackage* GetCurrentPackage();
	virtual UInt32	GetPackageInfo0C();
	virtual void	Unk_A1();
	virtual void	Unk_A2();
	virtual bhkCharacterController* GetCharacterController();
	virtual void	Unk_A4();
	virtual void	Unk_A5();
	virtual void	Unk_A6();
	virtual void	Unk_A7();
	virtual void	Unk_A8();
	virtual void	Unk_A9();
	virtual void	Unk_AA();
	virtual void	Unk_AB();
	virtual void	Unk_AC();
	virtual void	Unk_AD();
	virtual void	Unk_AE();
	virtual void	Unk_AF();
	virtual void	Unk_B0();
	virtual void	Unk_B1();
	virtual void	Unk_B2();
	virtual void	Unk_B3();
	virtual void	Unk_B4();
	virtual void	Unk_B5();
	virtual void	Unk_B6();
	virtual void	Unk_B7();
	virtual void	Unk_B8();
	virtual void	Unk_B9();
	virtual void	Unk_BA();
	virtual void	Unk_BB();
	virtual void	Unk_BC();
	virtual void	Unk_BD();
	virtual void	Unk_BE();
	virtual void	SetDiveBreath(float breath);
	virtual float	GetDiveBreath();
	virtual void	Unk_C1();
	virtual void	Unk_C2();
	virtual void	Unk_C3();
	virtual void	Unk_C4();
	virtual void	Unk_C5();
	virtual void	Unk_C6();
	virtual bool	GetAlerted();
	virtual void	SetAlert(bool alert);
	virtual void	Unk_C9();
	virtual void	Unk_CA();
	virtual void	Unk_CB();
	virtual void	Unk_CC();
	virtual void	Unk_CD();
	virtual void	Unk_CE();
	virtual void	Unk_CF();
	virtual void	Unk_D0();
	virtual void	Unk_D1();
	virtual void	Unk_D2();
	virtual void	Unk_D3();
	virtual void	Unk_D4();
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
	virtual void	Unk_E0();
	virtual void	Unk_E1();
	virtual void	Unk_E2();
	virtual TESIdleForm* GetIdleForm10C();
	virtual void	SetIdleForm10C(TESIdleForm* idleForm);
	virtual void	StopIdle();
	virtual void	Unk_E6();
	virtual void	Unk_E7();	// float GetActorValue
	virtual void	Unk_E8();
	virtual void	Unk_E9();
	virtual void	Unk_EA();
	virtual void	Unk_EB();
	virtual void	Unk_EC();
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
	virtual SInt16	GetCurrentAction();
	virtual void	Unk_FA();
	virtual void	Unk_FB();
	virtual void	Unk_FC();
	virtual void	Unk_FD();
	virtual void	Unk_FE();
	virtual void	Unk_FF();
	virtual void	Unk_100();
	virtual bool	IsAiming();
	virtual void	Unk_102();
	virtual SInt32	GetKnockedState();
	virtual void	SetKnockedState(char state);
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
	virtual bool	IsWeaponOut();
	virtual void	SetWeaponOut(Actor* actor, bool weaponOut);
	virtual void	Unk_117();
	virtual void	Unk_118();
	virtual void	Unk_119(Actor* actor);
	virtual void	Unk_11A(UInt32 unk);
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
	virtual void	Unk_133();
	virtual void	Unk_134();
	virtual void	Unk_135();
	virtual void	Unk_136();
	virtual void	Unk_137();
	virtual void	Unk_138();
	virtual void	Unk_139();
	virtual void	Unk_13A();
	virtual void	Unk_13B();
	virtual void	Unk_13C();
	virtual void	Unk_13D();
	virtual void	Unk_13E();
	virtual void	Unk_13F(UInt32 unk);
	virtual void	Unk_140();
	virtual void*	GetDetectionData(Actor* target, UInt32 detecting);
	virtual void	Unk_142();
	virtual void	Unk_143();
	virtual void	Unk_144();
	virtual void	Unk_145();
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
	virtual void	Unk_157();
	virtual void	Unk_158();
	virtual void	Unk_159();
	virtual void	Unk_15A();
	virtual void	Unk_15B();
	virtual void	Unk_15C();
	virtual void	Unk_15D();
	virtual void	Unk_15E();
	virtual void	Unk_15F();
	virtual void	Unk_160();
	virtual void	Unk_161();
	virtual void	Unk_162();
	virtual void	Unk_163();
	virtual void	Unk_164();
	virtual void	Unk_165();
	virtual void	Unk_166();
	virtual void	Unk_167();
	virtual void	Unk_168();
	virtual void	Unk_169();
	virtual void	Unk_16A();
	virtual float	GetActorAlpha();
	virtual void	SetActorAlpha(float alpha);
	virtual void	Unk_16D();
	virtual void	Unk_16E();
	virtual void	Unk_16F();
	virtual void	Unk_170();
	virtual void	Unk_171();
	virtual void	Unk_172();
	virtual void	Unk_173();
	virtual void	Unk_174();
	virtual void	Unk_175();
	virtual void	Unk_176();
	virtual void	Unk_177();
	virtual void	Unk_178();
	virtual void	Unk_179();
	virtual void	Unk_17A();
	virtual void	Unk_17B();
	virtual void	Unk_17C();
	virtual void	Unk_17D();
	virtual void	Unk_17E();
	virtual void	Unk_17F();
	virtual void	Unk_180();
	virtual void	Unk_181();
	virtual void	Unk_182();
	virtual void	Unk_183();
	virtual void	Unk_184();
	virtual void	SetQueuedIdleFlags(UInt32 flags);
	virtual void	Unk_186();
	virtual void	Unk_187();
	virtual void	Unk_188();
	virtual void	Unk_189();
	virtual void	Unk_18A(Actor* actor);
	virtual void	Unk_18B();
	virtual void	Unk_18C();
	virtual void	Unk_18D();
	virtual void	Unk_18E();
	virtual void	Unk_18F();
	virtual void	Unk_190();
	virtual void	Unk_191();
	virtual void	Unk_192(UInt8 unk);
	virtual void	Unk_193();
	virtual void	Unk_194();
	virtual void	Unk_195();
	virtual void	Unk_196();
	virtual void	Unk_197();
	virtual void	Unk_198();
	virtual void	Unk_199();
	virtual void	Unk_19A();
	virtual void	Unk_19B();
	virtual void	Unk_19C();
	virtual void	Unk_19D();
	virtual void	Unk_19E();
	virtual void	Unk_19F();
	virtual void	Unk_1A0();
	virtual void	Unk_1A1();
	virtual void	Unk_1A2();
	virtual void	Unk_1A3();
	virtual void	Unk_1A4();
	virtual void	Unk_1A5();
	virtual void	Unk_1A6();
	virtual void	Unk_1A7();
	virtual void	Unk_1A8();
	virtual void	Unk_1A9();
	virtual void	Unk_1AA();
	virtual void	Unk_1AB();
	virtual void	Unk_1AC();
	virtual void	Unk_1AD();
	virtual void	Unk_1AE();
	virtual void	Unk_1AF();
	virtual void	Unk_1B0();
	virtual void	Unk_1B1();
	virtual void	Unk_1B2();
	virtual void	Unk_1B3();
	virtual void	Unk_1B4();
	virtual void	Unk_1B5();
	virtual void	Unk_1B6();
	virtual void	Unk_1B7();
	virtual void	Unk_1B8();
	virtual void	Unk_1B9();
	virtual void	Unk_1BA();
	virtual void	Unk_1BB();
	virtual void	Unk_1BC();
	virtual void	Unk_1BD();
	virtual void	Unk_1BE();
	virtual void	Unk_1BF();
	virtual void	Unk_1C0();
	virtual void	Unk_1C1();
	virtual void	Unk_1C2();
	virtual void	Unk_1C3();
	virtual void	Unk_1C4();
	virtual void	Unk_1C5();
	virtual TESIdleForm* GetIdleForm350();
	virtual void	SetIdleForm350(TESIdleForm* idleForm);
	virtual void	Unk_1C8();
	virtual void	Unk_1C9();
	virtual void	Unk_1CA();
	virtual void	Unk_1CB();
	virtual void	Unk_1CC();
	virtual float	GetLightAmount();
	virtual void	SetLightAmount(float lightAmount);
	virtual void	Unk_1CF();
	virtual void	Unk_1D0();
	virtual void	Unk_1D1();
	virtual void	Unk_1D2();
	virtual void	Unk_1D3();
	virtual void	Unk_1D4();
	virtual void	Unk_1D5();
	virtual void	Unk_1D6();
	virtual void	Unk_1D7();
	virtual void	Unk_1D8();
	virtual void	Unk_1D9();
	virtual void	Unk_1DA();
	virtual float	GetRadsSec();
	virtual ActorHitInfo* GetHitInfo();
	virtual void	CopyHitInfo(ActorHitInfo* hitInfo);
	virtual void	ResetHitInfo();
	virtual ActorHitInfo* GetHitInfo254();
	virtual void	CopyHitInfo254(ActorHitInfo* hitInfo);
	virtual void	ResetHitInfo254();
	virtual void	Unk_1E2();
	virtual void	Unk_1E3();
	virtual void	Unk_1E4();
	virtual void	Unk_1E5();
	virtual void	Unk_1E6();
	virtual void	Unk_1E7();
	virtual void	Unk_1E8();
	virtual void	Unk_1E9();
	virtual void	Unk_1EA();
	virtual void	Unk_1EB();
	virtual void	Unk_1EC();
	virtual void	Unk_1ED();	// Leads to Last Target

	class Data2C {
	public:
		float	unk00[12];
		UInt32	unk30[2];
		float	unk38[2];
		UInt8	unk40;
		UInt8	pad41[3];
		UInt32	flags;		// 44	flags, bit28 = IsGhost
	};

	PackageInfo		currentPackage;	// 04
	float			unk1C;			// 1C	not initialized, only by descendant!
	float			unk20;			// 20	not initialized, only by descendant to -1.0! flt020 gets set to GameHour minus one on package evaluation
	UInt32			unk24;			// 24	not initialized, only by descendant!
	UInt32			processLevel;	// 28	not initialized, only by descendant to 3 for Low, 2 for MidlleLow, 1 MiddleHighProcess and 0 for HigProcess
	Data2C*			unk2C;			// 2C
};
assert(sizeof(BaseProcess) == 0x030);

class LowProcess : public BaseProcess {
public:
	struct FloatPair {
		float	flt000;
		float	flt004;
	};

	class ActorValueModifier {
	public:
		UInt8	actorValue;	// 00 Might allow for other values
		UInt8	pad[3];		// 01
		float	damage;		// 04
	};

	struct ActorValueModifiers {
		TList<ActorValueModifier>	avModifierList;	// 00
		UInt8						unk008;			// 08
		UInt8						pad009[3];		// 09
		void**						modifiedAV;	// 0C	array of damaged actorValue
	};

	virtual void	Unk_1EE();
	virtual void	Unk_1EF();
	virtual void	Unk_1F0();
	virtual void	Unk_1F1();
	virtual void	Unk_1F2();
	virtual void	Unk_1F3();
	virtual void	Unk_1F4();
	virtual void	Unk_1F5();
	virtual void	Unk_1F6();
	virtual void	Unk_1F7();
	virtual void	Unk_1F8();
	virtual void	Unk_1F9();
	virtual void	Unk_1FA();
	virtual void	Unk_1FB();
	virtual void	Unk_1FC();
	virtual void	Unk_1FD();
	virtual void	Unk_1FE();
	virtual void	Unk_1FF();
	virtual void	Unk_200();
	virtual void	Unk_201();
	virtual void	Unk_202();
	virtual void	Unk_203();
	virtual void	Unk_204();
	virtual void	Unk_205();
	virtual void	Unk_206();

	UInt8				byte30;		// 8 = IsAlerted
	UInt8				pad31[3];
	UInt32				unk34;
	FloatPair			unk38;
	TESForm*			unk40;		// Used when picking idle anims.
	UInt32				unk44;		// not initialized!	refr, expected actor, might be CombatTarget
	UInt32				unk48;
	UInt32				unk4C;
	UInt32				unk50;
	UInt32				unk54;		// not initialized!
	UInt32				unk58;
	UInt32				unk5C;
	TList<UInt32>		unk60;		// List
	UInt32				unk68;
	UInt32				unk6C;
	TList<TESForm>		unk70;
	TList<UInt32>		unk78;
	TList<UInt32>		unk80;
	UInt32				unk88;
	UInt32				unk8C;
	UInt32				unk90;
	UInt32				unk94;
	ActorValueModifiers	damageModifiers;
	float				gameDayDied;
	UInt32				unkAC;		// not initialized!
	UInt32				unkB0;		// not initialized!
};
assert(sizeof(LowProcess) == 0x0B4);

class MiddleLowProcess : public LowProcess {
public:
	virtual void		Unk_207();

	UInt32				unk0B4;			// B4
	ActorValueModifiers	tempModifiers;	// B8
};
assert(sizeof(MiddleLowProcess) == 0x0C8);

class MiddleHighProcess : public MiddleLowProcess {
public:
	virtual void	SetAnimation(UInt32 newAnimation);
	virtual void	Unk_209();
	virtual void	Unk_20A();
	virtual void	Unk_20B();
	virtual void	Unk_20C();
	virtual void	Unk_20D();
	virtual void	Unk_20E();
	virtual void	Unk_20F();
	virtual void	Unk_210();
	virtual void	Unk_211();
	virtual void	Unk_212();
	virtual void	Unk_213();
	virtual void	Unk_214();
	virtual void	Unk_215();
	virtual void	Unk_216();
	virtual void	Unk_217();
	virtual void	Unk_218();
	virtual void	Unk_219();
	virtual void	Unk_21A();
	virtual void	Unk_21B();

	TList<TESForm>						unk0C8;				// 0C8
	TList<UInt32>						unk0D0;				// 0D0
	UInt32								unk0D8[3];			// 0D8
	PackageInfo							interruptPackage;	// 0E4
	UInt8								unk0FC[12];			// 0FC	Saved as one, might be Pos/Rot given size
	UInt32								unk108;				// 108
	TESIdleForm*						idleForm10C;		// 10C
	UInt32								unk110;				// 110  EntryData, also handled as part of weapon code. AmmoInfo.
	InventoryChanges::EntryData*		weaponInfo;			// 114
	InventoryChanges::EntryData*		ammoInfo;			// 118
	void*								unk11C;				// 11C QueuedFile*
	UInt8								byt120;				// 120
	UInt8								byt121;				// 121
	UInt8								byt122;				// 122
	UInt8								fil123;				// 123
	UInt32								unk124;				// 124
	UInt32								unk128;				// 128 Gets copied over during TESNPC.CopyFromBase
	UInt8								byt12C;				// 12C
	UInt8								byt12D;				// 12D
	UInt8								byt12E;				// 12E
	UInt8								byt12F;				// 12F
	void*								ptr130;				// 130	its an animation. Current Animation?
	UInt8								byt134;				// 134
	bool								isWeaponOut;		// 135
	UInt8								byt136;				// 136
	UInt8								byt137;				// 137
	bhkCharacterController*				charCtrl;			// 138
	UInt8								KnockedState;		// 13C
	UInt8								unk13D[3];			// 13D
	UInt32								unk140[8];			// 140
	MagicItem*							magicItem160;		// 160
	UInt32								unk164[3];			// 164
	float								actorAlpha;			// 170
	UInt32								unk174;				// 174
	void*								unk178;				// 178 BSFaceGenAnimationData*
	UInt32								unk17C[15];			// 17C
	void*								unk1B8;				// 1B8
	MagicTarget*						magicTarget1BC;		// 1BC
	ActorAnimData*						animData;			// 1C0
	BSAnimGroupSequence*				animSequence[3];	// 1C4
	UInt32								unk1D0[3];			// 1D0
	NiNode*								limbNodes[15];		// 1DC
	NiNode*								unk218;				// 218
	NiNode*								unk21C;				// 21C
	void*								ptr220;				// 220
	BSBound*							boundingBox;		// 224
	UInt32								unk228[3];			// 228
	float								radsSec234;			// 234
	float								rads238;			// 238
	float								waterRadsSec;		// 23C
	ActorHitInfo*						hitInfo240;			// 240
	UInt32								unk244;				// 244
	void*								unk248;				// 248 BSFaceGenNiNode*
	void*								unk24C;				// 24C BSFaceGenNiNode*
	NiTriShape*							unk250;				// 250
	ActorHitInfo*						hitInfo254;			// 254
	UInt32								unk258;				// 258
};
assert(sizeof(MiddleHighProcess) == 0x25C);

class HighProcess : public MiddleHighProcess {
public:
	enum AnimAction {
		kAnimAction_None = -1,
		kAnimAction_Equip_Weapon = 0,
		kAnimAction_Unequip_Weapon = 1,
		kAnimAction_Attack = 2,
		kAnimAction_Attack_Eject = 3,
		kAnimAction_Attack_Follow_Through = 4,
		kAnimAction_Attack_Throw = 5,
		kAnimAction_Attack_Throw_Attach = 6,
		kAnimAction_Block = 7,
		kAnimAction_Recoil = 8,
		kAnimAction_Reload = 9,
		kAnimAction_Stagger = 10,
		kAnimAction_Dodge = 11,
		kAnimAction_Wait_For_Lower_Body_Anim = 12,
		kAnimAction_Wait_For_Special_Idle = 13,
		kAnimAction_Force_Script_Anim = 14,
		kAnimAction_ReloadLoopStart = 15,
		kAnimAction_ReloadLoopEnd = 16,
		kAnimAction_ReloadLoop = 17,
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

	TList<void>*				detectedActors;		// 25C TList<DetectionData>*
	TList<void>*				detectingActors;	// 260 TList<DetectionData>*
	void*						ptr264;				// 264
	void*						ptr268;				// 268
	void*						ptr26C;				// 26C
	UInt32						unk270;				// 270
	TList<void>					unk274;				// 274 TList<CombatTarget>
	UInt32						unk27C;				// 27C
	UInt32						unk280;				// 280
	UInt32						unk284[24];			// 284
	void*						ptr2E4;				// 2E4 NiBSBoneLODController*
	UInt32						unk2E8;				// 2E8
	SInt16						currentAction;		// 2EC
	UInt8						pad2EE[2];			// 2EE
	BSAnimGroupSequence*		currentSequence;	// 2F0
	UInt32						unk2F4[18];			// 2F4
	float						diveBreath;			// 33C
	UInt32						unk340[4];			// 340
	TESIdleForm*				idleForm350;		// 350
	UInt32						unk354[4];			// 354
	void**						ptr364;				// 364 NiBSplineCompTransformInterpolator**
	UInt32						unk368[23];			// 368
	float						lightAmount;		// 3C4
	UInt32						unk3C8[8];			// 3C8
	UInt32						fadeType;			// 3E8
	float						delayTime;			// 3EC
	UInt32						unk3F0;				// 3F0
	UInt32						unk3F4;				// 3F4
	UInt32						unk3F8[3];			// 3F8
	Actor*						combatTarget;		// 404
	UInt32						unk408[5];			// 408
	TESObjectREFR*				packageTarget;		// 41C
	UInt32						unk420;				// 420
	UInt32						queuedIdleFlags;	// 424
	UInt32						unk428[3];			// 428
	void*						ptr434;				// 434 bhkShapePhantom*
	UInt32						unk438;				// 438
	float						unk43C;				// 43C
	float						radsSec440;			// 440
	UInt8						plantedExplosive;	// 444
	UInt8						pad445[3];			// 445
	UInt32						unk448[9];			// 448
};
assert(sizeof(HighProcess) == 0x46C);

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
assert(sizeof(HighProcessEx) == 0x480);

class TESObjectREFR : public TESForm {
public:
	virtual void		Unk_4E();	// GetStartingPosition(Position, Rotation, WorldOrCell)
	virtual void		Unk_4F();
	virtual void		Unk_50();
	virtual void		Unk_51();
	virtual bool		CastShadows();
	virtual void		Unk_53();
	virtual void		Unk_54();
	virtual void		Unk_55();
	virtual void		Unk_56();
	virtual void		Unk_57();
	virtual void		Unk_58();
	virtual void		Unk_59();
	virtual void		Unk_5A();
	virtual void		Unk_5B();
	virtual void		Unk_5C();
	virtual void		Unk_5D();
	virtual void		Unk_5E();
	virtual TESObjectREFR* RemoveItem(TESForm* toRemove, ExtraDataList* extraList, UInt32 count, UInt32 unk3, UInt32 unk4, TESObjectREFR* destRef, UInt32 unk6, UInt32 unk7, UInt32 unk8, UInt8 unk9);	// 40 unk2 quantity? Returns the reference assigned to the removed item.
	virtual void		Unk_60();
	virtual void		Unk_61();	// Linked to AddItem, (item, count, ExtraDataList), func0042 in OBSE
	virtual void		Unk_62();	// Linked to Unequip (and or equip maybe)
	virtual void		Unk_63();
	virtual void		AddItem(TESForm* item, ExtraDataList* xDataList, UInt32 Quantity);	// Needs confirmation
	virtual void		Unk_65();
	virtual void		Unk_66();
	virtual void		Unk_67();					// Actor: GetMagicEffectList
	virtual bool		GetIsChildSize(bool checkHeight);		// 068 Actor: GetIsChildSize
	virtual UInt32		GetActorUnk0148();			// result can be interchanged with baseForm, so TESForm* ?
	virtual void		SetActorUnk0148(UInt32 arg0);
	virtual void		Unk_6B();
	virtual void		Unk_6C();	// REFR: GetBSFaceGenNiNodeSkinned
	virtual void		Unk_6D();	// REFR: calls 006C
	virtual void		Unk_6E();	// MobileActor: calls 006D then NiNode::Func0040
	virtual void		Unk_6F();
	virtual void		Unk_70();
	virtual void		AnimateNiNode();					// same in FOSE ! identical to Func0052 in OBSE which says (inits animation-related data, and more)
	virtual void		GenerateNiNode(bool arg0);				// same in FOSE !
	virtual void		Set3D(NiNode* niNode, bool unloadArt);	// same in FOSE !
	virtual NiNode*		GetNiNode();						// same in FOSE !
	virtual void		Unk_75();
	virtual void		Unk_76();
	virtual void		Unk_77();
	virtual void		Unk_78();
	virtual ActorAnimData*	GetActorAnimData();			// 0079
	virtual void*			GetValidBip01Names();	// 007A	returns ValidBip01Names*
	virtual void*		CallGetValidBip01Names(); // returns ValidBip01Names*
	virtual void		SetValidBip01Names(UInt32 validBip01Names);
	virtual void		GetPos();				// GetPos or GetDistance
	virtual void		Unk_7E(UInt32 arg0);
	virtual void		Unk_7F();
	virtual void		Unk_80(UInt32 arg0);
	virtual void		Unk_81(UInt32 arg0);
	virtual void		Unk_82();
	virtual UInt32		Unk_83();
	virtual void		Unk_84(UInt32 arg0);
	virtual UInt8		GetSitSleepState();		// Get 01AC
	virtual bool		IsCharacter();			// return false for Projectile, Actor and Creature, true for character and PlayerCharacter
	virtual bool		Unk_87();			// seems to always return 0
	virtual bool		Unk_88();			// seems to always return 0
	virtual void		Unk_89();
	virtual void		Unk_8A();			// SetParentCell (Interior only ?)
	virtual UInt8		GetDead(UInt8 Arg1);
	virtual bool		Unk_8C();
	virtual bool		Unk_8D();
	virtual void		Unk_8E();
	virtual void		Unk_8F();

	enum {
		kFlags_Unk00000002	= 0x00000002,
		kFlags_Deleted		= 0x00000020,		// refr removed from .esp or savegame
		kFlags_Persistent	= 0x00000400,		//shared bit with kFormFlags_QuestItem
		kFlags_Temporary	= 0x00004000,
		kFlags_Taken		= kFlags_Deleted | kFlags_Unk00000002,

		kChanged_Inventory = 0x08000000,
	};

	NiNode*				GetNode() { return (renderData != NULL ? renderData->niNode : NULL); };

	TESChildCell		childCell;				// 018
	UInt32				unk1C;					// 01C
	TESForm*			baseForm;				// 020
	NiPoint3			rot;					// 024
	NiPoint3			pos;					// 030 
	float				scale;					// 03C 
	TESObjectCELL*		parentCell;				// 040
	ExtraDataList		extraDataList;			// 044
	TESObjectREFRData*	renderData;				// 064	- (05C in FOSE)
};
assert(sizeof(TESObjectREFR) == 0x068);

class MobileObject : public TESObjectREFR {
public:
	virtual void		StartHighProcess();		// 090
	virtual void		Unk_91();
	virtual void		Unk_92();
	virtual void		Unk_93();
	virtual void		Unk_94();
	virtual void		Unk_95();
	virtual void		Unk_96();
	virtual void		Unk_97();
	virtual void		Unk_98();
	virtual void		Unk_99();
	virtual void		Unk_9A();
	virtual void		Unk_9B();
	virtual void		Unk_9C();
	virtual void		Unk_9D();
	virtual void		Unk_9E();
	virtual void		Unk_9F();
	virtual void		Unk_A0();	// StartConversation(targetActor, subjectLocationData, targetLocationData, headTrack, allowMovement, arg, topicID, arg, arg
	virtual void		Unk_A1();
	virtual void		Unk_A2();
	virtual void		Unk_A3();
	virtual void		Unk_A4();
	virtual void		Unk_A5();
	virtual void		Unk_A6();
	virtual void		Unk_A7();
	virtual void		Unk_A8();
	virtual void		Unk_A9();
	virtual void		Unk_AA();
	virtual void		Unk_AB();
	virtual void		Unk_AC();
	virtual void		Unk_AD();
	virtual void		Unk_AE();
	virtual void		Unk_AF();
	virtual void		Unk_B0();
	virtual void		Unk_B1();
	virtual void		Unk_B2();
	virtual void		Unk_B3();
	virtual void		Unk_B4();
	virtual void		Unk_B5();
	virtual void		Unk_B6();
	virtual void		Unk_B7();
	virtual void		Unk_B8();
	virtual void		Unk_B9();
	virtual void		Unk_BA();
	virtual void		Unk_BB();
	virtual void		Unk_BC();
	virtual void		Unk_BD();
	virtual void		Unk_BE();
	virtual void		Unk_BF();
	virtual void		Unk_C0();

	BaseProcess*	process;		// 068
	UInt32			unk06C;			// 06C - loaded	set to the talking actor ref when initialising ExtraTalkingActor
	UInt32			unk070;			// 070 - loaded
	UInt32			unk074;			// 074 - loaded
	UInt32			unk078;			// 078 - loaded
	UInt8			unk07C;			// 07C - loaded
	UInt8			unk07D;			// 07D - loaded
	UInt8			unk07E;			// 07E - loaded
	UInt8			unk07F;			// 07F - loaded
	UInt8			unk080;			// 080 - loaded
	UInt8			unk081;			// 081 - loaded
	UInt8			unk082;			// 082 - cleared when starting combat on player
	UInt8			unk083;			// 083 - loaded
	UInt8			unk084;			// 084 - loaded
	UInt8			unk085;			// 085 - loaded
	UInt8			unk086;			// 086 - loaded
	UInt8			unk087;			// 087	Init'd to the inverse of NoLowLevelProcessing
};
assert(sizeof(MobileObject) == 0x088);

class ActorValuesOwner {
public:
	virtual UInt32	GetBase(UInt32 avCode);
	virtual float	GetBaseF(UInt32 avCode);
	virtual UInt32	GetCurrent(UInt32 avCode);
	virtual float	GetCurrentF(UInt32 avCode);
	virtual float	Fn_04(UInt32 avCode);					// GetBaseActorValue04 (internal) result in st
	virtual float	GetDamage(UInt32 avCode);
	virtual float	Fn_06(UInt32 avCode);					// GetDamageActorValue or GetModifiedActorValue		called from Fn_08, result in st, added to Fn_01
	virtual UInt32	Fn_07(UInt32 avCode);					// Manipulate GetPermanentActorValue, maybe convert to integer.
	virtual float	GetPermanent(UInt32 avCode);			// GetPermanentActorValue (used from Eval) result in EAX
	virtual void*	Fn_09();								// GetActorBase (= this - 0x100) or GetActorBase (= this - 0x0A4)
	virtual UInt16	GetLevel();								// GetLevel (from ActorBase)
};
assert(sizeof(ActorValuesOwner) == 0x004);

class CachedValuesOwner {
public:
	virtual float	Fn_00();
	virtual float	Fn_01();
	virtual float	Fn_02();
	virtual float	Fn_03();
	virtual float	Fn_04();
	virtual float	Fn_05();
	virtual float	Fn_06();
	virtual float	Fn_07();
	virtual float	Fn_08();
	virtual float	Fn_09();
	virtual float	Fn_0A();
	virtual UInt32	Fn_0B();
	virtual UInt32	Fn_0C();
	virtual float	Fn_0D();
	virtual float	Fn_0E();
	virtual bool	Fn_0F();
};
assert(sizeof(CachedValuesOwner) == 0x004);

class PathingLocation {
public:
	virtual void	Unk_00();
	virtual void	Unk_01();
	virtual void	Unk_02();

	UInt32			unk04[9];	// 04
};
assert(sizeof(PathingLocation) == 0x028);

class ActorMover {
public:
	virtual void		Unk_00();
	virtual void		Unk_01();
	virtual void		Unk_02();
	virtual void		Unk_03();
	virtual void		Unk_04();
	virtual void		Unk_05();
	virtual void		Unk_06();
	virtual void		Unk_07();
	virtual UInt32		GetMovementFlags();
	//	Running		0x200
	//	Sneaking	0x400

	// bit 11 = swimming 
	// bit 9 = sneaking
	// bit 8 = run
	// bit 7 = walk
	// bit 0 = keep moving (Q)
	virtual void		Unk_09();
	virtual void		Unk_0A();
	virtual void		Unk_0B();
	virtual void		Unk_0C();
	virtual void		Unk_0D();
	virtual void		Unk_0E();

	UInt32				unk04[6];			// 04
	void*				pathingRequest;		// 1C PathingRequest*
	void*				pathingSolution;	// 20 PathingSolution*
	void*				pathHandler;		// 24 DetailedActorPathHandler*
	Actor*				actor;				// 28
	UInt32				unk2C;				// 2C
	void*				pathingMsgQueue;	// 30 ActorPathingMessageQueue*
	UInt32				movementFlags1;		// 34
	UInt32				unk38;				// 38
	UInt32				movementFlags2;		// 3C
	UInt32				unk40;				// 40
	PathingLocation		pathingLocation;	// 44
	UInt32				unk6C;				// 6C
	UInt8				unk70[4];			// 70
	UInt32				unk74;				// 74
	UInt32				unk78;				// 78
	UInt32				unk7C;				// 7C
	UInt32				unk80;				// 80
	UInt32				unk84;				// 84
};
assert(sizeof(ActorMover) == 0x088);

class Actor : public MobileObject {
public:
	enum ActorVal {
		kActorVal_Aggression			= 0,
		kActorVal_Confidence			= 1,
		kActorVal_Energy				= 2,
		kActorVal_Responsibility		= 3,
		kActorVal_Mood					= 4,
		kActorVal_Strength				= 5,
		kActorVal_Perception			= 6,
		kActorVal_Endurance				= 7,
		kActorVal_Charisma				= 8,
		kActorVal_Intelligence			= 9,
		kActorVal_Agility				= 10,
		kActorVal_Luck					= 11,
		kActorVal_ActionPoints			= 12,
		kActorVal_CarryWeight			= 13,
		kActorVal_CritChance			= 14,
		kActorVal_HealRate				= 15,
		kActorVal_Health				= 16,
		kActorVal_MeleeDamage			= 17,
		kActorVal_DamageResistance		= 18,
		kActorVal_PoisonResistance		= 19,
		kActorVal_RadResistance			= 20,
		kActorVal_SpeedMultiplier		= 21,
		kActorVal_Stamina				= 22,
		kActorVal_Karma					= 23,
		kActorVal_XP					= 24,
		kActorVal_Head					= 25,
		kActorVal_Torso					= 26,
		kActorVal_LeftArm				= 27,
		kActorVal_RightArm				= 28,
		kActorVal_LeftLeg				= 29,
		kActorVal_RightLeg				= 30,
		kActorVal_Brain					= 31,
		kActorVal_Barter				= 32,
		kActorVal_BigGuns				= 33,
		kActorVal_EnergyWeapons			= 34,
		kActorVal_Explosives			= 35,
		kActorVal_Lockpick				= 36,
		kActorVal_Medicine				= 37,
		kActorVal_MeleeWeapons			= 38,
		kActorVal_Repair				= 39,
		kActorVal_Science				= 40,
		kActorVal_Guns					= 41,
		kActorVal_Sneak					= 42,
		kActorVal_Speech				= 43,
		kActorVal_Survival				= 44,
		kActorVal_Unarmed				= 45,
		kActorVal_InventoryWeight		= 46,
		kActorVal_Paralysis				= 47,
		kActorVal_Invisibility			= 48,
		kActorVal_Chameleon				= 49,
		kActorVal_NightEye				= 50,
		kActorVal_Turbo					= 51,
		kActorVal_FireResistance		= 52,
		kActorVal_WaterBreathing		= 53,
		kActorVal_RadLevel				= 54,
		kActorVal_BloodyMess			= 55,
		kActorVal_UnarmedDamage			= 56,
		kActorVal_Assistance			= 57,
		kActorVal_ElectricResistance	= 58,
		kActorVal_FrostResistance		= 59,
		kActorVal_EnergyResistance		= 60,
		kActorVal_EMPResistance			= 61,
		kActorVal_Var1Medical			= 62,
		kActorVal_Var2					= 63,
		kActorVal_Var3					= 64,
		kActorVal_Var4					= 65,
		kActorVal_Var5					= 66,
		kActorVal_Var6					= 67,
		kActorVal_Var7					= 68,
		kActorVal_Var8					= 69,
		kActorVal_Var9					= 70,
		kActorVal_Var10					= 71,
		kActorVal_IgnoreCrippledLimbs	= 72,
		kActorVal_Dehydration			= 73,
		kActorVal_Hunger				= 74,
		kActorVal_Sleepdeprevation		= 75,
		kActorVal_Damagethreshold		= 76,
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

	virtual void		Unk_C1();
	virtual void		Unk_C2();
	virtual void		Unk_C3();
	virtual void		Unk_C4();
	virtual void		Unk_C5();
	virtual void		Unk_C6();
	virtual void		SetIgnoreCrime(bool ignoreCrime);
	virtual bool		GetIgnoreCrime();
	virtual void		Unk_C9();
	virtual void		Unk_CA();
	virtual void		Unk_CB();
	virtual void		Unk_CC();
	virtual void		Unk_CD();
	virtual void		Unk_CE();
	virtual void		Unk_CF();
	virtual void		Unk_D0();
	virtual void		Unk_D1();
	virtual void		Unk_D2();
	virtual void		Unk_D3();
	virtual void		Unk_D4();
	virtual void		Unk_D5();
	virtual void		Unk_D6();
	virtual void		Unk_D7();
	virtual bool		IsPlayerRef();
	virtual void		Unk_D9();
	virtual void		Unk_DA();
	virtual void		Unk_DB();
	virtual void		Unk_DC();
	virtual void		Unk_DD();
	virtual void		Unk_DE();
	virtual void		Unk_DF();
	virtual void		Unk_E0();
	virtual void		Unk_E1();
	virtual void		Unk_E2();
	virtual void		Unk_E3();
	virtual UInt32		GetActorType();	// Creature = 0, Character = 1, PlayerCharacter = 2
	virtual void		SetActorValue(UInt32 avCode, float value);
	virtual void		SetActorValueInt(UInt32 avCode, UInt32 value);
	virtual void		Unk_E7();
	virtual void		Unk_E8();
	virtual void		Unk_E9();
	virtual void		Unk_EA();
	virtual void		DamageActorValue(UInt32 avCode, float damage, Actor* attacker);
	virtual void		Unk_EC();
	virtual void		Unk_ED();
	virtual void		Unk_EE();
	virtual InventoryChanges::EntryData* GetPreferedWeapon(UInt32 unk);
	virtual void		Unk_F0();
	virtual void		Unk_F1();
	virtual void		Unk_F2();
	virtual void		Unk_F3();
	virtual void		Unk_F4();
	virtual void		Unk_F5();
	virtual void		Unk_F6();
	virtual void		Unk_F7();
	virtual void		Unk_F8();
	virtual void		Unk_F9();
	virtual void		Unk_FA();
	virtual void		Unk_FB(TESForm* form, UInt32 arg2, UInt8 arg3, UInt8 arg4);
	virtual void		Unk_FC();
	virtual void		Unk_FD();
	virtual void		Unk_FE();
	virtual void		Unk_FF();
	virtual void		Unk_100();
	virtual void		Unk_101();
	virtual void		Unk_102();
	virtual void		Unk_103();
	virtual void		Unk_104();
	virtual void		Unk_105();
	virtual void		Unk_106();
	virtual void		Unk_107();
	virtual void		Unk_108();
	virtual void		Unk_109();
	virtual CombatController* GetCombatController();
	virtual Actor*		GetCombatTarget();
	virtual void		Unk_10C();
	virtual void		Unk_10D();
	virtual void		Unk_10E();
	virtual float		GetTotalArmorDR();
	virtual float		GetTotalArmorDT();
	virtual UInt32		Unk_111();
	virtual void		Unk_112();
	virtual void		Unk_113();
	virtual void		Unk_114();
	virtual void		Unk_115();
	virtual float		CalcSpeedMult();
	virtual void		Unk_117();
	virtual void		Unk_118();
	virtual void		Unk_119();
	virtual void		Unk_11A();
	virtual void		Unk_11B();
	virtual void		Unk_11C();
	virtual void		Unk_11D();
	virtual void		Unk_11E();
	virtual void		Unk_11F();
	virtual void		Unk_120();
	virtual void		Unk_121();
	virtual void		RewardXP(UInt32 amount);
	virtual void		Unk_123();
	virtual void		Unk_124();
	virtual void		Unk_125();
	virtual void		SetPerkRank(BGSPerk* perk, UInt8 rank, bool alt);
	virtual void		RemovePerk(BGSPerk* perk, bool alt);
	virtual UInt8		GetPerkRank(BGSPerk* perk, bool alt);
	virtual void		Unk_129();
	virtual void		Unk_12A();
	virtual void		Unk_12B();
	virtual void		Unk_12C();
	virtual void		Unk_12D();
	virtual void		DoHealthDamage(Actor* attacker, float damage);
	virtual void		Unk_12F();
	virtual void		Unk_130();
	virtual float		Unk_131();
	virtual void		Unk_132();
	virtual void		Unk_133();
	virtual void		Unk_134();
	virtual void		Unk_135();
	virtual void		Unk_136();

	UInt32				GetBaseActorValue(ActorVal Code) { return avOwner.GetBase(Code); }
	UInt32				GetActorValue(ActorVal Code) { return avOwner.GetCurrent(Code); }
	void				EquipItem(TESForm* Form, UInt32 Quantity, ExtraDataList* List) { ThisCall(0x0088C650, this, Form, Quantity, List, 0, false, 0); }
	void				UnequipItem(TESForm* Form, UInt32 Quantity, ExtraDataList* List) { ThisCall(0x0088C790, this, Form, Quantity, List, 0, false, 0); }
	bool				IsFemale() { return ThisCall(0x0087F4C0, this); }

	MagicCaster			magicCaster;				// 088
	MagicTarget			magicTarget;				// 094
	ActorValuesOwner	avOwner;					// 0A4
	CachedValuesOwner	cvOwner;					// 0A8
	void*				ragDollController;			// 0AC bhkRagdollController*
	void*				ragDollPentrationUtil;		// 0B0 bhkRagdollPenetrationUtil*
	UInt32				unk0B4;						// 0B4-
	float				flt0B8;						// 0B8
	UInt8				byte0BC;					// 0BC-
	UInt8				byte0BD;					// 0BD
	UInt8				byte0BE;					// 0BE
	UInt8				byte0BF;					// 0BF
	Actor*				killer;					// 0C0
	UInt8				byte0C4;					// 0C4-
	UInt8				byte0C5;					// 0C5
	UInt8				byte0C6;					// 0C6
	UInt8				byte0C7;					// 0C7
	float				flt0C8;						// 0C8
	float				flt0CC;						// 0CC
	TList<void>			list0D0;					// 0D0
	UInt8				byte0D8;					// 0D8
	UInt8				byte0D9;					// 0D9
	UInt8				byte0DA;					// 0DA
	UInt8				byte0DB;					// 0DB
	UInt32				unk0DC;						// 0DC
	TList<void>			list0E0;					// 0E0
	UInt8				byte0E8;					// 0E8	const 1
	UInt8				byte0E9;					// 0E9
	UInt8				byte0EA;					// 0EA
	UInt8				byte0EB;					// 0EB
	UInt32				unk0EC;						// 0EC
	UInt8				byte0F0;					// 0F0-
	UInt8				byte0F1;					// 0F1-
	UInt8				byte0F2;					// 0F2
	UInt8				byte0F3;					// 0F3
	TList<void>			list0F4;					// 0F4
	TList<void>			list0FC;					// 0FC
	bool				isInCombat;					// 104
	UInt8				jipActorFlags1;				// 105
	UInt8				jipActorFlags2;				// 106
	UInt8				jipActorFlags3;				// 107
	UInt32				lifeState;					// 108	saved as byte HasHealth = 1 or 2, optionally 6, 5 = IsRestrained
	UInt32				criticalStage;				// 10C
	UInt32				unk110;						// 110-
	float				flt114;						// 114
	UInt8				byte118;					// 118-
	UInt8				byte119;					// 119+
	UInt16				jip11A;						// 11A+
	UInt32				unk11C;						// 11C-
	UInt32				unk120;						// 120-
	bool				forceRun;					// 124
	bool				forceSneak;					// 125
	UInt8				byte126;					// 126-
	UInt8				byte127;					// 127-
	Actor*				combatTarget;				// 128
	void*				combatTargets;				// 12C BSSimpleArray<Actor*>*
	void*				combatAllies;				// 130 BSSimpleArray<Actor*>*
	UInt8				byte134;					// 134-
	UInt8				byte135;					// 135+
	UInt16				jip136;						// 136+
	UInt32				unk138;						// 138-
	UInt32				unk13C;						// 13C-
	UInt32				actorFlags;					// 140	0x80000000 - IsEssential
	bool				ignoreCrime;				// 144
	UInt8				byte145;					// 145	Has to do with package evaluation
	UInt8				byte146;					// 146	Has to do with package evaluation
	UInt8				byte147;					// 147
	UInt32				unk148;						// 148-
	UInt8				inWater;					// 14C
	UInt8				isSwimming;					// 14D
	UInt16				jip14E;						// 14E+
	UInt32				unk150;						// 150-
	float				flt154;						// 154
	float				flt158;						// 158
	UInt8				byte15C;					// 15C-
	UInt8				byte15D;					// 15D-
	UInt16				jip15E;						// 15E+
	NiPoint3			startingPos;				// 160
	float				flt16C;						// 16C
	TESForm*			startingWorldOrCell;		// 170
	UInt8				byte174;					// 174-
	UInt8				byte175;					// 175-
	UInt16				jip176;						// 176+
	float				flt178;						// 178
	float				flt17C;						// 17C
	float				flt180;						// 180
	float				flt184;						// 184
	float				flt188;						// 188
	UInt8				byte18C;					// 18C-
	bool				isTeammate;					// 18D
	UInt8				byte18E;					// 18E-
	UInt8				byte18F;					// 18F
	ActorMover*			actorMover;					// 190
	UInt32				unk194;						// 194-
	UInt32				unk198;						// 198-
	float				flt19C;						// 19C
	UInt32				unk1A0;						// 1A0-
	UInt32				unk1A4;						// 1A4-
	UInt32				unk1A8;						// 1A8-
	UInt32				SitSleepState;				// 1AC-
	UInt8				byte1B0;					// 1B0-
	bool				forceHit;					// 1B1-
	UInt8				byte1B2;					// 1B2
	UInt8				byte1B3;					// 1B3
};
assert(sizeof(Actor) == 0x1B4);

class Creature : public Actor {
public:
	virtual void	Unk_137();

	UInt32			unk1B4[3];			// 1B4
};
assert(sizeof(Creature) == 0x1C0);

class Character : public Actor {
public:
	virtual void	Unk_137();
	virtual void	Unk_138();

	SkinInfo*		ActorSkinInfo;		// 1B4
	float			flt1B8;				// 1B8
	float			flt1BC;				// 1BC
	UInt8			isTrespassing;		// 1C0
	UInt8			byt1C1;				// 1C1
	UInt16			unk1C2;				// 1C2
	float			unk1C4;				// 1C4
};
assert(sizeof(Character) == 0x1C8);

class PlayerCharacter : public Character {
public:
	// used to flag controls as disabled in disabledControlFlags
	enum {
		kControlFlag_Movement		= 1 << 0,
		kControlFlag_Look			= 1 << 1,
		kControlFlag_Pipboy			= 1 << 2,
		kControlFlag_Fight			= 1 << 3,
		kControlFlag_POVSwitch		= 1 << 4,
		kControlFlag_RolloverText	= 1 << 5,
		kControlFlag_Sneak			= 1 << 6,
	};

	virtual void		Unk_139();
	virtual void		Unk_13A();
	
	bool				IsAiming() { return (process->IsWeaponOut() && process->IsAiming()); }
	TESWorldSpace*		GetWorldSpace() { return (parentCell != NULL ? parentCell->worldSpace : NULL); }
	TESRegion*			GetRegion() { return currentRegion; }
	void				UpdateInventory() {}
	bool				IsMoving() { return (actorMover->GetMovementFlags() & 0x800); }
	bool				IsAlive() { return !GetDead(1); }
	bool				IsFirstPerson() { return !isThirdPerson; }
	bool				IsVanity() { return *(bool*)0x011E07B8; }
	void				SetFoV(float FoV) {
							float* SettingWorldFoV = (float*)0x01203160;
							float* Setting1stPersonFoV = (float*)0x0120316C;
							worldFoV = *SettingWorldFoV = *Setting1stPersonFoV = FoV;
						}
	float				GetFoV(bool IsSpecialView) { return (IsSpecialView ? firstPersonFoV : worldFoV); }
	void				ResetCamera() {}
	bool				IsReloading() { return (ThisCall(0x008A8870, this)); }

	UInt32				unk1C8[(0x244-0x1C8) >> 2];		// 1C8	0224 is a package of type 1C, 208 could be a DialogPackage, 206 questObjectiveTargets is valid
	float				unk244[0x4D];					// 244	have to be a set of ActorValue
	float				unk378[0x4D];					// 378	have to be a set of ActorValue
	UInt32				unk4AC;							// 4AC
	float				unk4B0[0x4D];					// 4B0	have to be a set of ActorValue
	TList<void>			notes;							// 5E4 TList<BGSNote>
	void*				unk5EC;							// 5EC ImageSpaceModifierInstanceDOF*
	void*				unk5F0;							// 5F0 ImageSpaceModifierInstanceDOF*
	void*				unk5F4;							// 5F4 ImageSpaceModifierInstanceDRB*
	UInt32				unk5F8;							// 5F8
	TList<Actor>		teammates;						// 5FC
	UInt32				unk604[(0x648 - 0x604) >> 2];	// 604
	UInt8				unkThirdPersonPrev;				// 648
	UInt8				unk649;							// 649
	UInt8				unkThirdPerson;					// 64A
	UInt8				isThirdPersonBody;				// 64B
	UInt8				isThirdPerson;					// 64C
	UInt8				DisableFading;					// 64D
	UInt8				unk64E;							// 64E
	UInt8				isSpecialView;					// 64F
	UInt8				isSpecialViewPrevThird;			// 650
	UInt8				AlwaysRun;						// 651
	UInt8				AutoMove;						// 652
	UInt8				unk653;							// 653
	UInt32				unk654[7];						// 654
	float				worldFoV;						// 670
	float				firstPersonFoV;					// 674
	float				overShoulderFoV;				// 678
	UInt32				unk67C;							// 67C
	UInt8				disabledControlFlags;			// 680 kControlFlag_xxx
	UInt8				unk0681[3];						// 681
	UInt32				unk684[(0x68C - 0x684) >> 2];	// 684
	SkinInfo*			firstPersonSkinInfo;			// 68C
	ActorAnimData*		firstPersonAnimData;			// 690
	NiNode*				firstPersonNiNode;				// 694
	UInt32				unk698[(0x6A8-0x698) >> 2];		// 698
	TESTopic*			topic;							// 6A8
	UInt32				unk6AC[3];						// 6AC
	TESQuest*			quest;							// 6B8
	TList<void>			questObjectiveList;				// 6BC TList<BGSQuestObjective>
	UInt32				unk6C4[39];				// 6C4
	TESRegion*			currentRegion;			// 760
	TESRegionList		regionsList;			// 764
	UInt32				unk770[10];				// 770
	UInt8				isTravelPackage;		// 798
	UInt8				isWakeUpPackage;		// 799
	UInt8				isDrinkPackage;			// 79A
	UInt8				isUnkPackage;			// 79B
	UInt32				unk79C[7];				// 79C
	UInt8				gameDifficulty;			// 7B8
	UInt8				pad7B9[3];				// 7B9
	bool				isHardcore;				// 7BC
	UInt8				pad7BD[3];				// 7BD
	UInt32				unk7C0[49];				// 7C0
	TList<void>			perkEntries[74];		// 884 TList<BGSEntryPointPerkEntry>
	UInt32				unkAD4[161];			// AD4
	NiPoint3			ReticleOffset;			// D58
	void*				combatActors;			// D64 CombatActors
	UInt32				teammateCount;			// D68
	UInt32				unkD6C[5];				// D6C
	NiNode*				niNodeD80;				// D80
	UInt32				unkD84[12];				// D84
	NiNode*				niNodeDB4;				// DB4
	UInt32				unkDB8[7];				// DB8
	NiPoint3			vectorDD4;				// DD4
	NiPoint3			cameraPos;				// DE0
	void*				rigidBody;				// DEC bhkRigidBody
	bool				isInCombat;				// DF0
	bool				isUnseen;				// DF1
	UInt8				byteDF2;				// DF2
	UInt8				byteDF3;				// DF3
	UInt32				unkDF4[23];				// DF4
};
assert(sizeof(PlayerCharacter) == 0xE50);

class SkinInfo {
public:
	NiNode*			Bip01Node;				// 000
	UInt32			unk004;
	NiNode*			HeadNode;				// 008
	UInt32			unk00C;
	NiNode*			WeaponNode;				// 010
	UInt32			unk014;
	NiNode*			LForeTwistNode;			// 018
	UInt32			unk01C;
	NiNode*			Spine2Node;				// 020
	UInt32			unk024;
	NiNode*			Neck1Node;				// 028
	UInt32			unk02C;
	NiNode*			unk030;					// 030
	UInt32			unk034;
	NiNode*			unk038;					// 038
	UInt32			unk03C;
	NiNode*			unk040;					// 040
	UInt32			unk044;
	NiNode*			unk048;					// 048
	TESForm*		UpperBodyForm;
	TESModel*		UpperBodyModel;
	NiNode*			UpperBodyObject;		// 054
	UInt32			unk058;
	TESForm*		LeftHandForm;
	TESModel*		LeftHandModel;
	NiNode*			LeftHandObject;         // 064
	UInt32			unk068;
	TESForm*		RightHandForm;			// 06C
	TESModel*		RightHandModel;			// 070
	NiNode*			RightHandObject;		// 074
	UInt32			unk078;
	TESObjectWEAP*	WeaponForm;				// 07C
	TESModel*		WeaponModel;			// 080
	NiNode*			WeaponObject;			// 084
	UInt32			unk088;
	TESForm*		LightForm;				// 08C PipBoyForm (LightForm to maintain the compatibility with OR)
	TESModel*		LightModel;				// 090 PipBoyModel (LightModel to maintain the compatibility with OR)
	NiNode*			LightObject;			// 094 PipBoyObject (LightObject to maintain the compatibility with OR)
	UInt32			unk098[135];
};
assert(sizeof(SkinInfo) == 0x2B4);

class AnimSequenceBase {
public:
	virtual void					Destructor(UInt8 Arg);
	virtual void					AddAnimGroupSequence(BSAnimGroupSequence* AnimGroupSequence);
	virtual void					Unk_02();
	virtual UInt8					IsSingle();
	virtual BSAnimGroupSequence*	GetAnimGroupSequence(int Index); // Index is not used if Single (returns the anim); Index = -1 returns a random anim in the NiTList<BSAnimGroupSequence>* for Multiple
	virtual BSAnimGroupSequence*	GetAnimGroupSequence2(void* Unk01);
	virtual void					Unk_06();
};
assert(sizeof(AnimSequenceBase) == 0x004);

class AnimSequenceSingle : public AnimSequenceBase {
public:
	BSAnimGroupSequence* Anim;	// 04
};
assert(sizeof(AnimSequenceSingle) == 0x008);

class AnimSequenceMultiple : public AnimSequenceBase {
public:
	NiTList<BSAnimGroupSequence>* Anims;	// 04
};
assert(sizeof(AnimSequenceMultiple) == 0x008);

class ActorAnimData {
public:
	UInt32						unk000;				// 000
	Actor*						actor;				// 004
	NiNode*						RootNode;			// 008
	NiNode*						AccumNode;			// 00C
	UInt32						unk010;				// 010
	float						unk014;				// 014
	float						unk018;				// 018
	UInt32						unk01C;				// 01C
	float						unk020;				// 020
	UInt32						unk024;				// 024
	NiNode*						nPelvis;			// 028
	NiNode*						nBip01;				// 02C
	NiNode*						nLForearm;			// 030
	NiNode*						nHead;				// 034
	NiNode*						nWeapon;			// 038
	UInt32						unk03C[2];			// 03C
	NiNode*						nNeck1;				// 044
	UInt32						unk048[34];			// 048
	float						unk0D0;				// 0D0
	UInt32						unk0D4;				// 0D4
	NiControllerManager*		manager;			// 0D8
	NiTMap<UInt32, AnimSequenceBase>*	animsMap;			// 0DC
	BSAnimGroupSequence*		animSequences[8];	// 0E0
	BSAnimGroupSequence*		animSeq100;			// 100
	UInt32						unk104;				// 104
	UInt32						unk108;				// 108
	float						unk10C;				// 10C
	float						unk110;				// 110
	float						unk114;				// 114
	float						unk118;				// 118
	float						unk11C;				// 11C
	UInt32						unk120;				// 120
	void*						unk124;				// 124
	void*						unk128;				// 128
};
assert(sizeof(ActorAnimData) == 0x12C);

class TESAnimGroup : public NiRefObject {
public:
	enum { // From Oblivion. To be revisioned.
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

	UInt32		unk008;			//008
	UInt32		unk00C;			//00C
	UInt8		animGroup;		//010 This value is used with the animType (as UInt16) as key for the ActorAnimData NiTPointerMap<AnimSequenceBase>*
	UInt8		animType;		//011
	UInt8		pad012;			//012
	UInt8		pad013;			//013
	UInt32		unk014[10];		//014
};
assert(sizeof(TESAnimGroup) == 0x03C);

class SkyObject {
public:
	virtual SkyObject*	Destroy(bool doFree);
	virtual void	    GetNiNode(void);
	virtual void	    InitNiNode(NiNode* niNode);
    virtual void	    Update(void* sky, float value);

	NiNode*				RootNode;	// 04
};
assert(sizeof(SkyObject) == 0x08);

class Sun : public SkyObject {
public:
	NiBillboardNode*	 SunBillboard;		// 08
	NiBillboardNode*	 SunGlareBillboard;	// 0C
	NiTriShape*			 SunGeometry;		// 10
	NiTriShape*			 SunGlareGeometry;	// 14
	NiTArray<NiPick*>*	 SunPickList;		// 18
	NiDirectionalLight*  SunDirLight;		// 1C Same as g_TES->directionalLight
	float				 glareScale;		// 20
	UInt8				 byte24;			// 24
	UInt8				 byte25;			// 25
	UInt8			     byte26;			// 26
	UInt8				 byte27;			// 27
	BSShaderAccumulator* shaderAccum;		// 28 BSShaderAccumulator*
};
assert(sizeof(Sun) == 0x2C);

class Atmosphere : public SkyObject {
public:
	virtual void		Init(NiNode* niNode, BSFogProperty* _fogProp);
    
	NiNode*		    Mesh;			// 08
	BSFogProperty*	fogProperty;	// 0C Same as *0x11DEB00
	NiRefObject*	object10;		// 10
	NiRefObject*	Quad;			// 14
	UInt8			unk18;			// 18
	UInt8			pad19[3];

};
assert(sizeof(Atmosphere) == 0x01C);

class NiFogProperty : public NiProperty
{
public:
	unsigned __int16 m_flags;
	float m_fDepth;
	NiColor m_kColor;
};

class BSFogProperty : public NiFogProperty
{
public:
	float fStartDistance;
	float fEndDistance;
	float fStartWaterDistance;
	float fEndWaterDistance;
	NiPlane kPlane;
	float fFalloff;
	float fHeight;
	NiColor kWaterColor;
	float fPower;
};
assert(sizeof(BSFogProperty) == 0x64);


class Stars : public SkyObject {	
public:
	NiNode*			node08;			// 08
	float			flt0C;			// 0C
};
assert(sizeof(Stars) == 0x010);

class Clouds : public SkyObject {
public:

	NiTriStrips*		layers[4];		// 08 (NiTriStrips)
	NiSourceTexture*	textures[4];	// 18
	NiPoint3			layerPos[4];	// 28
	UInt16				numLayers;		// 58
	UInt8				byte5A;			// 5A
	UInt8				byte5B;			// 5B
};
assert(sizeof(Clouds) == 0x05C);

class Precipitation {
public:
	virtual Precipitation*	Destroy(bool doFree);

	NiNode*		node04;		// 04
	NiNode*		node08;		// 08
	UInt32		unk0C;		// 0C
	float		unk10;		// 10
	UInt32		unk14;		// 14
};
assert(sizeof(Precipitation) == 0x018);

class Moon : public SkyObject {
public:
	virtual void	Refresh(NiNode* niNode, const char* moonStr);
    
	NiNode*			MoonNode;			// 08
	NiNode*			ShadowNode;			// 0C
	NiTriShape*		MoonMesh;			// 10
	NiTriShape*		ShadowMesh;			// 14
	char*			texture_full;		// 18
	UInt32			unk1C;				// 1C
	char*			texture_three_wan;	// 20
	UInt32			unk24;				// 24
	char*			texture_half_wan;	// 28
	UInt32			unk2C;				// 2C
	char*			texture_one_wan;	// 30
	UInt32			unk34;				// 34
	UInt32			unk38;				// 38
	UInt32			unk3C;				// 3C
	char*			texture_one_wax;	// 40
	UInt32			unk44;				// 44
	char*			texture_half_wax;	// 48
	UInt32			unk4C;				// 4C
	char*			texture_three_wax;	// 50
	UInt32			unk54;				// 54
	float			AngleFadeStart;		// 58  (masser = 55, sec = 55)
	float			AngleFadeEnd;		// 5C  (masser = 45 sec = 40)
	float			unk60;				// 60
	float			unk64;				// 64
	float			ZOffset;			// 68
	UInt32			unk6C;				// 6C
	UInt32			unk70;				// 70
	float			degree;				// 74
	float			unk78;				// 78
	
	float			fadeValue() {
		float result;
		if ((this->degree) <= 180.0) {

			if ((this->degree) > 90) {
				result = (180.0f - this->degree) / 15.0f;
				return result > 1.0f ? 1.0f : result;
			}
			else {
				result = this->degree / 15.0f;
				return result > 1.0f ? 1.0f : result;
			}
		}
        return 0;
    }
};
assert(sizeof(Moon) == 0x07C);

class Sky {
public:
	void ForceWeather(TESWeather* Weather) { ThisCall(0x0063D0E0, this, Weather, 0); }
	static Sky* Get() { return *(Sky**)0x11DEA20; }

	float GetSunriseBegin() { return ThisCallD(0x595EA0, this); }
	float GetSunriseEnd()   { return ThisCallD(0x595F50, this); }
	float GetSunsetBegin()  { return ThisCallD(0x595FC0, this); }
	float GetSunsetEnd()    { return ThisCallD(0x596030, this); }
	float GetSunriseColorBegin() { return ThisCallD(0x63B9B0, this); }
	float GetSunsetColorEnd() { return ThisCallD(0x63BA30, this); }

	enum Flags : UInt32
	{
		kSkyFlag_IsInitWeather = 0x1,
		kSkyFlag_IsUpdateWeather = 0x3,
		kSkyFlag_IsUnderwater = 0x4,
		kSkyFlag_SetAcceleration = 0x8,
		kSkyFlag_FastTravel = 0x10,
		kSkyFlag_UpdateMoonPhase = 0x20,
		kSkyFlag_IsClimateChange = 0x40,
		kSkyFlag_NoCachedSunriseBegin = 0x100,
		kSkyFlag_NoCachedSunriseEnd = 0x200,
		kSkyFlag_NoCachedSunsetBegin = 0x400,
		kSkyFlag_NoCachedSunsetEnd = 0x800,
		kSkyFlag_NoCachedBeginSunriseColors = 0x1000,
		kSkyFlag_NoCachedEndSunsetColors = 0x2000,
	};

//	void RefreshMoon();
	void RefreshClimate(TESClimate* climate, bool immediate = true)
	{
		ThisCall(0x0063C8F0, this, climate, immediate);
	}
//	bool GetIsRaining();
	void**			_vtbl;				// 000
	NiNode*			nodeSkyRoot;		// 004
	NiNode*			nodeMoonsRoot;		// 008
	TESClimate*		firstClimate;		// 00C
	TESWeather*		firstWeather;		// 010
	TESWeather*		secondWeather;		// 014	Previous weather, gradually fading, on weather transition
	TESWeather*		defaultWeather;		// 018	Picked from currClimate weathers list. currClimate is set to this unless there's a regional weather
	TESWeather*		weatherOverride;	// 01C
	Atmosphere*		atmosphere;			// 020
	Stars*			stars;				// 024
	Sun*			sun;				// 028
	Clouds*			clouds;				// 02C
	Moon*			masserMoon;			// 030
	Moon*			secundaMoon;		// 034
	Precipitation*	precipitation;		// 038
	NiColor			skyUpper;			// 03C
	NiColor			fogColor;			// 048
	NiColor			CloudsLower;		// 054
	NiColor			sunAmbient;			// 060
	NiColor			sunDirectional;		// 06C
	NiColor			SunColor;			// 078
	NiColor			Stars;				// 084
	NiColor			SkyLower;			// 090
	NiColor			Horizon;			// 09C	virtual void	Refresh(NiNode* niNode, const char* moonStr);
	NiColor			CloudsUpper;		// 0A8
	NiColor			Lighting;			// 0B4
	NiColor			sunFog;				// 0C0
	float			windSpeed;			// 0CC
	float			windDirection;		// 0D0
	float			fogNearPlane;		// 0D4
	float			fogFarPlane;		// 0D8
	UInt32			unk0DC;				// 0DC
	UInt32			unk0E0;				// 0E0
	UInt32			unk0E4;				// 0E4
	float			fogPower;			// 0E8
	float			gameHour;			// 0EC
	float			lastUpdateHour;		// 0F0
	float			weatherPercent;		// 0F4
	UInt32			unk0F8;				// 0F8
	TList<void*>*	skySounds;			// 0FC   TList<SkySound>*
	float			lightningFxPerc;	// 100 // DONE
    UInt32			unk104;				// 104
	float			flt108;				// 108
	float			flt10C;				// 10C
	float			flt110;				// 110
	UInt32			unk114;				// 114
	UInt32			flags;				// 118
	void*			currFadeInIMOD;		// 11C ImageSpaceModifierInstanceForm*
	void*			currFadeOutIMOD;	// 120
	void*			transFadeInIMOD;	// 124  On weather transition, set to the previuos weather fadeIn/OutIMODs
	void*			transFadeOutIMOD;	// 128
	float			flt12C;				// 12C	Always 12.0
	float			flt130;				// 130	Always 23.99
	float			flt134;				// 134	Always 0
	
	bool GetIsUnderWater() { return this->flags & Sky::kSkyFlag_IsUnderwater; }

};
assert(sizeof(Sky) == 0x138);

class GridArray {
public:
	virtual void*	Destroy(bool doFree);
	virtual void	Fn_01(void);
	virtual void	Fn_02(void);
	virtual void	Fn_03(void);
	virtual void	Fn_04(void);
	virtual void	Fn_05(void);
};
assert(sizeof(GridArray) == 0x04);

class GridCellArray : public GridArray {
public:
	virtual void	Fn_06(void);
	virtual void	Fn_07(void);
	virtual void	Fn_08(void);
	virtual void	Fn_09(void);

	TESObjectCELL*	GetCell(UInt32 x, UInt32 y) { return *(TESObjectCELL**)ThisCall(0x004BA490, this, x, y); }
	TESObjectCELL*	GetCell(UInt32 Index) { return gridCells[Index]; }

	SInt32			worldX;			// 04	X coord of current cell within worldspace
	SInt32			worldY;			// 08	Y coord "
	UInt8			size;			// 0C	Init'd to uGridsToLoad
	UInt8			pad0D[3];		// 0D
	TESObjectCELL** gridCells;		// 10	Size is gridSize^2
	float			posX;			// 14	worldX * 4096
	float			posY;			// 18	worldY * 4096
	UInt32			unk1C[3];		// 1C
};
assert(sizeof(GridCellArray) == 0x028);

template <typename Data> class DNode{
public:
  DNode<Data> *next;
  DNode<Data> *prev;
  Data* data;
};
template <typename Data> class DList{
public:
    DNode<Data>* first;
    DNode<Data>* last;
    UInt32 count;  
};
assert(sizeof(DList<void>) == 0xC);

struct WaterGroup
{
    TESWaterForm			*waterForm;		// 00
    NiVector4				vector04;		// 04
    NiVector4				vector14;		// 14
    DList<TESObjectREFR>	waterPlanes;	// 24
    DList<void>				list30;			// 30
    DList<void>				list3C;			// 3C
    DList<void>				list48;			// 48
    NiAVObject				*object54;		// 54
    NiAVObject				*object58;		// 58
    UInt8					byte5C;			// 5C
    UInt8					byte5D;			// 5D
    UInt8					byte5E;			// 5E
    UInt8					byte5F;			// 5F
    UInt8					byte60;			// 60
    UInt8					pad61[3];		// 61
    DList<void>				list64;			// 64
    DList<void>				list70;			// 70
    DList<void>				list7C;			// 7C
    DList<void>				list88;			// 88
    NiObject				*object94;		// 94
    NiObject				*object98;		// 98
    UInt32					unk9C;			// 9C
    UInt32					unkA0;			// A0
    NiObject				*objectA4;		// A4
    NiObject				*objectA8;		// A8
    UInt32					unkAC;			// AC
};

class WaterManager {
public:
	UInt32 numWaterGroups;					// 000
	UInt32				unk04;					// 004
	UInt32				unk08;					// 008
	UInt32				unk0C;					// 00C
	UInt32				unk10;					// 010
	UInt32				unk14;					// 014
	UInt32				unk18;					// 018
	NiSourceTexture*	WaterTexture;			// 01C
	UInt32				unk20;					// 020
	float				unk24;					// 024
	UInt32				unk28;					// 028
	UInt32				unk2C;					// 02C
	UInt32				unk30;					// 030
	UInt8				unk34;					// 034
	UInt8				pad34[3];
	float				unk38;					// 038
	DList<WaterGroup>	waterGroups;			// 03C
	WaterGroup			*waterLOD; 				// 048
	NiTMap<TESObjectREFR*, TESObjectREFR*>		unkReflectionExplosion;	// 04C Seems to be used only under a bReflectExplosions = 1 condition
	NiTMap<TESObjectREFR*, TESObjectREFR*>		unk5C;	// 05C
	NiTMap<TESWaterForm*, bool>					unk6C;	// 06C
	NiTMap<TESObjectREFR*, void*>				unk7C;	// 07C NiTMap<TESObjectREFR*, WadingWaterData*>
	UInt32				unk8C;					// 08C
	UInt32				unk90;					// 090
	UInt32				unk94;					// 094
	float				unk98;					// 098
	UInt8				unk9C;					// 09C
	UInt8				pad9C[3];
};
assert(sizeof(WaterManager) == 0x0A0);

class TES {
public:
	virtual void		Fn_00(UInt32 arg1, UInt32 arg2, UInt32 arg3, UInt32 arg4, UInt32 arg5);
	
	void				PurgeCells() {}
	float				GetWaterHeight(TESObjectREFR* Ref) {
//							Logger::Log("Get Water Height");
							TESObjectCELL* Cell = Ref->parentCell;
							float r = worldSpace->defaultWaterHeight;

							if (Cell && Cell->flags0 & TESObjectCELL::kFlags0_HasWater) {
								if (Ref->renderData) {
									r = Ref->renderData->waterHeight;
//									Logger::Log("Ref->renderData %f", r);
								}
								else {
									r = Cell->GetWaterHeight();
//									Logger::Log("Cell %f", r);
								}
							}
//							Logger::Log("default %f", r);
							return r;
						}
	TESWaterForm*		GetWaterForm() { return currentCell ? currentCell->GetWaterForm() : NULL; }

	UInt32								unk04;				// 04
	GridCellArray*						gridCellArray;		// 08
	NiNode*								objectLODRoot;		// 0C
	NiNode*								landLOD;			// 10
	NiNode*								waterLOD;			// 14
	BSTempNodeManager*					tempNodeManager;	// 18
	NiDirectionalLight*					directionalLight;	// 1C
	void*								ptr20;				// 20
	SInt32								extCoordX;			// 24
	SInt32								extCoordY;			// 28
	SInt32								unk2C[2];			// 2C
	TESObjectCELL*						currentCell;		// 34
	TESObjectCELL**						interiorsBuffer;	// 38
	TESObjectCELL**						exteriorsBuffer;	// 3C
	UInt32								unk40[9];			// 40
	WaterManager*						waterManager;		// 64
	Sky*								sky;				// 68
	TList<void>							activeIMODs;		// 6C TList<ImageSpaceModifierInstance>
	UInt32								unk74[3];			// 74
	float								unk80[2];			// 80
	TESWorldSpace*						worldSpace;			// 88
	TList<void>							list8C;				// 8C
	TList<void>							list94;				// 94
	TList<void>							list9C;				// 9C
	void*								unkA4;				// A4 QueuedFile*
	NiSourceTexture*					unkA8;				// A8
	void*								unkAC;				// AC QueuedFile*
	void*								ptrB0;				// B0
	UInt32								unkB4[2];			// B4
	void*								navMeshInfoMap;		// BC NavMeshInfoMap*
	void*								unkC0;				// C0 LoadedAreaBound*
};
assert(sizeof(TES) == 0xC4);

class TESGameSound {
public:
	UInt32			unk00;		// 00
	UInt8			unk04;		// 04
	UInt8			pad04[3];
	UInt32			unk08;		// 08
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
	TESAnimGroup* animGroup;	//074
};
assert(sizeof(BSAnimGroupSequence) == 0x078);

class Tile {
public:
	enum TileValue {
		kTileValue_x = 0xFA1,
		kTileValue_y,
		kTileValue_visible,
		kTileValue_class,
		kTileValue_clipwindow = 0xFA6,
		kTileValue_stackingtype,
		kTileValue_locus,
		kTileValue_alpha,
		kTileValue_id,
		kTileValue_disablefade,
		kTileValue_listindex,
		kTileValue_depth,
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
		kTileValue_clicked = 0xFC7,
		kTileValue_clicksound = 0xFCB,
		kTileValue_filename,
		kTileValue_filewidth,
		kTileValue_fileheight,
		kTileValue_repeatvertical,
		kTileValue_repeathorizontal,
		kTileValue_animation = 0xFD2,
		kTileValue_linecount = 0xDD4,
		kTileValue_pagecount,
		kTileValue_xdefault,
		kTileValue_xup,
		kTileValue_xdown,
		kTileValue_xleft,
		kTileValue_xright,
		kTileValue_xbuttona = 0xFDD,
		kTileValue_xbuttonb,
		kTileValue_xbuttonx,
		kTileValue_xbuttony,
		kTileValue_xbuttonlt,
		kTileValue_xbuttonrt,
		kTileValue_xbuttonlb,
		kTileValue_xbuttonrb,
		kTileValue_xbuttonstart = 0xFE7,
		kTileValue_mouseoversound,
		kTileValue_draggable,
		kTileValue_dragstartx,
		kTileValue_dragstarty,
		kTileValue_dragoffsetx,
		kTileValue_dragoffsety,
		kTileValue_dragdeltax,
		kTileValue_dragdeltay,
		kTileValue_dragx,
		kTileValue_dragy,
		kTileValue_wheelable,
		kTileValue_wheelmoved,
		kTileValue_systemcolor,
		kTileValue_brightness,
		kTileValue_linegap = 0xFF7,
		kTileValue_resolutionconverter,
		kTileValue_texatlas,
		kTileValue_rotateangle,
		kTileValue_rotateaxisx,
		kTileValue_rotateaxisy,

		kTileValue_user0 = 0x1004,
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

		kTileValue_max
	};

	virtual Tile*		Destroy(bool doFree);
	virtual void		Init(Tile* parent, const char* name, Tile* replacedChild);
	virtual NiNode*		CalcNode();
	virtual UInt32		GetType();		// returns one of kTileValue_XXX
	virtual const char* GetTypeStr();	// 4-byte id
	virtual bool		Unk_05(UInt32 arg0, UInt32 arg1);
	virtual UInt32		UpdateField(UInt32 valueID, float floatValue, const char* strValue);
	virtual void		Unk_07();
	virtual UInt32		Unk_08();
	virtual void		Unk_09(UInt32 arg0, UInt32 arg1, UInt32 arg2);

	class ChildNode {
	public:
		ChildNode*	next;
		ChildNode*	prev;
		Tile*		child;
	};

	struct Value {
		UInt32		id;		// 00
		Tile*		parent;	// 04
		float		num;	// 08
		char*		str;	// 0C
		void*		action;	// 10
	};

	void						SetFloat(UInt32 Index, float Value) { ThisCall(0x00A012D0, this, Index, Value, 1); }

	ChildNode*					firstChild;		// 04
	ChildNode*					lastChild;		// 08
	UInt32						childCount;		// 0C
	TArray<Value>				valueList;		// 10
	BSString					name;			// 20
	Tile*						parent;			// 28
	NiNode*						node;			// 2C
	UInt32						flags;			// 30
	UInt8						unk34;			// 34
	UInt8						unk35;			// 35
	UInt8						pad35[2];		// 36
};
assert(sizeof(Tile) == 0x38);

class TileImage : public Tile {
public:
	float		flt038;			// 38
	UInt32		unk03C;			// 3C
	void*		shaderProp;		// 40 TileShaderProperty*
	UInt8		byt044;			// 44
	UInt8		pad044[3];		// 45-47
};
assert(sizeof(TileImage) == 0x48);

class TileRect : public Tile {
public:
	UInt32	unk38;	// 38
};
assert(sizeof(TileRect) == 0x3C);

class TileMenu : public TileRect {
public:
	Menu*	menu;	// 3C
};
assert(sizeof(TileMenu) == 0x40);

class Menu {
public:
	enum MenuType {
		kMenuType_None = 0,			// for gamemode
		kMenuType_BigFour,			// F1 - F4 menus
		kMenuType_Any,
		kMenuType_Console,
		kMenuType_Main,

		kMenuType_Min =				0x3E9,
		kMenuType_Message =			kMenuType_Min,
		kMenuType_Inventory,
		kMenuType_Stats,
		kMenuType_HUDMain,
		kMenuType_Loading =			0x3EF,
		kMenuType_Container,
		kMenuType_Dialog,
		kMenuType_SleepWait =		0x3F4,
		kMenuType_Start,
		kMenuType_LockPick,
		kMenuType_Quantity =		0x3F8,
		kMenuType_Map =				0x3FF,
		kMenuType_Book =			0x402,
		kMenuType_LevelUp,
		kMenuType_Persuasion =		0x40A,
		kMenuType_Repair,
		kMenuType_RaceSex,
		kMenuType_Credits =			0x417,
		kMenuType_CharGen,
		kMenuType_TextEdit =		0x41B,
		kMenuType_Barter =			0x41D,
		kMenuType_Surgery,
		kMenuType_Hacking,
		kMenuType_VATS,
		kMenuType_Computers,
		kMenuType_RepairServices,
		kMenuType_Tutorial,
		kMenuType_SpecialBook,
		kMenuType_ItemMod,
		kMenuType_LoveTester =		0x432,
		kMenuType_CompanionWheel,
		kMenuType_TraitSelect,
		kMenuType_Recipe,
		kMenuType_SlotMachine =		0x438,
		kMenuType_Blackjack,
		kMenuType_Roulette,
		kMenuType_Caravan,
		kMenuType_Trait =			0x43C,
		kMenuType_Max =				kMenuType_Trait,
	};

	virtual void	Destructor(bool arg0);		// pass false to free memory
	virtual void	SetField(UInt32 idx, Tile* value);
	virtual void	Unk_02(UInt32 arg0, UInt32 arg1);	// show menu?
	virtual void	HandleClick(UInt32 buttonID, Tile* clickedButton); // buttonID = <id> trait defined in XML
	virtual void	HandleMouseover(UInt32 arg0, Tile * activeTile);	//called on mouseover, activeTile is moused-over Tile
	virtual void	Unk_05(UInt32 arg0, UInt32 arg1);
	virtual void	Unk_06(UInt32 arg0, UInt32 arg1, UInt32 arg2);
	virtual void	Unk_07(UInt32 arg0, UInt32 arg1, UInt32 arg2);
	virtual void	Unk_08(UInt32 arg0, UInt32 arg1);
	virtual void	Unk_09(UInt32 arg0, UInt32 arg1);
	virtual void	Unk_0A(UInt32 arg0, UInt32 arg1);
	virtual void	Unk_0B();
	virtual bool	HandleKeyboardInput(char inputChar);	//for keyboard shortcuts, return true if handled
	virtual UInt32	GetID();
	virtual bool	Unk_0E(UInt32 arg0, UInt32 arg1);
	virtual void	Unk_0F();
	virtual void	Unk_10();
	virtual void	Unk_11();

	TileMenu*		tile;		// 04
	UInt32			unk08;		// 08
	UInt32			unk0C;		// 0C
	UInt32			unk10;		// 10
	UInt32			unk14;		// 14
	UInt32			unk18;		// 18
	UInt32			unk1C;		// 1C
	UInt32			id;			// 20
	UInt32			unk24;		// 24
};
assert(sizeof(Menu) == 0x28);

class HUDMainMenu : public Menu {
public:
	struct QueuedMessage {
		char	msgText[0x204];			// 000
		char	iconPate[MAX_PATH];		// 204
		char	soundPath[MAX_PATH];	// 308
		float	displayTime;			// 40C
	};

	UInt32					unk028;			// 028
	TileImage*				tile02C;		// 02C
	TileText*				tile030;		// 030
	TileRect*				tile034;		// 034
	TileRect*				tile038;		// 038
	TileRect*				tile03C;		// 03C
	TileImage*				tile040;		// 040
	TileImage*				tile044;		// 044
	TileText*				tile048;		// 048
	TileText*				tile04C;		// 04C
	TileImage*				tile050;		// 050
	TileImage*				tile054;		// 054
	TileText*				tile058;		// 058
	TileRect*				tile05C;		// 05C
	TileRect*				tile060;		// 060
	TileText*				tile064;		// 064
	TileText*				tile068;		// 068
	TileImage*				tile06C;		// 06C
	TileImage*				tile070;		// 070
	TileText*				tile074;		// 074
	TileText*				tile078;		// 078
	TileImage*				tile07C;		// 07C
	TileImage*				tile080;		// 080
	TileText*				tile084;		// 084
	TileText*				sneakLabel;		// 088
	TileImage*				tile08C;		// 08C
	TileText*				tile090;		// 090
	TileImage*				tile094;		// 094
	TileText*				tile098;		// 098
	TileRect*				tile09C;		// 09C
	TileText*				tile0A0;		// 0A0
	TileImage*				tile0A4;		// 0A4
	TileText*				tile0A8;		// 0A8
	TileText*				tile0AC;		// 0AC
	TileText*				tile0B0;		// 0B0
	TileText*				tile0B4;		// 0B4
	TileText*				tile0B8;		// 0B8
	TileText*				tile0BC;		// 0BC
	TileText*				tile0C0;		// 0C0
	TileImage*				tile0C4;		// 0C4
	TileRect*				tile0C8;		// 0C8
	TileText*				tile0CC;		// 0CC
	TileImage*				tile0D0;		// 0D0
	TileImage*				tile0D4;		// 0D4
	TileImage*				tile0D8;		// 0D8
	TileText*				tile0DC;		// 0DC
	TileText*				tile0E0;		// 0E0
	TileImage*				tile0E4;		// 0E4
	TileText*				tile0E8;		// 0E8
	TileText*				tile0EC;		// 0EC
	TileText*				tile0F0;		// 0F0
	TileImage*				crosshair;		// 0F4
	TileImage*				tile0F8;		// 0F8
	TileImage*				tile0FC;		// 0FC
	TileImage*				tile100;		// 100
	TileImage*				tile104;		// 104
	TileImage*				tile108;		// 108
	TileImage*				tile10C;		// 10C
	TileImage*				tile110;		// 110
	TileRect*				tile114;		// 114
	TileRect*				tile118;		// 118
	TileRect*				tile11C;		// 11C
	TileRect*				tile120;		// 120
	TileRect*				tile124;		// 124
	TileRect*				tile128;		// 128
	TileRect*				tile12C;		// 12C
	TileRect*				tile130;		// 130
	TileRect*				tile134;		// 134
	TileRect*				tile138;		// 138
	TileRect*				tile13C;		// 13C
	TileRect*				tile140;		// 140
	TileRect*				tile144;		// 144
	void*					tile148;		// 148 Tile3D*
	TileRect*				tile14C;		// 14C
	TileRect*				tile150;		// 150
	TileImage*				tile154;		// 154
	TileImage*				tile158;		// 158
	TileText*				tile15C;		// 15C
	TileRect*				tile160;		// 160
	TileText*				tile164;		// 164
	TileText*				tile168;		// 168
	TileText*				tile16C;		// 16C
	TileImage*				tile170;		// 170
	TileImage*				tile174;		// 174
	TileText*				tile178;		// 178
	TileText*				tile17C;		// 17C
	TileImage*				tile180;		// 180
	UInt32					unk184[2];		// 184
	TList<QueuedMessage>	queuedMessages;	// 18C
	UInt32					currMsgKey;		// 194
	UInt32					array198[4];	// 198 BSSimpleArray<void>
	UInt32					unk1A8[4];		// 1A8
	TESObjectREFR*			crosshairRef;	// 1B8
	UInt32					unk1BC[3];		// 1BC
	TileRect*				tile1C8;		// 1C8
	TileRect*				tile1CC;		// 1CC
	UInt32					unk1D0;			// 1D0
	TileRect*				tile1D4;		// 1D4
	TileRect*				tile1D8;		// 1D8
	TileRect*				tile1DC;		// 1DC
	TileRect*				tile1E0;		// 1E0
	TileRect*				tile1E4;		// 1E4
	TileRect*				tile1E8;		// 1E8
	UInt32					unk1EC[5];		// 1EC
	NiControllerSequence*	niContSeq;		// 200
	UInt32					unk204[6];		// 204
	Actor*					healthTarget;	// 21C
	UInt32					unk220[4];		// 220
	void*					ptr230;			// 230
	void*					ptr234;			// 234
	UInt32					unk238[16];		// 238
};
assert(sizeof(HUDMainMenu) == 0x278);

class ModInfo {
public:
	struct ChunkInfo {
		UInt32	type;		// e.g. 'GRUP', 'GLOB', etc
		UInt16	length;
		UInt16	pad;
	};

	struct FormInfo {  // Record Header in FNVEdit
		UInt32		recordType;			// 00 i.e. 'FACT', 'GMST'						Signature
		UInt32		dataSize;			// 04 looks like size of entire record			Data Size
		UInt32		formFlags;			// 08 copied to TESForm->flags					Record Flags
		UInt32		formID;				// 0C											FormID
		UInt32		unk10;				// 10											Version Control Info 1
		UInt16		formVersion;		// 14 always initialized to 0F on SaveForm.		Form Version
		UInt16		unk16;				// 16                                           Version Control Info 2
	};

	struct GroupInfo { // Record Header in FNVEdit
		UInt32		recordType;			// 00 'GRUP'									Signature
		UInt32		groupSize;			// 04 Size of entire record						Size
		UInt32		groupLabel;			// 08 copied to TESForm->flags					Label
		UInt32		groupType;			// 0C forms, dialog, cell...					Type
		UInt32		unk10;				// 10											Stamp
		UInt16		unk14;				// 14											Part of Unknown
		UInt16		unk16;				// 16                                           Part of Unknown
	};

	struct FileHeader {	// File header in FNVEdit Signature 'HEDR'
		float	version;		//	00
		UInt32	recordCount;	//	04
		UInt32	nextObectID;	//	08
	};

	struct	MasterSize {	// Data member of the master list in WIN32_FIND_DATA format
		UInt32	low;
		UInt32	high;
	};

	TList<void>			unkList;			// 000 treated as ModInfo during InitializeForm, looks to be a linked list of modInfo
	void*				pointerMap;			// 008 *NiTPointerMap<TESFile*>*
	UInt32				unk00C;				// 00C
	BSFile*				unkFile;			// 010
	UInt32				unk014;				// 014 
	void*				unk018;				// 018 seen all zeroes. size unknown, seen not valid pointer in FalloutNV.esm
	void*				unk01C;				// 01C as above
	char				name[0x104];		// 020
	char				filepath[0x104];	// 124
	UInt32				unk228;				// 228
	UInt32				unk22C;				// Masters are init'd to dword_1186740 (0x2800) same val as BSFile+10? Buffer size ?
	UInt32				unk230;				// 230
	UInt32				unk234;				// 234
	UInt32				unk238;				// 238
	UInt32				unk23C;				// 23C
	FormInfo			formInfo;			// 240
	ChunkInfo			subRecordHeader;	// 258
	UInt32				unk260;				// 260 could be file size, has it is compared with fileOffset during load module. But filesize would be an Int64 !
	UInt32				fileOffset;			// 264
	UInt32				dataOffset;			// 268 index into dataBuf
	UInt32				subrecordBytesRead;	// 26C generates error on Read if != expected length
	FormInfo			writeInfo;			// 270 "used" to add record to the plugin.
	UInt32				writeOffset;		// 288
	UInt32				subrecordBytesToWrite;	// 28C
	TList<void>			tList290;			// 290 looks to be a list of form or a list of formInfo. referenced from TESForm::WriteForm
	UInt8				unk298;				// 298
	UInt8				bIsBigEndian;		// 299
	UInt8				unk29A;				// 29A
	UInt8				pad29B;
	UInt32				fileData[80];		// 29C WIN32_FIND_DATA?
	FileHeader			header;				// 3DC
	UInt8				flags;				// 3E8	Bit 0 is ESM . Runtime: Bit 2 is Valid, Bit 3 is Unselected Editor: 2 is selected, 3 is active, 4 may be invalid, 6 is endian, 14 controls VCI.
	UInt8				pad3E9[3];
	TList<char*>*		refModNames;		// 3EC	paired with 3F0
	UInt32				unk3F0;				// 3F0
	TList<MasterSize*>* refModData;		// 3F4 most likely full of 0
	UInt32				unk3F8;				// 3F8
	UInt32				numRefMods;			// 3FC related to modindex; see 4472D0
	ModInfo**			refModInfo;		// 400 used to look up modInfo based on fixed mod index, double-check
	UInt32				unk404;				// 404
	UInt32				unk408;				// 408
	UInt8				modIndex;			// 40C init to 0xFF
	UInt8				pad40D[3];
	BSString			author;				// 410
	BSString			description;		// 418
	void*				dataBuf;			// 420 
	UInt32				dataBufSize;		// 424 looks like size of entire record
	UInt8				unk428;				// 428 decide if forms needs to be reloaded on LoadFiles
	UInt8				pad429[3];
};
assert(sizeof(ModInfo) == 0x42C);

class ModList {
public:
	TList<ModInfo>		modInfoList;		// 00
	UInt32				loadedModCount;		// 08
	ModInfo*			loadedMods[0xFF];	// 0C
};
assert(sizeof(ModList) == 0x408);

class MainDataHandler {
public:
	
	TESForm*				CreateForm(UInt8 FormType) { TESForm* (__cdecl* CreateForm)(UInt8) = (TESForm* (__cdecl*)(UInt8))0x00465110; return CreateForm(FormType); }
	bool					AddData(TESForm* Form) { return ThisCall(0x004603B0, this, Form); }
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

	UInt32							unk00;					// 000
	BoundObjectListHead*			boundObjects;			// 004
	TList<TESPackage>				packageList;			// 008
	TList<TESWorldSpace>			worldSpaceList;			// 010
	TList<TESClimate>				climateList;			// 018
	TList<TESImageSpace>			imageSpaceList;			// 020
	TList<TESImageSpaceModifier>	imageSpaceModList;		// 028
	TList<TESWeather>				weathers;				// 030
	TList<EnchantmentItem>			enchantmentItemList;	// 038
	TList<SpellItem>				spellItemList;			// 040
	TList<BGSHeadPart>				headPartList;			// 048
	TList<TESHair>					hairList;				// 050
	TList<TESEyes>					eyeList;				// 058
	TList<TESRace>					raceList;				// 060
	TList<BGSEncounterZone>			encounterZoneList;		// 068
	TList<TESLandTexture>			landTextureList;		// 070
	TList<BGSCameraShot>			cameraShotList;			// 078
	TList<TESClass>					classList;				// 080
	TList<TESFaction>				factionList;			// 088
	TList<TESReputation>			reputationList;			// 090
	TList<TESChallenge>				challengeList;			// 098
	TList<TESRecipe>				recipeList;				// 0A0
	TList<TESRecipeCategory>		recipeCategoryList;		// 0A8
	TList<TESAmmoEffect>			ammoEffectList;			// 0B0
	TList<TESCasino>				casinoList;				// 0B8
	TList<TESCaravanDeck>			caravanDeckList;		// 0C0
	TList<Script>					scriptList;				// 0C8
	TList<TESSound>					soundList;				// 0D0
	TList<BGSAcousticSpace>			acousticSpaceList;		// 0D8
	TList<BGSRagdoll>				ragdollList;			// 0E0
	TList<TESGlobal>				globalList;				// 0E8
	TList<BGSVoiceType>				voiceTypeList;			// 0F0
	TList<BGSImpactData>			impactDataList;			// 0F8
	TList<BGSImpactDataSet>			impactDataSetList;		// 100
	TList<TESTopic>					topicList;				// 108
	TList<TESTopicInfo>				topicInfoList;			// 110
	TList<TESQuest>					questList;				// 118
	TList<TESCombatStyle>			combatStyleList;		// 120
	TList<TESLoadScreen>			loadScreenList;			// 128
	TList<TESWaterForm>				waterFormList;			// 130
	TList<TESEffectShader>			effectShaderList;		// 138
	TList<BGSProjectile>			projectileList;			// 140
	TList<BGSExplosion>				explosionList;			// 148
	TList<BGSRadiationStage>		radiationStageList;		// 150
	TList<BGSDehydrationStage>		dehydrationStageList;	// 158
	TList<BGSHungerStage>			hungerStageList;		// 160
	TList<BGSSleepDeprivationStage>	sleepDepriveStageList;	// 168
	TList<BGSDebris>				debrisList;				// 170
	TList<BGSPerk>					perkList;				// 178
	TList<BGSBodyPartData>			bodyPartDataList;		// 180
	TList<BGSNote>					noteList;				// 188
	TList<BGSListForm>				listFormList;			// 190
	TList<BGSMenuIcon>				menuIconList;			// 198
	TList<TESObjectANIO>			anioList;				// 1A0
	TList<BGSMessage>				messageList;			// 1A8
	TList<BGSLightingTemplate>		lightingTemplateList;	// 1B0
	TList<BGSMusicType>				musicTypeList;			// 1B8
	TList<TESLoadScreenType>		loadScreenTypeList;		// 1C0
	TList<MediaSet>					mediaSetList;			// 1C8
	TList<MediaLocationController>	mediaLocControllerList;	// 1D0
	TESRegionList*					regionList;			// 1D8
	NiTArray<TESObjectCELL*>		cellArray;				// 1DC
	NiTArray<BGSAddonNode*>			addonArray;				// 1EC
	UInt32							unk1FC[3];				// 1FC	208 looks like next created refID
	UInt32							nextCreatedRefID;		// 208	Init'd to FF000800
	UInt32							unk20C;					// 20C	last unselected mod in modList. GECK: active ESM
	ModList							modList;				// 210
	UInt8							unk618;					// 618
	UInt8							unk619;					// 619
	UInt8							unk61A;					// 61A	referenced during LoadForm (ie TESSpellList). bit 1 might mean refID to pointer conversion not done. For GECK means save in progress
	UInt8							unk61B;					// 61B
	UInt32							unk61C;					// 61C
	UInt8							unk620;					// 620
	UInt8							loading;				// 621	Init'd to 0 after loadForms
	UInt8							unk622;					// 622	referenced during loading of modules
	UInt8							unk623;					// 623
	void*							regionManager;			// 624 TESRegionManager*
	InventoryChanges::Data*			vendorContainer;		// 628
	UInt32							unk62C;					// 62C	
	UInt32							unk630;					// 630
	UInt32							unk634;					// 634
	UInt32							unk638;					// 638
};
assert(sizeof(MainDataHandler) == 0x63C);

class InputControl {
public:
	enum {
		kFlag_HasJoysticks =	1 << 0,
		kFlag_HasMouse =		1 << 1,
		kFlag_HasKeyboard =		1 << 2,
		kFlag_BackgroundMouse =	1 << 3,
	};
	
	enum {
		kMaxDevices = 8,
	};

	class Joystick {
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

	struct Unk1AF8 {
		UInt32	bufLen;
		UInt8	unk04[0x2C - 4];
	};

	UInt32					unk0000;							// 0000
	UInt32					flags;								// 0004
	IDirectInput8*			dinputInterface;					// 0008
	IDirectInputDevice8*	joystickInterfaces[kMaxDevices];	// 000C - format is c_dfDIJoystick
	IDirectInputDevice8*	keyboardInterface;					// 002C - format is c_dfDIKeyboard
	IDirectInputDevice8*	mouseInterface;						// 0030 - format is c_dfDIMouse2
	UInt32					unk0030[0x140];						// 0034
	Joystick				devices[kMaxDevices];				// 0534
	DIDEVCAPS				devCaps[kMaxDevices];				// 1754
	JoystickObjectsInfo		devInfo[kMaxDevices];				// 18B4
	UInt32					numJoysticks;						// 18F4
	UInt8					CurrentKeyState[0x100];				// 18F8
	UInt8					PreviousKeyState[0x100];			// 19F8
	Unk1AF8					unk1AF8;							// 1AF8
	DIMOUSESTATE2			CurrentMouseState;					// 1B24
	DIMOUSESTATE2			PreviousMouseState;					// 1B38
	UInt32					oldMouseButtonSwap;					// 1B4C - state of SwapMouseButton when program launched
	UInt32					unk1B50;							// 1B50
	UInt32					oldDoubleClickTime;					// 1B54
	UInt32					unk1B54[(0x1B90 - 0x1B54) >> 2];	// 1B58
	UInt8					KeyboardInputControls[28];			// 1B94
	UInt8					MouseInputControls[28];				// 1BB0
	UInt8					JoystickInputControls[28];			// 1BCC
	UInt32					unk1BE4[(0x1C00 - 0x1BE4) >> 2];	// 1BE4
};
assert(sizeof(InputControl) == 0x1C04);

class BSAudioManager {
public:
	enum Volumes {
		kMaster = 0,
		kFoot,
		kVoice,
		kEffects,
		kMusic,
		kRadio,
		kVATSCamera,
	};

	void**						_vtbl;					// 000
	UInt32                      unk004[10];				// 004
	void*						unk02C;					// 02C
	float                       flt030;					// 030
	UInt32                      unk034[2];				// 034
	void*						unk03C;					// 03C
	UInt32                      unk040[5];				// 040
	NiTMap<UInt32, BSGameSound>	playingSounds;			// 054
	NiTMap<UInt32, BSSoundInfo> playingSoundInfos1;		// 064
	NiTMap<UInt32, BSSoundInfo> playingSoundInfos2;		// 074
	NiTMap<UInt32, NiAVObject>  soundPlayingObjects;	// 084
	TList<BSGameSound>			gameSounds;				// 094
	UInt32                      unk09C;					// 09C
	UInt32                      unk0A0;					// 0A0
	UInt32                      unk0A4;					// 0A4
	UInt32                      unk0A8;					// 0A8
	_RTL_CRITICAL_SECTION		criticalSectionAC;
	_RTL_CRITICAL_SECTION		criticalSectionC4;
	_RTL_CRITICAL_SECTION		criticalSectionDC;
	_RTL_CRITICAL_SECTION		criticalSectionF4;
	_RTL_CRITICAL_SECTION		criticalSection10C;
	UInt32						unk124;
	UInt32						unk128;
	UInt32						unk12C;
	UInt32						time130;
	UInt8						byte134;
	UInt8						byte135;
	UInt8						pad136[2];
	UInt32						threadID;
	void*						audioMgrThread;			// 13C BSAudioManagerThread*
	float                       volumes[12];			// 140
	UInt32                      unk170[4];				// 170
	UInt32                      nextMapKey;				// 180
	UInt8						ignoreTimescale;
	UInt8						byte185;
	UInt8						byte186;
	UInt8						byte187;
};
assert(sizeof(BSAudioManager) == 0x188);

class SoundControl { // BSWin32Audio
public:

	struct SoundData {
		UInt32			Unk00;
		UInt8			Unk04;
		UInt32			Unk08;
	};

	void					Play(TESSound* Sound) { SoundData Data; SoundData DataB; ThisCall(0x00AD73B0, this, &Data, Sound->refID, 0x101); ThisCall(0x00418900, &DataB, &Data); ThisCall(0x00AD8830, &DataB, 0); }

	void**					_vtbl;						// 000
	UInt8					IsInitialized;				// 004
	UInt8					IsInitialized2;
	UInt8					pad004[2];
	UInt32					unk008;						// 008
	UInt32					unk00C;						// 00C
	void*					AudioListener;				// 010 BSWin32AudioListener*
	UInt32					unk014[9];					// 014
	IDirectSound8*			dsoundInterface;			// 038
	IDirectSoundBuffer8*	primaryBufferInterface;		// 03C
	DSCAPS					soundCaps;					// 040
	UInt32					unkA0;						// 0A0
};
assert(sizeof(SoundControl) == 0x0A4);

class Main {
public:
	InputControl*	GetInputControl() { return *(InputControl**)0x011F35CC; }
	bool			OnKeyDown(UInt16 KeyCode) { InputControl* input = GetInputControl(); if (KeyCode >= 256) return OnMouseDown(KeyCode - 256); if (KeyCode != 255 && input->CurrentKeyState[KeyCode] && !input->PreviousKeyState[KeyCode]) return true; return false; }
	bool			OnKeyPressed(UInt16 KeyCode) { InputControl* input = GetInputControl(); if (KeyCode >= 256) return OnMousePressed(KeyCode - 256); if (KeyCode != 255 && input->CurrentKeyState[KeyCode] && input->PreviousKeyState[KeyCode]) return true; return false; }
	bool			OnKeyUp(UInt16 KeyCode) { InputControl* input = GetInputControl(); if (KeyCode >= 256) return OnMouseUp(KeyCode - 256); if (KeyCode != 255 && !input->CurrentKeyState[KeyCode] && input->PreviousKeyState[KeyCode]) return true; return false; }
	bool			OnMouseDown(UInt8 ButtonIndex) { InputControl* input = GetInputControl(); if (ButtonIndex != 255 && input->CurrentMouseState.rgbButtons[ButtonIndex] && !input->PreviousMouseState.rgbButtons[ButtonIndex]) return true; return false; }
	bool			OnMousePressed(UInt8 ButtonIndex) { InputControl* input = GetInputControl(); if (ButtonIndex != 255 && input->CurrentMouseState.rgbButtons[ButtonIndex] && input->PreviousMouseState.rgbButtons[ButtonIndex]) return true; return false; }
	bool			OnMouseUp(UInt8 ButtonIndex) { InputControl* input = GetInputControl(); if (ButtonIndex != 255 && !input->CurrentMouseState.rgbButtons[ButtonIndex] && input->PreviousMouseState.rgbButtons[ButtonIndex]) return true; return false; }
	bool			OnControlDown(UInt16 ControlID) { InputControl* input = GetInputControl(); return OnKeyDown(input->KeyboardInputControls[ControlID]) + OnMouseDown(input->MouseInputControls[ControlID]); }
	bool			OnControlPressed(UInt16 ControlID) { InputControl* input = GetInputControl(); return OnKeyPressed(input->KeyboardInputControls[ControlID]) + OnMousePressed(input->MouseInputControls[ControlID]); }
	bool			OnControlUp(UInt16 ControlID) { InputControl* input = GetInputControl(); return OnKeyUp(input->KeyboardInputControls[ControlID]) + OnMouseUp(input->MouseInputControls[ControlID]); }
	void			SetControlState(UInt8 ControlID, UInt8 CurrentState, UInt8 PreviousState) {
						InputControl* input = GetInputControl();
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
	SoundControl*	GetSound() { return *(SoundControl**)0x011F6D98; }
	void			PurgeModels() {}

	UInt8			unk00;				// 00
	UInt8			quitGame;			// 01	// The seven are initialized to 0, this one is set by QQQ
	UInt8			exitToMainMenu;		// 02
	UInt8			unk03;				// 03
	UInt8			unk04;				// 04
	UInt8			unk05;				// 05
	UInt8			FlyCam;				// 06
	UInt8			disableAI;			// 07
	HWND			window;				// 08
	HINSTANCE		procInstance;		// 0C
	UInt32			mainThreadID;		// 10
	HANDLE			mainThreadHandle;	// 14
	void*			unk18;				// 18 ScrapHeapManager::Buffer*
	UInt32			unk1C;				// 1C
	UInt32			unk20;				// 20
	UInt32			unk24;				// 24
	UInt32			unk28[24];			// 28
	void*			accumulator0;		// 88 BSShaderAccumulator*
	void*			accumulator1;		// 8C BSShaderAccumulator*
	void*			accumulator2;		// 90 BSShaderAccumulator*
	void*			accumulator3;		// 94 BSShaderAccumulator*
	void*			accumulator4;		// 98 BSShaderAccumulator*
	UInt32			unk9C;				// 9C
	NiCamera*		camera;				// A0
};
assert(sizeof(Main) == 0x0A4);

class MenuInterfaceManager {
public:
	bool					IsActive(UInt32 MenuType) { if (MenuType == Menu::MenuType::kMenuType_Main) return (menuStack[0] == Menu::MenuType::kMenuType_Loading && menuStack[1] == Menu::MenuType::kMenuType_Start) || (menuStack[0] == Menu::MenuType::kMenuType_Console && menuStack[1] == Menu::MenuType::kMenuType_Loading && menuStack[2] == Menu::MenuType::kMenuType_Start); return menuStack[0] == MenuType; }
	bool					ShowMessageBox(const char* Message, void* Callback, const char* Button0, const char* Button1 = NULL, const char* Button2 = NULL, const char* Button3 = NULL, const char* Button4 = NULL, const char* Button5 = NULL, const char* Button6 = NULL, const char* Button7 = NULL, const char* Button8 = NULL, const char* Button9 = NULL) { bool (__cdecl* ShowUIMessageBox)(const char*, UInt32, UInt32, void*, UInt32, UInt32, float, float, const char*, ...) = (bool (__cdecl*)(const char*, UInt32, UInt32, void*, UInt32, UInt32, float, float, const char*, ...))0x00703E80; return ShowUIMessageBox(Message, 0, 0, Callback, 0, 23, 0.0f, 0.0f, Button0, Button1, Button2, Button3, Button4, Button5, Button6, Button7, Button8, Button9, NULL); }
	void					ShowMessage(const char* Message) { bool (__cdecl* ShowUIMessage)(const char*, UInt32, const char*, const char*, float, bool) = (bool (__cdecl*)(const char*, UInt32, const char*, const char*, float, bool))0x007052F0; ShowUIMessage(Message, 0, NULL, NULL, 2.0f, 0); }
	UInt8					GetMessageBoxButton() { UInt8 B = msgBoxButton; msgBoxButton = -1; return B; }
	void					SetCrosshair(bool Enabled) { HUDMainMenu **HMainMenu = (HUDMainMenu**)0x11D96C0; (*HMainMenu)->crosshair->SetFloat(0x0FA3, (float)Enabled); }

	UInt32					flags;				// 000
	SceneGraph*				MenuRoot;			// 004
	SceneGraph*				MenuRoot3D;			// 008
	UInt8					currentMode;		// 00C	1 = GameMode; 2 = MenuMode
	UInt8					pad00D[3];			// 00D
	UInt32					unk010;				// 010
	UInt32					unk014;				// 014
	UInt32					pickLength;			// 018
	UInt32					unk01C[3];			// 01C
	TileImage*				cursor;				// 028
	float					unk02C;				// 02C
	float					unk030;				// 030
	float					unk034;				// 034
	float					cursorX;			// 038
	float					unk03C;				// 03C
	float					cursorY;			// 040
	UInt32					unk044[11];			// 044
	TList<TESObjectREFR>	selectableRefs;		// 070
	UInt32					unk078;				// 078
	bool					debugText;			// 07C
	UInt8					byte07D;			// 07D
	UInt8					byte07E;			// 07E
	UInt8					byte07F;			// 07F
	NiNode*					niNode080;			// 080
	NiNode*					niNode084;			// 084
	UInt32					unk088;				// 088
	void*					shaderAccum08C;		// 08C BSShaderAccumulator*
	void*					shaderAccum090;		// 090 BSShaderAccumulator*
	void*					shadowScene094;		// 094 ShadowSceneNode*
	void*					shadowScene098;		// 098 ShadowSceneNode*
	Tile*					menuRoot;			// 09C
	Tile*					unk0A0;				// 0A0 seen "Strings"
	NiNode*					unk0A4;				// 0A4 saw Tile? seen NiNode
	UInt32					unk0A8;				// 0A8
	NiObject*				unk0AC;				// 0AC seen NiAlphaProperty
	UInt32					unk0B0[3];			// 0B0
	Tile*					activeTileAlt;		// 0BC
	UInt32					unk0C0[3];			// 0B0
	Tile*					activeTile;			// 0CC
	Menu*					activeMenu;			// 0D0
	Tile*					tile0D4;			// 0D4
	Menu*					menu0D8;			// 0D8
	UInt32					unk0DC[2];			// 0DC
	UInt8					msgBoxButton;		// 0E4 -1 if no button pressed
	UInt8					pad0E5[3];			// 0E5
	UInt32					unk0E8;				// 0E8
	UInt32					unk0EC;				// 0EC
	TESObjectREFR*			debugSelection;		// 0F0	compared to activated object during Activate
	UInt32					unk0F4;				// 0F4
	UInt32					unk0F8;				// 0F8
	TESObjectREFR*			crosshairRef;		// 0FC
	UInt32					unk100[4];			// 100
	UInt8					byte110;			// 110
	UInt8					pad111[3];			// 111
	UInt32					menuStack[10];		// 114
	void*					ptr13C;				// 13C	Points to a struct, possibly. First member is *bhkSimpleShapePhantom
	UInt32					unk140[5];			// 140
	UInt32					unk154;				// 154
	UInt32					unk158;				// 158
	UInt32					unk15C;				// 15C
	UInt32					unk160;				// 160
	UInt32					unk164;				// 164
	UInt32					unk168;				// 168
	void*					unk16C;				// 16C
	UInt32					unk170;				// 170
	void*					pipboyManager;		// 174 FOPipboyManager*
	UInt32					unk178;				// 178
	NiTArray<void>			array17C;			// 17C NiTPrimitiveArray@PackedMenu@BGSMenuPacker
	UInt32					unk18C[130];		// 18C
	NiObject				*unk394;			// 394 seen NiSourceTexture
	UInt32					unk398[47];			// 398
	NiTArray<void>			array454;			// 454 NiTPrimitiveArray@TextureType@BSTextureManager
	NiTArray<void>			array464;			// 464 NiTPrimitiveArray@FilterMode@NiTexturingProperty
	UInt32					unk474[18];			// 474
	UInt32					unk4BC;				// 4BC
	UInt32					unk4C0[48];			// 4C0
};
assert(sizeof(MenuInterfaceManager) == 0x580);

class TimeGlobals {
public:
	TESGlobal* GameYear;		// 00
	TESGlobal* GameMonth;		// 04
	TESGlobal* GameDay;			// 08
	TESGlobal* GameHour;		// 0C
	TESGlobal* GameDaysPassed;	// 10
	TESGlobal* TimeScale;		// 14

	static float GetGameTime() { TimeGlobals* Globals = (TimeGlobals*)0x011DE7B8; return Globals->GameHour->data * 60.0f * 60.0f; }
	static TimeGlobals* Get() { return (TimeGlobals*)0x11DE7B8; }
};
assert(sizeof(TimeGlobals) == 0x018); // Static class, size could be larger

class QueuedModelLoader {
public:
	UInt32	Unk000[7]; // LockFreeMaps for models
};
assert(sizeof(QueuedModelLoader) == 0x01C);

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

namespace Pointers {
	namespace Generic {
		static float*			  MPF					= (float*)0x00000000;
		static BSRenderedTexture* MenuRenderedTexture	= *(BSRenderedTexture**)0x011DED3C;
		static BSRenderedTexture* BlurredReflection	= *(BSRenderedTexture**)0x011C7AD4;
        
		static NiPoint3*		  CameraWorldTranslate	= (NiPoint3*)0x011F474C;
		static NiPoint3*		  CameraLocation		= (NiPoint3*)0x011F426C;
		static NiNode**			  DetectorWindowNode	= (NiNode**)0x011FA008;
	}
	namespace Functions {
		static void* (__cdecl* MemoryAlloc)(size_t) = (void* (__cdecl*)(size_t))0x00AA13E0;
        static void* (__cdecl* FormMemoryAlloc)(size_t) = (void* (__cdecl*)(size_t))0x00401000;
        static void* (__cdecl* FormMemoryDeAlloc)(void*) = (void* (__cdecl*)(void*))0x00401030;

		static bool  (__cdecl* ExtractArgs)(CommandParam*, void*, UInt32*, TESObjectREFR*, TESObjectREFR*, Script*, ScriptEventList*, ...) = (bool (__cdecl*)(CommandParam*, void*, UInt32*, TESObjectREFR*, TESObjectREFR*, Script*, ScriptEventList*, ...))0x005ACCB0;
		static void  (* PrintToConsole)(const char*, ...) = (void (*)(const char*, ...))0x00703C00;
		static char* (__cdecl* GetPassDescription)(UInt32) = (char* (__cdecl*)(UInt32))0x00B4F9D0;
	}
	namespace VirtualTables {
		static const void* NiNode			= (void*)0x0109B5AC;
		static const void* BSFadeNode		= (void*)0x010A8F90;
		static const void* BSFaceGenNiNode	= (void*)0x010660DC;
		static const void* BSTreeNode		= (void*)0x010668E4;
		static const void* NiTriShape		= (void*)0x0109D454;
		static const void* NiTriStrips		= (void*)0x0109CD44;
        static const void* BSDismemberSkinInstance = (void*) 0x01069A84;
		static const void* BSMultiBoundNode   = (void*)0x010C1D14;
		static const void* NiParticleNode     = (void*)0x010BD44C;

	}
	namespace Settings {
		static UInt32* MinGrassSize				= (UInt32*)0x00000000;
		static float*  GrassStartFadeDistance	= (float*)0x00000000;
		static float*  GrassEndDistance			= (float*)0x00000000;
		static float*  GrassWindMagnitudeMin	= (float*)0x00000000;
		static float*  GrassWindMagnitudeMax	= (float*)0x00000000;
		static float*  TexturePctThreshold		= (float*)0x00000000;
	}
	namespace ShaderParams {
		static float* GrassWindMagnitudeMax	= (float*)0x00000000;
		static float* GrassWindMagnitudeMin	= (float*)0x00000000;
		static UInt8* WaterHighResolution	= (UInt8*)0x01200059;
		static float* RockParams			= (float*)0x01200658;
		static float* RustleParams			= (float*)0x01200668;
		static float* WindMatrixes			= (float*)0x01200688;
	}
}
