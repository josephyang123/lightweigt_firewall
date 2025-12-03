### # Lightweigt_firewall

- This is a simple C++ project that simulates a basic login system for a firewall menu.  
- It includes user registration, login, and basic file hiding/encryption.

---

### # Lightweight_firewall

- This is a simple C++ project that simulates a basic login system for a firewall menu.  
- It includes user registration, login, and basic file hiding/encryption.

---

### ### Project Overview

- **What this firewall does**  
- A minimal, user-space prototype firewall written in C++. It demonstrates a guarded entry point for a network-related application by requiring user authentication before the main logic runs. The project is intended as a learning and prototyping tool for access control, packet handling experiments, and simple rule-based filtering.

- **What problems it solves**  
- Provides a simple example of protecting a small tool or demo service from unauthorized use.  
- Serves as a starting point for experimenting with packet inspection, raw sockets, and access control logic without the complexity of kernel-level firewalls.  
- Demonstrates secure credential handling basics (hashed credentials) and a clear place to extend into network filtering.

- **Why it is lightweight**  
- **Design philosophy**: focused, readable, and easy to extend; not intended as a production-grade firewall.  
- **Simplicity**: single executable prototype with minimal control flow and a tiny on-disk credential store.  
- **Minimal dependencies**: uses standard C++ libraries and OpenSSL for hashing; no kernel modules or heavy frameworks.

---

### ### Features

- **Current capabilities**  
- Interactive registration and login flow that stores hashed credentials in a local file (`.credentials.txt`).  
- SHA-256 hashing of credentials using OpenSSL EVP APIs.  
- Compact codebase suitable for extension into packet handling or rule-based filtering.

- **Planned features**  
- Packet capture and inspection using raw sockets or libpcap.  
- Rule engine for allow/deny lists by IP, port, or protocol.  
- Logging, configurable verbosity, and rotation.  
- Per-user roles and encrypted credential storage.  
- Unit tests and CI integration.

---

### ### Installation

- **Required dependencies**  
- **Compiler**: `g++` (C++17) or equivalent (Clang, MSVC).  
- **Build tools**: `make` (optional).  
- **Libraries**: OpenSSL development headers and libraries (`libssl-dev` or equivalent) for SHA-256 hashing.

- **Supported platforms**  
- **Linux**: primary target.  
- **macOS**: supported with OpenSSL installed via Homebrew and a compatible compiler.  
- **Windows**: possible with MinGW or Visual Studio; OpenSSL must be installed and linked. Socket and privilege code may need adaptation.

- **How to compile**  
- If your project has a single source file (for example `main.cpp`):

- g++ -std=c++17 -O2 -Wall -Wextra -lssl -lcrypto -o lightweight-firewall main.cpp

- If the project contains multiple source files in the project root:

- g++ -std=c++17 -O2 -Wall -Wextra -lssl -lcrypto -o lightweight-firewall *.cpp
- Where to put the Makefile snippet Place the Makefile in the project root (the same folder as your .cpp files). Name it Makefile (capital M) so running make will pick it up.

- Makefile snippet

- makefile
- CXX = g++
- CXXFLAGS = -std=c++17 -O2 -Wall -Wextra
- LDLIBS = -lssl -lcrypto
- SRCS = $(wildcard *.cpp)
- OBJS = $(SRCS:.cpp=.o)
- TARGET = lightweight-firewall

- all: $(TARGET)

- $(TARGET): $(OBJS)
-     $(CXX) $(CXXFLAGS) -o $@ $^ $(LDLIBS)

- clean:
-     rm -f $(OBJS) $(TARGET)
- Usage
- How to run the executable

- bash
- ./lightweight-firewall
- On Windows:

- powershell
- lightweight-firewall.exe
- Basic interactive flow

- First run: If no credentials exist, the program prompts to register a new user and password. Credentials are hashed and stored in .credentials.txt.

- Subsequent runs: The program prompts for User ID and Password. On successful authentication it prints Welcome to Firewall and proceeds to the main logic.

- Example command-line scenarios

- Run the program in the foreground for interactive testing: ./lightweight-firewall

- Run under a debugger for development: gdb --args ./lightweight-firewall

- Example configuration

- No external configuration file in the current prototype.

- Credentials are stored in the working directory in .credentials.txt as two space-separated SHA-256 hex strings: <user-id-hash> <password-hash>.

- Expected input and output behavior

- Input: interactive text input via stdin for registration and login.

- Output: console messages indicating registration, login success, or failure.

- Files: .credentials.txt created in the working directory when a user registers.

- Project Structure
- Important files and folders

- main.cpp — entry point and interactive menu logic (authentication and simple program flow).

- README.md or README.txt — project documentation.

- .credentials.txt — local credential store created at runtime (do not commit).

- Makefile — optional build helper (place in project root).

- src/ — recommended folder for splitting code into modules as the project grows.

- tests/ — recommended location for unit tests.

- Where the core logic lives

- Authentication and credential handling are implemented in the main source file (functions such as hashPassword, writeFile, readFile, Register, Menu, and logIn).

- Future network and firewall logic should be placed in a dedicated module (for example firewall_core.cpp / firewall_core.h) to separate concerns and improve testability.

- Contributing
- How to propose changes

- Fork the repository.

- Create a branch named feature/your-feature or fix/issue-number.

- Commit changes with clear, descriptive messages.

- Open a Pull Request against main with a summary of changes and any testing instructions.

- Coding style and standards

- Use modern C++ (C++17) idioms.

- Keep functions small and focused. Prefer std::string, std::vector, and RAII for resource management.

- Compile with -Wall -Wextra and resolve warnings before submitting.

- Use consistent indentation (4 spaces recommended) and clear naming.

- Document public functions with brief comments.

- Security and review

- Security-sensitive changes (authentication, storage, networking) should include a short security rationale.

- Add tests for changes that affect credential handling or network behavior.

- Pull requests that change credential handling or network behavior will receive additional review.

- License
- This project is released under the MIT License.

- Suggested LICENSE file content


- MIT License

- Copyright (c) YEAR Your Name

- Permission is hereby granted, free of charge, to any person obtaining a copy
- of this software and associated documentation files (the "Software"), to deal
- in the Software without restriction, including without limitation the rights
- to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
- copies of the Software, and to permit persons to whom the Software is
- furnished to do so, subject to the following conditions:

- [Full MIT text continues...]
- Include a short header in new source files:

- c
- /*
-   Copyright (c) YEAR Your Name
-   Licensed under the MIT License
- */
- Notes and Next Steps
- Security note The current prototype appends a static "salt" string to passwords before hashing. For production use, switch to per-user random salts, use a slow KDF (e.g., PBKDF2 or Argon2), and protect the credential file with proper file permissions or encryption.

- Recommended refactors

- Split authentication, storage, and firewall logic into separate modules.

- Add unit tests and CI to validate hashing, login flows, and future packet filtering logic.

- Add logging, configuration parsing, and a rule engine for flexible filtering.

- References
- Linux cpp GitHub: https://github.com/psantana5/firewall/blob/main/Linux/src/main.cpp

- Code


### ### References
- Linux cpp GitHub https://github.com/psantana5/firewall/blob/main/Linux/src/main.cpp