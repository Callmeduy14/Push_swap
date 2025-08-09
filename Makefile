NAME		:= push_swap
CC			:= cc
CFLAGS		:= -Wall -Wextra -Werror
AR			:= ar rcs
RM			:= rm -f

SRC_DIR		:= src
INC_DIR		:= include
OBJ_DIR		:= obj

SRCS := \
	$(SRC_DIR)/main.c \
	$(SRC_DIR)/parse.c \
	$(SRC_DIR)/errors.c \
	$(SRC_DIR)/stack.c \
	$(SRC_DIR)/ops_swap.c \
	$(SRC_DIR)/ops_push.c \
	$(SRC_DIR)/ops_rotate.c \
	$(SRC_DIR)/ops_revrotate.c \
	$(SRC_DIR)/lis.c \
	$(SRC_DIR)/solver.c \
	$(SRC_DIR)/cost.c \
	$(SRC_DIR)/utils.c \
	$(SRC_DIR)/tiny.c
	
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC_DIR)/push_swap.h
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

all: $(NAME)

clean:
	$(RM) -r $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re