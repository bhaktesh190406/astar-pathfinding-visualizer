# 🧠 A* Pathfinding Visualizer (C + Python)

A visual implementation of the **A* (A-Star) Algorithm** using a **C backend for performance** and a **Python (Pygame) frontend** for interactive visualization.

---

## 🚀 Features

* ✅ A* Algorithm (g + h = f)
* 🎮 Interactive grid (20×20)
* 🖱️ Left-click to add obstacles
* 🖱️ Right-click to remove obstacles
* 🟢 Start node (Green)
* 🔴 End node (Red)
* 🔵 Path visualization (Blue)
* ❌ Detects "No Path Found"
* ⚡ Fast execution using C (via ctypes)

---

## 🛠️ Tech Stack

* **C** → A* Algorithm logic
* **Python** → Visualization
* **Pygame** → UI rendering
* **ctypes** → C–Python integration

---

## 📂 Project Structure

```
Astar-Visualizer/
│
├── astar.c          # A* algorithm (C)
├── astar.dll        # Compiled shared library
├── main.py          # Python visualizer
└── README.md
```

---

## ⚙️ Setup Instructions

### 1. Compile C Code

```bash
gcc -shared -o astar.dll -fPIC astar.c
```

---

### 2. Install Python Dependencies

```bash
pip install pygame numpy
```

---

### 3. Run the Visualizer

```bash
python main.py
```

---

## 🎮 Controls

| Action          | Input       |
| --------------- | ----------- |
| Add obstacle    | Left Click  |
| Remove obstacle | Right Click |
| Run A*          | SPACE       |
| Clear grid      | C           |

---

## 🧠 Algorithm Overview

The A* algorithm finds the shortest path using:

* **g(n)** → Cost from start to current node
* **h(n)** → Heuristic (Manhattan distance)
* **f(n) = g(n) + h(n)**

It ensures:

* Optimal path (if heuristic is admissible)
* Efficient search using priority selection

---

## 📸 Visualization

* 🟩 Start Node
* 🟥 End Node
* ⬛ Obstacles
* 🟦 Final Path

---

## ⚠️ Limitations

* Grid size is fixed (20×20)
* Uses array instead of priority queue (can be optimized)
* No diagonal movement (4-directional only)

---

## 🚀 Future Improvements

* 🎯 Drag start/end nodes
* ↘️ Diagonal movement (8-direction)
* ⚡ Priority Queue (Min Heap)
* 🌈 Open/Closed set visualization
* 🧠 Real-time pathfinding

---

## 🤝 Contributing

Feel free to fork this repo and improve:

* Performance
* UI/UX
* Algorithm enhancements

---

## 📌 Author

**Bhaktesh Chandajkar**

---

## ⭐ If you like this project

Give it a ⭐ on GitHub and share!

---
