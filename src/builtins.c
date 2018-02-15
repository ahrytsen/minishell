/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 15:02:36 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/02/15 21:18:08 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_echo(char **av)
{
	int	i;
	int n;

	i = 0;
	n = 0;
	ft_strcmp(av[0], "-n") ? n++ : i++;
	while(av[i])
		ft_printf("%s", av[i++]);
	n ? ft_printf("\n") : 0;
}

void	ft_exit(char **av)
{
	exit(0);
}

int 	ft_env(char **argv, char **env)
{

}

/*void 	ft_cd(char **av)
{

}*/
