#pragma once

class NiNode;
class NiPick;
class NiTextKeyExtraData;
class NiFormArray;
class NiStringPalette;
class NiStream;
class NiTimeController;
class NiPropertyState;
class NiDynamicEffectState;
class NiProperty;
class NiFogProperty;
class NiAlphaProperty;
class NiMaterialProperty;
class NiTexturingProperty;
class NiCullingProcess;
class NiDynamicEffect;
class NiControllerManager;
class NiVisibleArray;
class NiAdditionalGeometryData;
class NiGeometryGroup;
class NiRenderedCubeMap;
class NiTexture;
class NiGeometry;
class NiTriBasedGeom;
class NiTriShape;
class NiTriStrips;
class NiPixelData;
class NiParticles;
class NiObjectGroup;
class NiLines;
class NiSwitchNode;
class NiGeometryGroupManager;
class NiScreenElements;
class NiSourceCubeMap;
class NiRenderer;
class Ni2DBuffer;
class NiD3DRenderStateGroup;
class NiD3DShaderProgram;
class NiD3DShader;
class NiDX9LightManager;
class NiDX9VertexBufferManager;
class NiDX9ShaderConstantManager;
class NiDX9IndexBufferManager;
class NiDX9TextureManager;
class NiDX9RenderedTextureData;
class NiDX9RenderedCubeMapData;
class NiDX9DynamicTextureData;
class NiDX9AdapterDesc;
class NiDX9DeviceDesc;
class NiDX9Renderer;
class NiDX9RenderState;
class NiDX92DBufferData;
class NiDX9ShaderDeclaration;

class ShadowSceneLight;
class AnimSequenceBase;

class TESObjectREFR;

class bhkCollisionObject;

struct NiRTTI {
	const char* name;
	NiRTTI*		parent;
};
assert(sizeof(NiRTTI) == 0x008);

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

class NiPoint2 {
public:
	float	x;
	float	y;
};
assert(sizeof(NiPoint2) == 0x008);

class NiPoint3 {
public:
	float NiPoint3::operator * (const NiPoint3 pt) const { return x * pt.x + y * pt.y + z * pt.z; }

	void GetLookAt(NiPoint3* LookAt, NiPoint3* Rotation) {
		float x, y, z, r;
		
		x = this->x - LookAt->x;
		y = this->y - LookAt->y;
		z = this->z - LookAt->z;
		r = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
		Rotation->x = D3DXToDegree(atan2(y, x)) + 90.0f;
		Rotation->y = D3DXToDegree(acos(z / r)) - 90.0f;
		Rotation->z = 0;
	}

	float x;
	float y;
	float z;
};
assert(sizeof(NiPoint3) == 0x00C);

class NiVector4 {
public:
	void Normalize() {
		float len = sqrt((x * x) + (y * y) + (z * z));
		if (len > 0.000001f) {
			x = x / len;
			y = y / len;
			z = z / len;
		}
		else {
			x = 0.0f;
			y = 0.0f;
			z = 1.0f;
		}
	}

	float x;
	float y;
	float z;
	float w;
};
assert(sizeof(NiVector4) == 0x010);

class NiMatrix33 {
public:
	NiPoint3 NiMatrix33::operator * (const NiPoint3 pt) const {
		return {
			data[0][0] * pt.x + data[0][1] * pt.y + data[0][2] * pt.z,
			data[1][0] * pt.x + data[1][1] * pt.y + data[1][2] * pt.z,
			data[2][0] * pt.x + data[2][1] * pt.y + data[2][2] * pt.z
		};
	}
	NiMatrix33 NiMatrix33::operator * (const NiMatrix33 mat) const {
		NiMatrix33 prd;

		prd.data[0][0] =
			data[0][0] * mat.data[0][0]+
			data[0][1] * mat.data[1][0]+
			data[0][2] * mat.data[2][0];
		prd.data[1][0] =
			data[1][0] * mat.data[0][0]+
			data[1][1] * mat.data[1][0]+
			data[1][2] * mat.data[2][0];
		prd.data[2][0] =
			data[2][0] * mat.data[0][0]+
			data[2][1] * mat.data[1][0]+
			data[2][2] * mat.data[2][0];
		prd.data[0][1] =
			data[0][0] * mat.data[0][1]+
			data[0][1] * mat.data[1][1]+
			data[0][2] * mat.data[2][1];
		prd.data[1][1] =
			data[1][0] * mat.data[0][1]+
			data[1][1] * mat.data[1][1]+
			data[1][2] * mat.data[2][1];
		prd.data[2][1] =
			data[2][0] * mat.data[0][1]+
			data[2][1] * mat.data[1][1]+
			data[2][2] * mat.data[2][1];
		prd.data[0][2] =
			data[0][0] * mat.data[0][2]+
			data[0][1] * mat.data[1][2]+
			data[0][2] * mat.data[2][2];
		prd.data[1][2] =
			data[1][0] * mat.data[0][2]+
			data[1][1] * mat.data[1][2]+
			data[1][2] * mat.data[2][2];
		prd.data[2][2] =
			data[2][0] * mat.data[0][2]+
			data[2][1] * mat.data[1][2]+
			data[2][2] * mat.data[2][2];
		return prd;
	}
	void GenerateRotationMatrixZXY(NiPoint3* v, bool degrees) {
		float a = v->x;
		float b = v->y;
		float c = v->z;

		if (degrees) { a = D3DXToRadian(a); b = D3DXToRadian(b); c = D3DXToRadian(c); }
		data[0][0] = cos(a) * cos(c) - sin(a) * sin(b) * sin(c);
		data[0][1] = -cos(b) * sin(a);
		data[0][2] = cos(a) * sin(c) + cos(c) * sin(a) * sin(b);
		data[1][0] = cos(c) * sin(a) + cos(a) * sin(b) * sin(c);
		data[1][1] = cos(a) * cos(b);
		data[1][2] = sin(a) * sin(c) - cos(a) * cos(c) * sin(b);
		data[2][0] = -cos(b) * sin(c);
		data[2][1] = sin(b);
		data[2][2] = cos(b) * cos(c);
	}

	float data[3][3];
};
assert(sizeof(NiMatrix33) == 0x024);

class NiTransform {
public:
	NiMatrix33	rot;		// 00
	NiPoint3	pos;		// 24
	float		scale;		// 30
};
assert(sizeof(NiTransform) == 0x034);

class NiPlane {
public:
	enum {
		NoSide = 0,
		PositiveSide = 1,
		NegativeSide = 2,
	};

	NiPoint3	Normal;
	float		Constant;
};
assert(sizeof(NiPlane) == 0x010);

class NiBound {
public:
	UInt32 WhichSide(NiPlane* Plane) {
		float Distance = Plane->Normal * Center - Plane->Constant;
		UInt32 Result = NiPlane::NoSide;

		if (Distance <= -Radius) Result = NiPlane::NegativeSide; else if (Distance >= Radius) Result = NiPlane::PositiveSide;
		return Result;
	}

	NiPoint3	Center;
	float		Radius;
};
assert(sizeof(NiBound) == 0x010);

class NiFrustum {
public:
	float	Left;		// 00
	float	Right;		// 04
	float	Top;		// 08
	float	Bottom;		// 0C
	float	Near;		// 10
	float	Far;		// 14
	UInt8	Ortho;		// 18
	UInt8	pad18[3];
};
assert(sizeof(NiFrustum) == 0x01C);

class NiFrustumPlanes {
public:
	enum {
		NearPlane = 0,
		FarPlane = 1,
		LeftPlane = 2,
		RightPlane = 3,
		TopPlane = 4,
		BottomPlane = 5,
		MaxPlanes = 6
	};

	NiPlane	CullingPlanes[MaxPlanes];	// 00
	UInt32	ActivePlanes;				// 60
};
assert(sizeof(NiFrustumPlanes) == 0x064);

class NiViewport {
public:
	float	l;
	float	r;
	float	t;
	float	b;
};
assert(sizeof(NiViewport) == 0x010);

class NiColor {
public:
	float	r;
	float	g;
	float	b;
};
assert(sizeof(NiColor) == 0x00C);

class NiColorAlpha {
public:
	float	r;
	float	g;
	float	b;
	float	a;
};
assert(sizeof(NiColorAlpha) == 0x010);

template <typename T>
class NiTList {
public:
	struct Entry {
		Entry* next;
		Entry* prev;
		T* data;
	};

	virtual void	Destructor(bool free);
	virtual Entry*	AllocateEntry();
	virtual void	Free(Entry* entry);

	Entry*	start;		// 004
	Entry*	end;		// 008
	UInt32	numItems;	// 00C
};
assert(sizeof(NiTList<void>) == 0x010);

template <typename TKey, typename TData>
class NiTMap {
public:
	struct Entry {
		Entry*	next;
		TKey	key;
		TData*	data;
	};

	virtual UInt32	CalculateBucket(UInt32 key);
	virtual bool	CompareKey(UInt32 lhs, UInt32 rhs);
	virtual void	Fn_03(UInt32 arg0, UInt32 arg1, UInt32 arg2);	// assign to entry
	virtual void	Fn_04(UInt32 arg);
	virtual void	Fn_05();	// locked operations
	virtual void	Fn_06();	// locked operations

	UInt32			m_numBuckets;	// 4
	Entry**			m_buckets;		// 8
	UInt32			m_numItems;		// C
};
assert(sizeof(NiTMap<void, void>) == 0x010);

template <typename T>
class NiTArray {
public:

	UInt16			Add(T* Item) { return (UInt16)ThisCall(0x00AAF050, this, Item); }

	void** _vtbl;			// 00
	T*		data;			// 04
	UInt16	capacity;		// 08 - init'd to size of preallocation
	UInt16	end;			// 0A - index of the first free entry in the block of free entries at the end of the array (or numObjs if full)
	UInt16	numObjs;		// 0C - init'd to 0
	UInt16	growSize;		// 0E - init'd to size of preallocation
};
assert(sizeof(NiTArray<void>) == 0x010);

template <typename T>
class NiTLargeArray {
public:
	void**	_vtbl;			// 00
	T*		data;			// 04
	UInt32	capacity;		// 08 - init'd to size of preallocation
	UInt32	firstFreeEntry;	// 0C - index of the first free entry in the block of free entries at the end of the array (or numObjs if full)
	UInt32	numObjs;		// 10 - init'd to 0
	UInt32	growSize;		// 14 - init'd to size of preallocation
};
assert(sizeof(NiTLargeArray<void>) == 0x018);

class NiPixelFormat {
public:
	enum Format {
		kFormat_RGB = 0,
		kFormat_RGBA,
		kFormat_PAL,
		kFormat_PALALPHA,
		kFormat_DXT1,
		kFormat_DXT3,
		kFormat_DXT5,
		kFormat_RGB24NONINTERLEAVED,
		kFormat_BUMP,
		kFormat_BUMPLUMA,
		kFormat_RENDERERSPECIFIC,
		kFormat_ONE_CHANNEL,
		kFormat_TWO_CHANNEL,
		kFormat_THREE_CHANNEL,
		kFormat_FOUR_CHANNEL,
		kFormat_DEPTH_STENCIL,
		kFormat_UNKNOWN,
		kFormat_MAX
	};

	enum Component {
		kComp_RED = 0,
		kComp_GREEN,
		kComp_BLUE,
		kComp_ALPHA,
		kComp_COMPRESSED,
		kComp_OFFSET_U,
		kComp_OFFSET_V,
		kComp_OFFSET_W,
		kComp_OFFSET_Q,
		kComp_LUMA,
		kComp_HEIGHT,
		kComp_VECTOR_X,
		kComp_VECTOR_Y,
		kComp_VECTOR_Z,
		kComp_PADDING,
		kComp_INTENSITY,
		kComp_INDEX,
		kComp_DEPTH,
		kComp_STENCIL,
		kComp_EMPTY,
		kComp_MAX
	};

	enum Representation {
		kRep_NORM_INT = 0,
		kRep_HALF,
		kRep_FLOAT,
		kRep_INDEX,
		kRep_COMPRESSED,
		kRep_UNKNOWN,
		kRep_INT,
		kRep_MAX
	};

	enum Tiling {
		kTile_NONE = 0,
		kTile_XENON,
		kTile_MAX
	};

	struct NiComponentSpec {
		Component		eComponent;			// 0
		Representation	eRepresentation;	// 4
		UInt8			BitsPerComponent;	// 8
		UInt8			Signed;				// 9
		UInt8			padA[2];			// A
	};

	UInt8			BitsPerPixel;	// 00
	UInt8			SRGBSpace;		// 01
	UInt8			pad02[2];
	Format			eFormat;		// 04
	Tiling			eTiling;		// 08
	UInt32			RendererHint;	// 0C
	UInt32			ExtraData;		// 10
	NiComponentSpec	Components[4];	// 14
};
assert(sizeof(NiPixelFormat) == 0x044);

class NiRefObject {
public:
	virtual ~NiRefObject();
	virtual void	DeleteThis();	// calls virtual dtor

	void	IncRef();
	void	DecRef();
	bool	Release();

	volatile SInt32	m_uiRefCount;	// 04
};
assert(sizeof(NiRefObject) == 0x08);

class NiObject : public NiRefObject {
public:
	virtual NiRTTI*				 GetRTTI();
	virtual NiNode*				 GetAsNiNode();
	virtual NiSwitchNode*		 GetAsNiSwitchNode();
	virtual UInt32				 Unk_05();
	virtual UInt32				 Unk_06();
	virtual NiGeometry*			 GetAsNiGeometry();
	virtual NiTriBasedGeom*		 GetAsNiTriBasedGeom();
	virtual NiTriStrips*		 GetAsNiTriStrips();
	virtual NiTriShape*			 GetAsNiTriShape();
	virtual void*				 GetAsBSSegmentedTriShape(); // return BSSegmentedTriShape*
	virtual UInt32				 Unk_0C();
	virtual UInt32				 Unk_0D();
	virtual UInt32				 Unk_0E();
	virtual UInt32				 Unk_0F();
	virtual UInt32				 Unk_10();
	virtual UInt32				 Unk_11();
	virtual UInt32				 Unk_12();
	virtual NiObject*			 CreateClone(UInt32 cloner); //cloner: NiCloningProcess
	virtual void				 LoadBinary(NiStream* stream);
	virtual void				 LinkObject(NiStream* stream);
	virtual bool				 RegisterStreamables(NiStream* stream);
	virtual void				 SaveBinary(NiStream* stream);
	virtual bool				 IsEqual(NiObject* object);
	virtual void				 ProcessClone(void* cloner); //cloner: NiCloningProcess
	virtual void				 PostLinkObject(NiStream* stream);
	virtual bool				 StreamCanSkip();
	virtual const NiRTTI*		 GetStreamableRTTI();
	virtual UInt32				 GetBlockAllocationSize();
	virtual NiObjectGroup*		 GetGroup();
	virtual void				 SetGroup(NiObjectGroup* group);
	virtual UInt32				 Unk_20();
};
assert(sizeof(NiObject) == 0x08);

class NiExtraData : public NiObject {
public:
	char*	m_pcName;	// 08
};
assert(sizeof(NiExtraData) == 0x0C);

class NiObjectNET : public NiObject {
public:

	void				SetName(const char* Name) { 
		//BSFixedString S; S.Create(Name); ThisCall(0x00AB4020, this, &S); S.Dispose();
	}

	const char*			m_pcName;				// 08
	NiTimeController*	m_controller;			// 0C 
	NiExtraData**		m_extraData;			// 10 extra data
	UInt16				m_extraDataLen;			// 14 max valid entry
	UInt16				m_extraDataCapacity;	// 16 array len
};
assert(sizeof(NiObjectNET) == 0x18);

class NiAVObject : public NiObjectNET {
public:
	enum {
		kFlag_AppCulled						= 1 << 0,
		kFlag_SelectiveUpdate				= 1 << 1,
		kFlag_UpdatePropertyControllers		= 0x00000004,

		kFlag_SelectiveUpdateRigid			= 0x00000010,

		kFlag_OverrideSelectiveTransforms	= 0x00000080,
	};

	class ControllerUpdateContext {
	public:
		enum {
			kDirty =	1 << 0,
		};
		float	delta;
		UInt32	flags;
	};

	virtual void		UpdateControllers(ControllerUpdateContext* ctx);	// calls controller vtbl+0x8C
	virtual void		UpdateNodeBound(ControllerUpdateContext* ctx);
	virtual void		ApplyTransform(NiMatrix33* mtx, NiPoint3* translate, bool postTransform);
	virtual void		SetPropertyState(NiProperty* prop);
	virtual void		Unk_25(UInt32 arg0);
	virtual void		Unk_26(UInt32 arg0);
	virtual NiAVObject*	GetObjectByString(BSFixedString* name);
	virtual void		SetSelectiveUpdateFlags(bool* selectiveUpdate, bool selectiveUpdateTransforms, bool* rigid);
	virtual void		UpdateDownwardPass(ControllerUpdateContext* ctx, UInt32 unk1);
	virtual void		UpdateSelectedDownwardPass(ControllerUpdateContext* ctx, UInt32 unk1);
	virtual void		UpdateRigidDownwardPass(ControllerUpdateContext* ctx, UInt32 unk1);
	virtual void		UpdateWorldBound();
	virtual void		UpdateWorldData(ControllerUpdateContext* ctx);
	virtual void		UpdateNoControllers(ControllerUpdateContext* ctx);
	virtual void		UpdateDownwardPassTempParent(NiNode* parent, ControllerUpdateContext* ctx);
	virtual void		Unk_30();	// calls virtual function on parent
	virtual void		Unk_31(UInt32 arg0);
	virtual void		Unk_32(UInt32 arg0);

	NiAVObject* GetObjectByName(const char* Name) {
		BSFixedString Head;
		NiAVObject* r = NULL;

		Head.Create(Name);
		r = GetObjectByString(&Head);
		Head.Dispose();
		return r;
	}

	float GetDistance(NiPoint3* Point) {
		NiPoint3 v;

		v.x = this->m_worldTransform.pos.x - Point->x;
		v.y = this->m_worldTransform.pos.y - Point->y;
		v.z = this->m_worldTransform.pos.z - Point->z;
		return sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
	}

	NiNode*			m_parent;			// 18
	NiAVObject*		unk1C;				// 1C
	NiTransform		m_localTransform;	// 20
	NiTransform		m_worldTransform;	// 54
	float			unk88;				// 88
	float			unk8C;				// 8C
	float			unk90;				// 90
	float			unk94;				// 94
	UInt32			m_flags;			// 98 - bitfield
	float			unk9C;				// 9C
	UInt32			unkA0;				// A0
	UInt8			unkA4;				// A4
	UInt8			unkA5;				// A5 - bitfield
};
assert(sizeof(NiAVObject) == 0xA8);

class NiNode : public NiAVObject {
public:
	virtual void	AddObject(NiAVObject* nChild, bool firstAvail);
	virtual void	RemoveObject(NiAVObject** RemovedChild, NiAVObject* nChild);
	virtual void	Unk_35();
	virtual void	RemoveChild(NiAVObject* obj);
	virtual void	Unk_37();
	virtual void	RemoveAt(UInt32 i);
	virtual void	Unk_39();
	virtual void	Unk_3A();
	virtual void	UpdateUpwardPass();

	void					New(UInt16 Children) { ThisCall(0x00AAED00, this, Children); };

	NiTArray<NiAVObject*>	m_children;	// A8
};
assert(sizeof(NiNode) == 0xB8);

class NiCamera : public NiAVObject {
public:
	float			WorldToCam[4][4];	// A8
	NiFrustum		Frustum;			// E8
	float			MinNearPlaneDist;	// 104
	float			MaxFarNearRatio;	// 108
	NiViewport		ViewPort;			// 10C
	float			LODAdjust;			// 11C
};
assert(sizeof(NiCamera) == 0x120);

class SceneGraph : public NiNode {
public:
	void				UpdateParticleShaderFoV(float FoV) { void (__cdecl* UpdateParticleShaderFoVData)(float) = (void (__cdecl*)(float))0x00C71820; ThisCall(0x00B17960, this, FoV, 0, NULL, 0); UpdateParticleShaderFoVData(FoV); }
	void				SetNearDistance(float Distance) { float* SettingNearDistance = (float*)0x012C8D54; *SettingNearDistance = Distance; }

	NiCamera*			camera;					// B8
	UInt32				unkBC;					// BC
	NiCullingProcess*	cullingProcess;			// C0
	UInt32				IsMinFarPlaneDistance;	// C4 The farplane is set to 20480.0 when the flag is true. Probably used for interiors.
	float				cameraFOV;				// C8
	float				unkCC;					// CC
	UInt32				unkD0;					// D0
	UInt32				unkD4;					// D4
};
assert(sizeof(SceneGraph) == 0xD8);

class NiLight : public NiAVObject {
public:
	UInt32		unkA8[11];	// A8
};
assert(sizeof(NiLight) == 0xD4);

class NiPointLight : public NiLight {
public:
	float		unkD4;	// D4
	float		unkD8;	// D8
	float		unkDC;	// DC
};
assert(sizeof(NiPointLight) == 0xE0);

class NiVBChip {
public:
	UInt32					Index;      // 00
	UInt32					Unk04;		// 04 union { NiVBBlock* m_pkBlock; NiVBDynamicSet* m_pkDynamicSet; };
	IDirect3DVertexBuffer9* VB;			// 08
	UInt32					Offset;		// 0C
	UInt32					LockFlags;	// 10
	UInt32					Size;		// 14
	NiVBChip*				Next;		// 18
	NiVBChip*				Prev;		// 1C
};
assert(sizeof(NiVBChip) == 0x020);

class NiGeometryBufferData {
public:
	UInt32							Flags;					// 00
	NiGeometryGroup*				GeometryGroup;			// 04
	UInt32							FVF;					// 08
	IDirect3DVertexDeclaration9*	VertexDeclaration;		// 0C
	UInt32							unk10;					// 10
	UInt32							VertCount;				// 14
	UInt32							MaxVertCount;			// 18
	UInt32							StreamCount;			// 1C
	UInt32*							VertexStride;			// 20
	NiVBChip**						VBChip;					// 24
	UInt32							IndexCount;				// 28
	UInt32							IBSize;					// 2C
	IDirect3DIndexBuffer9*			IB;						// 30
	UInt32							BaseVertexIndex;		// 34
	D3DPRIMITIVETYPE				PrimitiveType;			// 38
	UInt32							TriCount;				// 3C
	UInt32							MaxTriCount;			// 40
	UInt32							NumArrays;				// 44
	UInt16*							ArrayLengths;			// 48
	UInt16*							IndexArray;				// 4C
};
assert(sizeof(NiGeometryBufferData) == 0x50);

class NiGeometryData : public NiObject {
public:
	enum Consistency {
		MUTABLE			 = 0x0000,
		STATIC			 = 0x4000,
		VOLATILE		 = 0x8000,
		CONSISTENCY_MASK = 0xF000,
	};

	UInt16						Vertices;			// 008
	UInt16						ID;					// 00A
	UInt16						DirtyFlags;			// 00C
	UInt16						DataFlags;			// 00E
	NiBound						Bound;				// 010
	NiPoint3*					Vertex;				// 020
	NiPoint3*					Normal;				// 024
	NiColorAlpha*				Color;				// 028
	UInt32						Texture;			// 02C NiPoint2*
	UInt32						Unk030;				// 030
	UInt32						Unk034;				// 034
	UInt32						Unk038;				// 038
	NiAdditionalGeometryData*	AdditionalGeoData;	// 03C
	NiGeometryBufferData*		BuffData;			// 040
	UInt8						KeepFlags;			// 044
	UInt8						CompressFlags;		// 045
	UInt8						hasGeoData;			// 046
	UInt8						pad47;				// 047
};
assert(sizeof(NiGeometryData) == 0x48);

class NiSkinPartition : public NiObject {
public:
	class Partition {
	public:
		UInt16*					pBones;			// 00
		float*					Weights;		// 04
		UInt16*					VertexMap;      // 08
		UInt8*					BonePalette;	// 0C
		UInt16*					TriList;		// 10
		UInt16*					StripLengths;	// 14
		UInt16					Vertices;		// 18
		UInt16					Triangles;		// 1A
		UInt16					Bones;			// 1C
		UInt16					Strips;			// 1E
		UInt16					BonesPerVertex; // 20
		UInt16					pad20;
		UInt32					Unk24;		// 24
	};

	UInt32		PartitionsCount;		// 08
	Partition*	Partitions;				// 0C
};
assert(sizeof(NiSkinPartition) == 0x10);

class NiSkinData : public NiObject {
public:
	class BoneVertData {
	public:
		UInt16	Verts;		// 00
		float	Weight;		// 04
	};

	class BoneData {
	public:
		NiTransform		SkinToBone;		// 00
		NiBound			Bound;			// 34
		BoneVertData*	BoneVertData;	// 44
		UInt16			Verts;			// 48
		UInt16			pad44;
	};

	NiSkinPartition*	SkinPartition;		// 08
	NiTransform			RootParentToSkin;	// 0C
	BoneData*			BoneData;			// 40
	UInt32				Bones;				// 44

};
assert(sizeof(NiSkinData) == 0x48);

class NiSkinInstance : public NiObject {
public:
	NiSkinData*			SkinData;				// 08
	NiSkinPartition*	SkinPartition;			// 0C
	NiAVObject*			RootParent;				// 10
	NiAVObject**		BoneObjects;			// 14
	NiTransform**		WorldTrasforms;			// 18
	UInt32				Bones;					// 1C
	UInt32				BoneRegisters;			// 20
	UInt32				Unk24;					// 24
	UInt32				Unk28;					// 28
	UInt32				Unk2C;					// 2C
	UInt32				Unk30;					// 30
	UInt32				Unk34;					// 34
};
assert(sizeof(NiSkinInstance) == 0x38);

class NiProperty : public NiObjectNET {
public:
	enum PropertyType {
		kType_Alpha,
		kType_Lighting,
	};
};
assert(sizeof(NiProperty) == 0x18);

class NiGeometry : public NiAVObject {
public:
	NiProperty*				GetProperty(NiProperty::PropertyType Type) { return propertyState; }

	NiProperty*				propertyState;		// 0A8
	NiProperty*				dynamicEffectState;	// 0AC
	NiGeometryData*			geomData;			// 0B0
	NiSkinInstance*			skinInstance;		// 0B4
};
assert(sizeof(NiGeometry) == 0x0B8);

class NiDX9TextureData : public NiObject {
public:
	NiTexture*				parent;		// 08
	UInt32					width;		// 0C
	UInt32					height;		// 10
	NiPixelFormat			format;		// 14
	UInt8					unk58;		// 58
	UInt8					unk59;		// 59
	UInt8					unk5A;		// 5A
	UInt8					unk5B;		// 5B
	UInt32					unk5C;		// 5C
	NiDX9Renderer*			renderer;	// 60
	IDirect3DBaseTexture9*	texture;	// 64
	UInt16					levels;		// 68
	UInt16					textureType;// 6A
	UInt32					unk6C;		// 6C
};
assert(sizeof(NiDX9TextureData) == 0x70);

class NiTexture : public NiObject {
public:
	virtual void	Unk_21();
	virtual void	Unk_22();
	virtual UInt32	GetWidth();
	virtual UInt32	GetHeight();
	virtual UInt32	GetByteSize();

	enum PixelLayout {
		kPixelLayout_Palettized8 = 0,
		kPixelLayout_HighColor16,
		kPixelLayout_TrueColor32,
		kPixelLayout_Compressed,
		kPixelLayout_Bumpmap,
		kPixelLayout_Palettized4,
		kPixelLayout_PixDefault,
		kPixelLayout_SingleColor8,
		kPixelLayout_SingleColor16,
		kPixelLayout_SingleColor32,
		kPixelLayout_DoubleColor32,
		kPixelLayout_DoubleColor64,
		kPixelLayout_FloatColor32,
		kPixelLayout_FloatColor64,
		kPixelLayout_FloatColor128,
		kPixelLayout_SingleColor4,
	};

	enum AlphaFormat {
		kAlpha_None = 0,
		kAlpha_Binary,	// 1bpp
		kAlpha_Smooth,	// 8bpp
		kAlpha_Default,
	};

	enum MipMapFlag {
		kMipMap_Disabled = 0,
		kMipMap_Enabled,
		kMipMap_Default,
	};

	struct FormatPrefs {
		PixelLayout pixelLayout;
		AlphaFormat alphaFormat;
		MipMapFlag	mipmapFormat;
	};

	FormatPrefs			formatPrefs;	// 008
	NiDX9TextureData*	rendererData;	// 014
	BSFixedString*		name;			// 018
	NiTexture*			nextTex;		// 01C
	NiTexture*			prevTex;		// 020
};
assert(sizeof(NiTexture) == 0x24);

class NiSourceTexture : public NiTexture {
public:
	virtual void LoadPixelDataFromFile();
	virtual void DestroyAppPixelData();
	virtual bool CreateRendererData();

	void*			persistentSrcRendererData;		// 24 NiPersistentSrcTextureRendererData*
	NiPixelData*	pixelData;						// 28
	UInt32			unk2C;							// 2C
	UInt8			flags;							// 30
};
assert(sizeof(NiSourceTexture) == 0x34);

class NiRenderedTexture : public NiTexture {
public:
	virtual Ni2DBuffer* GetBuffer();

	Ni2DBuffer* buffer;		// 24
	UInt32		unk28;		// 28
	UInt32		unk2C;		// 2C
	UInt8		unk30;		// 30
	UInt8		unk31;		// 31
	UInt8		pad32[2];	// 32
	UInt32		unk34;		// 34
	UInt32		unk38;		// 38
};
assert(sizeof(NiRenderedTexture) == 0x3C);

class NiD3DVertexShader {
public:
	UInt32					unk00;				// 00
	UInt32					unk04;				// 04
	UInt32					unk08;				// 08
	UInt32					unk0C;				// 0C
	UInt32					unk10;				// 10
	UInt32					unk14;				// 14
	UInt32					unk18;				// 18
	UInt32					unk1C;				// 1C
	IDirect3DVertexShader9* ShaderHandle;		// 20
	UInt32					unk24;				// 24
	UInt32					unk28;				// 28
	UInt32					Counter;			// 2C It seems sometimes this is not set as expected
	UInt16					StartRegister;		// 30
	UInt8					Vector4Count;		// 32
	UInt8					unk33;				// 33
};
assert(sizeof(NiD3DVertexShader) == 0x34);

class NiD3DPixelShader {
public:
	UInt32					unk00;				// 00
	UInt32					unk04;				// 04
	UInt32					unk08;				// 08
	UInt32					unk0C;				// 0C
	UInt32					unk10;				// 10
	UInt32					unk14;				// 14
	UInt32					unk18;				// 18
	UInt32					unk1C;				// 1C
	UInt32					unk20;				// 20
	UInt32					unk24;				// 24
	UInt32					unk28;				// 28
	UInt32					unk2C;				// 2C
	UInt32					unk30;				// 30
	UInt32					unk34;				// 34
	UInt32					unk38;				// 38
	UInt32					unk3C;				// 3C
	UInt32					unk40;				// 40
	UInt32					unk44;				// 44
	UInt32					unk48;				// 48
	UInt32					unk4C;				// 4C
	UInt32					unk50;				// 50
	UInt32					Counter;			// 54 It seems sometimes this is not set as expected
	IDirect3DPixelShader9*	ShaderHandle;		// 58
	void*					ShaderFunction;		// 5C Deallocated after the ShaderHandle creation
	UInt16					StartRegister;		// 60
	UInt8					Vector4Count;		// 62
	UInt8					unk63;				// 63
};
assert(sizeof(NiD3DPixelShader) == 0x64);

class BSShader : public NiRefObject {
public:
	enum ShaderType {
		GrassShader = 1,
		SkyShader = 2,
		WaterShader = 3,
		BloodSplatterShader = 4,
		UnknownShader = 5,
		LightingShader = 6,
		EffectShader = 7,
		UtilityShader = 8,
		DistantTreeShader = 9,
		ParticleShader = 10,
	};

	UInt32		unk08;		// 08
	ShaderType	shaderType; // 0C
	UInt32		unk10;		// 10
	UInt32		unk14;		// 14
	UInt32		unk18;		// 18
	UInt32		unk1C;		// 1C
	UInt32		unk20;		// 20
	UInt32		unk24;		// 24
	UInt32		unk28;		// 28
	UInt32		unk2C;		// 2C
	UInt32		unk30;		// 30
	UInt32		unk34;		// 34
	UInt32		unk38;		// 38
	UInt32		unk3C;		// 3C
	UInt32		unk40;		// 40
	UInt32		unk44;		// 44
	UInt32		unk48;		// 48
	UInt32		unk4C;		// 4C
	UInt32		unk50;		// 50
};
assert(sizeof(BSShader) == 0x54);

class WaterShader : public BSShader {
public:
	UInt32				Unk54;		// 54
	UInt32				Unk58;		// 58
	UInt32				Unk5C;		// 5C
	UInt32				Unk60;		// 60
	UInt32				Unk64;		// 64
	UInt32				Unk68;		// 68
};
assert(sizeof(WaterShader) == 0x6C);

class Ni2DBuffer : public NiObject {
public:
	UInt32				width;	// 008
	UInt32				height;	// 00C
	NiDX92DBufferData*	data;	// 010
};
assert(sizeof(Ni2DBuffer) == 0x014);

class NiDepthStencilBuffer : public Ni2DBuffer {};
assert(sizeof(NiDepthStencilBuffer) == 0x014);

class NiDX92DBufferData : public NiRefObject {
public:
	Ni2DBuffer*				ParentData;		// 08
	NiPixelFormat*			pixelFormat;	// 0C
	UInt32					unk10;			// 10
	IDirect3DSurface9*		Surface;		// 14
};
assert(sizeof(NiDX92DBufferData) == 0x18);

class NiRenderTargetGroup : public NiObject {
public:
	UInt32							unk08;						// 08
	Ni2DBuffer*						RenderTargets[4];			// 0C
	UInt32							numRenderTargets;			// 1C
	NiDepthStencilBuffer*			DepthStencilBuffer;			// 20
	void*							RenderData;					// 24
};
assert(sizeof(NiRenderTargetGroup) == 0x28);

class NiRenderer : public NiObject {
public:
	enum ClearFlags {
		kClear_BACKBUFFER = 0x1,
		kClear_STENCIL = 0x2,
		kClear_ZBUFFER = 0x4,
		kClear_NONE = 0,
		kClear_ALL = kClear_BACKBUFFER | kClear_STENCIL | kClear_ZBUFFER
	};

	void Clear(float* Rect, UInt32 Flags) { ThisCall(0x00CD5D00, this, Rect, Flags); }

};
assert(sizeof(NiRenderer) == 0x08);

class NiDX9Renderer : public NiRenderer {
public:

	void		SetSamplerState(DWORD Sampler, D3DSAMPLERSTATETYPE State, DWORD Value) { device->SetSamplerState(Sampler, State, Value); };

	UInt32								CriticalSection;			// 08
	UInt32								ThreadOwner;				// 0C
	UInt32								lockCount;					// 10
	UInt32								unk14;						// 14
	UInt32								unk18;						// 18
	UInt32								unk1C;						// 1C
	UInt32								unk20;						// 20
	UInt32								frameState;					// 24
	UInt32								unk28;						// 28
	UInt8								RenderTargetGroupActive;	// 2C
	UInt8								unk2D;						// 2D
	UInt8								pad2E[2];					// 2E
	UInt32								unk30;						// 30
	UInt32								unk34;						// 34
	IDirect3DDevice9*					device;						// 38
	D3DCAPS9							D3DCaps9;					// 3C
	HWND								WndDevice;					// 16C
	HWND								WndFocus;					// 170
	char								DriverDesc[512];			// 174
	UInt32								Adapter;					// 374
	UInt32								DevType;					// 378
	UInt32								BehaviorFlags;				// 37C
	UInt32								AdapterFormat;				// 380
	UInt8								unk384;						// 384
	UInt8								unk385;						// 385
	UInt8								pad386[2];					// 386
	UInt32								AdapterDesc;				// 388
	UInt32								DeviceDesc;					// 38C
	UInt32								Background;					// 390
	float								ZClear;						// 394
	UInt32								StencilClear;				// 398
	UInt32								RendFlags;					// 39C
	char								Behavior[32];				// 3A0
	NiTMap<void*,void*>					PrePackObjects;				// 3C0
	UInt32								unk3D0;						// 3D0
	UInt32								unk3D4;						// 3D4
	NiPoint3							CamRight;					// 3D8
	NiPoint3							CamUp;						// 3E4
	NiPoint3							ModelCamRight;				// 3F0
	NiPoint3							ModelCamUp;					// 3FC
	NiPoint3							unk408;						// 408
	UInt32								unk414;						// 414
	NiPoint3							unk418;						// 418
	UInt32								unk424;						// 424
	float								NearDepth;					// 428
	float								DepthRange;					// 42C
	D3DMATRIX							D3DIdentity;				// 430
	D3DVIEWPORT9						viewport;					// 470
	UInt32								HWBones;					// 488
	UInt32								MaxStreams;					// 48C
	UInt32								MaxPixelShaderVersion;		// 490
	UInt32								MaxVertexShaderVersion;		// 494
	UInt8								unk498;						// 498
	UInt8								pad499[3];					// 499
	UInt32								ResetCounter;				// 49C
	UInt8								DeviceLost;					// 4A0
	UInt8								pad4A1[3];					// 4A1
	NiPixelFormat*						TextureFormats[4][22];		// 4A4 [TEXUSE_NUM][TEX_NUM]
	NiPixelFormat*						DefaultTextureFormat[4];	// 604 [TEXUSE_NUM]
	NiPixelData*						DefaultTextureData[4];		// 614 [TEXUSE_NUM]
	UInt32								ReplacementDataFormat;		// 624
	NiRenderTargetGroup*				defaultRTGroup;					// 628
	NiRenderTargetGroup*				currentRTGroup;					// 62C
	NiRenderTargetGroup*				CurrOnscreenRenderTargetGroup;	// 630
	NiTMap<HWND, NiRenderTargetGroup*>	OnscreenRenderTargetGroups;		// 634 NiTPointerMap<HWND, NiRenderTargetGroupPtr>
	UInt32								MaxNumRenderTargets;			// 644
	bool								IndependentBitDepths;			// 648
	bool								MRTPostPixelShaderBlending;		// 649
	UInt8								pad64A[2];						// 64A
	UInt32								unk64C;							// 64C
	UInt32								unk650;							// 650
	UInt32								unk654;							// 654
	NiDX9VertexBufferManager*			vertexBufferManager;			// 658
	NiDX9IndexBufferManager*			indexBufferManager;				// 65C
	NiTMap<NiRenderedTexture*, void*>	RenderedTextures;				// 660 NiTPointerMap<NiRenderedTexture*, NiDX9RenderedTextureData*>
	NiTMap<NiRenderedCubeMap*, void*>	RenderedCubeMaps;				// 670 NiTPointerMap<NiRenderedCubeMap*, NiDX9RenderedCubeMapData*>
	UInt32								unk680;							// 680
	UInt32								unk684;							// 684
	UInt32								unk688;							// 688
	UInt32								unk68C;							// 68C
	D3DXMATRIXA16						worldMatrix;					// 690
	D3DXMATRIX							viewMatrix;						// 6D0
	D3DXMATRIX							projMatrix;						// 710
	D3DXMATRIX							unkMatrix;						// 750
	D3DXMATRIX							invViewMatrix;					// 790
	NiPoint2*							ScreenTextureVerts;				// 7D0
	NiColorAlpha*						ScreenTextureColors;			// 7D4
	NiPoint2*							ScreenTextureTexCoords;			// 7D8
	UInt16								sNumScreenTextureVerts;			// 7DC
	UInt16								pad7DE;
	UInt16*								ScreenTextureIndices;			// 7E0
	UInt32								NumScreenTextureIndices;		// 7E4
	UInt32								width;							// 7E8
	UInt32								height;							// 7EC
	UInt32								CreationUseFlags;				// 7F0
	HWND								CreationWndDevice;				// 7F4
	HWND								CreationWndFocus;				// 7F8
	UInt32								CreationAdapter;				// 7FC
	UInt32								CreationDesc;					// 800
	UInt32								CreationFBFormat;				// 804
	UInt32								CreationDSFormat;				// 808
	UInt32								CreationPresentationInterval;	// 80C
	UInt32								CreationSwapEffect;				// 810
	UInt32								CreationFBMode;					// 814
	UInt32								CreationBackBufferCount;		// 818
	UInt32								iCreationRefreshRate;			// 81C
	UInt32								unk820;							// 820
	UInt32								unk824;							// 824
	UInt32								unk828;							// 828
	UInt32								unk82C;							// 82C
	UInt32								unk830;							// 830
	UInt32								unk834;							// 834
	UInt32								unk838;							// 838
	UInt32								unk83C;							// 83C
	UInt32								unk840;							// 840
	UInt32								unk844;							// 844
	UInt32								unk848;							// 848
	UInt32								unk84C;							// 84C
	UInt32								unk850;							// 850
	UInt32								unk854;							// 854
	UInt32								unk858;							// 858
	UInt32								unk85C;							// 85C
	UInt32								unk860;							// 860
	NiTMap<D3DFORMAT, NiPixelFormat *>	DepthStencilFormats;			// 864 NiTMap<D3DFormat, NiPixelFormat *>
	UInt32								unk874;							// 874
	UInt32								unk878;							// 878
	UInt32								unk87C;							// 87C
};
assert(sizeof(NiDX9Renderer) == 0x880);

class BSRenderedTexture : public NiObject {
public:
	NiRenderTargetGroup*	RenderTargetGroup;	// 008
	UInt32					unk00C[5];			// 00C
	UInt32					unk020;				// 020
	UInt32					unk024;				// 024
	UInt32					unk028;				// 028
	UInt32					unk02C;				// 02C
	NiRenderedTexture*		RenderedTexture;	// 030
	UInt32					unk034;				// 034
	UInt32					unk038;				// 038
	UInt32					unk03C;				// 03C
};
assert(sizeof(BSRenderedTexture) == 0x40);

class ShadowSceneNode : public NiNode {
public:
	UInt32					unk0B8[91];
};
assert(sizeof(ShadowSceneNode) == 0x224);