# embedded-lab
A collection of embedded systems projects and experiments.

This repository is used as a personal lab for exploring microcontrollers, sensors, signal processing, and human-machine interfaces.
Projects focus on **real hardware behavior**, **signal stability**, and **clean architecture**, rather than simple demos.

## Goals

- practice embedded systems design with real sensors and peripherals
- explore signal filtering, calibration, and noisy inputs
- build reusable patterns for small embedded applications
- document hardware, wiring, and design decisions clearly

## Platforms

- ESP32 (primary)
- Arduino-compatible microcontrollers
- breadboard-based prototyping (schematic + real wiring)

## Projects

| Project | Description |
|--------|-------------|
| [esp32-ultrasonic-distance-feedback](https://github.com/morgween/embedded-lab/tree/main/esp32-ultrasonic-distance-feedback) | Ultrasonic distance indicator with LED bargraph, buzzer and buttons |
| [esp32-thermistor-fan-automation](https://github.com/morgween/embedded-lab/tree/main/esp32-thermistor-fan-automation) | Automated fan with thermistor, control buttons and information leds |

More projects will be added over time.

## Structure

Each project lives in its own folder and contains:
- source code
- hardware schematic
- wiring photos or diagrams
- a short demo (gif or video)
- project-specific README

---

This repository is intentionally kept simple and hardware-focused.
