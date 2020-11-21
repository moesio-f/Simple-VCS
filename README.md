# Simple-VCS, A simple Version Control System.
This program is a simple Version Control System (VCS) made as a case study of file access and an introduction to searching/sorting algorithms. It currently works for a single text file, providing options to commit, checkout, log, search and sort. At the moment, It doesn't have an error handling code since I assumed that every input is going to be correct and valid. I intend to update this project as I learn more about algorithms and data structures. For now, I'll keep the source available and add a few of my insights :smile:.

## :grey_question: How does it work?
Simple-VCS works using command-line arguments. You can open the command prompt and set the directory where the executable is. Then you can type _"Simple-VCS help"_ to list all commands available.
```C
printf("dir [newDir]: if newDir is empty, show current directory. Otherwise, updates directory to newDir.\n");
printf("user [newUser]: if newUser is empty, show user. Otherwise, set user to newUser\n");
printf("init [fileName]: Initialize a new repository for the given file. (File must be on the current directory)\n");
printf("commit [fileName] [message]: Commit the current version of the file. (message can contain blanks and multiple words)\n");
printf("checkout [fileName] [identifier]: Go to another version of the file.\n");
printf("log [fileName]: List all (committed) versions of the file.\n");
printf("list [dir]: List all repositories on the given dir (if none, use the current dir).\n");
printf("find [fileName] [word]: Find the first occurrence of the given word on file.\n");
printf("sort [fileName] [mode] [listNumber]: Sort the n-th list with respect to the mode (increasing or decreasing, returns the sorted list).\n");
printf("General usage: \'Simple-VCS command arguments\'\n");
```
The _Simple-VCS_ creates a config file that holds the current directory (The directory that will be your file to be version controlled) and the current username. Before you can commit a change of a given file, you first have to init a repository for this file. Once you "init" a repository, a hidden folder will be created. This folder contains a _main.vcs_ file that holds all information about the repository (i. e., all commit the information and the user who created the repository). When you "commit" a change on a file, this file will be copied to this hidden folder, so it'll be available in the future.
