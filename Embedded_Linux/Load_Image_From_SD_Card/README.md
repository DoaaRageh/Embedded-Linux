# Load Image from SD Card
- **Create zImage:** Include the content "Hello from zImage".
- **Create myfile.dtb:** Include the content "Hello from dtb file".
- **Create a Script:** to check MMC availability and load zImage and myfile.dtb.
- **Generate U-Boot Script Image:** Convert the script into a U-Boot-compatible image.
- **Edit bootcmd:** Configure U-Boot to automatically load and execute the script on boot.

## Create zImage and myfile.dtb files in the boot partition
- Write in zImage file **Hello from zImage**
![Screenshot from 2024-07-25 15-19-58](https://github.com/user-attachments/assets/89a28f37-de9d-48c6-992b-9ad77808d2aa)

- Write in myfile.dtb **Hello from dtb file**
![Screenshot from 2024-07-26 07-46-39](https://github.com/user-attachments/assets/ffdc32ff-90eb-4275-adb7-f1a324d3e6a5)


## Create myScript.txt file in the boot partition
![Screenshot from 2024-07-26 07-09-36](https://github.com/user-attachments/assets/ac057c66-4001-4483-a6af-adbbdaebe705)


This script checks for the availability of the MMC device and network connectivity to load **zImage** and **myfile.dtb** files.

-   **If the MMC device is available:**
    -   Attempts to load **zImage** and **myfile.dtb** from the FAT partition to **0x60100000** and **0x60000000** addresses in DRAM.
    -   Prints a success message: "loaded zImage and dtb files from mmc".
    
-   **If the MMC device is not available but the server is reachable:**
    -   Prints a message indicating that the files loaded from the network: "loaded zImage and dtb files from network".
    
-   **If neither the MMC device is available nor the server is reachable:**
    -   Prints an error message: "No Option".
    
## Generate the U-Boot Script
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
**Run QEMU with the Virtual SD Card**
```
qemu-system-arm -M vexpress-a9 -m 128M -nographic -kernel u-boot -sd ~/sd.img
```
- **qemu-system-arm:** Starts the QEMU emulator for ARM architecture.
- **-M vexpress-a9:** Specifies the machine type to emulate (Versatile Express with ARM Cortex-A9).
- **-m 128M:** Allocates 128MB of RAM to the emulated system.
- **-nographic:** Disables graphical output and redirects the console to the terminal.
- **-kernel u-boot:** Uses the U-Boot binary located in the current directory as the kernel.
- **-sd ~/sd.img:** Attaches the virtual SD card image located at `~/sd.img`.

If the U-Boot binary is not in the current directory, you should provide the full path to the binary.

**Edit the bootcmd Environment Variable**
```
editenv bootcmd
fatload mmc 0:1 0x60003000 ubootScript; source 0x60003000
```
After setting **bootcmd** to `fatload mmc 0:1 0x60003000 ubootScript; source 0x60003000`, U-Boot will automatically load and execute the ubootScript from the SD card on boot, which then loads zImage and myfile.dtb.

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

![Screenshot from 2024-07-26 07-13-48](https://github.com/user-attachments/assets/ddbfd7dd-d0d1-4f94-9e5a-37c15316260b)

To ensure that the script and files have been loaded successfully, use the **md** command in U-Boot to check their contents in memory.
- **ubootScript**
![Screenshot from 2024-07-26 07-27-22](https://github.com/user-attachments/assets/5adc7048-f1e2-4a10-b123-5a59a5b4249f)

- **zImage**
![Screenshot from 2024-07-26 07-30-13](https://github.com/user-attachments/assets/ac4d6859-3aca-4e92-9e0e-37ea2e9c7831)

- **myfile.dtb**
![Screenshot from 2024-07-26 07-37-46](https://github.com/user-attachments/assets/1ecff471-11b1-4447-ade7-75fcbebb7f9e)
