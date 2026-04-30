#include <stdio.h>
#include <stdlib.h>

#include "renderer.h"
#include "window.h"

int main(void)
{
	Window window;
	if (!window_create(&window, 1280, 720, "vanta"))
	{
		fprintf(stderr, "main: failed to create window\n");
		return EXIT_FAILURE;
	}

	if (!renderer_init())
	{
		fprintf(stderr, "main: failed to intialize renderer\n");
		window_destroy(&window);
		return EXIT_FAILURE;
	}
	/*
	Camera camera;
	camera_init(&camera, 1280.0f / 720.0f);
	*/

	// double last_time = window_get_time();
	while (!window_should_close(&window))
	{
		// double now = window_get_time();
		// float dt = (float)(now - last_time);
		// last_time = now

		window_input_poll(); // why don't we need a window pointer! i love glfw!
		// camera_update(&camera, dt);

		renderer_begin_frame();
		renderer_draw_scene();
		renderer_end_frame();

		window_swap_buffer(&window);
	}

	return EXIT_SUCCESS;
}
