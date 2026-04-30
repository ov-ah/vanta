#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <stdbool.h>

typedef struct
{
	GLuint program;
} Shader;

bool shader_load(Shader *shader, const char *vert_path, const char *frag_path);
void shader_bind(const Shader *shader);
void shader_destroy(const Shader *shader);

#endif
