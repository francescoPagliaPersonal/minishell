# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fpaglia <fpaglia@student.42vienna.com      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/16 14:48:27 by fpaglia           #+#    #+#              #
#    Updated: 2025/09/16 14:53:47 by fpaglia          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
FLAGS = -g3
INCLUDES = -I../libs/libft 

LIB_DIR := ../libs
INC_DIR := ../include

LIBFT := $(LIB_DIR)/libft/libft.a

$(LIBFT) :
	make -C $(LIB_DIR)/libft libft.a

.PHONY: libs
libs: $(LIBFT)
