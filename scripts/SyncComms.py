# Command definitions
COMMS ={
    # name : (code, description)
    "LIGHTS_ON":  ("L1", "Turns the room lights on"),
    "LIGHTS_OFF": ("L0", "Turns the room lights off"),
    "TV_ON":      ("T1", "Powers on the television"),
    "TV_OFF":     ("T0", "Powers off the television"),
    "GET_TEMP":   ("GT", "Reads the current room temperature"),
    "SET_TEMP":   ("ST", "Sets the desired room temperature by turning opn the AC"),    #!!TODO!!
    "WEATHER":    ("WH", "Gets the current weather information for the location"),      #!!TODO!!
    "REMINDER":   ("RE", "Sets a reminder for the user at a specified time"),           #!!TODO!!
    "OPEN_APP":   ("OA", "Opens a specified application on the user's computer")        #!!TODO!!
}

# Header for Arduino code - AUTO-GENERATED
def sync_arduino_header(path="lib/commands.h"):
    with open(path, "w") as f:
        f.write("// !!AUTO-GENERATED \n#pragma once\n\n")
        for name, (code, desc) in COMMS.items():
            line_content = f'#define {name} "{code}"'
            formatted_line = f"{line_content.ljust(25)} // {desc}\n"
            f.write(formatted_line)
    print(f"Arduino header '{path}' created")


if __name__ == "__main__":
    sync_arduino_header()