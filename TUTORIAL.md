# Mini-Pascal Compiler — Tutorial 📖

A complete step-by-step guide to building a toy compiler for Mini-Pascal using Flex, Bison, and LLVM.

## Table of Contents

1. [Project Overview](#1-project-overview)
2. [Environment Setup](#2-environment-setup)
3. [Project Structure](#3-project-structure)
4. [Lexical Analysis (Flex)](#4-lexical-analysis-flex)
5. [Grammar & Parsing (Bison)](#5-grammar--parsing-bison)
6. [AST Design](#6-ast-design)
7. [LLVM IR Code Generation](#7-llvm-ir-code-generation)
   - [7b. Semantic Analysis (Sema)](#7b-semantic-analysis-sema)
8. [Main Driver](#8-main-driver)
9. [Build System (Makefile)](#9-build-system-makefile)
10. [Compiling and Running Test Programs](#10-compiling-and-running-test-programs)
11. [Mini-Pascal Language Reference](#11-mini-pascal-language-reference)
12. [Common Issues & Debugging](#12-common-issues--debugging)
13. [Generated Artifacts](#13-generated-artifacts)
- [Appendix A — Formal Grammar (BNF)](#appendix-a--formal-grammar-bnf)

---

## 1. Project Overview

### Compilation Pipeline

```
source.pas → [Flex] → tokens → [Bison] → AST → [Sema] → AST → [LLVM CodeGen] → IR → [Clang] → executable
```

Each stage transforms the program from one representation to the next:

| Stage | Tool | Input | Output |
|-------|------|-------|--------|
| Lexing | Flex | Source text | Token stream |
| Parsing | Bison | Tokens | Abstract Syntax Tree |
| Semantic analysis | `sema.cpp` | AST | Validated AST (or errors) |
| Code Generation | LLVM C++ API | AST | LLVM IR (.ll file) |
| Linking | Clang | LLVM IR | Native executable |

### What This Compiler Supports

- Integer and boolean types
- Variables with `var` blocks
- Functions and procedures with parameters and local variables
- Control flow: `if-then-else`, `while-do`, `for-to/downto-do`
- I/O: `write`, `writeln` (integers and string literals)
- Command-line argument access via `paramstr(n)`
- Arithmetic: `+`, `-`, `*`, `div`, `mod`
- Comparison: `=`, `<>`, `<`, `>`, `<=`, `>=`
- Boolean: `and`, `or`, `not`
- Comments: `{ }`, `(* *)`, `//`

---

## 2. Environment Setup

### macOS (Homebrew)

```bash
# Install all required tools
brew install flex bison llvm

# Bison 3.x is required (macOS ships with 2.3 which is too old)
# LLVM from brew is not in PATH by default on Apple Silicon

# Verify installation
flex --version          # Should show 2.6+
/opt/homebrew/opt/bison/bin/bison --version  # Should show 3.x
/opt/homebrew/opt/llvm/bin/llvm-config --version  # Should show 14+
clang --version
```

### Ubuntu/Debian Linux

```bash
sudo apt update
sudo apt install flex bison llvm-dev libllvm-dev clang build-essential

# Verify
flex --version
bison --version
llvm-config --version
clang --version
```

### Key version requirements

| Tool | Minimum Version | Purpose |
|------|----------------|---------|
| Flex | 2.6+ | Lexer generation |
| Bison | 3.0+ | Parser generation (C++ union support) |
| LLVM | 14+ | IR generation and optimization |
| Clang | Any recent | Linking LLVM IR to native code |

---

## 3. Project Structure

```
mini-pascal-compiler/
├── README.md              # Project overview and team info
├── TUTORIAL.md            # This file
├── Makefile               # Build system
├── build_and_test.sh      # Automated test runner
├── src/
│   ├── lexer.l            # Flex lexical analyzer
│   ├── parser.y           # Bison grammar with semantic actions
│   ├── ast.h              # AST node type definitions
│   ├── sema.h             # Semantic analyzer header
│   ├── sema.cpp           # Type checking + symbol table
│   ├── codegen.h          # LLVM code generation header
│   ├── codegen.cpp        # LLVM code generation implementation
│   └── main.cpp           # Driver program
├── tests/
│   ├── factor.pas         # Prime factorization
│   ├── isprime.pas        # Primality check
│   ├── pidigits.pas       # Digits of π
│   └── fibonacci.pas      # Fibonacci numbers
└── build/                 # Generated during build (gitignored)
    ├── parser.tab.cpp     # Bison output
    ├── parser.tab.h       # Token definitions
    └── lex.yy.cpp         # Flex output
```

---

## 4. Lexical Analysis (Flex)

### Overview

The lexer (`src/lexer.l`) transforms source text into a stream of tokens. Each token has a type (e.g., `TOK_IF`, `TOK_INT_LIT`) and optionally a value.

### Key Design Decisions

1. **Case-insensitive keywords** — Pascal is case-insensitive, so we use `(?i:keyword)` patterns
2. **String literals** — Handle escaped quotes (`''` → `'`)
3. **Comments** — Support `{ }`, `(* *)`, and `//`
4. **Line tracking** — `%option yylineno` for error reporting

### Token Categories

```
Keywords:    program, var, begin, end, if, then, else, while, do, for,
             to, downto, function, procedure, write, writeln, exit,
             integer, boolean, true, false, and, or, not, div, mod

Literals:    123 (integer), 'hello' (string), true/false (boolean)
Identifiers: [a-zA-Z_][a-zA-Z0-9_]*
Operators:   :=  + - * = <> < > <= >=
Punctuation: ; : , . ( )
```

### Lexer Rules (excerpt)

```lex
(?i:program)    { return TOK_PROGRAM; }
(?i:if)         { return TOK_IF; }
[0-9]+          { yylval.intVal = atoi(yytext); return TOK_INT_LIT; }
[a-zA-Z_][a-zA-Z0-9_]* { yylval.strVal = strdup(yytext); return TOK_IDENT; }
":="            { return TOK_ASSIGN; }
\{[^}]*\}      { /* block comment */ }
```

### How it works

Flex generates a DFA (Deterministic Finite Automaton) from the regular expressions. At runtime, `yylex()` reads characters and returns the matching token. The longest match wins, with earlier rules breaking ties.

---

## 5. Grammar & Parsing (Bison)

### Overview

The parser (`src/parser.y`) defines the Context-Free Grammar (CFG) for Mini-Pascal. Bison generates an LALR(1) parser that calls `yylex()` for tokens and builds an AST via semantic actions.

### Grammar Rules (simplified)

```
program      → PROGRAM IDENT ';' decl_section compound_stmt '.'
decl_section → var_decl_block subprog_decls
var_decl     → VAR (ident_list ':' type ';')+
subprog      → FUNCTION IDENT '(' params ')' ':' type ';' local_vars compound_stmt ';'
             | PROCEDURE IDENT '(' params ')' ';' local_vars compound_stmt ';'
compound_stmt→ BEGIN stmt_list END
stmt         → IDENT ':=' expr
             | IF expr THEN stmt [ELSE stmt]
             | WHILE expr DO stmt
             | FOR IDENT ':=' expr TO|DOWNTO expr DO stmt
             | WRITE[LN] '(' expr_list ')'
             | compound_stmt
expr         → simple_expr (rel_op simple_expr)?
simple_expr  → term (('+' | '-' | 'or') term)*
term         → factor (('*' | 'div' | 'mod' | 'and') factor)*
factor       → INT_LIT | BOOL_LIT | STRING_LIT | IDENT | IDENT '(' args ')' | '(' expr ')'
             | NOT factor | '-' factor
```

### Operator Precedence (low to high)

1. `=`, `<>`, `<`, `>`, `<=`, `>=` (comparison)
2. `+`, `-`, `or` (additive)
3. `*`, `div`, `mod`, `and` (multiplicative)
4. `not`, unary `-` (unary)

### Dangling Else Resolution

```yacc
%nonassoc TOK_THEN
%nonassoc TOK_ELSE
```

This tells Bison to prefer shift (associate `else` with nearest `if`).

### Semantic Actions (example)

```yacc
stmt:
    TOK_IF expr TOK_THEN stmt TOK_ELSE stmt {
        $$ = mkIf($2, $4, $6, yylineno);  // Build AST node
    }
```

---

## 6. AST Design

### Node Hierarchy

The AST (`src/ast.h`) uses tagged unions with factory functions:

```cpp
struct Expr { ExprKind kind; /* fields per kind */ };
struct Stmt { StmtKind kind; /* fields per kind */ };
struct Decl { DeclKind kind; /* fields per kind */ };
struct Program { string name; vector<Decl*> decls; Stmt* body; };
```

### Expression Kinds

| Kind | Fields | Example |
|------|--------|---------|
| IntLit | intVal | `42` |
| BoolLit | boolVal | `true` |
| StringLit | strVal | `'hello'` |
| Ident | name | `x` |
| BinOp | binOp, left, right | `x + 1` |
| UnaryOp | unaryOp, left | `-x`, `not b` |
| FuncCall | name, args | `arccot(5, s)` |

### Statement Kinds

| Kind | Fields | Example |
|------|--------|---------|
| Assign | name, expr | `x := 42` |
| If | cond, thenStmt, elseStmt | `if x > 0 then ...` |
| While | cond, body | `while x > 0 do ...` |
| For | name, expr, endExpr, forDir, body | `for i := 1 to n do ...` |
| Write | args, writeLn | `writeln(x)` |
| Block | stmts | `begin ... end` |
| ProcCall | name, args | `doSomething(x)` |
| Exit | expr | `exit(result)` |

---

## 7. LLVM IR Code Generation

### Overview

The code generator (`src/codegen.cpp`) walks the AST and emits LLVM IR using the IRBuilder API. Key concepts:

- **Module**: Top-level container for all functions and globals
- **Function**: Named block of code with parameters and return type
- **BasicBlock**: Sequence of instructions with one terminator (br, ret)
- **IRBuilder**: Helper that tracks insertion point and creates instructions

### Key Implementation Details

#### Function Compilation

Pascal functions assign their return value by assigning to the function name:
```pascal
function add(a, b: integer): integer;
begin
  add := a + b
end;
```

We implement this by allocating a return-value variable (`funcname.retval`) and creating an exit block:

```cpp
funcRetVal = createAlloca(func, fname + ".retval", retType);
namedValues[fname] = funcRetVal;  // Assign to func name = set return
// ... generate body ...
// Exit block: load retval and return
builder.CreateRet(builder.CreateLoad(retType, funcRetVal));
```

#### Command-Line Arguments

`paramstr(n)` accesses `argv[n]` and converts to integer:
```cpp
// Built into codegen: argv GEP + atoi call
auto* elemPtr = builder.CreateGEP(charPtrTy, argvPtr, idx);
auto* strPtr = builder.CreateLoad(charPtrTy, elemPtr);
return builder.CreateCall(atoi, {strPtr});
```

#### Write/WriteLn

Maps to `printf` calls:
- String literals → `printf("%s", str)` (directly via global string pointer)
- Integer expressions → `printf("%d", val)`
- `writeln` adds `printf("\n")`

#### Control Flow (example: while)

```cpp
void CodeGen::genWhile(Stmt* s) {
    auto* condBB = BasicBlock::Create(context, "while.cond", currentFunc);
    auto* bodyBB = BasicBlock::Create(context, "while.body", currentFunc);
    auto* endBB  = BasicBlock::Create(context, "while.end", currentFunc);

    builder.CreateBr(condBB);           // jump to condition
    builder.SetInsertPoint(condBB);
    auto* cond = genExpr(s->cond);      // evaluate condition
    builder.CreateCondBr(cond, bodyBB, endBB);  // branch

    builder.SetInsertPoint(bodyBB);
    genStmt(s->body);                   // generate body
    builder.CreateBr(condBB);           // loop back

    builder.SetInsertPoint(endBB);      // continue here after loop
}
```

### Generated IR Example

For `fibonacci.pas`, the generated IR includes:
```llvm
define i32 @main(i32 %argc, ptr %argv) {
entry:
  %n = alloca i32
  ; ... load paramstr(1) into n ...
  br label %for.cond

for.cond:
  %cur = load i32, ptr %i
  %cmp = icmp sle i32 %cur, %n.val
  br i1 %cmp, label %for.body, label %for.end

for.body:
  ; temp := a + b; a := b; b := temp
  br label %for.cond

for.end:
  ; printf("%d\n", b)
  ret i32 0
}
```

---

## 7b. Semantic Analysis (Sema)

Before any IR is generated, `src/sema.cpp` walks the AST to validate the
program. The pass is the practical implementation of the *"proper semantic
analysis (type checking, symbol table)"* requirement and produces meaningful
errors with line numbers.

### What Sema validates

| Category | Examples |
|----------|----------|
| Identifier resolution | undeclared variables, redeclarations in the same scope |
| Type compatibility | `n := true` (bool → int), `flag := 1 + 2` (int → bool) |
| Operator/operand types | `not 5`, `bool + int`, comparing int with bool |
| Control-flow conditions | `if n then ...` when `n` is `integer` |
| For-loop variable | must be `integer`, must be declared |
| Function/procedure calls | arity mismatch, wrong argument types, calling a procedure as an expression |
| Function return path | `exit(value)` value type matches function's declared return type |

### How it is structured

- A **scoped symbol table** implemented as a `std::vector<std::map<...>>`,
  pushed on entry to a function/procedure and popped on exit.
- Two passes over the top-level declarations:
  1. Register all globals (variables and subprogram signatures) so subprograms
     can reference each other regardless of declaration order.
  2. Type-check each subprogram body, then the main body.
- A small `Ty` enum (`Integer`, `Boolean`, `String`, `Error`) is used during
  expression checking. `Error` propagates without raising secondary errors,
  so a single mistake produces one diagnostic, not a cascade.

### Example output

```bash
$ ./minipc tests/_bad.pas
[minipc] Parsing tests/_bad.pas...
[minipc] Parsed program 'Bad' successfully.
[minipc] Running semantic analysis...
[sema] line 14: cannot assign boolean to 'n' of type integer
[sema] line 15: cannot assign integer to 'flag' of type boolean
[sema] line 17: if-condition must be boolean, got integer
[sema] line 18: function 'add' expects 2 argument(s), got 1
[sema] line 19: undeclared identifier 'undefined'
[sema] line 20: and requires boolean operands, got boolean and integer
[minipc] Semantic analysis failed: 6 error(s).
```

If Sema reports any errors, the driver returns non-zero and **codegen never
runs**, so the LLVM IR file and the executable are not produced.

---

## 8. Main Driver

The driver (`src/main.cpp`) orchestrates the pipeline:

```
1. Parse command-line args (input file, -o output, --emit-ir, -h/--help)
2. Open source file and set yyin
3. Call yyparse() → builds programAST
4. Run Sema::analyze(programAST) → fails fast on type errors
5. Create CodeGen, call generate(programAST) → produces LLVM IR
6. Write IR to .ll file
7. Shell out to clang to compile IR → native executable
```

---

## 9. Build System (Makefile)

### Key targets

```bash
make            # Build the compiler (./minipc)
make clean      # Remove all generated files
```

### Build flow

```
src/parser.y → [bison] → build/parser.tab.cpp + build/parser.tab.h
src/lexer.l  → [flex]  → build/lex.yy.cpp
build/*.cpp + src/codegen.cpp + src/main.cpp → [c++] → minipc
```

### Handling LLVM paths

The Makefile uses `llvm-config` to get compiler and linker flags:
```makefile
LLVM_CXXFLAGS := $(shell $(LLVM_CONFIG) --cxxflags)
LLVM_LDFLAGS  := $(shell $(LLVM_CONFIG) --ldflags --libs core)
```

---

## 10. Compiling and Running Test Programs

### Build the compiler first

```bash
make
```

### Compile and run each test program

```bash
# Factor: prime factorization
./minipc tests/factor.pas -o factor
./factor 84         # Output: 2 2 3 7
./factor 100        # Output: 2 2 5 5

# IsPrime: primality check
./minipc tests/isprime.pas -o isprime
./isprime 17        # Output: true
./isprime 4         # Output: false

# PiDigits: first n digits of π
./minipc tests/pidigits.pas -o pidigits
./pidigits 5        # Output: 31415
./pidigits 6        # Output: 314159

# Fibonacci: nth Fibonacci number
./minipc tests/fibonacci.pas -o fibonacci
./fibonacci 10      # Output: 55
./fibonacci 20      # Output: 6765
```

### Automated testing

```bash
./build_and_test.sh
```

This script builds the compiler, compiles all test programs, and validates outputs.

### Inspecting intermediate output

```bash
# View generated LLVM IR
./minipc tests/fibonacci.pas --emit-ir

# The .ll file is also written to disk
cat fibonacci.ll
```

---

## 11. Mini-Pascal Language Reference

### Program Structure

```pascal
program ProgramName;

var
  x, y: integer;
  flag: boolean;

function myFunc(a: integer; b: integer): integer;
var
  local: integer;
begin
  myFunc := a + b
end;

begin
  { main body }
  x := paramstr(1);
  writeln(myFunc(x, 10))
end.
```

### Types

| Type | Description | Values |
|------|-------------|--------|
| `integer` | 32-bit signed | -2^31 to 2^31-1 |
| `boolean` | 1-bit | `true`, `false` |

### Statements

```pascal
x := expr;                           { assignment }
if cond then stmt                    { conditional }
if cond then stmt else stmt          { conditional with else }
while cond do stmt                   { while loop }
for i := start to end do stmt        { ascending for }
for i := start downto end do stmt    { descending for }
begin stmt; stmt; ... end            { compound statement }
write(expr, expr, ...)               { print without newline }
writeln(expr, expr, ...)             { print with newline }
exit(expr)                           { early return from function }
procname(args)                       { procedure call }
```

### Built-in Functions

| Function | Description |
|----------|-------------|
| `paramstr(n)` | Returns command-line argument n as integer (via atoi) |
| `write(...)` | Print values (integers and string literals) |
| `writeln(...)` | Print values followed by newline |

### Comments

```pascal
{ This is a block comment }
(* This is also a block comment *)
// This is a line comment
```

---

## 12. Common Issues & Debugging

### Build Problems

| Problem | Solution |
|---------|----------|
| `bison: command not found` | Install bison 3.x. On macOS: `brew install bison` and use `/opt/homebrew/opt/bison/bin/bison` |
| `llvm-config not found` | Install LLVM. On macOS: `brew install llvm`. Set `LLVM_CONFIG` in Makefile |
| Linker errors about LLVM symbols | Ensure `llvm-config --libs core` returns correct library flags |
| `error: use of undeclared identifier 'yylineno'` | Add `%option yylineno` to lexer.l |

### Runtime Problems

| Problem | Solution |
|---------|----------|
| `Segmentation fault` | Check that command-line arg is provided (e.g., `./factor 84` not `./factor`) |
| Wrong output | Use `--emit-ir` flag and inspect the `.ll` file |
| `Parse error at line N` | Check syntax — likely missing semicolons or mismatched `begin`/`end` |
| `undefined variable` | Ensure variable is declared in a `var` block |
| Integer overflow in pidigits | 32-bit integers limit precision to ~7 digits of π |

### Debugging Tips

1. **Inspect generated IR**: `./minipc test.pas --emit-ir` shows LLVM IR on stdout
2. **Run LLVM verifier**: The compiler runs `verifyModule()` automatically and prints errors
3. **Check Bison conflicts**: Run `bison -v parser.y` to generate `parser.output` with state details
4. **Test incrementally**: Start with simple programs before complex ones

### Parser Conflicts

The dangling-else ambiguity is resolved with:
```yacc
%nonassoc TOK_THEN
%nonassoc TOK_ELSE
```

If you add new grammar rules and get shift/reduce conflicts, check `build/parser.output`.

---

## 13. Generated Artifacts

After compiling a program, these files are produced:

| File | Description |
|------|-------------|
| `program.ll` | LLVM IR (human-readable assembly-like text) |
| `program` | Native executable (ELF on Linux, Mach-O on macOS) |

### Example: Generated LLVM IR for a simple assignment

```pascal
program Simple;
var x: integer;
begin
  x := 42;
  writeln(x)
end.
```

Produces:
```llvm
@fmt = private unnamed_addr constant [3 x i8] c"%d\00"
@nl = private unnamed_addr constant [2 x i8] c"\0A\00"

define i32 @main(i32 %argc, ptr %argv) {
entry:
  %x = alloca i32
  store i32 42, ptr %x
  %x.val = load i32, ptr %x
  call i32 (ptr, ...) @printf(ptr @fmt, i32 %x.val)
  call i32 (ptr, ...) @printf(ptr @nl)
  ret i32 0
}

declare i32 @printf(ptr, ...)
```

---

## Appendix A — Formal Grammar (BNF)

The following BNF is the canonical reference for the Mini-Pascal language
accepted by `src/parser.y`. Non-terminals are lower-case; terminals are
upper-case (`TOK_*` in the Bison grammar) or quoted literals. `?` denotes an
optional element, `*` zero-or-more, and `+` one-or-more. Empty alternatives
are written as `ε`.

```ebnf
program          ::= "program" IDENT ";" decl-section compound-stmt "."

decl-section     ::= var-decl-block subprog-decl*

var-decl-block   ::= "var" var-decl-line+
                   | ε
var-decl-line    ::= ident-list ":" type ";"
ident-list       ::= IDENT ("," IDENT)*
type             ::= "integer" | "boolean"

subprog-decl     ::= "function"  IDENT param-section ":" type ";" local-vars compound-stmt ";"
                   | "procedure" IDENT param-section            ";" local-vars compound-stmt ";"
                   | "procedure" IDENT                          ";" local-vars compound-stmt ";"

param-section    ::= "(" param-list ")"
                   | "(" ")"
param-list       ::= param-group (";" param-group)*
param-group      ::= ident-list ":" type

local-vars       ::= "var" var-decl-line+
                   | ε

compound-stmt    ::= "begin" stmt-list "end"
stmt-list        ::= stmt (";" stmt)*

stmt             ::= ε
                   | IDENT ":=" expr
                   | IDENT "(" expr-list ")"
                   | IDENT
                   | compound-stmt
                   | "if" expr "then" stmt
                   | "if" expr "then" stmt "else" stmt
                   | "while" expr "do" stmt
                   | "for" IDENT ":=" expr ("to" | "downto") expr "do" stmt
                   | "write"   "(" expr-list ")"
                   | "writeln" "(" expr-list ")"
                   | "writeln"
                   | "exit" "(" expr ")"

expr             ::= simple-expr (rel-op simple-expr)?
simple-expr      ::= term (add-op term)*
term             ::= factor (mul-op factor)*
factor           ::= INT_LIT
                   | "true" | "false"
                   | STR_LIT
                   | IDENT
                   | IDENT "(" expr-list ")"
                   | "(" expr ")"
                   | "not" factor
                   | "-" factor

expr-list        ::= expr ("," expr)*

rel-op           ::= "=" | "<>" | "<" | ">" | "<=" | ">="
add-op           ::= "+" | "-" | "or"
mul-op           ::= "*" | "div" | "mod" | "and"
```

### Operator precedence (lowest to highest)

| Level | Operators                          | Associativity |
|-------|------------------------------------|---------------|
| 1     | `=` `<>` `<` `>` `<=` `>=`         | non-associative |
| 2     | `+` `-` `or`                       | left            |
| 3     | `*` `div` `mod` `and`              | left            |
| 4     | unary `not`, unary `-`             | right           |

### Dangling-else resolution

The grammar is ambiguous on `if a then if b then s1 else s2`. Bison resolves
this by giving `TOK_ELSE` a higher precedence than `TOK_THEN` via:

```yacc
%nonassoc TOK_THEN
%nonassoc TOK_ELSE
```

This binds `else` to the nearest unmatched `if`, matching standard Pascal
semantics.

### Lexical rules

```
IDENT    ::= [A-Za-z_][A-Za-z0-9_]*       (case-insensitive against keywords)
INT_LIT  ::= [0-9]+
STR_LIT  ::= "'" ( [^'] | "''" )* "'"     ('' is the escape for a single quote)
COMMENT  ::= "{" ... "}"                  (block)
           | "(*" ... "*)"                (block)
           | "//" ... <end-of-line>       (line)
WHITESPACE is skipped.
```

---

## Acknowledgments

- 🐉 Aho, Lam, Sethi, Ullman — *Compilers: Principles, Techniques, and Tools*
- LLVM Project — https://llvm.org/
- GNU Bison — https://www.gnu.org/software/bison/
- Flex — https://github.com/westes/flex

---
