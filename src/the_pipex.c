/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_pipex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 13:34:44 by brivera           #+#    #+#             */
/*   Updated: 2025/09/12 13:43:10 by brivera          ###   ########.fr       */
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

static void	execute_command(t_pipex *data)
{
	
}

static void	run_pipeline(int i, t_pipex *data)
{
	setup_pipe(i, data);
	execute_command(data);
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
		}
		i++;
	}
	wait_childs(data->argc - 4, &status, data->pid);
	return(status);
}
