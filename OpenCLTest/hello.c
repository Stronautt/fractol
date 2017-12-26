/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hello.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/25 14:15:35 by pgritsen          #+#    #+#             */
/*   Updated: 2017/12/26 18:10:26 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "../fractol.h"
 
#define SIZE 1200
#define MAX_SOURCE_SIZE 0x400000

int main()
{
	/* Basic OpenCl initialization */
	cl_int				err;
	cl_device_id		device;
	cl_context			context;
	cl_command_queue	gpu_queue;	

	err = clGetDeviceIDs(NULL, CL_DEVICE_TYPE_GPU, 1, &device, NULL);
	context = clCreateContext(0, 1, &device, NULL, NULL, &err);
	gpu_queue = clCreateCommandQueue(context, device, 0, &err);

	/* Buffer OpenCl initialization */
	cl_mem		pixels;
	cl_program	program;

	pixels = clCreateBuffer(context, CL_MEM_READ_WRITE,
							SIZE * SIZE * sizeof(t_uint), NULL, &err);

	/* Kernel OpenCl initialization	*/
	cl_kernel	kernel;
	char		obj_name[] = "./kernel/hello.cl.o";
	char		*obj_content;
	size_t		obj_size;
	int			fd;

	obj_content = malloc(sizeof(char) * MAX_SOURCE_SIZE);
	fd = open(obj_name, O_RDONLY);
	obj_size = read(fd, obj_content, MAX_SOURCE_SIZE);
	program = clCreateProgramWithBinary(context, 1, &device,
		(const size_t *)&obj_size,
		(const unsigned char **)&obj_content, NULL, &err);
	err = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
	kernel = clCreateKernel(program, "fill_mandelfract", &err);

	double	pivot[2] = {-0.75, 0};
	double	dx = 0.002;
	int		width = SIZE;
	int		height = SIZE;
	size_t	global[3] = {SIZE, SIZE, 0};

	err = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *)&pixels);
	err = clSetKernelArg(kernel, 1, sizeof(double), (void *)&pivot[0]);
	err = clSetKernelArg(kernel, 2, sizeof(double), (void *)&pivot[1]);
	err = clSetKernelArg(kernel, 3, sizeof(double), (void *)&dx);
	err = clSetKernelArg(kernel, 4, sizeof(double), (void *)&height);
	err = clSetKernelArg(kernel, 5, sizeof(int), (void *)&width);
	err = clEnqueueNDRangeKernel(gpu_queue, kernel, 2, NULL, global, NULL, 0, NULL, NULL);

	t_uint	*output;

	output = malloc(SIZE * SIZE * sizeof(t_uint));
	ft_bzero(output, SIZE * SIZE * sizeof(t_uint));
	err = clEnqueueReadBuffer(gpu_queue, pixels, CL_TRUE, 0,
	 	SIZE * SIZE * sizeof(t_uint), output, 0, NULL, NULL);
	// if (!err)
	// 	for (int i = 0; i < SIZE; i++)
	// 		for (int j = 0; j < SIZE; j++)
	// 			printf("%#.6X\n", output[i * SIZE + j]);
	printf("%d\n", err);
	// y : d[1] = pivot_y + (xy[1] - height / 2) * dx;
	// x : d[0] = pivot_x + (xy[0] - width / 2) * dx;

	// cl_device_id device_id = NULL;
	// cl_context context = NULL;
	// cl_command_queue command_queue = NULL;
	// cl_mem memobj = NULL;
	// cl_program program = NULL;
	// cl_kernel kernel = NULL;
	// cl_platform_id platform_id = NULL;
	// cl_uint ret_num_devices;
	// cl_uint ret_num_platforms;
	// cl_int ret;
	 
	// t_vertice string[MEM_SIZE][MEM_SIZE];

	// FILE *fp;
	// char fileName[] = "./kernel/hello.cl.o";
	// char *source_str;
	// size_t source_size;
	 
	// /* Load the source code containing the kernel*/
	// fp = fopen(fileName, "r");
	// if (!fp) {
	// 	fprintf(stderr, "Failed to load kernel.\n");
	// 	exit(1);
	// }
	// source_str = malloc(MAX_SOURCE_SIZE);
	// source_size = fread(source_str, 1, MAX_SOURCE_SIZE, fp);
	// fclose(fp);
	 
	// /* Get Platform and Device Info */
	// ret = clGetPlatformIDs(1, &platform_id, &ret_num_platforms);

	// ret = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_GPU, 1, &device_id, &ret_num_devices);

	// /* Create OpenCL context */
	// context = clCreateContext(NULL, 1, &device_id, NULL, NULL, &ret);

	// /* Create Command Queue */
	// command_queue = clCreateCommandQueue(context, device_id, 0, &ret);
	 
	// /* Create Memory Buffer */
	// memobj = clCreateBuffer(context, CL_MEM_READ_WRITE, MEM_SIZE * MEM_SIZE * sizeof(t_vertice), NULL, &ret);
	// /* Create Kernel Program from the source */
	// program = clCreateProgramWithBinary(context, 1, &device_id, (const size_t *)&source_size,
	// 	(const unsigned char **)&source_str, NULL, &ret);
	 
	// /* Build Kernel Program */
	// ret = clBuildProgram(program, 1, &device_id, NULL, NULL, NULL);
	// if (ret)
	// 	printf("Program didn't compiled!\n");
	 
	// /* Create OpenCL Kernel */
	// kernel = clCreateKernel(program, "hello", &ret);
	// if (ret)
	// 	printf("Kernel didn't created!\n");
	 
	// /* Set OpenCL Kernel Parameters */
	// double		x = -0.75;
	// double		y = 0;
	// double		dx = 0.002;
	// int			h = MEM_SIZE;
	// int			w = MEM_SIZE;

	// ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *)&memobj);	
	// ret = clSetKernelArg(kernel, 1, sizeof(x), (void *)&x);
	// ret = clSetKernelArg(kernel, 2, sizeof(y), (void *)&y);
	// ret = clSetKernelArg(kernel, 3, sizeof(dx), (void *)&dx);
	// ret = clSetKernelArg(kernel, 4, sizeof(h), (void *)&h);
	// ret = clSetKernelArg(kernel, 5, sizeof(w), (void *)&w);
	 
	// /* Execute OpenCL Kernel */
	// ret = clEnqueueTask(command_queue, kernel, 0, NULL,NULL);
	// if (ret)
	// 	printf("Execute error!\n");
	
	// /* Copy results from the memory buffer */
	// ret = clEnqueueReadBuffer(command_queue, memobj, CL_TRUE, 0,
	// 	MEM_SIZE * MEM_SIZE * sizeof(t_vertice), string, 0, NULL, NULL);
	 
	// /* Display Result */
	// for (int i = 0; i < MEM_SIZE; i++)
	// 	for (int j = 0; j < MEM_SIZE; j++)
	// 		ft_printf("%#.6lX\n", string[i][j].color);
	 
	// /* Finalization */
	// ret = clFlush(command_queue);
	// ret = clFinish(command_queue);
	// ret = clReleaseKernel(kernel);
	// ret = clReleaseProgram(program);
	// ret = clReleaseMemObject(memobj);
	// ret = clReleaseCommandQueue(command_queue);
	// ret = clReleaseContext(context);
	 
	// free(source_str);
	 
	return 0;
}
