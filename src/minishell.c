/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 11:02:52 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/02/27 21:45:01 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>


void	sig_handler(int signo)
{
  if (signo == SIGINT)
	  ft_printf("");
  return ;
}

void	msh_init()
{
	extern char	**environ;
	int			shlvl;
	char		*tmp;

	msh_get_environ()->env = ft_strdup_arr(environ);
	tmp = ft_getenv("SHLVL");
	shlvl = tmp ? ft_atoi(tmp) : 0;
	ft_setenv("SHLVL", ft_itoa(shlvl + 1), 1);
	signal(SIGINT, sig_handler);
	signal(SIGWINCH, sig_handler);
	signal(SIGINFO, sig_handler);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

int		main(void)
{
	char	pwd[MAXPATHLEN];
	int		st;
	char	*cmds;
	char	**cmd;
	int		i;
/*	struct termios tty;

	tcgetattr (0, &tty);
	tty.c_lflag &= ~(ECHOCTL);
	tcsetattr (0, TCSASOFT, &tty);

	env = ft_cpyenv(envp);*/
	msh_init();
	ft_printf("%s $> ", getcwd(pwd, MAXPATHLEN));
	while (get_next_line(0, &cmds))
	{
		i = 0;
		cmd = ft_strsplit(cmds, ';');
		while (cmd[i])
		{
			st = ft_exec(ft_strsplit(cmd[i], ' '), NULL);
			free(cmd[i++]);
		}
		free(cmd);
		free(cmds);
		st != -1 ?ft_printf("%s $> ", getcwd(pwd, MAXPATHLEN)) : 0;
	}
}
