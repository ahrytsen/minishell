/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 17:32:57 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/02/15 20:25:45 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <libft.h>
# include <sys/param.h>
# include <signal.h>
# include <term.h>
# include <fcntl.h>
# include <termios.h>


typedef struct	s_builtins
{
	char	*cmd;
	void	(*ft_builtin)();
}				t_builtins;

void			ft_echo(char **av);
char			*ft_getenv(const char **env, const char *name);
int				ft_setenv(void **envp, const char *name,
							const char *value, int overwrite);
int				ft_unsetenv(const char **env, const char *name);
void			ft_exit(char **av);

#endif
