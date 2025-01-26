/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtari-ca <rtari-ca@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 10:00:00 by rodrigo           #+#    #+#             */
/*   Updated: 2025/01/26 13:42:15 by rtari-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "libft/libft.h"
#include "printf/ft_printf.h"

char temp[2] = {0, 0};

static void process_message(unsigned char create_char, char **message)
{
	if (create_char == '\0')
    {
		ft_putstr_fd(*message, 1);
		ft_putchar_fd('\n', 1);
		free(*message);
		*message = NULL;
	}
	else
	{
		temp[0] = create_char;
		if (!*message)
			*message = ft_strdup(temp);
			else
			{
				char *new_msg = ft_strjoin(*message, temp);
				free(*message);
				*message = new_msg;
			}
		}
}

void handle_signal(int signal)
{
	static unsigned char create_char = 0;
	static int bit_index = 0;
	static char *message = NULL;

	create_char |= (signal == SIGUSR1);
	bit_index++;
	if (bit_index == 8)
	{
		process_message(create_char, &message);
		bit_index = 0;
		create_char = 0;
		}
	else
	{
		create_char <<= 1;
	}
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
