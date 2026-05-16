import argparse
import urllib.request
import json
import os
import subprocess

THRESHOLD = 2.5 * (1024**3)  # 2.5 GB

def buy(packages):
    os.makedirs("ingredients", exist_ok=True)
    for pkg in packages:
        url = f"https://pypi.org/pypi/{pkg}/json"
        print(f"Fetching metadata for {pkg} from {url}")
        with urllib.request.urlopen(url) as resp:
            data = json.load(resp)

        latest = data["info"]["version"]
        tarball = data["urls"][0]["url"]
        filename = os.path.join("ingredients", os.path.basename(tarball))

        print(f"Downloading {pkg}=={latest} → {filename}")
        urllib.request.urlretrieve(tarball, filename)

        if os.path.getsize(filename) > THRESHOLD:
            print("Handing off to C++ compressor...")
            subprocess.run(["./recipypes_cook", filename])

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("packages", nargs="+")
    args = parser.parse_args()
    buy(args.packages)
