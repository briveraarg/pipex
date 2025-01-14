/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 17:07:04 by brivera@stu       #+#    #+#             */
/*   Updated: 2025/01/14 14:31:03 by brivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	open_fds(t_fds *fds, int argc, char **argv)
{
	fds->outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fds->outfile == -1)
		error_and_exit("Error archivo_salida");
	fds->infile = open(argv[1], O_RDONLY);
	if (fds->infile == -1)
		perror("Error archivo_entrada");
}

static void	read_stdin_heredoc(char **argv, t_fds *fds)
{
	char	*line;
	size_t	delimiter_len;

	delimiter_len = ft_strlen(argv[2]);
	while (1)
	{
		ft_putstr_fd("pipe heredoc > ", 1);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			error_and_exit("Entrada estándar inesperada");
		if (ft_strncmp(line, argv[2], delimiter_len) == 0
			&& line[delimiter_len] == '\n')
			break ;
		ft_putstr_fd(line, fds->infile);
		free(line);
	}
	free(line);
}

void	open_fd_heredoc(t_fds *fds, char **argv, int argc)
{
	fds->outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fds->outfile == -1)
		error_and_exit("Error archivo_salida");
	fds->infile = open("/tmp/heredoc_temp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fds->infile == -1)
		error_and_exit("Error creando archivo temporal para here_doc");
	read_stdin_heredoc(argv, fds);
	close(fds->infile);
	fds->infile = open("/tmp/heredoc_temp", O_RDONLY);
	if (fds->infile == -1)
		error_and_exit("Error abriendo archivo temporal para here_doc");
}
