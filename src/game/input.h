#ifndef SRC_GAME_INPUT_H
#define SRC_GAME_INPUT_H

#include "common.h"
#include "win/win.h"

int   input_init(void);
void  input_cursor_unlock(void);
void  input_cursor_lock(void);
void  input_cursor_delta(double *x, double *y);
void  input_cursor_pos( double *x, double *y );
bool  input_getkey(int key);
float*input_vector(void);

#endif /* SRC_GAME_INPUT_H */
