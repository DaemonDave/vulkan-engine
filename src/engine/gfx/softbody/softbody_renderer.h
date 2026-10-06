#ifndef SRC_GAME_SOFTBODY_SOFTBODY_RENDERER_H
#define SRC_GAME_SOFTBODY_SOFTBODY_RENDERER_H

#include "gfx/gfx_types.h"

#include "softbody.h"

#include "engine/types.h"

typedef Handle SoftbodyRenderer;

struct Frame;


SoftbodyRenderer  softbody_renderer_create (void);
void              softbody_renderer_destroy(SoftbodyRenderer*);

void softbody_geometry_prepare(
		SoftbodyRenderer handle, 
		struct SBMesh *restrict mesh);

void softbody_geometry_update(
		SoftbodyRenderer handle,
		struct SBMesh *restrict mesh, 
		struct Frame *restrict frame);


void softbody_renderer_draw(SoftbodyRenderer, struct Frame*);
void softbody_renderer_draw_shadowmap(
	SoftbodyRenderer handle,
	struct Frame *frame);

#endif /* SRC_GAME_SOFTBODY_SOFTBODY_RENDERER_H */
