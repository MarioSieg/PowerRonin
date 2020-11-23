import platform
import os.path
import sys
import subprocess

compiler_exe = "shaderc.exe" if platform.system() == "Windows" else "shaderc"
source_dir = "src/"
out_dir = "bin/"

if not os.path.isfile(compiler_exe):
    print("Shader compile executable \"" + compiler_exe + "\" not found!")
    sys.exit(-1)

subfolders = [ f.path for f in os.scandir(source_dir) if f.is_dir() ]
for dir in subfolders:
    vertex = os.path.join(dir, "vertex.shader")
    fragment = os.path.join(dir, "fragment.shader")
    variables_def = os.path.join(dir, "variables.shader")
    if not os.path.isfile(variables_def):
        print("Missing \"variables.shader\" definition file: " + variables_def)
        continue
    if not os.path.isdir("bin/" + os.path.basename(os.path.dirname(vertex))):
        os.mkdir("bin/" + os.path.basename(os.path.dirname(vertex)))
        os.mkdir("bin/" + os.path.basename(os.path.dirname(vertex)) + "/dx11")
        os.mkdir("bin/" + os.path.basename(os.path.dirname(vertex)) + "/glsl")
        os.mkdir("bin/" + os.path.basename(os.path.dirname(vertex)) + "/spirv")
        os.mkdir("bin/" + os.path.basename(os.path.dirname(vertex)) + "/metal")
    if os.path.isfile(vertex):
        # Vulkan:
        print("Compiling vertex shader for Vulkan...")
        cmd = compiler_exe + " -f " + vertex + " -o bin/" + os.path.basename(os.path.dirname(vertex)) + "/spirv/vertex.shc --platform linux -p spirv --varyingdef " + variables_def + " --type vertex"
        print(cmd)
        subprocess.call(cmd)

        # OpenGL:
        print("Compiling vertex shader for OpenGL...")
        cmd = compiler_exe + " -f " + vertex + " -o bin/" + os.path.basename(os.path.dirname(vertex)) + "/glsl/vertex.shc --platform linux --varyingdef "+ variables_def + " --type vertex"
        print(cmd)
        subprocess.call(cmd)

        if platform.system() == "Windows":
            # DX11/12:
            print("Compiling vertex shader for Direct3D11/12...")
            cmd = compiler_exe + " -f " + vertex + " -o bin/" + os.path.basename(os.path.dirname(vertex)) + "/dx11/vertex.shc --platform windows -p vs_5_0 --varyingdef " + variables_def + " --type vertex"
            print(cmd)
            subprocess.call(cmd)

        if platform.system() == "Darwin":
            # Metal:
            print("Compiling vertex shader for Metal...")
            cmd = compiler_exe + " -f " + vertex + " -o bin/" + os.path.basename(os.path.dirname(vertex)) + "/spirv/vertex.shc --platform osx -p metal --varyingdef " + variables_def + " --type vertex"
            subprocess.call(cmd)

    if os.path.isfile(fragment):
        # Vulkan:
        print("Compiling fragment shader for Vulkan...")
        cmd = compiler_exe + " -f " + fragment + " -o bin/" + os.path.basename(os.path.dirname(fragment)) + "/spirv/fragment.shc --platform linux -p spirv --varyingdef " + variables_def + " --type fragment"
        print(cmd)
        subprocess.call(cmd)

        # OpenGL:
        print("Compiling fragment shader for OpenGL...")
        cmd = compiler_exe + " -f " + fragment + " -o bin/" + os.path.basename(os.path.dirname(fragment)) + "/glsl/fragment.shc --platform linux --varyingdef " + variables_def + " --type fragment"
        print(cmd)
        subprocess.call(cmd)

        if platform.system() == "Windows":
            # DX11/12:
            print("Compiling fragment shader for Direct3D11/12...")
            cmd = compiler_exe + " -f " + fragment + " -o bin/" + os.path.basename(os.path.dirname(fragment)) + "/dx11/fragment.shc --platform windows -p ps_5_0 --varyingdef " + variables_def + " --type fragment"
            print(cmd)
            subprocess.call(cmd)

        print("Compiling fragment shader for Metal...")
        if platform.system() == "Darwin":
            # Metal:
            cmd = compiler_exe + " -f " + fragment + " -o bin/" + os.path.basename(os.path.dirname(fragment)) + "/spirv/fragment.shc --platform osx -p metal --varyingdef " + variables_def + " --type fragment"
            print(cmd)
            subprocess.call(cmd)
