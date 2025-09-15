/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 19:44:44 by brivera           #+#    #+#             */
/*   Updated: 2025/09/15 20:52:09 by brivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	clean_up(char **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

static char	*read_and_store(int fd, char **store, char *buffer)
{
	char	*temp;
	ssize_t	bytes_read;

	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (clean_up(store), NULL);
		if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		temp = *store;
		if (!temp)
			temp = ft_strdup("");
		if (!temp)
			return (clean_up(store), NULL);
		*store = ft_strjoin(temp, buffer);
		clean_up(&temp);
		if (!*store)
			return (NULL);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (*store);
}

static char	*extract_line_content(char **store)
{
	char	*line;
	char	*newline_pos;
	size_t	line_len;

	if (!*store || !**store)
		return (NULL);
	newline_pos = ft_strchr(*store, '\n');
	if (newline_pos)
		line_len = newline_pos - *store + 1;
	else
		line_len = ft_strlen(*store);
	line = ft_substr(*store, 0, line_len);
	if (!line)
		return (NULL);
	return (line);
}

static void	update_storage(char **store)
{
	char	*new_storage;
	char	*newline_pos;
	size_t	remaining_len;

	if (!*store)
		return ;
	newline_pos = ft_strchr(*store, '\n');
	if (!newline_pos || !*(newline_pos + 1))
		return (clean_up(store));
	remaining_len = ft_strlen(newline_pos + 1);
	new_storage = ft_substr(*store, newline_pos - *store + 1, remaining_len);
	clean_up(store);
	*store = new_storage;
}

char	*get_next_line(int fd)
{
	static char	*store;
	char		*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (clean_up(&store), NULL);
	buffer = (char *)ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (clean_up(&store), NULL);
	if (!read_and_store(fd, &store, buffer))
		return (clean_up(&buffer), NULL);
	clean_up(&buffer);
	line = extract_line_content(&store);
	if (!line)
		return (clean_up(&store), NULL);
	update_storage(&store);
	return (line);
}
