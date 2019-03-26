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

int			run_command(char *name, char **args, char **envp)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		if (execve(name, args, envp) == -1)
			ft_putstr_fd("don't talk to me like that!\n", 2);
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		ft_putstr_fd("fork malfunction. Please use spoon\n", 2);
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
		ft_printf("don't call me\n");
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
		{
			ft_arraydel(args);
			continue ;
		}
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
