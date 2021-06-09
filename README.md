# Secure-File-System-Simulation
A secure file system simulation in c++ using the 128-bit key AES algorithm for encrypting the file content and the metadata.
Many users often store their important information on computers that are easily accessible to anyone. Such information includes their personal information, important documents or even some documents related to their work. If this information is reaches on the wrong hands,it might prove disastrous for them and
hence, it's very important to take steps to decrease such chances. In order to achieve this goal, we have designed and built a new user-friendly cryptographic file system which makes use of AES Algorithm to encrypt the data of the users. Besides this, the file system also prevents untrusted users from deleting any data and hence provides an extra layer of security.

## Basic features of our file system
- Users can perform the basic commands provided by the Terminal such as create, delete, read, write and rename files.
- The file system supports directories.The directories can be used to store new directories and files inside it.
- These directories can be protected using a password. This password will be needed to access the contents inside the directory and delete the directory.
- The contents of the file will be encrypted using a 16-bit hexadecimal test key.
- The original contents of the file are never stored anywhere on the server. This means that the decrypted content can never be accessed without the key.

### Project Directory
```
Secure-File-System-Simulation
├── final_filesystem # Main directory
│ ├── aes-new 
│ |    ├── decrypt.cpp # Contains the decryption code of AES Algorithm
│ |    ├── encrypt.cpp # Contains the encryption code of AES Algorithm
| |    └── structures.h # Helper function for AES Algorithm
| ├── file.cpp # Simulates the file system
│ └── message.aes 
└── README.md # This document
```

### 16-bit hexadecimal test key example
01 04 02 03 01 03 04 0A 09 0B 07 0F 0F 06 03 00

# Running the simulation

    cd secure_file_system
    g++ file.cpp -o file
    ./file
    
It's is strongly recommended to use Linux Operating System to run this simulation as we have used colored text for better visualization of contents and  the command for these visualization techniques vary from OS to OS.

### Collaborators
- [Apoorv Singh Chauhan](https://github.com/apoorv-asc)
- [Joyeeta Dey](https://github.com/joyeeta-19)
- [Zeel Desai](https://github.com/zeel2104)

