/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 12:41:12 by brivera           #+#    #+#             */
/*   Updated: 2025/09/12 12:06:05 by brivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

bool	open_file_infile(char **argv, int *infile)
{
	*infile = open(argv[1], O_RDONLY);
	if (*infile == -1)
		return (perror(argv[1]), true);
	return (false);
}

bool	open_file_outfile(char **argv, int argc, int *outfile)
{
	*outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (*outfile == -1)
		return (perror(argv[argc - 1]), true);
	return (false);
}

static bool	create_pipes(t_pipex *data)
{
	pipe(data->pipes);
	if (data->pipes[0] == -1 || data->pipes[1] == -1)
		return (perror("pipe"), true);
	return (false);
}

void	setup_pipe_stdin_infile(t_pipex *data)
{
	if (open_file_infile(data->argv, &data->infile))
	{
		close(data->pipes[0]);
		close(data->pipes[1]);
		exit(EXIT_FAILURE);
	}
	if (dup2(data->infile, STDIN_FILENO) == -1)
		exit(EXIT_FAILURE);
	close(data->infile);
	close(data->pipes[0]);
}

void	setup_pipe_stout_outfile(t_pipex *data)
{
	if (open_file_outfile(data->argv, data->argc, &data->outfile))
	{
		close(data->pipes[0]);
		close(data->pipes[1]);
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
	if (i == data->argc - 4)
		setup_pipe_stout_outfile(data);
	else
	{
		if (dup2(data->pipes[1], STDOUT_FILENO) == -1)
			exit(EXIT_FAILURE);
		close(data->pipes[1]);
	}

}

int	pipex(t_pipex *data)
{
	int		i;
	pid_t	pid;

	i = 0;
	while (i < data->argc - 3)
	{
		if (create_pipes(data))
			return (EXIT_FAILURE);
		pid = fork();
		if (pid == -1)
			return (perror("fork"), EXIT_FAILURE);
		if (pid == 0)
		{
			setup_pipe(i, data);
			exit(EXIT_SUCCESS);
		}
		else
		{
			data->prev_pipes = dup(data->pipes[0]);
			close(data->pipes[0]);
			close(data->pipes[1]);
		}
		i++;
	}
	while (waitpid(-1, NULL, 0) > 0)
		;
	return(3);
}
 
int	main(int argc, char **argv, char **env)
{
	t_pipex	data;
	int		status;

	ft_memset(&data,0, sizeof(t_pipex));
	if (argc != 5)
		return (print_error_argument(), EXIT_FAILURE);
	if (control_len_argument(argv, argc))
		return (ft_putstr_fd("OMG! ", 2), print_error_argument(), EXIT_FAILURE);
	data.argv = argv;
	data.argc = argc;
	data.env = env;
	status = pipex(&data);
	return (status);
}
