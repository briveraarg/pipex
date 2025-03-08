/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 14:57:11 by brivera           #+#    #+#             */
/*   Updated: 2025/03/08 18:41:04 by brivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
/* ·········································································· */
/* ·········································································· */
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <errno.h>
# include <stdio.h>
# include <string.h>
# include <sys/wait.h>
# include "libft/libft.h"
/* ·········································································· */
/* ·········································································· */
typedef struct s_fds
{
	int	infile;
	int	outfile;
	int	pipes[2];
	int	prev_pipes;
}	t_fds;
/* ·········································································· */
/* ·········································································· */
void	print_error_exit(char *message);
void	error_and_exit(const char *message);
char	**free_matrix(char **array);
char	**create_command_matrix(const char *arg_command);
char	*find_command_in_path(const char *command, char **env);
void	close_pipes_chill(t_fds *fds);
void	pipex(int argc, char **argv, char **env, t_fds *fds);
#endif