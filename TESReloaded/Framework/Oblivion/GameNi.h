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
class NiLines;
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

class ShadowSceneLight;
class AnimSequenceBase;

class TESObjectREFR;

class bhkCollisionObject;

struct NiRTTI {
	const char* name;
	NiRTTI*		parent;
};
assert(sizeof(NiRTTI) == 0x008);

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

	UInt8			GetAnimSequence(UInt16 AnimGroupKey, AnimSequenceBase** AnimSequence) { return (UInt8)ThisCall(0x00470960, this, AnimGroupKey, AnimSequence); } // for NiTMap<UInt32, AnimSequenceBase>* 

	UInt32			m_numBuckets;	// 4
	Entry**			m_buckets;		// 8
	UInt32			m_numItems;		// C
};
assert(sizeof(NiTMap<void, void>) == 0x010);

template <typename T>
class NiTArray {
public:

	UInt16		Add(T* Item) { return (UInt16)ThisCall(0x004B3680, this, Item); }

	void**		_vtbl;			// 00
	T*			data;			// 04
	UInt16		capacity;		// 08 - init'd to size of preallocation
	UInt16		end;			// 0A - index of the first free entry in the block of free entries at the end of the array (or numObjs if full)
	UInt16		numObjs;		// 0C - init'd to 0
	UInt16		growSize;		// 0E - init'd to size of preallocation
};
assert(sizeof(NiTArray<void>) == 0x010);

template <typename T>
class NiTLargeArray {
public:
	void**		_vtbl;			// 00
	T*			data;			// 04
	UInt32		capacity;		// 08 - init'd to size of preallocation
	UInt32		firstFreeEntry;	// 0C - index of the first free entry in the block of free entries at the end of the array (or numObjs if full)
	UInt32		numObjs;		// 10 - init'd to 0
	UInt32		growSize;		// 14 - init'd to size of preallocation
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
	virtual void	Destructor(bool freeThis);

	UInt32			m_uiRefCount;				// 004
};
assert(sizeof(NiRefObject) == 0x008);

class NiObject : public NiRefObject {
public:
	virtual NiRTTI*		GetType();
	virtual NiObject*	Unk_02();
	virtual UInt32		Unk_03();
	virtual UInt32		Unk_04();
	virtual UInt32		Unk_05();
	virtual NiObject*	Copy();
	virtual void		Load(NiStream* stream);
	virtual void		PostLoad(NiStream* stream);
	virtual void		FindNodes(NiStream* stream);
	virtual void		Save(NiStream* stream);
	virtual bool		Compare(NiObject* obj);
	virtual void		DumpAttributes(NiTArray <char*>* dst);
	virtual void		DumpChildAttributes(NiTArray <char*>* dst);
	virtual void		Unk_0E();
	virtual void		Unk_0F(UInt32 arg);
	virtual void		Unk_10();
	virtual void		Unk_11();
	virtual void		Unk_12(UInt32 arg);
};
assert(sizeof(NiObject) == 0x008);

class NiExtraData : public NiObject {
public:
	virtual	bool	Unk_13();
	virtual bool	Unk_14();

	char*	m_pcName;	// 08
};
assert(sizeof(NiExtraData) == 0x00C);

class TESObjectExtraData : public NiExtraData {
public:
	TESObjectREFR*	refr;	// 0C
};
assert(sizeof(TESObjectExtraData) == 0x010);

class NiObjectNET : public NiObject {
public:
	void				SetName(const char* Name) { ThisCall(0x006FF420, this, Name); }

	const char*			m_pcName;						// 008
	NiTimeController*	m_controller;					// 00C
	NiExtraData**		m_extraDataList;				// 010
	UInt16				m_extraDataListLen;				// 014
	UInt16				m_extraDataListCapacity;		// 016
};
assert(sizeof(NiObjectNET) == 0x018);

class NiAVObject : public NiObjectNET {
public:
	virtual void		UpdateControllers(float fTime);
	virtual void		Unk_14();
	virtual void		ApplyTransform(NiMatrix33* Mat, NiPoint3* Trn, bool OnLeft);
	virtual NiAVObject* GetObjectByName(const char* Name);
	virtual void*		Unk_17();
	virtual void		UpdateDownwardPass(float fTime, bool bUpdateControllers);
	virtual void		UpdateSelectedDownwardPass(float fTime);
	virtual void		UpdateRigidDownwardPass(float fTime);
	virtual void		UpdatePropertiesDownward(NiPropertyState* ParentState);
	virtual void		UpdateEffectsDownward(NiDynamicEffectState* ParentState);
	virtual void		UpdateWorldData();
	virtual void		UpdateWorldBound();
	virtual void		OnVisible(NiCullingProcess* CullingProcess);
	virtual void		Unk_20(void* arg);			// get NiMaterialProperty, pass to arg if found

	enum {
		kFlag_AppCulled					= 1 << 0, // originally named m_bAppCulled but they appear to have used bitfields
		kFlag_SelUpdate					= 1 << 1, // Selective update flags
		kFlag_SelUpdateTransforms		= 1 << 2,
		kFlag_SelUpdatePropControllers	= 1 << 3,
		kFlag_SelUpdateRigid			= 1 << 4,
		kFlag_DisplayObject				= 1 << 5, // For use with occlusion culling system
		kFlag_DisableSorting			= 1 << 6, // For use with sorting/accumulation system
		kFlag_SelTransformsOverride		= 1 << 7, // Selective update over-ride flags
		kFlag_IsNode					= 1 << 8, // Is the object a leaf or a node
		kFlag_IsOccluded				= 1 << 9, // Used by OR to manage occluded geometries
		kFlag_IsOCNode					= 1 << 10, // Used by OR to manage if the object is a node for occlusion culling geos
	};
	
	float GetDistance(NiPoint3* Point) {

		NiPoint3 v;

		v.x = this->m_worldTransform.pos.x - Point->x;
		v.y = this->m_worldTransform.pos.y - Point->y;
		v.z = this->m_worldTransform.pos.z - Point->z;
		return sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z));

	}
	NiBound*	GetWorldBound() { return &m_kWorldBound; }
	float		GetWorldBoundRadius() { return m_kWorldBound.Radius; }

	UInt16					m_flags;				// 018
	UInt8					pad01A[2];				// 01A
	NiNode*					m_parent;				// 01C
	NiBound					m_kWorldBound;			// 020
	NiTransform				m_localTransform;		// 030
	NiTransform				m_worldTransform;		// 064
	NiTList<NiProperty>		m_propertyList;			// 098
	bhkCollisionObject*		m_spCollision;			// 0A8
};
assert(sizeof(NiAVObject) == 0x0AC);

class NiNode : public NiAVObject {
public:
	virtual void				AddObject(NiAVObject* nChild, UInt8 FirstAvail); // Add child node
	virtual NiAVObject*			RemoveObject(NiAVObject** RemovedChild, NiAVObject* nChild);
	virtual NiAVObject*			RemoveObjectAt(NiAVObject** RemovedChild, UInt32 Index);
	virtual NiAVObject*			SetObjectAt(NiAVObject** SetChild, UInt32 Index, NiAVObject* nChild);
	virtual void				Unk_25();
	virtual bool				Unk_26();
	
	void						New(UInt16 Children) { ThisCall(0x0070B780, this, Children); };
	TESObjectREFR*				GetRef() { return ((TESObjectExtraData*)ThisCall(0x006FF9C0, this, "REF"))->refr; }

	NiTArray<NiAVObject*>		m_children;			// 0AC
	NiTList<NiDynamicEffect*>	m_effects;			// 0BC
	NiBound						m_combinedBounds;	// 0CC
};
assert(sizeof(NiNode) == 0x0DC);

class NiBillboardNode : public NiNode {
public:
	enum {
		kMode_AlwaysFaceCamera = 0,
		kMode_RotateAboutUp,
		kMode_RigidFaceCamera,
		kMode_AlwaysFaceCenter,
		kMode_RigidFaceCenter,
		kMode_BSRotateAboutUp,
		kMode_Mask = 7,

		kFlag_Unk3 = 1 << 3,
	};

	UInt16	flags;				// 0DC
	UInt8	pad0DE[2];			// 0DE
	float	lastUpdateTime;		// 0E0
};
assert(sizeof(NiBillboardNode) == 0x0E4);

class NiCamera : public NiAVObject {
public:
	float		WorldToCam[4][4];		// 0AC
	NiFrustum	Frustum;				// 0EC
	float		MinNearPlaneDist;		// 108
	float		MaxFarNearRatio;		// 10C
	NiViewport	ViewPort;				// 110
	float		LODAdjust;				// 120
};
assert(sizeof(NiCamera) == 0x124);

class NiCullingProcess {
public:
	virtual void	Destructor(bool freeMemory);
	virtual void	ProcessCull(NiAVObject* Object);
	virtual void	Process(NiCamera* Camera, NiAVObject* Object, NiVisibleArray* VisibleGeo);
	virtual void	AppendVirtual(NiGeometry* Geo);

	UInt8			UseAppendVirtual;	// 04 - always false
	UInt8			pad05[3];			// 05
	NiVisibleArray* VisibleGeo;			// 08
	NiCamera*		Camera;				// 0C
	NiFrustum		CameraFrustum;		// 10
	NiFrustumPlanes	Planes;				// 2C
};
assert(sizeof(NiCullingProcess) == 0x90);

class SceneGraph : public NiNode {
public:
	void				UpdateParticleShaderFoVData(float FoV) { void (__cdecl* UpdateParticleShaderFoVData)(float) = (void (__cdecl*)(float))0x007B70E0; ThisCall(0x00411160, this, FoV, 0); UpdateParticleShaderFoVData(FoV); }

	NiCamera*			camera;					// 0DC
	UInt32				unk0E0;					// 0E0
	NiCullingProcess*	cullingProcess;			// 0E4
	UInt8				IsMinFarPlaneDistance;	// 0E8 The farplane is set to 20480.0 when the flag is true. Probably used for interiors.
	UInt8				pad0E8[3];
	float				cameraFOV;				// 0EC
};
assert(sizeof(SceneGraph) == 0x0F0);

class NiDynamicEffect : public NiAVObject {
public:
	virtual UInt32	GetEffectType();

	UInt8	On;				// 0AC
	UInt8	unk0AD;			// 0AD
	UInt8	CastShadows;	// 0AE used by Oblivion Reloaded for interior shadows
	UInt8	CanCarry;		// 0AF used by Oblivion Reloaded for interior shadows
	UInt32	Index;			// 0B0
	UInt32	unk0B4;			// 0B4
	UInt32	unk0B8;			// 0B8 - init'd to 1

	NiTList<NiNode>		affectedNodes;		// 0BC
	NiTList<NiNode>		unaffectedNodes;	// 0CC
};
assert(sizeof(NiDynamicEffect) == 0x0DC);

class NiLight : public NiDynamicEffect {
public:
	float		Dimmer;		// 0DC
	NiColor		Amb;		// 0E0
	NiColor		Diff;		// 0EC
	NiColor		Spec;		// 0F8
	void*		unk104;		// 104
};
assert(sizeof(NiLight) == 0x108);

class NiPointLight : public NiLight {
public:
	float	Atten0;		// 108
	float	Atten1;		// 10C
	float	Atten2;		// 110
};
assert(sizeof(NiPointLight) == 0x114);

class NiDirectionalLight : public NiLight {
public:
	NiPoint3	m_direction;	// 108
};
assert(sizeof(NiDirectionalLight) == 0x114);

class NiProperty : public NiObjectNET {
public:
	enum PropertyType {
		kType_Alpha,
		kType_Fog,
		kType_Material,
		kType_RendSpec,
		kType_Shade,
		kType_Stencil,
		kType_Texturing,
		kType_VertexColor,
		kType_WireFrame,
		kType_ZBuffer
	};

	virtual UInt32	GetPropertyType();
	virtual void	Update(float unk0);
};
assert(sizeof(NiProperty) == 0x018);

class NiPropertyState : public NiRefObject {
public:
	NiProperty* prop[10]; // 008
	//  0 08 Alpha
	//  1 0C Fog
	//  2 10 Material
	//  3 14 RendSpec
	//  4 18 Lighting
	//  5 1C Stencil
	//  6 20 Texturing
	//  7 24 VertexColor
	//  8 28 WireFrame
	//  9 2C ZBuffer
};
assert(sizeof(NiPropertyState) == 0x030);

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
	UInt8							SoftwareVP;				// 10
	UInt8							pad10[3];
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
assert(sizeof(NiGeometryBufferData) == 0x050);

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
	NiBound						Bound;				// 00C
	NiPoint3*					Vertex;				// 01C
	NiPoint3*					Normal;				// 020
	NiColorAlpha*				Color;				// 024
	UInt32						Texture;			// 028 NiPoint2*
	UInt16						ActiveVertices;		// 02C
	UInt16						DataFlags;			// 02E
	UInt8						KeepFlags;			// 030
	UInt8						CompressFlags;		// 031
	UInt8						pad030[2];
	NiAdditionalGeometryData*	AdditionalGeomData;	// 034
	NiGeometryBufferData*		BuffData;			// 038
	UInt8						Unk03C;				// 03C
	UInt8						Unk03D;				// 03D
	UInt8						pad03C[2];
};
assert(sizeof(NiGeometryData) == 0x040);

class NiSkinPartition : public NiObject {
public:
	class Partition {
	public:
		void**					_vtbl;			// 00
		UInt16*					pBones;			// 04
		float*					Weights;		// 08
		UInt32					Unk04[4];		// 0C
		UInt16					Vertices;		// 1C
		UInt16					Triangles;		// 1E
		UInt16					Bones;			// 20
		UInt16					Strips;			// 22
		UInt16					BonesPerVertex; // 24
		UInt16					pad24;
		NiGeometryBufferData*	BuffData;		// 28
	};

	UInt32		PartitionsCount;		// 08
	Partition*	Partitions;				// 0C
};
assert(sizeof(NiSkinPartition) == 0x010);

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
	UInt32				Bones;				// 40
	BoneData*			BoneData;			// 44
};
assert(sizeof(NiSkinData) == 0x048);

class NiSkinInstance : public NiObject {
public:
	NiSkinData*			SkinData;				// 08
	NiSkinPartition*	SkinPartition;			// 0C
	NiAVObject*			RootParent;				// 10
	NiAVObject**		BoneObjects;			// 14
	UInt32				FrameID;				// 18
	UInt32				Bones;					// 1C
	void*				BoneMatrixes;			// 20 Matrixes array for the bones D3DMATRIX
	UInt32				BoneRegisters;			// 24
	void*				SkinToWorldWorldToSkin;	// 28 D3DMATRIX
};
assert(sizeof(NiSkinInstance) == 0x02C);

class NiGeometry : public NiAVObject {
public:
	virtual void	Render(NiRenderer* arg);
	virtual void	Unk_22(NiRenderer* arg);
	virtual void	SetGeomData(NiObject* obj);
	virtual void	Unk_24();
	virtual void	Unk_25(NiRenderer* arg);
	
	NiProperty*				GetProperty(NiProperty::PropertyType Type) { return (propertyState ? propertyState->prop[Type] : NULL); }

	NiPropertyState*		propertyState;		// 0AC
	NiDynamicEffectState*	dynamicEffectState;	// 0B0
	NiGeometryData*			geomData;			// 0B4
	NiSkinInstance*			skinInstance;		// 0B8
	NiD3DShader*			shader;				// 0BC BSShader
};
assert(sizeof(NiGeometry) == 0x0C0);

class NiDX9TextureData {
public:
	void**					_vtbl;			// 00
	NiTexture*				parent;			// 04
	NiDX9Renderer*			pRenderer;		// 08
	NiPixelFormat			PixelFormat;	// 0C
	IDirect3DBaseTexture9*  dTexture;		// 50
	UInt32					Width;			// 54
	UInt32					Height;			// 58
	UInt32					Levels;			// 5C
};
assert(sizeof(NiDX9TextureData) == 0x060);

class NiDX9SourceTextureData : public NiDX9TextureData {
public:
	UInt32					unk60;				// 60
	UInt8					ReplacementData;	// 64
	UInt8					Mipmap;				// 65
	UInt8					pad64;
	UInt32					FormattedSize;		// 68
	UInt32					Palette;			// 6C NiPalette
	UInt32					LevelsSkipped;		// 70
	UInt32					SourceRevID;		// 74
	UInt32					PalRevID;			// 78
};
assert(sizeof(NiDX9SourceTextureData) == 0x07C);

class NiTexture : public NiObjectNET {
public:
	virtual UInt32	GetWidth();
	virtual UInt32	GetHeight();

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

	FormatPrefs			formatPrefs;	// 018
	NiDX9TextureData*	rendererData;	// 024
	NiTexture*			texPrev;		// 028
	NiTexture*			texNext;		// 02C
};
assert(sizeof(NiTexture) == 0x030);

class NiSourceTexture : public NiTexture {
public:
	virtual void	Unk_15();
	virtual void	FreePixelData();
	virtual bool	Unk_17();

	UInt8			unk030;				// 030 - is static?
	UInt8			unk031[3];			// 031
	void*			unk034;				// 034
	const char*		fileName;			// 038
	NiPixelData*	pixelData;			// 03C
	UInt8			loadDirectToRender;	// 040
	UInt8			persistRenderData;	// 041
	UInt8			pad042[2];			// 042
	void*			unk044;				// 044
};
assert(sizeof(NiSourceTexture) == 0x048);

class NiRenderedTexture : public NiTexture {
public:
	virtual Ni2DBuffer* GetBuffer();

	Ni2DBuffer* buffer;		// 030
	UInt8		unk034;		// 034
	UInt8		pad034[3];
	D3DFORMAT	format;		// 038
	UInt8		unk03C;		// 03C
	UInt8		pad03C;
};
assert(sizeof(NiRenderedTexture) == 0x040);

class NiD3DTextureStage {
public:
	UInt32				Stage;				// 00
	NiTexture*			Texture;			// 04
	UInt32				Unk08;				// 08
};
assert(sizeof(NiD3DTextureStage) == 0x00C);

class NiD3DShaderConstantMapEntry {
public:
	void**				_vtbl;				// 00
	UInt32				Unk04;				// 04
	UInt32				Unk08;				// 08
	char*				Key;				// 0C
	UInt32				Internal;			// 10
	UInt32				Flags;				// 14
	UInt32				Extra;				// 18
	UInt32				ShaderRegister;		// 1C
	UInt32				RegisterCount;		// 20
	char*				VariableName;		// 24
	UInt32				DataSize;			// 28
	UInt32				DataStride;			// 2C
	void*				DataSource;			// 30
	UInt8				Unk34;				// 34
	UInt8				pad34[3];
};
assert(sizeof(NiD3DShaderConstantMapEntry) == 0x038);

class NiD3DShaderConstantMap {
public:
	void**									_vtbl;				// 00
	UInt32									Unk04;				// 04
	UInt32									Unk08;				// 08
	NiTArray<NiD3DShaderConstantMapEntry*>	Entries;			// 0C
	UInt8									Modified;			// 1C
	UInt8									pad1C[3];
	NiD3DShaderProgram*						LastShaderProgram;	// 20
	UInt32									Unk24;				// 24
	IDirect3DDevice9*						Device;				// 28
	NiDX9Renderer*							Renderer;			// 2C
	NiDX9RenderState*						RenderState;		// 30

};
assert(sizeof(NiD3DShaderConstantMap) == 0x034);

class NiD3DShaderDeclaration : public NiObject {
public:
	NiDX9Renderer*				Renderer;		// 008
	NiDX9VertexBufferManager*	BufferManager;	// 00C
	IDirect3DDevice9*			Device;			// 010
	UInt32						Unk014;			// 014
	UInt32						Unk018;			// 018
	UInt32						Unk01C;			// 01C
	UInt32						StreamCount;	// 020
	UInt32						Unk024;			// 024
	UInt32						Unk028;			// 028
};
assert(sizeof(NiD3DShaderDeclaration) == 0x02C);

class NiDX9ShaderDeclaration : public NiD3DShaderDeclaration {
public:
	UInt32		Unk02C;			// 02C
	UInt32		Unk030;			// 030
	UInt32		Unk034;			// 034
};
assert(sizeof(NiDX9ShaderDeclaration) == 0x038);

class NiD3DShaderProgram : public NiRefObject {
public:
	enum ProgramType {
		PROGRAM_VERTEX = 0,
		PROGRAM_PIXEL,
		PROGRAM_GEOMETRY,
		PROGRAM_MAX
	};

	ProgramType				eProgramType;		// 08
	char*					Name;				// 0C
	char*					ShaderProgramName;	// 10
	UInt32					CodeSize;			// 14
	void*					Unk018;				// 18
	IDirect3DDevice9*		Device;				// 1C
	NiDX9Renderer*			Renderer;			// 20
	NiDX9RenderState*		RenderState;		// 24
};
assert(sizeof(NiD3DShaderProgram) == 0x028);

class NiD3DVertexShader : public NiD3DShaderProgram {
public:
	UInt8							SoftwareVP;		// 28
	UInt8							pad[3];			// 29
	UInt32							Usage;			// 2C
	IDirect3DVertexShader9*			ShaderHandle;	// 30
	IDirect3DVertexDeclaration9*	Declaration;	// 34
};
assert(sizeof(NiD3DVertexShader) == 0x038);

class NiD3DPixelShader : public NiD3DShaderProgram {
public:
	IDirect3DPixelShader9*			ShaderHandle;	// 28
};
assert(sizeof(NiD3DPixelShader) == 0x02C);

class NiD3DPass {
public:
	void**							_vtbl;						// 00
	char							Name[16];					// 04
	UInt32							CurrentStage;				// 14
	UInt32							StageCount;					// 18
	UInt32							TexturesPerPass;			// 1C
	NiTArray<NiD3DTextureStage*>	Stages;						// 20
	NiD3DRenderStateGroup*			RenderStateGroup;			// 30
	NiD3DShaderConstantMap*			PixelConstantMap;			// 34
	char*							PixelShaderProgramFile;		// 38
	char*							PixelShaderEntryPoint;		// 3C
	char*							PixelShaderTarget;			// 40
	NiD3DPixelShader*				PixelShader;				// 44
	NiD3DShaderConstantMap*			VertexConstantMap;			// 48
	char*							VertexShaderProgramFile;	// 4C
	char*							VertexShaderEntryPoint;		// 50
	char*							VertexShaderTarget;			// 54
	NiD3DVertexShader*				VertexShader;				// 58
	UInt8							SoftwareVP;					// 5C
	UInt8							RendererOwned;				// 5D
	UInt8							pad[2];
	UInt32							RefCount;					// 60
};
assert(sizeof(NiD3DPass) == 0x064);

class NiShader : public NiRefObject {
public:
	char*		Name;					// 008
	UInt32		Unk00C;					// 00C
};
assert(sizeof(NiShader) == 0x010);

class NiD3DShaderInterface : public NiShader {
public:
	IDirect3DDevice9*	D3DDevice;		// 010
	NiDX9Renderer*		D3DRenderer;	// 014
	NiDX9RenderState*	D3DRenderState;	// 018
	UInt8				Unk01C;			// 01C
	UInt8				Unk01D;			// 01D
	UInt8				pad[2];
};
assert(sizeof(NiD3DShaderInterface) == 0x020);

class NiD3DShader : public NiD3DShaderInterface {
public:
	UInt8					IsInitialized;		// 020
	UInt8					Unk021;				// 021
	UInt8					pad021[2];
	NiD3DShaderDeclaration* ShaderDeclaration;	// 024
	NiD3DRenderStateGroup*  RenderStateGroup;	// 028
	NiD3DShaderConstantMap* PixelConstantMap;	// 02C
	NiD3DShaderConstantMap* VertexConstantMap;	// 030
	UInt32					CurrentPassIndex;	// 034
	UInt32					PassCount;			// 038
	NiD3DPass*				CurrentPass;		// 03C
	NiTArray<NiD3DPass*>	Passes;				// 040
	UInt32					Unk050[8];			// 050
};
assert(sizeof(NiD3DShader) == 0x70);

class BSShader : public NiD3DShader {
public:
	UInt32		Unk070;			// 070
	UInt32		Unk074;			// 074
	UInt32		Unk078;			// 078
};
assert(sizeof(BSShader) == 0x7C);

class GeometryDecalShader : public BSShader {
public:
	UInt32				Unk07C[2];		// 07C
	NiD3DVertexShader*	Vertex[2];		// 084
	NiD3DPixelShader*	Pixel[2];		// 08C
	UInt32				Unk104[3];		// 094
};
assert(sizeof(GeometryDecalShader) == 0x0A0);

class WaterShader : public BSShader {
public:
	UInt32				Unk07C[16];		// 07C
	NiD3DVertexShader*	Vertex[2];		// 0BC
	NiD3DPixelShader*	Pixel[16];		// 0C4
	UInt32				Unk104[5];		// 104
};
assert(sizeof(WaterShader) == 0x118);

class TallGrassShader : public BSShader {
public:
	UInt32				Unk07C[6];			// 07C
	NiD3DVertexShader*	Vertex1[20];		// 094 Vertex1 + Vertex2 are a unique array but we split it for fast use (1 are compiled 1_1 and 2 are compiled 2_0)
	NiD3DVertexShader*	Vertex2[20];		// 0E4
	NiD3DPixelShader*	Pixel1[2];			// 134 Pixel1 + Pixel2 are a unique array but we split it for fast use (1 are compiled 1_1 and 2 are compiled 2_0)
	NiD3DPixelShader*	Pixel2[7];			// 13C
	float*				InstanceData;		// 158 Pointer to a struct of 912 floats (228 registers)
	UInt32				Unk15C;				// 15C
	UInt16				InstanceDataCount;	// 160
	UInt16				pad160;				// 162
	UInt32				Unk164[12];			// 164
};
assert(sizeof(TallGrassShader) == 0x194);

class BSImageSpaceShader : public BSShader {
public:
	UInt32		Unk07C;		// 07C
	UInt32		Unk080;		// 080
	UInt32		Unk084;		// 084
	UInt32		Unk088;		// 088
	UInt32		Unk08C;		// 08C
};
assert(sizeof(BSImageSpaceShader) == 0x90);

class WaterShaderDisplacement : public BSImageSpaceShader {
public:
	UInt32				Unk090[9];		// 090
	NiD3DVertexShader*	Vertex[8];		// 0B4
	NiD3DPixelShader*	Pixel[8];		// 0D4
	UInt32				Unk0F4[13];		// 0F4
};
assert(sizeof(WaterShaderDisplacement) == 0x128);

class WaterShaderHeightMap : public BSImageSpaceShader {
public:
	float				Unk090;				// 090
	float				Unk094;				// 094
	float				Unk098;				// 098
	float				Unk09C;				// 09C
	UInt32				Unk0A0;				// 0A0
	UInt32				Unk0A4;				// 0A4
	UInt32				Unk0A8;				// 0A8
	UInt32				Unk0AC;				// 0AC
	NiD3DVertexShader*	Vertex;				// 0B0
	NiD3DPixelShader*	Pixel[7];			// 0B4
	UInt32				CurrentPixelIndex;	// 0D0
	UInt32				Unk0D4;				// 0D4
	UInt32				Unk0D8;				// 0D8
	UInt32				Unk0DC;				// 0DC
	UInt32				Unk0E0;				// 0E0
	UInt32				Unk0E4;				// 0E4
	UInt32				Unk0E8;				// 0E8 BSRenderedTexture*
	UInt32				Unk0EC;				// 0EC BSRenderedTexture*
	UInt32				Unk0F0;				// 0F0 BSRenderedTexture*
	UInt32				Unk0F4;				// 0F4
	UInt32				Unk0F8;				// 0F8
	UInt32				Unk0FC;				// 0FC
	UInt32				Unk100;				// 100
	UInt32				Unk104;				// 104
	UInt32				Unk108;				// 108
};
assert(sizeof(WaterShaderHeightMap) == 0x10C);

class HDRShader : public BSImageSpaceShader {
public:
	NiD3DVertexShader*	Vertex[8];		// 090
	NiD3DPixelShader*	Pixel[8];		// 0B0
	UInt32				Unk0D0;			// 0D0
	UInt32				Unk0D4[13];		// 0D4
	UInt32				Unk108[7];		// 108
};
assert(sizeof(HDRShader) == 0x124);

class SpeedTreeLeafShader : public BSShader {
public:
	NiVector4			LeafData[48];	// 07C
	NiD3DVertexShader*	Vertex[4];		// 37C
	NiD3DPixelShader*	Pixel[2];		// 38C
	UInt32				Unk394;			// 394
};
assert(sizeof(SpeedTreeLeafShader) == 0x398);

class ShadowLightShader : public BSShader {
public:
	UInt32					Unk07C;					// 07C
	UInt32					Unk080;					// 080
	UInt32					Unk084;					// 084
	UInt32					Unk088;					// 088
	NiD3DShaderConstantMap* PixelConstantMapSLS;	// 08C
	NiD3DShaderConstantMap* VertexConstantMapSLS;	// 090
	NiD3DShaderConstantMap* PixelConstantMapSLS2;	// 094
	NiD3DShaderConstantMap* VertexConstantMapSLS2;	// 098
};
assert(sizeof(ShadowLightShader) == 0x09C);

class ParallaxShader : public ShadowLightShader {
public:
	NiD3DVertexShader*	Vertex[36];		// 09C
	NiD3DPixelShader*	Pixel[30];		// 12C
};
assert(sizeof(ParallaxShader) == 0x1A4);

class SkinShader : public ShadowLightShader {
public:
	NiD3DVertexShader*	Vertex[20];		// 09C
	NiD3DPixelShader*	Pixel[10];		// 0EC
};
assert(sizeof(SkinShader) == 0x114);

class ShaderDefinition {
public:
	NiDX9ShaderDeclaration* ShaderDeclaration;
	BSShader*				Shader;
};
assert(sizeof(ShaderDefinition) == 0x008);

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
	virtual UInt32		GetWidth();												// 01
	virtual UInt32		GetHeight();											// 02
	virtual void*		GetVar10();												// 03
	virtual NiRTTI*		GetRTTI();												// 04
	virtual	UInt32		func05();												// 05
	virtual	UInt32		func06();												// 06
	virtual UInt32		func07();												// 07
	virtual UInt32		func08();												// 08
	virtual UInt32		func09();												// 09
	virtual UInt32		func0A();												// 0A
	virtual bool		ReleaseSurface1();										// 0B
	virtual bool		GetBufferData(IDirect3DDevice9* D3DDevice);					// 0C
	virtual bool		SetRenderTarget(IDirect3DDevice9* D3DDevice, UInt32 Index);	// 0D
	virtual bool		SetDepthTarget(IDirect3DDevice9* D3DDevice);				// 0E
	virtual void		ReleaseSurface2();										// 0F

	Ni2DBuffer*			ParentData;												// 08
	IDirect3DSurface9*	Surface;												// 0C
};
assert(sizeof(NiDX92DBufferData) == 0x010);

class NiDX9ImplicitBufferData : public NiDX92DBufferData {
public:
	NiPixelFormat*			PixelFormat;								// 10
	D3DPRESENT_PARAMETERS	PresentParams;								// 14
	IDirect3DDevice9*		Device;										// 4C
};
assert(sizeof(NiDX9ImplicitBufferData) == 0x050);

class NiDX9ImplicitDepthStencilBufferData : public NiDX92DBufferData { };
assert(sizeof(NiDX9ImplicitDepthStencilBufferData) == 0x010);

class NiDX9TextureBufferData : public NiDX92DBufferData { };
assert(sizeof(NiDX9TextureBufferData) == 0x010);

class NiRenderTargetGroup : public NiObject {
public:
	virtual UInt32					GetWidth(UInt32 Index);											// 13
	virtual UInt32					GetHeight(UInt32 Index);										// 14
	virtual UInt32					GetDepthStencilWidth();											// 15
	virtual UInt32					GetDepthStencilHeight();										// 16
	virtual const NiPixelFormat*	GetPixelFormat(UInt32 Index);									// 17
	virtual const NiPixelFormat*	GetDepthStencilPixelFormat();									// 18
	virtual UInt32					GetBufferCount();												// 19
	virtual bool					AttachBuffer(Ni2DBuffer* Buffer, UInt32 Index);					// 1A
	virtual bool					AttachDepthStencilBuffer(NiDepthStencilBuffer* DepthBuffer);	// 1B
	virtual Ni2DBuffer*				GetBuffer(UInt32 Index);										// 1C
	virtual NiDepthStencilBuffer*	GetDepthStencilBuffer();										// 1D
	virtual void*					GetRendererData();												// 1E
	virtual void					SetRendererData(void* RendererData);							// 1F
	virtual void*					GetRenderTargetData(UInt32 RenderTargetIndex);					// 20
	virtual void*					GetDepthStencilBufferRendererData();							// 21

	Ni2DBuffer*						RenderTargets[4];			// 08
	UInt32							numRenderTargets;			// 18
	NiDepthStencilBuffer*			DepthStencilBuffer;			// 1C
	void*							RenderData;					// 20
};
assert(sizeof(NiRenderTargetGroup) == 0x024);

class NiGeometryGroup {
public:
	virtual void		Destructor(bool freeThis);
	virtual void		Unk_01();
	virtual void		AddObject(NiGeometryData* GeometryData, NiSkinInstance* SkinInstance, NiSkinPartition::Partition* Partition);
	virtual void		Unk_03();
	virtual void		RemoveObject(NiSkinPartition::Partition* Partition);
	virtual void		RemoveObject(NiGeometryData* GeometryData);
	virtual NiVBChip*	CreateChip(NiGeometryBufferData* BufferData, UInt32 Stream);
	virtual void		ReleaseChip(NiGeometryBufferData* BufferData, UInt32 Stream);
	virtual bool		IsDynamic();
	virtual void		Unk_09();

	UInt32				m_uiRefCount;	// 04
	IDirect3DDevice9*	device;			// 08
};
assert(sizeof(NiGeometryGroup) == 0x00C);

class NiDX9RenderState : public NiRefObject {
public:
	virtual void						 UpdateRenderState(const NiPropertyState* pkNew);							// 01
	virtual void						 SetAlpha(void* AlphaProperty);												// 02
	virtual void						 SetDither(void* DitherProperty);											// 03
	virtual void						 SetFog(NiFogProperty* FogProperty);										// 04
	virtual void						 SetMaterial(void* u1);														// 05
	virtual void						 SetShadeMode(void* ShadeProperty);											// 06
	virtual void						 SetSpecular(void* SpecularProperty);										// 07
	virtual void						 SetStencil(void* StencilProperty);											// 08
	virtual void						 SetWireframe(void* WireframeProperty);										// 09
	virtual void 						 SetZBuffer(void* ZBufferProperty);											// 0A
	virtual void						 RestoreAlpha();															// 0B
	virtual void						 SetVertexBlending(UInt16 u1);												// 0C
	virtual void						 SetNormalization(void* u1);												// 0D
	virtual void						 func_0E(UInt32 u1);														// 0E - doesn't do anything
	virtual float						 GetVar088();																// 0F
	virtual void						 func_10(float u1);															// 10
	virtual void						 func_11(float u1, float u2);												// 11
	virtual BOOL						 GetLeftHanded();															// 12
	virtual void						 func_13(BOOL u1);															// 13
	virtual void						 func_14(UInt32 u1);														// 14
	virtual void						 InitializeRenderStates();													// 15
	virtual void						 BackUpAllStates();															// 16
	virtual void 						 RestoreRenderState(D3DRENDERSTATETYPE state);								// 17
	virtual void						 RestoreAllRenderStates();													// 18
	virtual void 						 SetRenderState(D3DRENDERSTATETYPE state, UInt32 value, UInt8 BackUp);		// 19
	virtual UInt32						 GetRenderState(D3DRENDERSTATETYPE state);									// 1A
	virtual void						 ClearPixelShaders();														// 1B
	virtual void						 BackUpPixelShader();														// 1C
	virtual void						 func_1D();																	// 1D
	virtual void						 SetPixelShader(IDirect3DPixelShader9* PixelShader, UInt8 BackUp);			// 1E
	virtual IDirect3DPixelShader9*		 GetPixelShader();															// 1F
	virtual	void						 RestorePixelShader();														// 20
	virtual void						 RemovePixelShader(IDirect3DPixelShader9* PixelShader);						// 21
	virtual void						 SetVertexShader(IDirect3DVertexShader9* pShader, UInt8 BackUp);			// 22
	virtual IDirect3DVertexShader9*		 GetVertexShader();															// 23
	virtual void						 RestoreVertexShader();														// 24
	virtual void						 RemoveVertexShader(IDirect3DVertexShader9* pShader);						// 25
	virtual void						 SetFVF(UInt32 FVF, UInt8 BackUp);											// 26
	virtual UInt32						 GetFVF();																	// 27
	virtual void						 RestoreFVF();																// 28
	virtual void						 ClearFVF(UInt32 FVF);														// 29
	virtual void						 SetVertexDeclaration(IDirect3DVertexDeclaration9* pDecl, UInt8 BackUp);	// 2A
	virtual IDirect3DVertexDeclaration9* GetVertexDeclaration();													// 2B
	virtual void						 RestoreVertexDeclaration();												// 2C
	virtual void						 ClearVertexDeclatation(IDirect3DVertexDeclaration9* pDecl);				// 2D
	virtual void						 func_02E();																// 2E
	virtual void						 func_02F();																// 2F
	virtual void						 func_030();																// 30
	virtual void						 func_031();																// 31
	virtual void 						 SetTextureStageState(UInt32 Stage, D3DTEXTURESTAGESTATETYPE Type, UInt32 Value, UInt8 BackUp);	// 32
	virtual UInt32						 GetTextureStageState(UInt32 Stage, D3DTEXTURESTAGESTATETYPE Type);								// 33
	virtual void						 SetSamplerState(UInt32 Sampler, D3DSAMPLERSTATETYPE Type, UInt32 Value, UInt8 BackUp);			// 34
	virtual UInt32 						 GetSamplerState(UInt32 Sampler, D3DSAMPLERSTATETYPE Type);										// 35
	virtual void						 RestoreSamplerState(UInt32 Sampler, D3DSAMPLERSTATETYPE Type);									// 36
	virtual void						 ClearTextureList();																			// 37
	virtual void						 SetTexture(UInt32 Sampler, IDirect3DBaseTexture9* pTexture);									// 38
	virtual IDirect3DBaseTexture9*		 GetTexture(UInt32 Sampler);																	// 39
	virtual void						 RemoveTexture(IDirect3DBaseTexture9* pTexture);												// 3A
	virtual void						 SetSoftwareVertexProcessing(UInt8 bSoftware);													// 3B
	virtual UInt8						 GetSoftwareVertexProcessing();																	// 3C
	virtual void						 SetVar_0FF4(UInt8 u1);																			// 3D
	virtual UInt8						 GetVar_0FF4();																					// 3E
	virtual void						 SetVar_0FF5(UInt8 u1);																			// 3F
	virtual UInt8						 GetVar_0FF5();																					// 40
	virtual void						 Reset();																						// 41
	virtual void						 func_042();																					// 42

	struct NiRenderStateSetting {
		UInt32 CurrentValue;
		UInt32 PreviousValue;
	};

	UInt32							Flags;							// 0008
	UInt32							unk000C[(0x0074 - 0x000C) >> 2];// 000C
	NiAlphaProperty*				DisabledAlphaProperty;			// 0074
	float							CameraNear;						// 0078
	float							CameraFar;						// 007C
	float							CameraDepthRange;				// 0080
	float							MaxFogFactor;					// 0084
	float							MaxFogValue;					// 0088
	NiColor							CurrentFogColor;				// 008C
	UInt32							unk098[23];						// 0098
	UInt32							LeftHanded;						// 00F4
	UInt32							unk0F8[10];						// 00F8
	NiRenderStateSetting			RenderStateSettings[256];		// 0120
	NiRenderStateSetting			TextureStageStateSettings[128];	// 0920
	NiRenderStateSetting			SamplerStateSettings[80];		// 0D20
	UInt32							unk0FA0[(0x0FF0 - 0x0FA0) >> 2];// 0FA0
	NiDX9ShaderConstantManager*		ShaderConstantManager;			// 0FF0
	UInt8							ForceNormalizeNormals;			// 0FF4
	UInt8							InternalNormalizeNormals;		// 0FF5
	UInt8							UsingSoftwareVP;				// 0FF6
	UInt8							Declaration;					// 0FF7
	IDirect3DDevice9*				Device;							// 0FF8
	NiDX9Renderer*					Renderer;						// 0FFC
	UInt32							unk1000[(0x1018 - 0x1000) >> 2];// 1000
	D3DCAPS9						Caps;							// 1018
};
assert(offsetof(NiDX9RenderState, Device) == 0x0FF8);
assert(sizeof(NiDX9RenderState) == 0x1148);

class NiAccumulator : public NiObject {
public:
	virtual void	Start(NiCamera* camera);
	virtual void	Stop();
	virtual void	Add(NiVisibleArray* list);
	virtual bool	Fn_16();

	NiCamera*		camera;	// 08
};
assert(sizeof(NiAccumulator) == 0x00C);

class NiRenderer : public NiObject {
public:
	enum ClearFlags {
		kClear_BACKBUFFER	= 0x1,
		kClear_STENCIL		= 0x2,
		kClear_ZBUFFER		= 0x4,
		kClear_NONE			= 0,
		kClear_ALL			= kClear_BACKBUFFER | kClear_STENCIL | kClear_ZBUFFER
	};

	enum {
		kCopyFilterMode_None = 0,
		kCopyFilterMode_Point,
		kCopyFilterMode_Linear,
	};

	virtual bool			Unk_13(UInt32 arg);
	virtual const char*		GetRendererDesc();	
	virtual UInt32			GetFlags();
	virtual void			SetClearDepth(float arg);
	virtual float			GetClearDepth();
	virtual void			SetClearColor4(float* src);
	virtual void			SetClearColor3(float* src);
	virtual void			GetClearColor(float* dst);
	virtual void			SetClearStencil(UInt32 src);
	virtual UInt32			GetClearStencil();
	virtual bool			ValidateRenderTargetGroup(NiRenderTargetGroup* renderTarget);
	virtual void			IsDepthBufferCompatible(Ni2DBuffer* buffer, NiDepthStencilBuffer* dsBuffer);
	virtual NiRenderTargetGroup* GetDefaultRTGroup();	
	virtual NiRenderTargetGroup* GetCurrentRTGroup();	
	virtual UInt8			Unk_21();			
	virtual void			Unk_22();			
	virtual void			Unk_23();			
	virtual void			Unk_24(UInt32 arg);		
	virtual void*			Unk_25(void* arg0, UInt32 arg1, UInt32 arg2);	
	virtual void*			Unk_26(void* arg);			
	virtual UInt32			Unk_27();			
	virtual UInt32			Unk_28();			
	virtual void			Unk_29();			
	virtual bool			SetMipmapSkipLevel(UInt32 arg);
	virtual UInt32			GetMipmapSkipLevel();
	virtual bool			Unk_2C(UInt32 arg0, UInt32 arg1, UInt32 arg2, UInt32 arg3);
	virtual void			PurgeGeometryData(NiGeometryData* geo);
	virtual void			PurgeMaterial(NiMaterialProperty* material);			
	virtual void			PurgeEffect(NiDynamicEffect* effect);
	virtual void			PurgeScreenTexture();
	virtual void			PurgeSkinPartition(NiSkinPartition* skinPartition);
	virtual void			PurgeSkinInstance(NiSkinInstance* skinInstance);
	virtual void			Unk_33();
	virtual bool			Unk_34();
	virtual void			Unk_35();
	virtual bool			FastCopy(void* src, void* dst, RECT* srcRect, SInt32 xOffset, SInt32 yOffset);
	virtual bool			Copy(void* src, void* dst, RECT* srcRect, RECT* dstRect, UInt32 filterMode);
	virtual void			Unk_38();			
	virtual bool			Unk_39(void* arg);		
	virtual void			Unk_3A();			
	virtual void			Unk_3B(float arg);		
	virtual void*			Unk_3C(UInt32 size);	
	virtual void			Unk_3D(UInt32 arg0, UInt32 arg1);
	virtual void			Unk_3E(UInt32 arg0, UInt32 arg1);
	virtual void			Unk_3F(void* buf);		
	virtual bool			Unk_40(UInt32 arg0);
	virtual void			CreateSourceTexture(NiSourceTexture* texture);			
	virtual bool			CreateRenderedTexture(NiRenderedTexture* arg);	
	virtual bool			CreateSourceCubeMap(NiSourceCubeMap* arg);				
	virtual bool			CreateRenderedCubeMap(NiRenderedCubeMap* arg);	
	virtual bool			CreateDynamicTexture(void* arg);					
	virtual void			CreatePalette(void* arg);
	virtual bool			CreateDepthStencil(NiDepthStencilBuffer* arg, void* textureFormat);
	virtual void			LockDynamicTexture(void* arg0, void* arg1);
	virtual void			UnLockDynamicTexture(void* arg);
	virtual void			LockRenderer();
	virtual void			UnlockRenderer();
	virtual bool			BeginScene();
	virtual bool			EndScene();
	virtual void			DisplayScene();
	virtual void			Clear(float* rect, UInt32 flags);
	virtual void			SetupCamera(NiPoint3* pos, NiPoint3* at, NiPoint3* up, NiPoint3* right, NiFrustum* frustum, float* viewport);
	virtual void			SetupScreenSpaceCamera(NiViewport* viewport);
	virtual bool			BeginUsingRenderTargetGroup(NiRenderTargetGroup* renderTarget, ClearFlags clearFlags);
	virtual bool			EndUsingRenderTargetGroup();
	virtual void			BeginBatch(UInt32 arg0, UInt32 arg1);	
	virtual void			EndBatch();
	virtual void			BatchRenderShape(void* arg);
	virtual void			BatchRenderStrips(void* arg);
	virtual void			RenderTriShape(NiTriShape* obj);
	virtual void			RenderTriStrips(NiTriStrips* obj);		
	virtual void			RenderTriShape2(NiTriShape* obj);		
	virtual void			RenderTriStrips2(NiTriStrips* obj);	
	virtual void			RenderParticles(NiParticles* obj);
	virtual void			RenderLines(NiLines* obj);			
	virtual void			RenderScreenTexture();

	struct CriticalSection {
		CRITICAL_SECTION	CriticalSection;				// 000
		UInt32				pad018[24];						// 018
		UInt32				ThreadOwner;					// 078
		UInt32				LockCount;						// 07C
	};

	NiAccumulator*			accumulator;					// 008 BSShaderAccumulator
	NiPropertyState*		propertyState;					// 00C
	NiDynamicEffectState*	dynamicEffectState;				// 010
	UInt32					pad014[(0x080 - 0x014) >> 2];	// 00C
	CriticalSection			RendererLockCriticalSection;	// 080
	CriticalSection			PrecacheCriticalSection;		// 100
	CriticalSection			SourceDataCriticalSection;		// 180
	UInt32					SceneState1;					// 200
	UInt32					SceneState2;					// 204
	UInt32					unk208;							// 208
	UInt8					IsReady;						// 20C
	UInt8					unk20D;							// 20D
	UInt8					pad20E[2];						// 20E
};
assert(sizeof(NiRenderer) == 0x210);

class NiDX9Renderer : public NiRenderer {
public:
	class Unk6F4 {
	public:
		UInt32	unk00;
		UInt32	unk04;
		UInt32	unk08;
		UInt32	unk0C;
		UInt32	unk10;
		UInt32	unk14;
		UInt32	unk18;
		UInt32	unk1C;
		UInt32	unk20;
		UInt32	unk24;
		UInt32	unk28;
		UInt32	unk2C;
		UInt32	unk30;
		UInt32	unk34;
		UInt32	unk38;
		UInt32	unk3C;
		UInt32	unk40;
		UInt32	unk44;
		UInt32	unk48;
		UInt32	unk4C;
		UInt32	unk50;
		UInt32	unk54;
	};

	enum FrameBufferFormat {
		FBFMT_UNKNOWN = 0,
		FBFMT_R8G8B8,
		FBFMT_A8R8G8B8,
		FBFMT_X8R8G8B8,
		FBFMT_R5G6B5,
		FBFMT_X1R5G5B5,
		FBFMT_A1R5G5B5,
		FBFMT_A4R4G4B4,
		FBFMT_R3G3B2,
		FBFMT_A8,
		FBFMT_A8R3G3B2,
		FBFMT_X4R4G4B4,
		FBFMT_R16F,
		FBFMT_G16R16F,
		FBFMT_A16B16G16R16F,
		FBFMT_R32F,
		FBFMT_G32R32F,
		FBFMT_A32B32G32R32F,
		FBFMT_NUM
	};

	enum DepthStencilFormat {
		DSFMT_UNKNOWN = 0,
		DSFMT_D16_LOCKABLE = 70,
		DSFMT_D32 = 71,
		DSFMT_D15S1 = 73,
		DSFMT_D24S8 = 75,
		DSFMT_D16 = 80,
		DSFMT_D24X8 = 77,
		DSFMT_D24X4S4 = 79,
	};

	enum PresentationInterval {
		PRESENT_INTERVAL_IMMEDIATE = 0,
		PRESENT_INTERVAL_ONE = 1,
		PRESENT_INTERVAL_TWO = 2,
		PRESENT_INTERVAL_THREE = 3,
		PRESENT_INTERVAL_FOUR = 4,
		PRESENT_INTERVAL_NUM
	};

	enum SwapEffect {
		SWAPEFFECT_DEFAULT,
		SWAPEFFECT_DISCARD,
		SWAPEFFECT_FLIP,
		SWAPEFFECT_COPY,
		SWAPEFFECT_NUM
	};

	enum FrameBufferMode {
		FBMODE_DEFAULT,
		FBMODE_LOCKABLE,
		FBMODE_MULTISAMPLES_2			= 0x00010000,
		FBMODE_MULTISAMPLES_3			= 0x00020000,
		FBMODE_MULTISAMPLES_4			= 0x00030000,
		FBMODE_MULTISAMPLES_5			= 0x00040000,
		FBMODE_MULTISAMPLES_6			= 0x00050000,
		FBMODE_MULTISAMPLES_7			= 0x00060000,
		FBMODE_MULTISAMPLES_8			= 0x00070000,
		FBMODE_MULTISAMPLES_9			= 0x00080000,
		FBMODE_MULTISAMPLES_10			= 0x00090000,
		FBMODE_MULTISAMPLES_11			= 0x000a0000,
		FBMODE_MULTISAMPLES_12			= 0x000b0000,
		FBMODE_MULTISAMPLES_13			= 0x000c0000,
		FBMODE_MULTISAMPLES_14			= 0x000d0000,
		FBMODE_MULTISAMPLES_15			= 0x000e0000,
		FBMODE_MULTISAMPLES_16			= 0x000f0000,
		FBMODE_MULTISAMPLES_NONMASKABLE = 0x80000000,
		FBMODE_QUALITY_MASK				= 0x0000FFFF,
		FBMODE_NUM						= 18
	};

	enum RefreshRate {
		REFRESHRATE_DEFAULT = 0
	};

	virtual bool		DeleteRenderedCubeMap(NiRenderedCubeMap* arg);
	virtual bool		DeleteTexture(NiTexture* arg);					
	virtual bool		DeleteDynamicTexture(UInt32 arg);		

	void				SetSamplerState(DWORD Sampler, D3DSAMPLERSTATETYPE State, DWORD Value) { renderState->SetSamplerState(Sampler, State, Value, false); };
	void				PackGeometryBuffer(NiGeometryBufferData* GeoData, NiGeometryData* ModelData, NiSkinInstance* SkinInstance, NiD3DShaderDeclaration* ShaderDeclaration) { ThisCall(0x00767B40, this, GeoData, ModelData, SkinInstance, ShaderDeclaration, 0); }
	void				PackSkinnedGeometryBuffer(NiGeometryBufferData* GeoData, NiGeometryData* ModelData, NiSkinInstance* SkinInstance, NiSkinPartition::Partition* Partition, NiD3DShaderDeclaration* ShaderDeclaration) { ThisCall(0x00763130, this, GeoData, ModelData, SkinInstance, Partition, ShaderDeclaration, 0); }
	void				CalculateBoneMatrixes(NiSkinInstance* SkinInstance, NiTransform* WorldTrasform) { ThisCall(0x007655F0, this, SkinInstance, WorldTrasform, false, 3, true); }

	UInt32								pad210[(0x280 - 0x210) >> 2];	// 210
	IDirect3DDevice9*					device;							// 280
	D3DCAPS9							caps;							// 284
	HANDLE								deviceWindow;					// 3B4
	HANDLE								focusWindow;					// 3B8
	char								rendererInfo[0x200];			// 3BC
	UInt32								adapterIdx;						// 5BC
	UInt32								d3dDevType;						// 5C0 - D3DDEVTYPE
	UInt32								d3dDevFlags;					// 5C4 - D3DCREATE
	UInt8								softwareVertexProcessing;		// 5C8 - !D3DCREATE_HARDWARE_VERTEXPROCESSING
	UInt8								mixedVertexProcessing;			// 5C9 - D3DCREATE_MIXED_VERTEXPROCESSING
	UInt8								pad5CA[2];						// 5CA
	NiDX9AdapterDesc*					adapterDesc;					// 5CC
	NiDX9DeviceDesc*					deviceDesc;						// 5D0
	D3DCOLOR							clearColor;						// 5D4
	float								clearDepth;						// 5D8
	UInt32								clearStencil;					// 5DC
	UInt32								rendFlags;						// 5E0
	char								behavior[32];					// 5E4
	NiTMap<void*, void*>				PrePackObjects;					// 604 - NiTPointerMap <NiVBBlock *, NiDX9Renderer::PrePackObject *>
	UInt32								pad624[(0x648 - 0x614) >> 2];	// 614
	NiPoint3							camRight;						// 648
	NiPoint3							camUp;							// 654
	NiPoint3							modelCamRight;					// 660
	NiPoint3							modelCamUp;						// 66C
	float								NearDepth;						// 678
	float								DepthRange;						// 67C
	D3DMATRIX							identityMatrix;					// 680
	D3DVIEWPORT9						viewport;						// 6C0
	UInt32								HWBones;						// 6D8
	UInt32								MaxStreams;						// 6DC
	UInt32								Unk6E0;							// 6E0
	UInt32								Unk6E4;							// 6E4
	UInt8								pad6E8;							// 6E8
	UInt8								unk6E9;							// 6E9
	UInt8								pad6EA[2];						// 6EA
	UInt32								ResetCounter;					// 6EC
	UInt8								lostDevice;						// 6F0 - disables drawing
	UInt8								pad6F1[3];						// 6F1
	Unk6F4								unk6F4[4];						// 6F4
	UInt32								DefaultTextureFormat[4];		// 854 - NiPixelFormat*
	NiPixelData*						DefaultTextureData[4];			// 864
	UInt32								unk874;							// 874 - init'd to 0x16
	NiRenderTargetGroup*				defaultRTGroup;					// 878 - probably back buffer
	NiRenderTargetGroup*				currentRTGroup;					// 87C
	NiRenderTargetGroup*				currentscreenRTGroup;			// 880
	NiTMap<HWND*, NiRenderTargetGroup*>	screenRTGroups;					// 884 - NiTPointerMap <HWND *, NiPointer <NiRenderTargetGroup> >
	UInt32								unk894;							// 894
	UInt8								unk898;							// 898
	UInt8								pad899[3];						// 899
	NiObject*							unk89C;							// 89C - NiPropertyState (0x30)
	NiGeometryGroupManager*				geometryGroupMgr;				// 8A0
	NiGeometryGroup*					unsharedGeometryGroup;			// 8A4 - NiUnsharedGeometryGroup
	NiGeometryGroup*					dynamicGeometryGroup;			// 8A8 - NiDynamicGeometryGroup
	NiDX9RenderState*					renderState;					// 8AC
	NiDX9VertexBufferManager*			vertexBufferMgr;				// 8B0
	NiDX9IndexBufferManager*			indexBufferMgr;					// 8B4
	NiDX9TextureManager*				textureMgr;						// 8B8
	NiDX9LightManager*					lightMgr;						// 8BC
	NiTMap<NiRenderedTexture*, NiDX9RenderedTextureData*>	renderedTextures;				// 8C0 - NiTPointerMap <NiRenderedTexture *, NiDX9RenderedTextureData *>
	NiTMap<NiRenderedCubeMap*, NiDX9RenderedCubeMapData*>	renderedCubeMaps;				// 8D0 - NiTPointerMap <NiRenderedCubeMap *, NiDX9RenderedCubeMapData *>
	NiTMap<void* , NiDX9DynamicTextureData*>				dynamicTextures;				// 8E0 - NiTPointerMap <NiDynamicTexture *, NiDX9DynamicTextureData *>
	NiTexture*							ClipperImage;					// 8F0
	NiTList <NiDX92DBufferData*>		atDisplayFrame;					// 8F4
	NiTList <NiD3DShaderInterface*>		shaderInterfaces;				// 904
	UInt32								Unk914;							// 914
	UInt32								Unk918;							// 918
	UInt32								Unk91C;							// 91C
	UInt32								Unk920;							// 920
	UInt32								Unk924;							// 924
	UInt32								Unk928;							// 928
	UInt32								Unk92C;							// 92C
	UInt32								Unk930;							// 930
	UInt32								Unk934;							// 934
	UInt32								Unk938;							// 938
	UInt32								Unk93C;							// 93C
	D3DXMATRIXA16						worldMatrix;					// 940
	D3DXMATRIX							viewMatrix;						// 980
	D3DXMATRIX							projMatrix;						// 9C0
	D3DXMATRIX							invViewMatrix;					// A00
	UInt32								ScreenTextureVerts;				// A40 NiPoint2*
	NiColorAlpha*						ScreenTextureColors;			// A44
	UInt32								ScreenTextureTexCoords;			// A48 NiPoint2*
	UInt16								unkA4C;							// A4C
	UInt8								unkA4E[2];						// A4E
	UInt16*								ScreenTextureIndices;			// A50
	UInt32								NumScreenTextureIndices;		// A54
	UInt32								width;							// A58
	UInt32								height;							// A5C
	UInt32								flags;							// A60
	UInt32								windowDevice;					// A64
	UInt32								windowFocus;					// A68
	UInt32								adapterType;					// A6C
	UInt32								deviceType;						// A70
	FrameBufferFormat					frameBufferFormat;				// A74
	DepthStencilFormat					depthStencilFormat;				// A78
	PresentationInterval				presentationInterval;			// A7C
	SwapEffect							swapEffect;						// A80
	FrameBufferMode						frameBufferMode;				// A84
	UInt32								backBufferCount;				// A88
	RefreshRate							refreshRate;					// A8C
	UInt8								unkA90;							// A90
	UInt8								padA91[3];						// A91
	NiD3DShader*						defaultShader;					// A94
	NiTArray<void>						unkA98;							// A98 Callback
	NiTArray<void*>						unkAA8;							// AA8
	NiTArray<void>						lostDeviceCallbacks;			// AB8 LostDeviceCallback
	NiTArray<void*>						lostDeviceCallbacksRefcons;		// AC8
	UInt32								padAD0[(0xB00 - 0xAD8) >> 2];	// AD8
};
assert(sizeof(NiDX9Renderer) == 0xB00);

class NiControllerSequence : public NiObject {
public:
	enum {
		kState_Inactive = 0,
		kState_Animating,
		kState_EaseIn,
		kState_EaseOut,
		kState_TransSource,
		kState_TransDest,
		kState_MorphSource
	};

	enum {
		kCycle_Loop = 0,
		kCycle_Reverse,
		kCycle_Clamp,
	};

	struct ArrayItem {
		NiRefObject*	unk00;		// 00
		NiRefObject*	unk04;		// 04
		UInt32			unk08;		// 08
		UInt8			unk0C;		// 0C
		UInt8			pad0C[3];
	};

	struct Unk018 {
		NiRefObject* unk00;	// 00
		UInt16		unk04;		// 04
		UInt16		unk06;		// 06
		UInt16		unk08;		// 08
		UInt16		unk0A;		// 0A
		UInt16		unk0C;		// 0C
		UInt8		pad0E[2];	// 0E
	};

	char*				 filePath;		// 008
	UInt32				 arraySize;		// 00C
	UInt32				 arrayGrowBy;	// 010
	ArrayItem*			 interpArray;	// 014
	Unk018*				 unk018;		// 018
	float				 weight;		// 01C
	NiTextKeyExtraData*  TextKeys;		// 020
	UInt32				 cycleType;		// 024
	float				 freq;			// 028
	float				 beginkey;		// 02C
	float				 endkey;		// 030
	float				 last;			// 034
	float				 weightLast;	// 038
	float				 lastScaled;	// 03C
	NiControllerManager* controllerMgr; // 040
	UInt32				 state;			// 044
	float				 offset;		// 048
	float				 start;			// 04C - offset * -1?
	float				 end;			// 050
	UInt32				 unk054;		// 054
	UInt32				 unk058;		// 058
	char*				 accumRootName;	// 05C
	NiAVObject*			 accumRoot;		// 060
	NiStringPalette*	 unk064;		// 064
};
assert(sizeof(NiControllerSequence) == 0x068);

class NiAVObjectPalette : public NiObject { };
assert(sizeof(NiAVObjectPalette) == 0x008);

class NiDefaultAVObjectPalette : public NiAVObjectPalette {
public:
	NiTMap<void*, NiAVObject>	avObjectMap;	// 008
	UInt32						unk018;			// 018
	NiNode*						niNode;			// 01C
};
assert(sizeof(NiDefaultAVObjectPalette) == 0x020);

class BSFadeNode : public NiNode {
public:
	UInt8	unk0DC;			// 0DC
	UInt8	unk0DD[3];		// 0DD
	float	FarDistSqr;		// 0E0
	float	NearDistSqr;	// 0E4
	float	FadeAlpha;		// 0E8
	UInt8	MultType;		// 0EC
	UInt8	unk0ED[3];		// 0ED
};
assert(sizeof(BSFadeNode) == 0x0F0);

class BSRenderedTexture : public NiRefObject {
public:
	NiRenderTargetGroup* RenderTargetGroup;	// 008
	UInt32				 unk008[5];			// 00C
	NiRenderedTexture*	 RenderedTexture;	// 020
};
assert(sizeof(BSRenderedTexture) == 0x024);

class NiAlphaProperty : public NiProperty {
public:
	enum AlphaFlags {
        ALPHA_BLEND_MASK    = 0x0001,
        SRC_BLEND_MASK      = 0x001e,
        SRC_BLEND_POS       = 1,
        DEST_BLEND_MASK     = 0x01e0,
        DEST_BLEND_POS      = 5,
        TEST_ENABLE_MASK    = 0x0200,
        TEST_FUNC_MASK      = 0x1c00,
        TEST_FUNC_POS       = 10,
        ALPHA_NOSORTER_MASK = 0x2000
    };

	UInt16	flags;			// 018
	UInt8	alphaTestRef;	// 01A
	UInt8	unk01B;			// 01B
};
assert(sizeof(NiAlphaProperty) == 0x01C);

class NiShadeProperty : public NiProperty {
public:
	virtual UInt32 Unk_15();

	UInt16	flags;		// 018
	UInt8	pad01A[2];	// 01A
};
assert(sizeof(NiShadeProperty) == 0x01C);

class BSShaderProperty : public NiShadeProperty {
public:
	virtual UInt32	Unk_15();							// returns 0 - may be a 'get type'
	virtual bool	Unk_16(UInt32 arg);					// returns 0
	virtual void*	Unk_17(UInt32 arg0, UInt32 arg1);
	virtual UInt16	Unk_18(UInt32 arg);					// returns 1
	virtual void*	Unk_19();							// returns &unk58

	enum BSShaderFlags {
		kSpecular			= 0x00000001,
		kSkinned			= 0x00000002,
		kLowDetail			= 0x00000004,
		kVertexAlpha		= 0x00000008,
		kUnk1				= 0x00000010, // MultiSpecular?
		kSinglePass			= 0x00000020,
		kEmpty				= 0x00000040,
		kEnvMapping			= 0x00000080,
		kAlphaTexture		= 0x00000100,
		kUnk2				= 0x00000200,
		kFacegen			= 0x00000400,
		kParallaxShader		= 0x00000800,
		kUnk3				= 0x00001000,
		kNoProjShadow		= 0x00002000,
		kLandscapeTexturing = 0x00004000,
		kSimpleRefraction	= 0x00008000,
		kComplexRefraction	= 0x00010000,
		kEyeEnvMapping		= 0x00020000,
		kHair				= 0x00040000,
		kDynamicAlpha		= 0x00080000,
		kLocalMapHideSecret	= 0x00100000,
		kWindowsEnvMapping	= 0x00200000,
		kTreeBillboard		= 0x00400000,
		kShadowFrustum		= 0x00800000,
		kMultipleTexture	= 0x01000000,
		kRemappableTexture	= 0x02000000,
		kDecalSinglePass	= 0x04000000,
		kDynDecalSinglePass = 0x08000000,
		kParallaxOcclusion	= 0x10000000,
		kExternalEmittance	= 0x20000000,
		kShadowMap			= 0x40000000,
		kZBufferTest		= 0x80000000,
	};

	class RenderPass {
	public:
		UInt32	unk00;		// 00 - vtbl?
		UInt16	type;		// 04 - see 007B4920
		UInt8	isFPass;	// 06
	};
	
	bool				IsLightingProperty() {
							void* VFTBSShaderPPLightingProperty = (void*)0x00A91384;
							void* VFTLighting30ShaderProperty = (void*)0x00A9576C;
							void* VFTSpeedTreeBranchShaderProperty = (void*)0x00A92A94;
							bool r = false;
							void* VFT = *(void**)this;

							if (VFT == VFTBSShaderPPLightingProperty || VFT == VFTLighting30ShaderProperty || VFT == VFTSpeedTreeBranchShaderProperty) r = true;
							return r;
						}
	
	bool				IsWaterProperty() {
							void* VFTWaterShaderProperty = (void*)0x00A956EC;
							bool r = false;
							void* VFT = *(void**)this;

							if (VFT == VFTWaterShaderProperty) r = true;
							return r;
						}

	UInt32				passInfo;				// 01C
	float				alpha;					// 020 - init'd to 1
	UInt32				lastRenderPassState;	// 024 - init'd to 0
	NiTList<RenderPass>	passes;					// 028
	NiTList<RenderPass>	unk38;					// 038
	NiTList<RenderPass>	unk48;					// 048
	NiTList<RenderPass>	unk58;					// 058
	UInt32				unk068;					// 068
};
assert(sizeof(BSShaderProperty) == 0x06C);

class BSShaderLightingProperty : public BSShaderProperty {
public:
	NiTList<ShadowSceneLight*>	lights;		// 06C
	UInt32						unk07C;		// 07C
	NiTList<void*>				decals;		// 080 DECAL_DATA
	UInt32						unk090;		// 090
	float						unk094;		// 094
	UInt32						refID;		// 098
};
assert(sizeof(BSShaderLightingProperty) == 0x09C);

class BSShaderPPLightingProperty : public BSShaderLightingProperty {
public:
	virtual void*	Unk_1A(void * arg);
	virtual void	Unk_1B(void * arg0, UInt32 arg1, void * arg2);
	virtual UInt32	Unk_1C();
	virtual void	Unk_1D(UInt32 arg);
	virtual UInt32	Unk_1E();
	virtual void	Unk_1F(UInt32 arg);
	virtual void	Unk_20(UInt32 arg0, UInt32 arg1);
	virtual void	Unk_21();
	virtual void	Unk_22();
	virtual void	Unk_23();
	virtual void	Unk_24();
	virtual void	Unk_25();
	virtual void	Unk_26();
	virtual void	Unk_27();

	class TexEffectData {
	public:
		UInt32	unk00[(0x0C - 0x00) >> 2];	// 00
		float	fillR;			// 0C
		float	fillG;			// 10
		float	fillB;			// 14
		float	fillA;			// 18
		float	edgeR;			// 1C
		float	edgeG;			// 20
		float	edgeB;			// 24
		float	edgeA;			// 28
		UInt32	unk2C[(0x54 - 0x2C) >> 2];	// 2C
		float	edgeFalloff;	// 54
	};

	UInt32			pad09C;					// 09C
	UInt32			pad0A0;					// 0A0
	float			envmapLOD;				// 0A4
	float			unk0A8;					// 0A8
	float			unk0AC;					// 0AC
	float			unk0B0;					// 0B0
	float			unk0B4;					// 0B4
	UInt16			numLandscapeTextures;	// 0B8 - init'd to 2
	UInt8			pad0BA[2];				// 0BA
	NiTexture**		textures[4];			// 0BC - array for texturing: 0 diffuse, 1 normal, 2 glow, 3 unk
	UInt32			pad0CC;					// 0CC
	UInt8*			specEnable;				// 0D0
	UInt32			unk0D4;					// 0D4
	UInt32			unk0D8;					// 0D8
	UInt32			unk0DC;					// 0DC - init'd to 1
	TexEffectData*	spTexEffectData;		// 0E0
	UInt8			unk0E4;					// 0E4
	UInt8			pad0E5[3];				// 0E5
	float			refractionPower;		// 0E8
	UInt32			refractionPeriod;		// 0EC
};
assert(sizeof(BSShaderPPLightingProperty) == 0x0F0);

class SpeedTreeShaderLightingProperty : public BSShaderLightingProperty {
public:
	virtual void*	Unk_1A();
	virtual UInt32	Unk_1B();				// same as DistanceLODShaderProperty 1A-1D with unk0A4
	virtual void	Unk_1C(UInt32 arg);
	virtual UInt32	Unk_1D();
	virtual void	Unk_1E(UInt32 arg);
	virtual void	Unk_1F(NiObject* obj);	// set unk09C, destroy old object
	virtual UInt32	Unk_20();				// get unk0A0
	virtual void	Unk_21(UInt32 arg);		// set unk0A0
	virtual UInt32	Unk_22();				// return 0 or 3 based on unk0A0
	virtual void	Unk_23(UInt32 arg);		// set unk0A0 to 1 or 3 based on arg

	struct Str0A4
	{
		UInt32	pad00[2];	// 00
		UInt32	unk08;		// 08
		UInt16	unk0C;		// 0C
	};

	NiObject*	unk09C;	// 09C
	UInt32		unk0A0;	// 0A0
	Str0A4*		unk0A4;	// 0A4
};
assert(sizeof(SpeedTreeShaderLightingProperty) == 0x0A8);

class SpeedTreeLeafShaderProperty : public SpeedTreeShaderLightingProperty {
public:
	virtual SpeedTreeLeafShaderProperty* Unk_24();	// allocate a new SpeedTreeLeafShaderProperty
	virtual NiAdditionalGeometryData*	 Unk_25();	// allocate a new NiAdditionalGeometryData
	virtual UInt16						 Unk_26();	// return unk0AC
	virtual void*						 Unk_27();	// return unk0A8
	virtual UInt32						 Unk_28();	// return unk0A8 ? unk0A8[8] : 0
	virtual void						 Unk_29();	// call a fn on unk0A8 if it exists

	struct LeafData {
		UInt32		unk00;
		UInt32		unk04;
		float*		leafBase; // pointer to float4[48]
	};

	LeafData*	leafData;	// 0A8
	UInt16		unk0AC;		// 0AC
	UInt8		unk0AE[2];	// 0AE
};
assert(sizeof(SpeedTreeLeafShaderProperty) == 0x0B0);

class BSTreeModel : public NiRefObject {
public:
	UInt32					Unk08;				// 08
	UInt32					Unk0C;				// 0C
	UInt32					Unk10;				// 10
	UInt32					Unk14;				// 14
	UInt32					Unk18;				// 18
	UInt32					Unk1C;				// 1C
	UInt32					Unk20;				// 20
	UInt32					Unk24;				// 24
	UInt32					Unk28;				// 28
	UInt32					Unk2C;				// 2C
	NiSourceTexture*		BranchesTexture;	// 30
	NiTexturingProperty*	BranchesProp;		// 34
	NiSourceTexture*		LeavesTexture;		// 38
	NiTexturingProperty*	LeavesProp;			// 3C
	UInt32					Unk40;				// 40
	UInt32					Unk44;				// 44
	UInt32					Unk48;				// 48
	UInt32					Unk4C;				// 4C
	UInt32					Unk50;				// 50
	UInt32					Unk54;				// 54
};
assert(sizeof(BSTreeModel) == 0x058);

class BSTreeNode : public NiNode {
public:
	BSTreeModel*		TreeModel;		// DC
	UInt32				UnkE0;			// E0
	UInt32				UnkE4;			// E4
	UInt32				UnkE8;			// E8
	float				UnkEC;			// EC
};
assert(sizeof(BSTreeNode) == 0x0F0);

class ShadowSceneLight : public NiRefObject {
public:
	struct BVIntersectionData {
		NiPlane	planes[6];				// 00
		UInt32	intersections;			// 60 - bit field, mask = 0x3F (6 bits)
	};

	UInt32										unk08[(0xD4 - 0x8) >> 2];
	float										unkD4;				// D4
	float										currentFadeAlpha;	// D8
	float										unkDC;				// DC
	float										unkE0;				// E0
	NiTList<NiTriBasedGeom>						unkE4;				// E4
	UInt8										unkF4;				// F4
	UInt8										unkF5;				// F5
	UInt8										unkF5Pad[2];
	float										unkF8;				// F8
	UInt8										unkFC;				// FC
	UInt8										unkFCPad[3];
	NiPointLight*								sourceLight;		// 100
	UInt8										unk104;				// 104
	UInt8										unk104Pad[3];
	NiPoint3									lightPos;			// 108
	BSRenderedTexture*							shadowMap;			// 114
	UInt16										lightState;			// 118 when 0xFF, light source is culled (not active)
	UInt16										unk11A;				// 11A
	UInt32										unk11C;				// 11C
	UInt8										unk120;				// 120
	UInt8										pad121[3];
	NiCamera*									unk124;				// 124 BSCubeMapCamera*
	UInt32										unk128;				// 128
	UInt8										showDebug;			// 12C - debug shader toggle
	UInt8										unk12CPad[3];
	NiNode*										sourceNode;			// 130
	NiTList<NiAVObject>							unk134;				// 134
	NiTList<NiTriBasedGeom>::Entry*				unk144;				// 144
	NiTriShape*									unk148;				// 148
	NiCamera*									camera;				// 14C
	BVIntersectionData							unk150;				// 150
	BVIntersectionData							unk1B4;				// 1B4
	UInt32										unk218;				// 218
	UInt32										unk21C;				// 21C
};
assert(sizeof(ShadowSceneLight) == 0x220);

class ShadowSceneNode : public NiNode {
public:
	NiObject*							object1;			// 0DC
	UInt16								unk0E0;				// 0E0
	UInt8								pad0E2[2];			// 0E2
	NiTList<ShadowSceneLight>			lights;				// 0E4
	NiTList<ShadowSceneLight>			actorShadowCasters;	// 0F4
	NiTList<ShadowSceneLight>::Entry*	unk104;				// 104
	NiTList<ShadowSceneLight>::Entry*	unk108;				// 108
	NiTList<ShadowSceneLight>::Entry*	unk10C;				// 10C
	ShadowSceneLight*					sceneLight1;		// 110
	ShadowSceneLight*					sceneLight2;		// 114
	ShadowSceneLight*					directionalLight;	// 118
	UInt8								unk11C;				// 11C
	UInt8								pad11D[3];			// 11D
	NiObject*							object2;			// 120
	NiCamera*							cubeMapCamera;		// 124 BSCubeMapCamera*
	UInt32								unk128;				// 128
	UInt8								unk12C;				// 12C
	UInt8								pad12D[3];			// 12D
};
assert(sizeof(ShadowSceneNode) == 0x130);
