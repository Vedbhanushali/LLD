# 🖥️ C++ Low-Level Design Playground

Welcome to my **C++ Low-Level Design (LLD) Repository** — a curated collection of real-world system design problems implemented in C++ with a focus on **clean architecture, OOP principles, and threading concepts**.  
This repo is perfect for **interview preparation**, **learning LLD patterns**, or just exploring how complex systems are built step-by-step.

---

## 📂 Projects Included

### 1️⃣ Cron Job Scheduler ⏰

A simplified cron job system that schedules and executes commands at specific times.  
**Highlights:**  

- Threading with `std::thread` and `std::chrono`  
- Non-blocking execution with `detach()` and optional `join()` support  

---

### 2️⃣ Social Media App 📱

A basic design for a social media platform with users, posts, likes, and comments.  
**Highlights:**  

- OOP principles  
- Class relationships (User ↔ Post ↔ Comment)  
- Data storage simulation  

---

### 3️⃣ Chess Game ♟️

A low-level design of chess with all pieces, moves, and game rules.  
**Highlights:**  

- Polymorphism for chess pieces  
- Board management  
- Rule validation  

---

### 4️⃣ Poll Management System 📊

Create and manage polls with multiple options and vote tracking.  
**Highlights:**  

- Encapsulation of poll data  
- Vote counting and result display  
- Simple CLI interaction  

---

### 5️⃣ Snake & Ladder Game 🎲

A digital version of the classic board game.  
**Highlights:**  

- Random dice roll  
- Player turns  
- Snakes and ladders logic  

---

### 6️⃣ Splitwise 💰

An expense-sharing application for friends and groups.  
**Highlights:**  

- Expense tracking  
- Balances calculation  
- Settlement feature  

---

### 7️⃣ Thread Basics 🧵

Minimal examples to understand C++ multithreading.  
**Highlights:**  

- `std::thread` usage  
- `join()` and `detach()`  
- Mutex locking for thread safety  

---

### 8️⃣ Warehouse Management System 📦

Low-level system to manage inventory, orders, and stock updates.  
**Highlights:**  

- Order fulfillment  
- Inventory tracking  
- Stock validation  

---

## 🚀 Getting Started

### Prerequisites

- **C++17 or later** (recommended: g++ / clang++ / MSVC)
- Basic understanding of C++ OOP and STL

### Compilation & Run

```bash
g++ filename.cpp -o output -std=c++17 -pthread
./output
```
