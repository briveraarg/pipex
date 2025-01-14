/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 17:36:20 by brivera           #+#    #+#             */
/*   Updated: 2025/01/13 17:30:33 by brivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	**path_check(char **env)
{
	char	**path_dir;
	char	*dir_path;
	size_t	len;
	int		i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			len = ft_strlen(env[i]) - 5;
			dir_path = ft_substr(env[i], 5, len);
			path_dir = ft_split(dir_path, ':');
			free(dir_path);
			if (!dir_path)
				error_and_exit("Error de memoria");
			return (path_dir);
		}
		i++;
	}
	print_error_exit("Error de entorno anulado\n");
	return (NULL);
}

static char	*path_slash(const char *command)
{
	char	*dir_path_slash;

	dir_path_slash = NULL;
	if (access(command, F_OK) == 0)
	{
		dir_path_slash = ft_strdup(command);
		if (!dir_path_slash)
			error_and_exit("Error de memoria");
	}
	return (dir_path_slash);
}

char	*find_command_in_path(const char *command, char **env)
{
	char	**dir_command;
	char	*dir_full_path;
	char	*temp;
	int		i;

	if (ft_strchr(command, '/'))
		return (dir_full_path = path_slash(command));
	dir_command = path_check(env);
	i = 0;
	while (dir_command[i] != NULL)
	{
		dir_full_path = ft_strjoin(dir_command[i], "/");
		temp = dir_full_path;
		dir_full_path = ft_strjoin(temp, command);
		free(temp);
		if (!dir_full_path)
			error_and_exit("Error de memoria");
		if (path_slash(dir_full_path))
			return (free_matrix(dir_command), dir_full_path);
		free(dir_full_path);
		i++;
	}
	dir_full_path = NULL;
	free_matrix(dir_command);
	return (dir_full_path);
}
