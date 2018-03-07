/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 18:04:58 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/03/07 14:36:10 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	malloc_fail(void)
{
	ft_dprintf(2, "Fatal error: malloc error occurred\n");
	exit(1);
}

void	quotes_error(char q)
{
	ft_dprintf(2, "msh: unexpected EOF while looking for matching `%c'\n", q);
	exit(2);
}
