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
   or
   make env=mac
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

# How to Debug

* Logfile is at ``logs/typing.log``.  You can debug with this file like
  following command:

   ```
   less -R logs/typing.log
   (Then, press `Shift + f`)
   ```

# How to test

This project has unit tests using googletest testing framework.
You can build and execute unit tests as follows. **Note that currently not to support MacOS**.

**Requirements**: cmake version 3.1 or later.

Install cmake before you build unit tests.

```
sudo apt install cmake
```

```
cd unittests
cmake .
make
./unittests
```

# Motivation/MEMO

* When I was 18 years old, I wanted to create a typing game which is enable to
  edit questions easily.
    * How nostalgic!!!
* I made a first version at that time.  However, this program could work only
  MS-DOS on Windows.
* Therefore, I decided to refactor and change to play on Linux environment.
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
