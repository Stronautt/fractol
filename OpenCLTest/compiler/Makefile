# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/10 17:05:19 by pgritsen          #+#    #+#              #
#    Updated: 2017/12/25 20:01:55 by pgritsen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	kernel_compiler

CC			=	gcc

CFLAGS		=	-Wextra -Werror -Wall -O3 -g3

SRCS		=	compiler.c

OBJDIR		=	obj

OBJ			=	$(addprefix $(OBJDIR)/, $(SRCS:.c=.o))

INCLUDES	=	-framework OpenCL

all: $(NAME)

$(NAME): $(OBJDIR) $(OBJ)
	@printf "\n\033[32m[Creating $(NAME)].......\033[0m"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(INCLUDES)
	@printf "\033[32m[DONE]\033[0m\n"

$(OBJDIR):
	@printf "\n\033[32m[Creating folder $(OBJDIR)].......\033[0m"
	@mkdir $(OBJDIR)
	@printf "\033[32m[DONE]\033[0m\n"

$(OBJ): $(OBJDIR)/%.o : %.c
	@printf "\033[32m[Compiling $<].......\033[0m"
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "\033[32m[DONE]\033[0m\n"

clean:
	@printf "\033[31m[Cleaning object files].......\033[0m"
	@rm -rf $(OBJDIR)
	@printf "\033[31m[DONE]\033[0m\n"

fclean: clean
	@rm -rf $(NAME)
	@printf "\033[31m[Cleaning All].......\033[0m"
	@printf "\033[31m[DONE]\033[0m\n"

re:	fclean all
	@printf "\033[33m[Rebuild].......[END]\033[0m\n"

.NOTPARALLEL: all $(NAME) re
