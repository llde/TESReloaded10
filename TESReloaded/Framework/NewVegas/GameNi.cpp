#include "GameNi.h"

void NiPoint3::GetLookAt(NiPoint3* LookAt, NiPoint3* Rotation) {
    float x, y, z, r;
    
    x = this->x - LookAt->x;
    y = this->y - LookAt->y;
    z = this->z - LookAt->z;
    r = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
    Rotation->x = D3DXToDegree(atan2(y, x)) + 90.0f;
    Rotation->y = D3DXToDegree(acos(z / r)) - 90.0f;
    Rotation->z = 0;
}

void NiVector4::Normalize() {
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

void NiMatrix33::GenerateRotationMatrixZXY(NiPoint3* v, bool degrees) {
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

UInt32 NiBound::WhichSide(NiPlane* Plane) {
    float Distance = Plane->Normal * Center - Plane->Constant;
    UInt32 Result = NiPlane::NoSide;

    if (Distance <= -Radius) Result = NiPlane::NegativeSide; else if (Distance >= Radius) Result = NiPlane::PositiveSide;
    return Result;
}

template <typename T>
UInt16	NiTArray<T>::Add(T* Item) {
    return (UInt16)ThisCall(0x00A5EB20, this, Item);
}
template class NiTArray<NiAVObject*>; //CURSED

float NiAVObject::GetDistance(NiPoint3* Point) {

    NiPoint3 v;

    v.x = this->m_worldTransform.pos.x - Point->x;
    v.y = this->m_worldTransform.pos.y - Point->y;
    v.z = this->m_worldTransform.pos.z - Point->z;
    return sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
}

NiBound* NiAVObject::GetWorldBound() { 
    return m_kWorldBound;
}

float	NiAVObject::GetWorldBoundRadius() {
    return (m_kWorldBound ? m_kWorldBound->Radius : 0.0f); 
}

void NiNode::New(UInt16 Children) { 
    ThisCall(0x00A5ECB0, this, Children);
}

void	SceneGraph::UpdateParticleShaderFoV(float FoV) {
    void (__cdecl* UpdateParticleShaderFoVData)(float) = (void (__cdecl*)(float))0x00B54000;
    ThisCall(0x00C52020, this, FoV, 0, NULL, 0);
    UpdateParticleShaderFoVData(FoV);
}

void	SceneGraph::SetNearDistance(float Distance) { 
    float* SettingNearDistance = (float*)0x01203148;
    *SettingNearDistance = Distance;
}

NiProperty*	 NiGeometry::GetProperty(NiProperty::PropertyType Type) {
    return propertyState.prop[Type];
}


bool NiSkinInstance::IsPartitionEnabled(UInt32 partitionIndex) {
    void* VFT = *(void**)this;
    if (VFT == Pointers::VirtualTables::BSDismemberSkinInstance){
        BSDismemberSkinInstance* t = (BSDismemberSkinInstance*) this;
        if (t->IsRenderable == 0) return false;
        if (t->partitions && t->partitionNumber < partitionIndex){
            DismemberPartition p = t->partitions[partitionIndex];
            if (!p.Enabled) return false;
        }
    }
    return true;
} 

void NiObject::LogObjectAttributes(){
    NiTArray<char*>* debug = (NiTArray<char*>*) Pointers::Functions::FormMemoryAlloc(sizeof(NiTArray<char*>));
    memset(debug, 0, sizeof(NiTArray<char*>));
    *(void**)debug = (void*)0x0102102C;  //NiTArray<char*> vtbl;
    debug->growSize = 16; //Must be initialized > 0    
    this->DumpAttributes(debug);
    for (int i = 0; i < debug->numObjs; i++){Logger::Log("%s", debug->data[i]); }
    Pointers::Functions::FormMemoryDeAlloc(debug);
}

void	NiDX9Renderer::SetSamplerState(DWORD Sampler, D3DSAMPLERSTATETYPE State, DWORD Value) {
    renderState->SetSamplerState(Sampler, State, Value, false);
}

void	NiDX9Renderer::PackGeometryBuffer(NiGeometryBufferData* GeoData, NiGeometryData* ModelData, NiSkinInstance* SkinInstance, NiD3DShaderDeclaration* ShaderDeclaration) {
    
}

void NiDX9Renderer::PackSkinnedGeometryBuffer(NiGeometryBufferData* GeoData, NiGeometryData* ModelData, NiSkinInstance* SkinInstance, NiSkinPartition::Partition* Partition, NiD3DShaderDeclaration* ShaderDeclaration){
    
}

void	NiDX9Renderer::CalculateBoneMatrixes(NiSkinInstance* SkinInstance, NiTransform* WorldTrasform) {
    ThisCall(0x00E6FE30, this, SkinInstance, WorldTrasform, false, 3, true); 
}

bool BSShaderProperty::IsLightingProperty() {
    bool r = false;

    if (type == BSShaderType::kType_Default || type == BSShaderType::kType_Lighting3) r = true;
    return r;
}	
