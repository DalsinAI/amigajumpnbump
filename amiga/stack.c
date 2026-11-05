/* A Shell gives 4 KB of stack; libnix's startup sets this much up instead.
 * The AmiCradle Team. GPL 2 or later, like Jump 'n Bump. */
unsigned long __stack = 128 * 1024;
static const char version[] __attribute__((used)) = "$VER: JumpnBump 1.70 Amiga (05.11.2026)";
