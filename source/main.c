/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/29 14:46:02 by pgritsen          #+#    #+#             */
/*   Updated: 2017/12/30 14:28:31 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		main(void)
{
	static t_env	env;

	ft_make_draw_dependencies(&env);
	ft_make_help_dependecies(&env);
	ft_make_environment(&env);
	mlx_loop(env.mlx_p);
	return (0);
}
