/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_extender.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obajja <obajja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 15:56:51 by obajja            #+#    #+#             */
/*   Updated: 2025/06/04 22:53:52 by obajja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char *input_extender(char *input, char *replace, char *word, int stop)
{
	int i;
	int j;
	int len;
	char *extended;

	i = -1;
	j = -1;
	len = ft_strlen(input) - (ft_strlen(word) + 1) + ft_strlen(replace) + 1;
	extended = malloc (len * sizeof(char));
	if (!extended)
		return (NULL);
	while (++i < stop)
		extended[i] = input[i];
	len = (ft_strlen(word)) + i;
	while (replace[++j])
		extended[i++] = replace[j];
	while (input[++len])
		extended[i++] = input[len];
	extended[i + 1] = '\0';
	printf("Final: %s\n", extended);
	return (extended);
}

char *env_fetcher(char *word, char **env)
{
	int i;
	int len;
	char *replace;
	
	i = 0;
	len = ft_strlen(word);
	while (env[i])
	{	
		if (ft_strncmp(env[i], word, len) == 0 && env[i][len] == '=')
			break;
		i++;
	}
	if (!env[i])
		return (NULL);
	replace = ft_strdup(&env[i][len + 1]);
	if (!replace)
		return (NULL);
	return (replace);
}

char *word_assigner(char *input)
{
	char *word;
	int j;
	int len;
	int i;
	
	len = 0;
	i = 0;
	j = 0;
	word = NULL;
	while (input[i] && !ft_is_whitespace(input[i]) && input[i] != '"')
		i++;
	word = malloc ((i + 1) * sizeof(char));
	if (!word)
		return (NULL);
	len = i - 1;
	i = -1;
	while (i < len)
		word[++i] = input[j++];
	word[i + 1] = '\0';
	return (word);
}

int	is_extendable(char *input)
{
	int	i;

	i = 0;
	while (input[i] && input[i] != '$')
		i++;
	if (input[i] == '$')
	{
		i++;
		return (i);
	}
	else
		return (-1);
}

char *ft_extender(char *input, char **env)
{
	int	i;
	char *word;
	char *extended;
	char *replace;
	
	if ((i = is_extendable(input)) == -1)
		return (NULL);
	word = word_assigner(&input[i]);
	if (!word)
		return (NULL);
	replace = env_fetcher(word, env);
	if (!replace)
		return (NULL);
	extended = input_extender(input, replace, word, i - 1);
	if (!extended)
		return (NULL);
	return(extended);
}
