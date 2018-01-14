# setbackground

setbackground is a simple, cross-platform static library that lets you change
the desktop background (wallpaper). It follows the UNIX philosophy of doing one
thing and doing it well.

## Supported platforms

-   Windows
    -   Supports Windows XP and above
    -   Tested on Windows XP, Windows 7 and Windows 10
-   Linux
    -   Supported desktop environments:
        -   KDE (KDE Plasma 5.9 and above)
        -   Gnome (tested with Ubuntu 16.04)
        -   MATE (tested with version 1.16)
        -   Cinnamon (tested with version 2.8)
        -   LXDE (tested with Lubuntu 16.04)
        -   XFCE (tested with Xubuntu 16.04)
        -   Deepin (tested with Deepin 15.5)
-   MacOS
    -   Based on [macos-wallpaper](https://github.com/sindresorhus/macos-wallpaper)
    -   Tested on 10.12 (Sierra), should work on >=10.6

## Building

setbackground uses [CMake](https://cmake.org/). To build it, run the following
commands:

```
cmake .
make
```

This will build the library in the lib folder and a small CLI test tool in the
bin folder.

### Linux

setbackground requires GLIB2, DBUS, DCONF and XFCONF to build. On Debian based
distros, run the following command to install all dependencies:

```bash
sudo apt-get install build-essential cmake libgtk2.0-dev libxfconf-0-dev libdbus-1-dev libdconf-dev
```

Then, navigate to the folder and run:

```bash
cmake .
make
```

### Windows

The easiest way to build is to use MinGW.

Download and install both [MinGW-w64](https://mingw-w64.org/doku.php/download/mingw-builds)
and [CMake](https://cmake.org/download/).

Then, open a Command Prompt and run the following two commands:

```bash
cmake -G "MinGW Makefiles" .
cmake --build .
```

### MacOS X

Make sure XCode Command Line Tools is installed:

```bash
xcode-select --install
```

Install CMake. If you're using [Homebrew](https://brew.sh/):

```bash
brew install cmake
```

Then, navigate to the folder and run:

```bash
cmake .
make
```

## API

The library exposes only a single function:

```C
int set_background(const char* path);
```

The path is expected to be UTF8-encoded and it's recommended to always use
absolute paths, though relative paths are supported.

On success, the desktop background is changed to the given image, style is set
to "center" (if possible) and the function returns 0.

On failure, one of the error codes defined in errors.h is returned.

## FAQ

### Why only set\_background? Why not get\_background as well?

It turned out to be prohibitively difficult to get the current background on
all the supported platforms in a reliable way. Most notably, the signature of
that function would neccessarily be complicated, as different screens can have
different background images.

### What happens if I have multiple screens?

A call to `set_background` will change the background on all the connected
screens, if supported by your platform.

### Why UTF-8? Windows uses UTF-16.

[UTF-8 Everywhere](http://utf8everywhere.org/) has some good arguments. In
general, UTF-8 is the de-facto default on platforms other than Windows and
using a different encoding depending on the platform is a recipe for disaster.

### Why C?

Mostly for portability - C is reasonably easy to use from other languages, so
the library can be used from e.g. Go with minimal effort this way.

## Platform caveats

-   Windows XP only supports BMP images.
-   Deepin doesn't support changing the style (image will always be stretched).
