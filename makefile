CC := g++
CFLAGS := -Wall -g

# $(wildcard *.cpp /xxx/xxx/*.cpp): get all .cpp files from the current directory and dir "/xxx/xxx/"
SRCS := $(wildcard *.cpp)
# $(patsubst %.cpp,%.o,$(SRCS)): substitute all ".cpp" file name strings to ".o" file name strings
OBJS := $(patsubst %.cpp, out/%.out, $(SRCS))

all: $(OBJS)
out/%.out: %.cpp
	$(CC) $< $(CFLAGS) -o $@
clean:
	rm -rf out/*.out

.PHONY: all clean
