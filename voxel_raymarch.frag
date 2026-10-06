#version 460

layout(location = 0) in vec2 vUV;
layout(location = 0) out vec4 outColor;

// Camera with inverse view-projection (to reconstruct world ray)
layout(set = 0, binding = 0) uniform CameraUBO {
    mat4 invViewProj; // inverse(view * proj)
    vec3 camPos;      // world-space camera position
    float _pad0;
} cam;

// Model transform: we need inverse model to raycast in dataset local space
layout(set = 0, binding = 2) uniform ModelUBO {
    mat4 invModel; // inverse(model)
} model;

// Match your C struct layout using std430 and explicit uint arrays
layout(std430, set = 0, binding = 1) buffer DatasetSSBO {
    uint root;
    uint leaf_count;
    uint b;
    uint enabledMask;
    uint xs[16];
    uint ys[16];
    uint zs[16];
    uint vals[16]; // Voxel == uint32_t
} ds;

// ---- Helpers ----
bool intersectUnitCube(vec3 ro, vec3 rd, out float tEnter, out float tExit)
{
    vec3 invRd = 1.0 / rd;
    vec3 t0 = (vec3(0.0) - ro) * invRd;
    vec3 t1 = (vec3(1.0) - ro) * invRd;
    vec3 tMin = min(t0, t1);
    vec3 tMax = max(t0, t1);
    tEnter = max(max(tMin.x, tMin.y), tMin.z);
    tExit  = min(min(tMax.x, tMax.y), tMax.z);
    return tExit >= max(tEnter, 0.0);
}

ivec3 pToLeafCoord(vec3 p01)
{
    // ds.root is the leaf axis resolution per your CPU pattern (lane % root etc.)
    uint r = ds.root;
    vec3 q = clamp(p01, 0.0, 0.99999994); // avoid p==1.0
    vec3 scaled = q * float(r);
    return ivec3(scaled);
}

bool findVoxelAt(ivec3 c, out uint payload)
{
    // Scan 16 populated voxels
    for (uint i = 0u; i < 16u; ++i) {
        if (int(ds.xs[i]) == c.x &&
            int(ds.ys[i]) == c.y &&
            int(ds.zs[i]) == c.z)
        {
            payload = ds.vals[i];
            return true;
        }
    }
    payload = 0u;
    return false;
}

vec3 colorFromVoxel(uint u)
{
    // Use deterministic color mapping from the uint payload
    float r = float((u >> 16u) & 0xFFu) / 255.0;
    float g = float((u >>  8u) & 0xFFu) / 255.0;
    float b = float((u >>  0u) & 0xFFu) / 255.0;
    return vec3(r, g, b);
}

void main()
{
    // Reconstruct ray in WORLD space from screen UV
    vec2 ndc = vUV * 2.0 - 1.0;

    vec4 nearW = cam.invViewProj * vec4(ndc, 0.0, 1.0);
    vec4 farW  = cam.invViewProj * vec4(ndc, 1.0, 1.0);
    nearW /= nearW.w;
    farW  /= farW.w;

    vec3 roW = cam.camPos;
    vec3 rdW = normalize(farW.xyz - nearW.xyz);

    // Transform ray into DATASET (local/model) space
    vec3 ro = (model.invModel * vec4(roW, 1.0)).xyz;

    // For direction: ignore translation. Use invModel with w=0.
    vec3 rd = normalize((model.invModel * vec4(rdW, 0.0)).xyz);

    // Dataset local is assumed to occupy [0,1]^3
    float tEnter, tExit;
    if (!intersectUnitCube(ro, rd, tEnter, tExit)) {
        outColor = vec4(0.0);
        return;
    }

    uint r = ds.root;
    float step = 1.0 / float(r);

    float t = max(tEnter, 0.0) + 1e-4;
    uint maxSteps = r * 3u;

    bool hit = false;
    uint payload = 0u;

    for (uint s = 0u; s < maxSteps; ++s) {
        if (t > tExit) break;

        vec3 p01 = ro + rd * t; // local-space point in [0,1]^3 (ideally)
        if (any(lessThan(p01, vec3(0.0))) || any(greaterThan(p01, vec3(1.0)))) {
            t += step;
            continue;
        }

        ivec3 c = pToLeafCoord(p01);

        if (findVoxelAt(c, payload)) {
            hit = true;
            break;
        }

        t += step;
    }

    if (!hit) {
        outColor = vec4(0.0);
        return;
    }

    vec3 base = colorFromVoxel(payload);

    // Simple shading: fake light using a constant direction
    vec3 lightDir = normalize(vec3(0.3, 0.8, 0.4));
    float shade = 0.35 + 0.65 * max(dot(normalize(-rd), lightDir), 0.0);

    outColor = vec4(base * shade, 1.0);
}
