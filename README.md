# Reverse-Shell-Project
This project implements a simple reverse shell using C. It includes two programs: a **server** and a **client**. The server listens for incoming connections, while the client connects to the server and executes received commands, sending back the output.

---

## Description
A reverse shell is a type of shell where the target machine opens a connection to an attacker's machine, allowing the attacker to execute commands remotely. In this project:

- **Server:** Acts as the attacker's machine, sending commands to the client.
- **Client:** Acts as the target machine, executing commands and returning results.

This project demonstrates core concepts of **socket programming** and **remote command execution** in C.

---

## Requirements
- A Unix-like operating system (Linux, macOS, etc.)
- **GCC** compiler

---

## Building the Code
Use the provided `Makefile` to compile both programs.

**1-** Open a terminal.

**2-** Navigate to the project directory containing the `Makefile`.

**3-** Run the following command to build both the server and client:

```bash
make
```

---

## 🔧 Running the Programs
### **Server:**
To run the server, specify the desired port number:

```bash
./server <port_number>
```

**Example:**
```bash
./server 3000
```

### **Client:**
To run the client, provide the server's IP address and port number:

```bash
./client <port_number> <server_ip>
```

**Example:**
```bash
./client 3000 127.0.0.1
```

---

## Important Notes
- Ensure the server and client run on the same network or configure port forwarding if connecting across networks.
- Use this project responsibly **only** on authorized systems and networks.




