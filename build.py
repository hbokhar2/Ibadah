import sys
import pathlib
import subprocess

args = sys.argv[1:]

project_root = pathlib.Path(__file__).parent
cmake_path = project_root / "HorrorGameCXX" / "Dev" 
source_path = project_root / "HorrorGameCXX" / "Dev" 
build_path = project_root/ "HorrorGameCXX" / "Build"

build_path.mkdir(exist = True)

subprocess.run(["cmake", "-S", str(source_path), "-B", str(build_path)], check=True)
subprocess.run(["cmake", "-S", str(source_path), "-B", str(build_path)], check=True)
