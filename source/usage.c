/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usage.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/28 18:46:54 by pgritsen          #+#    #+#             */
/*   Updated: 2017/12/30 14:30:10 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

double		ft_lerp(double a, double b, double t)
{
	return ((1.0 - t) * a + t * b);
}

void		ft_open_help(t_window *win)
{
	t_window	*help;
	void		*logo;
	int			i;
	int			tmp;

	i = -1;
	while (win->env->help_table[++i].func)
		if (!ft_strcmp(win->title, win->env->help_table[i].key))
		{
			if (ft_get_win(win->env->wins, HELP))
				return ;
			help = ft_new_win(win->env, HW_WIDTH, HW_HEIGHT, HELP);
			ft_set_background(help, 0xFFFFFF);
			logo = mlx_xpm_file_to_image(win->env->mlx_p,
				"resource/help.xpm", &tmp, &tmp);
			!logo ? ft_err_handler("Can't find resource!", NULL, 0) : 0;
			mlx_put_image_to_window(win->env->mlx_p,
									help->win_p, logo, 100, 20);
			mlx_hook(help->win_p, 2, 0, &ft_key_handler, help);
			win->env->help_table[i].func(help);
		}
}

void		ft_make_help_dependecies(t_env *env)
{
	const t_dpndc	help_table[] = {
		{MANDELFRACT, &ft_mandelhelp, NULL, NULL},
		{BURNINGSHIP, &ft_burninghelp, NULL, NULL},
		{JULIAFRACT, &ft_juliahelp, NULL, NULL},
		{TRICORNFRACT, &ft_tricornhelp, NULL, NULL},
		{NULL, NULL, NULL, NULL}};

	!(env->help_table = malloc(sizeof(help_table))) ?
								ft_err_handler("Memmory fail!", NULL, 0) : 0;
	ft_memmove(env->help_table, help_table, sizeof(help_table));
}

void		ft_make_draw_dependencies(t_env *env)
{
	const t_dpndc	dpndc[] = {
		{PROGRAM_NAME, &ft_menu, NULL, NULL},
		{MANDELFRACT, &ft_mandelfract, F_MF, K_MF},
		{BURNINGSHIP, &ft_burningshipfract, F_BS, K_BS},
		{JULIAFRACT, &ft_julia, F_JF, K_JF},
		{TRICORNFRACT, &ft_tricornfract, F_TF, K_TF},
		{NULL, NULL, NULL, NULL}};
	const t_dpndc	init_table[] = {
		{MANDELFRACT, &ft_init_mandelfract, NULL, NULL},
		{BURNINGSHIP, &ft_init_buringship, NULL, NULL},
		{JULIAFRACT, &ft_init_julia, NULL, NULL},
		{TRICORNFRACT, &ft_init_tricornfract, NULL, NULL},
		{NULL, NULL, NULL, NULL}};

	!(env->dpndc = malloc(sizeof(dpndc))) ? ft_err_handler("Memmory fail!",
															NULL, 0) : 0;
	!(env->init_table = malloc(sizeof(init_table))) ?
								ft_err_handler("Memmory fail!", NULL, 0) : 0;
	ft_memmove(env->dpndc, dpndc, sizeof(dpndc));
	ft_memmove(env->init_table, init_table, sizeof(init_table));
}

void		ft_make_environment(t_env *env)
{
	t_window	*main;

	env->mlx_p = mlx_init();
	ft_init_cl(env, CL_DEVICE_TYPE_GPU);
	main = ft_new_win(env, MW_WIDTH, MW_HEIGHT, PROGRAM_NAME);
	ft_draw(*env, main);
	mlx_hook(main->win_p, 2, 0, &ft_key_handler, main);
	mlx_mouse_hook(main->win_p, &ft_menu_mouse_handler, main);
}
