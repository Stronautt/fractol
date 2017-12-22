/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot_fract.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/20 17:07:51 by pgritsen          #+#    #+#             */
/*   Updated: 2017/12/22 17:30:17 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	ft_mandelfract(t_window *w)
{
	pthread_t		threads[4];
	int				t[4][4];
	t_thread_stuff	s[4];
	int				i[2];
	static intmax_t	p[] = {
		0x000000, 0x19071A, 0x09012F, 0x040449,
		0x000764, 0x122C8A, 0x1852B1, 0x397DD1,
		0x86B5E5, 0xD3ECF8, 0xF1E9BF, 0xF8C95F,
		0xFFAA00, 0xCC8000, 0x995700, 0x6A3403
	};

	i[0] = -1;
	while (++i[0] < 2 && (i[1] = -1))
		while (++i[1] < 2)
		{
			ft_memmove(t[i[0] * 2 + i[1]],
				(int[4]){w->height * i[1] / 2, w->height * (i[1] + 1) / 2,
					w->width * i[0] / 2, w->width * (i[0] + 1) / 2}, 4 * 4);
			s[i[0] * 2 + i[1]] = (t_thread_stuff){w, p, t[i[0] * 2 + i[1]]};
			pthread_create(&threads[i[0] * 2 + i[1]], NULL,
				(void *(*)(void *))ft_draw_mandelfract, &s[i[0] * 2 + i[1]]);
		}
	i[0] = -1;
	while (++i[0] < 4)
		pthread_join(threads[i[0]], NULL);
}

void	ft_draw_mandelfract(t_thread_stuff *t)
{
	int				xy[2];
	intmax_t		it;
	double			d[2];
	double			zxy[4];

	xy[1] = t->lim[0] - 1;
	while (++xy[1] < t->lim[1] && !((xy[0] = t->lim[2] - 1) * 0))
	{
		d[1] = t->win->pivot.y + (xy[1] - t->win->height / 2) * t->win->dx;
		while (++xy[0] < t->lim[3] && (it = -1))
		{
			zxy[0] = 0.0;
			zxy[1] = 0.0;
			d[0] = t->win->pivot.x + (xy[0] - t->win->width / 2) * t->win->dx;
			while ((zxy[0] * zxy[0] + zxy[1] * zxy[1]) < 4.0
				&& (++it <= UCHAR_MAX))
			{
				zxy[2] = zxy[0] * zxy[0] - zxy[1] * zxy[3] + d[0];
				zxy[3] = 2 * zxy[0] * zxy[1] + d[1];
				zxy[0] = zxy[2];
				zxy[1] = zxy[3];
			}
			t->win->pixels.z_buff[xy[1]][xy[0]].color = t->palette[it % 16];
		}
	}
}
