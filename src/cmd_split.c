/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 10:48:20 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/03/08 11:51:03 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void		ft_skip_qoutes(char **s)
{
	char	q;

	q = **s;
	while (**s != q)
		if (!**s)
			quotes_error(q);
		else
			(*s)++;
	(*s)++;
}

static size_t	ft_countcmd(char const *s)
{
	char	tmp;
	int		m;
	size_t	res;

	m = 0;
	res = 0;
	while (*s)
	{
		if (*s == '"' || *s == '\'' || *s == '`')
			ft_skip_qoutes(&s);
		else if (*s == '\\' && s++)
			*s ? (s++) : 0;
		else if ((*s != ';' || *s != '|') && !m)
		{
			m = 1;
			res++;
		}
		else if (*s == ';' && m)
			m = 0;
		else if ((*s == '|' || *s == ';') && !m)
			syntax_error();
		s++;
	}
	return (res);
}

char	msh_splitcmd(char *line)
{

}
