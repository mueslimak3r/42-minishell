/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calamber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 10:14:12 by calamber          #+#    #+#             */
/*   Updated: 2019/03/24 10:26:24 by calamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char			**arg_parser(char *line)
{
	int			i;
	int			j;
	int			words;
	char		**ret;

	i = -1;
	j = 0;
	if (!line)
		return (0);
	words = sh_count_words(line);
	ret = (char **)ft_memalloc(sizeof(char *) * (words + 1));
	while (++i < words)
		ret[i] = sh_next_word(line, &j);
	return (ret);
}

char			**expand_args(char **args, char **envp)
{
	int			i;
	char		*new;
	char		*out;

	i = 0;
	while (args[i])
	{
		if (args[i][0] == '$')
		{
			if (!get_env(envp, args[i] + 1, &new))
				return (0);
			free(args[i]);
			args[i] = new;
		}
		else if (args[i][0] == '~')
		{
			if (!get_env(envp, "HOME", &new))
				return (0);
			out = ft_makepath(new, args[i] + 1, '/');
			free(args[i]);
			free(new);
			args[i] = out;
		}
		i++;
	}
	return (args);
}

char			**get_args(char **envp)
{
	char		*line;
	char		**array;

	if (envp)
		;
	ft_printf("\033[31m$>\033[37m");
	if (!(get_next_line(0, &line)))
		return (0);
	array = arg_parser(line);
	free(line);
	array = expand_args(array, envp);
	return (array);
}
