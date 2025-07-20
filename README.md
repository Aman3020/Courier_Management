
# 📦 Courier Management System (Enhanced C++ Project)

A secure and efficient **Courier Management System** built in **C++** using **Object-Oriented Programming (OOP)** principles and robust **file handling**. This project simulates courier management operations via a command-line interface.

---

## ✅ Features

- Admin login with username/password authentication
- Add new courier orders with status tracking
- Display all courier records in tabular format
- Search courier by tracking ID
- Delete courier record
- Update courier details (including status)
- Filter couriers by delivery status (Pending / In Transit / Delivered)
- Input validation to prevent empty fields or duplicates
- Stores all data persistently in a text file (`courier.txt`)
- Uses structured CSV-like file storage

---

## 🛠️ Requirements

- C++ Compiler (g++ recommended)
- Terminal / Command Prompt

---

## ⚙️ How to Compile & Run

1. Open terminal in the project folder.

2. Compile:
```bash
g++ -o Courier_Management Courier_Management.cpp
````

3. Run:

```bash
./Courier_Management
```

---

## 📚 OOP Concepts Used

* **Classes and Objects**: Courier, CourierManager, CourierFileHandler
* **Encapsulation**: Private members and public methods
* **File Handling**: Reading and writing CSV data
* **Exception Handling**: Runtime error management using try-catch blocks
* **Static Method**: Used for CSV parsing (`fromCSV`)
* **Single Responsibility Principle**: File handling logic separated via `CourierFileHandler`

---

## 🚀 How It Works

1. Admin authentication is required to access system.
2. Menu-driven interface for managing couriers.
3. Orders can be:

   * Added
   * Viewed
   * Updated
   * Deleted
   * Filtered by delivery status
4. Output is displayed neatly and stored persistently in `courier.txt`.

---

## 📥 How to Use

* After login, select options from the menu:

  * Insert couriers
  * Search / update / delete by tracking ID
  * Filter by status
* Records are auto-saved to a text file.

---

## 📁 Project Structure

```
Courier_Management.cpp
courier.txt (auto-generated)
README.md
```

---

## 📃 License

Free to use for educational and non-commercial purposes.

---

## 🙌 Contributing

* Fork this repository
* Raise issues or suggest improvements
* Submit pull requests for collaboration

---

```

Let me know if you'd like me to add a sample CSV output or example screenshots.
```
