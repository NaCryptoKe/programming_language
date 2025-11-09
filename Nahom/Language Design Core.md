**1. Core Features**

- **Dynamically Typed:** Values can change type at runtime. Designed for readability and beginner-friendliness.
- **Basic Types:**
  - `int` – 64-bit integer
  - `float` – double precision
  - `bool` – boolean (true / false)
  - `string` – text sequence
  - `None` – null equivalent
- **Composite Types:**
  - `List`: Dynamic array; no manual memory management. Inspired by Python’s list but internally optimized for DSA operations.
  - `Dictionary`: Key-value storage, JSON-like, supports nested structures.
- **Variables:**
  - `Simple assignment`; no type declaration required.
  - ```text
        x = 5
      name = "Nahom"
      x = "A string" // Allowed: dynamic typing
    
      global y // Marks variable as global; accessible across functions
      ```
    - Variables can be reassigned freely. Global variables can be referenced before initialization.
- **Control Flow:**
  - Conditionals: `if`, `if-else`, `if-elif-else` 
  - Loops: `while`, `do-while`, `for`, `for-each`, `for-range`
- **Functions:**
  - Declared with `def`. Support `return`, `break`, and `continue`.
  - ```text
    def add(x, y) {
        global sum = x + y
    }
    print(sum)
    ```
  - ```text
    def foo() {}
    def foo()
    {}
    ```     
- **Built-ins:**
  - `print()` – outputs to console 
  - `length(x)` – returns size of list, dict, or string 
  - `input()` – reads user input
- **Error Policy:**
  - Auto-corrects trivial syntax mistakes (e.g., missing quotes, stray commas, semicolons). 
  - Displays clear “fixed for you” message showing original and corrected line.

---

**2. Syntax Style**

- Curly braces define scope. 
- Statements can end with a semicolon or a newline. 
- Strings support single `'`, double `"`, and backtick **`** quotes. 
- Whitespace-insensitive (except inside strings).

---

**3. Data Structures**

- **Lists:**
  - Dynamic arrays usable as stacks (push, pop) or queues (enqueue, dequeue). 
  - Support indexing, slicing, and iteration.
- **Strings:**
  - Interpolation: `Hello, ${name}`
  - Concatenation via `+` or `concat()`
  - Implicit string conversion when combining types:
  - ```text
    "Result: " + 5  // → "Result: 5"
    ```
- **Range:**
  - Implemented like Python’s `range(start, end, step)` for cleaner looping syntax.
- **Execution Model:**
  - Interpreted language for fast iteration and learning. Future support for `JIT` compilation.