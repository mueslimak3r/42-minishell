/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calamber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 10:11:17 by calamber          #+#    #+#             */
/*   Updated: 2019/03/24 10:27:15 by calamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			changedir(char *name, char *cwd, t_env *env)
{
	char	buff[PATH_MAX + 1];
	char	*new;

	if (!name || !cwd)
		return (0);
	ft_unsetenv("PWD", env);
	ft_unsetenv("OLDPWD", env);
	if (chdir(name) != 0)
	{
		ft_putstr_fd(name, 2);
		ft_putstr_fd(" was killed long ago, before your time.\n", 2);
		return (0);
	}
	new = getcwd(buff, PATH_MAX + 1);
	if (!(ft_setenv("PWD", new, env) || ft_setenv("OLDPWD", cwd, env)))
		return (0);
	return (1);
}

int			do_cd(char *cwd, char **args, t_env *env)
{
	char	*new;

	new = 0;
	if (!args[1])
	{
		if (!get_env(env->envp, "HOME", &new))
			return (-1);
		changedir(new, cwd, env);
		free(new);
	}
	else
	{
		if (ft_strcmp(args[1], "-") == 0)
		{
			if (!get_env(env->envp, "OLDPWD", &new))
				return (-1);
			changedir(new, cwd, env);
			free(new);
		}
		else
			changedir(args[1], cwd, env);
	}
	return (0);
}

int			ft_cd(char **args, t_env *env)
{
	char	*cwd;
	char	buff[PATH_MAX + 1];

	cwd = getcwd(buff, PATH_MAX + 1);
	return (do_cd(cwd, args, env));
}
