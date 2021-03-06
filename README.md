<h1 align="center">
  <br>
  <img src="./images/qicon.svg" alt="QuickKey logo" style="vertical-align:middle" title="QuickKey" height="160" />
  <br>
  QuickKey
  <br>
  
  ![GitHub all releases](https://img.shields.io/github/downloads/leokraft/QuickKey/total?color=green)
  ![GitHub](https://img.shields.io/github/license/leokraft/QuickKey?color=green)
  
</h1>

<h4 align="center">A small Windows application to quickly find special characters and copy them to your clipboard in an instant, without disturbing your workflow.</h4>

## Usage

![usage](./images/usage.gif)

When in need of a special character while writing

1. Press the _QuickKey_-Hotkey to open up a search window. (default: `Ctrl Y`)
2. Type a description of you desired character like **integral** for **∫**.
   > While typing you will see characters whos tags match your typed words.
   > Seperate tags with a space.
3. As soon as you see your desired character click it to copy it to your clipboard or, if in first position, just press **Enter** to copy.

Alternatly you may browse all charcters, search for specific topics or just type the character-code to find you character.

## Install

> There are two ways to install _QuickKey_.\
> Either install it using the provided installer or build it on your own.

### Installer

Download the latest release from [here](https://github.com/leokraft/QuickKey/releases).\
Run the installer and follow the instructions.

### Build

**Prerequisites:**

1. Compiler (e.g. [MinGW](https://mingw-w64.org/doku.php/download))
2. [Qt 6.1 or newer](https://www.qt.io/download-qt-installer) prebuild files for your compiler
3. [Wix toolset](https://wixtoolset.org/releases/) to compile the installer

> Make sure you have the respective `bin/` folders added to your PATH.

Clone the repository, and run `qmake quickkey.pro` to create your own Makefile.\
To build run `make` or `mingw32-make`, depending on your installed compiler.\
Afterwards run the produced `QuickKey`-binary inside the `release/` folder.

## Configuration

A selection of configuration options

- light/darkmode
- hotkey to open _QuickKey_ search window
- Automatic paste

Settings can be accessed by right-clicking the _QuickKey_ tray icon and selecting _Settings_.

### Acknowledgement

This application is written using the **Qt 6.1.1** Open Source version under the GPLv3 License.
