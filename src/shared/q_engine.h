#pragma once

// Cross-platform (Linux & Windows) Asm defines

#if defined(_WIN32) && !defined(MINGW32)

	#define __asm1__( a )		__asm a
	#define __asm2__( a, b )	__asm a, b
	#define __asmL__( a )		__asm a

	#define __StartHook( a )	__asm lea eax, [__hookstart] \
								__asm jmp __hookend \
								__asm __hookstart:
	#define __EndHook( a )		__asm __hookend:

#elif MAC_PORT
//In order to use intel syntax need "Codewarrior-style inline assembly" enabled

// Linux has a few issues with defines in function defines
// So we'll create a double define to ensure the defines are properly processed
#define __asm1__i( a )		__asm{ a }
#define __asm2__i( a, b )	__asm{ a, b }
// proxy defines
#define __asm1__( a )           __asm1__i( a )
#define __asm2__( a, b )        __asm2__i( a, b )

#define __asmL__( a )      	__asm__( #a "\n" );

//Want to generate position independent code hence some extra messing around
//Only to avoid needing -read_only_relocs suppress; not sure if really necessary...
#define __StartHook( a )	__asm__ ( "call __hookoffset" #a "\n" ); \
							__asm__ ( "__hookoffset" #a ":\n" ); \
							__asm__ ( "pop %eax\n" ); \
							__asm__ ( "addl $__hookstart" #a "-__hookoffset" #a ", %eax\n" ); \
							__asm__ ("jmp __hookend" #a "\n"); \
							__asm__ ("__hookstart" #a ":\n");

#define __EndHook( a )		__asm__("__hookend" #a " :\n");

#else

// Linux has a few issues with defines in function defines
// So we'll create a double define to ensure the defines are properly processed
	#define __asm1__i( a )		__asm__( #a "\n" );
	#define __asm2__i( a, b )	__asm__( #a ", " #b "\n" );
        // proxy defines
        #define __asm1__( a )           __asm1__i( a )
        #define __asm2__( a, b )        __asm2__i( a, b )

	#define __asmL__( a )      	__asm__( #a "\n" );

	#define __StartHook( a )	__asm__( ".intel_syntax noprefix\n" ); \
								__asm__("lea eax, [__hookstart" #a "]\n"); \
								__asm__("jmp __hookend" #a "\n"); \
								__asm__(".att_syntax\n"); \
								__asm__("__hookstart" #a ":\n"); \
								__asm__(".intel_syntax noprefix\n");

	#define __EndHook( a )		__asm__(".att_syntax\n"); \
								__asm__("__hookend" #a ":\n"); \
								__asm__(".intel_syntax noprefix\n");

#endif


typedef struct netadr_s {
	int				type;
	byte			ip[4];
	byte			ipx[10];
	unsigned short	port;
} netadr_t;

// Common engine modification data and functions

typedef struct hookEntry_s
{
	const unsigned int	hookPosition;	//	The code we're patching
	unsigned char		origBytes[5];	//	What it originally was
	unsigned char		hookOpcode;		//	CALL or JMP
	const unsigned int	hookForward;	//	Function to direct the control flow into
	const char			*name;			//	Long name of the hook
} hookEntry_t;

typedef struct cvarEntry_s
{
	const char		*cvarname;
	unsigned int	flags;
} cvarEntry_t;

typedef enum engineDisable_e
{
	ENGINE_DISABLE_NONE=0,
	ENGINE_DISABLE_UI_CVAR,
	ENGINE_DISABLE_UI_HOOKS,
	ENGINE_DISABLE_UI_COMMANDS,
	ENGINE_DISABLE_UI_PATCHES,
	ENGINE_DISABLE_CGAME_HOOKS,
	ENGINE_DISABLE_CGAME_BUTTONS,
	ENGINE_DISABLE_CGAME_PATCHES,
} engineDisable_t;

#if defined(__GCC__) || defined(MINGW32) || MAC_PORT
	#define USED __attribute__((used))
	#define NORET __attribute__((noreturn))
#else //defined(__GCC__) || defined(MINGW32)
	#define USED
	#define NORET
#endif //defined(__GCC__) || defined(MINGW32)

#define HOOKDEF( pos, origBytes, opcode, fwd, name ) { \
	pos, origBytes, opcode, (unsigned int)fwd, name \
}

#define HOOK( name ) void NORET *Hook_##name( void )

#define EFUNC( type, name, args, address ) type USED (*ENG_##name) args = (type (*)args)address

#define CVAR_UNLOCK( cvarname, cvarflags ) { \
	ENG_Cvar_FindVar( cvarname )->flags = cvarflags; \
}

#define CMD_REROUTE( old, new, from, to ) { \
	ENG_Cmd_RemoveCommand( old ); \
	ENG_Cmd_AddCommand( new, (void (*)())to ); \
}

#define PATCH( address, type, to ) { \
	UnlockMemory( address, 1 ); \
	*(type *)address = (type)to; \
	LockMemory( address, 1 ); \
}

// Helper functions
qboolean UnlockMemory( int address, int size );
qboolean LockMemory( int address, int size );
#ifdef PATCH_ENGINE
	void PlaceHook( hookEntry_t *hook );
	void RemoveHook( const hookEntry_t *hook );
#endif

//API
void PatchEngine( void );
void UnpatchEngine( void );
