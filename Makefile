# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tmaluh <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/13 10:24:13 by tmaluh            #+#    #+#              #
#    Updated: 2019/08/14 21:42:21 by tmaluh           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := bin/name
NPWD := $(CURDIR)/$(NAME)

CC := gcc -march=native -mtune=native -Ofast -flto -pipe
CC_DEBUG := gcc -march=native -mtune=native -g3 -D DEBUG
CFLAGS := -Wall -Wextra -Werror -Wunused
IFLAGS := -I $(CURDIR)/includes \

SRCS := $(abspath $(wildcard srcs/*.c srcs/*/*.c srcs/*/*/*.c))
OBJ := $(SRCS:.c=.o)

DEL := rm -rf

WHITE := \033[0m
BGREEN := \033[42m
GREEN := \033[32m
RED := \033[31m
INVERT := \033[7m

SUCCESS := [$(GREEN)✓$(WHITE)]
SUCCESS2 := [$(INVERT)$(GREEN)✓$(WHITE)]

all: $(NAME)

$(OBJ): %.o: %.c
	@echo -n ' $@: '
	@$(CC) -c $(CFLAGS) $(LIBSINC) $(IFLAGS) $< -o $@
	@echo "$(SUCCESS)"

bin_dir:
	@mkdir -p bin

$(NAME): bin_dir $(OBJ)
	@echo -n ' <q.p> | $(NPWD): '
	@$(CC) $(OBJ) -o $(NAME)
	@echo "$(SUCCESS2)"

del:
	@$(DEL) $(OBJ)
	@$(DEL) $(NAME)

pre: del all
	@echo "$(INVERT)$(GREEN)Successed re-build.$(WHITE)"

set_cc_debug:
	@$(eval CC=$(CC_DEBUG))
debug_all: set_cc_debug pre
	@echo "$(INVERT)$(NAME) $(GREEN)ready for debug.$(WHITE)"
debug: set_cc_debug all
	@echo "$(INVERT)$(NAME) $(GREEN)ready for debug.$(WHITE)"

clean:
	@$(DEL) $(OBJ)

fclean: clean
	@$(DEL) $(NAME)
	@echo "$(INVERT)$(RED)deleted$(WHITE)$(INVERT): $(NPWD)$(WHITE)"

re: fclean all

.PHONY: re fclean clean all del pre debug debug_all
