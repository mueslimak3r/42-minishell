/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calamber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 10:22:27 by calamber          #+#    #+#             */
/*   Updated: 2019/03/24 10:23:36 by calamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <unistd.h>
# include <dirent.h>
# include <errno.h>

# define PATH_MAX 255

typedef struct	s_env
{
	char		**envp;
	int			size;
}				t_env;

int				ft_echo(char **args);
int				ft_pwd(void);
int				ft_cd(char **args, t_env *env);
int				ft_setenv(char *name, char *val, t_env *env);
int				ft_unsetenv(char *name, t_env *env);
int				ft_env(char **envp);
int				make_env(t_env *env);
int				get_env(char **envp, char *name, char **env_var);
char			**get_args(char **envp);
int				check_path(char **name, char **args, char **envp);
char			**arg_parser(char *line);
int				find_env(char **envp, char *name);
int				run_builtins(char **args, t_env *env);
char			*sh_next_word(char *line, int *j);
int				sh_count_words(char *line);

#endif
