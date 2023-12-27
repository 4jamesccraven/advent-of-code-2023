exe = partsManual.exe 

###---Environment---###
CXX = g++
CXXFlags = -std=c++17 -I$(INCDIR) -Wall -pedantic

BINDIR = ./bin
INCDIR = ./inc
SRCDIR = ./src
OBJDIR = ./obj

SRC = $(wildcard $(SRCDIR)/*.cpp)
INC = $(wildcard $(INCDIR)/*.h)
OBJ = $(SRC:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

###---Build---###
.PHONY: all
all: $(BINDIR)/$(exe)

$(BINDIR)/$(exe): $(OBJ)
	$(CXX) $(CXXFlags) -o $@ $(OBJ)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFlags) -o $@ -c $<

###---Utilities---###
.PHONY: clean, cleanwin, novim, novimwin, init, initwin
clean:
	rm -f $(BINDIR)/*.exe $(OBJDIR)/*.o

cleanwin:
	powershell -command "Remove-Item $(BINDIR)/*.exe; Remove-Item $(OBJDIR)/*.o"

novim:
	rm -f *~

novimwin:
	del *~

init:
	echo "Making directories..."
	mkdir src
	mkdir inc
	mkdir obj
	mkdir bin
	mkdir input
	echo "Keeping empty directories..."
	touch ./bin/.gitkeep
	touch ./src/.gitkeep
	echo "Making main..."
	touch ./src/$(exe:%.exe=%.cpp)
	echo "init complete."

initwin:
	echo "Making directories..."
	mkdir src
	mkdir inc
	mkdir obj
	mkdir bin
	mkdir input
	echo "Keeping empty directories..."
	powershell -command "New-Item -Path .\obj\.gitkeep; New-Item -Path .\bin\.gitkeep"
	echo "Making main..."
	powershell -command "New-Item -Path .\src\$(exe:%.exe=%.cpp)"
	echo "init complete."
