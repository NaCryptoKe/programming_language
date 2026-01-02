# NULO

The language name for me is **NULO**, which means *null* or *void* in Spanish and Portuguese.  
It represents simplicity, emptiness, and a starting point for creation, fitting for a language meant to be clean, intuitive, and beginner-friendly.

---

## **1. Core Features**

- **Dynamically Typed:**  
  Values can change type at runtime. Designed for readability and beginner-friendliness.

- **Basic Types:**  
  - `int` – 64-bit integer  
  - `float` – double precision  
  - `bool` – boolean (`true` / `false`)  
  - `string` – text sequence  
  - `None` – null equivalent  

- **Composite Types:**  
  - **List:** Dynamic array with automatic memory management. Inspired by Python lists but internally optimized for common data structure operations.  
  - **Dictionary:** Key-value storage similar to JSON objects, supports nested structures.  

- **Variables:**  
  - Support simple assignment without type declarations.  
  - Variables can be reassigned freely.  
  - Supports `global` for cross-function accessibility and `immutable` for constants.  
  - Global variables can be referenced before initialization.  

- **Control Flow:**  
  - Supports `if`, `if-else`, `if-elif-else` conditionals.  
  - Loop structures include `while`, `do-while`, `for`, `for-each`, and `for-range`.  

- **Functions:**  
  - Declared using `def`.  
  - Support `return`, `break`, and `continue`.  
  - Function definitions can be written in single-line or multi-line form.  

- **Built-ins:**  
  - `print()` – outputs to console  
  - `length(x)` – returns size of list, dictionary, or string  
  - `input()` – reads user input  

- **Error Policy:**  
  - Automatically corrects trivial syntax mistakes (e.g., missing quotes, extra commas, semicolons).  
  - Displays a clear “fixed for you” message showing the original and corrected line.  

---

## **2. Syntax Style**

- Curly braces define scope.  
- Statements can end with either a semicolon or a newline.  
- Strings support single `'`, double `"`, and backtick `` ` `` quotes.  
- Whitespace is ignored except inside strings.  
- Triple quotes (`"""` or `'''`) preserve formatting for multiline strings.  
- Triple backticks (`` ``` ``) collapse multiline strings into a single line, treating newlines as spaces.  

---

## **3. Data Structures**

- **Lists:**  
  - Dynamic arrays that can function as stacks or queues.  
  - Support indexing, slicing, and iteration.  

- **Strings:**  
  - Support variable interpolation using `${}` syntax.  
  - Support concatenation via `+` or `concat()`.  
  - Automatically convert non-string types when concatenated with strings.  

- **Range:**  
  - Provides a sequence of numbers similar to Python’s `range(start, end, step)`.  
  - Commonly used for iteration in loops.  

- **Execution Model:**  
  - Interpreted language designed for fast iteration and learning.  
  - Planned support for optional JIT compilation in future versions.  

---

## **4. Features Wishlist**

| Must Haves | Nice To Haves |
|-------------|---------------|
| Variables, Declaration & Assignment | Triple Quotes |
| Dynamically Typed | Explicitly defining data types |
| Control Flows (if, elif, else, while, for, break, continue) | Auto-fix code |
| Functions (`def`) | Optional Semicolons |
| Built-ins (print, input, length, concat) | Hybrid Comments |
| Comment Syntax (`//`) | Global variable access across scopes |
| Error Handling | Inline Docs / Docstrings |
| Standard Execution Model (Tree-walk) | Built-in list/dict helpers (append, push, pop, etc.) |
| Lists, Dictionaries (Maps), Range (For-each), String Interpolation (`${var}`) | Jupyter-style notebook mode |
| Lexer → Parser → Tree-walk Interpreter | Pretty printed runtime errors |
| Basic REPL (Read-Eval-Print Loop) | Syntax highlighting in REPL or terminal |

---

## ✅ **Week 1–2: Language Foundations**

- [x] Decide core features: variables, types, control flow, functions.  
- [x] Decide syntax style: braces for scope, flexible line endings.  
- [x] Decide data structures to support initially: list, dict, string, int, float.  
- [x] Make a feature wishlist: must-have vs nice-to-have.  

---
