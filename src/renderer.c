#include "renderer.h"
#include "shader.h"

static GLuint vao, vbo;
static GLuint vertexCount;
static ShaderProgram shaderProgram;

bool renderer_init(void)
{
	float vertices[] = {-0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.5f, -0.5f, 0.0f,
	                    1.0f,  0.0f,  0.0f, 0.5f, 0.0f, 0.0f, 1.0f};
	vertexCount = 3;

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
	                      (void *)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
	                      (void *)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);

	Shader vert, frag;
	if (!shader_compile(&vert, "shaders/basic.vert", GL_VERTEX_SHADER))
		return false;
	if (!shader_compile(&frag, "shaders/basic.frag", GL_FRAGMENT_SHADER))
	{
		shader_destroy(&vert);
		return false;
	}

	Shader stages[] = {vert, frag};
	if (!shader_program_link(&shaderProgram, stages, 2))
	{
		shader_destroy(&vert);
		shader_destroy(&frag);
		return false;
	}

	shader_destroy(&vert);
	shader_destroy(&frag);
	return true;
}

void renderer_begin_frame(void)
{
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void renderer_draw_scene(void)
{
	shader_program_bind(&shaderProgram);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, vertexCount);
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
	shader_program_destroy(&shaderProgram);
}
