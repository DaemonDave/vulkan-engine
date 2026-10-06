#ifndef SRC_ENGINE_GFX_GFX_H
#define SRC_ENGINE_GFX_GFX_H

#include "gfx_types.h"

void gfx_init(void);
void gfx_destroy(void);
void gfx_tick(void);

VkFrame * gfx_frame_get(void);

void 
gfx_frame_submit(VkFrame *);

//
bool gfx_loop(struct Frame *frame, uint32_t frame_slot);

void gfx_frame_mainpass_begin( VkFrame *frame);
void gfx_frame_mainpass_end( VkFrame *frame);

void gfx_wait_idle(void);

void gfx_get_swapchain_extents(int * width, int * height);

#endif /* SRC_ENGINE_GFX_GFX_H */
