#include "shader.h"
#include "util.h"

bool shader_load(Shader *shader, char *vertPath, char *fragPath)
{
	char *vertSource = read_file(vertPath);
	if (!vertSource)
	{
		fprintf(stderr, "shader: vertex shader source not found at %s\n",
		        vertPath);
		return false;
	}

	char *fragSource = read_file(fragPath);
	if (!fragSource)
	{
		fprintf(stderr, "shader: fragment shader source not found at %s\n",
		        fragPath);
		return false;
	}
	int success;
	char infoBuf[512];

	unsigned int vertShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertShader, 1, (const char **)&vertSource, NULL);
	glCompileShader(vertShader);
	glGetShaderiv(vertShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertShader, 512, NULL, infoBuf);
		fprintf(stderr, "shader: vertex shader compile error - %s\n", infoBuf);
		return false;
	}

	unsigned int fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragShader, 1, (const char **)&fragSource, NULL);
	glCompileShader(fragShader);
	glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragShader, 512, NULL, infoBuf);
		fprintf(stderr, "shader: fragment shader compile error - %s\n",
		        infoBuf);
		return false;
	}

	shader->program = glCreateProgram();
	glAttachShader(shader->program, vertShader);
	glAttachShader(shader->program, fragShader);
	glLinkProgram(shader->program);
	glGetProgramiv(shader->program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shader->program, 512, NULL, infoBuf);
		fprintf(stderr, "shader: shader program link error - %s\n", infoBuf);
		return false;
	}
	free(vertSource);
	free(fragSource);
	return true;
}

void shader_bind(const Shader *shader) { glUseProgram(shader->program); }

void shader_destroy(const Shader *shader) { glDeleteProgram(shader->program); }
