/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 17:42:37 by brivera           #+#    #+#             */
/*   Updated: 2025/09/15 20:06:28 by brivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	read_stdin_heredoc(char *delimiter, int infile)
{
	char	*line;
	size_t	delimiter_len;

	delimiter_len = ft_strlen(delimiter);
	while (1)
	{
		ft_putstr_fd("pipe heredoc > ", 1);
		line = get_next_line(STDIN_FILENO);
		if (!line)
		{
			ft_putendl_fd("Entrada estándar inesperada", 2);
			break ;
		}
		if (ft_strncmp(line, delimiter, delimiter_len) == 0
			&& line[delimiter_len] == '\n')
			break ;
		ft_putstr_fd(line, infile);
		ft_free_ptr((void **)&line);
	}
	ft_free_ptr((void **)&line);
}

bool	mode_heredoc(char **delimiter)
{
	int	infile;

	infile = open(ONE_WAY, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (infile == -1)
		return (perror("error al crear temporal"), true);
	read_stdin_heredoc(delimiter[2], infile);
	close(infile);
	return (false);
}
