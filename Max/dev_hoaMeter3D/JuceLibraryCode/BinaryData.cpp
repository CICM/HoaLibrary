/* ==================================== JUCER_BINARY_RESOURCE ====================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

namespace BinaryData
{

//================== maxmspsdk.xcconfig ==================
static const unsigned char temp_binary_data_0[] =
"// Xcode target configuration settings for the Max 6 SDK\n"
"// Used as the basis for Xcode projects to build Max externals.\n"
"//\n"
"// Changes to the settings in this file will be applied to all SDK examples\n"
"// To change settings for only one of the examples, override the settings using\n"
"// Xcode's target inspector.\n"
"//\n"
"// by Timothy Place\n"
"// Copyright \xc2\xa9 2012, Cycling '74\n"
"\n"
"\n"
"// Name & Version\n"
"PRODUCT_NAME = $(PROJECT_NAME)\n"
"PRODUCT_VERSION = 6.1.4\n"
"ARCHS = i386 x86_64\n"
"\n"
"\n"
"// Paths\n"
"C74SUPPORT = $(SRCROOT)/../../../../../../SDKs/MaxSDK-6.1.4/c74support\n"
"HEADER_SEARCH_PATHS = \"$(C74SUPPORT)/max-includes\" \"$(C74SUPPORT)/msp-includes\" \"$(C74SUPPORT)/jit-includes\"\n"
"FRAMEWORK_SEARCH_PATHS = \"$(C74SUPPORT)/max-includes\" \"$(C74SUPPORT)/msp-includes\" \"$(C74SUPPORT)/jit-includes\"\n"
"DSTROOT = $(SRCROOT)/../../../sdk-build/externals\n"
"// (This next path is relative to DSTROOT)\n"
"INSTALL_PATH = /\n"
"\n"
"\n"
"// Special Files\n"
"GCC_PREFIX_HEADER = $(C74SUPPORT)/max-includes/macho-prefix.pch\n"
"INFOPLIST_FILE = $(SRCROOT)/../../Info.plist\n"
"\n"
"\n"
"// Architecture and Deployment\n"
"ARCHS = i386 x86_64\n"
"\n"
"// The following section sets the Mac SDK version to be used.\n"
"// For most projects this has little to no impact because there are no direct dependencies on OS function calls.\n"
"// In those projects with OS function calls, it should be okay to use the most recent SDK version because the \n"
"// MACOSX_DEPLOYMENT_TARGET will disable functionality that is unavailable in the older target OS.\n"
"// For this reason, the SDKROOT variable is commented out, telling Xcode to use the default (which is the most recent SDK).\n"
"//\n"
"// If you do need to define the SDKROOT, different versions of Xcode have varying syntax and varying versions of the SDK present.\n"
"\n"
"// Xcode 3.x\n"
"// SDKROOT = $(DEVELOPER_DIR)/SDKs/MacOSX10.5.sdk\n"
"\n"
"// Xcode 4.0 - Xcode 4.2\n"
"// SDKROOT = $(DEVELOPER_DIR)/SDKs/MacOSX10.6.sdk\n"
"\n"
"// Xcode 4.3+\n"
"// SDKROOT = macosx10.6\n"
"\n"
"MACOSX_DEPLOYMENT_TARGET = 10.6\n"
"\n"
"\n"
"// Compiler Version -- leave them all commented out to get the default version provided by Xcode\n"
"// GCC_VERSION = 4.2\n"
"// GCC_VERSION = com.apple.compilers.llvmgcc42\n"
"// GCC_VERSION = com.apple.compilers.llvm.clang.1_0\n"
"\n"
"\n"
"// Preprocessor Defines\n"
"GCC_PREPROCESSOR_DEFINITIONS = \"DENORM_WANT_FIX = 1\" \"NO_TRANSLATION_SUPPORT = 1\"\n"
"\n"
"\n"
"// Static Configuration (don't change these)\n"
"WRAPPER_EXTENSION = mxo;\n"
"WARNING_CFLAGS = -Wmost -Wno-four-char-constants -Wno-unknown-pragmas\n"
"DEPLOYMENT_LOCATION = YES\n"
"GENERATE_PKGINFO_FILE = YES\n"
"\n"
"\n"
"// Flags to enforce some build-time checks for the symbols used while not actually performing a hard link\n"
"C74_SYM_LINKER_FLAGS = @$(C74SUPPORT)/max-includes/c74_linker_flags.txt\n"
"\n"
"\n"
"// hide all symbols by default\n"
"// mark a function to be exported with the C74_EXPORT macro -- most likely this will only apply to the main() function\n"
"OTHER_CFLAGS = -fvisibility=hidden\n";

const char* maxmspsdk_xcconfig = (const char*) temp_binary_data_0;


const char* getNamedResource (const char*, int&) throw();
const char* getNamedResource (const char* resourceNameUTF8, int& numBytes) throw()
{
    unsigned int hash = 0;
    if (resourceNameUTF8 != 0)
        while (*resourceNameUTF8 != 0)
            hash = 31 * hash + (unsigned int) *resourceNameUTF8++;

    switch (hash)
    {
        case 0xa54b1af8:  numBytes = 2800; return maxmspsdk_xcconfig;
        default: break;
    }

    numBytes = 0;
    return 0;
}

const char* namedResourceList[] =
{
    "maxmspsdk_xcconfig"
};

}
