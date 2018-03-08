/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 16:37:14 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/03/08 14:05:43 by ahrytsen         ###   ########.fr       */
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

void	string_mod(char *cmds)
{
	int		fd[2];
	int		fd_tmp;

	fd_tmp = dup(0);
	pipe(fd);
	dup2(fd[0], 0);
	ft_dprintf(fd[1], cmds);
	free(cmds);
	close(fd[1]);
	script_mod();
	dup2(fd_tmp, 0);
	exit(msh_get_environ()->st);
}

static void	ft_bquote(t_buf **cur, char **line)
{
	char	*st;
	char	*buf;
	int		fd[2];
	int		fd_tmp;

	st = *line;
	while (**line != '`')
		if (!*(*line)++)
			quotes_error('`');
	(*line)++;
	if ((*line - st) == 1)
		return ;
	pipe(fd);
	fd_tmp = dup(1);
	if (fork())
	{
		close(fd[1]);
		while ((get_next_line(fd[0], &buf)) > 0)
		{
			ft_putstr_mshbuf(cur, buf, -1);
			ft_putchar_mshbuf(cur, ' ');
			free(buf);
		}
	}
	else
	{
		close(fd[0]);
		dup2(fd[1], 1);
		string_mod(ft_strsub(st, 0 , *line - st - 1));
	}
	dup2(fd_tmp, 1);
	close(fd[0]);
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
		else if (**line == '`' && (*line)++)
			ft_bquote(cur, line);
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
		else if (*line == '`' && line++)
			ft_bquote(&cur, &line);
		else
			ft_putchar_mshbuf(&cur, *line++);
	free(tmp);
	return (ft_buftostr(head));
}
