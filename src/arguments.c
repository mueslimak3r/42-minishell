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

static void		msh_count_quotes(char **line, int *words, char quote, int *ret)
{
	*ret = 0;
	(*line)++;
	while ((**line) != quote && (**line))
		(*line)++;
	if (**line)
	{
		(*line)++;
		(*words)++;
	}
	else
		*ret = 1;
}

static int		count_words(char *line)
{
	int			words;
	int			ret;

	words = 0;
	while (*line)
	{
		while (*line <= 32 && *line != '\0')
			line++;
		if ((*line == '\"' && *(line + 1) != '\"') ||
			(*line == '\'' && *(line + 1) != '\''))
		{
			msh_count_quotes(&line, &words, *line, &ret);
			if (ret == 1)
				return (words);
		}
		if (*line > 32 && *line != '\"' && *line != '\'')
			words++;
		while (*line > 32 && *line != '\"' && *line != '\'')
			line++;
		if ((*line == '\"' && *(line + 1) == '\"') ||
			(*line == '\'' && *(line + 1) == '\''))
			line += 2;
	}
	return (words);
}

static char		*msh_handle_quotes(char *line, int *j, char quote)
{
	int			size;

	size = 0;
	(*j)++;
	while (line[*j] != quote && line[*j])
	{
		size++;
		(*j)++;
	}
	if (line[*j])
	{
		(*j)++;
		return (ft_strndup(line + *j - size - 1, size));
	}
	else
		return (ft_strdup(""));
}

static char		*msh_next_word(char *line, int *j)
{
	int			size;

	while (line[*j])
	{
		while (line[*j] <= 32 && line[*j] != '\0')
			(*j)++;
		if ((line[*j] == '\"' && line[*j + 1] != '\"') ||
			(line[*j] == '\'' && line[*j + 1] != '\''))
			return (msh_handle_quotes(line, j, line[*j]));
		if (line[*j] > 32 && line[*j] != '\"' && line[*j] != '\'')
		{
			size = 0;
			while (line[*j + size] > 32 && line[*j + size] != '\"'
												&& line[*j + size] != '\'')
				size++;
			while (line[*j] > 32 && line[*j] != '\"' && line[*j] != '\'')
				(*j)++;
			return (ft_strndup(line + *j - size, size));
		}
		if ((line[*j] == '\"' && line[*j + 1] == '\"') ||
			(line[*j] == '\'' && line[*j + 1] == '\''))
			*j += 2;
	}
	return (NULL);
}

char			**arg_parser(char *line)
{
	int			i;
	int			j;
	int			words;
	char		**ret;

	i = 0;
	j = 0;
	if (!line)
		return (NULL);
	words = count_words(line);
	ret = (char **)ft_memalloc(sizeof(char *) * (words + 1));
	while (i < words)
		ret[i++] = msh_next_word(line, &j);
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
			if ((find_env(envp, args[i] + 1)) == -1 ||
				!get_env(envp, args[i] + 1, &(new)))
				return (0);
			free(args[i]);
			args[i] = new;
		}
		else if (args[i][0] == '~')
		{
			if ((find_env(envp, "HOME")) == -1 ||
				!get_env(envp, "HOME", &new))
				return (0);
			out = ft_makepath(new, args[i] + 1, '/');
			free(args[i]);
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
