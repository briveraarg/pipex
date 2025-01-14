/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 12:04:49 by brivera           #+#    #+#             */
/*   Updated: 2025/01/13 17:28:16 by brivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_and_exit(const char *message)
{
	perror(message);
	exit(1);
}

void	print_error_exit(char *message)
{
	ft_putstr_fd(message, 2);
	exit (1);
}

char	**free_matrix(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
	return (NULL);
}

void	close_pipes_chill(t_fds *fds)
{
	close(fds->pipes[0]);
	close(fds->pipes[1]);
}
