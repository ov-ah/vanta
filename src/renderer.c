#include "renderer.h"
#include "shader.h"

static GLuint vao, vbo;
static GLuint vertex_count;
static Shader shader;

bool renderer_init(void)
{
	float vertices[] = {
	    -0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f,
	};
	vertex_count = 3;

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	if (!shader_load(&shader, "shaders/basic.vert", "shaders/basic.frag"))
		return false;
	return true;
}

void renderer_begin_frame(void)
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void renderer_draw_scene(void)
{
	shader_bind(&shader);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0);
}

void renderer_end_frame(void)
{
	// placeholder, ppfx, ui, etc.
}

void renderer_shutdown(void)
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	shader_destroy(&shader);
}
