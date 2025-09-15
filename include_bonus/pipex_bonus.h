/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 15:41:44 by brivera           #+#    #+#             */
/*   Updated: 2025/09/15 17:58:23 by brivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

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
	int		non_command_args;
	char	*dir_file;
	pid_t	*pid;
	int		argc;
	char	**argv;
	char	**env;
}	t_pipex;
/* ·········································································· */
/* ·········································································· */

void	print_error_argument(void);
bool	control_len_argument(char **argv, size_t argc);
bool	mode_heredoc(char **delimiter);

#endif