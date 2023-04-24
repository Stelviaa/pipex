SRCS = srcs/pipex.c srcs/parsing.c srcs/file_free.c srcs/error_managing.c
SRCS_BONUS	= srcs_bonus/pipex_bonus.c srcs_bonus/here_doc.c srcs_bonus/file_free_bonus.c srcs_bonus/error_managing_bonus.c srcs_bonus/parsing_bonus.c
CC = gcc
CFLAGS = -Wall -Wextra -Werror
CFLAGS += -Iincludes
NAME = pipex
NAME_BONUS = pipex_bonus
RM = rm -f
LIBS = -Llibft -lft

OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)

.c.o:
		$(CC) $(CFLAGS) -c $< -o $@

all:	$(NAME)

$(NAME):	$(OBJS)
			make -C libft
			$(CC) -o $(NAME) $(OBJS) $(LIBS)

bonus:	$(OBJS_BONUS)
		make -C libft
		$(CC) -o $(NAME_BONUS) $(OBJS_BONUS) $(LIBS)

debug: CFLAGS+=-g
debug: re

clean:
		$(RM) $(OBJS) $(OBJS_BONUS)
		make clean -C libft

fclean: clean
		$(RM) $(NAME) $(NAME_BONUS)
		make fclean -C libft

re: fclean all

.PHONY: all fclean clean re debug bonus