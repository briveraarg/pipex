/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 12:41:12 by brivera           #+#    #+#             */
/*   Updated: 2025/09/12 13:35:13 by brivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


int	main(int argc, char **argv, char **env)
{
	t_pipex	data;
	int		status;

	ft_memset(&data,0, sizeof(t_pipex));
	if (argc != 5)
		return (print_error_argument(), EXIT_FAILURE);
	if (control_len_argument(argv, argc))
		return (ft_putstr_fd("OMG! ", 2), print_error_argument(), EXIT_FAILURE);
	data.argv = argv;
	data.argc = argc;
	data.env = env;
	status = pipex(&data);
	return (status);
}
