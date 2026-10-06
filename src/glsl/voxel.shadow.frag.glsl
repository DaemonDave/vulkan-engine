#version 450

#define TREE_MAX_LEVELS 32


layout(set=0, binding=0) uniform Scene {
    mat4 matrix; // matches your .vert.shadow.glsl (not required here)
    vec3 dir;     // ray direction toward the light (assumed)
} light;

struct GlobalTreeGPU {
    uint root;
    uint bitw;        // CPU uses (bitw + 1) levels
    uint tree_total;

    uint tree_start[TREE_MAX_LEVELS];
    uint tree_count[TREE_MAX_LEVELS + 1];
    uint tree_bitw[TREE_MAX_LEVELS + 1];
};

layout(set=0, binding=1, std430) readonly buffer TreeMeta {
    GlobalTreeGPU meta;
};

layout(set=0, binding=2, std430) readonly buffer TreeFlat {
    uint tree_flat[];
};

// Must be written by vertex shader.
layout(location=0) in vec3 v_worldPos;

// Output: 1 = lit, 0 = fully shadowed
layout(location=0) out float outShadow;

// ---------- You MUST implement the same mapping your CPU uses ----------
// Convert world position to voxel-space [0, 1)^3 for your grid.
// Replace this with your real bounds transform.
vec3 worldToVoxel01(vec3 worldPos)
{
    // Placeholder: identity + clamp. Replace!
    return clamp(worldPos, vec3(0.0), vec3(0.999999));
}

// Slab test for [0,1]^3
bool intersectUnitCube(vec3 ro, vec3 rd, out float tEnter, out float tExit)
{
    vec3 invRd = 1.0 / rd;

    vec3 t0 = (vec3(0.0) - ro) * invRd;
    vec3 t1 = (vec3(1.0) - ro) * invRd;

    vec3 tmin = min(t0, t1);
    vec3 tmax = max(t0, t1);

    tEnter = max(max(tmin.x, tmin.y), tmin.z);
    tExit  = min(min(tmax.x, tmax.y), tmax.z);

    return tExit >= max(tEnter, 0.0);
}

uint kLevel0(uvec3 cell, uint b0)
{
    // Matches your CPU:
    // k = (z << b0 | y); k = (k << b0) | x;
    uint x = cell.x;
    uint y = cell.y;
    uint z = cell.z;
    uint k = (z << b0) | y;
    k = (k << b0) | x;
    return k;
}

void main()
{
    vec3 rd = normalize(light.dir);
    vec3 ro = v_worldPos;

    // Map ray origin to voxel-space [0,1)^3
    vec3 ro01 = worldToVoxel01(ro);

    float tEnter, tExit;
    if (!intersectUnitCube(ro01, rd, tEnter, tExit)) {
        outShadow = 1.0;
        return;
    }

    // ---- Level-0 parameters ----
    // Your CPU code uses (1u<<9) and suggests b0=3 for 8 cells (since 1u<<9 == 512 is scale).
    // But you can compute b0 from meta.tree_bitw or hardcode if you know it.
    // We'll hardcode b0=3 for now; change to your real value.
    const uint h = 0u;

    // Best: derive b0 from meta.tree_bitw[h] if it matches your CPU b0.
    // If meta.tree_bitw[0] is NOT b0, replace this line.
    uint b0 = meta.tree_bitw[h]; // expected: b0 such that N = 2^b0
    uint N0 = 1u << b0;

    // Ray marching
    // Step size: choose something stable. For level-0, a step of ~1/N0 is reasonable.
    float dt = 1.0 / float(N0) * 0.75;

    float t = max(tEnter, 0.0);

    float shadow = 1.0;

    // Limit steps to avoid loops with huge spans
    const int MAX_STEPS = 128;

    for (int step = 0; step < MAX_STEPS; ++step) {
        if (t > tExit) break;

        vec3 p01 = ro01 + rd * t;

        // Convert p01 to integer cell index in [0, N0-1]
        // Use min to avoid N0 from floating precision.
        uvec3 cell = uvec3(
            min(uint(floor(p01.x * float(N0))), N0 - 1u),
            min(uint(floor(p01.y * float(N0))), N0 - 1u),
            min(uint(floor(p01.z * float(N0))), N0 - 1u)
        );

        uint k = kLevel0(cell, b0);

        // Look up packed voxel at level 0:
        uint base = meta.tree_start[0];
        uint v = tree_flat[base + k];

        // Solid? (You may need to change this if Voxel encodes density.)
        if (v != 0u) {
            shadow = 0.0;
            break;
        }

        t += dt;
    }

    outShadow = shadow;
}
