# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdugot <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/12/03 12:08:51 by mdugot            #+#    #+#              #
#    Updated: 2017/03/31 09:44:27 by cdrouet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=ft_nm
CC= clang
CFLAGS= -Wall -Werror -Wextra
SRC_NAME= ft_nm.c \
		  nm_file.c \
		  handle_64.c
SRC_PATH= ./sources/
INC_PATH= ./includes/
LIB_NAME= libftprintf.a
LIB_ID= ftprintf
LIB_PATH= ./libft/
LIB_INC= ./libft/
OBJ_NAME= $(SRC_NAME:.c=.o)
OBJ_PATH= ./obj/
SRC= $(addprefix $(SRC_PATH), $(SRC_NAME))
OBJ= $(addprefix $(OBJ_PATH), $(OBJ_NAME))
LIB= $(addprefix $(LIB_PATH), $(LIB_NAME))

$(NAME) : $(LIB) $(OBJ)
	$(info Compiling executable...)
	@$(CC) $(CFLAGS) -I$(INC_PATH) -o $(NAME) -L$(LIB_PATH) -l$(LIB_ID) $(OBJ)
	$(info Done !)

.PHONY: all
all: $(NAME)

$(LIB):
	$(info Compiling libft)
	@make -C $(LIB_PATH)
	@echo ""

.PHONY: libft
libft:
	@make re -C $(LIB_PATH)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir $(OBJ_PATH) 2> /dev/null || echo "" > /dev/null
	@/bin/echo -n "Compiling $<..."
	@$(CC) -I$(INC_PATH) -I$(LIB_INC) $(CFLAGS) -o $@ -c $<
	@echo "Done !"

.PHONY: clean
clean:
	$(info Delete binaries)
	@rm -f $(OBJ)
	@rm -rf $(OBJ_PATH)
	$(info Done !)
	@echo ""
	$(info Delete libft Binaries)
	@make $@ -C $(LIB_PATH)
	@echo ""

.PHONY: fclean
fclean: clean
	$(info Delete executable)
	@rm -f $(NAME)
	$(info done !)
	@echo ""
	$(info Delete libft executable)
	@make $@ -C $(LIB_PATH)

.PHONY: re
re: fclean all
