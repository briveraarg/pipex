/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 15:28:24 by brivera           #+#    #+#             */
/*   Updated: 2025/09/15 20:31:30 by brivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	free_resources(char *path, char **command)
{
	ft_free_ptr((void *)&path);
	free_array(command);
}

void	execute_command(t_pipex *data, int i)
{
	size_t	command_len;
	char	*path;
	char	**command;

	if (data->is_heredoc)
		command_len = 3;
	else
		command_len = 2;
	command = ft_split(data->argv[i + command_len], ' ');
	if (!command)
		(perror("malloc"), exit(ENOMEM));
	path = find_command_in_path(command[0], data->env);
	if (!path)
	{
		ft_putstr_fd(command[0], STDERR_FILENO);
		ft_putendl_fd(" command not found", STDERR_FILENO);
		free_resources(path, command);
		exit(127);
	}
	if (execve(path, command, data->env) == -1)
	{
		free_resources(path, command);
		exit(127);
	}
	free_resources(path, command);
}
