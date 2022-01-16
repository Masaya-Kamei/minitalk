SRCSDIR		:= srcs
OBJSDIR		:= objs
INCLUDE		:= -I./includes

S_SRCSNAME	:= server.c
S_SRCS		:= $(addprefix $(SRCSDIR)/, $(S_SRCSNAME))
S_OBJS		:= $(addprefix $(OBJSDIR)/, $(S_SRCSNAME:.c=.o))
S_NAME		:= server

C_SRCSNAME	:= client.c
C_SRCS		:= $(addprefix $(SRCSDIR)/, $(C_SRCSNAME))
C_OBJS		:= $(addprefix $(OBJSDIR)/, $(C_SRCSNAME:.c=.o))
C_NAME		:= client

BONUS_SRCSDIR	:= $(addprefix ./bonus/, $(SRCSDIR))
BONUS_OBJSDIR	:= $(addprefix ./bonus/, $(OBJSDIR))
BONUS_INCLUDE	:= $(subst includes,bonus/includes,$(INCLUDE))

BONUS_S_SRCSNAME:= $(subst .c,_bonus.c,$(S_SRCSNAME))
BONUS_S_SRCS	:= $(addprefix $(BONUS_SRCSDIR)/, $(BONUS_S_SRCSNAME))
BONUS_S_OBJS	:= $(addprefix $(BONUS_OBJSDIR)/, $(BONUS_S_SRCSNAME:.c=.o))
BONUS_S_NAME	:= $(addsuffix _bonus, $(S_NAME))

BONUS_C_SRCSNAME:= $(subst .c,_bonus.c,$(C_SRCSNAME))
BONUS_C_SRCS	:= $(addprefix $(BONUS_SRCSDIR)/, $(BONUS_C_SRCSNAME))
BONUS_C_OBJS	:= $(addprefix $(BONUS_OBJSDIR)/, $(BONUS_C_SRCSNAME:.c=.o))
BONUS_C_NAME	:= $(addsuffix _bonus, $(C_NAME))

CC			:= gcc
CFLAGS		:= -Wall -Wextra -Werror
RM			:= rm -rf
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

bonus	:	$(BONUS_S_NAME) $(BONUS_C_NAME)

$(BONUS_S_NAME):	$(BONUS_S_OBJS) $(LIBFT)
			$(CC) $(CFLAGS) $(BONUS_INCLUDE) $(BONUS_S_OBJS) $(LIB) -o $(BONUS_S_NAME)

$(BONUS_C_NAME):	$(BONUS_C_OBJS) $(LIBFT)
			$(CC) $(CFLAGS) $(BONUS_INCLUDE) $(BONUS_C_OBJS) $(LIB) -o $(BONUS_C_NAME)

$(BONUS_OBJSDIR)/%.o  :   $(BONUS_SRCSDIR)/%.c
			@mkdir -p $(dir $@)
			$(CC) $(CFLAGS) $(BONUS_INCLUDE) $(LIBINCLUDE) -o $@ -c $<

clean	:
			$(RM) $(S_OBJS) $(C_OBJS) $(BONUS_S_OBJS) $(BONUS_C_OBJS)
			make clean -C $(LIBFTDIR)

fclean	: 	clean
			$(RM) $(S_NAME) $(C_NAME) $(BONUS_S_NAME) $(BONUS_C_NAME)
			make fclean -C $(LIBFTDIR)

re		:	fclean all

address	:	CFLAGS		+= -g -fsanitize=address
address	:	LIBFTTARGET	:= address
address	:	re

leak	:	CC			:= /usr/local/opt/llvm/bin/clang
leak	:	CFLAGS		+= -g -fsanitize=leak
leak	:	LIBFTTARGET	:= leak
leak	:	re

.PHONY: all clean fclean re bonus address leak
