
# La commande doit être interprétée, essaye de faire un exec sur les exports
```
minishell> echo          HEllo
minishell> export TEST="ho       Hello      "
cmd : export
args : export, TEST=, ho       Hello      , 

minishell> ec$TEST
cmd : echo       Hello      
args : echo       Hello      , 
```

# Essaye ces flags la, histoire d'etre sur
```
valgrind --show-leak-kinds=all --leak-check=full --num-callers=200 --track-origins=yes --track-fds=yes --trace-children=yes --suppressions=readline.supp ./minishell
```



----------------------------------------------------------


minishell: cd: Makefile: No such file or directory
bash: cd: Makefile: Not a directory

