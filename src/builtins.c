/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 15:02:36 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/02/20 17:56:00 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int		ft_echo(char **av)
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
	return (0);
}

int		ft_exit(char **av)
{
	ft_printf("exit\n");
	exit(*av ? ft_atoi(*av) : 0);
}

int		ft_cd(char **av, const char ***env)
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
	(!next_path) ? ft_printf("cd: %s not set\n", tmp) : 0;
	if (!next_path)
		return (1);
	if (chdir(next_path) == -1)
		return (ft_printf("cd: some error\n") ? 1 : 0);
	if (*av && ft_strequ(*av, "-"))
		ft_printf("%s\n", next_path);
	return ((ft_setenv(env, "OLDPWD", curent_path, 1) ||
			 ft_setenv(env, "PWD", getcwd(curent_path, MAXPATHLEN), 1)));
}

int		ft_unsetenv_builtin(char **av, const char ***env)
{
	while (*av)
		if (ft_unsetenv(*env, *av++))
			return (1);
	return (0);
}

int		ft_setenv_builtin(char **av, const char ***env)
{
	char	*value;

	while (*av)
	{
		value = ft_strchr(*av, '=');
		value ? (*value++ = 0) : 0;
		if (ft_setenv(env, *av++, value, 1))
			return -1;
	}
	return (0);
}
