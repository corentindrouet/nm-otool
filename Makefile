# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/04/14 13:10:40 by cdrouet           #+#    #+#              #
#    Updated: 2017/04/14 13:48:25 by cdrouet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OTOOL=ft_otool
NM=ft_nm

.PHONY:
all: $(NM) $(OTOOL)

.PHONY:
$(OTOOL):
	@make -C otool/

.PHONY:
$(NM):
	@make -C nm/

$(OTOOL).clean:
	@make -C otool/ clean

$(NM).clean:
	@make -C nm/ clean

clean: $(OTOOL).clean $(NM).clean

$(OTOOL).fclean:
	@make -C otool/ fclean

$(NM).fclean:
	@make -C nm/ fclean

fclean: $(OTOOL).fclean $(NM).fclean

$(OTOOL).re:
	@make -C otool/ re

$(NM).re:
	@make -C nm/ re

re: $(OTOOL).re $(NM).re
