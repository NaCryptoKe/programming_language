# Unnamed Language — Design Document
*A programming language designed from desire, not obligation.*

---

## The Premise

Most languages are built around a machine model, a math model, or a compromise between them. This one is built around a different question: **what does it feel like to think through a problem?**

Not how a CPU executes it. Not how a type theorist proves it. How a *person* reasons about it — with uncertainty, context, intent, and change.

---

## Core Philosophy

**1. Intent over syntax**
The language should be writable the way you'd explain something to a sharp colleague. Terseness is fine. Verbosity is fine. Neither should be punished.

**2. Time is a first-class value**
Values change. State evolves. Most languages pretend this is an awkward edge case. Here, time is built into the data model from the start.

**3. Errors are information, not disasters**
Errors carry context, history, and recovery paths. They are values. They compose.

**4. The type system should help, not interrogate**
Types exist to catch real mistakes and enable tooling — not to satisfy a theorem prover. The compiler should *infer aggressively* and *ask rarely*.

**5. Composition over everything**
Functions, modules, data transformations — everything composes the same way. No special cases for async, effects, or collections.

---

## Data Model

### Values are versioned by default

```
let count = 0
count = count + 1
count = count + 1

count          -- 2
count.history  -- [0, 1, 2]
count.at(0)    -- 0
```

You can opt out of tracking if you want pure performance. But the *default* is that mutation is observable and reversible locally.

### Time-aware types

```
type Temperature = Float with unit: Celsius
type Reading = { value: Temperature, at: Moment }
```

`Moment` is a built-in — wall clock, logical clock, or sequence number depending on context. The type system knows the difference between "a temperature" and "a temperature at a point in time."

### Shapes, not classes

No inheritance. No constructors. No `this`.

```
shape Point = { x: Float, y: Float }

shape Circle = { center: Point, radius: Float }
  with area = π * radius²
  with perimeter = 2 * π * radius
```

A `shape` is just a named record with optional computed fields. No methods. No mutation. Behavior lives in functions, not objects.

---

## Functions

### Uniform call syntax

```
-- All of these are equivalent:
add(3, 4)
3.add(4)
3 |> add(4)
```

The pipeline operator `|>` threads the left value as the first argument. This makes data transformation chains read naturally without special method syntax.

### Named and optional arguments everywhere

```
fn greet(name: Text, greeting: Text = "Hello") -> Text
  "{greeting}, {name}."

greet("Amara")                    -- "Hello, Amara."
greet("Amara", greeting: "Ciao") -- "Ciao, Amara."
```

No positional-vs-keyword distinction. All arguments are nameable. Order only matters for positional calls.

### Functions are not special

A function is a value. It has a type. It composes. You don't need lambdas vs named functions vs methods — there's one thing.

```
let double = fn(x) -> x * 2
let numbers = [1, 2, 3, 4]
numbers.map(double)  -- [2, 4, 6, 8]
```

---

## The Type System

### Infer everything, annotate for communication

Types are inferred. Annotations are optional documentation, not required ceremony.

```
let ratio = 3 / 4         -- inferred as Float
let ratio: Float = 3 / 4  -- same, but explicit for readers
```

### Union types are structural

```
type Result(T, E) = Ok(T) | Err(E)
type Option(T) = Some(T) | None
```

These are built-in, but they're not special. You can define your own variants the same way.

### Pattern matching is exhaustive and expressive

```
match response
  | Ok(data)  -> render(data)
  | Err(e) if e.retryable -> retry(request)
  | Err(e)    -> log_and_fail(e)
```

Guards are inline. The compiler tells you if a case is unreachable, or if you've missed one.

### No null. Not even as a concept.

`None` exists (as part of `Option`). There is no implicit nothing. A value either exists or it is explicitly absent and you handle it.

---

## Effects

### Effects are declared, not magical

```
fn fetch_user(id: Id) -> User
  reads: [Database]
  may_fail: [NetworkError, NotFound]
```

This is not Haskell's IO monad. It's not a checked exception system. It's a *declaration* — readable by humans and tools, enforceable by the compiler if you want strictness, advisory if you don't.

### Async is just an effect

```
fn load_profile(id: Id) -> Profile
  async
  reads: [API]
```

`async` is a declared effect. There is no `async/await` syntax. There is no callback hell. The runtime handles scheduling. You write sequential code; the compiler knows it can be suspended.

---

## Error Handling

### Errors are shaped, not strung

```
shape NotFound = {
  resource: Text,
  id: Any,
  at: Moment,
  context: Map(Text, Any)
}
```

Errors have structure. You can pattern match on them. You can add context as they propagate.

### The `?` operator threads errors upward

```
fn get_username(id: Id) -> Text | Err
  let user = find_user(id)?     -- returns Err upward if absent
  let profile = user.profile?   -- same
  profile.display_name
```

The `?` operator is not just "return on error" — it also *annotates* the error with the callsite, so stack traces are automatic.

---

## Concurrency

### Processes, not threads

Inspired by Erlang's model but with less ceremony. Every async task is an isolated process with a mailbox.

```
let worker = spawn {
  loop {
    receive
    | Compute(data) -> reply(process(data))
    | Stop          -> break
  }
}

send(worker, Compute(my_data))
```

No shared mutable state between processes. Passing by value is the default. Sharing is explicit.

### Structured concurrency

```
parallel {
  let a = fetch(url_1)
  let b = fetch(url_2)
  let c = fetch(url_3)
}
-- a, b, c are all resolved here; any failure cancels the rest
```

Concurrent tasks live inside a scope. They start together, end together. No fire-and-forget leaks.

---

## Modules

### Modules are first-class values

```
let Http = import "http"
let json = Http.get(url) |> parse_as(Json)
```

You can pass modules as arguments. You can mock them in tests. There's no global module registry with magic side effects on import.

### Visibility is explicit and minimal

Everything is private by default. You expose what you mean to expose.

```
module Geometry
  expose [area, perimeter]

  fn area(shape) -> ...
  fn perimeter(shape) -> ...
  fn internal_helper(x) -> ...  -- not exposed
```

---

## Metaprogramming

### Macros over reflection

Runtime reflection is a trap. It's powerful and untraceable. Instead: compile-time macros that are readable, debuggable, and hygienic.

```
@derive(Serializable, Comparable)
shape Person = { name: Text, age: Int }
```

`@derive` is a macro. It generates code you can inspect. The generated code is not magic — it's just code.

### No monkey-patching

You cannot extend types you don't own. You can write *companion functions* that live in your module, not on the type.

---

## Tooling as Language Design

These aren't afterthoughts. They're part of the spec.

### The REPL is a first-class environment

The language is designed to be explored. Every expression shows its type. History is queryable. You can reach back and redefine earlier values.

### Inline tests

```
fn add(a: Int, b: Int) -> Int
  a + b
  test:
    add(2, 3) == 5
    add(-1, 1) == 0
```

Tests live next to functions. They run in CI. They serve as documentation.

### Deterministic formatting

One formatter. One style. No arguments, no config files. `fmt` is part of the language toolchain, not a third-party opinion.

### Time-travel debugging

Because values are versioned and processes are isolated, the runtime can replay execution. The debugger lets you step backward, not just forward.

---

## What This Language Is Not

- Not a Lisp. (Though it respects them deeply.)
- Not Rust. Memory safety matters, but you shouldn't fight the borrow checker to write a web server.
- Not Python. Clarity doesn't require giving up expressiveness.
- Not Haskell. Purity is a tool, not a religion.
- Not TypeScript. Types should reduce noise, not generate it.

---

## What Success Looks Like

A junior developer can write something that works.
A senior developer can write something that *scales*.
Neither has to compromise their approach to use the same language.

Code written in this language should be readable six months later without regret.
Errors should feel like feedback, not punishment.
The type system should feel like a collaborator.

That's the bar.

---

*Document version: 0.1 — first principles draft*
*Status: dreaming*
