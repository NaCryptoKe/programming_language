# MiniLang Roadmap

## Language
- [x] Define initial keywords: `set` and `print`
- [x] Write an example program in `example.mini`
- [ ] Decide rules for variables, numbers, and arithmetic

## Compiler
- [x] Read a source file
- [x] Store tokens in a queue
- [ ] Recognize identifiers, numbers, operators, and punctuation
- [ ] Parse `set` and `print` statements
- [ ] Build an abstract syntax tree (AST)
- [ ] Check that variables are declared before use
- [ ] Evaluate the AST and print results
- [ ] Report errors with line and column numbers

## Later
- [ ] Add parentheses and operator precedence
- [ ] Generate bytecode for a small virtual machine
- [ ] Add conditionals and loops
