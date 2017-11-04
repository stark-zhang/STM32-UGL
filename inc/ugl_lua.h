/**
 * Title	UGL Module Lua Support User Header files(SoftWare Modules)
 * Author	Stark Zhang
 * Date		2017-10-03
 * Debug	None
**/

/* This is Lua Low Layer Support Functions, with a DIY LuaRT */
/* Lua File IO is depend on File System, Here is FatFS */

#ifndef __UGL_LUA_H
#define __UGL_LUA_H

#include "ugl.h"

#if (__Lua_Support == 1)

/**
 * FatFS support in STM32 HAL
**/
//#include "ff.h"

//#include "time.h"
/**
 * Lua JIT Header Files
**/
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"

/**
 * Type Re-define
**/
typedef int FILEHANDLE;

//DIY LuaRT

//Low Layer Functions
//extern void _sys_exit(int status);
//extern FILEHANDLE _sys_open(const char *name, int openmode);
//extern int _sys_close(FILEHANDLE fh);
//extern int _sys_write(FILEHANDLE fh, const unsigned char *buf, unsigned len, int mode);
//extern int _sys_read(FILEHANDLE fh, unsigned char*buf, unsigned len, int mode);
//extern int fgetc(FILE *stream);
//extern int _sys_seek(FILEHANDLE fh, long pos);
//extern int _sys_istty(FILEHANDLE fh);
//extern int _sys_ensure(FILEHANDLE fh);
//extern int _sys_flen(FILEHANDLE fh);
//extern int _sys_tmpnam(char *name, int fileno, unsigned maxlength);
//extern void _ttywrch(int ch);
//extern time_t time(time_t *t);
//extern int remove(const char *filename);
//extern char *_sys_command_string(char *cmd, int len);
//extern clock_t clock(void);
//extern int system(const char* a);
//extern int rename(const char *a, const char *b);

#endif /*__Lua_Support*/

#endif /*__UGL_LUA_H*/

//EOF
