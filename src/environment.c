/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 13:42:48 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/02/15 20:28:35 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*ft_new_env_str(const char *name, const char *value)
{
	char	*new_env;
	size_t	name_l;
	size_t	value_l;

	if (!name)
		return (NULL);
	name_l = ft_strlen(name);
	value_l = value ? ft_strlen(value) : 0;
	if (!(new_env = (char*)malloc(sizeof(char) * (name_l + value_l + 2))))
		return (NULL);
	ft_strcpy(new_env, name);
	new_env[name_l] = '=';
	ft_strcpy(new_env + name_l + 1, value ? value : "");
	return (new_env);
}

char		*ft_getenv(const char **env, const char *name)
{
	size_t	name_l;

	if (!name)
		return (NULL);
	name_l = ft_strlen(name);
	while (*env)
	{
		if (ft_strnequ(*env, name, name_l))
			return (ft_strchr(*env, '=') + 1);
		env++;
	}
	return (NULL);
}

int			ft_setenv(void **envp, const char *name,
						const char *value, int overwrite)
{
	size_t	i;
	char	**env;
	char	*tmp;
	size_t	name_l;

	i = -1;
	env = *envp;
	if (!(tmp = ft_new_env_str(name, value)))
		return (-1);
	name_l = ft_strlen(name);
	while (env[++i])
		if (ft_strnequ(env[i], name, name_l))
		{
			if (!overwrite)
				return (-1);
			free(*env);
			return ((*env = tmp) ? 0 : -1);
		}
	if (!(env = (char**)malloc(sizeof(char*) * (i + 2))))
		return (-1);
	ft_memcpy(env, *envp, sizeof(char*) * i);
	env[i] = tmp;
	env[i + 1] = NULL;
	free(*envp);
	return ((*envp = env) ? 0 : -1);
}

int			ft_unsetenv(const char **env, const char *name)
{
	size_t	name_l;

	if (!name || ft_strchr(name, '='))
		return (-1);
	name_l = ft_strlen(name);
	while (*env)
		if (ft_strnequ(*env++, name, name_l))
			break ;
	if (!*env)
		return (-1);
	while (*env++)
		*(env - 1) = *env;
	return (0);
}
