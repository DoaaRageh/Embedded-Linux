# Build Kernel Image for Vexpress
Build and configure the kernel image and DTB files, then boot with extlinux.

## Setup Kernel

**Clone the Kernel Repository**
```
git clone --depth=1 git://git.kernel.org/pub/scm/linux/kernel/git/stable/linux.git
```
**Navigate to the U-Boot Directory**
```
cd linux/
```
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

**Configure the Kernel**
Load the default configuration for vexpress
```
make vexpress_defconfig
```
**Customize the Configuration**
```
make menuconfig
```
This command opens a text-based graphical interface for interactively configuring build options and settings in kernel.
- Enable  devtmpfs
  
    Go to **Device Drivers**, then **Generic Driver options**, and select **Automount devtmpfs** by pressing **Space**.
![Screenshot from 2024-07-25 23-19-55](https://github.com/user-attachments/assets/51860ad0-1538-4805-ac3f-251c53b2b860)

- Change kernel compression to  XZ
  
    Go to **General setup**, then **Kernel compression mode**, and select **XY** by pressing **Space** or **Enter**.
![Screenshot from 2024-07-25 23-26-11](https://github.com/user-attachments/assets/489ccaa7-5a13-42e5-96d1-ec24c788cef8)

- Change your kernel local version to your name and append on it -v1.0
  
    Go to **General setup**, then **Local version - append to kernel release**, and then write your name and your version(-v1.0).
![Screenshot from 2024-07-25 23-49-11](https://github.com/user-attachments/assets/d8cacd06-71f5-4a25-bf01-30eebb3727cd)

- Exit the menu and save your configuration changes.

**Build the Kernel**
```
 make -j4 zImage modules dtbs
```
- **make:** This is the build command used to compile the source code according to the rules defined in the Makefile.
- **-j4:** This option tells `make` to execute 4 jobs (or compile processes) simultaneously. This can significantly speed up the build process, especially on multi-core processors. You can adjust the number according to the number of cores in your CPU for optimal performance.
- **zImage:** This target compiles the kernel image. zImage is a compressed version of the kernel image that is typically used for booting on many ARM devices, including vexpress.
- **modules:** This target compiles all the loadable kernel modules. Modules are pieces of code that can be loaded and unloaded into the kernel as needed, without the need to reboot the system.
- **dtbs:** This target builds the Device Tree Blobs. DTBs describe the hardware layout to the kernel, allowing it to know what hardware components are present and how to interface with them. They are essential for ARM systems, which often have varying hardware configurations.

**Verify the Kernel Version**
```
make kernelrelease
```
![Screenshot from 2024-07-26 00-34-56](https://github.com/user-attachments/assets/00c43ad5-da85-48ac-a591-6404ea044e8d)

## Boot using extlinux
**Copy the zImage and dtb file to the boot partition**
- The kernel image **zImage** is located in the **linux/arch/arm/boot/** directory. Copy it to the boot partition.
    ```
  cp linux/arch/arm/boot/zImage /media/doaa/boot/
    ```
- The DTB file **vexpress-v2p-ca9.dtb** is located in the **linux/arch/arm/boot/arm/dts/** directory. Copy it to the boot partition.
  ```
  cp linux/arch/arm/boot/arm/dts/vexpress-v2p-ca9.dtb /media/doaa/boot/
  ```

**Edit extlinux.conf configuration**
![Screenshot from 2024-07-27 07-35-51](https://github.com/user-attachments/assets/5ffa3048-7fe1-4d7e-b463-f4f0e1f32992)


**Start QEMU**
```
qemu-system-arm -M vexpress-a9 -m 128M -nographic -kernel u-boot -sd ~/sd.img
```
**Edit the bootcmd Environment Variable**
```
editenv bootcmd
bootflow scan
```
By setting the `bootcmd` environment variable to `bootflow scan`, you enable U-Boot to automatically find and use the `extlinux.conf` configuration for booting your system.

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
![Screenshot from 2024-07-27 07-45-41](https://github.com/user-attachments/assets/6f563287-03cd-477d-b7cd-8a0c15bbc2d1)

