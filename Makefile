SRCSDIR		:= ./srcs
OBJSDIR		:= ./objs

S_SRCSNAME	:= server.c
S_SRCS		:= $(addprefix $(SRCSDIR)/, $(S_SRCSNAME))
S_OBJS		:= $(addprefix $(OBJSDIR)/, $(S_SRCSNAME:.c=.o))
S_NAME		:= server

C_SRCSNAME	:= client.c
C_SRCS		:= $(addprefix $(SRCSDIR)/, $(C_SRCSNAME))
C_OBJS		:= $(addprefix $(OBJSDIR)/, $(C_SRCSNAME:.c=.o))
C_NAME		:= client

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

$(OBJSDIR)/%.o  :   $(SRCSDIR)/%.c
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
