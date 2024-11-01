# nds-badge
This is the code for the NDS badge I wore to Furry Migration 2024.
It's not really extensible, but I thought it would be a good guide for others to make their own NDS badges.

Makefile mostly copied from the Devkitpro template.

## Dependencies
Devkitpro needs to be installed: https://devkitpro.org/wiki/Getting_Started
Arch: `sudo pacman -S nds-dev`
Desmume is a submodule

## How to build
Run `make desmume`
Run `make run`

## Debug
Run make debug, then run target remote localhost:20000 in gdb to debug

## How to use
Select - Open the menu
A - Select item in menu
Y - Save
### NOTE: Saving does not work in the emulator! You have to use an actual flash cart on an actual DS to save images

## Acknowledgements
Huge thanks to the Devkitpro team! Their examples were very helpful.