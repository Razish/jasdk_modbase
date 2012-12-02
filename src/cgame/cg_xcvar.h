
#ifdef XCVAR_PROTO
	#define XCVAR_DEF( name, defVal, flags ) extern vmCvar_t name;
#endif

#ifdef XCVAR_DECL
	#define XCVAR_DEF( name, defVal, flags ) vmCvar_t name;
#endif

#ifdef XCVAR_LIST
	#define XCVAR_DEF( name, defVal, flags ) { & name , #name , defVal , flags },
#endif

		// name						default value	cvar flags
XCVAR_DEF( cg_smoothCamera,			"0",			CVAR_ARCHIVE )

#undef XCVAR_DEF
