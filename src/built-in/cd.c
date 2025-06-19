#include <minishell.h>

//SEND PARSED INPUT INSTEAD OF THE WHOLE THING, 
//CUZ NOW YOU ARE TRYING TO TOKENIZE AGAIN DUMBASS

void	ft_cd(t_mini *mini, char **args)
{
	char	*target;
	char	cwd[1024];
	char	*old_pwd;
	char	*pwd_entry;
	char	*old_pwd_entry;

	if (!args[1])
	{
		target = getenv("HOME");
		if (!target)
		{
			printf("cd: HOME not set\n");
			return ;
		}
	}
	else
		target = args[1];
	if (chdir(target) != 0)
	{
		perror ("cd");
		return ;
	}
	old_pwd = getcwd(cwd, sizeof(cwd));
	if (!old_pwd)
		return ;
	pwd_entry = ft_strjoin("PDW=", getcwd(cwd, sizeof(cwd)));
	old_pwd_entry = ft_strjoin("OLDPWD=", old_pwd);
	mini->env = ft_strsjoin(mini->env, pwd_entry);
	mini->env = ft_strsjoin(mini->env, old_pwd_entry);
	free(pwd_entry);
	free(old_pwd_entry);
}