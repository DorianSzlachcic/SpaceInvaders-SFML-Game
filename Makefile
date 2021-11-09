OBJDIR = obj
SRCDIR = src
CXXFLAGS = -std=c++17 -g -I/home/dorian/SFML/include
LDFLAGS = -L/home/dorian/SFML/lib -lsfml-window -lsfml-graphics -lsfml-system -lsfml-audio

SRC = $(wildcard $(SRCDIR)/*.cpp)
OBJ = $(SRC:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

all: SpaceInvaders

SpaceInvaders: $(OBJ)
	g++ $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	g++ $(CXXFLAGS) -o $@ -c $^

run: SpaceInvaders
	./SpaceInvaders

clean:
	rm -f $(OBJDIR)/*.o SpaceInvaders