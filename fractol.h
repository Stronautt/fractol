/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 22:04:33 by pgritsen          #+#    #+#             */
/*   Updated: 2017/12/22 17:31:52 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdio.h>
# include <errno.h>
# include <unistd.h>
# include <fcntl.h>
# include <mlx.h>
# include <math.h>
# include <time.h>
# include <limits.h>
# include <pthread.h>
# include "libft.h"

# define PROGRAM_NAME "Fracto'l"
# define W_WIDTH 1200
# define W_HEIGHT 1200

# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_Q 12
# define KEY_E 14
# define KEY_ARR_UP 126
# define KEY_ARR_DOWN 125
# define KEY_ARR_LEFT 123
# define KEY_ARR_RIGHT 124
# define M_B_LEFT 1
# define M_B_RIGHT 2
# define M_SCROLL_UP 4
# define M_SCROLL_DOWN 5
# define KEY_ESC 53

typedef unsigned char	t_uchar;
typedef unsigned int	t_uint;
typedef unsigned long	t_ulong;
typedef unsigned short	t_ushort;

struct			s_rot;
struct			s_vertice;
struct			s_poly;
struct			s_object;
struct			s_window;
struct			s_cam;
struct			s_env;
struct			s_img;

typedef struct	s_rot
{
	double	rx;
	double	ry;
	double	rz;
}				t_rot;

typedef struct	s_vertice
{
	struct s_vertice	*prev;
	double				x;
	double				y;
	double				z;
	intmax_t			color;
	struct s_vertice	*next;
}				t_vertice;

typedef struct	s_poly
{
	struct s_poly	*prev;
	t_vertice		*vertices;
	int				id;
	struct s_poly	*next;
}				t_poly;

typedef struct	s_object
{
	struct s_object	*prev;
	t_poly			*polygons;
	int				id;
	intmax_t		poly_c;
	struct s_object	*next;
}				t_object;

typedef struct	s_img
{
	int			s_l;
	int			endian;
	int			bpp;
	void		*p;
	char		*buff;
	t_vertice	**z_buff;
}				t_img;

typedef struct	s_window
{
	struct s_window	*prev;
	int				width;
	int				height;
	char			*title;
	void			*win_p;
	t_img			pixels;
	double			dx;
	t_vertice		pivot;
	struct s_env	*env;
	struct s_window	*next;	
}				t_window;

typedef struct	s_cam
{
	t_vertice		align;
	t_rot			rotation;
	int				id;
	struct s_cam	*next;
}				t_cam;

typedef struct	s_env
{
	t_cam		*cams;
	t_object	*objs;
	void		*mlx_p;
	t_window	*wins;
}				t_env;

typedef struct	s_thread_stuff
{
	t_window	*win;
	intmax_t	*palette;
	int			*lim;
}				t_thread_stuff;

/*
**		Handlers.c
**		↓↓↓↓↓↓↓↓↓↓
*/

void			ft_err_handler(char *msg, char *add, int err);

int				ft_key_handler(int key, t_window *win);

int				ft_mouse_handler(int key, int x, int y, t_window *win);

/*
**		Window_managing.c
**		↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓
*/

t_window		*ft_new_win(t_env *env, int width, int height, char *title);

t_window		*ft_get_win(t_window *wins, const char *title);

int				ft_destroy_win(t_window *win);

/*
**		Z_buffer.c
**		↓↓↓↓↓↓↓↓↓↓
*/

t_vertice		**ft_init_z_buffer(t_window win);

void			ft_parse_z_buff(t_env env, t_window *win);

/*
**		Mandelbrot_fract.c
**		↓↓↓↓↓↓↓↓↓↓
*/

void			ft_mandelfract(t_window *win);

void			ft_draw_mandelfract(t_thread_stuff *t);

#endif
