# TA_CoE
CAN-Bus reader for "Technische Alternative" (TA) "CAN over Ethernet" (CoE)

The idea behind this software is a slim and standalone daemon, which receives CoE data from a running C.M.I. hardware interface. The included telnet server returns all received data and makes a further handling convenient.
There are no external dependencies (besides the included libraries). A C++11 compiler is required to get the souce code built. It should work on many modern *nix plattforms.

Currently the software is not fully usable. The data is read, but the telnet server understands only a `list` command.

# Build
* clone this repository: `git clone https://github.com/ronny332/TA_CoE`
* move to working directory: `cd TA_CoE`
* run cmake: `cmake .`
* run the makefile: `make`
* start TA_CoE: `./TA_CoE -v`

# Options
* -v turns on the verbose level to maximum
* --v[0-9] will change the verbose level 

# Telnet Commands
* `get ALL` return all known values as text
* `get ALL as JSON` return all known values as JSON data 

connect to port 5441 (TCP) to run the command, for instance `echo list | nc localhost 5441`

![TA_CoE in an early version](https://github.com/ronny332/TA_CoE/raw/master/TA_CoE.png)