/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 17:32:57 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/03/07 14:38:28 by ahrytsen         ###   ########.fr       */
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

typedef struct	s_op
{
	int		v;
	int		i;
	char	*altpath;
	char	**exec;
}				t_op;

typedef struct	s_env
{
	char	**env;
	int		st;
}				t_env;

typedef struct	s_builtins
{
	char	*cmd;
	int		(*ft_builtin)();
}				t_builtins;

typedef struct	s_buf
{
	size_t			id;
	size_t			len;
	char			str[BUFF_SIZE];
	struct s_buf	*next;
}				t_buf;
/*
**				Builtins
*/
int				ft_echo(char **av);
int				ft_cd(char **av);
int				ft_env(char **av);
int				ft_setenv_builtin(char **av);
int				ft_unsetenv_builtin(char **av);
int				ft_exit(char **av);
/*
**				msh
*/
int				ft_exec(char **cmd, char *altpath);
t_env			*msh_get_environ(void);
void			ft_env_print(void);
char			*ft_getenv(const char *name);
int				ft_setenv(const char *name, const char *value, int overwrite);
int				ft_unsetenv(const char *name);
char			*parse_line(char *line);
/*
**				error
*/
void			malloc_fail(void);
void			quotes_error(char q);
/*
**				buffer
*/
t_buf			*ft_new_mshbuf(void);
void			ft_putstr_mshbuf(t_buf **buf, char *str, ssize_t len);
void			ft_putchar_mshbuf(t_buf **buf, char c);
char			*ft_buftostr(t_buf *buf_head);
void			*ft_free_mshbuf(t_buf *buf);

#endif
