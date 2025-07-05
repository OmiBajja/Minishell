/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_extender.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obajja <obajja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 15:56:51 by obajja            #+#    #+#             */
/*   Updated: 2025/07/05 18:03:25 by obajja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*input_extender(char *input, char *replace, char *word, int stop)
{
	int		i;
	int		j;
	int		len;
	char	*extended;

	i = -1;
	j = -1;
	len = ft_strlen(input) - (ft_strlen(word) + 1) + ft_strlen(replace) + 1;
	extended = ft_calloc(len, sizeof(char));
	if (!extended)
		return (NULL);
	while (++i < stop)
		extended[i] = input[i];
	len = (ft_strlen(word)) + i;
	while (replace[++j])
		extended[i++] = replace[j];
	while (input[++len])
		extended[i++] = input[len];
	extended[i] = '\0';
	return (extended);
}

static char	*env_fetcher(char *word, char **env, t_mini *mini)
{
	int		i;
	int		len;
	char	*replace;

	if (ft_strcmp(word, "?") == 0)
	{
		replace = ft_itoa(mini->status + g_sig);
		g_sig = 0;
		return (replace);
	}
	i = 0;
	len = ft_strlen(word);
	while (env[i])
	{
		if (ft_strncmp(env[i], word, len) == 0 && env[i][len] == '=')
			break ;
		i++;
	}
	if (!env[i])
		return (ft_calloc(1, 1));
	replace = ft_strdup(&env[i][len + 1]);
	if (!replace)
		return (NULL);
	return (replace);
}

char	*word_assigner(char *input)
{
	char	*word;
	int		j;
	int		len;
	int		i;

	i = 0;
	j = 0;
	word = NULL;
	if (ft_isdigit(input[0]) || input[0] == '?')
		i = 1;
	else
	{
		while (ft_isalnum(input[i]) || input[i] == '_')
			i++;
	}
	word = ft_calloc ((i + 1), sizeof(char));
	if (!word)
		return (NULL);
	len = i - 1;
	i = -1;
	while (i < len)
		word[++i] = input[j++];
	word[i + 1] = '\0';
	return (word);
}

int	is_extendable(char *input, int quotes)
{
	int	i;
	int	counter;

	counter = 1;
	i = 0;
	while (input[i])
	{
		if (input[i] == '\'' && quotes == 0)
			counter *= -1;
		if (input[i] == '$' && input[i + 1] && counter == 1
			&& (ft_isalnum(input[i + 1]) || input[i + 1] == '_'
				|| input[i + 1] == '?'))
			return (i + 1);
		i++;
	}
	return (-1);
}

char	*ft_extender(char *input, char **env, t_mini *mini, int quotes)
{
	int		i;
	char	*word;
	char	*extended;
	char	*replace;

	i = is_extendable(input, quotes);
	if (i == -1)
		return (NULL);
	word = word_assigner(&input[i]);
	if (!word)
		return (NULL);
	replace = env_fetcher(word, env, mini);
	if (!replace)
		return (free(word), NULL);
	extended = input_extender(input, replace, word, i - 1);
	if (!extended)
		return (free(word), free(replace), NULL);
	if (is_extendable(extended, 0) != -1)
	{
		free (word);
		word = ft_extender(extended, env, mini, 0);
		free (extended);
		extended = ft_strdup(word);
	}
	return (free(word), free(replace), extended);
}
