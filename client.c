/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   client.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: akivioja <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/21 13:52:17 by akivioja      #+#    #+#                 */
/*   Updated: 2023/05/24 17:38:05 by akivioja      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf/ft_printf.h"
#include "libft/libft.h"
#include "minitalk.h"

void	send_bits(int pid, char c)
{
	int	bit;

	bit = 0;
	while (bit < 8)
	{
		if ((c & (0x01 << bit)) != 0)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(100);
		bit++;
	}
}

int	main(int argc, char **argv)
{
	int	count;
	int	pid;

	count = 0;
	if (argc != 3)
		ft_printf("%s\n", "Error message");
	else
	{
		pid = ft_atoi(argv[1]);
		while (argv[2][count] != '\0')
		{
			send_bits(pid, argv[2][count]);
			count++;
		}
		send_bits(pid, argv[2][count]);
	}
	system("leaks client");
	return (0);
}
