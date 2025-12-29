# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: omizin <omizin@student.42heilbronn.de>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/29 16:20:07 by omizin            #+#    #+#              #
#    Updated: 2025/12/29 16:32:11 by omizin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ex00

SRCS_DIR = srcs
INCS_DIR = includes
OBJS_DIR = objs

CC = c++
CFLAGS = -Wall -Wextra -Werror -std=c++17 $(INCLUDE)

INCLUDE = -I$(INCS_DIR)

SRCS = main.cpp BitcoinExchange.cpp

RM = rm -rf

SRCS := $(addprefix $(SRCS_DIR)/, $(SRCS))

OBJS = $(SRCS:$(SRCS_DIR)/%.cpp=$(OBJS_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.cpp | $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

clean:
	$(RM) $(OBJS_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
