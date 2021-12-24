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