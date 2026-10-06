#ifndef SRC_ENGINE_WIN_WIN_H
#define SRC_ENGINE_WIN_WIN_H

#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>

#include "common.h"

int win_init();
void win_destroy();
bool win_should_close(void);
void win_close(void);

GLFWwindow *win_get();

#endif /* SRC_ENGINE_WIN_WIN_H */
