# AI Tools — Usage Log

The lab brief asks teams to declare which AI assistants we used and to share
the prompts. This document keeps that record.

## Tools

| Tool | Vendor | What we used it for |
|------|--------|---------------------|
| Claude | Anthropic | Walking through the existing code, gap-analysing it against the lab brief, fixing bugs, adding the semantic analysis pass, writing/polishing docs |
| ChatGPT | OpenAI | Reviewing the markdown documentation and a second opinion on a few design choices |

We prompted both tools in English. The brief mentions English prompts give
better results, and we found that to be true.

## Prompts we used (Claude)

These are the actual prompts we used. They're lightly cleaned up for typos
and formatting, but the wording is ours.

### Setting up the project (initial session)

> "I need to build a toy compiler for a Mini-Pascal language as a college
> project. The compiler should use Flex for lexing, Bison for parsing, and
> the LLVM C++ API for code generation, targeting macOS (arm64).
>
> The compiler needs to take a `.pas` source file and produce a native
> executable. It must support: integer and boolean types, variables,
> if/while/for, functions with parameters and return values, write/writeln
> for output, and command-line argument access.
>
> I need 4 test programs that it can compile and run:
>
> - `factor.pas`: prime factorization of a CLI integer
> - `isprime.pas`: prints true/false if a number is prime
> - `pidigits.pas`: prints the first n digits of pi
> - `fibonacci.pas`: prints the nth Fibonacci number
>
> Start with the project structure, AST definition, and lexer. Then we'll
> iterate on the parser, codegen, and test programs. Use this as additional
> context: https://github.com/danielscarvalho/PUC-SP-Compilers/blob/main/Project-Create-Compiler.md"

### Walkthrough (different session)

We opened a fresh Claude session with no prior context as a smoke test on
our documentation: if a stranger (in this case, another AI) can read the repo and
correctly identify what it is, what it does, and what's missing, the docs
and code are doing their job.

> "Walk through the project and tell me what you understand by it. Do you see any problems, given what kind of project you think this is?"

Claude correctly identified the project as a teaching-grade Pascal
compiler, summarized the pipeline accurately from the source files, and
flagged real gaps against the lab brief (placeholder team names, missing
screenshot evidence, an example in the README that contradicted the
behavior of `pidigits.pas`). We treated the response as a checklist and
worked through the items in the rest of this session.

### Comparing against the lab brief

> "These are the requirements for the lab \[full brief pasted in\]. Compare
> what we have so far against them and tell us what's missing."

### Iteration on screenshots and the build output

> "I added two screenshots in the `docs/` folder."

> "The one ending in `10.01.35` is the environment check, the second is the
> test run. This is what the build output looks like \[pasted terminal
> output with the LLVM deprecation warnings\]. Is it better to structure it
> differently?"

> "The screenshot looks like this now \[pasted clean run\]. Is that all we
> need, or is something else missing?"

### Pushing for more improvements

> "Do you see any more points of improvement in this project?"

## Prompts we used (ChatGPT)

We used ChatGPT informally for a second pair of eyes on the documentation
and a few design questions. We did not keep formal transcripts of those
sessions.

## How we worked

1. We described what we wanted to Claude — usually starting from the lab
   brief or from an existing piece of code we wanted reviewed.
2. Claude proposed changes and made them directly in the workspace using
   its tools (file edits, build commands, tests).
3. After every meaningful change we ran `make && ./build_and_test.sh` and
   read the output before moving on.
4. When something looked off (tone in the docs, a misleading example, a
   leftover deprecated API), we pushed back and Claude iterated.
5. ChatGPT got a turn whenever we wanted a different perspective on the
   markdown files.

## What we did ourselves

- Choosing the language scope — which Pascal features to keep and which to drop.
- The expected outputs and assertions in `build_and_test.sh`.
- Capturing and curating the screenshots in `docs/`.
- Filling in this document.
