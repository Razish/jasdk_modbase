#pragma once

#ifdef _WIN32
	#define __asm1__( a )			__asm a
	#define __asm2__( a, b )		__asm a, b
	#define __asmL__( a )			__asm a
#else
	#define __asm1__i( a )			__asm__( #a "\n" );
	#define __asm2__i( a, b )		__asm__( #a ", " #b "\n" );
		// proxy defines
		#define __asm1__( a )		__asm1__i( a )
		#define __asm2__( a, b )	__asm2__i( a, b )
	#define __asmL__( a )			__asm__( #a "\n" );
#endif

#define BREAK __asm1__( int 3 )

