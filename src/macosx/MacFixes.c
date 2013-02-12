#include <CoreFoundation/CoreFoundation.h>
#include "MacVersions.h"

int whichMacVersion()
{
	CFBundleRef mainBundle;
	CFStringRef mainBundleExecutableName, mainBundleVersion, mainBundleIcons;
	
	CFComparisonResult result;
	
	mainBundle = CFBundleGetMainBundle();
	mainBundleExecutableName = CFBundleGetValueForInfoDictionaryKey(mainBundle, kCFBundleExecutableKey);
	mainBundleVersion = CFBundleGetValueForInfoDictionaryKey(mainBundle, kCFBundleVersionKey);
    mainBundleIcons = CFBundleGetValueForInfoDictionaryKey(mainBundle, ICONS_DICTIONARY_KEY);
	
	result = CFStringCompareWithOptions(VERSION_STRING, mainBundleVersion, CFRangeMake(0,CFStringGetLength(VERSION_STRING)), kCFCompareEqualTo);
	
	if (result != kCFCompareEqualTo) {
        result = CFStringCompareWithOptions(APPSTORE_VERSION_STRING_LONG, mainBundleVersion, CFRangeMake(0,CFStringGetLength(APPSTORE_VERSION_STRING_LONG)), kCFCompareEqualTo);
        if (result != kCFCompareEqualTo) {
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