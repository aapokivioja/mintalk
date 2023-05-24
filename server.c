/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   server.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: akivioja <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/21 13:52:10 by akivioja      #+#    #+#                 */
/*   Updated: 2023/05/24 17:39:38 by akivioja      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf/ft_printf.h"
#include "libft/libft.h"
#include "minitalk.h"

// Two functions main & handler

t_sh	g_lolz;

void	handler_func(int signal)
{
	static int	bit;
	static int	shifts;
	int			cpy_char;

	cpy_char = 1;
	if (signal == SIGUSR1)
		shifts |= (0x01 << bit);
	bit++;
	if (g_lolz.str == NULL)
		g_lolz.str = "";
	if (bit == 8)
	{
		g_lolz.str = ft_strjoin(g_lolz.str, (const char *)&shifts);
		cpy_char = shifts;
		bit = 0;
		shifts = 0;
	}
	if ((char)cpy_char == '\0')
	{
		ft_printf("%s\n", g_lolz.str);
		free(g_lolz.str);
	}
}

int	main(int argc, char **argv)
{
	int	pid;

	(void)argv;
	pid = getpid();
	ft_printf("%d\n", pid);
	while (argc == 1)
	{
		signal(SIGUSR1, handler_func);
		signal(SIGUSR2, handler_func);
		pause();
	}
	return (0);
}
