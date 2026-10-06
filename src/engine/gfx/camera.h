#ifndef SRC_ENGINE_GFX_CAMERA_H
#define SRC_ENGINE_GFX_CAMERA_H

#define CGLM_FORCE_DEPTH_ZERO_TO_ONE
#include <cglm/cglm.h>

struct Camera {

	mat4 projection;

	mat4 view_rotation;
	mat4 view_translation;
	mat4 view;

};

#endif /* SRC_ENGINE_GFX_CAMERA_H */
