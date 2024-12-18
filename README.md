# SpedenSpelit

**WORK IN PROGRESS**

## Table of contensts

- [Project's goals](#projects-goals)
- [Project's topic – SpedenSpelit](#projects-topic--speden-spelit)
- [Additional features](#additional-features)
- [Technical Specifications](#technical-specifications)
- [List of components used](#list-of-components-used)
- [Case](#case)
- [Simulation](#simulation)

## Project's goals

The goal of the project is to implement a microprocessor application that monitors its surroundings with the help of sensors, and controls the hardware connected to the microprocessor based on the signals from the sensors. With the addition of learn basic skills of project work and documentation.

## Project's topic – Speden Spelit

Speden Spelit Speed Test works as the project’s topic. The Speed Test was one of the games used during the airing of the Finnish game show Speden Spelit in the years of 1988–2002. The goal of the Speed Test is to hit the right button indicated by a flash of a light in time, while the speed of the required inputs increases.

## Additional features

During the development of the project, there have been added additional features to the game. The features include two additional game modes. These game modes are a "sequence memory mode" and a "blind mode". These modes can be accessed from the games start menu.

## Technical Specifications

**Circuit diagram**

![Reaction-game-circuit-diagram](./pictures/circuit-diagram.png)

**Flowchart**

![SpedenSpelit_Flowchart_5](./pictures/flowchart.png)

## List of components used

| Type                                | Amount      | Part model            |
|-------------------------------------|-------------|-----------------------|
|Shift register                       | 3           | TI 74HC595N           |
|7-segment display                    | 3           | Kingbright SA52-11EWA |
|Turquoise LED, Through Hole, 5mm     | 1           | HLMP-4740             |
|Red LED, Through Hole, 5mm           | 1           | Generic               |
|Yellow LED, Through Hole, 5mm        | 1           | Generic               |
|Green LED, Through Hole, 5mm         | 1           | Generic               |
|SMD Piezo Buzzer                     | 1           | KLJ-1625              |
|Button switch                        | 5           | Kailh Choc v1 red     |
|180 Ω resistor (yello and green LED) | 2           | Generic               |
|680 Ω resistor (Turquoise LED)       | 1           | Generic               |
|390 Ω resistor (7-segment display)   | 21          | Generic               |
|2k Ω resistor (red LED)              | 1           | Generic               |


## Case

You can find the case .stl and .f3d files in the [/case-files](./case-files) folder
![Picture-of-the-case](./pictures/case.png)


## Simulation

You can simulate the game from wokwi [here](https://wokwi.com/projects/415181822807852033) or at https://wokwi.com/projects/415181822807852033.
