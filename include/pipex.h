/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 14:57:11 by brivera           #+#    #+#             */
/*   Updated: 2025/09/15 15:29:39 by brivera          ###   ########.fr       */
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
# include "../libft/libft.h"
# include <stdbool.h>
/* ·········································································· */
/* ·········································································· */

typedef struct s_pipex
{
	int		infile;
	int		outfile;
	int		pipes[2];
	int		prev_pipes;
	pid_t	*pid;
	int		argc;
	char	**argv;
	char	**env;
}	t_pipex;
/* ·········································································· */
/* ·········································································· */
int		pipex(t_pipex *data);
char	*find_command_in_path(const char *command, char **env);
char	*ft_strjoin_free(char *s1, char *s2);
bool	control_len_argument(char **argv, size_t argc);
void	execute_command(t_pipex *data, int i);
void	print_error_argument(void);
void	setup_pipe(int i, t_pipex *data);
void	ft_free_ptr(void **ptr);
void	*free_array(char **array);

#endif