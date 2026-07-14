_This project has been created as part of the 42 curriculum by ldubau, ejones_
# Minishell

This project is about creating a simple shell.
Yes, your very own little Bash.<br>
You will gain extensive knowledge about processes and file descriptors.

# Description

The project goal is to create a program that reproduce the bash terminal in C.<br>
The terminal Bash is an interactive command interpreter and<br>
command language developed for Unix-like operating systems,<br>
we can use it to "speak" to our computer. We have to implement bash original commands<br>
and some builtin function like below :<br>
- echo with option -n
- cd with only a relative or absolute path
- pwd with no options
- export with no options
- unset with no options
- env with no options or arguments
- exit with no option

The program also have to handle these keyboard control like the real bash terminal :
- ctrl-C displays a new prompt on a new line.
- ctrl-D exits the shell.
- ctrl-\ does nothing
<br><br>
# Instructions

Clone the repository with the ```git clone``` command:

To compile:<br>
```cd minishell && make```

To run the program:<br>
```./minishell```

A prompt will appear. You may enter your commands to be executed.<br>
```minishell>[here]```
# Resources

