# retro-typing

Retro typing game written in C.

![sample](https://github.com/fkawa-play/retro-typing/blob/images/images/sample_typing.png)

# Description

* You can play 5 stages for typing.
* While running this program, please DO NOT EXECUTE ``Ctrl-c``.
    * This program stops immediately.
* PLEASE DO NOT remove any files in this repos except `ranking/`.

# Requirement

**NOTE**: Only tested following environments:

1. Ubuntu 16.04.3 LTS
1. CentOS Linux release 7.4.1708 (Core)
1. MaxOS X Yosemite 10.10.5 and macOS High Sierra 10.13.2

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
    * Ubuntu / CentOS

       ```
       pushd retro-typing/
       make
       ```
    * MacOS

       ```
       pushd retro-typing/
       make env=mac
       ```
1. Run the binary.  Let's play!!!:

   ```
   ./typing
   ```

For more detail, please refer [CUSTOMIZE.md](https://github.com/fkawa-play/retro-typing/blob/master/CUSTOMIZE.md)
