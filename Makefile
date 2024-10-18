MY_SOURCES = pipex.c \
			error_handling.c \
			validation.c \
			helpers/helpers.c \
			bonus/pipex_bonus.c


MY_OBJECTS = $(MY_SOURCES:.c=.o)

NAME = pipex

CC = cc

#CFLAGS += -Wall -Werror -Wextra

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(MY_OBJECTS)
	make -C libftPrintfGnl
	$(CC) $(CFLAGS) $(MY_OBJECTS) libftPrintfGnl/libft.a -o $(NAME)

clean:
	make clean -C libftPrintfGnl
	rm -f $(MY_OBJECTS)

fclean: clean
	make fclean -C libftPrintfGnl
	rm -f $(NAME)

re: fclean all
