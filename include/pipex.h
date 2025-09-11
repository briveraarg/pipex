/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 14:57:11 by brivera           #+#    #+#             */
/*   Updated: 2025/09/11 15:41:39 by brivera          ###   ########.fr       */
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
	int		argc;
	char	**argv;
	char	**env;
}	t_pipex;
/* ·········································································· */
/* ·········································································· */
void	print_error_argument(void);
bool	control_len_argument(char **argv, size_t argc);

#endif