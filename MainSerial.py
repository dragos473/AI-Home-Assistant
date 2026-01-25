import speech_recognition as sr
import serial
import time
from google import genai
GEMINI_API_KEY = "AIzaSyAbNjVk6DtIv5Yjf6tNtfikxus9Cthdbfo"

rec = sr.Recognizer()
arduino  = serial.Serial('COM3', 9600, timeout=1)
time.sleep(2)
client = genai.Client(api_key=GEMINI_API_KEY)

with sr.Microphone(device_index= 2) as source:
    rec.adjust_for_ambient_noise(source, duration=2)
    rec.dynamic_energy_threshold = True
    rec.pause_threshold = 0.8
    print("Setup done!")
    while (1):
        try: 
            audio = rec.listen(source)
            prompt =  rec.recognize_google(audio, language="en-US")
            msg = client.models.generate_content(model = "gemini-2.5-flash-lite", contents = "Respond in exactly 30 characters." + prompt).text
            arduino.write(bytes(msg, 'utf-8'))
        except sr.UnknownValueError:
            print("Sorry, I could not understand the audio.")
        except sr.RequestError as e:
            print(f"Error with Google API: {e}")