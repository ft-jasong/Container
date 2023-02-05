RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
PURPLE = \033[0;35m
CYAN = \033[0;36m
WHITE = \033[0;37m
NC = \033[0m

CXX = c++
CXXFLAG = -Wall -Wextra -Werror -std=c++98
SANFLAG = # -g3 -fsanitize=address

NAME = containers
TESTER = benchmark

INCDIR = ./incs/

SRC = srcs/main.cpp
TEST_SRC = srcs/ft_stl.cpp
OBJ = $(SRC:.cpp=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	@$(CXX) $(CXXFLAG) $(SANFLAG) $^ -o $@ -O3 -I$(INCDIR)
	@echo "$(GREEN)$(NAME) compiled$(NC)"

%.o : %.cpp
	@echo "$(CYAN)Compiling $<$(NC)"
	@$(CXX) $(CXXFLAG) -c $< -o $@ -O3 -I$(INCDIR)

clean : 
	@rm -f $(OBJ)
	@echo "$(RED)$(NAME) objects removed$(NC)"


fclean : clean
	@rm -f $(NAME) $(TESTER)
	@echo "$(RED)$(NAME) removed$(NC)"

re : fclean all

benchmark:
	@echo "$(GREEN)$(TESTER) compiling$(NC)"
	@$(CXX) $(CXXFLAG) $(SANFLAG) $(TEST_SRC) -o $(TESTER) -O3 -I$(INCDIR)
	@./$(TESTER)

.PHONY: all clean fclean re benchmark