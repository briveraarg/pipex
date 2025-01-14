/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_pipex_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 17:28:03 by brivera@stu       #+#    #+#             */
/*   Updated: 2025/01/13 16:36:16 by brivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	print_error_argument(void)
{
	ft_putstr_fd("Puede ingresar:\n", 2);
	ft_putstr_fd("./pipex_bonus here_doc DELIMITADOR comando1 comando2 ", 2);
	ft_putstr_fd("archivo_salida.\n", 2);
	ft_putstr_fd("./pipex_bonus archivo_entrada comando1 comando2 ", 2);
	ft_putstr_fd("comando 3 ... archivo_salida.\n", 2);
	exit(1);
}

int	main(int argc, char **argv, char **env)
{
	t_fds	fds;
	int		i;

	if (argc >= 5)
	{
		i = 0;
		while (i < argc - 1)
		{
			if ((ft_strlen(argv[i]) == 0))
				print_error_argument();
			i++;
		}
		if (ft_strncmp(argv[1], "here_doc", 8) == 0)
		{
			here_doc(argc, argv, env, &fds);
			return (0);
		}
		open_fds(&fds, argc, argv);
		pipex(argc, argv, env, &fds);
		close(fds.infile);
		close(fds.outfile);
	}
	else
		print_error_argument();
	return (0);
}
