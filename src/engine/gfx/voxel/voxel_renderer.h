#ifndef SRC_GAME_VOXEL_VOXEL_RENDERER_H
#define SRC_GAME_VOXEL_VOXEL_RENDERER_H

#include <math.h>
#include <stdint.h>
#include <string.h>
#include <GLFW/glfw3.h>
#include <cglm/cglm.h>   // mat4, vec3, vec4 types + cglm helpers
#include <cglm/mat4.h>
#include <cglm/vec3.h>
#include "common.h"
#include "gfx/gfx_types.h"

// Optional: only include if your voxel code is defined in a header (use/remove as needed)
#include "voxel.h"

typedef Handle VoxelRenderer;

typedef struct VoxelTreeCPU VoxelTreeCPU;

VoxelRenderer voxel_renderer_create(void);
void           voxel_renderer_destroy(VoxelRenderer *);

// Upload/prepare CPU voxel dataset -> GPU SSBO (if you split prepare/update)
void voxel_dataset_prepare(VoxelRenderer handle /*, optional: CPU dataset params */);

// Per-update upload (your memcpy + vmaFlushAllocation)
void voxel_dataset_update(
    VoxelRenderer handle,
    const VoxelTreeCPU *restrict tree);

// Render the raymarch pass
void voxel_renderer_draw(VoxelRenderer handle, struct Frame *frame);

#endif /* SRC_GAME_VOXEL_VOXEL_RENDERER_H */
