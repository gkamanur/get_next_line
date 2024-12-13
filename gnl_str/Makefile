# Name of the library
NAME = get_next_line.a

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
BUFFER_SIZE ?= 1

# Source files and corresponding object files
SRC = get_next_line.c get_next_line_utils.c
OBJ = $(SRC:.c=.o)

# Default rule to create the library
all: $(NAME)

# Rule to create the library from object files
$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)
	@echo "Library $(NAME) created."

# Rule to compile each .c file to .o file
%.o: %.c get_next_line.h
	$(CC) $(CFLAGS) -D BUFFER_SIZE=$(BUFFER_SIZE) -c $< -o $@

# Rule to clean object files
clean:
	rm -f $(OBJ)
	@echo "Object files removed."

# Rule to clean object files and the library
fclean: clean
	rm -f $(NAME)
	@echo "Library $(NAME) removed."

# Rule to recompile everything
re: fclean all

# Rule to run the code using the library
run: $(NAME)
	$(CC) $(CFLAGS) -D BUFFER_SIZE=$(BUFFER_SIZE) main.c $(NAME) -o a.out
	./a.out

# Declare phony targets
.PHONY: all clean fclean re run

