/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 15:33:59 by brivera           #+#    #+#             */
/*   Updated: 2025/09/15 21:37:30 by brivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	print_argument_error(void)
{
	ft_putendl_fd("Usage:", STDERR_FILENO);
	ft_putendl_fd("./pipex infile cmd1 cmd2 outfile", STDERR_FILENO);
}

bool	check_empty_arguments(char **argv, size_t argc)
{
	size_t	i;

	i = 1;
	while (i < argc - 1)
	{
		if ((ft_strlen(argv[i]) == 0))
			return (true);
		i++;
	}
	return (false);
}
