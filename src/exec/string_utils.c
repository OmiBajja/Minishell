/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pafranci <pafranci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 02:41:25 by pafranci          #+#    #+#             */
/*   Updated: 2025/05/29 02:05:42 by pafranci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		len_s1;
	int		len_s2;
	char	*res;

	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	res = (char *)malloc(((len_s1 + len_s2) + 1) * sizeof(char));
	if (!res)
		return (NULL);
	i = 0;
	while (i < len_s1)
	{
		res[i] = s1[i];
		i++;
	}
	i = 0;
	while (i < len_s2)
	{
		res[i + len_s1] = s2[i];
		i++;
	}
	res[i + len_s1] = '\0';
	return (res);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*sub_s;

	if (start >= (unsigned int)ft_strlen(s))
	{
		sub_s = (char *)malloc(sizeof(char));
		if (!sub_s)
			return (NULL);
		sub_s[0] = '\0';
		return (sub_s);
	}
	if ((start + len) >= (unsigned int)ft_strlen(s))
		sub_s = (char *)malloc(((ft_strlen(s) - start) + 1) * sizeof (char));
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
	sub_s[i] = '\0';
	return (sub_s);
}

bool	is_needle_in_haystack(const char *haystack, const char *needle)
{
	while (*needle != '\0')
	{
		if (*haystack != *needle)
			return (false);
		haystack++;
		needle++;
	}
	return (true);
}

char	*ft_strnstr(const char *haystack, const char *needle, int n)
{
	int	i;
	int	needle_len;

	needle_len = ft_strlen(needle);
	if (*needle == '\0')
		return ((char *)haystack);
	i = 0;
	while (haystack[i] != '\0' && ((i + needle_len) - 1) < n)
	{
		if (haystack[i] == needle[0])
		{
			if (is_needle_in_haystack(&haystack[i], needle) == true)
				return ((char *)&haystack[i]);
		}
		i++;
	}
	return (NULL);
}
