#ifndef SRC_GAME_SOFTBODY_WIREFRAME_RENDERER_H
#define SRC_GAME_SOFTBODY_WIREFRAME_RENDERER_H

#include "../../engine/types.h"
#include "gfx/gfx_types.h"

typedef Handle WireframeRenderer;

struct Frame;

WireframeRenderer 
wireframe_renderer_create(void);

void 
wireframe_renderer_destroy(
	WireframeRenderer*);

void
wireframe_renderer_draw(
	WireframeRenderer, 
	struct Frame*);


void
wireframe_line(
	WireframeRenderer,
	float p1[3],
	float p2[3],
	uint32_t color
);

void
wireframe_triangle(
	WireframeRenderer,
	float p1[3],
	float p2[3],
	float p3[3],
	uint32_t color
);

#endif /* SRC_GAME_SOFTBODY_WIREFRAME_RENDERER_H */
