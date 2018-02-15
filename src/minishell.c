/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 11:02:52 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/02/14 20:20:35 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

const static t_builtins	g_builtins[] =
{
	{"echo", &ft_echo},
/*
**	{"cd", &ft_cd},
**	{"setenv", &ft_setenv},
**	{"unsetenv", &ft_unsetenv},
**	{"env", &ft_env},
*/
	{"exit", &ft_exit},
	{NULL, NULL}
};

void	ft_wrong_cmd(char *w_cmd)
{
	ft_putstr_fd(w_cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
}

void	ft_exec(char **cmd)
{
	int		i;

	i = 0;
	while(g_builtins[i].cmd && ft_strcmp(cmd[0], g_builtins[i].cmd))
		i++;
	g_builtins[i].cmd ? g_builtins[i].ft_builtin(cmd + 1)
		: ft_wrong_cmd(cmd[0]);
	i = 0;
	while (cmd[i])
		free(cmd[i++]);
	free(cmd);
}

void sig_handler(int signo)
{
  if (signo == SIGINT)
	  ft_printf("\n");
  return ;
}

int		main(int ac, char **av, char **env)
{
	char	pwd[MAXPATHLEN];
	char	*cmds;
	char	**cmd;
	int		i;
	struct termios tty;

	tcgetattr (0, &tty);
	tty.c_lflag &= ~(ECHOCTL);
	tcsetattr (0, TCSADRAIN, &tty);
	signal(SIGINT, sig_handler);
	while (1)
	{
		ft_printf("%s $> ", getcwd(pwd, MAXPATHLEN));
		get_next_line(0, &cmds);
		i = 0;
		cmd = ft_strsplit(cmds, ';');
		while (cmd[i])
		{
			ft_exec(ft_strsplit(cmd[i], ' '));
			free(cmd[i++]);
		}
		free(cmd);
	}
	free(cmds);
}

/* int main(void) */
/* { */
/*   if ( == SIG_ERR) */
/* 	  ft_printf("\ncan't catch SIGINT\n"); */
/*   // A long long wait so that we can easily issue a signal to this process */
/*   while(1) */
/*     sleep(1); */
/*   return 0; */
/* } */
