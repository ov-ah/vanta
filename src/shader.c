#include "shader.h"
#include "util.h"

#include <stdio.h>
#include <stdlib.h>

bool shader_compile(Shader *shader, const char *path, GLenum type)
{
	char *src = read_file(path);
	if (!src)
	{
		fprintf(stderr, "shader: could not read file %s\n", path);
		return false;
	}

	shader->id = glCreateShader(type);
	shader->type = type;
	glShaderSource(shader->id, 1, (const char **)&src, NULL);
	glCompileShader(shader->id);
	free(src);

	int success;
	glGetShaderiv(shader->id, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		char logBuf[512];
		glGetShaderInfoLog(shader->id, sizeof(logBuf), NULL, logBuf);
		fprintf(stderr, "shader: could not compile shader - %s\n", logBuf);
		shader_destroy(shader);
		return false;
	}
	return true;
}

void shader_destroy(Shader *shader)
{
	glDeleteShader(shader->id);
	shader->id = 0;
}

bool shader_program_link(ShaderProgram *program, Shader *shaders, int count)
{
	program->id = glCreateProgram();
	for (int i = 0; i < count; i++)
		glAttachShader(program->id, shaders[i].id);

	glLinkProgram(program->id);

	int success;
	glGetProgramiv(program->id, GL_LINK_STATUS, &success);
	if (!success)
	{
		char logBuf[512];
		glGetProgramInfoLog(program->id, sizeof(logBuf), NULL, logBuf);
		fprintf(stderr, "shader: could not link shader program - %s\n", logBuf);
		shader_program_destroy(program);
		return false;
	}
	return true;
}

void shader_program_bind(const ShaderProgram *program)
{
	glUseProgram(program->id);
}

void shader_program_destroy(ShaderProgram *program)
{
	glDeleteProgram(program->id);
	program->id = 0;
}
