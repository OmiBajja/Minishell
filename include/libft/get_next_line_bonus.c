/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obajja <obajja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 18:12:03 by pafranci          #+#    #+#             */
/*   Updated: 2025/07/14 15:56:03 by obajja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*read_next_line(int fd, char *whats_left)
{
	int		read_bytes;
	char	*buffer;
	char	*tmp;

	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof (char));
	if (!buffer)
		return (NULL);
	read_bytes = 1;
	while (!ft_strchr_gnl(whats_left, '\n') && read_bytes != 0)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes == -1)
			return (free(whats_left), free(buffer), NULL);
		buffer[read_bytes] = '\0';
		tmp = whats_left;
		whats_left = ft_strjoin_gnl(tmp, buffer);
		free(tmp);
	}
	return (free(buffer), whats_left);
}

char	*crop_next_line(char *whats_left)
{
	char	*res;
	int		line_len;

	if (!whats_left || !whats_left[0])
		return (NULL);
	line_len = ft_strlen_sizet(whats_left)
		- (ft_strlen_sizet(ft_strchr_gnl(whats_left, '\n')));
	if (!ft_strchr_gnl(whats_left, '\n'))
		line_len = ft_strlen_sizet(whats_left);
	if (whats_left[line_len] == '\n')
		line_len++;
	res = ft_substr_gnl(whats_left, 0, line_len);
	return (res);
}

char	*update_whats_left(char *whats_left)
{
	int		i;
	int		j;
	char	*res;

	i = ft_strlen_sizet(whats_left)
		- (ft_strlen_sizet(ft_strchr_gnl(whats_left, '\n')));
	if (!whats_left[i])
		return (free(whats_left), NULL);
	res = (char *)malloc(sizeof(char) * (ft_strlen_sizet(whats_left) - i + 1));
	if (!res)
		return (NULL);
	i++;
	j = 0;
	while (whats_left[i])
		res[j++] = whats_left[i++];
	res[j] = '\0';
	return (free(whats_left), res);
}

char	*get_next_line(int fd)
{
	char		*next_line;
	static char	*whats_left[1024];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	whats_left[fd] = read_next_line(fd, whats_left[fd]);
	if (!whats_left[fd])
		return (NULL);
	next_line = crop_next_line(whats_left[fd]);
	whats_left[fd] = update_whats_left(whats_left[fd]);
	return (next_line);
}
/*
#include <fcntl.h>

int	main(void)
{
	int	fd;
	int line_count = 36;

	fd = open("get_next_line.h", O_RDONLY);
	while (line_count-- > 0)
		printf("%s", get_next_line(fd));
	// printf("%s", get_next_line(fd));
	// printf("%s", get_next_line(fd));
	return (0);
}
*/