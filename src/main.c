#include "../includes/minishell.h"

int     run_builtins(char **args, char **envp)
{
    if (envp)
        ;
    if (ft_strcmp(args[0], "exit") == 0)
    {
        ft_printf("goodbye\n");
        return (0);
    }
    else if (ft_strcmp(args[0], "env") == 0)
    {
        while (*envp)
            ft_printf("%s\n", *(envp++));
        ft_printf("\n");
        return (1);
    }
    return (2);
}

int        run_command(char **args, char **envp)
{
    pid_t	pid;
	int		status;
    int     ret;

    ret = 0;
    if ((ret = run_builtins(args, envp)) != 2)
        return (ret);
	pid = fork();
	if (pid == 0)
	{
		if (execve(args[0], args, envp) == -1)
		{
			ft_printf("permission denied\n");
		}
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		ft_printf("msh: unable to fork process\n");
		exit(EXIT_FAILURE);
	}
	wait(&status);
    return (1);
}

void        print_prompt(void)
{
    char	buff[PATH_MAX + 1];
    char	*cwd;
    cwd = getcwd(buff, PATH_MAX + 1);
    ft_printf("\033[37m%s \033[31m$>\033[37m", cwd);
}

char        **get_args(void)
{
    char    *line;
    char    **array;
    print_prompt();
    if (!(get_next_line(0, &line)))
        return (0);
    array = ft_strsplit(line, ' ');
    free (line);
    return (array);
}

void        sh_loop(char **envp)
{
    int     stat;
    char    **args;

    stat = 1;
    args = 0;
    while (stat)
    {
        args = get_args();
        stat = run_command(args, envp);
        ft_arraydel(args);
    }
}
char        **make_env(void)
{
    int     i;
    extern char	**environ;
    char    **ret;

    i = 0;
    while (environ[i])
        i++;
    if (!(ret = ft_memalloc(sizeof(char*) * (i + 1))))
        return (0);
    i = 0;
    while (environ[i])
    {
        ret[i] = ft_strdup(environ[i]);
        i++;
    }
    return (ret);
}

int        main(void)
{
    char    **env;

    if (!(env = make_env()))
        return (1);
    sh_loop(env);
    ft_arraydel(env);
    return (0);
}
