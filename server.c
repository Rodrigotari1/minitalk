/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodrigo <rodrigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 10:00:00 by rodrigo           #+#    #+#             */
/*   Updated: 2025/01/25 18:18:57 by rodrigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "libft/libft.h"
#include "printf/ft_printf.h"

void	handle_signal(int signal)
{
	static unsigned char	create_char;
	static int			bit_index;
	static char			*message = NULL;
	static char			temp[2] = {0, 0};

	create_char |= (signal == SIGUSR1);
	bit_index++;
	if (bit_index == 8)
	{
		if (create_char == '\0')
		{
			ft_putstr_fd(message, 1);
			ft_putchar_fd('\n', 1);
			free(message);
			message = NULL;
		}
		else
		{
			temp[0] = create_char;
			if (!message)
				message = ft_strdup(temp);
			else
			{
				char *new_msg = ft_strjoin(message, temp);
				free(message);
				message = new_msg;
			}
		}
		bit_index = 0;
		create_char = 0;
	}
	else
		create_char <<= 1;
}

int	main(void)
{
	ft_printf("%d\n", getpid());
	signal(SIGUSR1, handle_signal);
	signal(SIGUSR2, handle_signal);
	while (1)
		pause();
	return (0);
} 