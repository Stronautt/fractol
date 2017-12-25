/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burningship_frac.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/20 17:07:51 by pgritsen          #+#    #+#             */
/*   Updated: 2017/12/25 14:01:52 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static inline intmax_t	ft_smooth(intmax_t it, intmax_t max_it)
{
	double	t;
	int		r;
	int		g;
	int		b;

	t = (double)it / (double)max_it;
	r = 9 * (1 - t) * t * t * t * 255;
	g = 4 * (1 - t) * (1 - t) * t * t * 255;
	b = 1.5 * (1 - t) * (1 - t) * (1 - t) * t * 255;
	return (r * 0x10000 + g * 0x100 + b);
}

static void				ft_draw_burningship(t_thread_stuff *t)
{
	int				xy[2];
	intmax_t		it;
	double			d[2];
	double			*zxy;

	xy[1] = t->lim[0] - 1;
	while (++xy[1] < t->lim[1] && !((xy[0] = t->lim[2] - 1) * 0))
	{
		d[1] = t->win->pivot.y + (xy[1] - t->win->height / 2) * t->win->dx;
		while (++xy[0] < t->lim[3] && (it = -1))
		{
			zxy = (double[3]){0.0, 0.0, 0.0};
			d[0] = t->win->pivot.x + (xy[0] - t->win->width / 2) * t->win->dx;
			while ((zxy[0] * zxy[0] + zxy[1] * zxy[1]) <= 16.0 && (++it <= 160))
			{
				zxy[2] = zxy[0] * zxy[0] - zxy[1] * zxy[1] + d[0];
				zxy[1] = 2 * fabs(zxy[0] * zxy[1]) + d[1];
				zxy[0] = zxy[2];
			}
			t->win->pixels.z_buff[xy[1]][xy[0]].color = ft_smooth(it, 160);
		}
	}
}

void					ft_burningshipfract(t_window *win)
{
	pthread_t		threads[4];
	t_thread_stuff	s[4];
	int				i[2];

	i[0] = -1;
	while (++i[0] < 2 && (i[1] = -1))
		while (++i[1] < 2)
		{
			s[i[0] * 2 + i[1]] = (t_thread_stuff){win,
				{win->height * i[1] / 2, win->height * (i[1] + 1) / 2,
					win->width * i[0] / 2, win->width * (i[0] + 1) / 2}};
			pthread_create(&threads[i[0] * 2 + i[1]], NULL,
				(void *(*)(void *))ft_draw_burningship, &s[i[0] * 2 + i[1]]);
		}
	i[0] = -1;
	while (++i[0] < 4)
		pthread_join(threads[i[0]], NULL);
}
