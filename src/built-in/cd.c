#include <minishell.h>

//SEND PARSED INPUT INSTEAD OF THE WHOLE THING, 
//CUZ NOW YOU ARE TRYING TO TOKENIZE AGAIN DUMBASS

char	*ft_get_env_val(char **env, const char *key)
{
	int	i;
	int	key_len;

	key_len = ft_strlen(key);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], key, key_len) == 0 && env[i][key_len] == '=')
			return (&env[i][key_len + 1]);
		i++;
	}
	return (NULL);
}

void	ft_replace_env(char ***env, const char *key, const char *value)
{
	int		i;
	int		key_len;
	char	*new_pwd;
	char	**new_env;
	char	*temp;

	key_len = ft_strlen(key);
	new_pwd = ft_strjoin(key, "=");
	temp = new_pwd;
	new_pwd = ft_strjoin(new_pwd, value);
	free(temp);
	i = 0;
	while ((*env)[i])
	{
		if (ft_strncmp((*env)[i], key, key_len) == 0 && (*env)[i][key_len] == '=')
		{
			free((*env)[i]);
			(*env)[i] = new_pwd;
			return ;
		}
		i++;
	}
	new_env = ft_strsjoin(*env, new_pwd);
	ft_freestrs(*env);
	*env = new_env;
	free(new_pwd);
}

void	ft_cd(t_mini *mini, char **args)
{
	char	*target;
	char	cwd[1024];
	char	*old_pwd;

	if (!args[1])
	{
		target = ft_get_env_val(mini->env, "HOME");
		if (!target)
		{
			printf("cd: HOME not set\n");
			return ;
		}
	}
	else if (strcmp(args[1], "-") == 0)
	{
		target = ft_get_env_val(mini->env, "OLDPWD");
		if (!target)
		{
			printf("cd: OLDPWD not set\n");
			return ;
		}
		printf("%s\n", target);
	}
	else
		target = args[1];
	old_pwd = ft_get_env_val(mini->env, "PWD");
	if (chdir(target) != 0)
	{
		perror ("cd");
		return ;
	}
	if (!getcwd(cwd, sizeof(cwd)))
	{
		perror("cd");
		return ;
	}
	if (old_pwd)
		ft_replace_env(&mini->env, "OLDPWD", old_pwd);
	ft_replace_env(&mini->env, "PWD", cwd);
}