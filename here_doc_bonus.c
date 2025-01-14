/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 16:51:07 by brivera@stu       #+#    #+#             */
/*   Updated: 2025/01/14 14:31:05 by brivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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
		print_error_exit(": no existe el comando\n");
	}
	if (execve(path, command, env) == -1)
		error_and_exit("Error execve");
	free(path);
	free_matrix(command);
}

static void	setup_pipe_io(int i, int argc, t_fds *fds)
{
	if (i == 0)
		dup2(fds->infile, STDIN_FILENO);
	else
		dup2(fds->prev_pipes, STDIN_FILENO);
	if (i == argc - 5)
		dup2(fds->outfile, STDOUT_FILENO);
	else
		dup2(fds->pipes[1], STDOUT_FILENO);
	close(fds->pipes[0]);
	close(fds->pipes[1]);
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

void	here_doc(int argc, char **argv, char **env, t_fds *fds)
{
	int		i;
	pid_t	pid;

	open_fd_heredoc(fds, argv, argc);
	i = 0;
	fds->prev_pipes = -1;
	while (i < argc - 4)
	{
		create_pipes(fds);
		pid = fork();
		if (pid == -1)
			error_and_exit("Error fork");
		if (pid == 0)
		{
			setup_pipe_io(i, argc, fds);
			execute_command(argv[i + 3], env);
		}
		else
			close_pipes_and_comunication(fds);
		i++;
	}
	while (waitpid(-1, NULL, 0) > 0)
		;
}
