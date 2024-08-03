# BusyBox with NFS
configure an NFS server on your host machine to provide the root filesystem for a BusyBox-based embedded Linux system.
- Install and set up the NFS server.
- Prepare the root filesystem.
- Configure network settings.
- Boot the kernel in QEMU with NFS as the root filesystem.

## Install NFS Server
```
sudo apt install nfs-kernel-server
```
**Verify the NFS Server Status**

ensure that NFS Server is running properly
![Screenshot from 2024-07-27 19-50-52](https://github.com/user-attachments/assets/cfdef6d9-fa7b-4c5d-83c2-eb174c8723fa)

## Mount rootfs
**Create a Mount Point** 

Create a directory where the NFS share will be mounted.
```
sudo mkdir /srv/nfs-share
```
**Copy Data to the NFS Share**
```
sudo cp -r ~/rootfs/* /srv/nfs-share/
```
**Check IP address of your host machine**
```
ifconfig
```
This command displays the network interfaces and their IP addresses. You need to know the server's IP address to configure the client to connect to it.
![Screenshot from 2024-08-02 15-28-24](https://github.com/user-attachments/assets/e0dc2f99-e45d-4405-8ea5-cb1167c8841d)

The IP address for my computer is `192.168.1.3`. so i will assign `192.168.1.10` to the target (QEMU).

**Edit the Exports File**
```
sudo vim /etc/exports
```
Add the following line to export the **/srv/nfs-share** directory
```
/srv/nfs-share 192.168.1.10(rw,no_root_squash,no_subtree_check)
```
- **/srv/nfs-share:** This specifies the directory on the NFS server that you are sharing.
- **192.168.1.10:** This specifies the client that is allowed to access the NFS share.
- **(rw,no_root_squash,no_subtree_check):** These are the options that control the permissions and behavior of the NFS share for the specified client.
    - **rw:** This option allows the specified client to have read and write access to the shared directory.
    - **no_root_squash:** By default, NFS changes the root user's permissions to an anonymous user (nobody). The `no_root_squash` option allows the client’s root user to retain root privileges on the server    
    - **no_subtree_check:** By default, NFS performs checks to ensure that the file being accessed is within the exported directory. The `no_subtree_check` option disables this behavior to improve performance.

![image](https://github.com/user-attachments/assets/ab889944-a5de-40c2-89a5-605b53fba643)

**Restart the NFS**
```
sudo systemctl restart nfs-kernel-server
```
Restart the NFS server to apply the changes made in the `/etc/exports` file.

**Edit the tapScript**
![Screenshot from 2024-08-02 17-12-22](https://github.com/user-attachments/assets/58326d95-8d1f-48a4-9373-f2348515125d)

## Start QEMU
```
sudo qemu-system-arm -M vexpress-a9 -nographic -net nic -net tap,script=./tapScript -kernel u-boot -sd ~/sd.img
```  
We need to set up IP addresses for the server (computer) and client (QEMU). The kernel will be booted from a TFTP server, and the target’s root filesystem will be mounted from the NFS server.

**Set Server IP Address**
```
setenv serverip 192.168.1.3
```
Configures the IP address of the NFS server in U-Boot. This tells the client where to find the NFS share.

**Set Client IP Address**
```
setenv ipaddr 192.168.1.10
```
Configures the IP address of the NFS client (QEMU) in U-Boot.

**Edit the bootcmd Environment Variable**
```
editenv bootcmd
tftp $kernel_addr_r zImage;tftp $fdt_addr_r vexpress-v2p-ca9.dtb; bootz $kernel_addr_r - $fdt_addr_r
```
  Load the kernel image and device tree from the TFTP server and then boot the kernel.

**Edit the bootargs Environment Variable**
```
editenv bootargs
console=ttyAMA0  root=/dev/nfs ip=192.168.1.10:::::eth0 nfsroot=192.168.1.3:/srv/nfs-share,nfsvers=3,tcp rw init=/sbin/init
```
  Set kernel parameters to
  - Use a serial console.
  - Mount the root filesystem from an NFS server.
  - Set the network settings and initial program to run during boot.

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

![Screenshot from 2024-08-02 17-17-13](https://github.com/user-attachments/assets/e52edd85-1286-4c30-83ee-6fef2805b5a1)

![Screenshot from 2024-08-02 17-18-00](https://github.com/user-attachments/assets/3b139193-a9c7-4db2-be78-1e612749d5bd)

![Screenshot from 2024-08-02 17-18-46](https://github.com/user-attachments/assets/ff80f6bf-586c-4350-8117-c2585b82d671)

