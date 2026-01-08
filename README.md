
# Random Password Generator and Analyzer
This project is a Password Generator and Security Analyzer that helps users create strong passwords, check their strength, estimate cracking time, and get security tips.

Target Users:   Anyone wanting to improve password security and understand password strength is a target user of this application

# **Password Security Analyzer & Generator** 

## **Project Overview**
A comprehensive C++ console application that analyzes, generates, and evaluates password security using mathematical combinatorics. This tool demonstrates real-world applications of discrete mathematics in cybersecurity.

**Course:** Discrete Mathematics  
**Developer:** [Abeera Arfan and Huda Yasin]  
**Date:** [4th January 2026]

---

##  **Features**
-  **Password Generation** – Create secure passwords
-  **Security Analysis** – Calculate entropy & cracking time
-  **Brute-force Simulation** – Educational cracking demonstration
-  **Combinatorial Math** – nPr & nCr calculators
-  **Interactive Reports** – Detailed security assessments

# **Getting Started**

# **Prerequisites**
```bash
# Windows with MinGW or Visual Studio
# C++11 or higher
```

### **Compilation**
```bash
g++ -o password_analyzer main.cpp -std=c++11
password_analyzer.exe
```

---

## **Usage**

### **Sample Output**
=== QUICK PASSWORD ANALYSIS ===
Password: MyP@ssw0rd!
Length: 11 characters
Entropy: 68.2 bits
Strength: Strong
Time to crack: 1.5 million years
```

### **Menu Options**
1. Generate Strong Password
2. Create Custom Password
3. Calculate Password Entropy
4. Estimate Cracking Time
5. Quick Password Analysis
6. Brute-force Math Verification
7. Brute-force Crack Simulation
8. Permutations Calculator (nPr)
9. Combinations Calculator (nCr)
10. Generate Security Report
11. Get Security Tips
0. Exit

---

## **Technical Details**

### **Mathematical Formulas**
- **Entropy**: `H = L × log₂(C)` (bits)
- **Permutations**: `P(n,r) = n!/(n-r)!`
- **Combinations**: `C(n,r) = n!/(r!(n-r)!)`

### **Character Sets**
| Type | Size | Example |
|------|------|---------|
| Lowercase | 26 | a-z |
| Uppercase | 26 | A-Z |
| Digits | 10 | 0-9 |
| Symbols | 33 | !@#$%^&*()... |

### **Strength Classification**
| Entropy | Strength | Color |
|---------|----------|-------|
| < 28 | Very Weak | 🔴 |
| 28-35 | Weak | 🔴 |
| 36-59 | Moderate | 🟡 |
| 60-79 | Strong | 🟢 |
| ≥ 80 | Very Strong | 🔵 |

---

## **Project Structure**
```
Password-Security-Analyzer/
├── main.cpp              # Main source code (1000+ lines)
├── README.md             # This documentation
├── password_analyzer.exe # Compiled executable
└── screenshots/          # Program screenshots
```

---

## **Learning Outcomes**
1. Apply combinatorial mathematics to security problems
2. Understand password entropy and its importance
3. Analyze algorithm time complexity (O(C^L))
4. Implement mathematical models in C++
5. Present technical information effectively

---

## **Important Notes**
- **Educational tool only** – Not for real password cracking
- **Windows dependency** – Uses Windows.h for colors
- **Simplified model** – Assumes 10⁷ attempts/second
- **No dictionary attacks** – Pure brute-force simulation only
## **Academic Context**
This project demonstrates:
- Counting techniques (Rosen Chapter 6)
- Probability calculations (Rosen Chapter 7)
- Algorithm analysis (Rosen Chapter 3)
- Information theory applications

---

## **Ethical Use Statement**
> **FOR EDUCATIONAL PURPOSES ONLY** – This tool is part of a Discrete Mathematics course project. Never use for unauthorized access or real password cracking.

---

## **Developer Information**
**Name:** [Abeera Arfan and Huda Yasin]  
**Student ID:** [2025-CS-29 and 2025-CS-46]  
**Course:** [CSC101-Discrete Mathematics]  
**Instructor:** [Sir Waqas Ali]  
**Submission Date:** [4th January 2026]  

---
