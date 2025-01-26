/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtari-ca <rtari-ca@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 10:00:00 by rodrigo           #+#    #+#             */
/*   Updated: 2025/01/26 13:41:55 by rtari-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdlib.h>
#include "printf/ft_printf.h"
#include "libft/libft.h"

static void	send_signal(int pid, unsigned char c)
{
	int	bit;

	bit = 7;
	while (bit >= 0)
	{
		if (c & (1 << bit))
		{
			if (kill(pid, SIGUSR1) == -1)
				exit(1);
		}
		else
		{
			if (kill(pid, SIGUSR2) == -1)
				exit(1);
		}
		bit--;
		usleep(100);
	}
}

int	main(int argc, char *argv[])
{
	pid_t	server_pid;
	char	*message;

	if (argc != 3)
	{
		ft_printf("Error: Usage: %s <server_pid> <message>\n", argv[0]);
		return (1);
	}
	server_pid = ft_atoi(argv[1]);
	if (server_pid <= 0)
	{
		ft_printf("Error: Invalid PID\n");
		return (1);
	}
	message = argv[2];
	while (*message)
		send_signal(server_pid, *message++);
	send_signal(server_pid, '\0');  // Send null terminator
	return (0);
}
