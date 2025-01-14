/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_matrix.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 11:57:47 by brivera           #+#    #+#             */
/*   Updated: 2025/01/13 13:16:04 by brivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**create_command_matrix(const char *arg_command)
{
	char	**matrix;

	if (!arg_command)
		return (NULL);
	matrix = ft_split(arg_command, ' ');
	if (!matrix)
		error_and_exit("Error de memoria");
	return (matrix);
}
