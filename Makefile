# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rodrigo <rodrigo@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/21 10:00:00 by rodrigo           #+#    #+#             #
#    Updated: 2024/03/21 10:00:00 by rodrigo          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_CLIENT = client
NAME_SERVER = server

SRCS_CLIENT = client.c
SRCS_SERVER = server.c

OBJS_CLIENT = $(SRCS_CLIENT:.c=.o)
OBJS_SERVER = $(SRCS_SERVER:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

PRINTF_DIR = printf
PRINTF = $(PRINTF_DIR)/libftprintf.a

all: $(NAME_CLIENT) $(NAME_SERVER)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(PRINTF):
	make -C $(PRINTF_DIR)

$(NAME_CLIENT): $(OBJS_CLIENT) $(LIBFT) $(PRINTF)
	$(CC) $(CFLAGS) $(OBJS_CLIENT) $(LIBFT) $(PRINTF) -o $(NAME_CLIENT)

$(NAME_SERVER): $(OBJS_SERVER) $(LIBFT) $(PRINTF)
	$(CC) $(CFLAGS) $(OBJS_SERVER) $(LIBFT) $(PRINTF) -o $(NAME_SERVER)

%.o: %.c minitalk.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS_CLIENT) $(OBJS_SERVER)
	make -C $(LIBFT_DIR) clean
	make -C $(PRINTF_DIR) clean

fclean: clean
	rm -f $(NAME_CLIENT) $(NAME_SERVER)
	make -C $(LIBFT_DIR) fclean
	make -C $(PRINTF_DIR) fclean

re: fclean all

.PHONY: all clean fclean re 