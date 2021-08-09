# What is Distract ?

## Introduction
Distract is an `ECS Game Engine` written in `C`.

It also uses the CSFML library for windowing and input handling.

It was orignally was created for a `RPG` game called [ThatDayITriedToBecomeTheDemonKing](https://github.com/Heliferepo/ThatDayITriedToBecomeTheDemonKing-myrpg)

So the engine might be well suited for types of games such as Point and click and RPG Style such as Final Fantasy ...

But as it is an `ECS Game Engine` it can be used for any type of game.

Warning:
It is made in accordingly in `C99` and uses some `GCC` extensions nottably for `va_args` arguments in macros
So clang might complain about some things.
If you get any warnings or errors please report them and I will try to fix them.

## Coding Style
The engine is following a certain coding style taken from the Epitech C Coding Style Guide.
The only rule that has been changed is the number of function per file.

We use the following rules:

    No more than 5 functions in a *.c file. -> Deprecated
    No more than 3 levels of branching.
    No more than 1 else if in a branching chain.
    No typedefs in *.c files.
    No structure arguments passed by value (always use a pointer).
    Functions must not exceed 20 lines.
    Variable declarations must always be done at the top of the function scope.
    The only empty line in functions is the one separating variable declarations with the rest of the function's body.
    Source files must start with some header containing the project name and file description.

We encourage you to follow the coding style to produce quick and readable code.

## Memory Management
The engine uses a memory management system based on the `C++ memory management` system.

And the leaks are comfirmed to be 0.

If you find any please really make sure to inform us.

## Build the project

### Prerequisites

- CMake
- GCC
- g++
- [SFML](http://www.sfml-dev.org/)
- [CSFML](https://github.com/CSFML/CSFML)
- [Doxygen](http://www.stack.nl/~dimitri/doxygen/) -> Optional but recomended for the documentation

### Build

```
git clone git@github.com:Heliferepo/Distract.git
cd Distract
make
```

### Documentation

You will need to install doxygen to generate the documentation.

A Doxygen configuration file is included in the root directory.
Just run `doxygen Doxyfile` and a html documentation will be generated in the `hmtl` directory.
Open it with a browser to see the documentation the file will be located in `html/index.html`.