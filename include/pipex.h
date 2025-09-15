/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 14:57:11 by brivera           #+#    #+#             */
/*   Updated: 2025/09/15 21:39:16 by brivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

/* =============================== INCLUDES ================================ */
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <errno.h>
# include <stdio.h>
# include <string.h>
# include <sys/wait.h>
# include <stdbool.h>
# include "../libft/libft.h"

/* ================================ STRUCT ================================= */
typedef struct s_pipex
{
	int		infile;
	int		outfile;
	int		pipes[2];
	int		prev_pipes;
	int		non_command_args;
	pid_t	*pid;
	int		argc;
	char	**argv;
	char	**env;
}	t_pipex;

/* ============================ ARG / PARSING ============================== */
bool	check_empty_arguments(char **argv, size_t argc);
void	print_argument_error(void);

/* ============================== EXECUTION ================================ */
int		pipex(t_pipex *data);
void	execute_command(t_pipex *data, int i);
void	setup_pipe(int i, t_pipex *data);

/* ============================== COMMAND PATH ============================= */
char	*find_command_in_path(const char *command, char **env);

/* =============================== UTILITIES =============================== */
char	*ft_strjoin_free(char *s1, char *s2);
void	ft_free_ptr(void **ptr);
void	*free_array(char **array);

#endif