import subprocess
import os
import sys
import pkg_resources

REQUIRED_PACKAGES = [
    "SpeechRecognition",
    "google-genai",
    "pyserial",
    "psutil",
    "PyAudio"
]

def check_and_install_dependencies():
    print("[HOOK] Checking Python dependencies...")
    installed = {pkg.key for pkg in pkg_resources.working_set}
    missing = [pkg for pkg in REQUIRED_PACKAGES if pkg.replace('_', '-') not in installed]

    if missing:
        print(f"[HOOK] Missing: {missing}. Installing now...")
        # Uses the current Python interpreter to run pip
        subprocess.check_call([sys.executable, "-m", "pip", "install", *missing])
    else:
        print("[HOOK] All dependencies present.")

try:
    Import("env")

    # 1. Sync Header (Runs BEFORE compilation)
    def sync_header(source, target, item):
        print("\n[HOOK] Syncing Python COMMS to commands.h...")
        subprocess.run(["python", "scripts/SyncComms.py"])

    # 2. Launch Voice Assistant (Runs AFTER upload)
    def launch_assistant(source, target, env):
        check_and_install_dependencies()
        print("\n[HOOK] Upload successful. Starting Voice Assistant...")
        # 'start' command on Windows opens a new terminal window 
        # so PlatformIO can finish its process independently
        subprocess.Popen("cmd /c start cmd /k python scripts/VoiceAssistant.py", shell=True)

    env.AddPreAction("buildprog", sync_header)
    env.AddPostAction("upload", launch_assistant)
except NameError:
    print("Not running within PlatformIO environment. Hooks not set.")