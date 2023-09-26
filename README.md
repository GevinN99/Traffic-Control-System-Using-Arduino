# Traffic Control System README

This project implements a traffic control system using Arduino. The system manages vehicle and pedestrian traffic at an intersection with traffic lights, ultrasonic sensors, and a boom gate for a car park. Below is a detailed explanation of the project components, code, and operation.

## Table of Contents

- [Components](#components)
- [Code Structure](#code-structure)
- [Installation](#installation)
- [Usage](#usage)
- [Operation](#operation)
- [Contributing](#contributing)
- [License](#license)

## Components

### Traffic Light Control

- Main road traffic light with red and green LEDs.
- Pedestrian traffic light with red and green LEDs.
- Car park traffic light with red and green LEDs.
- Buzzer for audio signaling.

### Ultrasonic Sensors

- Main road vehicle detection sensor.
- Entry gate vehicle detection sensor.
- Exit gate vehicle detection sensor.

### Boom Gate Motors

- Entry gate motor with two control pins.
- Exit gate motor with two control pins.

### Pedestrian Button

- A push button to request a pedestrian crossing.

## Code Structure

The Arduino code provided manages the traffic control system. Here's an overview of the code structure:

- **Sensor Initialization:** Pins for ultrasonic sensors and traffic lights are defined and configured in the `setup()` function.

- **Main Loop:** The `loop()` function continually reads sensor values, monitors the state of the pedestrian button, and controls traffic lights and boom gates based on sensor data and user input.

- **Ultrasonic Sensor Function:** The `UltrasonicSensor()` function calculates distances using ultrasonic sensors and updates the `distance` variable.

- **Initial State Function:** The `InitialState()` function sets the initial state of all components, including traffic lights, boom gates, and the buzzer.

- **Boom Gate Motor Control Functions:** There are several functions for controlling boom gate motors. The `boomGateMotorState()` function sets the direction and action of the boom gate motors based on the provided state.

## Installation

To run this project, follow these steps:

1. Install the [Arduino IDE](https://www.arduino.cc/en/software) on your computer if you haven't already.

2. Connect the Arduino board to your computer using a USB cable.

3. Open the Arduino IDE and create a new project.

4. Copy and paste the provided code into the Arduino IDE.

5. Make sure to select the correct Arduino board type and port in the Arduino IDE.

6. Upload the code to the Arduino board.

7. Connect the ultrasonic sensors, LEDs, push button, and motor drivers to the appropriate pins on your Arduino board according to the defined pin assignments in the code.

8. Power up the system.

## Usage

Once the code is uploaded and the hardware is connected, the traffic control system will operate automatically. Here's how the system works:

## Operation

### Vehicle Traffic Light Control

1. The main road traffic light starts in the "Green" state.

2. When a vehicle is detected at the main road (while the pedestrian light is green), the main road traffic light turns "Red."

3. After 1 second of the pedestrian light turning "Red," it turns "Green" for 10 seconds, then "Yellow" for 3 seconds, and finally "Red" again.

4. After 1 second of a vehicle being detected, the main road traffic light turns "Flashing Red" for 3 seconds and then "Red" again.

5. After 3 seconds of the main road traffic light being "Red," it turns "Green" again.

### Car Park Light and Boom Gate Control

- The car park light and boom gate are controlled based on the main road traffic light and vehicle detection at entry and exit gates.

- When the main road traffic light is "Green," the car park light is "Red," and the boom gate is open.

- When the main road traffic light turns "Red" (vehicle detected or pedestrian crossing), the car park light turns "Green," and the boom gate starts closing. It reverses its direction for 3 seconds to close.

- Once the boom gate is fully closed, the car park light turns "Red" again.

### Pedestrian Traffic Light Control

1. The pedestrian traffic light starts in the "Red/Down" state.

2. When the pedestrian button is pressed (main road traffic light is "Green"), the pedestrian light turns "Yellow" for 3 seconds and then "Red."

3. After 3 seconds of the main road traffic light turning "Red" or the boom gate being lowered, the pedestrian light turns "Green."

4. When the pedestrian button is pressed, the car park light turns "Red," and the boom gate motor activates for 3 seconds to lower the boom gate (only if the gate was not already lowered).

## Contributing

Contributions to this project are welcome! If you have ideas for improvements or new features, feel free to open an issue or submit a pull request on the project's repository.

## License

This project is licensed under the [MIT License](LICENSE). You are free to use, modify, and distribute this code for personal and commercial use, with proper attribution to the original author.
