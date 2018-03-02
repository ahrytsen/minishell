/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 14:27:36 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/03/02 18:57:47 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	ft_env_usage(char c)
{
	ft_dprintf(2,
			"env: illegal option -- %c\n"
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

static int	ft_env_flags(char ***av, t_op *options)
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
			tmp = (!*(str + 1)) ? *(++*av) : (str + 1);
			*str == 'u' ? ft_unsetenv(tmp) : 0;
			*str == 'u' && options->v
				? ft_printf("#env unset:\t%s\n", tmp) : 0;
			*str == 'P' ? options->altpath = tmp : 0;
			*str == 'S' ? options->exec = ft_strdup_arr(*av) : 0;
			*str == 'S' ? free(options->exec[0]) : 0;
			*str == 'S' ? options->exec[0] = ft_strdup(tmp) : 0;
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
		return ((wait(&st) != -1) ? st : 1);
	ft_bzero(&options, sizeof(t_op));
	while (*av && **av == '-' && !ft_env_flags(&av, &options))
		av++;
	options.i ? ft_clearenv() : 0;
	options.i && options.v ? ft_printf("#env clearing environ\n") : 0;
	while (*av && !options.exec && (tmp = ft_strchr(*av, '=')))
	{
		options.v ? ft_printf("#env setenv:\t%s\n", *av) : 0;
		*tmp = 0;
		ft_setenv(*av++, ++tmp, 1);
	}
	!options.exec && *av ? options.exec = ft_strdup_arr(av) : 0;
	if (options.v && options.exec && (st = -1))
		ft_printf("#env executing: %s\n", options.exec[0]);
	while (options.v && options.exec && options.exec[(++st)])
		ft_printf("#env\targ[%d]= '%s'\n", st, options.exec[st]);
	options.exec ? ft_exec(options.exec, options.altpath)
		: ft_env_print();
	exit(0);
}
