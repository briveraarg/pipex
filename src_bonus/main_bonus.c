/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 15:45:53 by brivera           #+#    #+#             */
/*   Updated: 2025/09/15 17:58:35 by brivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int argc, char **argv, char **env)
{
	t_pipex	data;
	int		status;

	ft_memset(&data, 0, sizeof(t_pipex));
	if (argc < 5)
		return (print_error_argument(), EXIT_FAILURE);
	if (control_len_argument(argv, argc))
		return (ft_putstr_fd("OMG! ", 2), print_error_argument(), EXIT_FAILURE);
	if (!ft_strncmp(argv[1], "here_doc", 8))
	{
		if (mode_heredoc(argv))
			return (EXIT_FAILURE);
	}
	data.non_command_args = 3;
	data.prev_pipes = -1;
	data.argv = argv;
	data.argc = argc;
	data.env = env;
	status = 0;
	return (status);
}
