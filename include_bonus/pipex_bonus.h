/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 15:41:44 by brivera           #+#    #+#             */
/*   Updated: 2025/09/15 20:17:27 by brivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100000
# endif
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

# define ONE_WAY "/tmp/heredoc_temp"
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
	bool	is_heredoc;
}	t_pipex;
/* ·········································································· */
/* ·········································································· */

void	print_error_argument(void);
char	*get_next_line(int fd);
bool	control_len_argument(char **argv, size_t argc);
bool	mode_heredoc(char **delimiter);
void	ft_free_ptr(void **ptr);
void	execute_command(t_pipex *data, int i);
void	*free_array(char **array);
char	*ft_strjoin_free(char *s1, char *s2);
int		pipex(t_pipex *data);
char	*find_command_in_path(const char *command, char **env);
void	setup_pipe(int i, t_pipex *data);
#endif