typedef struct	s_vertice
{
	long		tr;
	double		x;
	double		y;
	double		z;
	long		color;
	long		ash;
}				t_vertice;

long	ft_smooth(long it, long max_it)
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

static inline int		point_in_cardiod(double *xy)
{
	double fi;
	double r;
	double rc;

	r = sqrt(pow(xy[0] - 0.25, 2) + pow(xy[1], 2));
	fi = atan2(xy[1], xy[0] - 0.25);
	rc = 0.5 - 0.5 * cos(fi);
	if (r <= rc)
		return (1);
	return (0);
}

__kernel void hello(__global t_vertice *z_buff, double pivot_x,
					double pivot_y, double dx, int height, int width)
{
	int		xy[2];
	long	it;
	double	d[2];
	double	zxy[3];
	double	fi;
	double	r;
	double	rc;

	xy[1] = -1;
	while (++xy[1] < height && (xy[0] = -1))
	{
		d[1] = pivot_y + (xy[1] - height / 2) * dx;
		while (++xy[0] < width && (it = -1))
		{
			zxy[0] = 0;
			zxy[1] = 0;
			d[0] = pivot_x + (xy[0] - width / 2) * dx;
			if (point_in_cardiod(d))
				continue ;
			while ((zxy[0] * zxy[0] + zxy[1] * zxy[1]) <= 4.0 && (++it <= 128))
			{
				zxy[2] = zxy[0] * zxy[0] - zxy[1] * zxy[1] + d[0];
				zxy[1] = 2 * zxy[0] * zxy[1] + d[1];
				zxy[0] = zxy[2];
			}
			z_buff[xy[1] * height + xy[0]].color = ft_smooth(it, 128);
		}
	}
}
