# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jasong <jasong@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/23 13:23:38 by jasong            #+#    #+#              #
#    Updated: 2022/12/23 13:42:48 by jasong           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CXX = c++
CXXFLAG = -Wall -Wextra -Werror -std=c++98

NAME = container

SRCDIR = ./srcs
INCDIR = ./incs

all : $(NAME)

SRCS : $(addprefix $(SRCDIR), main.cpp \
				)
OBJS : $(SRC:.cpp=.o)

%.o : %.cpp:
	$(CXX) $(CXXFLAG) -c $< -o $@ -I$(INCDIR)

clean:
	@rm -f $(OBJS)

fclean : clean
	@rm -f $(NAME)

re : fclean all