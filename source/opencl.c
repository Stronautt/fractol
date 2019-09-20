/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/26 21:20:01 by pgritsen          #+#    #+#             */
/*   Updated: 2018/01/03 15:21:47 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	ft_init_cl(t_env *env, cl_device_type dev_type)
{
	cl_int			err;
	t_uint			n_o_p;
	cl_platform_id	*p_ids;
	int				i;

	err = clGetPlatformIDs(0, NULL, &n_o_p);
	err ? ft_err_handler("OpenCl", "Can't get platform id's!", 0) : 0;
	p_ids = malloc(sizeof(cl_platform_id) * n_o_p);
	err = clGetPlatformIDs(n_o_p, p_ids, NULL);
	err ? ft_err_handler("OpenCl", "Can't get platform id's!", 0) : 0;
	i = -1;
	while (++i < (int)n_o_p)
		if (!(err = clGetDeviceIDs(p_ids[i], dev_type, 1, &env->cl_data.device, NULL)))
			break ;
	err ? err = clGetDeviceIDs(p_ids[0], CL_DEVICE_TYPE_DEFAULT,
			1, &env->cl_data.device, NULL) : 0;
	free(p_ids);
	err ? ft_err_handler("OpenCl", "Can't get device!", 0) : 0;
	env->cl_data.context = clCreateContext(0, 1, &env->cl_data.device,
											NULL, NULL, &err);
	err ? ft_err_handler("OpenCl", "Can't create context!", 0) : 0;
	env->cl_data.queue = clCreateCommandQueue(env->cl_data.context,
												env->cl_data.device, 0, &err);
	err ? ft_err_handler("OpenCl", "Can't create queue!", 0) : 0;
}

void	ft_parse_kernel(t_env *env, t_window *win,
						const char *kernel_name, const char *func_name)
{
	int		fd;
	cl_int	er;
	size_t	obj_size;
	char	*obj_content;

	if (!(fd = open(kernel_name, O_RDONLY)))
		ft_err_handler("OpenCl", "Fail!", 0);
	if (!(obj_content = malloc(MAX_SOURCE_SIZE)))
		ft_err_handler("OpenCl", "Fail!", 0);
	obj_size = read(fd, obj_content, MAX_SOURCE_SIZE);
	win->cl_data.program = clCreateProgramWithSource(env->cl_data.context, 1,
		(const char **)&obj_content, (const size_t *)&obj_size, &er);
	ft_memdel((void **)&obj_content);
	er ? ft_err_handler("OpenCl", "Can't create program!", 0) : 0;
	er = clBuildProgram(win->cl_data.program, 1, &env->cl_data.device,
						NULL, NULL, NULL);
	er ? ft_err_handler("OpenCl", "Can't build program!", 0) : 0;
	win->cl_data.kernel = clCreateKernel(win->cl_data.program, func_name, &er);
	er ? ft_err_handler("OpenCl", "Can't create kernel!", 0) : 0;
}
