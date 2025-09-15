/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 12:41:12 by brivera           #+#    #+#             */
/*   Updated: 2025/09/15 21:37:33 by brivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **env)
{
	t_pipex	data;
	int		status;

	ft_memset(&data, 0, sizeof(t_pipex));
	if (argc != 5)
		return (print_argument_error(), EXIT_FAILURE);
	if (check_empty_arguments(argv, argc))
		return (ft_putstr_fd("OMG! ", 2), print_argument_error(), EXIT_FAILURE);
	data.non_command_args = 3;
	data.prev_pipes = -1;
	data.argv = argv;
	data.argc = argc;
	data.env = env;
	status = pipex(&data);
	return (status);
}
