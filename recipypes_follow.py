import sys
import os

def follow(env_name):
    os.makedirs(env_name, exist_ok=True)
    py_version = f"{sys.version_info.major}.{sys.version_info.minor}.{sys.version_info.micro}"
    manifest = os.path.join(env_name, "manifest.txt")
    with open(manifest, "w") as f:
        f.write(f"Python version: {py_version}\n")
    print(f"Environment {env_name} initialized with Python {py_version}")
