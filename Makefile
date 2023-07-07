NAME = fractol

SRC_DIR = srcs
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)

CFLAGS = -Wall -Wextra -Werror
LIBS = -L. -lmlx42 -ldl -lglfw -pthread -lm
INCLUDES = -Iinclude

OBJ_DIR = obj
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))

.PHONY: all clean fclean re

all: $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	gcc $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJ_FILES)
	gcc $(CFLAGS) -o $(NAME) $(OBJ_FILES) $(LIBS)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all
