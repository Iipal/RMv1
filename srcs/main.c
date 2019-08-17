#include "rmv1.h"

__v4df	ro = { 0.0, 0.0, -5.0, 0.0 };
__v4df	rd = { 0.0, 0.0, 1.0, 1.0 };

__v4df	s = { 0.0, 0.0, 0.0, 0.0 };
float_t	sr = 1.0f;

uint32_t	g_flags = 0U;

/*
 * p: arbitrary point in 3D space
 * c: sphere center
 * r: sphere radius
 *
 * SDF(Signed Distance Function), return value means point 'p' is:
 *  negative: inside sphere.
 *  positive: outside sphere.
 *  zero:     on the sphere surface.
 */
float_t	dst_from_sphere(__v4df const p, __v4df const c, float_t const r)
{
	return v_len(p - c) - r;
}

Color	ray_march(void)
{
	float_t	total_dist	= 0.0f;

	for (size_t i = 0; NUM_OF_STEPS > i; ++i) {
		__v4df	curr_pos = ro + total_dist * rd;

		float_t	dist_to_closest = dst_from_sphere(curr_pos, s, sr);

		if (MIN_HIT_DIST > dist_to_closest)
			return (Color){ .c = { 255, 128, 0 } };

		if (MAX_TRACE_DIST < total_dist)
			break ;

		total_dist += dist_to_closest;
	}
	return (Color){ 0x0 };
}

static void	render_ray_march(Sdl *restrict const sdl)
{
	__v2df	i;
	for (Y(i) = CANVAS_STARTY; CANVAS_ENDY > Y(i); Y(i)++) {
		for (X(i) = CANVAS_STARTX; CANVAS_ENDX > X(i); X(i)++) {
			__v2df	uv = { Y(i) / 1000.0, X(i) / 1000.0 };
			rd = (__v4df){X(uv), Y(uv), 1.0, 0.0};
			Color	pxl = ray_march();
			if (pxl.hex)
				sdl_pixelput(sdl->wsurf,
					CONVERT_FROM_CANVAS(X(i), Y(i), WIN_X, WIN_Y), pxl);
		}
	}
}

static inline void	key_press(SDL_Keycode const key)
{
	if (SDLK_z == key)
		TOGGLE_BIT(g_flags, OUT_FPS_COUNTER);
}

static inline void	fps_counter(Time *const fps)
{
	fps->old = fps->current;
	fps->current = SDL_GetTicks();
	fps->res = (fps->current - fps->old) / 1000.0f;
}

static void	render_loop(Environment *restrict const env)
{
	bool		quit = false;
	Sdl *const	sdl = env->sdl;

	while (!quit)
	{
		while (0 < SDL_PollEvent(&sdl->e))
			if (SDL_QUIT == sdl->e.type)
				quit = true;
			else if (SDL_KEYDOWN == sdl->e.type)
			{
				if (SDLK_ESCAPE == sdl->e.key.keysym.sym)
					quit = true;
				else
					key_press(sdl->e.key.keysym.sym);
			}
		SDL_FillRect(sdl->wsurf, NULL, 0xfaf4f2);
		render_ray_march(sdl);
		SDL_UpdateWindowSurface(sdl->w);
		if (IS_BIT(g_flags, OUT_FPS_COUNTER))
			printf("ms: %.4f\n", env->fps.res);
		fps_counter(&env->fps);
	}
}

int	main(void)
{
	Environment	*env = calloc(1, sizeof(*env));
	env->sdl = calloc(1, sizeof(*env->sdl));
	if (!sdl_init(env->sdl, WIN_X, WIN_Y, "Ray Marching"))
		return -1;
	render_loop(env);
	sdl_free(&env->sdl);
	free(env->sdl);
	free(env);
}
