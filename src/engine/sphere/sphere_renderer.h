#ifndef SRC_ENGINE_SPHERE_SPHERE_RENDERER_H
#define SRC_ENGINE_SPHERE_SPHERE_RENDERER_H

#include "gfx/gfx.h"
#include "gfx/gfx_types.h"
#include "gfx/vk_util.h"

#include "common.h"
#include "res/res.h"
#include "event/event.h"
#include "handle/handle.h"

#include "icosphere.h"

typedef Handle SphereRenderer;

SphereRenderer 
sphere_renderer_create(void);

void 
sphere_renderer_destroy(
	SphereRenderer*);

void
sphere_renderer_draw(
	SphereRenderer, 
	struct Frame*);

void
sphere_renderer_add(
	SphereRenderer,
	float    c[3],
	float    r,
	uint32_t color
);

#endif /* SRC_ENGINE_SPHERE_SPHERE_RENDERER_H */
