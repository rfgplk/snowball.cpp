#!/usr/bin/env python3
import os
import subprocess

directory = "./bin/rigor"  

for filename in os.listdir(directory):
    path = os.path.join(directory, filename)
    if os.path.isfile(path) and os.access(path, os.X_OK):
        try:
            result = subprocess.run([path], capture_output=True)
            ret = result.returncode
            if ret == 0 or ret == 1:
                print(f"{filename}: PASS (returned {ret})")
            else:
                print(f"{filename}: FAIL (returned {ret})")
        except Exception as e:
            print(f"{filename}: ERROR ({e})")
