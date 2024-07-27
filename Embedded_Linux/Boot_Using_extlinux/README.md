# Boot using extlinux
- Boot a system using extlinux configuration with QEMU by creating and configuring extlinux.conf.
- Set up QEMU and configure U-Boot to use bootflow for automatic booting.

## Create and Configure extlinux.conf
- **Create the extlinux Directory**
  
    Create a directory named extlinux in the boot partition. This directory will contain the bootloader configuration.
  ```
  mkdir -p /media/doaa/boot/extlinux
  ```
  
- **Create the extlinux.conf File**

    Inside the extlinux directory, create a file named extlinux.conf. This file is used to configure the bootloader, specifying which kernel to load and any necessary boot parameters.
  ```
  touch /media/doaa/boot/extlinux/extlinux.conf
   ```
  
- **Write Configuration to extlinux.conf**

    Add the necessary boot configuration details to extlinux.conf.
![Screenshot from 2024-07-27 05-31-03](https://github.com/user-attachments/assets/e99646d9-ea4b-45de-84c5-6e33b711c029)
  - **LABEL myconf**: This sets a label for the boot entry, which can be used to identify this particular boot configuration.
  - **KERNEL `../zImage`:** Specifies the path to the kernel image.
  - **FDT `../myfile.dtb`:** Specifies the path to the Device Tree Blob (DTB) file. 

**When you boot the QEMU:**
- **Scan for Boot Configuration:** U-Boot will look for the extlinux directory in the boot partition and check for the extlinux.conf file.
- **Parse extlinux.conf:** U-Boot will read the extlinux.conf file and parse the configuration details.
- **Identify the Boot Entry:** U-Boot will identify the boot entry labeled myconf.
- **Load the Kernel:** U-Boot will load the kernel image from the specified path `../zImage`.
- **Load the Device Tree:** U-Boot will load the Device Tree Blob from the specified path `../myfile.dtb`.
- **Boot the System:** U-Boot will then proceed to boot the system using the loaded kernel and device tree.

## Start QUMU
```
qemu-system-arm -M vexpress-a9 -m 128M -nographic -kernel u-boot -sd ~/sd.img
```
- **qemu-system-arm:** Starts the QEMU emulator for ARM architecture.
- **-M vexpress-a9:** Specifies the machine type to emulate (Versatile Express with ARM Cortex-A9).
- **-m 128M:** Allocates 128MB of RAM to the emulated system.
- **-nographic:** Disables graphical output and redirects the console to the terminal.
- **-kernel u-boot:** Uses the U-Boot binary located in the current directory as the kernel.
- **-sd ~/sd.img:** Attaches the virtual SD card image located at `~/sd.img`.

**Edit the bootcmd Environment Variable**
```
editenv bootcmd
bootflow scan
```
By setting the **bootcmd** environment variable to **bootflow scan**, you enable U-Boot to automatically find and use the extlinux.conf configuration for booting your system.

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

To ensure that both the kernel image and the Device Tree Blob (DTB) are loaded correctly into memory, you should verify the contents of the memory addresses specified by `kernel_addr_r` and `fdt_addr_r` in U-Boot.

- **zImage**
![Screenshot from 2024-07-27 05-32-22](https://github.com/user-attachments/assets/6f901096-8f58-4e20-b8c0-9b72d997f2e6)

- **myfile.dtb**
![Screenshot from 2024-07-27 05-32-49](https://github.com/user-attachments/assets/51ffa09e-78c0-483d-9699-f47da457fd7f)

