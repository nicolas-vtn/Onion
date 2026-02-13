# Onion

A **C++ playground workspace using CMake**.

This repository is structured as a modular C++ monorepo where:

* `libs/` contains reusable internal libraries
* `projects/` contains executable applications
* `docs/` contains documentation
* `out/` contains generated build files (not versioned)

---

## Structure

```
.
├── libs/        # Reusable internal libraries
├── projects/    # Applications and executables
├── docs/        # Documentation
├── out/         # Build output (generated)
└── CMakeLists.txt
```

---

## Current Modules

### Libraries

* **datetime**
  Basic date/time utilities.

### Projects

* **helloword**
  Minimal example executable using the workspace structure.

---

## Design Goals

* Modern C++ (C++20+)
* Modular architecture
* Clear dependency flow
* Scalable workspace for multiple independent projects

---

## Future Direction

This workspace is intended to host:

* Game experiments
* Networking modules
* Rendering experiments
* Desktop tools
* Systems-level C++ utilities

The structure is designed to scale cleanly as the number of projects grows.