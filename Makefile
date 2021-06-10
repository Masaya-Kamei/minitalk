S_SRCNAME	:= server.c receive_msg.c
S_SRCDIR	:= ./srcs/server/
S_SRCS		:= $(addprefix $(S_SRCDIR), $(S_SRCNAME))
S_OBJS		:= $(S_SRCS:.c=.o)
S_NAME		:= server

C_SRCNAME	:= client.c send_msg.c
C_SRCDIR	:= ./srcs/client/
C_SRCS		:= $(addprefix $(C_SRCDIR), $(C_SRCNAME))
C_OBJS		:= $(C_SRCS:.c=.o)
C_NAME		:= client

LIBFTDIR	:= ./libft
LIBFTNAME 	:= libft.a
LIBFT		:= $(LIBFTDIR)/$(LIBFTNAME)
LIBFTTARGET	:= all

CC			:= gcc
CFLAGS		:= -Wall -Wextra -Werror
RM			:= rm -rf
INCLUDE		:= -I./include
NAME		:= minitalk

all		:	$(NAME)

.c.o	:
			$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $(<:.c=.o)

$(LIBFT):
			make $(LIBFTTARGET) -C $(LIBFTDIR)

$(NAME)	:	$(S_NAME) $(C_NAME)

$(S_NAME):	$(S_OBJS) $(LIBFT)
			$(CC) $(CFLAGS) $(INCLUDE) $(S_OBJS) $(LIBFT) -o $(S_NAME)

$(C_NAME):	$(C_OBJS) $(LIBFT)
			$(CC) $(CFLAGS) $(INCLUDE) $(C_OBJS) $(LIBFT) -o $(C_NAME)

clean	:
			$(RM) $(S_OBJS) $(C_OBJS)
			make clean -C $(LIBFTDIR)

fclean	: 	clean
			$(RM) $(S_NAME) $(C_NAME)
			make fclean -C $(LIBFTDIR)

re		:	fclean all

debug	: CFLAGS += -g
debug	: LIBFTTARGET := debug
debug	: re

address	: CFLAGS += -g -fsanitize=address
address	: LIBFTTARGET := address
address	: re

.PHONY:	all clean fclean re debug address
