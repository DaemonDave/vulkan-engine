/* widget_renderer_api.h */

#ifndef WIDGET_RENDERER_API_H
#define WIDGET_RENDERER_API_H

#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>

struct nk_font_atlas;

void nk_glfw3_font_stash_begin(struct nk_font_atlas **atlas);
void nk_glfw3_font_stash_end(VkQueue graphics_queue);

void nk_glfw3_device_destroy(void);

void nk_glfw3_char_callback(GLFWwindow *win, unsigned int codepoint);

void nk_glfw3_key_callback(
    GLFWwindow *win,
    int key,
    int scancode,
    int action,
    int mods
);

void nk_gflw3_scroll_callback(
    GLFWwindow *win,
    double xoff,
    double yoff
);

void nk_glfw3_mouse_button_callback(
    GLFWwindow *win,
    int button,
    int action,
    int mods
);

#endif
