Fish Sky Sea
==========

A retro-style fishing game.


![2025-08-24 21 47 34](https://github.com/user-attachments/assets/8db3ba43-d17d-471f-8418-be5ec208baa5)
Solitaire Mode

Platforms
=========

Linux and macOS

Building
========

Install SDL2, SDL2_image, SDL2_mixer, SDL2_net

Run make

Controls
========
W reel in

S let out line

A shorten pole

D lengthen pole

E set hook on a nibbling fish / pole action

Q special move (when available)


You can also send out a glimmer to attract fish with a timed release of <E>

You can reel in faster by repeatedly tapping <E> while holding <W>

Modes
=====

Solitaire

AI

2 player keyboard

2 player LAN


See config.txt

Config.txt
==========

Configure window/fullscreen, gpu/software rendering, modes, LAN, gameplay.


If no config.txt is present than the game will produce its backup/default in the working directory.

Resources
=========

FYI The art and music are in the source code. The art is XPM data as C89 cstrings. The music is binary data. All in the bss.


The upside is that if you choose to build statically there is only two build artifacts, the config and the binary!
