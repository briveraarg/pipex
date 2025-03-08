/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 12:47:13 by brivera           #+#    #+#             */
/*   Updated: 2025/03/08 18:46:24 by brivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	execute_command(char *argv, char **env)
{
	char	*path;
	char	**command;

	command = create_command_matrix(argv);
	if (command == NULL)
		error_and_exit("Error de memoria");
	path = find_command_in_path(command[0], env);
	if (path == NULL)
	{
		ft_putstr_fd(argv, 2);
		free_matrix(command);
		print_error_exit(": command not found\n");
	}
	if (execve(path, command, env) == -1)
	{
		free_matrix(command);
		error_and_exit("Error execve");
	}
	free(path);
	free_matrix(command);
}

static void	setup_pipe_io(int i, int argc, t_fds *fds)
{
	if (i == 0 && fds->infile != -1)
		dup2(fds->infile, STDIN_FILENO);
	else if (fds->infile == -1)
		dup2(fds->pipes[0], STDIN_FILENO);
	else
		dup2(fds->prev_pipes, STDIN_FILENO);
	if (i == argc - 4)
		dup2(fds->outfile, STDOUT_FILENO);
	else
		dup2(fds->pipes[1], STDOUT_FILENO);
	close_pipes_chill(fds);
}

static void	create_pipes(t_fds *fds)
{
	pipe(fds->pipes);
	if (fds->pipes[0] == -1 || fds->pipes[1] == -1)
		error_and_exit("Error al crear pipe");
}

static void	close_pipes_and_comunication(t_fds *fds)
{
	close(fds->pipes[1]);
	if (fds->prev_pipes != -1)
		close(fds->prev_pipes);
	fds->prev_pipes = fds->pipes[0];
}

void	pipex(int argc, char **argv, char **env, t_fds *fds)
{
	int		i;
	pid_t	pid;

	i = 0;
	fds->prev_pipes = -1;
	if (fds->infile == -1)
		i = 1;
	while (i < argc - 3)
	{
		create_pipes(fds);
		pid = fork();
		if (pid == -1)
			error_and_exit("Error fork");
		if (pid == 0)
		{
			setup_pipe_io(i, argc, fds);
			execute_command(argv[i + 2], env);
		}
		else
			close_pipes_and_comunication(fds);
		i++;
	}
	while (waitpid(-1, NULL, 0) > 0)
		;
}
