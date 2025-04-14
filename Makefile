CXX = g++
CXXFLAGS = -std=c++2a -Wall -Wextra -Werror -g -MMD

SRCS =	src/Complex.cpp \
	src/DiffMatrix.cpp

OBJS_DIR = obj/
OBJS = $(SRCS:%.cpp=$(OBJS_DIR)%.o)

NAME = linearalgebra.a

DEPS = $(OBJS:.o=.d)

all: $(NAME)

$(NAME): $(OBJS)
	ar -rsc $(NAME) $(OBJS)

$(OBJS_DIR)%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@ -I./include

clean:
	rm -fr $(OBJS_DIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

-include $(DEPS)

.PHONY: all re clean fclean