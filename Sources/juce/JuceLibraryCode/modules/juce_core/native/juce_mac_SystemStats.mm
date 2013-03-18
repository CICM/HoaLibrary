/*
  ==============================================================================

   This file is part of the JUCE library - "Jules' Utility Class Extensions"
   Copyright 2004-11 by Raw Material Software Ltd.

  ------------------------------------------------------------------------------

   JUCE can be redistributed and/or modified under the terms of the GNU General
   Public License (Version 2), as published by the Free Software Foundation.
   A copy of the license is included in the JUCE distribution, or can be found
   online at www.gnu.org/licenses.

   JUCE is distributed in the hope that it will be useful, but WITHOUT ANY
   WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
   A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

  ------------------------------------------------------------------------------

   To release a closed-source product which uses JUCE, commercial licenses are
   available: visit www.rawmaterialsoftware.com/juce for more information.

  ==============================================================================
*/

ScopedAutoReleasePool::ScopedAutoReleasePool()
{
    pool = [[NSAutoreleasePool alloc] init];
}

ScopedAutoReleasePool::~ScopedAutoReleasePool()
{
    [((NSAutoreleasePool*) pool) release];
}

//==============================================================================
void Logger::outputDebugString (const String& text)
{
    std::cerr << text << std::endl;
}

//==============================================================================
namespace SystemStatsHelpers
{
   #if JUCE_INTEL && ! JUCE_NO_INLINE_ASM
    static void doCPUID (uint32& a, uint32& b, uint32& c, uint32& d, uint32 type)
    {
        uint32 la = a, lb = b, lc = c, ld = d;

        asm ("mov %%ebx, %%esi \n\t"
             "cpuid \n\t"
             "xchg %%esi, %%ebx"
               : "=a" (la), "=S" (lb), "=c" (lc), "=d" (ld) : "a" (type)
           #if JUCE_64BIT
                  , "b" (lb), "c" (lc), "d" (ld)
           #endif
        );

        a = la; b = lb; c = lc; d = ld;
    }
   #endif
}

//==============================================================================
SystemStats::CPUFlags::CPUFlags()
{
   #if JUCE_INTEL && ! JUCE_NO_INLINE_ASM
    uint32 familyModel = 0, extFeatures = 0, features = 0, dummy = 0;
    SystemStatsHelpers::doCPUID (familyModel, extFeatures, dummy, features, 1);

    hasMMX   = (features    & (1u << 23)) != 0;
    hasSSE   = (features    & (1u << 25)) != 0;
    hasSSE2  = (features    & (1u << 26)) != 0;
    has3DNow = (extFeatures & (1u << 31)) != 0;
   #else
    hasMMX = false;
    hasSSE = false;
    hasSSE2 = false;
    has3DNow = false;
   #endif

   #if JUCE_IOS || (MAC_OS_X_VERSION_MIN_REQUIRED >= MAC_OS_X_VERSION_10_5)
    numCpus = (int) [[NSProcessInfo processInfo] activeProcessorCount];
   #else
    numCpus = (int) MPProcessors();
   #endif
}

#if JUCE_MAC
struct RLimitInitialiser
{
    RLimitInitialiser()
    {
        rlimit lim;
        getrlimit (RLIMIT_NOFILE, &lim);
        lim.rlim_cur = lim.rlim_max = RLIM_INFINITY;
        setrlimit (RLIMIT_NOFILE, &lim);
    }
};

static RLimitInitialiser rLimitInitialiser;
#endif

//==============================================================================
#if ! JUCE_IOS
static String getOSXVersion()
{
    JUCE_AUTORELEASEPOOL
    NSDictionary* dict = [NSDictionary dictionaryWithContentsOfFile:
                                nsStringLiteral ("/System/Library/CoreServices/SystemVersion.plist")];

    return nsStringToJuce ([dict objectForKey: nsStringLiteral ("ProductVersion")]);
}
#endif

SystemStats::OperatingSystemType SystemStats::getOperatingSystemType()
{
   #if JUCE_IOS
    return iOS;
   #else
    StringArray parts;
    parts.addTokens (getOSXVersion(), ".", String::empty);

    jassert (parts[0].getIntValue() == 10);
    const int major = parts[1].getIntValue();
    jassert (major > 2);

    return (OperatingSystemType) (major + MacOSX_10_4 - 4);
   #endif
}

String SystemStats::getOperatingSystemName()
{
   #if JUCE_IOS
    return "iOS " + nsStringToJuce ([[UIDevice currentDevice] systemVersion]);
   #else
    return "Mac OSX " + getOSXVersion();
   #endif
}

bool SystemStats::isOperatingSystem64Bit()
{
   #if JUCE_IOS
    return false;
   #elif JUCE_64BIT
    return true;
   #else
    return getOperatingSystemType() >= MacOSX_10_6;
   #endif
}

int SystemStats::getMemorySizeInMegabytes()
{
    uint64 mem = 0;
    size_t memSize = sizeof (mem);
    int mib[] = { CTL_HW, HW_MEMSIZE };
    sysctl (mib, 2, &mem, &memSize, 0, 0);
    return (int) (mem / (1024 * 1024));
}

String SystemStats::getCpuVendor()
{
   #if JUCE_INTEL && ! JUCE_NO_INLINE_ASM
    uint32 dummy = 0;
    uint32 vendor[4] = { 0 };

    SystemStatsHelpers::doCPUID (dummy, vendor[0], vendor[2], vendor[1], 0);

    return String (reinterpret_cast <const char*> (vendor), 12);
   #else
    return String::empty;
   #endif
}

int SystemStats::getCpuSpeedInMegaherz()
{
    uint64 speedHz = 0;
    size_t speedSize = sizeof (speedHz);
    int mib[] = { CTL_HW, HW_CPU_FREQ };
    sysctl (mib, 2, &speedHz, &speedSize, 0, 0);

   #if JUCE_BIG_ENDIAN
    if (speedSize == 4)
        speedHz >>= 32;
   #endif

    return (int) (speedHz / 1000000);
}

//==============================================================================
String SystemStats::getLogonName()
{
    return nsStringToJuce (NSUserName());
}

String SystemStats::getFullUserName()
{
    return nsStringToJuce (NSFullUserName());
}

String SystemStats::getComputerName()
{
    char name [256] = { 0 };
    if (gethostname (name, sizeof (name) - 1) == 0)
        return String (name).upToLastOccurrenceOf (".local", false, true);

    return String::empty;
}

static String getLocaleValue (CFStringRef key)
{
    CFLocaleRef cfLocale = CFLocaleCopyCurrent();
    const String result (String::fromCFString ((CFStringRef) CFLocaleGetValue (cfLocale, key)));
    CFRelease (cfLocale);
    return result;
}

String SystemStats::getUserLanguage()   { return getLocaleValue (kCFLocaleLanguageCode); }
String SystemStats::getUserRegion()     { return getLocaleValue (kCFLocaleCountryCode); }

String SystemStats::getDisplayLanguage()
{
    CFArrayRef cfPrefLangs = CFLocaleCopyPreferredLanguages();
    const String result (String::fromCFString ((CFStringRef) CFArrayGetValueAtIndex (cfPrefLangs, 0)));
    CFRelease (cfPrefLangs);
    return result;
}

//==============================================================================
class HiResCounterHandler
{
public:
    HiResCounterHandler()
    {
        mach_timebase_info_data_t timebase;
        (void) mach_timebase_info (&timebase);

        if (timebase.numer % 1000000 == 0)
        {
            numerator   = timebase.numer / 1000000;
            denominator = timebase.denom;
        }
        else
        {
            numerator   = timebase.numer;
            denominator = timebase.denom * (uint64) 1000000;
        }

        highResTimerFrequency = (timebase.denom * (uint64) 1000000000) / timebase.numer;
        highResTimerToMillisecRatio = numerator / (double) denominator;
    }

    inline uint32 millisecondsSinceStartup() const noexcept
    {
        return (uint32) ((mach_absolute_time() * numerator) / denominator);
    }

    inline double getMillisecondCounterHiRes() const noexcept
    {
        return mach_absolute_time() * highResTimerToMillisecRatio;
    }

    int64 highResTimerFrequency;

private:
    uint64 numerator, denominator;
    double highResTimerToMillisecRatio;
};

static HiResCounterHandler hiResCounterHandler;

uint32 juce_millisecondsSinceStartup() noexcept         { return hiResCounterHandler.millisecondsSinceStartup(); }
double Time::getMillisecondCounterHiRes() noexcept      { return hiResCounterHandler.getMillisecondCounterHiRes(); }
int64  Time::getHighResolutionTicksPerSecond() noexcept { return hiResCounterHandler.highResTimerFrequency; }
int64  Time::getHighResolutionTicks() noexcept          { return (int64) mach_absolute_time(); }

bool Time::setSystemTimeToThisTime() const
{
    jassertfalse;
    return false;
}

//==============================================================================
int SystemStats::getPageSize()
{
    return (int) NSPageSize();
}
