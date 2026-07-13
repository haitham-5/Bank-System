# 🏦 Console Banking System

A lightweight, high-performance console-based banking management system written in modern C++. The system provides secure data persistence using file-based storage, complete client management capabilities, user authentication with role-based permissions, and transaction handling.

## ✨ Key Features

* **Client Management (CRUD):** Easily add, look up, update, and securely delete client profiles.
* **Transaction Engine:** Seamless support for deposits, withdrawals, and tracking real-time client account balances.
* **User Management (CRUD):** Add, update, find, and delete system users, each with an individually configurable set of permissions.
* **Authentication \& Login:** Username/password login screen gates access to the system; each session runs under the logged-in user's permission set.
* **Role-Based Access Control:** Fine-grained, bitmask-based permissions (Show Clients, Add Clients, Update Clients, Delete Clients, Find Clients, Transactions, Manage Users) or full admin access.
* **Password Hashing:** User passwords are hashed before being written to disk and are never displayed in plain text, including in the admin's "Show All Users" and "Find User" screens.
* **Data Persistence:** Automatically stores and reads client and user records from text files using structured record serialization.

## 🛠️ Architectural \& Performance Optimizations

* **Memory Efficient:** Optimized using pass-by-reference constraints (`const std::vector<sClient>\&`) across core lookup and saving routines to prevent expensive runtime array copying overhead.
* **Input Stream Safety:** Implemented robust stream validation techniques (`cin.clear()` and `ws` modifiers) to reduce input buffer mixing bugs when moving between structural menus.
* **Encapsulated Scope:** Codebase logic is completely isolated inside a distinct namespace to prevent global namespace pollution.
* **Header Guarded:** Uses `#pragma once` to prevent multiple-definition errors when included across translation units.

## 🔐 Users \& Permissions

Each user has a set of granular permissions, stored as a bitmask, or full (`-1`) access to every feature:

|Permission|Value|
|-|-|
|Show All Clients|1|
|Add New Clients|2|
|Update Clients|4|
|Delete Clients|8|
|Find Clients|16|
|Transaction Screen|32|
|Manage Users|64|
|Full System Access|-1|

Passwords are hashed on entry (both when creating and updating a user) and are never stored or displayed as plain text.

## 🚀 How to Run

1. Clone the repository:

```bash
   git clone https://github.com/haitham-5/Bank-System.git
   ```

2. On first run, log in with your admin credentials to access the Main Menu "the Admin Password is : 0000", or use the **Manage Users** screen to create additional users with custom permissions.

