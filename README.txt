# Building

Program requires a UNIX system to take advantage of <sys/socket.h>.
While in the terminal, type "make" to run our Makefile to create the
client and server executable.

$ make all //to create both the ./client and ./server exectuable
$ make [cc/ss] //cc creates client, ss creates server
$ make clean //deleted execturables

# Playing

Instructions are given step by step in either program. Either one can be run, the client will wait for the server to be created, and vice verso

The client program can be run by another user after the server has started.

The server expects connections on localhost.
