NAME        = push_swap
BONUS       = checker
CC          = cc
CFLAGS      = -Wall -Wextra -Werror
RM          = rm -f

SRC_DIR     = src
BONUS_DIR   = src/bonus
INC_DIR     = include
OBJ_DIR     = obj

LIBFT_DIR   = include/libft
LIBFT_A     = $(LIBFT_DIR)/libft.a


SRCS = \
    $(SRC_DIR)/main.c \
    $(SRC_DIR)/parse.c \
    $(SRC_DIR)/stack.c \
    $(SRC_DIR)/ops_swap.c \
    $(SRC_DIR)/ops_push.c \
    $(SRC_DIR)/ops_rotate.c \
    $(SRC_DIR)/ops_revrotate.c \
	$(SRC_DIR)/lis_index.c \
    $(SRC_DIR)/lis_mark.c \
	$(SRC_DIR)/lis_mark_utils.c \
    $(SRC_DIR)/solver.c \
    $(SRC_DIR)/cost_target.c \
	$(SRC_DIR)/cost_exec.c\
	$(SRC_DIR)/cost_calc.c\
    $(SRC_DIR)/utils.c \
    $(SRC_DIR)/tiny.c\
	$(SRC_DIR)/errors.c

BONUS_SRCS = \
    $(BONUS_DIR)/checker_main.c \
    $(BONUS_DIR)/checker_ops.c \
    $(BONUS_DIR)/checker_rotate.c \
	$(BONUS_DIR)/checker_swap.c

OBJS       = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
BONUS_OBJS = $(BONUS_SRCS:$(BONUS_DIR)/%.c=$(OBJ_DIR)/bonus_%.o)

OBJS_NO_MAIN := $(filter-out $(OBJ_DIR)/main.o, $(OBJS))

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC_DIR)/push_swap.h
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

$(OBJ_DIR)/bonus_%.o: $(BONUS_DIR)/%.c $(INC_DIR)/push_swap.h
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT_A)
	$(CC) $(CFLAGS) $(OBJS) -I$(INC_DIR) $(LIBFT_A) -o $(NAME)

$(BONUS): $(BONUS_OBJS) $(OBJS_NO_MAIN) $(LIBFT_A)
	$(CC) $(CFLAGS) $(BONUS_OBJS) $(OBJS_NO_MAIN) -I$(INC_DIR) $(LIBFT_A) -o $(BONUS)

$(LIBFT_A):
	$(MAKE) -C $(LIBFT_DIR)

bonus: $(BONUS)

clean:
	$(RM) -r $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME) $(BONUS) $(LIBFT_A)

re:
	$(MAKE) fclean
	$(MAKE) all

.PHONY: all clean fclean re bonus
