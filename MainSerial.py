import speech_recognition as sr
import serial
import time
import json
from google import genai

GEMINI_API_KEY = ""

# Command definitions
COMMS ={
    # name : (code, description)
    "LIGHTS_ON":  ("L1", "Turns the room lights on"),
    "LIGHTS_OFF": ("L0", "Turns the room lights off"),
    "TV_ON":      ("T1", "Powers on the television"),
    "TV_OFF":     ("T0", "Powers off the television"),
}

# Header for Arduino code - AUTO-GENERATED
def sync_arduino_header(path="commands.h"):
    with open(path, "w") as f:
        f.write("// !!AUTO-GENERATED \n#pragma once\n\n")
        for name, (code, _) in COMMS.items():
            f.write(f'#define CMD_{name} "{code}"\n')
    print(f"Arduino header '{path}' created")

# Context for AI model
available_commands = ", ".join(COMMS.keys())
context = f"""
You are a home automation controller. Your output must always be a JSON object.
Available Commands: {available_commands}.

If the user input matches a command intent, return: {{"type": "command", "value": "COMMAND_NAME"}}
If the user is chatting, return: {{"type": "chat", "value": "30-character response"}}
"""

def compute_response(user_input):
    prompt = f"\nUser Input: {user_input}\n"
    response = client.models.generate_content(
        model="gemini-2.5-flash-lite",
        config = {
            "system_instruction" : context,
            "response_mime_type" : "application/json",
        },
        contents=prompt
    ).text
    print(f"AI Response: {response}")

# Arduino setup - serial connection & header sync
sync_arduino_header()
rec = sr.Recognizer()
arduino  = serial.Serial('COM3', 9600, timeout=1)
print("Connecting to Arduino...")
time.sleep(2)
print("Arduino connected")
client = genai.Client(api_key=GEMINI_API_KEY)

with sr.Microphone(device_index= 2) as source:
    # Audio setup - adjust for ambient noise
    rec.adjust_for_ambient_noise(source, duration=2)
    rec.dynamic_energy_threshold = True
    rec.pause_threshold = 0.8
    print("Audio setup done!")
    while True:
        try: 
            audio = rec.listen(source)
            input =  rec.recognize_google(audio, language="en-US").lower()
            compute_response(input)
            # msg = client.models.generate_content(model = "gemini-2.5-flash-lite", contents = "Respond in 30 characters or less." + input).text
            # arduino.write(bytes(msg, 'utf-8'))
        except sr.UnknownValueError:
            print("Sorry, I could not understand the audio.")
        except sr.RequestError as e:
            print(f"Error with Google API: {e}")