# Section 1
**Question:** Describe what happens when the terminal is opened.  
**Answer:** When the new terminal is opened it initializes with customized environment variables (HELLO set to HOSTNAME and LOCAL set to the current user's name from whoami), making them available globally and locally within the shell session, respectively.

# Section 2
**Question1:** List the user commands and redirect the output to /tmp/commands.list.  
**Answer:**`$ compgen -c > /tmp/commands.list`

**Question2:** Edit in your profile to display date at login and change your prompt permanently.  
**Answer:** First, edit your `.profile` file using `$ vim ~/.profile` and add `echo "Welcome! Today's date is $(date)"` to display the date at login. Then, open your `.bashrc` file with `$ vim ~/.bashrc` and set `export PS1="\u@\h:\w $ "` to permanently change your shell prompt format.

**Question3:** What is the command to count the word in a file or number of file in directory.  
a. Count the number of user commands.  
**Answer:**  
**Count Words in a File:**`wc -w filename`  
**Count number of file in directory:**`find directory_path -type f | wc -l`  
**Count the number of user commands:**`compgen -c | wc -l` **Output:**`4410`

**Question4:** What happens if you execute:  
**a.** cat filename1 | cat filename2  
**b.** ls | rm  
**c.** ls /etc/passwd | wc –l  
**Answer:**  
**a.** Executing `cat filename1 | cat filename2` will only output the content of filename2 because the `cat` command, when given a filename as an argument `cat filename2`, reads directly from that file instead of from the standard input provided by the pipe `|`. Therefore, the second `cat` command `cat filename2` ignores the piped input from `cat filename1` and simply outputs the contents of `filename2`.  
**b.** Executing `ls | rm` will not delete anything and will print `rm: missing operand` because **rm** expects filenames as arguments directly on the command line. When you pipe the output of **ls** to **rm**, **rm** doesn't understand that it should read from the pipe. **rm** does not read from standard input in this context, so it receives no filenames and consequently produces the error message.  
**c.** Executing `ls /etc/passwd | wc –l` will output `1` because the `ls /etc/passwd` command lists the file **/etc/passwd**, and the output of `ls` is just the single line containing `/etc/passwd`. This single line is then counted by `wc -l`, resulting in the output `1`, indicating there is one line of output from `ls`.

**Question5:** Write a command to search for all files on the system that, its name is “.profile”.  
**Answer:**`$ sudo find / -name .profile`  
**Output:**`find: ‘/run/user/1000/doc’: Permission denied find: ‘/run/user/1000/gvfs’: Permission denied /home/doaa/.profile /etc/skel/.profile /root/.profile /snap/core20/2318/etc/skel/.profile /snap/core20/2318/root/.profile /snap/core20/1828/etc/skel/.profile /snap/core20/1828/root/.profile`

**Question6:** List the inode numbers of /, /etc, /etc/hosts.  
**Answer:** `$ ls -id / /etc /etc/hosts`  
**Output:**`2 /  13893633 /etc  13893798 /etc/hosts`

**Question7:** Create a symbolic link of /etc/passwd in /boot.  
**Answer:** `$ sudo ln -s /etc/passwd /boot`

**Question8:** Create a hard link of /etc/passwd in /boot. Could you? Why?  
**Answer:** `$ sudo ln /etc/passwd /boot`   
Yes, I could create a hard link between `/etc/passwd` and `/boot` because they are on the same filesystem. This is possible when there is no separate partition for `/boot`, which means both directories are part of the root filesystem (`/).

**Question9:** Echo \ it will jump to the next line, and will print >  
Notice the prompt ”>” what is that? and how can you change it from “>” to “:”.  
**Answer:** The prompt `>` indicating that it expects additional input to complete the command. This is because the backslash `\` tells the shell that the command is not yet finished. Once you provide additional input, the shell will then execute the complete command and print the final result.
To change it from `>` to `:`, you should add the following line to your **.bashrc** file:`export PS2=":"`.


