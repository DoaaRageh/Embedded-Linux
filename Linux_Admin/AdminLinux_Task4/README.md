# Section 1
**Question:** What is a Bash script that creates a user named 'yourName' and adds them to the 'FamilyName' group, checking for existing user and group, and displaying relevant information for the user and group.

![Screenshot from 2024-07-18 03-38-33](https://github.com/user-attachments/assets/f5335f7b-53f8-4177-ad76-29e5a2285838)

The script adds a user to a group and checks whether the user and group already exist before making any changes.

## First Run with User "doaa"
![Screenshot from 2024-07-18 03-27-40](https://github.com/user-attachments/assets/d22b7da0-5bcb-4db9-942b-a3e97f221776)

- The script starts by checking if the group "elryan" exists.
- Since "elryan" does not exist, the script creates it with `sudo groupadd "$group"`.
- Next, the script checks if the user "doaa" exists.
- Since "doaa" exists, the script prints "doaa already exists." and adds "doaa" to the "elryan" group with `sudo usermod -aG "$group" "$user"`.
- The script then confirms the addition by printing "doaa has been added to elryan group successfully".
- Finally, it displays user and group information.

**Then, I change the user in the script from "doaa" to "heba" and run it again.**

## Second Run with User "heba"
![Screenshot from 2024-07-18 03-29-15](https://github.com/user-attachments/assets/72efa48f-8251-41b1-9228-50c55778384b)

- The script starts by checking if the group "elryan" exists.
- Since "elryan" already exists, the script does not create it again.
- Next, the script checks if the user "heba" exists.
- Since "heba" does not exist, the script creates the user "heba" and adds her to the "elryan" group with `sudo useradd -m -G "$group" "$user"`.
- The script then confirms the addition by printing "heba has been added to elryan group successfully".
- Finally, it displays user and group information.



# Section 2

**Question1:** Create a supplementary (Secondary) group called pgroup with group ID of 30000.  
**Answer:**`$ sudo groupadd -g 30000 pgroup`

**Question2:** Lock any user created account so he can't log in.  
**Answer:**`$ sudo usermod -L doaa`

**Question3:** Delete user account.  
**Answer:**`$ sudo userdel -r doaa`

**Question4:** Delete group account.  
**Answer:**`$ sudo groupdel pgroup`

**Question5:** State the difference between adduser and useradd with example shown.  
**Answer:**  
> **adduser**
> - More user-friendly and interactive, making it easier for beginners or those who prefer a guided setup process.
> - Automatically creates the home directory and sets up a default environment, including copying files from /etc/skel to the new home directory.
> ```
>  sudo adduser heba
> ```

>  **useradd**
>  - More basic and requires manual configuration. Suitable for scripts and advanced users who need fine control over user creation.
>  -   Does not create a home directory by default (unless -m is specified) and requires explicit options to set user information.
>  ```
>  sudo useradd -m heba
> ```



