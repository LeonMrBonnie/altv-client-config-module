# alt:V Config Module

## What is this

This is a module allowing it to create simple alt:V resources using `.cfg` files.<br>
It can be used both on clientside and on serverside.<br>
These files use the same format as the `resource.cfg`, `server.cfg` etc.<br>
This module is *not* meant for complex resources, and is meant to quickly and easily create resources.<br>
Even though this module is really simple, it *should be* very fast, as the whole code is parsed to C++ code from the config file.

## How to build

Make sure to fetch the submodules and then run `build-client.bat` or `build-server.bat` (on Unix systems: `build-server.sh`). This will compile the project and copy the created `.dll` or `.so` into the `dist/client` or `dist/server` directory.

## How to contribute

You can contribute to the module by making a pull request. Before submitting your pull request, make sure you have tested the changes,
meaning you successfully compiled the project and tested the changes in alt:V.<br>
If you want to make a big change to the module please discuss the change with me before working on it, as I might close any pull request I don't find helpful.

## How to use

WIP
