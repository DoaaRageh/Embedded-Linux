# Question2
**Q:** Move the binary file output to the directory /usr/local/bin with sudo permissions. Afterward, attempt to execute the binary from any working directory and explain the outcome. Provide a detailed explanation supported by evidence as to why the binary can be executed from any location.
**Answer:**``~/Tasks/Linux-Administration$ sudo mv binarySearch.out /usr/local/bin`` ``~/Tasks/Linux-Administration$ cd ~`` ``~$ binarySearch.out`` The file binarySearch.out will be executed because it has been moved to /usr/local/bin, which is included in the system's PATH environment variable. The PATH variable is a list of directories that the shell searches for executable files, allowing you to run the file from any location.

# Na2na2a
**Question 1:** List the available shells in your system.
**Answer:**``~$ cat /etc/shells`` **Output:** ``# /etc/shells: valid login shells /bin/sh /bin/bash /usr/bin/bash /bin/rbash /usr/bin/rbash /bin/dash /usr/bin/dash``

**Question 2:** List the environment variables in your current shell.
**Answer:**``~$ env`` **Output:**``SHELL=/bin/bash SESSION_MANAGER=local/doaa-VirtualBox:@/tmp/.ICE-unix/1814,unix/doaa-VirtualBox:/tmp/.ICE-unix/1814 ...............``

**Question 3:** Display your current shell name.
**Answer:**``~$ basename $SHELL`` **Output:** ``bash``

**Question 4:** Execute the following command : echo \ then press enter What is the purpose of \ ?
**Answer:**``~$ echo \``When you press Enter after this line, the shell displays ``>``, indicating that it expects additional input to complete the command. This is because the backslash tells the shell that the command is not yet finished. Once you provide additional input, the shell will then execute the complete command and print the final result.
**Output:**``~$ echo \`` ``> doaa`` ``doaa`` 

**Question 5:** Create a Bash shell alias named PrintPath for the “echo $PATH” command.
**Answer:**``~$ alias PrintPath='echo $PATH'`` ``~$ PrintPath`` **Output:**``/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin``


