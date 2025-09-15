/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 15:41:44 by brivera           #+#    #+#             */
/*   Updated: 2025/09/15 21:39:18 by brivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

/* ============================ CONFIG / MACROS ============================ */
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100000
# endif
# define ONE_WAY "/tmp/heredoc_temp"

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
	char	*dir_file;
	pid_t	*pid;
	int		argc;
	char	**argv;
	char	**env;
	bool	is_heredoc;
}	t_pipex;

/* ============================ ARG / PARSING ============================== */
void	print_argument_error(void);
bool	check_empty_arguments(char **argv, size_t argc);
bool	mode_heredoc(char **delimiter);

/* ============================== EXECUTION ================================ */
int		pipex(t_pipex *data);
void	execute_command(t_pipex *data, int i);
void	setup_pipe(int i, t_pipex *data);

/* ============================== COMMAND PATH ============================= */
char	*find_command_in_path(const char *command, char **env);

/* =============================== UTILITIES =============================== */
void	ft_free_ptr(void **ptr);
void	*free_array(char **array);
char	*ft_strjoin_free(char *s1, char *s2);

/* ============================= INPUT HELPERS ============================= */
char	*get_next_line(int fd);

#endif