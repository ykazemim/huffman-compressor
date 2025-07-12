CXX = g++
CXXFLAGS := -std=c++17

SRCDIR = .
BUILDDIR = build
SRCS = Main.cpp FileProcessor.cpp HuffmanBinaryTree.cpp Huffman.cpp Config.cpp
OBJS = $(SRCS:%.cpp=$(BUILDDIR)/%.o)

TARGET = Compressor.exe

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	if not exist $(BUILDDIR) mkdir $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	del /Q $(BUILDDIR)\*.o $(TARGET) 2>nul || exit 0

.PHONY: all clean