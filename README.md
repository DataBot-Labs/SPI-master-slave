# SPI-master-slave

MultiBus Protocol v1.0 — Firmware Pack

Overview

The MultiBus Protocol v1.0 is a custom SPI-based master-slave communication system designed to connect up to 100 ESP32 devices to a single Arduino Due master. This protocol features automatic device addressing, CRC error detection, and a self-healing bus with automatic retry.

1. Master Firmware (Arduino Due)

Libraries Used:

SPI.h


1. Automatic Addressing System

On first boot, each Slavedevice reads its Flash Chip ID.

The Master will request the IDs.

Based on the response time, the master will assign unique addresses to each slave.

Address gets stored permanently in EEPROM.


2. CRC Error Detection

Every packet will include a CRC byte:

3. Optional Serial Log System

Every device will log incoming data, outgoing data, and CRC status.

