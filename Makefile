# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/10 17:05:19 by pgritsen          #+#    #+#              #
#    Updated: 2017/12/29 16:47:34 by pgritsen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	fractol

CC			=	gcc

CFLAGS		=	-Wextra -Werror -Wall -O3 -g3

HDRSDIR		=	includes

HDRS		=	$(addprefix $(HDRSDIR)/, fractol.h)

SRCSDIR		=	source

SRCS		=	main.c handlers.c window_managing.c draw.c mandelbrot_fract.c	\
				burningship_frac.c opencl.c usage.c menu.c julia_fract.c

OBJDIR		=	obj

OBJ			=	$(addprefix $(OBJDIR)/, $(SRCS:.c=.o))

LIBS		=	libft/libft.a minilibx_macos/libmlx.a

INCLUDES	=	-Ilibft -Iminilibx_macos -Llibft -Lminilibx_macos -lft -lmlx	\
				-framework OpenGL -framework AppKit -framework OpenCl

all: lib $(NAME)

$(NAME): $(OBJDIR) $(OBJ) $(HDRS) $(LIBS)
	@printf "\n\033[32m[Creating $(NAME)].......\033[0m"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(INCLUDES)
	@printf "\033[32m[DONE]\033[0m\n"

$(OBJDIR):
	@printf "\n\033[32m[Creating folder $(OBJDIR)].......\033[0m"
	@mkdir $(OBJDIR)
	@printf "\033[32m[DONE]\033[0m\n"

$(OBJ): $(OBJDIR)/%.o : $(SRCSDIR)/%.c
	@printf "\033[32m[Compiling $<].......\033[0m"
	@$(CC) $(CFLAGS) -Ilibft -Iminilibx_macos -c $< -o $@ -I$(HDRSDIR)
	@printf "\033[32m[DONE]\033[0m\n"

$(LIBS): lib

lib:
	@printf "\033[33m[Creating libft.a].......[START]\033[0m\n"
	@make -j3 -C libft
	@printf "\033[33m[Creating libft.a].......[END]\033[0m\n"
	@printf "\n\033[33m[Creating libmlx.a].......[START]\033[0m\n"
	@make -j3 -C minilibx_macos
	@printf "\033[33m[Creating libmlx.a].......[END]\033[0m\n"

clean:
	@make -j3 -C libft clean
	@make -j3 -C minilibx_macos clean
	@printf "\033[31m[Cleaning object files].......\033[0m"
	@rm -rf $(OBJDIR)
	@printf "\033[31m[DONE]\033[0m\n"

clean_$(NAME):
	@printf "\033[31m[Cleaning object files].......\033[0m"
	@rm -rf $(OBJDIR)
	@printf "\033[31m[DONE]\033[0m\n"

fclean: clean	
	@make -j3 -C libft fclean
	@rm -rf $(NAME)
	@printf "\033[31m[Cleaning All].......\033[0m"
	@printf "\033[31m[DONE]\033[0m\n"

re:	fclean all
	@printf "\033[33m[Rebuild].......[END]\033[0m\n"

re_$(NAME): clean_$(NAME) all

.NOTPARALLEL: all $(NAME) re re_$(NAME)
