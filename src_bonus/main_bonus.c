/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 15:45:53 by brivera           #+#    #+#             */
/*   Updated: 2025/09/15 21:37:35 by brivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int argc, char **argv, char **env)
{
	t_pipex	data;
	int		status;

	ft_memset(&data, 0, sizeof(t_pipex));
	if (argc < 5)
		return (print_argument_error(), EXIT_FAILURE);
	if (check_empty_arguments(argv, argc))
		return (ft_putstr_fd("OMG! ", 2), print_argument_error(), EXIT_FAILURE);
	if (!ft_strncmp(argv[1], "here_doc", 8))
	{
		if (mode_heredoc(argv))
			return (EXIT_FAILURE);
		data.is_heredoc = true;
	}
	if (data.is_heredoc)
		data.non_command_args = 4;
	else
		data.non_command_args = 3;
	data.prev_pipes = -1;
	data.argv = argv;
	data.argc = argc;
	data.env = env;
	status = pipex(&data);
	return (status);
}
