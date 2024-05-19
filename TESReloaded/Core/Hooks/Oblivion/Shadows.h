#pragma once

void RenderShadowMapHook();
extern int (__fastcall* RenderCanopyMap)(GridCellArray*);
int __fastcall RenderCanopyMapHook(GridCellArray* This);
void AddCastShadowFlagHook();
void EditorCastShadowFlagHook();