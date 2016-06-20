
When compiling on Windows, we use "#pragma lib" to link in necessary libraries. If you are using G++ or Clang on Windows you must link to the following libraries:

wsock32
ws2_32
IPHLPAPI
Winmm
Shlwapi
Psapi

Visual Studio 2015 compilation has now been fixed
