# TA_CoE
CAN-Bus reader for "Technische Alternative" (TA) "CAN over Ethernet" (CoE)

There are no external dependencies (besides the included libraries). The Source Code should build on every modern *nix plattform.
For the use on older distributions like Raspbian the compiler flag "-std=c++0x" is used instead of "-std=c++11".

Currently the software is not fully usable. The data is read, but the telnet server is not replying anything.

# Build
* clone this repository: `git clone https://github.com/ronny332/TA_CoE`
* move to working directory: `cd TA_CoE`
* run cmake: `cmake .`
* run the makefile: `make`
* start TA_CoE: `./TA_CoE`

# Options
* -v turns on the verbose level to maximum
* --v[0-9] will change the verbose level 