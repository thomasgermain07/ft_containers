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
DEBUG = -g3 -fsanitize=address

opti :
	@(make -j all)

all : $(NAME)

-include $(DPDCS)

$(NAME) : $(OBJS)
	@($(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME))
	@(echo "$(NAME) created")

fg : $(OBJS)
	@($(CXX) $(CXXFLAGS) $(DEBUG) $(OBJS) -o $(NAME))
	@(echo "$(NAME) created")

$(OBJSDIR)/%.o : $(SRCSDIR)/%.cpp | $(OBJSDIR)
	@(echo "Compiling -> $^")
	@($(CXX) $(CXXFLAGS) -MMD -c $< -o $@)

$(OBJSDIR) :
	@(mkdir -p .objs)

clean :
	@(rm -f $(NAME))

fclean : clean
	@(rm -rf $(OBJSDIR))

re : fclean all

