# 🏦 Console Banking System

A lightweight, high-performance console-based banking management system written in modern C++. The system provides secure data persistence using file-based storage, complete client management capabilities, and transaction handling.

## ✨ Key Features

* **Client Management (CRUD):** Easily add, look up, update, and securely delete client profiles.
* **Transaction Engine:** Seamless support for deposits, withdrawals, and tracking real-time client account balances.
* **Data Persistence:** Automatically stores and reads client records from text files using structured record serialization.

## 🛠️ Architectural \& Performance Optimizations

* **Memory Efficient:** Optimized using pass-by-reference constraints (`const std::vector<sClient>\&`) across core lookup and saving routines to prevent expensive runtime array copying overhead.
* **Input Stream Safety:** Implemented robust stream validation techniques (`cin.clear()` and `ws` modifiers) to completely eliminate input buffer mixing bugs when moving between structural menus.
* **Encapsulated Scope:** Codebase logic is completely isolated inside a distinct namespace to prevent global namespace pollution.

## 🚀 How to Run

1. Clone the repository:

&#x20; 'bash
   git clone \[https://github.com/haitham-5/Bank-System.git]

&#x20;            (https://github.com/haitham-5/Bank-System.git)

