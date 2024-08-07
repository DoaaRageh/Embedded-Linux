# Create Buildroot Package
Create a new Buildroot package by organizing source files, writing a Makefile, and configuring Buildroot to build and install a custom application into the root filesystem.

## Create Directory Structure
Create the necessary directory structure for the package.
```
mkdir -p package/simpleapp/src
```
## Create the Source File
Navigate to the source directory and create the **main.c** file.
```
cd package/simpleapp/src
touch main.c
vim main.c
```
Write the following code inside **main.c**
```
#include <stdio.h>

int main() {
    printf("Hello from Application\n");
    return 0;
}
```
## Create the Makefile
Create the Makefile that Buildroot will use to compile the application.
```
touch Makefile
vim Makefile
```
Inside the **Makefile**, write the following
```
simpleapp: main.c
        $(CC) $< -o $@

.PHONY: clean
clean:
        -rm simpleapp

```
## Create Buildroot Package Makefile
Navigate back to the **simpleapp** directory and create the **simpleapp.mk** file.
```
cd ../
touch simpleapp.mk
vim simpleapp.mk
```
Write the following content in **simpleapp.mk**
```
SIMPLEAPP_VERSION = 1.0
SIMPLEAPP_SITE = package/simpleapp/src
SIMPLEAPP_SITE_METHOD = local

define SIMPLEAPP_BUILD_CMDS
    $(MAKE) CC="$(TARGET_CC)" LD="$(TARGET_LD)" -C $(@D)
endef

define SIMPLEAPP_INSTALL_TARGET_CMDS
    $(INSTALL) -D -m 0755 $(@D)/simpleapp  $(TARGET_DIR)/usr/bin
endef

$(eval $(generic-package))
```
## Create Buildroot Configuration File
Create the **Config.in** file.
```
touch Config.in
vim Config.in
```
Write the following content in **Config.in**
```
config BR2_PACKAGE_SIMPLEAPP
    bool "simpleapp"
    help
        simpleapp package.
```   
## Update Main Package Config.in
Navigate back to the package directory in Buildroot and update the **Config.in** file to include the new package.
```
cd ../
vim Config.in
```
Add the following menu entry under **Target Packages**
```
menu "SIMPLEAPP Packages"
    source "package/simpleapp/Config.in"
endmenu
```
## Configure Buildroot
Configure buildroot to include the new package
```
cd ~/builroot
make menuconfig
```
Go to **Target packages**, then **SIMPLEAPP Packages**, and select **simpleapp** package by pressing **Space**.
![Screenshot from 2024-08-06 00-10-53](https://github.com/user-attachments/assets/cb7536d2-713a-4975-a6b0-437034865258)

![Screenshot from 2024-08-06 00-11-15](https://github.com/user-attachments/assets/48cdf6f4-7cf4-4b08-adc4-dfb6786443b9)
## Build Buildroot
```
make -j8
```
![Screenshot from 2024-08-06 00-16-02](https://github.com/user-attachments/assets/3e6db460-896c-4fa0-9723-9275fe57b769)

![Screenshot from 2024-08-06 00-15-29](https://github.com/user-attachments/assets/9ffa58f3-ea5d-43d6-b9a6-9ed9d452dd3e)
Once the build is complete, the custom application **simpleapp** will be part of the root filesystem.

## Run the Application
```
cd /usr/bin
./simpleapp
```
![Screenshot from 2024-08-06 00-26-33](https://github.com/user-attachments/assets/c6a49fdd-4930-4cf9-9656-551dae6d1055)

