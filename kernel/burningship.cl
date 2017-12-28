#pragma OPENCL EXTENSION cl_khr_fp64 : enable

#define MAX_ITERATIONS 255

static inline unsigned int	ft_smooth(int it, int max_it)
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

static inline char			point_in_cardiod(double x, double y)
{
	double fi;
	double r;
	double rc;

	r = sqrt(pow(x - 0.25, 2) + pow(y, 2));
	fi = atan2(y, x - 0.25);
	rc = 0.5 - 0.5 * cos(fi);
	if (r <= rc)
		return (1);
	return (0);
}

__kernel void
fill_burningship(__global int *buff, double pivot_x,
				double pivot_y, double dx, int height, int width)
{
	int				it = 0;
	int				x = get_global_id(0);
	int				y = get_global_id(1);
	double3			z = (double3) 0;
	double2			c;

	c = (double2)(pivot_x + (x - width / 2) * dx,
		pivot_y + (y - height / 2) * dx);
	while ((z.x * z.x + z.y * z.y) <= 4.0 && (++it <= MAX_ITERATIONS))
	{
		z.z = z.x * z.x - z.y * z.y + c.x;
		z.y = 2.0 * fabs(z.x * z.y) + c.y;
		z.x = z.z;
	}
	buff[y * width + x] = ft_smooth(it, MAX_ITERATIONS);
}
