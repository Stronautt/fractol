/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.cl                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 22:01:23 by pgritsen          #+#    #+#             */
/*   Updated: 2017/12/29 14:30:22 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma OPENCL EXTENSION cl_khr_fp64 : enable

#define MAX_ITERATIONS 256

static inline unsigned int	ft_smooth(int it, int max_it)
{
	double	t;
	int		r;
	int		g;
	int		b;

	t = (double)it / (double)max_it;
	r = 9 * (1 - t) * t * t * t * 255;
	g = 15 * (1 - t) * (1 - t) * t * t * 255;
	b = 8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255;
	return (r * 0x10000 + g * 0x100 + b);
}

__kernel void
fill_julia(__global int *buff, double pivot_x, double pivot_y, double dx,
			double cx, double cy, int height, int width)
{
	int				it = 0;
	int				x = get_global_id(0);
	int				y = get_global_id(1);
	double3			z = (double3) 0;

	z = (double3)(1.5 * (x - width / 2) / (0.5 * dx * width) + pivot_x,
		0.85 * (y - height / 2) / (0.5 * dx * height) + pivot_y, 0);
	it = MAX_ITERATIONS + 1;
	while ((z.x * z.x + z.y * z.y) <= 4.0 && --it > 1)
	{
		z.z = z.x * z.x - z.y * z.y + cx;
		z.y = 2 * z.x * z.y + cy;
		z.x = z.z;
	}
	buff[y * width + x] = ft_smooth(it, MAX_ITERATIONS);
}
