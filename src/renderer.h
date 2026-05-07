#ifndef RENDERER_H
#define RENDERER_H

#include <stdbool.h>

bool renderer_init(void);
void renderer_begin_frame(void);
void renderer_draw_scene(void);
void renderer_end_frame(void);
void renderer_shutdown(void);

#endif
