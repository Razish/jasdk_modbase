
#ifdef XCVAR_PROTO
	#define XCVAR_DEF( name, defVal, flags, notify ) extern vmCvar_t name;
#endif

#ifdef XCVAR_DECL
	#define XCVAR_DEF( name, defVal, flags, notify ) vmCvar_t name;
#endif

#ifdef XCVAR_LIST
	#define XCVAR_DEF( name, defVal, flags, notify ) { & name , #name , defVal , flags, 0, notify },
#endif

		// name						default value	cvar flags		notify
XCVAR_DEF( g_randFix,				"1",			CVAR_ARCHIVE,	qtrue )
XCVAR_DEF( g_engineModifications,	"1",			CVAR_ARCHIVE,	qfalse )
XCVAR_DEF( g_antiFakePlayer,		"1",			CVAR_ARCHIVE,	qfalse )
XCVAR_DEF( g_maxConnPerIP,			"3",			CVAR_ARCHIVE,	qfalse )
XCVAR_DEF( g_securityLog,			"1",			CVAR_ARCHIVE,	qfalse )
XCVAR_DEF( g_userinfoValidate,		"-1",			CVAR_ARCHIVE,	qfalse )
XCVAR_DEF( g_charRestrictRGB,		"1",			CVAR_ARCHIVE,	qfalse )

#undef XCVAR_DEF
