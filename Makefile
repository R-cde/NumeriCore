
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

.PHONY: debug
debug: CXXFLAGS += -g
debug: clean $(TARGET)

.PHONY: o2
o2: CXXFLAGS += -O2
o2: clean $(TARGET)

.PHONY: o3
o3: CXXFLAGS += -O3
o3: clean $(TARGET)

