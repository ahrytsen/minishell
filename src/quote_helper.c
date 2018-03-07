/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 20:08:03 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/03/07 21:05:38 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_dquote_slash(t_buf **cur, char **line)
{
	if (**line == '"')
		ft_putchar_mshbuf(cur, *(*line)++);
	else if (**line == '$')
		ft_putchar_mshbuf(cur, 8);
	else if (**line == 't')
		ft_putchar_mshbuf(cur, 10);
	else if (**line == 'n')
		ft_putchar_mshbuf(cur, 10);
}
