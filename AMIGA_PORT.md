Jump 'n Bump for AmigaOS 3.x
============================

A port of Jump 'n Bump (https://gitlab.com/LibreGames/jumpnbump, the SDL 2
version, release 1.70 at commit 2475c443569d9e21ff553f17004cdea44ab6a76f,
GPL-2.0 or later), the bunny-stomping platform game for up to four players
on one keyboard, for AmigaOS 3.2 on a 68040 or 68060 with an FPU and an RTG
screen, on OpenGPU's SDL 2.

Status: builds and links; not yet run on an Amiga.


What you need
-------------

- A 68040 or 68060 with an FPU (not an LC040 or EC040), AmigaOS 3.2, an RTG
  card (or the AmigaChrome lab).
- OpenGPU 0.6 or later: opengpu.library, LIBS:OpenGPU/SDL2.module and
  LIBS:OpenGPU/SDL2_mixer.module (installed by OpenUp).
- About 600 KB of disk.


How to play
-----------

Double-click JumpnBump in its drawer, or from a Shell:

    cd JumpnBump
    JumpnBump [-fullscreen] [-scaleup] [-nosound] [-musicnosound] [-nogore] [-nojoy]

In the menu every player who wants to play jumps over the tree trunk and
walks right into the arena. Keys (positions as on a QWERTY keyboard):

- Dot: A, W, D
- Jiffy: cursor left, up, right
- Fizz: J, I, L
- Mijji: 4, 8, 6 on the numeric pad
- 1, 2, 3, 4: hand that bunny to the computer (a bot) or take it back
- F10: window / full screen; Esc: end the game; F12: quit

The window is 400x256 (the game's own size); -scaleup draws it at 800x512
with the game's Scale2x filter. -fullscreen opens a screen of the game's
own size rather than the Workbench's.

Extra levels from Brainchild Design's site run with `-dat <level.dat>`;
none come with this drawer (they are not in the upstream repository).



Standard keys
-------------

Every AmiCradle game has the same keys on Right Amiga (GFOpenUp's
SDL2.module, after 0.8.26):

- Right Amiga + F: window or full screen, remembered for next time
- Right Amiga + P: pause (Right Amiga + P again goes on)
- Right Amiga + Q: quit
- Right Amiga + M: free the mouse pointer, or let the game take it again
- Right Amiga + S: a screenshot in the drawer's Screenshots
- Help: this game's keys (the drawer's Controls file)
- Right Amiga + F1, F2: F11, F12; Right Amiga + cursor keys: Page Up,
  Page Down, Home, End

The FULLSCREEN tooltype on the game's icon (take the brackets off) starts
it full screen.


Building
--------

GFOpenAmigaGCC 16.2.0-open4 or later, the OpenGPU developer kit and a C
compiler for the build machine (for upstream's gobpack and jnbpack, which
pack data/ into jumpbump.dat):

    make -f amiga/Makefile.amigaos -j2 dist \
         STOVE=/path/to/openamigagcc-16.2.0-open4 \
         NDK=/path/to/OpenNDK/Include_H SDL2KIT=/path/to/opengpu-sdk

The defaults are CradleLab's paths. Output: build/amigaos/JumpnBump and
build/amigaos/jumpbump.dat; 'dist' makes dist/JumpnBump/ (JumpnBump,
jumpbump.dat, ReadMe, README-jumpnbump, COPYING.txt, AUTHORS, with
GlowIcons) and dist/JumpnBump.info. The icons are made from
amiga/icons/icons.json (see "about" there).


What was changed
----------------

- amiga/Makefile.amigaos: upstream's source list and defines without
  USE_NET, ZLIB_SUPPORT and BZLIB_SUPPORT; links the kit's libSDL2_mixer.a
  and libSDL2.a. The data is packed exactly as data/Makefile does.
- amiga/stack.c: 128 KB of stack and a $VER string.
- amiga/amiga_screens.c (from the Seven Kingdoms port): SDL2.module 0.6
  leaves empty "SDL" screens after a full-screen window; after SDL_Quit()
  they are closed, or sent behind the Workbench.
- sdl/gfx.c: an atexit() handler calls SDL_Quit() and then closes those
  screens (the game often exit()s without SDL_Quit(), and -nosound skips
  it). The picture is 8-bit with a palette, converted each frame into one
  32-bit XRGB surface kept for the run (OpenGPU's SDL 2 reports a 24-bit
  window; the texture is asked for as SDL_PIXELFORMAT_RGB888 explicitly).
  Full screen is SDL_WINDOW_FULLSCREEN, not _DESKTOP.
- globals.h: the data file is PROGDIR:jumpbump.dat.
- sdl/sound.c: mixing at 22050 Hz instead of 44100 (the game mixes its own
  effects on the 68040 in SDL_mixer's post-mix callback); the MOD music is
  read from memory with Mix_LoadMUS_RW (upstream writes a /tmp file), with
  T:jumpnbump.mod as a fallback; no MUSIC_CMD.
- network.h: two prototypes the local game needs moved out of USE_NET
  (upstream's build without network did not compile).
- main.c: write_calib_data() (joystick calibration) read the .dat's
  directory as native ints; it reads it as little-endian now.

Big-endian: the .dat directory, the GOB sprite headers, the 16-bit SMP
samples and calib.dat were already read byte by byte as little-endian by
upstream; PCX pictures and levelmap.txt are bytes and text. Only the
calibration writer above needed a fix.


Cut
---

- Network play (no SDL_net; -server and -connect are not recognised).
- gzip/bzip2-compressed .dat files.
- The GTK level-chooser (menu/, Python) and the PC icons.


What a tester should check first
--------------------------------

1. It starts in a window with the menu picture in the right colours (the
   8-bit to 32-bit conversion) and the menu music plays (MOD through
   SDL2_mixer.module, from memory: watch the Shell for "Couldn't load
   music").
2. Two players on the keyboard, and 1-4 to hand bunnies to the bots: jump
   sounds, splash, death sounds clean (the samples' byte order).
3. The frame rate at 400x256, then with -scaleup.
4. F10 and -fullscreen; then quitting with F12 and Esc leaves no grey
   screen in front of the Workbench.
5. -nosound starts and quits cleanly too.


Licence
-------

The game and its data (graphics, sounds, music and the level in data/,
from Brainchild Design's source release) are under the GNU GPL, version 2
or later (COPYING.txt in the drawer; credits in AUTHORS). The port's own
files are under the same licence.
