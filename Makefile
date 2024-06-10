# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lgosselk <lgosselk@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/10 16:12:42 by lgosselk          #+#    #+#              #
#    Updated: 2024/01/23 12:57:16 by lgosselk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

## SI no hay bonus eliminar get_next_line y ft_strdup

RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
DEFAULT = \033[0m

# Makefile #

NAME	=	pipex

NAME_B	=	pipex_bonus	

GCC		=	gcc

FLAGS	= 	-Wall -Wextra -Werror

RM		=	rm -rf

HEADER		=	./includes/pipex.h

SRCS		=	src/pipex.c src/childs.c src/error.c

FUNC_SRCS	=	functions/ft_split.c functions/ft_strdup.c functions/ft_strjoin.c \
				functions/ft_strncmp.c functions/ft_strlen.c functions/ft_strnstr.c

SRCS_BONUS	=	bonus/pipex_bonus.c src/childs.c \
				src/error.c

OBJS		=	$(SRCS:.c=.o)

OBJS_FUNC	=	$(FUNC_SRCS:.c=.o)

OBJS_BONUS	=	$(SRCS_BONUS:.c=.o)

%.o: %.c $(HEADER) Makefile
							@${GCC} ${FLAGS} -c $< -o $@

$(NAME):	$(OBJS) $(OBJS_FUNC)
				@$(GCC) $(OBJS) $(OBJS_FUNC) -o $(NAME)
				@echo "$(GREEN)$(NAME) created!$(DEFAULT)"

all:		$(NAME)

bonus:		$(NAME_B)

$(NAME_B):	$(OBJS_BONUS) $(OBJS_FUNC)
				@$(GCC) $(OBJS_BONUS) $(OBJS_FUNC) -o $(NAME)
				@echo "$(GREEN)$(NAME_B) created!$(DEFAULT)"

clean:
				@$(RM) $(OBJS)
				@$(RM) $(OBJS_FUNC)
				@$(RM) $(OBJS_BONUS)
				@echo "$(YELLOW)object files deleted!$(DEFAULT)"

fclean:			clean
				@$(RM) $(NAME)
				@$(RM) $(NAME_B)
				@echo "$(RED)all deleted!$(DEFAULT)"

re:			fclean all

re_bonus:	fclean bonus

.PHONY:		all clean fclean re