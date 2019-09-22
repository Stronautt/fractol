/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/29 14:46:02 by pgritsen          #+#    #+#             */
/*   Updated: 2017/12/30 16:13:46 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int					poll_event(t_env *env)
{
	SDL_Event	e;

	Uint8* keystate = SDL_GetKeyboardState(NULL);
	if (keystate[SDL_SCANCODE_D]) {
		env->wins->next->pivot.x += 0.01;
	} else if (keystate[SDL_SCANCODE_A]) {
		env->wins->next->pivot.x -= 0.01;
	} else if (keystate[SDL_SCANCODE_W]) {
		env->wins->next->pivot.y -= 0.01;
	} else if (keystate[SDL_SCANCODE_S]) {
		env->wins->next->pivot.y += 0.01;
	}

	while (SDL_PollEvent(&e))
		if (e.type == SDL_QUIT || e.window.event == SDL_WINDOWEVENT_CLOSE
			|| (e.type == SDL_KEYDOWN && e.key.keysym.sym == EXIT_KEY))
			return (0);
		// else if (e.window.event == SDL_WINDOWEVENT_RESIZED)
		// 	sgl_resize_window(e.window.windowID, e.window.data1,
		// 								e.window.data2);
		// else if (e.type == SDL_KEYDOWN)
		// 	trace_input(e.key, game);
		else if (e.type == SDL_KEYUP) {
			if (e.key.keysym.scancode == SDL_SCANCODE_D) {
				env->wins->next->pivot.x += 0.01;
			} else if (e.key.keysym.scancode == SDL_SCANCODE_A) {
				env->wins->next->pivot.x -= 0.01;
			} else if (e.key.keysym.scancode == SDL_SCANCODE_W) {
				env->wins->next->pivot.y -= 0.01;
			} else if (e.key.keysym.scancode == SDL_SCANCODE_S) {
				env->wins->next->pivot.y += 0.01;
			}
			// key_up(e, e.key.keysym.scancode, game);
		}
		// else if (e.type == SDL_MOUSEBUTTONDOWN && game->state == 0)
		// 	menu_mouse(e.button, game);
		// else if (e.type == SDL_MOUSEBUTTONDOWN && game->state == 1)
		// 	level_selector_mouse(e.button, game);
		// else if (e.type == SDL_MOUSEBUTTONDOWN && game->state == 3)
		// 	death_cam_mouse(e.button, game);
	return (1);
}

int		main(void)
{
	static t_env	env;
	t_window		*main;

	ft_make_draw_dependencies(&env);
	ft_make_environment(&env);
	main = ft_new_win(&env, MW_WIDTH, MW_HEIGHT, MANDELFRACT);
	ft_init_mandelfract(main);
	while (1)
	{
		ft_draw(env, main);
		// draw_deps[gd.state](win->surface, &gd);
		// expose_actions(gd);
		if (!poll_event(&env))
			return (0);
		// gd.state == 1 ? level_selector_mouse_hover(gd) : 0;
		// gd.move && gd.state == 2 ? move(&gd, gd.move * gd.mov_speed) : 0;
		// gd.rotate && gd.state == 2 ? rotate(&gd, gd.rotate * gd.rot_speed) : 0;
		SDL_UpdateWindowSurface(main->win_p);
		// sgl_vsync();
	}
	SDL_Quit();
	return (0);
}
