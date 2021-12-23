#pragma once
#define hkFactor 0.1428767293691635

class hkPackedNiTriStripsData;
class hkCollidable;
class hkRayHitCollector;
class hkBroadPhaseAabbCache;

class bhkCharacterController;
class bhkCharacterProxy;

__declspec(align(16)) class hkVector4 {
public:
	float	x;
	float	y;
	float	z;
	float	w;
};
assert(sizeof(hkVector4) == 0x010);

class hkQuaternion {
public:
	hkVector4	vec;
};
assert(sizeof(hkQuaternion) == 0x010);

class hkBaseObject {
public:
	virtual void Destructor(bool FreeThis);
};
assert(sizeof(hkBaseObject) == 0x004);

class hkRefObject : public hkBaseObject {
public:
	UInt16		sizeAndFlags;	// 04
	UInt16		refCount;		// 06
};
assert(sizeof(hkRefObject) == 0x008);

class bhkRefObject : public NiObject {
public:
	virtual void	SetObject(hkRefObject* hkObject);
	virtual void	Unk_14();

	hkRefObject*	hkObject;	// 008
};
assert(sizeof(bhkRefObject) == 0x00C);

class bhkSerializable : public bhkRefObject {
public:
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

	void*			hkData;		// 00C
};
assert(sizeof(bhkSerializable) == 0x010);

class bhkWorldObject : public bhkSerializable {
public:
	virtual void	Unk_20();
	virtual void	Unk_21();
	virtual NiNode*	CreateNiGeometry(NiNode* Node);
};
assert(sizeof(bhkWorldObject) == 0x010);

class bhkRigidBody : public bhkWorldObject {
public:
	UInt32			unk010;		// 010
	UInt32			unk014;		// 014
	UInt32			unk018;		// 018
};
assert(sizeof(bhkRigidBody) == 0x1C);

class bhkRigidBodyT : public bhkRigidBody {
public:
	UInt32			pad01C;		// 01C
	hkQuaternion	localRot;	// 020
	hkVector4		localPos;	// 030
	UInt32			unk040;		// 040
	UInt32			unk044;		// 044
	UInt32			unk048;		// 048
	UInt32			unk04C;		// 04C
};
assert(sizeof(bhkRigidBodyT) == 0x50);

class bhkShape : public bhkSerializable {
public:
	virtual void	Unk_20();
	virtual void	Unk_21();
	virtual void	Unk_22();
	virtual void	Unk_23();
	virtual void	CreateNiGeometry(NiNode* Node);
	virtual void	Unk_25();
	virtual void	AddMaterialProperty(NiAVObject* Object);

	enum {
		kMaterial_Stone = 0,
		kMaterial_Cloth,
		kMaterial_Dirt,
		kMaterial_Glass,
		kMaterial_Grass,
		kMaterial_Metal,
		kMaterial_Organic,
		kMaterial_Skin,
		kMaterial_Water,
		kMaterial_Wood,
		kMaterial_HeavyStone,
		kMaterial_HeavyMetal,
		kMaterial_HeavyWood,
		kMaterial_Chain,
		kMaterial_Snow,
		kMaterial_StoneStairs,
		kMaterial_ClothStairs,
		kMaterial_DirtStairs,
		kMaterial_GlassStairs,
		kMaterial_GrassStairs,
		kMaterial_MetalStairs,
		kMaterial_OrganicStairs,
		kMaterial_SkinStairs,
		kMaterial_WaterStairs,
		kMaterial_WoodStairs,
		kMaterial_HeavyStoneStairs,
		kMaterial_HeavyMetalStairs,
		kMaterial_HeavyWoodStairs,
		kMaterial_ChainStairs,
		kMaterial_SnowStairs,
		kMaterial_Elevator,
		kMaterial_Default,
	};

	UInt32			material;	// 010
};
assert(sizeof(bhkShape) == 0x14);

class bhkPackedNiTriStripsShape : public bhkShape {};
assert(sizeof(bhkPackedNiTriStripsShape) == 0x14);

class NiCollisionObject : public NiObject {
public:
	NiAVObject*		SceneObject;	// 008
};
assert(sizeof(NiCollisionObject) == 0x0C);

class bhkCollisionObject : public NiCollisionObject {
public:
	enum {
		kFlag_Active	= 1 << 0,
		kFlag_Reset		= 1 << 1,
		kFlag_Notify	= 1 << 2,
		kFlag_SetLocal	= 1 << 3,
	};

	UInt16				flags;			// 00C
	UInt8				pad00E[2];		// 00E
	bhkRigidBody*		bRigidBody;		// 010
};
assert(sizeof(bhkCollisionObject) == 0x14);

class bhkCollisionObjectEx : public bhkCollisionObject {
public:
	NiNode*			GeoNode;	// 014
};
assert(sizeof(bhkCollisionObjectEx) == 0x18);

class hkWorldRayCastInput {
public:
	hkVector4	From;							// 00
	hkVector4	To;								// 10
	UInt8		EnableShapeCollectionFilter;	// 20
	UInt8		pad20[3];
	UInt32		FilterInfo;						// 24
	UInt32		pad28[2];
};
assert(sizeof(hkWorldRayCastInput) == 0x30);

class hkShapeRayCastOutput {
public:
	hkVector4	Normal;					// 00
	UInt32		ShapeKey;				// 10
	float		HitFraction;			// 14
	UInt32		pad18[2];
};
assert(sizeof(hkShapeRayCastOutput) == 0x20);

class hkWorldRayCastOutput : public hkShapeRayCastOutput {
public:
	hkCollidable*	RootCollidable;		// 20
	UInt32			pad24[3];
};
assert(sizeof(hkWorldRayCastOutput) == 0x30);

class bhkWorldRayCastData {
public:
	void		Init() { ThisCall(0x004F5EA0, this); }
	void		SetFrom(NiPoint3* From) { WorldRayCastInput.From.x = From->x * hkFactor; WorldRayCastInput.From.y = From->y * hkFactor; WorldRayCastInput.From.z = From->z * hkFactor; }
	void		SetTo(NiPoint3* To) { WorldRayCastInput.To.x = To->x * hkFactor; WorldRayCastInput.To.y = To->y * hkFactor; WorldRayCastInput.To.z = To->z * hkFactor; }

	hkWorldRayCastInput		WorldRayCastInput;		// 00
	hkWorldRayCastOutput	WorldRayCastOutput;		// 30
	hkVector4				unk60;					// 60
	hkBroadPhaseAabbCache*	BroadPhaseAabbCache;	// 70
	hkRayHitCollector*		RayHitCollector1;		// 74
	hkRayHitCollector*		RayHitCollector2;		// 78
	UInt32					pad7C;
};
assert(sizeof(bhkWorldRayCastData) == 0x80);

class hkWorld : public hkRefObject {
public:
	bool		CastRay(bhkWorldRayCastData* WorldRayCastData) { ThisCall(0x00898ED0, this, &WorldRayCastData->WorldRayCastInput, &WorldRayCastData->WorldRayCastOutput); return WorldRayCastData->WorldRayCastOutput.RootCollidable != NULL; }

	void*		simulation;				// 008
	float		unk00C;					// 00C
	hkVector4	unk020;					// 010
	hkVector4	gravity;				// 020
	// More...
};
assert(sizeof(hkWorld) == 0x030);

class hkShape : public hkRefObject {
public:
	bhkRefObject*		bRefObject;		// 008
};
assert(sizeof(hkShape) == 0x00C);

class hkPackedNiTriStripsShape : public hkShape {
public:
	UInt32						unk0C;					// 00C
	hkPackedNiTriStripsData*	PackedNiTriStripsData;	// 010
};
assert(sizeof(hkPackedNiTriStripsShape) == 0x14);

class hkScaledMoppBvTreeShape : public hkShape {
public:
	hkPackedNiTriStripsShape*	PackedNiTriStripsShape;		// 00C
};
assert(sizeof(hkScaledMoppBvTreeShape) == 0x010);

class hkRigidBody : public hkRefObject {
public:
	hkWorld*			World;			// 008
	bhkRigidBody*		bRigidBody;		// 00C
	UInt32				unk010;			// 010
	hkShape*			Shape;			// 014
	UInt32				unk018;
	hkBaseObject*		unk01C;
	UInt32				unk020;
	UInt32				unk024;
	UInt32				unk028;
	UInt32				unk02C;
	UInt32				unk030;
	UInt32				unk034;
	UInt32				unk038;
	UInt32				unk03C;
	UInt32				unk040;
	UInt32				unk044;
	UInt32				unk048;
	UInt32				unk04C;
	hkBaseObject*		unk050;
	UInt32				unk054;
	UInt8				unk058;			// 058
	UInt8				pad058[3];
	UInt32				unk05C;			// 05C
	UInt32				unk060;			// 060
	UInt32				unk064;
	UInt32				unk068;
	UInt32				unk06C;
	UInt32				unk070;
	UInt32				unk074;
	UInt32				unk078;
	UInt32				unk07C;
	UInt32				unk080;
	UInt32				unk084;
	UInt32				unk088;
	UInt16				unk08C;
	UInt16				unk08E;			// 08E
	UInt32				unk090;
};
assert(sizeof(hkRigidBody) == 0x94);