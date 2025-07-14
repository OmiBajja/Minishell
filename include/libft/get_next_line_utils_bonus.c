/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obajja <obajja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 18:12:45 by pafranci          #+#    #+#             */
/*   Updated: 2025/07/14 15:55:13 by obajja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen_sizet(char const *str)
{
	size_t	count;

	if (!str)
		return (0);
	count = 0;
	while (str[count] != '\0')
		count++;
	return (count);
}

char	*ft_strchr_gnl(const char *s, int c)
{
	if (!s)
		return (NULL);
	c %= 256;
	while (*s != '\0')
	{
		if ((int)*s == c)
			return ((char *)s);
		s++;
	}
	if (c == 0)
		return ((char *)(s + ft_strlen_sizet(s)));
	return (NULL);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	int		i;
	int		len_s1;
	int		len_s2;
	char	*res;

	if (!s1)
		len_s1 = 0;
	else
		len_s1 = ft_strlen_sizet(s1);
	if (!s2)
		len_s2 = 0;
	else
		len_s2 = ft_strlen_sizet(s2);
	res = (char *)malloc(((len_s1 + len_s2) + 1) * sizeof(char));
	if (!res)
		return (NULL);
	i = -1;
	while (++i < len_s1)
		res[i] = s1[i];
	i = -1;
	while (++i < len_s2)
		res[i + len_s1] = s2[i];
	res[i + len_s1] = '\0';
	return (res);
}

char	*ft_strdup_gnl(const char *s)
{
	int		i;
	int		s_len;
	char	*s_dup;

	s_len = ft_strlen_sizet(s);
	s_dup = (char *)malloc((s_len + 1) * sizeof (char));
	if (!s_dup)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		s_dup[i] = s[i];
		i++;
	}
	s_dup[i] = '\0';
	return (s_dup);
}

char	*ft_substr_gnl(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*sub_s;

	if (start >= ft_strlen_sizet(s))
	{
		sub_s = (char *)malloc(sizeof(char));
		if (!sub_s)
			return (NULL);
		sub_s[0] = '\0';
		return (sub_s);
	}
	if ((start + len) >= ft_strlen_sizet(s))
		sub_s = (char *)malloc(((ft_strlen_sizet(s) - start) + 1)
				* sizeof (char));
	else
		sub_s = (char *)malloc((len + 1) * sizeof(char));
	if (!sub_s)
		return (NULL);
	i = 0;
	while (i < len && s[i + start])
	{
		sub_s[i] = s[i + start];
		i++;
	}
	return (sub_s[i] = '\0', sub_s);
}
