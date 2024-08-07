# Load Image from Server

-   **Set Up TAP Interface:** Create a configuration script and make it executable.
-   **Install TFTP Server:** Set up and configure TFTP server on the host machine.
-   **Add Files to TFTP:** Place `zImage` and `myfile.dtb` with test content in the tftp directory.
-   **Create U-Boot Script:** Write and convert a script for network-based file loading.
-   **Run QEMU:** Start QEMU with TAP and SD card, and configure U-Boot to use the script.

## Set Up TAP Network Interface
Create a TAP network interface on your x86 host machine. This allows QEMU to communicate with your network.

- Create a file named **tapScript** with the following content
![Screenshot from 2024-07-25 12-59-17](https://github.com/user-attachments/assets/719d8b97-f45d-4986-9a41-fa387d3b0e88)
This script assigns a static IP address to a TAP interface and brings the interface up.

- Make the script executable
    ```
    chmod +x tapScript
    ```
## Configure TFTP Server on the Host
- Install a TFTP server on your x86 host machine.
    ```
    sudo apt install tftpd-hpa
    ```
- Verify the TFTP Server Status
    ```
    sudo systemctl status tftpd-hpa
    ```
  ![Screenshot from 2024-07-26 13-05-20](https://github.com/user-attachments/assets/0c9bc4ab-fdf0-4226-bfa2-ea31bbff1525)
After installing the TFTP server, you want to ensure that it is running properly.

- Edit TFTP Configuration
    - Open the configuration file located at **/etc/default/tftpd-hpa** using a text editor with root permissions.
        ```
        sudo vim /etc/default/tftpd-hpa
	  ```
	  
   - Add the **--create** option to the **TFTP_OPTIONS** line in the configuration file. This option allows the TFTP server to create new files on the server.
   ![Screenshot from 2024-07-26 13-47-14](https://github.com/user-attachments/assets/c92abe09-6536-453d-a36b-a95d2bf22881)

- Change the Owner of the TFTP Directory
Ensure the **TFTP** server can access and manage files in the directory by setting the ownership to the **tftp** user
    ```
    chown tftp:tftp /srv/tftp
    ```
## Create zImage and myfile.dtb files in the tftp directory
- Write in zImage **Hello from zImage on the server**
![Screenshot from 2024-07-26 15-10-35](https://github.com/user-attachments/assets/9e7158f7-3b33-4065-8eb3-9c610d679fb2)

- Write in myfile.dtb **Hello from dtb file on the server**
![Screenshot from 2024-07-26 15-11-22](https://github.com/user-attachments/assets/905a890e-c309-4bf4-878d-80f06b0d12b3)

## Create myScript.txt file in the boot partition
![Screenshot from 2024-07-26 18-38-28](https://github.com/user-attachments/assets/07aa031e-48a1-451c-bc29-bcb8da088430)
```
setenv ipaddr 192.168.0.8
setenv serverip 192.168.0.7
  ```
  - These lines set environment variables for network configuration
	- **ipaddr** is set to **192.168.0.8**, which is the IP address of the device.
	- **serverip** is set to **192.168.0.7**, which is the IP address of the TFTP server.
```
tftp $kernel_addr_r zImage
tftp $fdt_addr_r myfile.dtb
```
- These lines use the TFTP protocol to download files:
	- The **zImage** file is downloaded to the memory address specified by the **kernel_addr_r** variable.
	- The **myfile.dtb** file is downloaded to the memory address specified by the **fdt_addr_r** variable.
```
echo "Loaded zImage and dtb files from network"
```
- This line prints a message indicating that the `zImage` and `dtb` files have been successfully loaded from the network.


## Generate the U-Boot script image
Convert the text file into a U-Boot script image using the **mkimage** tool
```
mkimage -A arm -T script -C none -n ubootScript -d myscript.txt ubootScript
```
- **mkimage:** U-Boot's image creation tool.
- **-A arm:** Specifies the architecture as ARM.
- **-T script:** Sets the image type to script.
- **-C none:** No compression.
- **-n ubootScript:** Names the image.
- **-d myscript.txt:** Input file containing the script.
- **ubootScript:** Output file name for the U-Boot script image.

This command creates a binary image **ubootScript** that U-Boot can execute.

## Execute U-Boot Script
**Run QEMU with TAP Network**
```
sudo qemu-system-arm -M vexpress-a9 -nographic -net nic -net tap,script=./tapScript -kernel u-boot -sd ~/sd.img
```
-   **sudo qemu-system-arm:** Runs QEMU with ARM architecture emulation.
-   **-M vexpress-a9:** Specifies the machine type to emulate (Versatile Express a9).
-   **-nographic:** Disables graphical output, using the terminal instead.
-   **-net nic:** Adds a virtual network interface card to the emulated ARM machine.
-   **-net tap,script=./tapScript:** Sets up a TAP interface on the x86 host and configures it using tapScrip.
-   **-kernel u-boot:** Specifies the U-Boot binary to be used as the kernel image.
-   **-sd ~/sd.img:** Specifies the SD card image to be used.

**Edit the bootcmd Environment Variable**
```
editenv bootcmd
fatload mmc 0:1 0x60003000 ubootScript; source 0x60003000
```
After setting **bootcmd** to **fatload mmc 0:1 0x60003000 ubootScript; source 0x60003000**, u-boot will automatically load and execute the **ubootScript** from the SD card on boot, which then loads zImage and myfile.dtb.

**Set the kernel_addr_r and fdt_addr_r variables**
```
setenv kernel_addr_r 0x60100000
setenv fdt_addr_r 0x60000000
```
Configure the **kernel_addr_r** and **fdt_addr_r** variables to specify the DRAM addresses for loading the zImage and myfile.dtb files.

**Save the Environment Variables**
```
saveenv
```
Save the changes to ensure they persist across reboots.

**Reboot QEMU**
```
reset
```
Restart QEMU to apply the changes.
![Screenshot from 2024-07-26 19-07-34](https://github.com/user-attachments/assets/b4be7048-818e-4de4-9fb7-56dc13a2200d)

To ensure that the script and files have been loaded successfully, use the **md** command in U-Boot to check their contents in memory.
- **ubootScript**
![Screenshot from 2024-07-26 19-09-58](https://github.com/user-attachments/assets/407e1c3f-47fa-45cc-80ca-959103db60f7)

- **zImage**
![Screenshot from 2024-07-26 19-11-01](https://github.com/user-attachments/assets/49394eb3-2b86-454d-8443-8e32af0fdacc)

- **myfile.dtb**
![Screenshot from 2024-07-26 19-11-53](https://github.com/user-attachments/assets/ea67d770-2e88-4c82-a4dc-0c6b9c3da4e2)


