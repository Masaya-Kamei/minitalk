S_SRCSNAME	:= server.c receive_msg.c
S_SRCSDIR	:= ./srcs/server
S_SRCS		:= $(addprefix $(S_SRCSDIR)/, $(S_SRCSNAME))
S_NAME		:= server

C_SRCSNAME	:= client.c send_msg.c
C_SRCSDIR	:= ./srcs/client
C_SRCS		:= $(addprefix $(C_SRCSDIR)/, $(C_SRCSNAME))
C_NAME		:= client

S_OBJSDIR	:= ./objs/server
S_OBJSNAME	:= $(S_SRCSNAME:.c=.o)
S_OBJS		:= $(addprefix $(S_OBJSDIR)/, $(S_OBJSNAME))

C_OBJSDIR	:= ./objs/client
C_OBJSNAME	:= $(C_SRCSNAME:.c=.o)
C_OBJS		:= $(addprefix $(C_OBJSDIR)/, $(C_OBJSNAME))

CC			:= gcc
CFLAGS		:= -Wall -Wextra -Werror
RM			:= rm -rf
INCLUDE		:= -I./include
NAME		:= minitalk

LIBFTDIR	:= ./libft
LIBFT		:= $(LIBFTDIR)/libft.a
LIBFTTARGET	:= all

LIBINCLUDE  := -I${LIBFTDIR}
LIBDIR      := -L${LIBFTDIR}
LIBLINK     := -lft
LIB			:= $(LIBINCLUDE) $(LIBDIR) $(LIBLINK)

all		:	$(NAME)

$(LIBFT):
			make $(LIBFTTARGET) -C $(LIBFTDIR)

$(NAME)	:	$(S_NAME) $(C_NAME)

$(S_NAME):	$(S_OBJS) $(LIBFT)
			$(CC) $(CFLAGS) $(INCLUDE) $(S_OBJS) $(LIB) -o $(S_NAME)

$(C_NAME):	$(C_OBJS) $(LIBFT)
			$(CC) $(CFLAGS) $(INCLUDE) $(C_OBJS) $(LIB) -o $(C_NAME)

$(S_OBJSDIR)/%.o  :   $(S_SRCSDIR)/%.c
			@mkdir -p $(dir $@)
			$(CC) $(CFLAGS) $(INCLUDE) $(LIBINCLUDE) -o $@ -c $<

$(C_OBJSDIR)/%.o  :   $(C_SRCSDIR)/%.c
			@mkdir -p $(dir $@)
			$(CC) $(CFLAGS) $(INCLUDE) $(LIBINCLUDE) -o $@ -c $<

clean	:
			$(RM) $(S_OBJS) $(C_OBJS)
			make clean -C $(LIBFTDIR)

fclean	: 	clean
			$(RM) $(S_NAME) $(C_NAME)
			make fclean -C $(LIBFTDIR)

re		:	fclean all

address	:	CFLAGS		+= -g -fsanitize=address
address	:	LIBFTTARGET	:= address
address	:	re

leak	:	CC			:= /usr/local/opt/llvm/bin/clang
leak	:	CFLAGS		+= -g -fsanitize=leak
leak	:	LIBFTTARGET	:= leak
leak	:	re

.PHONY: all clean fclean re address leak
