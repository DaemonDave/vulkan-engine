#ifndef SRC_ENGINE_SPHERE_ICOSAHEDRON_H
#define SRC_ENGINE_SPHERE_ICOSAHEDRON_H

#include <stddef.h>
#include <stdint.h>

void icosahedron_vertex(float**out, size_t *count);
void icosahedron_index(uint16_t**out, size_t *count);

#endif /* SRC_ENGINE_SPHERE_ICOSAHEDRON_H */
