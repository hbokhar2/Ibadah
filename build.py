import sys
import os
import subprocess

def getPaths() -> list[str]:

    projectRoot = os.getenv("IBADAH")
    projectCXXPath = projectRoot + "/IbadahCXX"
    cmakePath = projectRoot + "/IbadahCXX/Build"
    gdBinPath = projectRoot + "/IbadahGD/Bin" 

    return projectRoot, projectCXXPath, cmakePath, gdBinPath

def cmakeBuild(projectCXXPath, cmakePath) -> bool:

    try:
        buildSystemResult = subprocess.run(["cmake", "-B", cmakePath, "-S", (projectCXXPath + "/Dev")])
        buildResult = subprocess.run(["cmake", "--build", cmakePath, "-j", "20"])
        return True
    except:
        print("Failed to build project.")
        return False

def copySrcToGD(cmakePath, gdBinPath):

    try:
        rmResult = subprocess.run(["rm", "-rf", (gdBinpath + "/libIbadah.so")])
    except:
        try:
            cpResult = subprocess.run(["cp", (cmakePath + "/libIbadah.so"), gdBinPath])
            return True;
        except:
            print("Failed to copy over binary to Godot.")
            return False;

projectRoot, projectCXXPath, cmakePath, gdBinPath = getPaths()

cmakeBuild(projectCXXPath, cmakePath)

copySrcToGD(cmakePath, gdBinPath)
