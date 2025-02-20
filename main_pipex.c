/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 12:41:12 by brivera           #+#    #+#             */
/*   Updated: 2025/02/20 18:26:11 by brivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	print_error_argument(void)
{
	ft_putstr_fd("Ingrese:\n", 2);
	ft_putstr_fd("./pipex archivo_entrada comando 1 comando 2 ", 2);
	ft_putstr_fd("archivo_salida.\n", 2);
	exit(1);
}

int	main(int argc, char **argv, char **env)
{
	t_fds	fds;
	int		i;

	if (argc == 5)
	{
		i = 1;
		while (i < argc - 1)
		{
			if ((ft_strlen(argv[i]) == 0))
				print_error_argument();
			i++;
		}
		fds.outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fds.outfile == -1)
			perror("Error archivo_salida");
		fds.infile = open(argv[1], O_RDONLY);
		if (fds.infile == -1)
			perror("Error archivo_entrada");
		pipex(argc, argv, env, &fds);
		close(fds.infile);
		close(fds.outfile);
	}
	else
		print_error_argument();
	return (0);
}
