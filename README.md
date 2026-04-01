# push_swap

*This project has been created as part of the 42 curriculum by ramarti2.*

---

## 📖 Description

**push_swap** is an algorithmic project from the 42 curriculum focused on sorting data efficiently using a limited set of stack operations.

The objective is to sort a list of integers using two stacks (**a** and **b**) and a predefined set of instructions, while minimizing the number of operations. This project emphasizes algorithm design, optimization, and complexity analysis.

You must implement a program that outputs the smallest possible sequence of operations to sort the input list.

---

## ⚙️ Instructions

### 🛠️ Compilation

To compile the project:

```bash
make
```

This will generate the executable:

```bash
./push_swap
```

---

### ▶️ Usage

Run the program with a list of integers as arguments:

```bash
./push_swap 4 67 3 87 23
```

The program will output a sequence of instructions that sort the numbers.

[!] Warning: It is recommended that the list doesn't exceed 500 integers or else it will be a lot slower. This project was evaluated at 500 integers maximum.
---

### 🔁 Available Operations

You must only use the following stack operations on stacks a and b:

#### swaps:
* **sa** — swap the two elements at the top of a
* **sb** — swap the two elements at the top of b
* **ss** — sa and sb at the same time

#### pushes:
* **pa** — "push to a" (push the element at the top of b to the top of a)
* **pb** — "push to b" (push the element at the top of a to the top of b)

#### rotations:
* **ra** — rotate a (shift up all elements of a by 1)
* **rb** — rotate b (shift up all elements of b by 1)
* **rr** - ra and rb at the same time

#### reverse rotations:
* **rra** — reverse rotate a (shift down all elements of stack a by 1)
* **rrb** — reverse rotate b (shift down all elements of stack b by 1)
* **rrr** — rra and rrb at the same time

---

### ✅ Checking Your Solution

You can verify your program using the `checker` at the root of the repository (checker_linux for linux and checker_Mac for MacOS).

```bash
ARG="4 67 3 87 23"; ./push_swap $ARG | ./checker $ARG
```

Expected output:

```
OK
```
#### Alternative way to check:

Use the push-swap visualizer.

Link: https://push-swap42-visualizer.vercel.app/

Here you can generate or paste in your own list of numbers, paste in the instructions push_swap generates for it, and see visually how your stack gets sorted using these movements!
---

### 📊 Performance Requirements

This project was evaluated based on the number of operations:
* **3 numbers** → should be sorted in 0-3 operations
* **5 numbers** → should be sorted in less than 12 operations
* **100 numbers** → should be sorted in fewer than ~700 operations
* **500 numbers** → should be sorted in fewer than ~5500 operations

(In most cases, these thresholds are met but there might still be a chance it goes over the threshold. I'm not sure)

---

## 🧠 Algorithm Strategy

In this project, you are allowed to choose your own algorithm that uses the required moves.  I made my own implementation of the Turkish Algorithm explained here:

https://medium.com/@ayogun/push-swap-c1f5d2d41e97

In short, the algorithm starts by pushing the first two elements of a to b.  

Then for each element of a, you calculate the number of moves required to push it so that it lies right above the the largest number in stack b that is less than it or, if there is none, above the largest number in b.

You push the "cheapest" number to b.

After doing this several times, eventually you will end up with 3 numbers in stack a.  These are sorted and then all the elements of stack b get pushed back to their correct positions in stack a (so stack a may need to be rotated before you push an element of b back to it).

Implementing this algorithm requires you to figure out the logic of calculating costs, which could require keeping track of values such as the number and type of rotations you want to do, the positions of the nodes on the stack, indices, target nodes on the opposite stack, etc.

---

## 🛠️ Features

* Handles multiple input formats (quoted or space-separated)
* Input validation (no duplicates, valid integers)
* Efficient sorting algorithms for different input sizes (different algortithms for 2, 3, 4 and >= 5 elements)
* Error handling (`Error` message for invalid input)

---

## 🚀 Example

```bash
./push_swap 3 2 1
```

Output:

```
sa
rra
```

---

## ⚠️ Error Handling

The program must return:

```
Error
```

In cases such as:

* Non-integer arguments
* Duplicate numbers
* Overflow or invalid input

---

## 🧾 Final Notes

push_swap is a key project for developing problem-solving and optimization skills. The focus is not just to sort, but to do it **efficiently** with limited tools.
