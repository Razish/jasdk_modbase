#include <CoreFoundation/CoreFoundation.h>
#include "MacVersions.h"
#include "q_engine.h"
#include "q_shared.h"

int whichMacVersion()
{
	CFBundleRef mainBundle;
	CFStringRef mainBundleExecutableName, mainBundleVersion, mainBundleIcons;
	
	CFComparisonResult result;
	
	mainBundle = CFBundleGetMainBundle();
    if(!mainBundle){
        Com_Printf("Mac Version Check Error: No Main Bundle\n");
        return VERSION_ERR;
    }
    
	mainBundleExecutableName = CFBundleGetValueForInfoDictionaryKey(mainBundle, kCFBundleExecutableKey);
    if (!mainBundleExecutableName){
        Com_Printf("Mac Version Check Error: No Main Executable Name\n");
        return VERSION_ERR;
    }
    
	mainBundleVersion = CFBundleGetValueForInfoDictionaryKey(mainBundle, kCFBundleVersionKey);
    if (!mainBundleVersion){
        Com_Printf("Mac Version Check Error: No Bundle Version\n");
        return VERSION_ERR;
    }
    
    mainBundleIcons = CFBundleGetValueForInfoDictionaryKey(mainBundle, ICONS_DICTIONARY_KEY);
    if (!mainBundleIcons){
        Com_Printf("Mac Version Check Error: No Icons File\n");
        return VERSION_ERR;
    }
	
	result = CFStringCompareWithOptions(STD_VERSION_STRING, mainBundleVersion, CFRangeMake(0,CFStringGetLength(STD_VERSION_STRING)), kCFCompareEqualTo);
	
	if (result != kCFCompareEqualTo) {
        result = CFStringCompareWithOptions(APPSTORE_VERSION_STRING_LONG, mainBundleVersion, CFRangeMake(0,CFStringGetLength(APPSTORE_VERSION_STRING_LONG)), kCFCompareEqualTo);
        if (result != kCFCompareEqualTo) {
            Com_Printf("Mac Version Check Error: Unknown Version\n");
            return VERSION_ERR;//wrong version and not app store!
        }
        return VERSION_101_APPSTORE;//app store version!
	}
    
    result = CFStringCompareWithOptions(STEAM_ICONS_FILE, mainBundleIcons, CFRangeMake(0,CFStringGetLength(STEAM_ICONS_FILE)), kCFCompareEqualTo);
    
    if (result == kCFCompareEqualTo) {
        return VERSION_101E_STEAM;//steam version!
    }

	result = CFStringCompareWithOptions(DIG_DL_EX_STRING, mainBundleExecutableName, CFRangeMake(0,CFStringGetLength(DIG_DL_EX_STRING)), kCFCompareEqualTo);
	
	if (result == kCFCompareEqualTo) {
        return VERSION_101E_DIGDL;//digital download version
    } else {
        return VERSION_101E_DISC;//disc version
    }
    
    //TODO: handle VERSION_101E_GOLD (no idea how to detect it, as don't have a copy)
}

void patchMacPk3Checks(int macVersion)
{
    int patchLocation;
    
    switch (macVersion) {
        case VERSION_101_APPSTORE:
            patchLocation = 0x3d773;
            break;
        case VERSION_101E_STEAM:
            patchLocation = 0x3d7b3;
            break;
        default:
            return;
    }
    
    Com_Printf("Patching Mac .pk3 checks...\n");
    UnlockMemory(patchLocation,2);
    *(char *)patchLocation = 0x90;
    *(char *)(patchLocation+1) = 0x90;
    LockMemory(patchLocation,2);
    Com_Printf("...DONE\n");
}