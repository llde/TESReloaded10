#include "GameNi.h"

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