# CLI GAME ENGINE
- cli 
- ncurses
- ECS: Entity, Component, Systems
- makefile

## Requirements
- Linux

In most distro `Ncurses` is installed by default, otherwise you need to install the library.

## Compiling flags

The main flags are:
- ncurses: `-lncurses`
- In some cases the ncurses library is split in this other library: `-ltinfo` (use this flag if the compiler give an error on undefined reference to `stdscr`)
- form?


## ECS

### Conventions:
- before component class name `C..`, es: `CSprite`, `CBox`, ...
- before component instatiation of class `c...`, es: `sSprite`, ...
- this two roule are the same with systems with `s`
- private member variable have `m_...`, es: `m_components`, ...

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
