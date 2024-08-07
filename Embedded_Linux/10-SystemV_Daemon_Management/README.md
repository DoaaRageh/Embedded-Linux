# Embedded-Linux

# System-V Daemon Management
Set up System-V initialization scripts to manage two custom daemons, **hello** and **hi**, at different runlevels.

- Create script files for **hello** and **hi**.
- Create runlevel directories and create symbolic links in these directories to the initialization scripts.
- Write an **rc** script for transitions and update the **inittab** file.

## Create Scripts
Navigate to the `/usr/bin` directory and create two script files, **hello** and **hi**
```
cd /usr/bin
touch hello hi
```
![Screenshot from 2024-08-06 14-58-50](https://github.com/user-attachments/assets/6571c29c-6b09-4863-8fb6-ce8c65189fb5)

Write the following content to the **hello** script
```
#!/bin/sh 

while true; do  
    echo "Hello from runlevel 2" 
sleep 10 
done
```
Write the following content to the **hi** script
```
#!/bin/sh

while true; do 
    echo "Hi from runlevel 3" 
sleep 10
done
```
Make both scripts executable
```
chmod +x hello
chmod +x hi
```
## Create runlevel directories
Navigate to the **/etc** directory and create directories for runlevels 2 and 3
```
cd /etc
mkdir rc2.d rc3.d
```
![Screenshot from 2024-08-06 15-34-23](https://github.com/user-attachments/assets/cddaf4b6-0a8f-4b15-b412-4e6e99205b25)

## Create Initialization Scripts
Navigate to the **/etc/init.d** directory and create initialization scripts for **hello** and **hi**
```
cd /etc/init.d
touch hello hi
```
![Screenshot from 2024-08-06 15-33-15](https://github.com/user-attachments/assets/3aa317ab-9779-41ed-abae-9e4aca1ccdb1)

Write the following content to the **hello** initialization script
```
case "$1" in
  start)               
        printf "Starting Your Daemon: "
        start-stop-daemon -S -n hello -a  /usr/bin/hello &        
        [ $? = 0 ] && echo "OK" || echo "FAIL"         
        ;;                                    
  stop)   
        printf "Stopping Your Daemon: "
        start-stop-daemon -K -n hello       
        [ $? = 0 ] && echo "OK" || echo "FAIL"
        ;;                                                           
  *)                   
        echo "Usage: $0 {start|stop}" 
        exit 1                               
esac             
                 
exit $? 
```
Write the following content to the **hi** initialization script
```
case "$1" in
  start)               
        printf "Starting Your Daemon: "
        start-stop-daemon -S -n hi -a  /usr/bin/hi &        
        [ $? = 0 ] && echo "OK" || echo "FAIL"         
        ;;                                    
  stop)   
        printf "Stopping Your Daemon: "
        start-stop-daemon -K -n hi       
        [ $? = 0 ] && echo "OK" || echo "FAIL"
        ;;                                                           
  *)                   
        echo "Usage: $0 {start|stop}" 
        exit 1                               
esac             
                 
exit $? 
```
Make both scripts executable
```
chmod +x hello
chmod +x hi
```
## Create Symbolic Links in Runlevel Directories
Create symbolic links in the **rc2.d** and **rc3.d** directories to manage the startup and shutdown of these scripts

For run level 2:
```
cd /etc/rc2.d
ln -s  /etc/init.d/hello  ./S22hello
ln -s  /etc/init.d/hi  ./K22hi
```
For run level 3:
```
cd /etc/rc3.d
ln -s  /etc/init.d/hello  ./K22hello
ln -s  /etc/init.d/hi  ./S22hi
```
## Create the rc Script
Navigate to the **/etc/init.d** directory and create the **rc** script to handle the transitions between runlevels
```
cd /etc/init.d
touch rc
```
Write the following content to the **rc** script
```
#!/bin/sh

directory="$1"

case "$directory" in
    "2")
        for i in /etc/rc2.d/K??*; do
            [ ! -f "$i" ] && continue
            "$i" stop
        done
  
	for i in /etc/rc2.d/S??*; do
            [ ! -f "$i" ] && continue
            "$i" start
        done
	;;

    "3")
        for i in /etc/rc3.d/K??*; do
            [ ! -f "$i" ] && continue
            "$i" stop
        done

	for i in /etc/rc3.d/S??*; do
            [ ! -f "$i" ] && continue
            "$i" start
        done
        ;;

    *)
        echo "Usage: $0 {2|3} (runlevel)"
        exit 1
        ;;
esac

exit 0
```
Make the script executable
```
chmod +x rc
```
## Update  inittab
Edit the **/etc/inittab** file to include entries for the **rc** script to manage runlevels 2 and 3
```
vim /etc/inittab
```

Add the following lines to the **inittab** file
```
si11:2:wait:/etc/init.d/rc 2
si12:3:wait:/etc/init.d/rc 3
```
![Screenshot from 2024-08-06 15-51-27](https://github.com/user-attachments/assets/5aa8c507-aa52-4ae1-91b5-368b15a4c397)
## Switch Between Runlevels
Switch to runlevel 2
```
init 2
```
![Screenshot from 2024-08-06 14-16-23](https://github.com/user-attachments/assets/819795a8-1c50-4a40-a38a-49276f411a06)
Switch to runlevel 3
```
init 3
```
![Screenshot from 2024-08-06 14-16-47](https://github.com/user-attachments/assets/52b1d32c-75db-47ba-bf20-6969ae1365b1)

This will start the **hello** script in runlevel 2 and the **hi** script in runlevel 3

