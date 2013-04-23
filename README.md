robotpi-subbrain
================

## An Arduino based Central Nervous System

This is an Arduino sketch that acts as the sub-brain/CNS of a Raspberry Pi based robot. The Raspberry Pi sends voltages over GPIO to the Arduino which has a series of pins waiting for input signals. These signals control a CanaKit Motor Driver. The idea is that two pins are used to alert the Arduino of the direction (left, right, forward, reverse) another pin sends a signal to alter the motor time to a short burst (i.e. a pusle) and a final fourth pin just stops everything (break).

This is written with the intention of being used on an Arduino Uno or Arduino Mega 2560.
