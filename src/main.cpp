/*
 * main.cpp - Driver for Mini-Pascal compiler
 * Integrates: Flex (lexer) → Bison (parser) → LLVM (codegen) → clang (linker)
 *
 * Usage: ./minipc source.pas [-o output] [--emit-ir]
 */
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <iostream>
#include "ast.h"
#include "codegen.h"
#include "sema.h"

// Bison/Flex interface
extern FILE* yyin;
extern int yyparse();
extern Program* programAST;

static void printUsage(const char* prog) {
    std::cout
        << "Usage: " << prog << " <source.pas> [options]\n"
        << "\n"
        << "Compiles a Mini-Pascal source file to a native executable using\n"
        << "Flex (lexer), Bison (parser) and LLVM (code generation).\n"
        << "\n"
        << "Options:\n"
        << "  -o <file>     Name of the output executable\n"
        << "                (default: source filename without extension)\n"
        << "  --emit-ir     Print the generated LLVM IR to stdout and skip linking\n"
        << "  -h, --help    Show this help message and exit\n"
        << "\n"
        << "Examples:\n"
        << "  " << prog << " tests/factor.pas -o factor\n"
        << "  " << prog << " tests/fibonacci.pas --emit-ir\n";
}

int main(int argc, char* argv[]) {
    // Help flag handled before any other validation so `minipc --help` works.
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            printUsage(argv[0]);
            return 0;
        }
    }

    if (argc < 2) {
        printUsage(argv[0]);
        return 1;
    }

    std::string inputFile = argv[1];
    std::string outputFile = "";
    bool emitIR = false;

    // Parse command-line options
    for (int i = 2; i < argc; i++) {
        if (strcmp(argv[i], "-o") == 0 && i + 1 < argc) {
            outputFile = argv[++i];
        } else if (strcmp(argv[i], "--emit-ir") == 0) {
            emitIR = true;
        } else {
            std::cerr << "Unknown option: " << argv[i] << "\n";
            printUsage(argv[0]);
            return 1;
        }
    }

    // Default output name: strip extension
    if (outputFile.empty()) {
        outputFile = inputFile;
        auto dot = outputFile.rfind('.');
        if (dot != std::string::npos) outputFile = outputFile.substr(0, dot);
        auto slash = outputFile.rfind('/');
        if (slash != std::string::npos) outputFile = outputFile.substr(slash + 1);
    }

    // === PHASE 1: Lexing + Parsing ===
    yyin = fopen(inputFile.c_str(), "r");
    if (!yyin) {
        std::cerr << "Error: cannot open '" << inputFile << "'\n";
        return 1;
    }

    std::cout << "[minipc] Parsing " << inputFile << "...\n";
    if (yyparse() != 0) {
        std::cerr << "[minipc] Parsing failed.\n";
        fclose(yyin);
        return 1;
    }
    fclose(yyin);

    if (!programAST) {
        std::cerr << "[minipc] No program AST produced.\n";
        return 1;
    }
    std::cout << "[minipc] Parsed program '" << programAST->name << "' successfully.\n";

    // === PHASE 2: Semantic Analysis ===
    std::cout << "[minipc] Running semantic analysis...\n";
    Sema sema;
    if (!sema.analyze(programAST)) {
        std::cerr << "[minipc] Semantic analysis failed: "
                  << sema.errorCount() << " error(s).\n";
        return 1;
    }

    // === PHASE 3: LLVM Code Generation ===
    std::cout << "[minipc] Generating LLVM IR...\n";
    CodeGen codegen;
    if (!codegen.generate(programAST)) {
        std::cerr << "[minipc] Code generation failed.\n";
        return 1;
    }

    std::string irFile = outputFile + ".ll";
    if (!codegen.writeToFile(irFile)) {
        std::cerr << "[minipc] Failed to write IR to " << irFile << "\n";
        return 1;
    }
    std::cout << "[minipc] Generated " << irFile << "\n";

    if (emitIR) {
        codegen.dump();
        return 0;
    }

    // === PHASE 4: Compile IR to executable using clang ===
    std::string cmd = "clang " + irFile + " -o " + outputFile + " -lm 2>&1";
    std::cout << "[minipc] Compiling: " << cmd << "\n";
    int ret = system(cmd.c_str());
    if (ret != 0) {
        std::cerr << "[minipc] Linking failed.\n";
        return 1;
    }

    std::cout << "[minipc] Compiled successfully: ./" << outputFile << "\n";
    return 0;
}
