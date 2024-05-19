#include "GameNi.h"
#include "Game.h"
void BSTextureManager::DiscardShadowMap(BSRenderedTexture* Texture)
{
    ThisCall(0x007C1A30, this, Texture);
}

BSRenderedTexture* BSTextureManager::FetchShadowMap(void)
{
    return (BSRenderedTexture*)ThisCall(0x007C1960, this);
}

BSTextureManager* BSTextureManager::CreateInstance(void)
{
    BSTextureManager* Instance = (BSTextureManager*)Pointers::Functions::MemoryAlloc(0x48);
    ThisCall(0x007C1FF0, Instance);
    return Instance;
}

void BSTextureManager::DeleteInstance(void)
{
    ThisCall(0x007C2100, this);
    Pointers::Functions::MemoryDealloc(this);
}

void BSTextureManager::ReserveShadowMaps(UInt32 Count)
{
    ThisCall(0x007C2710, this, TheRenderManager, Count);
}

BSRenderedTexture* BSTextureManager::GetDefaultRenderTarget(UInt32 Type)
{
    return (BSRenderedTexture*)ThisCall(0x007C23C0, this, TheRenderManager, Type);
}

BSTextureManager** BSTextureManager::Singleton = (BSTextureManager**) 0x00B42F50;