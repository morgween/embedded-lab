# esp32 thermistor fan automation

Automated fan controller built on ESP32.

The project reads temperature using an NTC thermistor and controls a DC fan
via PWM with soft-start ramping. Supports manual speed presets, automatic
temperature-based control, and sensor error detection with LED indicators.

## Features

- NTC thermistor temperature sensing with EMA filtering
- PWM motor control with soft start/stop ramping
- four operating states: OFF, MANUAL, AUTO, ERROR
- manual mode with configurable speed presets
- auto mode with temperature-threshold hysteresis
- three LED indicators: OK (green), AUTO (blue), ERROR (red)
- four-button interface: power, speed up, speed down, auto
- sensor fault detection with automatic recovery
- serial logging for debugging and telemetry

## Hardware

- ESP32
- NTC thermistor
- DC fan motor with driver (MOSFET/H-bridge)
- 3 x LEDs (green, blue, red)
- 4 x push buttons
- resistors
- breadboard and jumper wires

## How it works

1. thermistor ADC value is read and filtered with EMA
2. sensor range is validated (shorted / disconnected detection)
3. in auto mode, fan speed adjusts based on temperature thresholds
4. in manual mode, preset speed steps are cycled with buttons
5. motor PWM ramps gradually to target duty for smooth operation
6. LEDs indicate current state and events

## Controls

| Button | Action |
|--------|--------|
| Power | toggle system on/off |
| Speed Up | increase manual speed preset |
| Speed Down | decrease manual speed preset |
| Auto | toggle auto/manual mode |

## Schema

![schema](docs/proj.png)

## Demo

Speed change in manual mode, +-5 steps (duty change) 
![demo1](docs/manual_mode_change_speed.gif)
Test auto mode, temeprature in the room is low, touching thermistor fastly starting the fan 
![demo2](docs/auto_mode_touch_thermistor.gif)
Test error state, after removing one part from the board (in this case thermistor), board going to failed mode showing it with red LED
![demo3](docs/error_state.gif)
---

Part of the **embedded-lab** repository.
