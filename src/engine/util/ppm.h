#ifndef SRC_ENGINE_UTIL_PPM_H
#define SRC_ENGINE_UTIL_PPM_H

void gfx_util_write_ppm(
	const int width, 
	const int height, 
	unsigned char *buffer, 
	char *filename
);

#endif /* SRC_ENGINE_UTIL_PPM_H */
