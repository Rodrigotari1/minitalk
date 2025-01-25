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

CC = gcc
CFLAGS = -Wall -Wextra -Werror
CLIENT_SRCS = client.c
SERVER_SRCS = server.c
LIBFT_DIRECTORY = libft
FT_PRINTF_DIRECTORY = printf
LIBFT_ARCHIVE = $(LIBFT_DIRECTORY)/libft.a
FT_PRINTF_ARCHIVE = $(FT_PRINTF_DIRECTORY)/libftprintf.a
CLIENT_NAME = client
SERVER_NAME = server

all: $(CLIENT_NAME) $(SERVER_NAME)

$(CLIENT_NAME): $(CLIENT_SRCS) $(LIBFT_ARCHIVE) $(FT_PRINTF_ARCHIVE)
	$(CC) $(CFLAGS) -o $@ $(CLIENT_SRCS) -L$(LIBFT_DIRECTORY) -lft -L$(FT_PRINTF_DIRECTORY) -lftprintf

$(SERVER_NAME): $(SERVER_SRCS) $(LIBFT_ARCHIVE) $(FT_PRINTF_ARCHIVE)
	$(CC) $(CFLAGS) -o $@ $(SERVER_SRCS) -L$(LIBFT_DIRECTORY) -lft -L$(FT_PRINTF_DIRECTORY) -lftprintf

$(LIBFT_ARCHIVE):
	$(MAKE) -C $(LIBFT_DIRECTORY)

$(FT_PRINTF_ARCHIVE):
	$(MAKE) -C $(FT_PRINTF_DIRECTORY)

clean:
	$(MAKE) -C $(LIBFT_DIRECTORY) clean
	$(MAKE) -C $(FT_PRINTF_DIRECTORY) clean

fclean: clean
	$(MAKE) -C $(LIBFT_DIRECTORY) fclean
	$(MAKE) -C $(FT_PRINTF_DIRECTORY) fclean
	rm -f $(CLIENT_NAME) $(SERVER_NAME)

re: fclean all

.PHONY: all clean fclean re
