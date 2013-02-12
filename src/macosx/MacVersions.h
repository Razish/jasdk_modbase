#define DIG_DL_EX_STRING CFSTR("Jedi Academy MP (NoCD)")//Old Digital Download Executable file
#define EX_STRING CFSTR("Jedi Academy MP")//Others Executable file

#define VERSION_STRING CFSTR("1.0.3e")//Bundle version and Bundle versions string, short (for all but app store version)
#define APPSTORE_VERSION_STRING CFSTR("1.01")//Bundle versions string, short (app store)
#define APPSTORE_VERSION_STRING_LONG CFSTR("109339")//Bundle version (app store)

#define STEAM_ICONS_FILE CFSTR("AppIcon")//Icon file for steam
#define APPSTORE_ICONS_FILE CFSTR("AppIcon.icns")//Icon file for app store
#define ICONS_FILE CFSTR("Icon_MP")//Icon file for rest

#define ICONS_DICTIONARY_KEY CFSTR("Icon file")

#define BUILD_NUMBER 9467//AspyrBuildNumber for all but app store (when missing)

enum {
    VERSION_ERR = -1,
    VERSION_UNKNOWN,
    VERSION_101E_DISC,
    VERSION_101E_DIGDL,
    VERSION_101E_GOLD,
    VERSION_101E_STEAM,
    VERSION_101_APPSTORE
};

extern int whichMacVersion();