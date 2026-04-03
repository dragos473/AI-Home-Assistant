# AI Home Assistant – Voice-Controlled Room Automation

A voice-controlled home automation system that combines an Arduino microcontroller with a Python-powered AI backend. Speak a command, and Gemini interprets the intent, dispatches it over serial, and the Arduino executes it — whether that's toggling a TV via IR, reading room temperature, or displaying a conversational response on an OLED screen.

## 🚀 Key Features

**Voice-to-Action Pipeline:** Captures voice input via microphone, transcribes it with Google Speech Recognition, and routes it through Gemini 2.5 Flash Lite to classify intent as either a device command or a conversational reply.

**IR Device Control:** Sends raw IR signals to power a TV on/off using a captured TCL power code. The system tracks device state to prevent redundant toggles.

**Environment Monitoring:** Reads real-time temperature and humidity from a DHT11 sensor and displays formatted readings on command.

**OLED Typewriter Display:** All responses — AI chat replies, sensor readings, status messages — are rendered on a 128x64 OLED with a character-by-character typewriter animation and automatic line wrapping.

**Synced Command Protocol:** A single Python dictionary (`SyncComms.py`) acts as the source of truth for all command codes. A build hook auto-generates the corresponding C++ header before every compilation, eliminating protocol drift between the two layers.

**Zero-Setup Build Hooks:** PlatformIO pre-build and post-upload hooks handle everything automatically — syncing the command header, installing Python dependencies, and launching the Voice Assistant in a separate terminal after flashing.

## 🛠 Technical Stack

**Hardware:** Arduino, IR LED (38kHz), DHT11 Sensor, SH1106 128x64 OLED (I2C)

**Firmware:** C++ / PlatformIO (IRremote, U8g2, DHT11)

**Backend:** Python (SpeechRecognition, Google Gemini API, PySerial)

**Communication:** Serial (9600 baud) with a shared auto-generated command protocol
