import os

def sort_envs(base_dir="."):
    manifests = []
    for root, dirs, files in os.walk(base_dir):
        for f in files:
            if f == "manifest.txt":
                path = os.path.join(root, f)
                with open(path) as mf:
                    version = mf.read().strip()
                manifests.append((root, version))

    print("Environment summary:")
    for env, version in manifests:
        print(f"{env}: {version}")
