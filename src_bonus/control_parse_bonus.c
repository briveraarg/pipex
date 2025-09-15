/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_parse_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 17:33:17 by brivera           #+#    #+#             */
/*   Updated: 2025/09/15 21:40:07 by brivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	print_argument_error(void)
{
	ft_putendl_fd("Usage:", 2);
	ft_putendl_fd("./pipex infile cmd1 cmd2 outfile", 2);
	ft_putendl_fd("./pipex_bonus infile cmd1 cmd2 cmd3 ... outfile", 2);
	ft_putendl_fd("./pipex_bonus here_doc LIMITER cmd1 cmd2 outfile", 2);
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
