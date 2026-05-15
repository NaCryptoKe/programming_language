# Dynamic Typing

Nulo is dynamically typed. Variables can store values of any type, and a *single variable* can even store values of different types at different times.

Trying to perform an operation on values of the wrong type, say dividing a int by string, then error will be detected at runtime.

I picked dynamically typing because it's intuitive, and as the book implies easier to implement than statically typed.

# Automatic memory management

Because nulo is a high level language I'm avoiding memory acquisition and freeing to a more modest garbage collector.

# Data types

The following are the built-in data types. There are only few I think are necessary:

- **Numbers:** Nulo has two types of numbers, one is for *float* which is more precise and the other is *int*.

I'm avoiding octal, hexadecimal, and other types for simplicity stakes, and to make my life easier.

```Nulo
1234; // An int
12.34; // A float
```

- **Booleans:** basically it has logic values, *True* and *False*.

```Nulo
true;
false;
```

- **Strings:** I've taken a drastic or somewhat drastic change to how strings operate in this language.

It ranges from using single and double quotes as well backticks for strings; but also backticks also can do **string interpolation** the same as javascript.

The additional things I added are, tripple single and double quotes will give you a multiline input like *python* and preserve newlines.

But, if we use tripple backtick then newlines will be turned to spaces.

```Nulo
"Hello";
'Nulo';
`A string`;
$`String {interpolation}`;

"""
Preserves
Newlines
"; // This is the same as; Preserves \n Newlines. But if it was backticks it would have been Preserves Newlines

```
