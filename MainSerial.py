import speech_recognition as sr

rec = sr.Recognizer()

with sr.Microphone(device_index= 2) as source:
    rec.adjust_for_ambient_noise(source, duration=2)
    rec.dynamic_energy_threshold = True
    rec.pause_threshold = 1.5
    print("Setup done!")
    while (1):
        try: 
            audio = rec.listen(source)
            msg =  rec.recognize_google(audio, language="ro-RO")
            print(msg)
        except sr.UnknownValueError:
            print("Sorry, I could not understand the audio.")
        except sr.RequestError as e:
            print(f"Error with Google API: {e}")