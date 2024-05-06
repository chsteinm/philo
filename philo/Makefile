NAME = philo_bonus
CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread #-g3 -fsanitize=thread
SRCS = main.c ft_strtol_utils.c ft_lst_funcs.c ft_strtol.c init.c print_and.c take_fork.c utils.c
OBJ = $(addprefix $(BUILD_DIR)/,$(SRCS:.c=.o))
BUILD_DIR = .build

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@
	@echo "\ncompile done!\n"

$(BUILD_DIR)/%.o: %.c Makefile
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

-include $(OBJ:.o=.d)

clean:
	rm -rf $(BUILD_DIR)

fclean: clean
	rm -rf $(NAME)

re: fclean
	@make --no-print-directory

.PHONY: all clean fclean re