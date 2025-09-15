/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_command_in_path.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 16:39:15 by brivera           #+#    #+#             */
/*   Updated: 2025/09/15 15:09:36 by brivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	**path_check(char **env)
{
	int		i;
	char	**path_dir;
	char	*dir_path;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			dir_path = ft_substr(env[i], 5, ft_strlen(env[i]) - 5);
			path_dir = ft_split(dir_path, ':');
			if (!dir_path)
				return (perror("malloc"), ft_free_ptr((void *)&dir_path), NULL);
			return (ft_free_ptr((void *)&dir_path), path_dir);
		}
		i++;
	}
	return (NULL);
}

static char	*path_slash_access(const char *command)
{
	char	*dir_path_slash;

	dir_path_slash = NULL;
	if (access(command, F_OK) == 0)
	{
		dir_path_slash = ft_strdup(command);
		if (!dir_path_slash)
		{
			perror("malloc");
			return (NULL);
		}
	}
	return (dir_path_slash);
}

char	*find_command_in_path(const char *command, char **env)
{
	char	**dir_command;
	char	*dir_full_path;
	int		i;

	if (ft_strchr(command, '/'))
		return (dir_full_path = path_slash_access(command));
	dir_command = path_check(env);
	i = 0;
	while (dir_command[i] != NULL)
	{
		dir_full_path = ft_strjoin_free
			(ft_strdup(dir_command[i]), ft_strdup("/"));
		dir_full_path = ft_strjoin_free(dir_full_path, ft_strdup(command));
		if (!dir_full_path)
			return (perror("malloc"), NULL);
		if (path_slash_access(dir_full_path))
			return (free_array(dir_command), dir_full_path);
		ft_free_ptr((void *)&dir_full_path);
		i++;
	}
	free_array(dir_command);
	return (dir_full_path);
}
