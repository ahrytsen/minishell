/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 16:37:14 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/02/22 17:17:24 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	quote_checker(char **line)
{
	t_quote	quote[3];

	quote = {
		{'\'', "quote", 0},

	}
	while (**line)
	{
		if (**line == '\'')
			while (**line && )
			{

			}

	}
}
