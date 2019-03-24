/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calamber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 10:09:22 by calamber          #+#    #+#             */
/*   Updated: 2019/03/24 10:10:50 by calamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			run_builtins(char **args, t_env *env)
{
	if (ft_strcmp(args[0], "exit") == 0)
		return (1);
	else if (ft_strcmp(args[0], "env") == 0)
		return (ft_env(env->envp));
	else if (ft_strcmp(args[0], "echo") == 0)
		return (ft_echo(args));
	else if (ft_strcmp(args[0], "pwd") == 0)
		return (ft_pwd());
	else if (ft_strcmp(args[0], "setenv") == 0)
		return (ft_setenv(args[1] ? args[1] : 0, (args[2] ? args[2] : 0), env));
	else if (ft_strcmp(args[0], "unsetenv") == 0)
		return (ft_unsetenv(args[1], env));
	else if (ft_strcmp(args[0], "cd") == 0)
		return (ft_cd(args, env));
	return (2);
}

int			run_command(char *name, char **args, char **envp)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		if (execve(name, args, envp) == -1)
		{
			ft_printf("command not found: %s\n", *args);
		}
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		ft_printf("unable to fork process\n");
		exit(EXIT_FAILURE);
	}
	wait(&status);
	return (status);
}

int			run_dispatch(char **args, t_env *env)
{
	int		ret;
	char	*name;

	name = 0;
	if (!(*args))
		return (0);
	if ((ret = run_builtins(args, env)) != 2)
		return (ret);
	ret = 0;
	if (check_path(&name, args, env->envp))
	{
		ret = run_command(name, args, env->envp);
		free(name);
	}
	else
		ret = run_command(args[0], args, env->envp);
	return (ret);
}

int			check_return(char **args, int stat)
{
	if (stat)
		;
	if (args[0] && ft_strcmp(args[0], "exit") == 0)
	{
		ft_printf("goodbye\n");
		return (1);
	}
	return (0);
}

void		sh_loop(t_env *env)
{
	char	**args;
	int		quit;

	quit = 0;
	args = 0;
	while (!quit)
	{
		args = get_args(env->envp);
		if (!args)
			continue ;
		quit = check_return(args, run_dispatch(args, env));
		ft_arraydel(args);
	}
}

int			main(void)
{
	t_env	env;

	ft_bzero(&env, sizeof(t_env));
	if (!make_env(&env))
		return (1);
	sh_loop(&env);
	ft_arraydel(env.envp);
	return (0);
}
