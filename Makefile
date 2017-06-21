NAME = minishell

CC = gcc

CFLAGS = -Wall -Wextra -Werror

INCLUDES = includes/

SRCS = srcs/main.c\
	   srcs/read.c\
	   srcs/history_command.c\
	   srcs/move_cursor.c\
	   srcs/split_comand.c\
	   srcs/launch.c\
	   srcs/ft_echo.c\
	   srcs/ft_env.c\
	   srcs/ft_setenv.c\
	   srcs/ft_unsetenv.c\
	   srcs/ft_cd.c\
	   srcs/ft_exit.c\
	   srcs/util_error.c\
	   srcs/util_search_path.c\
	   srcs/util.c\
	   srcs/util_env.c\
	   srcs/util_make_str.c\
	   srcs/util_ft_strtok.c\
	   srcs/util_path.c\
	   srcs/util_read.c\
	   srcs/util_read_bufer.c\
	   srcs/util_mode_terminal.c

OBJ = $(SRCS:.c=.o)

LIBFTDIR = libft/

all: $(NAME)

$(NAME) : $(OBJ) $(LIBFTDIR)libft.a
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -L./$(LIBFTDIR) -lft

%.o: srcs/%.c $(INCLUDES)
	$(CC) $(CFLAGS) -c -o $@ $< -I $(INCLUDES) -I $(LIBFTDIR)

$(LIBFTDIR)libft.a: libft/Makefile
	make -C libft/

clean:
	rm -f $(OBJ)
	make clean -C $(LIBFTDIR)

fclean: clean
	rm -f $(NAME)

re: clean all

norm:
	norminette srcs/ includes/*.h
