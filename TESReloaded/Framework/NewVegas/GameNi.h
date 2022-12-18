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

class BSShaderAccumulator;

class ShadowSceneLight;
class AnimSequenceBase;

class TESObjectREFR;
class TESWaterCullingProcess;

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

	void GetLookAt(NiPoint3* LookAt, NiPoint3* Rotation);

	float x;
	float y;
	float z;
};
assert(sizeof(NiPoint3) == 0x00C);

class NiVector4 {
public:
	void Normalize();

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
	void GenerateRotationMatrixZXY(NiPoint3* v, bool degrees);

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
	UInt32 WhichSide(NiPlane* Plane);

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

	Entry*	start;		// 000
	Entry*	end;		// 004
	UInt32	numItems;	// 008
};
assert(sizeof(NiTList<void>) == 0x00C);

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
	UInt16			Add(T* Item);

	void**	_vtbl;			// 00
	T*		data;			// 04
	UInt16	capacity;		// 08 - init'd to size of preallocation
	UInt16	end;			// 0A - index of the first free entry in the block of free entries at the end of the array (or numObjs if full)
	UInt16	numObjs;		// 0C - init'd to 0
	UInt16	growSize;		// 0E - init'd to size of preallocation
};
assert(sizeof(NiTArray<void>) == 0x010);

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
	virtual void		Destructor(bool freeThis);	// 00
	virtual void		Free(void);					// 01

	UInt32				m_uiRefCount;	// 004
};
assert(sizeof(NiRefObject) == 0x008);

class NiObject : public NiRefObject {
public:
	virtual NiRTTI*		GetType();		// 02
	virtual NiNode*		GetAsNiNode();	// 03 
	virtual UInt32		Unk_04();		// 04
	virtual UInt32		Unk_05();		// 05
	virtual UInt32		Unk_06();		// 06
	virtual UInt32		Unk_07();		// 07
	virtual UInt32		Unk_08();		// 08
	virtual UInt32		Unk_09();		// 09
	virtual UInt32		Unk_0A();		// 0A
	virtual UInt32		Unk_0B();		// 0B
	virtual UInt32		Unk_0C();		// 0C
	virtual UInt32		Unk_0D();		// 0D
	virtual UInt32		Unk_0E();		// 0E
	virtual UInt32		Unk_0F();		// 0F
	virtual UInt32		Unk_10();		// 10
	virtual UInt32		Unk_11();		// 11
	virtual NiObject*	Copy();			// 12
	virtual void		Load(NiStream* stream);
	virtual void		PostLoad(NiStream* stream);
	virtual void		FindNodes(NiStream* stream);
	virtual void		Save(NiStream* stream);
	virtual bool		Compare(NiObject* obj);
	virtual void		DumpAttributes(NiTArray <char*>* dst);
	virtual void		DumpChildAttributes(NiTArray <char*>* dst);
	virtual void		Unk_1A();
	virtual void		Unk_1B(UInt32 arg);
	virtual void		Unk_1C();
	virtual void		GetType2();	
	virtual void		Unk_1E(UInt32 arg);
	virtual void		Unk_1F();
	virtual void		Unk_20();
	virtual void		Unk_21();
	virtual void		Unk_22();
    
    
    void LogObjectAttributes();
};
assert(sizeof(NiObject) == 0x008);

class NiExtraData : public NiObject {
public:
	virtual	bool	Unk_23();
	virtual bool	Unk_24();

	char*	m_pcName;	// 08
};
assert(sizeof(NiExtraData) == 0x00C);

class NiObjectNET : public NiObject {
public:
	void				SetName(const char* Name) { char* (__cdecl* CreateString)(const char*) = (char* (__cdecl*)(const char*))0x00A5B690; char* S = CreateString(Name); ThisCall(0x00A5B950, this, &S); }

	const char*			m_pcName;						// 008
	NiTimeController*	m_controller;					// 00C
	NiExtraData**		m_extraDataList;				// 010
	UInt16				m_extraDataListLen;				// 014
	UInt16				m_extraDataListCapacity;		// 016
};
assert(sizeof(NiObjectNET) == 0x018);

struct PropertyNode{
    PropertyNode* next;
    PropertyNode* prev;
    NiProperty* data;
};
struct PropertyList {
    PropertyNode* first;
    PropertyNode* last;
    UInt32 count;
};


template <std::size_t N> struct Debug; // No definition

template <> struct Debug<12> {}; // Definition for "old" sizeof;

template struct Debug<sizeof(PropertyNode)>; // Issue error if definition is missing

class NiAVObject : public NiObjectNET {
public:
	virtual void			UpdateControllers(float fTime);
	virtual void			Unk_24();
	virtual void			Unk_25();
	virtual NiAVObject*		GetObjectByName(const char* Name);
	virtual void*			Unk_27();
	virtual void			UpdateDownwardPass(float fTime, bool bUpdateControllers);
	virtual void			UpdateSelectedDownwardPass(float fTime);
	virtual void			UpdateRigidDownwardPass(float fTime);
	virtual void			UpdatePropertiesDownward(NiPropertyState* ParentState);
	virtual void			UpdateEffectsDownward(NiDynamicEffectState* ParentState);
	virtual void			UpdateTransformData();
	virtual void			UpdateTransformBound();
	virtual void			OnVisible(NiCullingProcess* CullingProcess);
	virtual void			Unk_30(void* arg);			// get NiMaterialProperty, pass to arg if found
	virtual void			Unk_31(void* arg);
	virtual void			Unk_32(void* arg);
	virtual void			Unk_33(void* arg);
	virtual void			Unk_34(void* arg);
	virtual void			Unk_35(void* arg);
	virtual void			Unk_36(void* arg);	// last is 036 verified

	enum {
		kFlag_AppCulled					= 1 << 0,
		kFlag_SelUpdate					= 1 << 1,
		kFlag_SelUpdateTransforms		= 1 << 2,
		kFlag_SelUpdatePropControllers	= 1 << 3,
		kFlag_SelUpdateRigid			= 1 << 4,
	};

	float GetDistance(NiPoint3* Point);
	NiBound*	GetWorldBound();
	float		GetWorldBoundRadius();
    
	NiNode*					m_parent;				// 018
	UInt32					unk001C;				// 01C
	NiBound*				m_kWorldBound;			// 020
	PropertyList			propertyList;			// 024
	UInt32					m_flags;				// 030
	NiTransform				m_localTransform;		// 034
	NiTransform				m_worldTransform;		// 068
};
assert(sizeof(NiAVObject) == 0x9C);

class NiNode : public NiAVObject {
public:
	virtual void		AddObject(NiAVObject* nChild, UInt8 FirstAvail); // Add child node
	virtual NiAVObject* RemoveObject(NiAVObject** RemovedChild, NiAVObject* nChild);
	virtual NiAVObject* RemoveObjectAt(NiAVObject** RemovedChild, UInt32 Index);
	virtual NiAVObject* SetObjectAt(NiAVObject** SetChild, UInt32 Index, NiAVObject* nChild);
	virtual void		ApplyTransform(const NiMatrix33& Mat, const NiPoint3& Trn, bool OnLeft);
	virtual bool		Unk_3B();
	virtual bool		Unk_3C();
	virtual bool		Unk_3D();
	virtual bool		Unk_3E();
	virtual bool		Unk_3F();
	
	void				New(UInt16 Children);

	NiTArray<NiAVObject*>	m_children;	// 09C
};
assert(sizeof(NiNode) == 0xAC);

class NiBillboardNode : public NiNode {
public:
	virtual void	Unk_40();

	UInt32			unkAC[2];		// AC
};
assert(sizeof(NiBillboardNode) == 0xB4);

class NiCamera : public NiAVObject {
public:
	D3DMATRIX 	    WorldToCam;	        // 94
	NiFrustum		Frustum;			// D4
	float			MinNearPlaneDist;	// F8
	float			MaxFarNearRatio;	// FC
	NiViewport		ViewPort;			// 100
	float			LODAdjust;			// 110
};
assert(sizeof(NiCamera) == 0x114);

class SceneGraph : public NiNode {
public:
	void				UpdateParticleShaderFoV(float FoV);
	void				SetNearDistance(float Distance);
    
	NiCamera*			camera;					// AC
	UInt32				unkB0;					// B0
	NiCullingProcess*	cullingProcess;			// B4
	UInt8				IsMinFarPlaneDistance;	// B8 The farplane is set to 20480.0 when the flag is true. Probably used for interiors.
	UInt8				padB8[3];
	float				cameraFOV;				// BC
};
assert(sizeof(SceneGraph) == 0xC0);

class NiDynamicEffect : public NiAVObject {
public:
	UInt8			On;				// 9C
	UInt8			unk9D;			// 9D
	UInt8			CastShadows;	// 9E
	UInt8			CanCarry;		// 9F
	UInt32			Index;			// A0
	UInt32			unkA4;			// A4
	UInt32			unkA8;			// A8
	UInt32			unkAC;			// AC
	UInt32			unkB0;			// B0
	UInt32			unkB4;			// B4
	UInt32			unkB8;			// B8
	UInt32			unkBC;			// BC
	UInt32			unkC0;			// C0
};
assert(sizeof(NiDynamicEffect) == 0xC4);

class NiLight : public NiDynamicEffect {
public:
	float			Dimmer;	// C4
	NiColor			Amb;	// C8
	NiColor			Diff;	// D4
	NiColor			Spec;	// E0
	void*			unk104;	// EC
};
assert(sizeof(NiLight) == 0xF0);

class NiPointLight : public NiLight {
public:
	float			Atten0;		// F0
	float			Atten1;		// F4
	float			Atten2;		// F8
};
assert(sizeof(NiPointLight) == 0xFC);

class NiDirectionalLight : public NiLight {
public:
	NiPoint3		direction;			// F0
};
assert(sizeof(NiDirectionalLight) == 0xFC);

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
	virtual void		Destructor(bool freeThis);			// 00
	virtual void		Free();								// 01

	UInt32							Flags;					// 04
	NiGeometryGroup*				GeometryGroup;			// 08
	UInt32							FVF;					// 0C
	IDirect3DVertexDeclaration9*	VertexDeclaration;		// 10
	UInt32							unk10;					// 14
	UInt32							VertCount;				// 18
	UInt32							MaxVertCount;			// 1C
	UInt32							StreamCount;			// 20
	UInt32*							VertexStride;			// 24
	NiVBChip**						VBChip;					// 28
	UInt32							IndexCount;				// 2C
	UInt32							IBSize;					// 30
	IDirect3DIndexBuffer9*			IB;						// 34
	UInt32							BaseVertexIndex;		// 38
	D3DPRIMITIVETYPE				PrimitiveType;			// 3C
	UInt32							TriCount;				// 40
	UInt32							MaxTriCount;			// 44
	UInt32							NumArrays;				// 48
	UInt16*							ArrayLengths;			// 4C
	UInt16*							IndexArray;				// 50
};
assert(sizeof(NiGeometryBufferData) == 0x54);

class NiGeometryData : public NiObject {
public:
	enum Consistency {
		MUTABLE			 = 0x0000,
		STATIC			 = 0x4000,
		VOLATILE		 = 0x8000,
		CONSISTENCY_MASK = 0xF000,
	};

	UInt16						Vertices;			// 008
	UInt16						Unk00A;				// 00A
	UInt16						Unk00C;				// 00C
	UInt16						Unk00E;				// 00E
	UInt32						Unk010;				// 010
	UInt32						Unk014;				// 014
	UInt32						Unk018;				// 018
	UInt32						Unk01C;				// 01C
	NiPoint3*					Vertex;				// 020
	NiPoint3*					Normal;				// 024
	NiColorAlpha*				Color;				// 028
	UInt32						Texture;			// 02C NiPoint2*
	UInt32						Unk030;				// 030
	NiGeometryBufferData*		BuffData;			// 034
	UInt8						Unk038;				// 038
	UInt8						Unk039;				// 039
	UInt8						Unk03A;				// 03A
	UInt8						Unk03B;				// 03B
	UInt8						Unk03C;				// 03C
	UInt8						pad03C[3];
};
assert(sizeof(NiGeometryData) == 0x40);

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
		UInt16					pad28;
		NiGeometryBufferData*	BuffData;		// 28
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
	UInt32				FrameID;				// 18
	UInt32				Bones;					// 1C
	UInt32				BoneRegisters;			// 20
	UInt32				BoneSize;				// 24
	void*				BoneMatrixes;			// 28 Matrixes array for the bones D3DMATRIX
	void*				SkinToWorldWorldToSkin;	// 2C D3DMATRIX
	UInt32				Unk30;					// 30
	
	bool IsPartitionEnabled(UInt32 partitionIndex);
    
};
assert(sizeof(NiSkinInstance) == 0x34);

class DismemberPartition {
public:
    UInt8 Enabled;
    UInt8 StartCap;  //Questionable, but it's the only way I can make sense of that code
    UInt16 bodyPart;
}; 
assert(sizeof(DismemberPartition) == 4);

class BSDismemberSkinInstance : public NiSkinInstance {
public:
    UInt32 partitionNumber;
    DismemberPartition* partitions;
    UInt8  IsRenderable;  //In Load this is made in OR with every partition->Enabled flag
    UInt8  pad[3];
};
assert(sizeof(BSDismemberSkinInstance) == 0x40);

class NiProperty : public NiObjectNET {
public:
	enum PropertyType {
		kType_Alpha,
		kType_Culling,
		kType_Material,
		kType_Shade,
		kType_Stencil,
		kType_Texturing,
	};
    virtual PropertyType GetPropertyType();
};
assert(sizeof(NiProperty) == 0x18);

class NiPropertyState {
public:
	NiProperty* prop[6];
	// 0 00
	// 1 04
	// 2 08
	// 3 0C
	// 4 10
	// 5 14
};

class NiGeometry : public NiAVObject {
public:
	virtual void	Unk_37();
	virtual void	Unk_38();
	virtual void	Unk_39();
	virtual void	Unk_3A();
	virtual void	Unk_3B();

	NiProperty*			GetProperty(NiProperty::PropertyType Type);

	NiPropertyState		propertyState;	// 9C
	UInt32				unkB4;			// B4
	NiGeometryData*		geomData;		// B8
	NiSkinInstance*		skinInstance;	// BC This seems to be a BSDismemberSkinInstance (old NiSkinInstance constructor is never used)
	NiD3DShader*		shader;			// C0
};
assert(sizeof(NiGeometry) == 0xC4);

class NiDX9TextureData : public NiObject {
public:
	NiTexture*				parent;			// 08
	UInt32					width;			// 0C
	UInt32					height;			// 10
	NiPixelFormat			PixelFormat;	// 14
	UInt8					Unk58;			// 58
	UInt8					Unk59;			// 59
	UInt8					Unk5A;			// 5A
	UInt8					Unk5B;			// 5B
	UInt32					Unk5C;			// 5C
	NiDX9Renderer*			pRenderer;		// 60
	IDirect3DBaseTexture9*	dTexture;		// 64
	UInt32					Levels;			// 68
};
assert(sizeof(NiDX9TextureData) == 0x6C);

class NiDX9SourceTextureData : public NiDX9TextureData {
public:
	UInt8					ReplacementData;	// 6C
	UInt8					Mipmap;				// 6D
	UInt8					pad64[2];
	UInt32					FormattedSize;		// 70
	UInt32					Palette;			// 74 NiPalette
	UInt32					LevelsSkipped;		// 78
	UInt32					SourceRevID;		// 7C
	UInt32					PalRevID;			// 80
};
assert(sizeof(NiDX9SourceTextureData) == 0x84);

class NiTexture : public NiObjectNET {
public:
	virtual UInt32	GetWidth();
	virtual UInt32	GetHeight();
	virtual void	Unk_25();
	virtual void	Unk_26();
	virtual void	Unk_27();
	virtual void	Unk_28();

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
	NiTexture*			nextTex;		// 028 - linked list updated in ctor/dtor
	NiTexture*			prevTex;		// 02C
};
assert(sizeof(NiTexture) == 0x30);

class NiSourceTexture : public NiTexture {
public:
	virtual void	Unk_29();
	virtual void	Unk_2A();
	virtual void	Unk_2B();

	char*			ddsPath1;		// 30
	char*			ddsPath2;		// 34
	UInt32			unk38;			// 38
	UInt32			unk3C;			// 3C
	UInt32			unk40;			// 40
	UInt32			unk44;			// 44
};
assert(sizeof(NiSourceTexture) == 0x48);

class NiRenderedTexture : public NiTexture {
public:
	virtual Ni2DBuffer* GetBuffer();

	Ni2DBuffer* buffer;		// 030
	UInt32		unk034;		// 034
	UInt32		unk038;		// 038
	UInt32		unk03C;		// 03C
};
assert(sizeof(NiRenderedTexture) == 0x040);

class NiD3DTextureStage;
class NiD3DShaderConstantMap;

enum ShaderDefinitionEnum
{
  kShaderDefinition_ShadowLightShader = 0x1,
  kShaderDefinition_TallGrassShader = 0x2,
  kShaderDefinition_DistantLODShader = 0x3,
  kShaderDefinition_SpeedTreeBranchShader = 0x4,
  kShaderDefinition_SpeedTreeFrondShader = 0x5,
  kShaderDefinition_SpeedTreeLeafShader = 0x6,
  kShaderDefinition_BSShaderBloodSplatter = 0x7,
  kShaderDefinition_BSDistantTreeShader = 0x8,
  kShaderDefinition_NiD3DDefaultShader = 0x9,
  kShaderDefinition_SkyShader = 0xA,
  kShaderDefinition_HairShader = 0xD,
  kShaderDefinition_SkinShader = 0xE,
  kShaderDefinition_ParallaxShader = 0xF,
  kShaderDefinition_NiDX9ShaderDeclaration = 0x10,
  kShaderDefinition_WaterShader = 0x11,
  kShaderDefinition_ParticleShader = 0x18,
  kShaderDefinition_BoltShader = 0x19,
  kShaderDefinition_BeamShader = 0x1A,
  kShaderDefinition_Lighting30Shader = 0x1D,
  kShaderDefinition_PrecipitationShader = 0x1E,
  kShaderDefinition_TileShader = 0x20,
  kShaderDefinition_BSShaderNoLighting = 0x21,
  kShaderDefinition_VolumetricFogShader = 0x22,
};


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
	UInt8						Unk028;			// 028
	UInt8						Unk029[3];		// 029

};
assert(sizeof(NiD3DShaderDeclaration) == 0x02C);

class NiDX9ShaderDeclaration : public NiD3DShaderDeclaration {
public:
	UInt32		Unk02C;			// 02C
	UInt32		Unk030;			// 030
	UInt8		Unk034;			// 034
	UInt8		Unk035[3];		// 035

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

	ProgramType			eProgramType;		// 08
	char*				Name;				// 0C
	char*				ShaderProgramName;	// 10
	UInt32				CodeSize;			// 14
	void*				Unk018;				// 18
	void*				Unk01C;				// 1C
	IDirect3DDevice9*	Device;				// 20
	NiDX9Renderer*		Renderer;			// 24
	NiDX9RenderState*	RenderState;		// 28
};
assert(sizeof(NiD3DShaderProgram) == 0x2C);

class NiD3DVertexShader : public NiD3DShaderProgram {
public:
	UInt8							SoftwareVP;		// 2C
	UInt8							pad[3];			// 2D
	UInt32							Usage;			// 30
	IDirect3DVertexShader9*			ShaderHandle;	// 34
	IDirect3DVertexDeclaration9*	Declaration;	// 38
};
assert(sizeof(NiD3DVertexShader) == 0x3C);

class NiD3DPixelShader : public NiD3DShaderProgram {
public:
	IDirect3DPixelShader9* ShaderHandle;	// 2C
};
assert(sizeof(NiD3DPixelShader) == 0x30);

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
	UInt8							Unk04C;						// 4C
	UInt8							pad04C[3];
	char*							VertexShaderProgramFile;	// 50
	char*							VertexShaderEntryPoint;		// 54
	char*							VertexShaderTarget;			// 58
	NiD3DVertexShader*				VertexShader;				// 5C
	UInt8							SoftwareVP;					// 60
	UInt8							RendererOwned;				// 61
	UInt8							pad[2];
	UInt32							RefCount;					// 64
};
assert(sizeof(NiD3DPass) == 0x68);

class NiShader : public NiRefObject {
public:
	char*		Name;					// 008
	UInt32		Unk00C;					// 00C
	UInt8		Unk010;					// 010
	UInt8		pad010[3];
};
assert(sizeof(NiShader) == 0x14);

class NiD3DShaderInterface : public NiShader {
public:
	IDirect3DDevice9*	D3DDevice;		// 014
	NiDX9Renderer*		D3DRenderer;	// 018
	NiDX9RenderState*	D3DRenderState;	// 01C
	UInt8				Unk020;			// 020
	UInt8				pad01C[3];
};
assert(sizeof(NiD3DShaderInterface) == 0x24);

class NiD3DShader : public NiD3DShaderInterface {
public:
	UInt8					IsInitialized;		// 024
	UInt8					Unk021;				// 025
	UInt8					pad021[2];
	NiD3DShaderDeclaration* ShaderDeclaration;	// 028
	NiD3DRenderStateGroup*  RenderStateGroup;	// 02C
	NiD3DShaderConstantMap* PixelConstantMap;	// 030
	NiD3DShaderConstantMap* VertexConstantMap;	// 034
	UInt32					Unk038[14];			// 038
};
assert(sizeof(NiD3DShader) == 0x70);

class BSShader : public NiD3DShader {
public:
	UInt32		Unk070;			// 070
	UInt32		Unk074;			// 074
	UInt32		Unk078;			// 078
};
assert(sizeof(BSShader) == 0x7C);

class WaterShader : public BSShader {
public:
	UInt32				Unk07C[70];		// 07C
	NiD3DVertexShader*	Vertex[3];		// 194
	NiD3DPixelShader*	Pixel[38];		// 1A0
	UInt32				Unk238[6];		// 238
};
assert(sizeof(WaterShader) == 0x250);


class ShadowLightShader : public BSShader{
public:
	UInt32 unk07C[4];
};
assert(sizeof(ShadowLightShader) == 0x8C);


class ParallaxShader : public ShadowLightShader{
public:
	NiD3DVertexShader*  Vertex[20];
 	NiD3DPixelShader*   Pixel[33];
};
assert(sizeof(ParallaxShader) == 0x160);

class BSImageSpaceShader : public BSShader {
public:
	UInt32				Unk07C[18];	// 07C
	NiD3DVertexShader*	Vertex;		// 0C4
	NiD3DPixelShader*	Pixel;		// 0C8
};
assert(sizeof(BSImageSpaceShader) == 0xCC);

class WaterShaderHeightMap : public BSImageSpaceShader {
public:
	UInt32				Unk0CC;		// 0CC
};
assert(sizeof(WaterShaderHeightMap) == 0xD0);

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
	virtual void		func02();												// 02
	virtual void		func03();												// 03
	virtual void		func04();												// 04
	virtual	void		func05();												// 05
	virtual	void		func06();												// 06
	virtual void		func07();												// 07
	virtual void		func08();												// 08
	virtual void		func09();												// 09
	virtual void		func0A();												// 0A
	virtual void		func0B();												// 0B
	virtual void		func0C();												// 0C
	virtual void		func0D();												// 0D
	virtual void		func0E();												// 0E
	virtual void		func0F();												// 0F
	virtual void		func10();												// 10
	virtual void		func11();												// 11
	virtual void		func12();												// 12
	virtual void		func13();												// 13
	virtual void		func14();												// 14
	virtual void		func15();												// 15
	virtual void		func16();												// 16
	virtual void		func17();												// 17
	virtual void		func18();												// 18
	virtual void		func19();												// 19
	virtual void		func1A();												// 1A

	Ni2DBuffer*			ParentData;												// 08
	UInt32				Unk0C;													// 0C
	UInt32				Unk10;													// 10
	IDirect3DSurface9*	Surface;												// 14
};

class NiRenderTargetGroup : public NiObject {
public:
	virtual UInt32					GetWidth(UInt32 Index);											// 23
	virtual UInt32					GetHeight(UInt32 Index);										// 24
	virtual UInt32					GetDepthStencilWidth();											// 25
	virtual UInt32					GetDepthStencilHeight();										// 26
	virtual const NiPixelFormat*	GetPixelFormat(UInt32 Index);									// 27
	virtual const NiPixelFormat*	GetDepthStencilPixelFormat();									// 28
	virtual UInt32					GetBufferCount();											// 29
	virtual bool					AttachBuffer(Ni2DBuffer* Buffer, UInt32 Index);					// 2A
	virtual bool					AttachDepthStencilBuffer(NiDepthStencilBuffer* DepthBuffer);	// 2B
	virtual Ni2DBuffer*				GetBuffer(UInt32 Index);										// 2C
	virtual NiDepthStencilBuffer*	GetDepthStencilBuffer();										// 2D
	virtual void*					GetRendererData();												// 2E
	virtual void					SetRendererData(void* RendererData);							// 2F
	virtual void*					GetRenderTargetData(UInt32 RenderTargetIndex);					// 30
	virtual void*					GetDepthStencilBufferRendererData();							// 31
	virtual void					func32();													// 32
	virtual void					func33();													// 33

	UInt32							Unk08;						// 08
	Ni2DBuffer*						RenderTargets[4];			// 0C
	UInt32							numRenderTargets;			// 1C
	NiDepthStencilBuffer*			DepthStencilBuffer;			// 20
	void*							RenderData;					// 24
};
assert(sizeof(NiRenderTargetGroup) == 0x28);

class NiDX9RenderState : public NiRefObject {
public:
	virtual void							UpdateRenderState(const NiPropertyState* pkNew);// 02
	virtual void							SetAlpha(void* AlphaProperty);					// 03
	virtual void							SetDither(void* DitherProperty);				// 04
	virtual void							SetFog(NiFogProperty* FogProperty);				// 05
	virtual void							SetMaterial(void* u1);							// 06
	virtual void							SetShadeMode(void* ShadeProperty);				// 07
	virtual void							SetSpecular(void* SpecularProperty);			// 08
	virtual void							SetStencil(void* StencilProperty);				// 09
	virtual void							SetWireframe(void* WireframeProperty);			// 0A
	virtual void 							SetZBuffer(void* ZBufferProperty);				// 0B
	virtual void							RestoreAlpha();									// 0C
	virtual void							SetVertexBlending(UInt16 u1);					// 0D
	virtual void							SetNormalization(void* u1);						// 0E
	virtual void							func_0F(UInt32 u1);								// 0F
	virtual float							GetVar088();									// 10
	virtual void							func_11(float u1);								// 11
	virtual void							func_12(float u1, float u2);					// 12
	virtual BOOL							func_13();										// 13
	virtual void							func_14(BOOL u1);								// 14
	virtual void							func_15(UInt32 u1);								// 15
	virtual void							InitializeRenderStates();						// 16
	virtual void							BackUpAllStates();								// 17
	virtual void 							RestoreRenderState(D3DRENDERSTATETYPE state);	// 18
	virtual void							RestoreAllRenderStates();						// 19
	virtual void 							SetRenderState(D3DRENDERSTATETYPE state, UInt32 value, UInt8 Arg3, UInt8 Arg4);					// 1A
	virtual UInt32							GetRenderState(D3DRENDERSTATETYPE state);														// 1B
	virtual void							ClearPixelShaders();																			// 1C
	virtual void							BackUpPixelShader();																			// 1D
	virtual void							func_1E();																						// 1E
	virtual void							SetPixelShader(IDirect3DPixelShader9* PixelShader, UInt8 BackUp);								// 1F
	virtual IDirect3DPixelShader9*			GetPixelShader();																				// 20
	virtual	void							RestorePixelShader();																			// 21
	virtual void							RemovePixelShader(IDirect3DPixelShader9* PixelShader);											// 22
	virtual void							SetVertexShader(IDirect3DVertexShader9* pShader, UInt8 BackUp);									// 23
	virtual IDirect3DVertexShader9*			GetVertexShader();																				// 24
	virtual void							RestoreVertexShader();																			// 25
	virtual void							RemoveVertexShader(IDirect3DVertexShader9* pShader);											// 26
	virtual void							SetFVF(UInt32 FVF, UInt8 BackUp);																// 27
	virtual UInt32							GetFVF();																						// 28
	virtual void							RestoreFVF();																					// 29
	virtual void							ClearFVF(UInt32 FVF);																			// 2A
	virtual void							SetVertexDeclaration(IDirect3DVertexDeclaration9* pDecl, UInt8 BackUp);							// 2B
	virtual IDirect3DVertexDeclaration9*	GetVertexDeclaration();																			// 2C
	virtual void							RestoreVertexDeclaration();																		// 2D
	virtual void							ClearVertexDeclatation(IDirect3DVertexDeclaration9* pDecl);										// 2E
	virtual void							func_02F();																						// 2F
	virtual void 							SetTextureStageState(UInt32 Stage, D3DTEXTURESTAGESTATETYPE Type, UInt32 Value, UInt8 BackUp);	// 30
	virtual UInt32							GetTextureStageState(UInt32 Stage, D3DTEXTURESTAGESTATETYPE Type);								// 31
	virtual void							func_032();																						// 32
	virtual HRESULT							SetSamplerState(UInt32 Sampler, D3DSAMPLERSTATETYPE Type, UInt32 Value, UInt8 BackUp);			// 33
	virtual UInt32 							GetSamplerState(UInt32 Sampler, D3DSAMPLERSTATETYPE Type);										// 34
	virtual void							RestoreSamplerState(UInt32 Sampler, D3DSAMPLERSTATETYPE Type);									// 35
	virtual void							ClearTextureList();																				// 36
	virtual void							SetTexture(UInt32 Sampler, IDirect3DBaseTexture9* pTexture);									// 37
	virtual IDirect3DBaseTexture9*			GetTexture(UInt32 Sampler);																		// 38
	virtual void							RemoveTexture(IDirect3DBaseTexture9* pTexture);													// 39
	virtual void							SetSoftwareVertexProcessing(UInt8 bSoftware);													// 3A
	virtual UInt8							GetSoftwareVertexProcessing();																	// 3B
	virtual void							SetVar_0FF4(UInt8 u1);																			// 3C
	virtual UInt8							GetVar_0FF4();																					// 3D
	virtual void							SetVar_0FF5(UInt8 u1);																			// 3E
	virtual UInt8							GetVar_0FF5();																					// 3F
	virtual void							Reset();																						// 40
	virtual void							func_041();																						// 41
	
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
	UInt32                          Unk98[23];						// 0098
	UInt32							LeftHanded;						// 00F4
	UInt32							Unk0F8[10];						// 00F8
	NiRenderStateSetting			RenderStateSettings[256];		// 0120
	UInt32							Unk0920[64];					// 0920
	NiRenderStateSetting			TextureStageStateSettings[128];	// 0A20
	NiRenderStateSetting			SamplerStateSettings[80];		// 0E20
	UInt32							unk10A0[20];					// 10A0
	NiDX9ShaderConstantManager*		ShaderConstantManager;			// 10F0
	UInt8							ForceNormalizeNormals;			// 10F4
	UInt8							InternalNormalizeNormals;		// 10F5
	UInt8							UsingSoftwareVP;				// 10F6
	UInt8							Declaration;					// 10F7
	IDirect3DDevice9*				Device;							// 10F8
	NiDX9Renderer*					Renderer;						// 10FC
	UInt32							unk1000[(0x1018 - 0x1000) >> 2];// 1100
	D3DCAPS9						Caps;							// 1118
};
assert(offsetof(NiDX9RenderState, Device) == 0x10F8);
assert(sizeof(NiDX9RenderState) == 0x1248);

class NiRenderer : public NiObject {
public:
	enum ClearFlags {
		kClear_BACKBUFFER = 0x1,
		kClear_STENCIL = 0x2,
		kClear_ZBUFFER = 0x4,
		kClear_NONE = 0,
		kClear_ALL = kClear_BACKBUFFER | kClear_STENCIL | kClear_ZBUFFER
	};

	virtual void			Unk_23();
	virtual void			Unk_24();
	virtual void			Unk_25();
	virtual void			Unk_26();
	virtual void			Unk_27();
	virtual void			Unk_28();
	virtual void			Unk_29();
	virtual void			Unk_2A();
	virtual void			Unk_2B();
	virtual void			Unk_2C();
	virtual void			Unk_2D();
	virtual void			Unk_2E();
	virtual void			Unk_2F();
	virtual void			Unk_30();
	virtual void			Unk_31();
	virtual NiRenderTargetGroup* GetDefaultRT();	// get back buffer rt
	virtual NiRenderTargetGroup* GetCurrentRT();	// get currentRTGroup
	virtual void			Unk_34();
	virtual void			Unk_35();
	virtual void			Unk_36();
	virtual void			Unk_37();
	virtual void 			Unk_38();
	virtual void 			Unk_39();
	virtual void			Unk_3A();
	virtual void			Unk_3B();
	virtual void			PurgeGeometry(NiGeometryData* geo);
	virtual void			PurgeMaterial(NiMaterialProperty* material);
	virtual void			PurgeEffect(NiDynamicEffect* effect);
	virtual void			PurgeScreenTexture();
	virtual void			PurgeSkinPartition(NiSkinPartition* skinPartition);
	virtual void			PurgeSkinInstance(NiSkinInstance* skinInstance);
	virtual void			Unk_42();
	virtual bool			Unk_43();
	virtual void			Unk_44();
	virtual bool			FastCopy(void* src, void* dst, RECT* srcRect, SInt32 xOffset, SInt32 yOffset);
	virtual bool			Copy(void* src, void* dst, RECT* srcRect, RECT* dstRect, UInt32 filterMode);
	virtual void			Unk_47();
	virtual bool			Unk_48(void* arg);
	virtual void			Unk_49();
	virtual void			Unk_4A(float arg);
	virtual void 			Unk_4B(UInt32 size);
	virtual void			Unk_4C(UInt32 arg0, UInt32 arg1);
	virtual void			Unk_4D(UInt32 arg0, UInt32 arg1);
	virtual void			Unk_4E(void* buf);
	virtual void			CreateSourceTexture(NiSourceTexture* texture);
	virtual bool			CreateRenderedTexture(NiRenderedTexture* arg);
	virtual bool			CreateSourceCubeMap(NiSourceCubeMap* arg);
	virtual bool			CreateRenderedCubeMap(NiRenderedCubeMap* arg);
	virtual bool			CreateDynamicTexture(void* arg);
	virtual void			Unk_54();
	virtual bool			CreateDepthStencil(NiDepthStencilBuffer* arg, void* textureFormat);
	virtual void			Unk_56();
	virtual void			Unk_57();
	virtual void			Unk_58();
	virtual void			Unk_59();
	virtual void			Unk_5A();
	virtual void			Unk_5B();
	virtual void			Unk_5C();
	virtual void			Unk_5D();
	virtual void			Unk_5E();
	virtual bool			BeginScene();
	virtual bool			EndScene();
	virtual void			DisplayScene();
	virtual void			Clear(float* rect, UInt32 flags);
	virtual void			SetupCamera(NiPoint3* pos, NiPoint3* at, NiPoint3* up, NiPoint3* right, NiFrustum* frustum, float* viewport);
	virtual void			SetupScreenSpaceCamera(float* viewport);
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

	UInt32					Unk008[126];				// 008
	UInt32					SceneState;					// 200
	UInt32					Unk204;						// 204
	UInt32					Unk208;						// 208
	UInt32					Unk20C;						// 20C
};
assert(sizeof(NiRenderer) == 0x210);

class NiDX9Renderer : public NiRenderer {
public:
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
		FBMODE_MULTISAMPLES_2 = 0x00010000,
		FBMODE_MULTISAMPLES_3 = 0x00020000,
		FBMODE_MULTISAMPLES_4 = 0x00030000,
		FBMODE_MULTISAMPLES_5 = 0x00040000,
		FBMODE_MULTISAMPLES_6 = 0x00050000,
		FBMODE_MULTISAMPLES_7 = 0x00060000,
		FBMODE_MULTISAMPLES_8 = 0x00070000,
		FBMODE_MULTISAMPLES_9 = 0x00080000,
		FBMODE_MULTISAMPLES_10 = 0x00090000,
		FBMODE_MULTISAMPLES_11 = 0x000a0000,
		FBMODE_MULTISAMPLES_12 = 0x000b0000,
		FBMODE_MULTISAMPLES_13 = 0x000c0000,
		FBMODE_MULTISAMPLES_14 = 0x000d0000,
		FBMODE_MULTISAMPLES_15 = 0x000e0000,
		FBMODE_MULTISAMPLES_16 = 0x000f0000,
		FBMODE_MULTISAMPLES_NONMASKABLE = 0x80000000,
		FBMODE_QUALITY_MASK = 0x0000FFFF,
		FBMODE_NUM = 18
	};

	enum RefreshRate {
		REFRESHRATE_DEFAULT = 0
	};

	void							SetSamplerState(DWORD Sampler, D3DSAMPLERSTATETYPE State, DWORD Value);
	void							PackGeometryBuffer(NiGeometryBufferData* GeoData, NiGeometryData* ModelData, NiSkinInstance* SkinInstance, NiD3DShaderDeclaration* ShaderDeclaration);
	void							PackSkinnedGeometryBuffer(NiGeometryBufferData* GeoData, NiGeometryData* ModelData, NiSkinInstance* SkinInstance, NiSkinPartition::Partition* Partition, NiD3DShaderDeclaration* ShaderDeclaration);
	void							CalculateBoneMatrixes(NiSkinInstance* SkinInstance, NiTransform* WorldTrasform);

	UInt32							pad210[(0x288 - 0x210) >> 2];	// 210
	IDirect3DDevice9*				device;							// 288
	D3DCAPS9						caps;							// 28C
	HANDLE							deviceWindow;					// 3BC
	HANDLE							focusWindow;					// 3C0
	char							rendererInfo[0x200];			// 3C4
	UInt32							adapterIdx;						// 5C4
	UInt32							d3dDevType;						// 5C8 - D3DDEVTYPE
	UInt32							d3dDevFlags;					// 5CC - D3DCREATE
	UInt8							softwareVertexProcessing;		// 5D0 - !D3DCREATE_HARDWARE_VERTEXPROCESSING
	UInt8							mixedVertexProcessing;			// 5D1 - D3DCREATE_MIXED_VERTEXPROCESSING
	UInt8							pad5D2[2];						// 5D2
	UInt32							Unk5D4[15];						// 5D4
	NiTMap<void*, void*>			PrePackObjects;					// 610 - NiTPointerMap <NiVBBlock *, NiDX9Renderer::PrePackObject *>
	UInt32							Unk620[153];					// 620
	NiRenderTargetGroup*			defaultRTGroup;					// 884 - back buffer
	NiRenderTargetGroup*			currentRTGroup;					// 888
	NiRenderTargetGroup*			currentscreenRTGroup;			// 88C
	NiTMap<HWND*, NiRenderTargetGroup*>	screenRTGroups;					// 890 - NiTPointerMap <HWND *, NiPointer <NiRenderTargetGroup> >
	UInt32							Unk8A0[6];						// 8A0
	NiDX9RenderState*				renderState;					// 8B8
	UInt32							Unk8BC[33];						// 8BC
	D3DXMATRIXA16					worldMatrix;				// 940
	D3DXMATRIX						viewMatrix;					// 980
	D3DXMATRIX						projMatrix;					// 9C0
	D3DXMATRIX						UnkMatrix;					// A00
	D3DXMATRIX						invViewMatrix;				// A40
	UInt32							UnkA80[6];					// A80
	UInt32							width;						// A98
	UInt32							height;						// A9C
	UInt32							flags;						// AA0
	UInt32							windowDevice;				// AA4
	UInt32							windowFocus;				// AA8
	UInt32							adapterType;				// AAC
	UInt32							deviceType;					// AB0
	FrameBufferFormat				frameBufferFormat;			// AB4
	DepthStencilFormat				depthStencilFormat;			// AB8
	PresentationInterval			presentationInterval;		// ABC
	SwapEffect						swapEffect;					// AC0
	FrameBufferMode					frameBufferMode;			// AC4
	UInt32							backBufferCount;			// AC8
	RefreshRate						refreshRate;				// ACC
	UInt32							UnkAD0[44];					// AD0
};
assert(sizeof(NiDX9Renderer) == 0xB80);

class NiControllerSequence : public NiObject {
public:
	virtual void	Unk_23();

	struct ControlledBlock {
		void*	unk00;		// 00 NiInterpolator*
		void*	unk04;		// 04 NiMultiTargetTransformController*
		UInt32	unk08;		// 08
		UInt8	unk0C;		// 0C
		UInt8	pad0C[3];
	};

	const char*				sequenceName;			// 08
	UInt32					numControlledBlocks;	// 0C
	UInt32					arrayGrowBy;			// 10
	ControlledBlock**		controlledBlocks;		// 14
	const char**			unkNodeName;			// 18
	float					weight;					// 1C
	NiTextKeyExtraData*		textKeyData;			// 20
	UInt32					cycleType;				// 24
	float					frequency;				// 28
	float					startTime;				// 2C
	float					stopTime;				// 30
	float					flt34;					// 34
	float					flt38;					// 38
	float					flt3C;					// 3C
	NiControllerManager*	manager;				// 40
	UInt32					unk44;					// 44
	UInt32					unk48;					// 48
	float					flt4C;					// 4C
	float					flt50;					// 50
	float					flt54;					// 54
	UInt32					unk58;					// 58
	const char*				rootNodeName;			// 5C
	UInt32					unk60[5];				// 60
};
assert(sizeof(NiControllerSequence) == 0x74);

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
	UInt16	flags;		// 018
	UInt8	pad01A[2];	// 01A
	UInt32	Unk01C;		// 01C
};
assert(sizeof(NiShadeProperty) == 0x20);

class BSShaderProperty : public NiShadeProperty {
public:
	enum BSShaderType {
		kType_TallGrass		= 0,
		kType_Default		= 1,
		kType_Sky			= 10,
		kType_Skin			= 14,
		kType_Water			= 17,
		kType_Lighting3		= 29,
		kType_Tile			= 32,
		kType_NoLighting	= 33,
	};
	enum BSShaderFlags {
		kFlags_Specular				= 0x00000001,
		kFlags_Skinned				= 0x00000002,
		kFlags_LowDetail			= 0x00000004,
		kFlags_VertexAlpha			= 0x00000008,
		kFlags_Unk1					= 0x00000010, // MultiSpecular?
		kFlags_SinglePass			= 0x00000020,
		kFlags_Empty				= 0x00000040,
		kFlags_EnvMapping			= 0x00000080,
		kFlags_AlphaTexture			= 0x00000100,
		kFlags_Unk2					= 0x00000200,
		kFlags_Facegen				= 0x00000400,
		kFlags_ParallaxShader		= 0x00000800,
		kFlags_Unk3					= 0x00001000,
		kFlags_NoProjShadow			= 0x00002000,
		kFlags_LandscapeTexturing	= 0x00004000,
		kFlags_SimpleRefraction		= 0x00008000,
		kFlags_ComplexRefraction	= 0x00010000,
		kFlags_EyeEnvMapping		= 0x00020000,
		kFlags_Hair					= 0x00040000,
		kFlags_DynamicAlpha			= 0x00080000,
		kFlags_LocalMapHideSecret	= 0x00100000,
		kFlags_WindowsEnvMapping	= 0x00200000,
		kFlags_TreeBillboard		= 0x00400000,
		kFlags_ShadowFrustum		= 0x00800000,
		kFlags_MultipleTexture		= 0x01000000,
		kFlags_RemappableTexture	= 0x02000000,
		kFlags_DecalSinglePass		= 0x04000000,
		kFlags_DynDecalSinglePass	= 0x08000000,
		kFlags_ParallaxOcclusion	= 0x10000000,
		kFlags_ExternalEmittance	= 0x20000000,
		kFlags_ShadowMap			= 0x40000000,
		kFlags_ZBufferTest			= 0x80000000,
	};
	
	bool	IsLightingProperty();
	
	UInt32	Unk020;		// 020
	UInt32	Unk024;		// 024
	float	Unk028;		// 028
	float	Unk02C;		// 02C
	float	Unk030;		// 030
	float	Unk034;		// 034
	UInt32	Unk038;		// 038
	UInt32	Unk03C;		// 03C
	UInt32	Unk040;		// 040
	UInt32	Unk044;		// 044
	UInt32	Unk048;		// 048
	UInt32	Unk04C;		// 04C
	UInt32	Unk050;		// 050
	UInt32	Unk054;		// 054
	UInt32	type;		// 058
	float	Unk05C;		// 05C
};
assert(sizeof(BSShaderProperty) == 0x60);

class WaterShaderProperty : BSShaderProperty
{
public:
    struct VarAmounts
    {
      float unk;
      float fWaterReflectivityAmt;
      float fWaterOpacity;
      float fWaterDistortionAmt;
    };

  UInt8 byte60;
  UInt8 byte61;
  UInt8 byte62;
  bool bDepth;
  UInt32 dword64;
  UInt32 dword68;
  float blendRadiusX;
  float blendRadiusY;
  float fogPower;
  float fog78;
  UInt8 byte7C;
  UInt8 byte7D;
  UInt8 byte7E;
  bool isUseDefaultWater;
  bool bReflect;
  UInt8 bRefract;
  UInt8 UV;
  UInt8 byte83;
  UInt32 dword84;
  NiColorAlpha shallowColor;
  NiColorAlpha deepColor;
  NiColorAlpha reflectionColor;
  WaterShaderProperty::VarAmounts Vars;
  float floatC8;
  float floatCC;
  float blendRadiusZ;
  float floatD4;
  NiVector4 depthData;
  float floatE8;
  float floatEC;
  float floatF0;
  float floatF4;
  float floatF8;
  float floatFC;
  float fresnelZ;
  float fresnelW;
  float float108;
  float float10C;
  float float110;
  float float114;
  UInt8 fWaterFresnelTerm[4];
  float fWaterNoise;
  float fFogAmount;
  float texScale;
  UInt32 dword128;
  UInt32 dword12C;
  UInt32 dword130;
  NiSourceTexture *noiseTexture;
  BSRenderedTexture *noDepth;
  BSRenderedTexture *reflections;
  BSRenderedTexture *refractions;
  BSRenderedTexture *depth;
  UInt32 dword148;
  UInt32 dword14C;
};
assert(sizeof(WaterShaderProperty) == 0x150);


class BSShaderLightingProperty : public BSShaderProperty {
public:
	UInt32	Unk060;	// 060
	UInt32	Unk064;	// 064
	UInt32	Unk068;	// 068
	float	Unk06C;	// 06C
	UInt32	Unk070;	// 070
	UInt32	Unk074;	// 074
	UInt32	Unk078;	// 078
};
assert(sizeof(BSShaderLightingProperty) == 0x7C);

class BSShaderPPLightingProperty : public BSShaderLightingProperty {
public:
	UInt32		Unk07C;	// 07C
	UInt32		Unk080;	// 080
	float		Unk084;	// 084
	float		Unk088;	// 088
	float		Unk08C;	// 08C
	float		Unk090;	// 090
	float		Unk094;	// 094
	float		Unk098;	// 098
	float		Unk09C;	// 09C
	float		Unk0A0;	// 0A0
	UInt32		Unk0A4;	// 0A4
	UInt16		numLandscapeTextures;	// 0A8
	UInt8		pad0A8[2];
	NiTexture** textures[4];			// 0BC - array for texturing: 0 diffuse, 1 normal, 2 glow, 3 unk
	UInt32		Unk0BC;	// 0BC
	UInt32		Unk0C0;	// 0C0
	UInt32		Unk0C4;	// 0C4
	UInt32		Unk0C8;	// 0C8
	UInt32		Unk0CC;	// 0CC
	UInt32		Unk0D0;	// 0D0
	UInt32		Unk0D4;	// 0D4
	UInt32		Unk0D8;	// 0D8
	UInt32		Unk0DC;	// 0DC
	UInt32		Unk0E0;	// 0E0
	UInt32		Unk0E4;	// 0E4
	UInt32		Unk0E8;	// 0E8
	UInt32		Unk0EC;	// 0EC
	UInt32		Unk0F0;	// 0F0
	UInt32		Unk0F4;	// 0F4
	UInt32		Unk0F8;	// 0F8
	UInt32		Unk0FC;	// 0FC
	UInt32		Unk100;	// 100
};
assert(sizeof(BSShaderPPLightingProperty) == 0x104);

class SpeedTreeShaderLightingProperty : public BSShaderLightingProperty {
public:
	UInt32	Unk07C[3];	// 07C
};
assert(sizeof(SpeedTreeShaderLightingProperty) == 0x88);

class SpeedTreeLeafShaderProperty : public SpeedTreeShaderLightingProperty {
public:
	struct LeafData {
		UInt32		unk00;
		UInt32		unk04;
		float*		leafBase; // pointer to float4[48]
	};

	LeafData*	leafData;	// 088
};
assert(sizeof(SpeedTreeLeafShaderProperty) == 0x8C);

class BSFadeNode : public NiNode {
public:
	float			unkAC;			// AC
	float			unkB0;			// B0
	float			unkB4;			// B4
	float			FadeAlpha;		// B8
	UInt32			unkBC;			// BC
	UInt32			unkC0;			// C0
	UInt32			MultType;		// C4
	UInt32			unkC8;			// C8
	TESObjectREFR*	unkCC;			// CC
	UInt32			unkD0[5];		// D0
};
assert(sizeof(BSFadeNode) == 0xE4);

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
	void*					Unk2C;				// 2C BSShaderTextureSet*
	NiSourceTexture*		LeavesTexture;		// 30
	void*					Unk34;				// 34 BSShaderTextureSet*
	UInt32					Unk38;				// 38
	float					Unk3C;				// 3C
	UInt32					Unk40;				// 40
	UInt8					Unk44;				// 44
	UInt8					pad44[3];
	float					Unk48;				// 48
	float					Unk4C;				// 4C
};
assert(sizeof(BSTreeModel) == 0x50);

class BSTreeNode : public BSFadeNode {
public:
	BSTreeModel*		TreeModel;		// E4
	UInt32				UnkE0;			// E8
	UInt32				UnkE4;			// EC
	UInt32				UnkE8;			// F0
	float				UnkEC;			// F4
};
assert(sizeof(BSTreeNode) == 0xF8);

class ShadowSceneLight : public NiRefObject {
public:
	UInt32					unk008;			// 008
	float					flt00C[53];		// 00C
	NiTList<NiTriBasedGeom>	lgtList0E0;		// 0E0
	UInt8					byte0EC;		// 0EC
	UInt8					byte0ED;		// 0ED
	UInt8					byte0EE[2];		// 0EE
	UInt32					unk0F0;			// 0F0
	UInt32					unk0F4;			// 0F4
	NiPointLight*			sourceLight;	// 0F8
	UInt32					unk0FC;			// 0FC
	UInt32					unk100[6];		// 100
	UInt8					byte118;		// 118
	UInt8					pad119[3];		// 119
	float					flt11C;			// 11C
	float					flt120;			// 120
	UInt8					byte124;		// 124
	UInt8					pad125[3];		// 125
	UInt32					unk128[66];		// 128
	UInt32					array230[4];	// 230 BSSimpleArray<NiNode>
	void*					portalGraph;	// 240 BSPortalGraph*
	UInt32					unk244[3];		// 244
};
assert(sizeof(ShadowSceneLight) == 0x250);

class ShadowSceneNode : public NiNode {
public:
	UInt32								unk0AC[2];			// 0AC
	NiTList<ShadowSceneLight>			lights;				// 0B4
	NiTList<ShadowSceneLight>			actorShadowCasters;	// 0C0
	NiTList<ShadowSceneLight>::Entry*	unk0CC;				// 0CC
	NiTList<ShadowSceneLight>::Entry*	unk0D0;				// 0D0
	NiTList<ShadowSceneLight>::Entry*	unk0D4;				// 0D4
	ShadowSceneLight*					sceneLight1;		// 0D8
	ShadowSceneLight*					sceneLight2;		// 0DC
	ShadowSceneLight*					directionalLight;	// 0E0
	UInt32								unk0E4[6];			// 0E4
	void*								ptr0FC;				// 0FC
	void*								ptr100;				// 100
	UInt32								unk104;				// 104
	UInt32								unk108[3];			// 108
	void*								ptr114;				// 114
	void*								ptr118;				// 118
	UInt32								unk11C;				// 11C
	UInt32								unk120;				// 120
	UInt32								unk124;				// 124
	NiCamera*							cubeMapCam;			// 128 BSCubeMapCamera*
	UInt32								unk12C;				// 12C
	UInt8								byte130;			// 130
	UInt8								byte131;			// 131
	UInt8								pad132[2];			// 132
	void*								fogProperty;		// 134 BSFogProperty*
	UInt32								unk138;				// 138
	UInt32								array13C[4];		// 13C BSSimpleArray<NiFrustumPlanes>
	UInt32								array14C[4];		// 14C BSSimpleArray<void>
	UInt32								unk15C[3];			// 15C
	NiVector4							unk168;				// 168
	NiVector4							unk178;				// 178
	NiVector4							unk188;				// 188
	NiVector4							unk198;				// 198
	NiVector4							unk1A8;				// 1A8
	NiVector4							unk1B8;				// 1B8
	UInt32								lightingPasses;		// 1C8
	float								flt1CC[3];			// 1CC
	UInt32								unk1D8;				// 1D8
	UInt8								byte1DC;			// 1DC
	UInt8								pad1DD[3];			// 1DD
	void*								portalGraph;		// 1E0 BSPortalGraph*
	UInt32								unk1E4[3];			// 1E4
	float								flt1F0[3];			// 1F0
	UInt8								byte1FC;			// 1FC
	UInt8								pad1FD[3];			// 1FD
};
assert(sizeof(ShadowSceneNode) == 0x200);
