#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <stdbool.h>

typedef struct
{
	GLuint id;
	GLenum type;
} Shader;

typedef struct
{
	GLuint id;
} ShaderProgram;

bool shader_compile(Shader *shader, const char *path, GLenum type);
void shader_destroy(Shader *shader);

bool shader_program_link(ShaderProgram *program, Shader *shaders, int count);
void shader_program_bind(const ShaderProgram *program);
void shader_program_destroy(ShaderProgram *program);

#endif
