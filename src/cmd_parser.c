/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 16:37:14 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/03/07 21:44:01 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	parse_dollar(t_buf **cur, char **line)
{
	char	*st;
	char	*tmp;


	st = *line;
	if (*st == '0' && (*line)++)
	{
		ft_putstr_mshbuf(cur, "msh", -1);
		return ;
	}
	else if (!ft_isalnum(*st) && *st != '_')
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

static void	ft_quote(t_buf **cur, char **line)
{
	char	*st;

	st = *line;
	while (**line != '\'')
	{
		if (!**line)
			quotes_error('\'');
		(*line)++;
	}
	ft_putstr_mshbuf(cur, st, *line - st);
	(*line)++;
}

static void	ft_dquote(t_buf **cur, char **line)
{
	while (**line != '"')
		if (!**line)
			quotes_error('"');
		else if (**line == '\\' && (*line)++)
		{
			if (**line == '"' || **line == '$')
				ft_putchar_mshbuf(cur, *(*line)++);
			else
				ft_putchar_mshbuf(cur, '\\');
		}
		else if (**line == '$' && (*line)++)
			parse_dollar(cur, line);
		else
			ft_putchar_mshbuf(cur, *(*line)++);
	(*line)++;
}

char		*parse_line(char *line)
{
	char	*tmp;
	t_buf	*head;
	t_buf	*cur;

	tmp = line;
	(!(head = ft_memalloc(sizeof(t_buf))) || !line) ? malloc_fail() : 0;
	cur = head;
	while (*line)
		if (*line == '\\' && line++)
			ft_putchar_mshbuf(&cur, *line ? *line++ : *line);
		else if (*line == '$' && line++)
			parse_dollar(&cur, &line);
		else if (*line == '~' && line++)
			ft_putstr_mshbuf(&cur, ft_getenv("HOME"), -1);
		else if (*line == '\'' && line++)
			ft_quote(&cur, &line);
		else if (*line == '"' && line++)
			ft_dquote(&cur, &line);
	/*else if (*line == '`' && line++)
	  ft_bquote(&cur, &line);*/
		else
			ft_putchar_mshbuf(&cur, *line++);
	free(tmp);
	return (ft_buftostr(head));
}
