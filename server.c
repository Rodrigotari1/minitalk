/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rodrigo <rodrigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 10:00:00 by rodrigo           #+#    #+#             */
/*   Updated: 2025/01/26 13:57:11 by rodrigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "libft/libft.h"
#include "printf/ft_printf.h"

static char	g_temp[2] = {0, 0};

static void	process_message(unsigned char create_char, char **message)
{
	char	*new_msg;

	if (create_char == '\0')
	{
		ft_putstr_fd(*message, 1);
		ft_putchar_fd('\n', 1);
		free(*message);
		*message = NULL;
	}
	else
	{
		g_temp[0] = create_char;
		if (!*message)
			*message = ft_strdup(g_temp);
		else
		{
			new_msg = ft_strjoin(*message, g_temp);
			free(*message);
			*message = new_msg;
		}
	}
}

static void	handle_signal(int signal)
{
	static char				*message;
	static int				bit_index;
	static unsigned char	create_char;

	create_char = (create_char << 1) | (signal == SIGUSR1);
	bit_index++;
	if (bit_index == 8)
	{
		process_message(create_char, &message);
		bit_index = 0;
		create_char = 0;
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
