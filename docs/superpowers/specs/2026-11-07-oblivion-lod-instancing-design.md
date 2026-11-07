# Oblivion Distant LOD Geometry Instancing

## Status

Design approved for specification review on 2026-11-07.

## Goal

Add an Oblivion-only `InstanceManager` singleton that creates and renders a
hardware-instanced representation of eligible static geometry beneath a
`NiNode`. Integrate it with distant LOD rendering using the existing
`InstanceFarGeometry` setting and a shared Direct3D 9 shader-model-3 vertex and
pixel shader pair.

The original NiNode hierarchy remains the source of truth. Geometry that is
not eligible for instancing continues to use the game's renderer.

## Scope and non-goals

- Implement and register the manager only in the Oblivion target.
- Traverse `NiNode` trees and collect static, unskinned triangle shapes and
  strips with supported Direct3D 9 vertex layouts and valid buffers.
- Batch only geometries with compatible mesh data, vertex layout, texture, and
  alpha behavior.
- Preserve diffuse texture, vertex color, and alpha cutouts with one common
  shader pair.
- Keep skinned, animated, unsupported, or invalid geometry on the vanilla
  rendering path.
- Do not add per-material shader variants, modify source NiNode contents, or
  change New Vegas or Skyrim rendering.

## Approaches considered

1. **D3D9 hardware instancing (selected):** Retain compatible mesh/index
   buffers, bind per-instance transforms as a second vertex stream, and issue
   indexed instanced draws. This meets the performance goal and uses the
   requested common shader pair.
2. **CPU-merged geometry:** Combine vertices and indices into a single mesh.
   This reduces draw calls but is not hardware instancing and requires
   rebuilding geometry data.
3. **Per-geometry rendering:** Draw each source geometry through the common
   shader. This is simpler but does not reduce draw-call count.

## Manager and data flow

Add an `InstanceManager` in `TESReloaded/Core`, following the existing
Oblivion manager singleton pattern. Register its global pointer and
initialization in `Framework/Oblivion/Managers.*` and include its source and
header in the Oblivion Visual Studio project and filters.

The public manager operations are:

- `Initialize()` to allocate the singleton and load the common shader pair.
- `Create(NiNode*)` to build/cache instance batches for the supplied root and
  report whether the cached representation is ready.
- `Render(NiNode*)` to issue the cached batches and report success or failure.
- `Invalidate(NiNode*)` and `Clear()` to release cached resources when a
  hierarchy or worldspace is replaced.

Creation traverses the root, rejects null, app-culled, skinned, animated, and
unsupported nodes/geometries, and groups eligible geometries by shared mesh
and compatible appearance state. Each source geometry contributes its world
transform to the batch's instance data. Before each draw, test its world bound
against the active culling planes without mutating the game's active-plane
mask, and upload only visible instance transforms. If no culling process or no
active planes are available, treat the geometry as visible, matching the
unculled rendering path. Batches that cannot safely use the common vertex
layout remain uninstanced.

Rendering uses Direct3D 9 indexed geometry instancing: the source mesh is
bound as geometry data, the instance transform buffer is bound as per-instance
data, and `SetStreamSourceFreq` selects indexed-data and instance-data
frequencies for the draw. The shader applies the per-instance transform and
view-projection transform, then samples the batch diffuse texture and
vertex color with alpha cutout behavior.

## Oblivion render integration

Use the existing `RenderObject` hook at the main `WorldSceneGraph` traversal.
When `InstanceFarGeometry` is disabled, leave the original render path
unchanged. When enabled:

1. Locate the distant-LOD root and lazily create or refresh its batches.
2. Temporarily set the app-culled flag on eligible source geometries only,
   preserving each original flag value.
3. Run the game's normal `RenderObject` traversal.
4. Render the instance batches against the active scene depth buffer.
5. Restore the original app-culled flags on every exit path.

Unsupported or unbatched source geometries are never hidden from the normal
renderer. The custom pass must restore all altered D3D state, including shader,
texture, vertex declaration, stream bindings, stream frequencies, and render
states, so subsequent engine rendering remains unaffected.

## Cache lifetime and failures

Cache batches by root and current worldspace. Invalidate resources when the
distant-LOD root or worldspace changes, and provide explicit invalidation for
callers that mutate a cached hierarchy. Release manager-created resources and
any retained Direct3D COM references from invalidation/clear operations. Do not
take ownership of the game's geometry buffers or NiNode hierarchy.

If shader loading, batch construction, or resource creation fails, report the
failure through repository-standard logging and do not suppress the affected
geometry from the vanilla renderer. An unexpected draw failure must be logged
and disable that batch for subsequent frames so the source geometry returns to
the vanilla path. All temporary source flags and D3D state must be restored
even when a batch fails.

## Shader assets

Add one vertex shader and one pixel shader source under
`Extra/Shaders/OblivionReloaded/Shaders`, following the existing
`.vso.hlsl`/`.pso.hlsl` naming and `ShaderRecord::LoadShader` compilation flow.
Both shaders target shader model 3. Treat the `InstanceLOD` pair as built-in
manager shaders: load them with the manager without a separate shader toggle,
and exempt only their exact names from the loader's optional `Shaders.Extra`
filter. `InstanceFarGeometry` continues to control whether the LOD instance
render path is used. No per-material shader variants are in scope.

## Validation

- Build the Oblivion project and confirm the new manager files are part of the
  target.
- Confirm both shaders load/compile as `vs_3_0` and `ps_3_0`.
- Exercise a distant-LOD node with repeated compatible meshes, unique meshes,
  alpha-cutout textures, and unsupported/skinned geometry.
- Verify that the setting-off path is unchanged, setting-on geometry is not
  double-rendered, and vanilla geometry remains visible when batch creation
  fails.
- Verify stream frequencies, stream bindings, shaders, textures, and culling
  flags are restored after rendering and after a reported failure; confirm
  off-frustum instances are not submitted and active culling-plane state is
  unchanged.
- Verify cached resources are released and rebuilt across worldspace/root
  changes.
- A runtime smoke test requires the Windows Oblivion environment; source and
  project validation should still be run where that environment is unavailable.
