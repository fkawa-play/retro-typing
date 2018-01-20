# retro-typing

Retro typing game written in C.

# Description

* You can play 5 stages for typing.  Let's play!
* While running this program, please DO NOT EXECUTE ``Ctrl-c``.
    * This program stops immediately.
* DO NOT remove any files in this repos except `ranking/`.

# Requirement

* **NOTE**: Only tested following environments:
    1. Ubuntu 16.04.3 LTS
    1. CentOS Linux release 7.4.1708 (Core)

## For Ubuntu

Please install following packages:

```
sudo apt install -y gcc make libncursesw5-dev ncurses-doc
```

## For CentOS

Please install following packages:

```
sudo yum install -y gcc make ncurses-devel
```

# How to Play

1. Open terminal app.
    * I strongly recommend to use following constraints. (Otherwise, the layout
      will be off)
        1. **xterm-256color** for termcap.
        1. Window size more than **200(Width) x 25(Height)**
1. Clone this repos:

   ```
   git clone https://github.com/fkawa-play/retro-typing.git
   ```
1. Compile and generate a binary:

   ```
   pushd retro-typing/
   make
   ```
1. Run the binary.  Let's play!!!:

   ```
   ./typing
   ```

# How to edit typing questions

You can configure typing questions as you like.
To configure typing questions, you should check following procedures:

**NOTE**: Please align with THE NUMBER OF QUESTIONS for all files.

1. Edit materials/sentence**num**.txt:
    * You can add/modify existing questions.
1. Edit materials/ruby**num**.txt:
    * You can add/modify existing questions.
    * Please align with the line number of questions.
1. Edit ``MAX_QUESTIONS`` in typing.h.
    * Please align with the line number of questions.
1. Re-build the program:

   ```
   make
   ```
1. Run the program:

   ```
   ./typist
   ```

# How to reset ranking

All of ranking data are initialized by '0.00'.

```
rm ranking/*.log
```

# How to Contribute/Debug

* Feel free to pick an issue and push a PR.
    * You can request your awesome branch into ``develop`` as PR.
* Logfile is at ``logs/typing.log``.  You can debug with this file like
  following command:

   ```
   tailf logs/typing.log
   ```

# Motivation

* When I was 18 years old, I wanted to create a typing game which is enable to
  edit questions easily.
    * How nostalgic!!!
* I made a first version at that time.  However, this program could work only
  MS-DOS on Windows.
* Therefore, I decided to refactor and change to play on Linux environment.

# MEMO

* These codes and English are very ugly.  I'll fix them step by step...
* I made a framework of typing game by using following knowledges.
  It's a simple!
    1. File input/output
    1. Structure(struct foo)
    1. Pointer, Pointer array
    1. ncurses
        * getch(), color, viewing
    1. Timer
    1. Logger
