#ifndef WINDOW_H
#define WINDOW_H

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <stdbool.h>

typedef struct GLFWwindow GLFWwindow;

typedef struct
{
	GLFWwindow *handle;
	int width, height;
	const char *title;
} Window;

bool window_create(Window *win, int width, int height, char *title);
bool window_should_close(const Window *win);
void window_swap_buffer(const Window *win);
void window_input_poll(void);
void window_destroy(Window *win);

void window_resize_callback(Window *win, GLFWframebuffersizefun cb);

#endif
