# Recipypes

Recipypes is a ritualized build and package system that unifies **compilation**, **compression**, and **environment management** across Python and C++.

## 🔑 Features
- **Cook (C++)** → Compiles sources and compresses binaries/packages with dynamic ratios:
  - 3:1 → desktops
  - 10:1 → x86 systems with ≥16 GB RAM
  - 50:1 → server-scale systems with ≥64 GB RAM
- **Buy (Python)** → Fetches PyPI packages and hands off large tarballs/wheels to the C++ compressor.
- **Follow (Python)** → Creates environments and records Python interpreter versions for reproducibility.
- **Sort (Python)** → Harmonizes Python versions across environments by scanning manifests.

## ⚙️ Build Instructions
```bash
make recipypes_cook

Or manually:
