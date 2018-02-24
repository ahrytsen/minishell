/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 17:09:28 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/02/23 17:20:52 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <env.h>

static void	ft_env_usage(char c)
{
	ft_printf("env: illegal option -- %c\n"
			"usage: env [-iv] [-P utilpath] [-S string] [-u name]\n"
			"           [name=value ...] [utility [argument ...]]\n", c);
	exit(1);
}

static void	ft_env_print(void)
{
	char **env;

	env = msh_get_environ()->env;
	while (env && *env)
		ft_printf("%s\n", *env++);
}

static void	ft_clearenv(void)
{
	char **env;

	env = msh_get_environ()->env;
	while (env && *env)
	{
		free((void*)*env);
		*env = NULL;
		env++;
	}
}

static int	ft_env_flags(char ***av, const char **env, t_env *options)
{
	char	*str;
	char	*tmp;

	str = **av;
	while (*++str)
		if (*str == 'i')
			options->i = 1;
		else if (*str == 'v')
			options->v++
				? ft_printf("#env verbosity now at %d\n", options->v) : 0;
		else if (*str == 'u' || *str == 'S' || *str == 'P')
		{
			if (!*(str + 1))
				tmp = *(++*av);
			else
				tmp = str + 1;
			*str == 'u' ? ft_unsetenv(env, tmp) : 0;
			*str == 'u' && options->v
				? ft_printf("#env unset:\t%s\n", tmp) : 0;
			*str == 'P' ? options->altpath = tmp : 0;
			*str == 'S' ? options->exec = *av : 0;
			return (*str == 'S' ? 1 : 0);
		}
		else
			ft_env_usage(*str);
	return (0);
}

int			ft_env(char **av)
{
	char	*tmp;
	int		st;
	t_op	options;

	if (fork())
	{
		wait(&st);
		return (st);
	}
	ft_bzero(&options, sizeof(t_env));
	while (*av && **av == '-' && !ft_env_flags(&av, *env, &options))
		av++;
	options.i ? ft_clearenv() : 0;
	options.i && options.v ? ft_printf("#env clearing environ\n") : 0;
	while (*av && !options.exec && (tmp = ft_strchr(*av, '=')))
	{
		options.v ? ft_printf("#env setenv:\t%s\n", *av) : 0;
		*tmp = 0;
		ft_setenv(*av++, ++tmp, 1);
	}
	!options.exec && *av ? options.exec = av : 0;

	options.exec ? ft_exec(options.exec, env, options.altpath)
		: ft_env_print(*env);
	exit(0);
}
