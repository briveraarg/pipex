/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 15:28:24 by brivera           #+#    #+#             */
/*   Updated: 2025/09/15 15:28:37 by brivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute_command(t_pipex *data, int i)
{
	char	*path;
	char	**command;

	command = ft_split(data->argv[i + 2], ' ');
	if (!command)
		(perror("malloc"), exit(ENOMEM));
	path = find_command_in_path(command[0], data->env);
	if (!path)
	{
		ft_putstr_fd(command[0], STDERR_FILENO);
		ft_putendl_fd(" command not found", STDERR_FILENO);
		free_array(command);
		ft_free_ptr((void *)&data->pid);
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
