/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahrytsen <ahrytsen@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 11:02:52 by ahrytsen          #+#    #+#             */
/*   Updated: 2018/02/09 20:54:10 by ahrytsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_cd(char *path)
{
	chdir(path);
}

int		main(void)
{
	char	test[MAXPATHLEN];
	char	*line;

	while(1)
	{
		ft_printf("%s $>", getcwd(test, MAXPATHLEN));
		ft_bzero(test, MAXPATHLEqN);
		get_next_line(1, &line);
	}
}

/* void sig_handler(int signo) */
/* { */
/*   if (signo == SIGINT) */
/*     ft_printf("received SIGINT\n"); */
/* } */

/* int main(void) */
/* { */
/*   if (signal(SIGINT, sig_handler) == SIG_ERR) */
/*   ft_printf("\ncan't catch SIGINT\n"); */
/*   // A long long wait so that we can easily issue a signal to this process */
/*   while(1) */
/*     sleep(1); */
/*   return 0; */
/* } */
