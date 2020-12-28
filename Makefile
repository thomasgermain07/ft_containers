NAME = a.out
SRCSDIR = srcs
OBJSDIR = .objs
SRCS = main.cpp\
		ListTest.cpp\
		VectorTest.cpp\
		QueueTest.cpp\
		StackTest.cpp\
		MapTest.cpp

OBJS = $(addprefix $(OBJSDIR)/, $(SRCS:.cpp=.o))
DPDCS = $(OBJS:.o=.d)
CXXFLAGS = -Wall -Wextra -Werror
CXX = clang++

opti :
	@(make -j all)

all : $(NAME)

-include $(DPDCS)

$(NAME) : $(OBJS)
	@($(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME))
	@(echo "$(NAME) created")

fg : $(OBJS)
	@($(CXX) $(CXXFLAGS) -g3 -fsanitize=address $(OBJS) -o $(NAME))
	@(echo "$(NAME) debug mode created")

$(OBJSDIR)/%.o : $(SRCSDIR)/%.cpp | $(OBJSDIR)
	@(echo "Compiling -> $^")
	@($(CXX) $(CXXFLAGS) -MMD -c $< -o $@)

$(OBJSDIR) :
	@(mkdir -p .objs)

clean :
	@(rm -f $(NAME))
	@(rm -rf $(NAME).dSYM)

fclean : clean
	@(rm -rf $(OBJSDIR))

re : fclean all

