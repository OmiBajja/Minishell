/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obajja <obajja@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 00:53:56 by obajja            #+#    #+#             */
/*   Updated: 2025/05/08 15:44:59 by obajja           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void ft_pwd(char **envp)
{
	int i;
	char *pwd;

	i = 0;
	while (!ft_strstr(envp[i],"PWD="))
		i++;
	pwd = ft_strstr(envp[i],"PWD=");
	printf("%s\n",&pwd[4]);
}