# 💰 Expense & Budget Tracker

**DA1 Mini Project | VIT Chennai**

A personal finance web application to track daily expenses, monitor monthly budgets, and analyze spending by category.

---

## 🌐 Live Demo

👉 [Click here to open the app](https://your-deployment-link.vercel.app)

---

## 📋 Features

- ➕ Add expenses with Date, Category, Amount, and Note
- 📊 Dashboard with monthly summary and budget usage bar
- 🏷️ Category-wise breakdown with donut chart
- 🔍 Search expenses by date, category, or note
- ⚠️ Budget warning when monthly limit is exceeded
- 💾 Data saved in browser (localStorage)
- 🗑️ Delete individual expenses
- 📅 Navigate between months

---

## 🛠️ Tech Stack

| Layer | Technology |
|---|---|
| Core Logic | C (menu-driven, file handling, structs) |
| Frontend | HTML, CSS, JavaScript |
| Chart | Chart.js |
| Hosting | Vercel / GitHub Pages |

---

## 📁 Project Structure

```
expense-tracker/
├── index.html      # Complete web application (single file)
├── main.c          # Original C program (console version)
└── README.md       # This file
```

---

## ▶️ C Program Features

The `main.c` file contains the original console-based C program with:

- ✅ Menu-driven program using `switch/case`
- ✅ 9 user-defined functions
- ✅ 1 struct (`Expense`)
- ✅ File handling (`save` and `load` using `expenses.txt`)
- ✅ Input validation (date format, amount range, menu input)

### How to Run (locally)
```bash
gcc main.c -o tracker
./tracker        # Linux/Mac
tracker.exe      # Windows
```

---

## 📌 C Concepts Used

| Concept | Where Used |
|---|---|
| `struct` | `Expense` struct with date, category, amount, note |
| `switch/case` | Main menu navigation |
| File I/O | `saveToFile()` and `loadFromFile()` |
| Functions | `addExpense()`, `viewMonthlyExpenses()`, `viewCategoryTotals()`, `searchExpenses()`, `setBudget()`, `saveToFile()`, `loadFromFile()`, `showMenu()`, `validateDate()` |
| Input Validation | Date format check, amount > 0, menu range check |
| Arrays of structs | `Expense expenses[500]` |
| String functions | `strcpy`, `strcmp`, `strncmp`, `strstr`, `strtok` |

---

## 👨‍💻 Developed By

- **Name:** Mohit Ranjan
- **Register No:** 29mohitranjan10
- **Course:** DA1 — Digital Assignment
- **Institution:** VIT Chennai
