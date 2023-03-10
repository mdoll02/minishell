NAME = minishell

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

LIBFT = dependencies/libft/libft.a
LIBFT_DIR = dependencies/libft

DEPENDENCIES = $(LIBFT) -lreadline
INCLUDES = -I dependencies/libft -I includes

SRC_DIR = src
OBJ_DIR = obj

SRC = main.c \
	  execution.c \
	  builtins/echo.c \
	  builtins/exit.c \
	  builtins/cd.c \
	  builtins/pwd.c \
	  builtins/env.c \
	  builtins/unset.c \
	  builtins/export.c \
	  parsing/parse_command.c \
	  parsing/parse_env_var.c \
	  parsing/parse_next_arg.c \
	  parsing/get_arg_end.c \
	  parsing/parse_arg_env.c \
	  parsing/get_exec_path.c \
	  env/load_env.c \
	  env/get_env.c \
	  env/set_env.c \
	  env/clear_env.c \
	  env/remove_env.c \
	  env/export_env.c \
	  utils/get_shell_dir.c \
	  #pipes/create_pipes.c

OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJ)
	@echo "OBJ: $(OBJ)"
	@make -C $(LIBFT_DIR) bonus
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(DEPENDENCIES)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)/builtins
	@mkdir -p $(OBJ_DIR)/parsing
	@mkdir -p $(OBJ_DIR)/env
	@mkdir -p $(OBJ_DIR)/utils
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)
	@echo "Compiling $<"

clean:
	@make -C $(LIBFT_DIR) clean
	@rm -f $(OBJ)

fclean: clean
	@make -C $(LIBFT_DIR) fclean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
.NOTPARALLEL: all clean fclean re