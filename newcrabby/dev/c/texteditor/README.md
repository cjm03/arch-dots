# ECRAB: primitive text editor
Simple program for editing text files. Similarly to vim, there are NORMAL and INSERT modes. In normal mode, navigation with the 
arrow keys and/or HJKL is supported. In insert mode, navigation is only possible via the arrow keys. You start in normal mode, 
and must press 'i' to enter insert mode. ESC moves you back to normal mode from insert mode. Ctrl-Q to quit and Ctrl-S to save.
## Usage
Clone the repo, navigate into it, and run `make`. Default output will be a binary called 'ec', so modify the Makefile as desired.
Run using `./test <path/to/file>`.
