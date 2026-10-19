CC = cc
CFLAGS = -Wall -Wextra -Werror -g
NAME = Cube

OBJ_DIR = obj

MACROLIBXDIR:= MacroLibX/
MACROLIBX:=$(addprefix $(MACROLIBXDIR), libmlx.so)

INCLUDES=  -I$(MACROLIBX)

SOURCES = test.c

OBJECTS = $(addprefix $(OBJ_DIR)/, $(SOURCES:.c=.o))

all: $(MACROLIBX) $(NAME)

$(NAME): $(OBJECTS) $(MACROLIBX)
	$(CC) $(CFLAGS) $(OBJECTS) $(MACROLIBX)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ -lSDL2

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR)
	rm -f *.o
	@make -C $(MACROLIBXDIR) clean

fclean: clean
	rm -f $(NAME)
	@make -C $(MACROLIBXDIR) clean

re: fclean all

.PHONY: all clean fclean re
