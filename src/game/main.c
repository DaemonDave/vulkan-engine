#include "engine/engine.h"
#include "engine/win/win.h"
#include "engine/log/log.h"
#include "engine/gfx/gfx.h"
#include "engine/gfx/camera.h"
#include "teapot/teapot.h"

#include "engine/util/ppm.h"

#include "engine/mem/mem.h"
#include "engine/mem/arr.h"

#include "input.h"
#include "freecam.h"


#include "softbody/softbody.h"
#include <limits.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>


#include "frame.h"

#ifndef WIDGET_RENDERER_H
#include "engine/widget/widget_renderer_helper.h"
#endif

extern struct VkEngine vk;

#define HEAP_MEGABYTES 1024

#ifdef NDEBUG
	#define BUILD_VERSION "Build: " __DATE__" rel\n" 
#else
	#define BUILD_VERSION "Build: " __DATE__" debug\n" 
#endif

void mem_error(enum MEM_ERROR err)
{
	engine_crash("Memory error");
}

int main(int argc, char**argv)
{
	mem_init( HEAP_MEGABYTES * 1024*(size_t)1024 );
	mem_set_error_callback(mem_error);
	log_info("Hello Vulkan!");
	

	engine_init();
	input_init();


	uint32_t teagfx = gfx_teapot_renderer_create();
	softbody_create();

	uint32_t frames = 0;
	uint32_t fps_max = 300;
	uint32_t fps = 0;
	double   last_title = 0.0;
	double   last = 0;
	double   sleep = 0;

	static struct Freecam freecam = {
		.fov = 90.0,
		.pos = {
			0, 2, 1
		}
	};

	while (!win_should_close()) 
	{
		// Frame data passed into fcns
		struct Frame *frame = frame_begin();
		uint32_t frame_slot = vk.current_frame;		
		VkFrame *vk_frame = frame->vk;
		
		///
		// 
		///
		double now   = glfwGetTime();
		double delta = now - last; 
		last = now;

		if (last_title + 1.0 < now) 
		{
			fps = frames;
			frames = 0;
			last_title += 1.0;

		}

		/* Text stuff */
		char print[4096];
		snprintf(print, sizeof(print), 
			"FPS: %i/%i, d %.2fms\n"
			"Device: %s\n"
			BUILD_VERSION
			"%.2f MB / %i MB\n"
			"[%.2f, %.2f, %.2f], [%.1f, %.1f], [%.1f]\n"
			"[%.2f, %.2f, %.2f]\n",
			fps, fps_max, (delta)*1000.0,
			vk.dev_name,
			mem_used() / 1024.0f / 1024.0f,  HEAP_MEGABYTES,
			freecam.pos[0], freecam.pos[1], freecam.pos[2], 
			freecam.yaw, freecam.pitch,
			freecam.fov,
			freecam.dir[0], freecam.dir[1], freecam.dir[2]
		);


		/* Camera stuff */
		freecam_update(&freecam, delta);
		freecam_to_camera(&freecam, &frame->camera);

		glm_perspective(
			glm_rad(freecam.fov),
			frame->width / (float) frame->height,
			0.01f, 100.0f,
			frame->camera.projection
		);

		frame->camera.projection[1][1] *= -1; 

		/* Render stuff */
		/*
		 * Build Nuklear's UI commands before rendering them.
		 * This calls nk_glfw3_new_frame() and creates the Nuklear
		 * draw command list.
		 */
		WidgetRendererBuildWidgets();

		/*
		 * Upload the UI vertex/index data for this frame here, if
		 * your renderer requires an explicit upload step.
		 */
		/*
		 * 2. Convert Nuklear commands to CPU-side vertex/index data
		 *    and upload them into this frame slot's Vulkan buffers.
		 */
		WidgetRendererUpdate(frame);


		//term_update(frame);


		softbody_update(frame, &freecam);
		softbody_predraw(frame, &freecam);

		/// Pre VULKAN RENDER LOOP GEOMETRY UPDATES GO ABOVE HERE
		/*
		 * 3. Record the render pass and draw commands.
		 */
		gfx_frame_mainpass_begin(frame->vk);

		softbody_draw(frame, &freecam);



		gfx_teapot_draw(frame);
		
		// GUI DRAWS LAST SO IT DOESN'T GET OVERWRITTEN
		/* Nuklear must draw while the render pass is active */
		widget_renderer_draw();		

		gfx_frame_mainpass_end(frame->vk);

		/* End stuff */
		frame_end(frame);
		// ALL GUI code moved to engine
		engine_tick();

		sleep = (1.0f/(float)fps_max) - (glfwGetTime()-now);
		if(sleep > 0.0) 
		{
			usleep(980*1000*sleep);
		}
		frames++;
	}


	engine_wait_idle();
	gfx_teapot_renderer_destroy(teagfx);

	engine_destroy();

	return 0;
}
