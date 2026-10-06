#ifndef SRC_GAME_FREECAM_H
#define SRC_GAME_FREECAM_H

#include "gfx/camera.h"

struct Freecam {
	float yaw;
	float pitch;
	float dir[3];
	float pos[3];
	float fov;
};

void freecam_update(struct Freecam *, double delta);
void freecam_to_camera(struct Freecam *, struct Camera *);

#endif /* SRC_GAME_FREECAM_H */
