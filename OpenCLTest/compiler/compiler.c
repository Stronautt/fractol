/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compiler.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/25 14:15:35 by pgritsen          #+#    #+#             */
/*   Updated: 2017/12/25 20:13:50 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <OpenCL/opencl.h>

#define MAX_SOURCE_SIZE 0x100000

int		main(int ac, char **av)
{
	cl_platform_id platform_id = NULL;
	cl_device_id device_id = NULL;
	cl_context context = NULL;
	cl_program program = NULL;
	cl_uint ret_num_devices;
	cl_uint ret_num_platforms;
	cl_int ret;

	DIR				*dir;
	int				fd;
	struct dirent*	in_file;

	char	*source_str;
	size_t	source_size;
	char	*object_name;
	char	*file_name;

	if (ac < 2)
		return (0);
	dir = opendir(av[1]);
	while ((in_file = readdir(dir)))
	{
		if (!strcmp(in_file->d_name, ".") || !strcmp(in_file->d_name, "..")
			|| in_file->d_name[strlen(in_file->d_name) - 1] == 'o')
			continue ;
		file_name = malloc(strlen(in_file->d_name) + strlen(av[1]) + 2);
		strcat(file_name, av[1]);
		strcat(file_name, "/");
		strcat(file_name, in_file->d_name);
		if (!(fd = open(file_name, O_RDWR)))
		{
			printf("%s : Kernel didn't compiled!\n", file_name);
			continue ;
		}
		source_str = malloc(MAX_SOURCE_SIZE);
		source_size = read(fd, source_str, MAX_SOURCE_SIZE);
		close(fd);
		ret = clGetPlatformIDs(1, &platform_id, &ret_num_platforms);
		if (ac >= 3 && !strcmp(av[2], "GPU"))
			ret = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_GPU, 1, &device_id, &ret_num_devices);
		else if (ac >= 3 && !strcmp(av[2], "CPU"))
			ret = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_CPU, 1, &device_id, &ret_num_devices);
		else
			ret = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_DEFAULT, 1, &device_id, &ret_num_devices);
		context = clCreateContext(NULL, 1, &device_id, NULL, NULL, &ret);
		program = clCreateProgramWithSource(context, 1, (const char **)&source_str,
			(const size_t *)&source_size, &ret);
		free(source_str);		
		ret = clBuildProgram(program, 1, &device_id, NULL, NULL, NULL);
		if (ret)
		{
			printf("%s : Kernel didn't compiled!\n", file_name);
			continue ;
		}
		clGetProgramInfo(program, CL_PROGRAM_BINARY_SIZES, sizeof(size_t), &source_size, NULL);
		source_str = malloc(source_size);
		clGetProgramInfo(program, CL_PROGRAM_BINARIES, source_size, &source_str, NULL);
		object_name = malloc(strlen(file_name) + 3);
		strcat(object_name, file_name);
		strcat(object_name, ".o");
		remove(object_name);
		if (!(fd = open(object_name, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP)))
		{
			printf("%s : Object file creating error!\n", object_name);
			continue ;
		}
		write(fd, source_str, source_size);
		close(fd);
		ret = clReleaseProgram(program);
		ret = clReleaseContext(context);
		free(source_str);
		close(fd);
	}
	return (0);
}
