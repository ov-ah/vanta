#include "renderer.h"
#include "shader.h"

static GLuint vao, vbo, ebo;
static GLuint vertexCount;
static ShaderProgram shaderProgram;

static void renderer_cleanup_buffers(void)
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	vao = vbo = 0;
}

bool renderer_init(void)
{
	// https://open.gl/drawing
	float vertices[] = {
	    -0.5f, 0.5f,  1.0f, 0.0f, 0.0f, // Top-left
	    0.5f,  0.5f,  0.0f, 1.0f, 0.0f, // Top-right
	    0.5f,  -0.5f, 0.0f, 0.0f, 1.0f, // Bottom-right
	    -0.5f, -0.5f, 1.0f, 1.0f, 1.0f  // Bottom-left
	};

	GLuint elements[] = {
	    0, 1, 2, // 1
	    2, 3, 0  // 2
	};

	vertexCount = 3;

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements,
	             GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
	                      (void *)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
	                      (void *)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);

	Shader vert, frag;
	if (!shader_compile(&vert, "shaders/basic.vert", GL_VERTEX_SHADER))
	{
		renderer_cleanup_buffers();
		return false;
	}
	if (!shader_compile(&frag, "shaders/basic.frag", GL_FRAGMENT_SHADER))
	{
		shader_destroy(&vert);
		renderer_cleanup_buffers();
		return false;
	}

	Shader stages[] = {vert, frag};
	if (!shader_program_link(&shaderProgram, stages, 2))
	{
		shader_destroy(&vert);
		shader_destroy(&frag);
		renderer_cleanup_buffers();
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
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void renderer_end_frame(void)
{
	// placeholder, ppfx, ui, etc.
}

void renderer_shutdown(void)
{
	renderer_cleanup_buffers();
	shader_program_destroy(&shaderProgram);
}
