/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_parce_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 17:33:17 by brivera           #+#    #+#             */
/*   Updated: 2025/09/15 20:51:57 by brivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	print_error_argument(void)
{
	ft_putendl_fd("Ingrese:", STDERR_FILENO);
	ft_putendl_fd("./pipex infile cmd1 ... cmd4 outfile", STDERR_FILENO);
	ft_putendl_fd("./pipex infile here_doc DELIMITADOR cmd1 ... cmd4 outfile",
		STDERR_FILENO);
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
