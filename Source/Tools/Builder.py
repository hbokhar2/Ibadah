import sys
import subprocess
import shutil
from pathlib import Path


def get_paths() -> tuple[Path, Path, Path]:
    """
    Returns: project root, cxx dir, gd dir, and build dir.
    """
    ibadah_root_path = Path(__file__).resolve().parents[2]

    ibadah_cxx_path = ibadah_root_path / "Source"
    ibadah_build_path = (ibadah_cxx_path.resolve().parents[0]) / "Build"

    return ibadah_root_path, ibadah_cxx_path, ibadah_build_path


def cmake_generate_build_system(ibadah_cxx_path: Path, ibadah_build_path: Path) -> bool:
    try:
        result = subprocess.run(
            ["cmake", "-B", str(ibadah_build_path), "-S", str(ibadah_cxx_path)],
            check = True  
        )
        return True
        
    except FileNotFoundError:
        print("[ERROR] CMake could not be found. Is CMake installed?")
        return False
        
    except subprocess.CalledProcessError as e:
        print(f"CMake generation failed with exit code {e.returncode}.")
        return False


def cmake_build(ibadah_build_path: Path) -> bool:
    try:
        result = subprocess.run(
            ["cmake", "--build", str(ibadah_build_path), "--parallel", "50"],
            check = True
        )

        return True

    except FileNotFoundError:
        print("[ERROR] CMake could not be found. Is CMake installed?")
        return False

    except subprocess.CalledProcessError as e:
        print(f"CMake build failed with exit code {e.returncode}.")
        return False


def cmake_clean(ibadah_build_path: Path):
    try:
        shutil.rmtree(ibadah_build_path)

    except OSError as e:
        print(f"[ERROR] {e.strerror}.")
        print("Skipping clean...")


if __name__ == "__main__":
    if len(sys.argv) > 1:
        command = sys.argv[1]
    else:
        print("[ERROR] No command provided.")
        print("Use options like: clean, build, generate, all")
        sys.exit(1)

    ibadah_root_path, ibadah_cxx_path, ibadah_build_path = get_paths()

    if not all(p.exists() for p in (ibadah_root_path, ibadah_cxx_path)):
        print("[ERROR] Could not find project paths.")
        sys.exit(1)

    valid_commands = {"clean", "generate", "build", "all"}
    if str(command) not in valid_commands:
        print(f"[ERROR] Unknown command: {command}")
        print("Use options like: clean, build, generate, all")
        sys.exit(1)

    if str(command) == "clean":
        ok = cmake_clean(ibadah_build_path)
        if not ok:
            sys.exit(1)

    if str(command) == "generate":
        ok = cmake_generate_build_system(ibadah_cxx_path, ibadah_build_path)
        if not ok:
            sys.exit(1)

    if str(command) == "build":
        ok = cmake_build(ibadah_build_path)
        if not ok:
            sys.exit(1)

    if str(command) == "all":
        if ibadah_build_path.exists():
            cmake_clean(ibadah_build_path)

        ok = cmake_generate_build_system(ibadah_cxx_path, ibadah_build_path)
        ok = cmake_build(ibadah_build_path)

        print("Done building!")
