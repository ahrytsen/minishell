/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 16:45:16 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/03/14 21:36:05 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

#ifdef unix
static char term_buffer[2048];
#else
#define term_buffer 0
#endif

void	init_terminal_data()
{
  char	*termtype = getenv ("TERM");
  int 	success;

  if (termtype == 0)
	  ft_dprintf(2, "Specify a terminal type with `setenv TERM <yourtype>'.\n");
  success = tgetent (term_buffer, termtype);
  if (success < 0)
    ft_dprintf(2, "Could not access the termcap data base.\n");
  if (success == 0)
    ft_dprintf(2, "Terminal type `%s' is not defined.\n", termtype);
}

char	*ft_readline(char *promt)
{

	while (1)
	{

	}
}
