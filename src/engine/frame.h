#ifndef SRC_ENGINE_FRAME_H
#define SRC_ENGINE_FRAME_H

#include <stdint.h>

#include "gfx/camera.h"

struct VkFrame;

struct Frame {
    struct Camera camera;

    double delta;
    struct VkFrame *vk;

    uint32_t width;
    uint32_t height;
};

#endif /* SRC_ENGINE_FRAME_H */
