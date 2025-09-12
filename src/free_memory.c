/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 17:28:12 by brivera           #+#    #+#             */
/*   Updated: 2025/09/12 18:51:33 by brivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free_ptr(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

void	*free_array(char **array)
{
	size_t	i;

	if (!array)
		return (NULL);
	i = 0;
	while (array[i] != NULL)
	{
		ft_free_ptr((void **)&array[i]);
		i++;
	}
	free(array);
	return (NULL);
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*joined;

	if (!s1 || !s2)
		return (NULL);
	joined = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (joined);
}