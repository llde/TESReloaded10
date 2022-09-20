# TESReloaded
TESReloaded is a custom made graphical extender for Bethesda games Oblivion, Fallout New Vegas and Skyrim, developped by [Alenet](https://github.com/Alenett) and maintained by [Llde](https://github.com/llde).

It overrides the rendering pipeline to inject various effects that can be completely configured.

It relies on the script Extender of each game, such as [xOBSE](https://github.com/llde/xOBSE) or [xNVSE](https://github.com/xNVSE/NVSE). The script extender must be installed first. 

----
## Features
The mod supports the following effects (more to come):
* **Ambient occlusion**

Proximity shadowing.

* **BloodLens**

Blood effects on the screen when hurt.

* **Bloom**

Increases brightness of lights and light blurriness.

* **Cinema**

Grain and film effects

* **Coloring**

Color fine tuning.

* **Depth of Field**

Dynamic depth of field based on distance.

* **Godrays**

Sun beam effects.

* **LowHF**

Screen and sound effects during low health/fatigue.

* **MotionBlur**

Motion blur during camera movements.

* **POM Shaders**

Parallax occlusion mapping to add bump effect to surfaces.

* **Rain**

Precipitation shader that replaces vanilla rain effect.

* **Shadows (for exteriors and interiors)**

Post process and forward shadows in exteriors during the day, and support to up to four light sources in interiors.

* **Sharpening**

Increases detail contrast.

* **SMAA**

Anti Aliasing.

* **Snow/Snow accumulation**

Snow precipitation, and white blanket effect on the surfaces.

* **Watersurface/Underwater**

Overhaul of the look of the water surfaces/lighting under water, caustics.

* **Volumetric Fog**

Exponential fog which adds up with depth.

* **WaterLens** 

Droplets appear on the screen went getting in and out of water

* **WetWorld**

Water puddles appear during rainy weather.


----
## Configuration

To activate/Deactivate each effect, press O in game to bring up the menu. Navigate the menu with the arrow keys, and activate/deactivate effects and increase/decrease effect values with the numpad +/- keys.

The configuration is stored in the `.dll.config` file and can be edited directly with a text editor.

----
## Building from source
To build, with Visual Studio 2019 (Community Edition) with Desktop Development librairies, Windows SDK and DirectX9 SDK installed, run the `build.bat` file in command line, with the following command:

```bat
build.bat "ProjectName" "C:/DeployFolder/"
```

 * `"Project Name"` can be either `OblivionReloaded` or `NewVegasReloaded`. 
 * The second argument is optional, and can be used to copy the built library to the game folder or (preferably) to a mod folder managed by [Mod Organizer 2](https://vivanewvegas.github.io/mo2.html). Otherwise, the built files can be found in the `/build/` folder at the root, to be copied manually.

----
## Installation

First Make sure that xOBSE/xNVSE is installed.

The files from the built folder must be then copied into the game Data folder.

To use a mod manager, create a zip with the contents of the `/build/` folder and drag & drop it into the mod list.

It can be helpful to create a separate mod with only the `.config` file to try different settings.

----
## Troubleshooting

If the mod loaded properly, a message will appear at the bottom of the title screen with the version number. If not, try reinstalling directX or the directX SDK.

### TESReloaded is not compatible with the following mods:
* **ENB**

If you want extra control over the look of your game, use Reshade which is compatible.

* **Improved Lighting Shaders**

Problem: Big areas covered in broken shaders results in bright blue surfaces. 

Solution: Remove the TESReloaded Shaders with "SLS" in the name, as they are the source of the conflict. Only post process shadows will be working.

* **Enhanced Camera**

Problem: Crash when loading a game.

Solution: Disable "First Person Shadow" setting in Enhanced Camera .ini. 

----
## License
The project uses the GNU public license.

The redistribution and use of the binaries, with or without modification, are permitted and publishing binaries is allowed, but the following conditions MUST be met:
 - the current license MUST be included in the redistribution of the binaries and it cannot be modified
 - the distributed binaries MUST report the word "UNOFFICIAL" (or a branch name) in the product description
 - the distributer MUST state that the official channels cannot be used for unofficial versions.
 - the source MUST be provided (included or separated)


----
## Contributing

If you want to contribute, create a fork of the project, and [join the discord](https://discord.com/invite/QgN6mR6eTK) to discuss possible developments.
