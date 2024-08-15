# Create a Custom Layer and Recipe in Yocto
- Set up the Yocto build environment.
- Create and configure a new layer.
- Write a custom recipe.
- Update the build configuration.
- Build the recipe to ensure it functions as expected.

## Set Up the Yocto Build Environment
```
cd ~/yocto
source oe-init-build-env
```
This sets up the environment variables and paths for BitBake.

## Create a New Layer
Create a new bitbake layer named **meta-iti** to contain custom recipes and configurations.
```
cd ~/yocto
bitbake-layers create-layer meta-iti
```

## Create a Recipe
**Create a Directory for Your Recipes**
```
cd ~/yocto/meta-iti/
mkdir my_recipes
```

**Modify the Layer Configuration**
```
cd conf/
vim layer.conf 
```
![Screenshot from 2024-08-07 17-02-09](https://github.com/user-attachments/assets/52cfe4e9-0fd0-406e-b79b-b94592a7b63f)
- **BBFILES:append = " ${LAYERDIR}/my-*/*.bb":** Adds recipe files in directories matching `my-*` within the layer directory to bitbake's search path.
- **VAR = "3":** Sets the `VAR` variable to `3`, affecting the displayed message in the recipe based on its value.

**Create a Bitbake Recipe**
```
cd ../my-recipes
touch myrecipe_1.0.bb
vim myrecipe_1.0.bb
```
**Write the Recipe**
```
SUMMARY = "bitbake-layers recipe"
DESCRIPTION = "Recipe created by Doaa"
LICENSE = "MIT"

python do_display_banner() {
    var = d.getVar('VAR')
    if var == "3":
        bb.plain("***********************************************");
        bb.plain("*                                             *");
        bb.plain("*                   Hello                     *");
        bb.plain("*                                             *");
        bb.plain("***********************************************");
    elif var == "4":
        bb.plain("***********************************************");
        bb.plain("*                                             *");
        bb.plain("*                     Hi                      *");
        bb.plain("*                                             *");
        bb.plain("***********************************************");
    else:
        bb.plain("***********************************************");
        bb.plain("*                                             *");
        bb.plain("*              Welcome To Recipe              *");
        bb.plain("*                                             *");
        bb.plain("***********************************************");
}

addtask display_banner before do_build
```
The recipe is designed to display **Hello** when the VAR variable is set to 3, **Hi** when VAR is set to 4, and **Welcome To Recipe** for any other value.
## Update the Build Configuration
```
cd ~/yocto/poky/build/conf
vim bblayers.conf
```
The **bblayers.conf** file lists all the layers included in the build. Add the path to your new **meta-iti** layer here to include it in the build process.

![Screenshot from 2024-08-07 17-11-43](https://github.com/user-attachments/assets/c991f9f3-1345-415d-bfad-678975f900c0)

## Show the Active Layers
Verify that **meta-iti** is listed among the active layers.
```
bitbake-layers show-layers
```

![Screenshot from 2024-08-07 17-14-36](https://github.com/user-attachments/assets/5c3a53bc-4907-4614-8aff-0bfd46395056)

## Build the Recipe
Run bitbake to build your custom recipe.
```
bitbake myrecipe
```
![Screenshot from 2024-08-07 17-16-59](https://github.com/user-attachments/assets/929a05e9-8fa4-4210-82a2-171e4d041b87)



