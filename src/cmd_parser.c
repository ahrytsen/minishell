/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 16:37:14 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/03/02 21:01:34 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	parse_dollar(t_buf **cur, char **line)
{
	char	*st;
	char	*tmp;

	st = *line;
	if (!ft_isalnum(*st) && *st != '_')
	{
		ft_putchar_mshbuf(cur, '$');
		return ;
	}
	while (ft_isalnum(**line) || **line == '_')
		(*line)++;
	tmp = ft_strsub(st, 0, *line - st);
	ft_putstr_mshbuf(cur, ft_getenv(tmp), -1);
	free(tmp);
}

char		*parse_line(char *line)
{
	char	*tmp;
	t_buf	*head;
	t_buf	*cur;

	tmp = line;
	if (!(head = ft_memalloc(sizeof(t_buf))) || !line)
		malloc_fail();
	cur = head;
	while (*line)
	{
		if (*line == '$' && line++)
			parse_dollar(&cur, &line);
		else if (*line == '~' && line++)
			ft_putstr_mshbuf(&cur, ft_getenv("HOME"), -1);
		else
			ft_putchar_mshbuf(&cur, *line++);
	}
	free(tmp);
	return (ft_buftostr(head));
}
