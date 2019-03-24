#include "../includes/minishell.h"

int     ft_echo(char **args)
{
    int n;
    int count;

    count = 0;
    n = 0;
    if (*(args + 1) && ft_strcmp(*(args + 1), "-n") == 0)
    {
        n = 1;
        args++;
    }
    while (*(++args))
    {
        if (count > 0)
            ft_printf(" ");
        ft_printf("%s", *args);
        count++;
    }
    if (n == 0)
        ft_printf("\n");
    return (0);
}

int     ft_pwd(void)
{
    char	buff[PATH_MAX + 1];
    char	*cwd;
    cwd = getcwd(buff, PATH_MAX + 1);
    ft_printf("%s\n", cwd);
    return (0);
}