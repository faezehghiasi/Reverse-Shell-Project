# Reverse-Shell-Project
This project implements a simple reverse shell using C. It consists of two programs: a server and a client. 
The server listens for incoming connections, while the client connects to the server and executes commands received from the server. 
The server then receives the output of these commands.

## Description
A reverse shell is a type of shell where the target machine opens a connection to an attacker's machine, allowing the attacker to execute commands on the target system. In this project, the server acts as the attacker's machine, and the client acts as the target machine. The server sends commands to the client, which executes them and sends back the results. This project demonstrates the basic principles of socket programming and remote command execution.

## Requirements
A Unix-like operating system (Linux, macOS, etc.)

GCC (x.y.z)

## Building the Code
You can use the provided Makefile to build the server and client programs.

**1-** Open a terminal.

**2-** Navigate to the directory containing the Makefile.

**3-** Run the following command to build both the server and client:

```bash
make
```

## Running the Programs
### Server :

To run the server, specify the desired port number:

> ./server <port_number>

For example, to run the server on port 3000:

```bash
./server 3000
```

### Client :

To run the client, specify the server's IP address and port:

> ./client <port_number> <server_ip>

For example, to connect to a server at 127.0.0.1 on port 3000:

```bash
./client 3000 127.0.0.1
```

## Notes
* Ensure that the server and client are running on the same network or that the necessary ports are open if running on different networks.

* Use this code responsibly and only on networks and systems where you have permission to do so.
