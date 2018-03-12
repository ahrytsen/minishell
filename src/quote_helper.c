/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 20:08:03 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/03/12 16:08:38 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_dquote_slash(t_buf **cur, char **line)
{
	if (**line == 'a')
		ft_putchar_mshbuf(cur, 7);
	else if (**line == 'b')
		ft_putchar_mshbuf(cur, 8);
	else if (**line == 't')
		ft_putchar_mshbuf(cur, 9);
	else if (**line == 'n')
		ft_putchar_mshbuf(cur, 10);
	else if (**line == 'v')
		ft_putchar_mshbuf(cur, 11);
	else if (**line == 'f')
		ft_putchar_mshbuf(cur, 12);
	else if (**line == 'r')
		ft_putchar_mshbuf(cur, 7);
	else if (**line == '0')
	{
		ft_putchar_mshbuf(cur, ft_atoi_base(*line, 8));
		while(**line >= '0' && **line < '8')
			(*line)++;
		return ;
	}
	else if (**line)
		ft_putchar_mshbuf(cur, **line);
	**line ? (*line)++ : 0;
}

void	ft_bquote_slash(t_buf **cur, char **line)
{
	if(!**line)
		return ;
	else if (**line == '`')
		ft_putchar_mshbuf(cur, **line);
	else
	{
		ft_putchar_mshbuf(cur, '\\');
		ft_putchar_mshbuf(cur, **line);
	}
	(*line)++;
}

void	ft_slash(t_buf **cur, char **line)
{
	if(!**line)
		return ;
	else
		ft_putchar_mshbuf(cur, **line);
	(*line)++;
}

void	ft_bquote_helper(t_buf **cur, char *str)
{
	int		fd_put[2];
	int		fd_get[2];
	char	*line;
	int		i;

	pipe(fd_put);
	pipe(fd_get);
	if (fork() && (i = 1))
	{
		close(fd_put[0]);
		close(fd_get[1]);
		ft_dprintf(fd_put[1], "%s", str);
		close(fd_put[1]);
		while (get_next_line(fd_get[0], &line) == 1 && i++)
		{
			i > 2 ? ft_putchar_mshbuf(cur, ' ') : 0;
			ft_putstr_mshbuf(cur, line, -1);
			free(line);
		}
		close(fd_get[0]);
	}
	else
	{
		close(fd_get[0]);
		close(fd_put[1]);
		dup2(fd_put[0], 0);
		dup2(fd_get[1], 1);
		script_mod();
		close(fd_get[1]);
		close(fd_put[0]);
		exit(msh_get_environ()->st);
	}
}
