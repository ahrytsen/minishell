/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 11:02:52 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/03/13 14:23:00 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	sig_handler(int signo)
{
	if (signo == SIGINT)
		ft_printf("");
	return ;
}

void	msh_init(void)
{
	extern char	**environ;
	int			shlvl;
	char		*tmp;

	msh_get_environ()->env = ft_strdup_arr(environ);
	tmp = ft_getenv("SHLVL");
	shlvl = tmp ? ft_atoi(tmp) : 0;
	tmp = ft_itoa(shlvl + 1);
	ft_setenv("SHLVL", tmp, 1);
	free(tmp);
	signal(SIGINT, sig_handler);
	signal(SIGWINCH, sig_handler);
	signal(SIGINFO, sig_handler);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

int		interact_mod(void)
{
	char	pwd[MAXPATHLEN];
	char	*cmds;
	char	**cmd;
	int		i;

	while (1)
	{
		isatty(1) ? ft_printf("\033[33m%s \033[32m$>\033[0m ",
							getcwd(pwd, MAXPATHLEN)) : 0;
		i = get_next_line(0, &cmds);
		if (!i || i == -1)
			return (!i ? msh_get_environ()->st : 1);
		i = 0;
		cmd = msh_splitsemicolon(cmds);
		while (cmd && cmd[i])
		{
			msh_get_environ()->st = ft_exec(msh_splitwhitespaces(cmd[i]), NULL);
			free(cmd[i++]);
		}
		free(cmd);
		free(cmds);
	}
}

int		script_mod(void)
{
	char	*cmds;
	char	**cmd;
	int		i;

	while (1)
	{
		i = get_next_line(0, &cmds);
		if (!i || i == -1)
			return (!i ? msh_get_environ()->st : 1);
		i = 0;
		cmd = msh_splitsemicolon(cmds);
		while (cmd[i])
		{
			msh_get_environ()->st = ft_exec(msh_splitwhitespaces(cmd[i]), NULL);
			free(cmd[i++]);
		}
		free(cmd);
		free(cmds);
	}
}

int		main(void)
{
	msh_init();
	interact_mod();
	return (msh_get_environ()->st);
}
