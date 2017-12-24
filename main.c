/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 22:01:23 by pgritsen          #+#    #+#             */
/*   Updated: 2017/12/24 16:12:40 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	ft_make_environment(t_env *env)
{
	t_window	*main;

	*env = (t_env){
		.mlx_p = mlx_init()
	};
	main = ft_new_win(env, W_WIDTH, W_HEIGHT, PROGRAM_NAME);
	mlx_hook(main->win_p, 2, 0, &ft_key_handler, main);
	mlx_mouse_hook(main->win_p, &ft_mouse_handler, main);
	main->pivot.x = -0.75;
	main->pivot.y = 0.0;
	main->dx = 0.002;
}

int		main(int ac, char **av)
{
	static t_env	env;

	(void)ac;
	(void)av;
	char	*str;
	str = cuddaMalloc(123);
	ft_make_environment(&env);
	ft_parse_z_buff(env, ft_get_win(env.wins, PROGRAM_NAME));
	mlx_loop(env.mlx_p);
	return (0);
}
