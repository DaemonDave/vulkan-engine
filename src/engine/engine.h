#ifndef SRC_ENGINE_ENGINE_H
#define SRC_ENGINE_ENGINE_H

#include <stdint.h>

#include "frame.h"
#include "gfx/gfx_types.h"
#include "gfx/camera.h"


void engine_init(void);
void engine_destroy(void);
void engine_tick(void);

void engine_wait_idle(void);



struct Frame * frame_begin(void);

void frame_end(struct Frame *);

void _engine_crash(const char*, const char*, const char*, int);
#define engine_crash(msg) (_engine_crash)(msg, __FILE__, __func__, __LINE__)

#endif /* SRC_ENGINE_ENGINE_H */
