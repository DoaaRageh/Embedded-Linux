# Create and Build a Yocto Recipe for a Demo Application
Create a new bitbake recipe to fetch, build, and install a demo application from a GitHub repository in Yocto.

## Set Up the Yocto Build Environment
Navigate to the Yocto directory and source the build environment script. This prepares the environment for building recipes.
```
cd ~/yocto/poky
source oe-init-build-env
```

## Create a New Recipe
Navigate to the **meta-iti** layer's recipes directory, and create a new recipe for the demo application.
```
cd ~/yocto/meta-iti/my-recipes/
touch demoapp_1.0.bb
vim demoapp_1.0.bb
```
**Write the demoapp Recipe**

In the **demoapp_1.0.bb** file, write a bitbake recipe to fetch, build, and install a demo application from a GitHub repository. 
```
SUMMARY = "Demo App"
DESCRIPTION = "A recipe to build a DemoApp from GitHub."

LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

SRC_URI = "git://github.com/FadyKhalil/DemoApp.git;protocol=https;branch=main"
SRCREV = "720c663c5fd7246b4b42c5205d74db7d9784b5b2"

DEPENDS = "cmake"

inherit cmake

S = "${WORKDIR}/git"

do_configure() {
    cmake -S ${S} -B ${B} -DCMAKE_EXE_LINKER_FLAGS="-static" -DCMAKE_SHARED_LINKER_FLAGS="-static"
}

do_compile() {
    oe_runmake -C ${B}
}

do_install() {
    mkdir -p ${D}${bindir}
    cp ${B}/calculator ${D}${bindir}
}
```
The recipe uses CMake for configuration and build processes.

## Build the demoapp Recipe
Use the bitbake command to build the demo application. This step compiles the code and prepares the package for deployment.
```
bitbake demoapp
```
![Screenshot from 2024-08-15 10-37-58](https://github.com/user-attachments/assets/9c333f3e-cd76-4248-a8d2-bf81c288c5d1)

## Check Application
After the build completes, verify the installation by navigating to the directory where the **calculator** binary is installed. Run the application to ensure it functions correctly.

![Screenshot from 2024-08-15 18-10-51](https://github.com/user-attachments/assets/5a9c0e46-e483-49a3-8246-dc02f5edb2d7)

