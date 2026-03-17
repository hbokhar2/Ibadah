import sys
import platform
import os
import subprocess
import shutil
from pathlib import Path

def getPaths(command: str) -> tuple[bool, Path | None, Path | None, Path | None, Path | None]:

    envVal = os.getenv("IBADAH")

    if not envVal:
        print("Path variable, IBADAH, is not set")
        return False, None, None, None, None

    projectRoot = Path(envVal)

    projectCXXPath = projectRoot / "IbadahCXX"
    buildPath = projectRoot / "IbadahCXX" / "Build"
    gdBinPath = projectRoot / "IbadahGD" / "Bin"

    if command == "cleanbuild" and os.path.isdir(buildPath):
        shutil.rmtree(buildPath)

    if not os.path.isdir(buildPath):
        try:
            buildPath.mkdir(parents = True, exist_ok = True)
        except OSError as e:
            print(f"Failed to make build directory: {e}")
            return False, None, None, None, None

    return True, projectRoot, projectCXXPath, buildPath, gdBinPath

def cmakeBuild(projectCXXPath: Path, buildPath: Path) -> bool:

    #Need to enforce "Unix Makefiles" build system on Windows."

    try:
        buildSystemResult = subprocess.run(["cmake", "-B", buildPath, "-S", (projectCXXPath / "Dev")], check = True)
        buildResult = subprocess.run(["cmake", "--build", buildPath, "-j", "20"], check = True)
        return True
    except subprocess.CalledProcessError as e:
        print(f"Failed to build project. {e.returncode}")
        return False
    except FileNotFoundError:
        print("'cmake' command not found. Please install CMake.")
        return False

def copySrcToGD(buildPath: Path, gdBinPath: Path) -> bool:

    system = platform.system()

    if system == "Windows":
        libName = "Ibadah.dll"
    elif system == "Darwin":
        libName = "libIbadah.dylib"
    else:
        libName = "libIbadah.so"

    try:
        print(f"Copying {libname} to {gdBinPath}...")
        shutil.copy((buildPath / libName), gdBinPath)
        return True
    except Exception as e:
        print(f"Failed to copy binary: {e}")
        return False

if __name__ == "__main__":

    command = sys.argv[1] if len(sys.argv) > 1 else ""

    pathSuccess, projectRoot, projectCXXPath, buildPath, gdBinPath = getPaths(command)

    if not projectRoot or not projectCXXPath or not buildPath or not gdBinPath:
        print("Build failed :(")
        sys.exit(1)

    buildSuccess = cmakeBuild(projectCXXPath, buildPath)

    copySuccess = copySrcToGD(buildPath, gdBinPath)

    if pathSuccess and buildSuccess and copySuccess:
        print("Build successful :) !")
    else:
        print("Build failed :(")
