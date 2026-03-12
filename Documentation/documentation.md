Optical Morse Communication Project

1\. Introduction

The Optical Morse project is a communication system that sends messages using light signals. In this project, a laser is used as a transmitter and an LDR sensor is used as a receiver. The laser sends Morse code signals, and the receiver detects the light and converts it into readable signals.



2\. Required Components

Arduino Nano

MOSFET module

Laser module

LDR (Light Dependent Resistor)

10k Resistor

Breadboard

Jumper wires

USB cable



3\. Required Components

Laser Transmitter Connection (using MOSFET Module)

Connect Arduino D9 → IN pin of the MOSFET module.

Connect Arduino GND → GND pin of the MOSFET module.

Connect 5V from Arduino → V+ of the MOSFET module.

Connect Arduino GND → V− of the MOSFET module.

Connect Laser positive (+) → OUT+.

Connect Laser negative (−) → OUT−.

LDR Receiver Connection

One leg of LDR → 5V

Other leg of LDR → A0

From the same A0 point → 10k resistor → GND

This forms the voltage divider needed for reading light.



4\. Working Principle (Optical Morse):

The Optical Morse project works on the principle of light-based communication. A laser is used to transmit signals in the form of Morse code (dots and dashes). The Arduino Nano controls the laser through the MOSFET module and turns it on and off to send the message.

At the receiver side, an LDR (Light Dependent Resistor) detects the laser light. When the laser light falls on the LDR, its resistance changes and the Arduino reads this change as a signal. The Arduino then processes these signals to determine whether the message has been received.



5\. Demonstration

Transmitter Side:

At the transmitter side, the Arduino Nano controls the laser module through the MOSFET module. When the code runs, the Arduino turns the laser on and off to send Morse code signals. These light signals represent the message being transmitted.

Receiver Side:

At the receiver side, the LDR sensor detects the laser light sent by the transmitter. When the light falls on the LDR, its resistance changes and the Arduino reads the signal through the analog pin. This confirms that the 

message sent from the transmitter has been successfully received.



6\. code

