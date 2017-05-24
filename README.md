Check-Reg
=
This repo is to register/validate project using github and curl.

Usage
-
Put a curl.exe or curl compatible with your current system in path.
And actually this repo is destined for Win usage. So unix users shall do 
some modifications.
See the header files for references.

Detailed Instructions
-
check.c includes functions that read info from net, actually somewhere we can
leave a message for the program to track.

nreg.c includes some functions co-operate with git. But actually no git support 
is needed.

verify-routine.c is my personal realization using the above functions.
