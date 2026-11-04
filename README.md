# AI Home Assistant

## Overview
The AI Home Assistant is a voice-controlled automation system that bridges natural language processing with embedded hardware control. It utilizes a Python backend integrated with the Google Gemini API to classify spoken audio into structured JSON commands. These commands are dynamically routed either as conversational responses or hardware directives to an Arduino-based microcontroller.

## System Architecture

The project is divided into two primary components synchronized via an automated build pipeline:

### 1. Software Backend (Python)
* **Voice Processing & NLU:** Captures spoken audio and leverages the Google Gemini API for intent classification and entity extraction.
* **Command Routing:** Parses the API output into structured JSON and serializes the data for transmission to the microcontroller over a serial interface.

### 2. Firmware (Arduino C++ / PlatformIO)
* **Hardware Execution:** Receives serial directives from the Python backend and translates them into actionable hardware states.
* **Appliance Management:** Drives raw IR (Infrared) signal transmissions to control standard household appliances.
* **User Interface:** Renders conversational AI text output and system states on an I2C OLED display.

### 3. Automated Protocol Synchronization
To maintain parity between the Python backend and the C++ firmware, the project utilizes automated PlatformIO build hooks (`pio_hooks.py` / `SyncComms.py`). Prior to compilation, these scripts auto-generate shared C++ headers (`commands.h`), ensuring that communication protocols and command IDs are strictly synchronized across both environments without manual intervention.

## Repository Structure

```text
├── include/                 # Project header files
├── lib/                     # Custom C++ libraries (e.g., HomeAssistant)
│   ├── commands.h           # Auto-generated shared protocol header
│   └── HomeAssistant.h      # Core microcontroller logic header
├── scripts/                 # Python backend and build scripts
│   ├── VoiceAssistant.py    # Main voice capture and Gemini API interface
│   ├── SyncComms.py         # Protocol synchronization logic
│   └── pio_hooks.py         # PlatformIO pre-build integration
├── src/                     # C++ source files
│   ├── main.cpp             # Firmware entry point
│   └── HomeAssistant.cpp    # Core microcontroller logic implementation
└── platformio.ini           # PlatformIO project configuration
```

## Hardware Requirements
* Arduino-compatible microcontroller
* I2C OLED Display
* IR Transmitter Module
* Microphone (for backend audio capture)

## Setup & Installation

### Firmware Deployment
1. Install [PlatformIO](https://platformio.org/).
2. Open the project directory in your PlatformIO-enabled IDE (e.g., VS Code).
3. The pre-build hooks will automatically execute `SyncComms.py` to generate `commands.h`.
4. Build and upload the firmware to your microcontroller:
   ```bash
   pio run --target upload
   ```

### Backend Initialization
1. Ensure Python 3.10+ is installed.
2. Navigate to the `scripts/` directory and install the required dependencies (e.g., serial, audio processing, and Gemini API libraries).
3. Export your Google Gemini API key as an environment variable.
4. Execute the voice assistant:
   ```bash
   python scripts/VoiceAssistant.py
   ```
