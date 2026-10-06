#include "win/win.h"
#include "common.h"
#include "event/event.h"
#include "engine/gfx/gfx_types.h"
#include "engine/log/log.h"

void nk_glfw3_char_callback(GLFWwindow *win, unsigned int codepoint);
void nk_glfw3_key_callback(GLFWwindow *win, int key, int scancode, int action, int mods);
void nk_glfw3_scroll_callback(GLFWwindow *win, double xoff, double yoff);
void nk_glfw3_mouse_button_callback(GLFWwindow *win, int button, int action, int mods);

extern struct VkEngine vk;

static void win_resize_callback(GLFWwindow *window, int w, int h)
{
	event_fire(EVENT_WIN_RESIZE, NULL);
}

#ifndef NDEBUG
void
log_win_init_config(void)
{
    log_info("Window initialization configuration:");

    log_info("  %-32s = %d",
             "GLFW_CLIENT_API",
             GLFW_NO_API);

    log_info("  %-32s = %d",
             "GLFW_RESIZABLE",
             GLFW_TRUE);

    log_info("  %-32s = %d",
             "window_width",
             1200);

    log_info("  %-32s = %d",
             "window_height",
             900);

    log_info("  %-32s = %s",
             "window_title",
             "VulkanEngine1");

    LOG_POINTER("monitor", glfwGetPrimaryMonitor());
    LOG_POINTER("share", NULL);

    LOG_POINTER("window_user_pointer",
                &vk.widget_renderer);

    LOG_POINTER("framebuffer_size_callback",
                (void *)win_resize_callback);

    LOG_POINTER("char_callback",
                (void *)nk_glfw3_char_callback);

    LOG_POINTER("key_callback",
                (void *)nk_glfw3_key_callback);

    LOG_POINTER("scroll_callback",
                (void *)nk_glfw3_scroll_callback);
}
#endif


int win_init(void)
{
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE,  GLFW_TRUE);
	// VkEngine owns window, VkEngine points at widget_renderer
	vk.window = glfwCreateWindow(1200,900,"VulkanEngine1",glfwGetPrimaryMonitor(),NULL);
	glfwSetFramebufferSizeCallback(vk.window, win_resize_callback);

	//! DRE 2026 Window 
	glfwSetWindowUserPointer(vk.window, &vk.widget_renderer);

	glfwSetCharCallback(vk.window, nk_glfw3_char_callback);
	glfwSetKeyCallback(vk.window, nk_glfw3_key_callback);
	glfwSetScrollCallback(vk.window, nk_glfw3_scroll_callback);	
	
    #ifndef NDEBUG
    log_win_init_config();
    #endif
    

	return 0;
}

void win_destroy(void)
{
	glfwDestroyWindow(vk.window);
}

bool win_should_close(void)
{
	return glfwWindowShouldClose(vk.window);
}

void win_close(void)
{
	glfwSetWindowShouldClose(vk.window, GLFW_TRUE);
}

GLFWwindow * win_get(void)
{
	return vk.window;
}


