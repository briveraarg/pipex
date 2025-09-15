/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_pipes_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 12:28:08 by brivera           #+#    #+#             */
/*   Updated: 2025/09/15 20:24:32 by brivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static bool	open_file_infile(char **argv, int *infile, bool is_heredoc)
{
	if (is_heredoc)
		*infile = open(ONE_WAY, O_RDONLY);
	else
		*infile = open(argv[1], O_RDONLY);
	if (*infile == -1)
		return (perror(argv[1]), true);
	return (false);
}

static bool	open_file_outfile(char **argv, int argc, int *outfile)
{
	*outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (*outfile == -1)
		return (perror(argv[argc - 1]), true);
	return (false);
}

static void	setup_pipe_stdin_infile(t_pipex *data)
{
	if (open_file_infile(data->argv, &data->infile, data->is_heredoc))
	{
		close(data->pipes[0]);
		close(data->pipes[1]);
		ft_free_ptr((void *)&data->pid);
		exit(EXIT_FAILURE);
	}
	if (dup2(data->infile, STDIN_FILENO) == -1)
		exit(EXIT_FAILURE);
	close(data->infile);
	close(data->pipes[0]);
}

static void	setup_pipe_stout_outfile(t_pipex *data)
{
	if (open_file_outfile(data->argv, data->argc, &data->outfile))
	{
		close(data->pipes[0]);
		close(data->pipes[1]);
		ft_free_ptr((void *)&data->pid);
		exit(EXIT_FAILURE);
	}
	if (dup2(data->outfile, STDOUT_FILENO) == -1)
		exit(EXIT_FAILURE);
	close(data->outfile);
	close(data->pipes[1]);
}

void	setup_pipe(int i, t_pipex *data)
{
	if (i == 0)
		setup_pipe_stdin_infile(data);
	else
	{
		if (dup2(data->prev_pipes, STDIN_FILENO) == -1)
			exit(EXIT_FAILURE);
		close(data->pipes[0]);
		close(data->prev_pipes);
	}
	if (i == data->argc - (data->non_command_args + 1))
		setup_pipe_stout_outfile(data);
	else
	{
		if (dup2(data->pipes[1], STDOUT_FILENO) == -1)
			exit(EXIT_FAILURE);
		close(data->pipes[1]);
	}
}
