/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 17:32:57 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/02/22 20:59:11 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <libft.h>
# include <sys/param.h>
# include <sys/types.h>
# include <sys/dir.h>
# include <dirent.h>
# include <signal.h>
# include <term.h>
# include <fcntl.h>
# include <termios.h>

typedef struct	s_env
{
	char	**env;
}				t_env;
typedef struct	s_builtins
{
	char	*cmd;
	int		(*ft_builtin)();
}				t_builtins;

/*
**				Builtins
*/
int				ft_echo(char **av);
int			 	ft_cd(char **av, const char ***env);
int				ft_env(char **av, const char ***env);
int				ft_setenv_builtin(char **av, const char ***env);
int				ft_unsetenv_builtin(char **av, const char ***env);
int				ft_exit(char **av);
/*
**
*/
void			ft_exec(char **cmd, const char ***env, char *altpath);
char			**ft_cpyenv(const char **src_env);
char			*ft_getenv(const char **env, const char *name);
int				ft_setenv(const char ***envp, const char *name,
							const char *value, int overwrite);
int				ft_unsetenv(const char **env, const char *name);
void			ft_clearenv(const char **env);

#endif
