# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/03 18:56:52 by brivera@stu       #+#    #+#              #
#    Updated: 2025/09/15 15:29:09 by brivera          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		:= pipex
#NAME_BONUS := pipex_bonus

CC 			:= cc
CFLAGS 	 	:= -Wall -Werror -Wextra -g3 #-fsanitize=address,undefined,leak

LIBFT_DIR 	:= libft/
LIBFTA 	  	:= $(LIBFT_DIR)libft.a

INCLUDE			:= include/
#INCLUDE_BONUS	:= include_bonus/
HEADERS			:= $(INCLUDE)pipex.h
#HEADERS_BONUS	:= $(INCLUDE)pipex_bonus.h

SRCS_DIR 		:= src/
SRCS		 		:= 	$(SRCS_DIR)main.c \
						$(SRCS_DIR)control_parce.c \
						$(SRCS_DIR)setup_pipes.c \
						$(SRCS_DIR)the_pipex.c\
						$(SRCS_DIR)find_command_in_path.c\
						$(SRCS_DIR)execute_command.c\
						$(SRCS_DIR)free_memory.c

#SRC_DIR_BONUS 	:= src_bonus/

OBJ_DIR      	:= obj/
#OBJ_DIR_BONUS 	:= obj_bonus/
OBJS	        := $(addprefix $(OBJ_DIR), $(SRCS:$(SRCS_DIR)%.c=%.o))
#OBJS_BONUS 	:= $(addprefix $(OBJ_DIR_BONUS), $(notdir $(SRCS_BONUS:.c=.o)))


RED			:=	\033[91;1m
GREEN		:=	\033[92;1m
CLEAR_COLOR	:=	\033[0m
CYAN 		:=	\033[96;1m


all: $(NAME)
#bonus: $(NAME_BONUS)

$(NAME): $(LIBFTA) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFTA) -o $(NAME)
	@echo "$(GREEN)✅ Compilado PIPEX.\n$(CLEAR_COLOR)"

#$(NAME_BONUS): $(LIBFTA) $(OBJS_BONUS)
#	@$(CC) $(CFLAGS) $(OBJS_BONUS) $(LIBFTA) -o $(NAME_BONUS)
#	@echo "$(GREEN)\nCompilado BONUS DEL PIPEX.\n$(CLEAR_COLOR)"

$(LIBFTA):
	@make -C $(LIBFT_DIR)
	@echo "$(GREEN)✅ Compilado LIBFT\n$(CLEAR_COLOR)"

$(OBJ_DIR)%.o: $(SRCS_DIR)%.c $(HEADERS)
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -I$(INCLUDE) -c $< -o $@

clean:
	@$(RM) $(OBJS)
	@rm -rf $(OBJ_DIR)
	@make clean -C $(LIBFT_DIR)
	@echo "$(RED)⛔ Limpieza de archivos objeto.$(CLEAR_COLOR)"


fclean: clean
	@$(RM) $(NAME) 
	@make fclean -C $(LIBFT_DIR)
	@echo "$(RED)⛔ Limpieza total (ejecutables y librerías).$(CLEAR_COLOR)"

re: fclean all

valgrind:
	valgrind -s \
		--tool=memcheck \
		--leak-check=full \
		--show-leak-kinds=all \
		--show-reachable=yes \
		--track-origins=yes \
		--trace-children=yes \
		--track-fds=yes \
		time ./$(NAME) Makefile "echo argentina" "cat" outfile

norminette:
	@norminette $(SRCS) $(INCLUDE)

.PHONY: all clean fclean re bonus norminette valgrind

.DEFAULT_GOAL := all
