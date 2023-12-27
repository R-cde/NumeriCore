CXX = g++
CXXFLAGS = -std=c++20 -fmodules-ts -I./include -w

SRCDIR = src
INCDIR = include
BUILDDIR = build
TARGET = main

SRCEXT = cpp
SOURCES = $(wildcard $(SRCDIR)/**/*.cpp) main.cpp
OBJECTS = $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -r $(BUILDDIR) $(TARGET)

.PHONY: run
run: $(TARGET)
	./$(TARGET)
