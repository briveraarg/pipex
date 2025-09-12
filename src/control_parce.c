/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_parce.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 15:33:59 by brivera           #+#    #+#             */
/*   Updated: 2025/09/12 19:00:01 by brivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	print_error_argument(void)
{
	ft_putendl_fd("Ingrese:", STDERR_FILENO);
	ft_putendl_fd("./pipex infile comando 1 comando 2 outfile", STDERR_FILENO);
}

bool	control_len_argument(char **argv, size_t argc)
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
