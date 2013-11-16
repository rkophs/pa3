Author: Ryan Kophs
Date: 15 Nov 2013
Assignment 3

Description:
Each router will connect and sync with each other via a link-state algorithm. To begin, each router is instantiated at the same time. Each router will porse an init.txt file to grab the names and ports of its directly connected neighbors. Next each router will try and connect with those direct neighbors by either listening for an incoming neighbor connection or instantiating one to a neighbor router. 

If the source port of the connection for the router is less than the destination port, it will try and connect. However, if the source port is larget than the destination port, it will listen. All listeners are set up, then 10 seconds later, all routers will try connecting on the appropriate ports. After this, each router should be connected.

Next, each router will transmit its LSP to neighbor routers (flooding). Each router keeps a copy of an incoming LSP if it doesn't already exist in that router's pool or has a sequence number higher than a previously saved copy of the LSP. If the LSP is kept or updated, it is then forwarded to other subsequent neighbors. When ever a LSP is updated or added to a pool in each router, that router will recalculate its forwarding table via Dijkstra's algorithm.

This process continues every 5 seconds (i.e. a router sends its LSP ever 5 seconds). After a user defined time limit, one router will transmit a kill signal to each neighbor and die. Each neighbor will receive the signal, forward it, and die graciously. This time limit is defined as an optional commandline argument during initiation.

Initiate 1 router:
> ./router <name> <logfile> <init file> <optional.kill.timer>
However, do not use the same init file for each router or it will cause a segmentation fault!!!

Initiate multiple routers:
> sh routers.sh

Graceful ending:
Add an optional timer on just one of the routers in order to get it to end at that time and send commands to the other routers to end as well.

Compile:
> make clean
> make

Log:
A separate log file is set up for each router. Do not use the same log file for each router or bad things will happen!
The log is updated each time a new LSP is added, but not when an LSP is dropped. Therefore, the router table will be update on each non-dropped LSP, although there may be nothing to update, it is just that Dijkstra's is executed again and reflects in the log files.




