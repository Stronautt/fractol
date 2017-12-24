/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 22:01:23 by pgritsen          #+#    #+#             */
/*   Updated: 2017/12/24 19:13:20 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	ft_make_draw_dependencies(t_env *env)
{
	env->dpndc = (t_dpndc[]){
		{PROGRAM_NAME, (void (*)(void *))&ft_mandelfract},
		{"BurningShip", (void (*)(void *))&ft_burningshipfract},
		{NULL, NULL}
	};
	ft_parse_z_buff(*env, ft_get_win(env->wins, "BurningShip"));
	ft_parse_z_buff(*env, ft_get_win(env->wins, PROGRAM_NAME));
}

void	ft_make_environment(t_env *env)
{
	t_window	*main;
	t_window	*burningship;

	*env = (t_env){
		.mlx_p = mlx_init()
	};
	main = ft_new_win(env, W_WIDTH, W_HEIGHT, PROGRAM_NAME);
	burningship = ft_new_win(env, W_WIDTH, W_HEIGHT, "BurningShip");
	mlx_hook(main->win_p, 2, 0, &ft_key_handler, main);
	mlx_mouse_hook(main->win_p, &ft_mouse_handler, main);
	mlx_hook(burningship->win_p, 2, 0, &ft_key_handler, burningship);
	mlx_mouse_hook(burningship->win_p, &ft_mouse_handler, burningship);
	main->pivot.x = -0.75;
	main->pivot.y = 0.0;
	main->dx = 0.002;
	burningship->pivot.x = -0.75;
	burningship->pivot.y = 0.0;
	burningship->dx = 0.003;
}

int		main(int ac, char **av)
{
	static t_env	env;

	(void)ac;
	(void)av;
	ft_make_environment(&env);
	ft_make_draw_dependencies(&env);	
	mlx_loop(env.mlx_p);
	return (0);
}
