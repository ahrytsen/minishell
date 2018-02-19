/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 15:02:36 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/02/19 17:48:53 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_echo(char **av)
{
	int	i;
	int n;

	i = 0;
	n = 1;
	if (*av && !ft_strcmp(*av, "-n") && ++i)
		n = 0;
	while(av[i])
		ft_printf("%s", av[i++]);
	n ? ft_printf("\n") : 0;
}

void	ft_exit(char **av)
{
	ft_printf("exit\n");
	exit(*av ? ft_atoi(*av) : 0);
}

void 	ft_cd(char **av, const char ***env)
{
	char	*tmp;
	char	*next_path;
	char	curent_path[MAXPATHLEN];

	tmp = NULL;
	next_path = NULL;
	getcwd(curent_path, MAXPATHLEN);
	if (*av && ft_strequ(*av, "-"))
		tmp = "OLDPWD";
	else if ((*av && ft_strequ(*av, "--")) || !*av)
		tmp = "HOME";
	else
		next_path = *av;
	(!next_path && tmp) ? next_path = ft_getenv(*env, tmp) : 0;
	(!next_path && tmp) ? ft_printf("cd: %s not set\n", tmp) : 0;
	(!next_path) ? exit(1) : 0;
	if (chdir(next_path) == -1)
	{
		ft_printf("cd: some error\n");
		exit(1);
	}
	if (*av && ft_strequ(*av, "-"))
		ft_printf("%s\n", next_path);
	ft_setenv(env, "OLDPWD", curent_path, 1);
	ft_setenv(env, "PWD", getcwd(curent_path, MAXPATHLEN), 1);
}
