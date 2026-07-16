# 🏦 Console Banking & ATM Ecosystem

A lightweight, high-performance, and secure banking ecosystem written in modern C++. This repository contains two fully functional, decoupled systems that interact with the same local file database:

1. **The Core Banking Management System** — an admin-facing platform with complete CRUD controls, user administration, and role-based access control.
2. **The ATM System** — a client-facing, lightweight single-header interface designed for quick deposits, custom withdrawals, and rapid balance inquiries.

---

## 📑 Table of Contents

- [Features](#-system-features)
- [Architecture & Performance](#️-architectural--performance-optimizations)
- [Permissions](#-system-permissions-admin-portal)
- [File Structure](#-file-structure)
- [Data Format](#-shared-data-serialization-format-clienttxt)
- [Getting Started](#-getting-started)
- [Requirements](#-requirements)
- [Roadmap](#-roadmap)
- [Contributing](#-contributing)

---

## ✨ System Features

### 🏢 1. Core Banking Management System (Admin-Facing)

- **Client Management (CRUD):** Add, look up, update, and delete client profiles.
- **User Management (CRUD):** System administrators can manage operators, configuring customized privilege scopes.
- **Role-Based Access Control:** Fine-grained, bitmask-based permissions controlling specific screens (e.g., Show Clients, Manage Users) or full (`-1`) master admin access.
- **Secure Authentication:** Gated by username and password. User passwords are automatically hashed before being written to disk and are never displayed in plain text.

### 🏧 2. The ATM System (Client-Facing)

- **Secure ATM Login Screen:** Access is restricted using client account numbers and matching PIN codes verified against the active database.
- **Smart Transaction Engine:**
  - **Quick Withdraw:** Fast cash intervals ($20, $50, $100, $200, $400, $600, $800, $1000).
  - **Normal Withdraw:** Custom withdrawal amounts (enforcing the standard ATM rule: must be divisible by 10).
  - **Direct Deposit:** Easily deposit custom positive amounts directly into the account.
- **Instant Balance Check:** Rapidly check current balances in real-time.

---

## 🛠️ Architectural & Performance Optimizations

- **Shared Data Store:** Both programs operate on the same data file (`client.txt`), so updates made by an administrator in the Banking System are immediately available for ATM logins.
- **Memory Efficient:** Optimized with pass-by-reference constraints (`const std::vector<sClient>&` and `std::vector<sClient>&`) across core lookup and saving routines to eliminate expensive runtime copying overhead.
- **Compile-Guarded Single-Header ATM:**
  - The ATM program is completely contained within a modular, single-header file (`ATM.h`).
  - The ATM global state (`CurrentClient`) and system helper functions are marked `inline`, guaranteeing linker safety and allowing the header to be included across multiple source files without duplication errors.
- **Input Stream Safety:** Uses robust stream validation techniques (`cin.clear()` and stream buffer flushes) to defend against input buffer contamination when navigating menus.

---

## 🔐 System Permissions (Admin Portal)

Each operator has a set of granular permissions, stored as a bitmask, or full access:

| Permission | Value |
| :--- | ---: |
| Show All Clients | 1 |
| Add New Clients | 2 |
| Update Clients | 4 |
| Delete Clients | 8 |
| Find Clients | 16 |
| Transaction Screen | 32 |
| Manage Users | 64 |
| **Full System Access** | **-1** |

> 🔒 **Security Notice:** Passwords are securely hashed on entry (both when creating and updating a user) and are never stored or displayed in plain text.

---

## 📁 File Structure

```text
├── Bank.cpp          # Banking System entry point (Admin App)
├── Bank.h            # Banking System core logic and declarations
├── ATM.cpp           # ATM System entry point (Client App)
├── ATM.h             # Single-header ATM engine (guarded & inline-optimized)
├── client.txt        # Shared local client database (serialized)
└── users.txt         # Admin/operator system credentials
```

---

## 🗃 Shared Data Serialization Format (`client.txt`)

Data is structured using a `#//#` delimiter:

```text
AccountNumber#//#PinCode#//#Client Name#//#Phone Number#//#Balance
```

---

## 🚀 Getting Started

### Requirements

- A C++17-compatible compiler (e.g., `g++` 7+ or `clang++` 5+)
- Git

### 1. Clone the Repository

```bash
git clone https://github.com/haitham-5/Bank-System.git
cd Bank-System
```

### 2. Run the Banking Management System (Admin Portal)

**Compile:**

```bash
g++ -std=c++17 main.cpp -o BankSystem
```

**Run:**

```bash
./BankSystem
```

> **Note:** Log in with the default admin credentials — default admin password is `0000`.

### 3. Run the ATM System (Client Portal)

**Compile:**

```bash
g++ -std=c++17 ATM.cpp -o ATMSystem
```

**Run:**

```bash
./ATMSystem
```

> **Note:** Log in using any client's account number and PIN code present in `client.txt`.

---

## 📋 Requirements

| Component | Minimum Version |
| :--- | :--- |
| C++ Standard | C++17 |
| Compiler | GCC 7+ / Clang 5+ / MSVC 2019+ |
| OS | Linux, macOS, Windows |

---

## 🗺 Roadmap

- [ ] Migrate flat-file storage to SQLite for concurrent access safety
- [ ] Add transaction history/audit logs
- [ ] Add configurable withdrawal/deposit limits
- [ ] Add unit tests for core banking logic

---

## 🤝 Contributing

Contributions are welcome! Feel free to open an issue or submit a pull request for bug fixes, new features, or documentation improvements.

---
