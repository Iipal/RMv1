#ifndef RMV1_H
# define RMV1_H

# include <stdio.h>
# include <sys/types.h>

# include "libvectors.h"
# include "libftsdl.h"

# define NUM_OF_STEPS   5000
# define MIN_HIT_DIST   0.001
# define MAX_TRACE_DIST 1000.0

# define WIN_X 1000
# define WIN_Y 500

# define CANVAS_STARTX -(WIN_X / 2)
# define CANVAS_STARTY -(WIN_Y / 2)
# define CANVAS_ENDX   WIN_X / 2
# define CANVAS_ENDY   WIN_Y / 2

# define FROM_CANVAS(point, w_size) ((point) * (w_size) / (1000.0 * w_size))

# define STEP_SIZE 0.1f

extern __v4df	ro; /* represents Ray Origin */
extern __v4df	rd; /* represents Ray Direction */

extern __v4df	s; /* represents Sphere position */
extern float_t	sr; /* represents Sphere radius */

typedef struct	s_time
{
	float_t	old;
	float_t	current;
	float_t	res;
}	Time;

typedef struct	s_env
{
	Sdl		*sdl;
	Time	fps;
}	Environment;

extern uint32_t	g_flags;

# define OUT_FPS_COUNTER (1U << 0U)

# define SET_BIT(mask, bit) ((mask) |= (bit))
# define UNSET_BIT(mask, bit) ((mask) &= ~(bit))
# define TOGGLE_BIT(mask, bit) ((mask) ^= (bit))

# define IS_BIT(mask, bit) ((mask) & (bit))

#endif
