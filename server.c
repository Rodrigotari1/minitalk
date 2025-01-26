/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtari-ca <rtari-ca@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 10:00:00 by rodrigo           #+#    #+#             */
/*   Updated: 2025/01/26 13:36:08 by rtari-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "libft/libft.h"
#include "printf/ft_printf.h"

char temp[2] = {0, 0};

static void process_message(unsigned char create_char, char **message)
{
    if (create_char == '\0') // Null terminator received
    {
        ft_putstr_fd(*message, 1);
        ft_putchar_fd('\n', 1);
        free(*message);
        *message = NULL;
    }
    else // Append character to message
    {
        temp[0] = create_char;
        if (!*message)
            *message = ft_strdup(temp); // Start a new message
        else
        {
            char *new_msg = ft_strjoin(*message, temp); // Append character
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

    create_char |= (signal == SIGUSR1); // Set the current bit based on the signal
    bit_index++;
    if (bit_index == 8) // When a full character is formed
    {
        process_message(create_char, &message); // Process the full character
        bit_index = 0; // Reset bit index for the next character
        create_char = 0; // Reset the character accumulator
    }
    else
    {
        create_char <<= 1; // Shift bits to make room for the next bit
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
