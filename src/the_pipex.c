/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_pipex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 13:34:44 by brivera           #+#    #+#             */
/*   Updated: 2025/09/12 19:50:04 by brivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static bool	create_pipes(t_pipex *data)
{
	pipe(data->pipes);
	if (data->pipes[0] == -1 || data->pipes[1] == -1)
		return (perror("pipe"), true);
	return (false);
}

static void	execute_command(t_pipex *data, int i)
{
	char	*path;
	char	**command;

	command = ft_split(data->argv[i + 2], ' ');
	if(!command)
	{
		perror("malloc");
		exit(ENOMEM);
	}
	path = find_command_in_path(command[0], data->env);
	if (!path)
	{
		ft_putstr_fd(command[0], STDERR_FILENO);
		ft_putendl_fd(" command not found", STDERR_FILENO);
		free_array(command);
		exit(127);
	}
	if (execve(path, command, data->env) == -1)
	{
		ft_free_ptr((void *)&path);
		free_array(command);
		exit(127);
	}
	ft_free_ptr((void *)&path);
	free_array(command);
}

static void	run_pipeline(int i, t_pipex *data)
{
	setup_pipe(i, data);
	execute_command(data, i);
	exit(EXIT_SUCCESS);
}

static void	wait_childs(int cmd_len, int *exit_code, int pid[])
{
	int	i;
	int	status;

	i = 0;
	while (i < cmd_len)
	{
		waitpid(pid[i], &status, 0);
		i++;
	}
	if (WIFEXITED(status))
		*exit_code = WEXITSTATUS(status);
}

int	pipex(t_pipex *data)
{
	int		i;
	int		status;

	i = 0;
	data->pid = ft_calloc(data->argc - 3, sizeof(pid_t));
	while (i < data->argc - 3)
	{
		if (create_pipes(data))
			return (EXIT_FAILURE);
		data->pid[i] = fork();
		if (data->pid[i] == -1)
			return (perror("fork"), EXIT_FAILURE);
		if (data->pid[i] == 0)
			run_pipeline(i, data);
		else
		{
			data->prev_pipes = dup(data->pipes[0]);
			close(data->pipes[0]);
			close(data->pipes[1]);
			close(data->prev_pipes);
		}
		i++;
	}
	wait_childs(data->argc - 4, &status, data->pid);
	i = 0;
	while (i < data->argc - 3)
	{
		ft_free_ptr((void *)&data->pid[i]);
		i++;
	}
	ft_free_ptr((void *)&data->pid);
	return(status);
}
