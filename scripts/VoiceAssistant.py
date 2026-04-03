import speech_recognition as sr
import serial
import time
import json
from google import genai
from SyncComms import COMMS

GEMINI_API_KEY = open("API_KEY").read().strip()

# Context for AI model
available_commands = ", ".join(COMMS.keys())
context = f"""
You are a home automation controller. Your output must always be a JSON object.
Available Commands: {available_commands}.

If the user input matches a command intent, return: {{"type": "command", "value": "COMMAND_NAME"}}
If the user input matches a command intent with a parameter, return: {{"type": "commandP", "value": "COMMAND_NAME", "parameter": "PARAMETER_VALUE"}}
If the user is chatting, return: {{"type": "chat", "value": "30-character response"}}

-for time-based commands, the parameter will be a duration in seconds (e.g., "Set a reminder for 10 minutes" -> parameter: "600")
-for parameter-based commands, the parameter will be a string (e.g., "Set the temperature to 22 degrees" -> parameter: "22")
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
    JSON = json.loads(response)
    print(f"Parsed JSON: {JSON}")
    if JSON["type"] == "command":
        arduino.write(bytes(COMMS[JSON["value"]][0] + "\n", 'utf-8'))
    elif JSON["type"] == "commandP":
        arduino.write(bytes(COMMS[JSON["value"]][0] + "\n", 'utf-8'))
        time.sleep(0.5)  # Short delay to ensure command is processed
        arduino.write(bytes(JSON["parameter"] + "\n", 'utf-8'))
    else:
        arduino.write(bytes(JSON["value"] + "\n", 'utf-8'))


# Arduino setup - serial connection & header sync
rec = sr.Recognizer()
arduino  = serial.Serial('COM3', 9600, timeout=1)
# print("Connecting to Arduino...")
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
        except sr.UnknownValueError:
            print("Sorry, I could not understand the audio.")
        except sr.RequestError as e:
            print(f"Error with Google API: {e}")