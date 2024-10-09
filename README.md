# CLI GAME ENGINE

> **_NOTE:_** Project for personal educational purposes.

- CLI application 
- Ncurses library
- ECS: Entity, Component, Systems
- Makefile [^1]
- Game engine is not separate from the core application's function [^2]

[^1]: In future CMake.
[^2]: A scopo didattico.

## Requirements
- Linux

In most distro `Ncurses` is installed by default, otherwise you need to install the library.

> **_NOTE:_** Note on log file:
> - it is raccomanded to open the log file with therminal program like `less`, `cat`, etc...
> - in `.bashrc`, or `.zshrc`, or whatever you have, add `export CLICOLOR=TRUE` if colors are not displayed.

## Compiling

### Flags 
The main flags are:
- Ncurses: `-lncurses`
- In some cases the ncurses library is split in this other library: `-ltinfo` (use this flag if the compiler give an error on undefined reference to `stdscr`)
- form?
- Debugging: `-g`, `-Wall`


## ECS

### Conventions:
- before component class name `C..`, es: `CSprite`, `CBox`, ...
- before component instatiation of class `c...`, es: `cSprite`, ...
- this two roule are the same with systems with `s`
- private member variable have `m_...`, es: `m_cSprite`, ...
- variable and function name use maiusc character as delimiter: es: `gameEngine`, `modGravityExp`, `veryLongVariable` ...

### General:
- Components: store only pure data, no logic
- Systems are function or classes
- Systems operate on entities that have some precise component


### Systems order in game loop:
1. Input
2. Movement
3. Physics
4. AI
5. Renderer

## Future optimization
1. ~~Multi scene managment~~
2. ~~Action managment~~
3. ~~Game loop~~
4. Add assertion
5. Add custom memory allocator
6. Assets managment
7. Riorganizzare l'ordine nelle cartelle del progetto
8. Ricontrollare le incluzioni negli header file
9. Cambiare il vettore di shared pointer di entity in altro (vettore di puntatori normali?)
10. Implementare la rimozione delle entità nell'entity manager

# TO ADD
- a way to verify that for each constructor called is being also called the destructor, usefull??
