# Run QEMU with Emulated SD Card

## Setup U-Boot
U-Boot is essential for simulating the boot process and ensuring that the virtual SD card works correctly.

**Clone the U-Boot Repository**
```
git clone https://github.com/u-boot/u-boot
```
**Navigate to the U-Boot Directory**

```
cd u-boot
```
**Configure U-Boot Machine**
```
ls configs/ | grep vexpress_ca9x4_defconfig
```
Replace **vexpress_ca9x4_defconfig** with the name of the configuration file specific to your target machine.
- **ls configs/:** Lists the files in the configs directory, which contains U-Boot configuration files for different machines.
- **|:** The pipe symbol redirects the output of the **ls** command to the **grep** command.
- **grep vexpress_ca9x4_defconfig:** Searches through the list for the file named vexpress_ca9x4_defconfig.

**Set the cross compiler into the environment to be used by the U-Boot**
```
export CROSS_COMPILE=~/x-tools/arm-cortexa9_neon-linux-musleabihf/bin/arm-cortexa9_neon-linux-musleabihf-
```
Replace **~/x-tools/arm-cortexa9_neon-linux-musleabihf/bin/** with the actual path to your ARM cross-compilation toolchain **arm-cortexa9_neon-linux-musleabihf-**.

**Set the ARCH environment variable to arm**
```
export ARCH=arm
```
It specifies that the build process should target the ARM architecture.

**configure U-Boot with the default settings for the Vexpress Cortex-a9**
```
make vexpress_ca9x4_defconfig
```
**Open Configuration Menu**
```
make menuconfig
```
This command opens a text-based graphical interface for interactively configuring build options and settings in u-boot.
- Support editenv

    Go to **Command Line Interface**, then **Environment Commands**, and enable **editenv** by pressing **Space**.
![Screenshot from 2024-07-25 09-32-17](https://github.com/user-attachments/assets/9dfe0cda-f464-4245-9185-0896737a87c0)

- Support bootd

    Go to **Command Line Interface**, then **Boot Commands**, and enable **bootd** by pressing **Space**.
![Screenshot from 2024-07-25 09-32-39](https://github.com/user-attachments/assets/95741e09-f294-4bf0-8bfa-33d9c26d1856)

- Store the environment variable inside file call uboot.env

    Go to **Environment**, then select **Environment is in a FAT filesystem**, and then set the filename of FAT file to **uboot.env**.
![Screenshot from 2024-07-25 09-44-21](https://github.com/user-attachments/assets/2136bdb0-bfbd-4565-ab71-082dcd5cfd1c)

- Unset support of Flash  

    Go to **Environment**, and unselect **Environment is in flash memory** by pressing **Space**,
![Screenshot from 2024-07-25 09-47-45](https://github.com/user-attachments/assets/9f2ae6df-302f-493c-b819-062a749fc84e)

- Support **FAT file system**  
    - Configure the FAT interface to **mmc**
      
        Go to **Environment**, and set the block device name to **mmc**.
    ![Screenshot from 2024-07-25 10-03-30](https://github.com/user-attachments/assets/7a712da1-28f7-4584-b5c5-18a077dd4b20)

    - Configure the partition where the fat is store to **0:1**
    
        Go to **Environment**, then **Device and partition for where to store the environment in FAT**, and set it to **0:1**.
    ![Screenshot from 2024-07-25 10-19-27](https://github.com/user-attachments/assets/cd12f1ad-ee7f-4830-a9e4-bf5a5d188056)

- Configure **Memory Commands**  

    Go to **Command Line Interface**, then **Memory Commands**, and select **md5sum** and **meminfo**.
![Screenshot from 2024-07-25 10-47-19](https://github.com/user-attachments/assets/0c8f9424-8324-4056-b742-185bf949dd5b)

- Configure **Device access commands**  

    Go to **Command Line Interface**, then **Device access commands**, and select **lsblk**.
![Screenshot from 2024-07-25 10-51-05](https://github.com/user-attachments/assets/65e6918f-e506-4faf-bbb3-06947fe6d329)

- Configure **shell prompt** (optional)  

    Go to **Command Line Interface**, then **shell prompt**, and enter the text you want to appear in the U-Boot shell prompt before it accepts your commands.
![Screenshot from 2024-07-25 10-36-02](https://github.com/user-attachments/assets/c9068efc-2e9f-4d78-9fa3-fcf7573bc938)

- Exit the menu and save your configuration changes.

## Build U-Boot
Run the make command to compile U-Boot with the selected configurations.
```
make
```
## Test U-Boot
**Install Qemu**
```
sudo apt install qemu-system-arm
```
**Run qemu  with Emulated SD card**
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
```
qemu-system-arm -M vexpress-a9 -m 128M -nographic -kernel path/u-boot -sd path/sd.img
```
Replace **path/u-boot** with the actual path to the U-Boot binary and **path/sd.img** with the path to your SD card image.

