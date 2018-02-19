/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 11:02:52 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/02/19 21:05:54 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

const static t_builtins	g_builtins[] =
{
	{"echo", &ft_echo},
	{"cd", &ft_cd},
/*
**	{"setenv", &ft_setenv},
**	{"unsetenv", &ft_unsetenv},
*/
	{"env", &ft_env},
	{"exit", &ft_exit},
	{NULL, NULL}
};

char		*ft_search_exec(char **cmd, char **env, char *altpath)
{
	int				i;
	char			*exec_path;
	char			**path;

	i = 0;
	exec_path = NULL;
	if (!(path = ft_strsplit(altpath ? altpath : ft_getenv(env, "PATH"), ':')))
		return (NULL);
	while (path[i])
	{
		if (!(exec_path = malloc(ft_strlen(path[i]) + ft_strlen(*cmd) + 2)))
			return (NULL);
		ft_strcpy(exec_path, path[i]);
		ft_strcat(exec_path, "/");
		ft_strcat(exec_path, *cmd);
		if (!access(exec_path, X_OK))
			break;
		ft_memdel(&exec_path);
		free(path[i++]);
	}
	while (path[i])
		free(path[i++]);
	free(path);
	return (exec_path);
}

void	ft_exec(char **cmd, char ***env, char *altpath)
{
	int		i;

	i = 0;
	if (!ft_strchr(*cmd, '/'))
	{
		while(g_builtins[i].cmd && ft_strcmp(cmd[0], g_builtins[i].cmd))
			i++;
		g_builtins[i].cmd ? g_builtins[i].ft_builtin(cmd + 1, env)
			: ft_wrong_cmd(cmd[0]);
	}
	else
	{
		if (access(*cmd, X_OK) == 0)
			fork() ? wait(&i) : execve(*cmd, cmd, env);
		else
			ft_dprintf(2, "%s: command not found or permission denied\n", *cmd);
	}
	i = 0;
	while (cmd[i])
		free(cmd[i++]);
	free(cmd);
}

void	sig_handler(int signo)
{
  if (signo == SIGINT)
	  ft_printf("\n");
  return ;
}

int		main(int ac, char **av, char **envp)
{
	char	**env;
	char	pwd[MAXPATHLEN];
	char	*cmds;
	char	**cmd;
	int		i;
	/*struct termios tty;

	tcgetattr (0, &tty);
	tty.c_lflag &= ~(ECHOCTL);
	tcsetattr (0, TCSADRAIN, &tty);*/
	signal(SIGINT, sig_handler);
	env = ft_cpyenv(envp);
	while (1)
	{
		ft_printf("%s $> ", getcwd(pwd, MAXPATHLEN));
		get_next_line(0, &cmds);
		i = 0;
		cmd = ft_strsplit(cmds, ';');
		while (cmd[i])
		{
			ft_exec(ft_strsplit(cmd[i], ' '), &env);
			free(cmd[i++]);
		}
		free(cmd);
	}
	free(cmds);
}
