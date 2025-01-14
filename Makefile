# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/03 18:56:52 by brivera@stu       #+#    #+#              #
#    Updated: 2025/01/14 14:30:58 by brivera          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
NAME_BONUS = pipex_bonus

CC = cc
CFLAGS = -Wall -Werror -Wextra -g3 -fsanitize=address,undefined,leak
LIBFT_DIR = ./libft
LIBFTA = $(LIBFT_DIR)/libft.a

OBJ_DIR = obj
SRCS_NORMAL = main_pipex.c pipex.c control_path.c command_matrix.c utils.c
SRCS_BONUS = here_doc_bonus.c utils_bonus.c get_next_line_bonus.c \
			main_pipex_bonus.c pipex.c control_path.c command_matrix.c \
			utils.c
OBJS_NORMAL = $(addprefix $(OBJ_DIR)/, $(SRCS_NORMAL:.c=.o))
OBJS_BONUS = $(addprefix $(OBJ_DIR)/, $(SRCS_BONUS:.c=.o))

INCLUDES_NORMAL = pipex.h
INCLUDES_BONUS = pipex_bonus.h

RED         = \033[91;1m
GREEN       = \033[92;1m
CLEAR_COLOR = \033[0m

all: $(NAME)

bonus: $(NAME_BONUS)

$(NAME): $(LIBFTA) $(OBJS_NORMAL)
	@$(CC) $(CFLAGS) $(OBJS_NORMAL) $(LIBFTA) -o $(NAME)
	@echo "$(GREEN)\nCompilado PIPEX.\n$(CLEAR_COLOR)"

$(NAME_BONUS): $(LIBFTA) $(OBJS_BONUS)
	@$(CC) $(CFLAGS) $(OBJS_BONUS) $(LIBFTA) -o $(NAME_BONUS)
	@echo "$(GREEN)\nCompilado BONUS DEL PIPEX.\n$(CLEAR_COLOR)"

$(LIBFTA):
	@make -C $(LIBFT_DIR)
	@echo "$(GREEN)Compilado LIBFT.\n$(CLEAR_COLOR)"

$(OBJ_DIR)/%.o: %.c $(INCLUDES_NORMAL)
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo -n "\rCompilando: $<"

$(OBJ_DIR)/%.o: %.c $(INCLUDES_BONUS)
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo -n "\rCompilando BONUS: $<"

clean:
	@$(RM) $(OBJS_NORMAL) $(OBJS_BONUS)
	@rm -rf $(OBJ_DIR)
	@make clean -C $(LIBFT_DIR)
	@echo "$(RED)Limpieza de archivos objeto.$(CLEAR_COLOR)"

fclean: clean
	@$(RM) $(NAME) $(NAME_BONUS)
	@make fclean -C $(LIBFT_DIR)
	@echo "$(RED)Limpieza total (ejecutables y librerías).$(CLEAR_COLOR)"

re: fclean all

.PHONY: all clean fclean re bonus
