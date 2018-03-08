/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 15:02:36 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/03/08 20:44:40 by ahrytsen         ###   ########.fr       */
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
	while (av[i])
	{
		ft_printf("%s", av[i++]);
		av[i] ? ft_printf(" ") : 0;
	}
	n ? ft_printf("\n") : 0;
	return (0);
}

int		ft_exit(char **av)
{
	char	*tmp;

	ft_printf("exit\n");
	if (av && *av)
	{
		tmp = *av;
		while (*tmp)
			if (!ft_isdigit(*tmp++))
			{
				ft_dprintf(2, "exit: %s: numeric argument required\n", *av);
				exit(-1);
			}
	}
	if (av && *av && *(av + 1))
	{
		ft_dprintf(2, "exit: too many arguments\n");
		return (1);
	}
	exit((av && *av) ? ft_atoi(*av) : msh_get_environ()->st);
}

int		ft_cd(char **av)
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
	(!next_path && tmp) ? next_path = ft_getenv(tmp) : 0;
	(!next_path) ? ft_dprintf(2, "cd: %s not set\n", tmp) : 0;
	if (!next_path)
		return (1);
	if (chdir(next_path) == -1)
		return (ft_dprintf(2, "cd: some error\n") ? 1 : 0);
	if (*av && ft_strequ(*av, "-"))
		ft_printf("%s\n", next_path);
	return ((ft_setenv("OLDPWD", curent_path, 1) ||
			ft_setenv("PWD", getcwd(curent_path, MAXPATHLEN), 1)));
}

int		ft_unsetenv_builtin(char **av)
{
	int	ret;

	ret = 0;
	if (!av)
		return (1);
	while (*av)
		if (ft_unsetenv(*av++))
			ret = 1;
	return (ret);
}

int		ft_setenv_builtin(char **av)
{
	char	*value;
	int		i;
	int		ret;

	ret = 0;
	if (!av)
		return (1);
	else if (!*av)
		ft_env_print();
	while (*av)
	{
		value = ft_strchr(*av, '=');
		value ? (*value++ = 0) : 0;
		i = -1;
		while ((*av)[++i])
			if (((i && !ft_isalnum((*av)[i])) || (!i && !ft_isalpha((*av)[i])))
				&& (*av)[i] != '_')
				ft_dprintf(2, "setenv: `%s': not a valid identifier\n", *av++);
		if (ft_setenv(*av++, value, 1))
			ret = 1;
	}
	return (ret);
}
