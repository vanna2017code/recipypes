# Recipypes

Recipypes is a ritualized build and package system that unifies **compilation**, **compression**, and **environment management** across Python and C++.

[![Static Badge](https://img.shields.io/badge/gitter-chat-green?logo=gitter&color=green)](https://matrix.to/#/#recipypes:gitter.im)


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
```
Or manually:
```bash
g++ -O2 -lz -o recipypes_cook recipypes_cook.cpp
```
Requires zlib.
## Usage
```bash
recipypes cook <app_name>
recipypes buy <package>
recipypes follow <environment_name>
recipypes sort
```
## 🤝 Contribs
We welcome contributions!  
1. Fork the repo  
2. Create a new branch (`git checkout -b feature/my-feature`)  
3. Commit your changes (`git commit -m "Add my feature"`)  
4. Push to your fork (`git push origin feature/my-feature`)  
5. Open a Pull Request  

Join the [Gitter room](https://gitter.im/vanna2017code/recipypes) to discuss ideas and get feedback in real time.
