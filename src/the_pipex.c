/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_pipex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 13:34:44 by brivera           #+#    #+#             */
/*   Updated: 2025/09/15 21:33:05 by brivera          ###   ########.fr       */
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

static void	bye_bye_pipe_father(t_pipex *data)
{
	if (data->prev_pipes != -1)
		close(data->prev_pipes);
	data->prev_pipes = data->pipes[0];
	close(data->pipes[1]);
}

static void	run_pipeline(int i, t_pipex *data)
{
	setup_pipe(i, data);
	execute_command(data, i);
	exit(EXIT_SUCCESS);
}

static void	wait_children(int cmd_len, int *exit_code, int pid[])
{
	int	i;
	int	status;

	i = 0;
	*exit_code = 0;
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
	if (!data->pid)
		return (perror("malloc"), ENOMEM);
	while (i < data->argc - data->non_command_args)
	{
		if (create_pipes(data))
			return (ft_free_ptr((void *)&data->pid), EXIT_FAILURE);
		data->pid[i] = fork();
		if (data->pid[i] == -1)
			return (perror("fork"), ft_free_ptr((void *)&data->pid), 1);
		if (data->pid[i] == 0)
			run_pipeline(i, data);
		else
			bye_bye_pipe_father(data);
		i++;
	}
	wait_children(data->argc - data->non_command_args, &status, data->pid);
	ft_free_ptr((void *)&data->pid);
	if (data->prev_pipes != -1)
		close(data->prev_pipes);
	return (status);
}
