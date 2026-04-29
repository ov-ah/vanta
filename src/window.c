#include "window.h"
#include <stdio.h>

static void default_framebuffer_size_cb(GLFWwindow *handle, int w, int h)
{
	(void)handle;
	glViewport(0, 0, w, h);
}

bool window_create(Window *win, int width, int height, char *title)
{
	win->width = width;
	win->height = height;
	win->title = title;

	if (!glfwInit())
	{
		fprintf(stderr, "window: glfwInit() failed\n");
		return false;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	win->handle = glfwCreateWindow(width, height, title, NULL, NULL);
	if (!win->handle)
	{
		fprintf(stderr, "window: glfwCreateWindow() failed\n");
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(win->handle);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		fprintf(stderr, "window: gladLoadGLLoader() failed\n");
		glfwDestroyWindow(win->handle);
		glfwTerminate();
		return false;
	}
	glfwSetFramebufferSizeCallback(win->handle, default_framebuffer_size_cb);
	glfwSwapInterval(1);
	return true;
}

bool window_should_close(const Window *win)
{
	return glfwWindowShouldClose(win->handle);
}

void window_swap_buffer(const Window *win) { glfwSwapBuffers(win->handle); }

void window_input_poll() { glfwPollEvents(); }

void window_destroy(Window *win)
{
	if (win->handle)
	{
		glfwDestroyWindow(win->handle);
		win->handle = NULL;
	}
	glfwTerminate();
}
