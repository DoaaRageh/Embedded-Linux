# Create Virtual SD Card
- Create a 1GB Zero-Filled Image File Named sd.img.
- Configure the Partition Table.
- Map the Image to a Loop Device.
- Format the Partitions.
- Mount the Partitions.

## Create a 1GB Zero-Filled Image File Named sd.img
```
dd if=/dev/zero of=sd.img bs=1M count=1024
```
-   **dd:** This is a command-line utility used for low-level copying and conversion of raw data. It is often used for creating disk images, making backups, or copying data between devices.

-   **if=/dev/zero:** `if` It specifies the source of the data to be copied.
`/dev/zero` This is a special file in Unix-like operating systems that produces null bytes (zeros) when read.

-   **of=sd.img:** Output file is `sd.img`.

-   **bs=1M:** Block size is 1 megabyte.

-   **count=1024:** Number of blocks to write.

![Screenshot from 2024-07-24 20-52-42](https://github.com/user-attachments/assets/e7438e9c-39e5-4a26-bdd2-072e706bb236)

## Configure the Partition Table
Divide a 1GB virtual SD card into two sections: 
- 200MB bootable FAT16 partition named **boot**.
- 800MB non-bootable ext4 partition named **rootfs**.

open terminal and write:
```
cfdisk sd.img
```
It opens the **sd.img** file as if it were a real disk. This allows you to interact with the disk image and manage its partitions.

 Select **dos** and press Enter.
![Screenshot from 2024-07-25 01-03-22](https://github.com/user-attachments/assets/7c315b56-8634-4219-bed6-6942bf9d8125)

**Create the boot Partition:**
- Select **New** and press Enter, Then select the size of boot partition (200M).
![Screenshot from 2024-07-25 01-13-19](https://github.com/user-attachments/assets/eae41462-dbea-4001-941c-44d7bef68293)

- Select **Primary** and press Enter. This is necessary for it to be bootable partition.
![Screenshot from 2024-07-25 01-15-22](https://github.com/user-attachments/assets/a9b02652-3f63-4dac-8ddf-8b25016060c5)

- Select **Bootable** and press Enter, An asterisk (*) will be added in the Boot option in the table.
![Screenshot from 2024-07-25 01-23-05](https://github.com/user-attachments/assets/977ef35c-ec08-463c-9116-c35176189e53)

- Select **Type** and press Enter, Then select **FAT16** from the list.
![Screenshot from 2024-07-25 01-29-36](https://github.com/user-attachments/assets/93bf0105-9e59-4002-b176-20eb3d227d45)

- Use the arrow keys to navigate down to the remaining free space.

**Create the rootfs Partition:**
- Select **New** and press Enter, Then select the size of rootfs partition (800M).
- Select **extended** and press Enter.
- Select **Type** and press Enter, Then select **linux (ext4)** from the list.
![Screenshot from 2024-07-25 05-50-51](https://github.com/user-attachments/assets/8d52eb66-11c0-4682-ab24-2536144f127f)

- Select **write** to save configurations and press Enter, then write **yes** to confirm.
![Screenshot from 2024-07-25 05-55-18](https://github.com/user-attachments/assets/f24ffa96-11f2-4e10-b7f4-3903e028a4a4)

- Select **Quit** and press Enter.

## Map the Image to a Loop Device
A loop device is a pseudo-device in Unix-like operating systems that allows a file to be mounted and accessed as if it were a block device (like a hard drive or a partition). This is useful for working with disk images, such as ISO files or disk image files **(.img)**, without needing to write them to physical media.
```
sudo losetup -f --show --partscan sd.img
```
- **losetup:** Associate the disk image with a loop device.
- **-f:** Finds the first available (unused) loop device.
- **--show:** Shows the name of the loop device.
- **--partscan:** scans the image for partitions.

![Screenshot from 2024-07-25 06-07-29](https://github.com/user-attachments/assets/2452245f-4abc-4d9d-8fa2-66f545e838bf)

Check if the specific loop device **loop15** is currently in use and display its details:
```
lsblk | grep loop15
```
Replace **loop15** with the loop device associated with your virtual SD card.
-   **lsblk:** Lists information about all available or the specified block devices.
-   **|:** A pipe that passes the output of `lsblk` as input to the next command.
-   **grep loop15:** Searches the output for the term `loop15`.

![Screenshot from 2024-07-25 06-26-32](https://github.com/user-attachments/assets/80f5af8c-c601-46b5-bd6b-eb07a949f891)

## Format the Partitions

**Format the boot partition**
```
sudo mkfs.vfat -F 16 -n boot /dev/loop15p1
```
- **mkfs.vfat:** Creates a FAT filesystem on the specified partition.
- **-F 16:** Specifies the FAT type. 16 indicates **FAT16**, which is commonly used for smaller partitions or embedded systems.
- **-n boot:** Sets the filesystem label to boot.
- **/dev/loop15p1:** The specific partition on the loop device you are formatting.

![Screenshot from 2024-07-25 07-05-23](https://github.com/user-attachments/assets/6d58a60d-aeea-4fe1-ab93-a953fe286905)

**Format the rootfs partition**
```
sudo mkfs.ext4 -L rootfs /dev/loop15p2
```
- **mkfs.ext4:** Creates an ext4 filesystem on the specified partition.
-   **-L rootfs:** Sets the filesystem label to rootfs.
-   **/dev/loop15p2:** Specifies the partition to format.

![Screenshot from 2024-07-25 07-06-55](https://github.com/user-attachments/assets/365f3aa9-c47a-45b8-b1cb-ea0b735fffc3)

## Mount the Partitions
It is essential for accessing and managing the files on a partition

**Create mount points**
- You can create a mount point in any directory you prefer on your filesystem. A mount point is simply a directory where the contents of a partition will be accessed.
```
sudo mkdir /mnt/boot
sudo mkdir /mnt/rootfs
```
**Mount the partitions**
```
sudo mount /dev/loop15p1 /mnt/boot
sudo mount /dev/loop15p2 /mnt/rootfs
```
Now you can navigate to the mount points to work with the files on the partitions.
