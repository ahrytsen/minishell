/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 17:32:57 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/02/19 19:54:46 by ahrytsen         ###   ########.fr       */
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
	int		v;
	int		i;
	char	*altpath;
	char	**exec;
}				t_env;
typedef struct	s_builtins
{
	char	*cmd;
	void	(*ft_builtin)();
}				t_builtins;

void			ft_echo(char **av);
void		 	ft_cd(char **av, const char ***env);
void			ft_env(char **av, const char ***env);
char			**ft_cpyenv(char **src_env);
char			*ft_getenv(const char **env, const char *name);
int				ft_setenv(const char ***envp, const char *name,
							const char *value, int overwrite);
int				ft_unsetenv(const char **env, const char *name);
void			ft_clearenv(const char **env);
void			ft_exit(char **av);

#endif
