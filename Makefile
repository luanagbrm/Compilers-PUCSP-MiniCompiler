# Makefile for Mini-Pascal Compiler
# Builds: minipc (the compiler executable)
# Dependencies: flex, bison (3.x), llvm, clang

# ===== Tool Paths =====
# Adjust these if your system has different paths
LLVM_CONFIG ?= $(shell which llvm-config 2>/dev/null || echo /opt/homebrew/opt/llvm/bin/llvm-config)
BISON       ?= $(shell which bison 2>/dev/null | grep -v /usr/bin || echo /opt/homebrew/opt/bison/bin/bison)
FLEX        ?= flex
CXX         ?= clang++

# ===== Flags =====
LLVM_CXXFLAGS := $(shell $(LLVM_CONFIG) --cxxflags)
LLVM_LDFLAGS  := $(shell $(LLVM_CONFIG) --ldflags --libs core)
LLVM_SYSLIBS  := $(shell $(LLVM_CONFIG) --system-libs 2>/dev/null)

CXXFLAGS := -std=c++17 -Wall -g $(LLVM_CXXFLAGS) -Wno-unused-function -Wno-deprecated-register
LDFLAGS  := $(LLVM_LDFLAGS) $(LLVM_SYSLIBS)

# ===== Files =====
SRCDIR   := src
BUILDDIR := build
TARGET   := minipc

PARSER_Y   := $(SRCDIR)/parser.y
LEXER_L    := $(SRCDIR)/lexer.l
CODEGEN    := $(SRCDIR)/codegen.cpp
SEMA       := $(SRCDIR)/sema.cpp
MAIN       := $(SRCDIR)/main.cpp

# Generated files
PARSER_C   := $(BUILDDIR)/parser.tab.cpp
PARSER_H   := $(BUILDDIR)/parser.tab.h
LEXER_C    := $(BUILDDIR)/lex.yy.cpp

OBJS := $(BUILDDIR)/parser.tab.o $(BUILDDIR)/lex.yy.o $(BUILDDIR)/codegen.o $(BUILDDIR)/sema.o $(BUILDDIR)/main.o

# ===== Rules =====

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS)
	@echo "✅ Build successful: ./$(TARGET)"

$(BUILDDIR)/parser.tab.o: $(PARSER_C)
	$(CXX) $(CXXFLAGS) -I$(SRCDIR) -I$(BUILDDIR) -c $< -o $@

$(BUILDDIR)/lex.yy.o: $(LEXER_C) $(PARSER_H)
	$(CXX) $(CXXFLAGS) -I$(SRCDIR) -I$(BUILDDIR) -c $< -o $@

$(BUILDDIR)/codegen.o: $(CODEGEN) $(SRCDIR)/codegen.h $(SRCDIR)/ast.h
	$(CXX) $(CXXFLAGS) -I$(SRCDIR) -I$(BUILDDIR) -c $< -o $@

$(BUILDDIR)/sema.o: $(SEMA) $(SRCDIR)/sema.h $(SRCDIR)/ast.h
	$(CXX) $(CXXFLAGS) -I$(SRCDIR) -I$(BUILDDIR) -c $< -o $@

$(BUILDDIR)/main.o: $(MAIN) $(SRCDIR)/ast.h $(SRCDIR)/codegen.h $(SRCDIR)/sema.h $(PARSER_H)
	$(CXX) $(CXXFLAGS) -I$(SRCDIR) -I$(BUILDDIR) -c $< -o $@

# Bison: parser.y → parser.tab.cpp + parser.tab.h
$(PARSER_C) $(PARSER_H): $(PARSER_Y) | $(BUILDDIR)
	$(BISON) -d -o $(PARSER_C) --defines=$(PARSER_H) $<

# Flex: lexer.l → lex.yy.cpp
$(LEXER_C): $(LEXER_L) $(PARSER_H) | $(BUILDDIR)
	$(FLEX) -o $@ $<

$(BUILDDIR):
	mkdir -p $(BUILDDIR)

clean:
	rm -rf $(BUILDDIR) $(TARGET)
	rm -f tests/*.ll tests/factor tests/isprime tests/pidigits tests/fibonacci

.PHONY: all clean
