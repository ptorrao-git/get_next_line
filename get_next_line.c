/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptorrao- <ptorrao-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 12:48:22 by ptorrao-          #+#    #+#             */
/*   Updated: 2024/08/13 15:14:03 by ptorrao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*set_stash(char *stash)
{
	char	*temp;

	temp = ft_strndup(stash + ft_strclen(stash, '\n')
			+ 1, ft_strclen(stash, '\0') - ft_strclen(stash, '\n'));
	free (stash);
	if (!temp)
		return (NULL);
	return (temp);
}

char	*free_data(char *buf, char *stash)
{
	free(buf);
	free(stash);
	return (NULL);
}

char	*fill_stash(int fd, char *stash)
{
	char		*buf;
	ssize_t		size;

	size = BUFFER_SIZE;
	buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (NULL);
	*buf = 0;
	while (!ft_strchr(buf, '\n') && size != 0)
	{
		size = read(fd, buf, BUFFER_SIZE);
		if (size < 0)
			return (free_data(buf, stash));
		buf[size] = '\0';
		stash = ft_strjoin(stash, buf);
	}
	if (*stash == '\0' || size == -1)
		return (free_data(buf, stash));
	free(buf);
	return (stash);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*stash;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!stash)
		stash = NULL;
	stash = fill_stash(fd, stash);
	if (!stash)
		return (NULL);
	line = ft_strndup(stash, ft_strclen(stash, '\n') + 1);
	if (!line)
		return (NULL);
	stash = set_stash(stash);
	if (!stash)
		free(stash);
	return (line);
}

/* int main()
{
	int fd = open("example.txt", O_RDONLY);
	int i = 0;
	char *line;
	while(i < 4)
	{
		line = get_next_line(fd);
		printf("%s", line);
		free(line);
		i++;
	}
	close(fd);
	return(0);
} */