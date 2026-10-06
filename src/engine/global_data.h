#ifndef SRC_ENGINE_GLOBAL_DATA_H
#define SRC_ENGINE_GLOBAL_DATA_H

#include <stdint.h>

#define BATCH 16

typedef uint32_t Voxel;

typedef struct GlobalCameraUBO
{
    // Keep alignment-friendly ordering. Typical std140 rules apply to UBOs.
    // invViewProj is 16 floats (64 bytes). camPos is 3 floats + padding.
    float invViewProj[16]; // mat4
    float camPos[3];
    float _pad0;
} GlobalCameraUBO;

// Matches ModelUBO { mat4 invModel; } in shaders
typedef struct GlobalModelUBO
{
    float invModel[16]; // mat4
} GlobalModelUBO;

// Matches DatasetSSBO in shaders (std430 layout).
typedef struct GlobalDatasetSSBO
{
    uint32_t root;
    uint32_t leaf_count;
    uint32_t b;
    uint32_t enabledMask;

    uint32_t xs[BATCH];
    uint32_t ys[BATCH];
    uint32_t zs[BATCH];

    Voxel vals[BATCH]; // Voxel == uint32_t
} GlobalDatasetSSBO;

#endif /* SRC_ENGINE_GLOBAL_DATA_H */
