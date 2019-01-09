# DoSC
Diagnostics on Socket CAN

## Aim
The aim of this project is to build a library which makes OBD2 and UDS interface easier

## Why SocketCan
SocketCan treats the CAN bus as a first class citizen.  USB CAN adapters or native CAN interfaces on SoC provides a more seamless experience than ELM (or similar) interface chips.

While ELM is a fanstastic bit of silicon unifying the legacy OBD protocols all cars since 2008 have been required to implement CAN as one of their interfaces.
This library leans into that fact and ignores non-CAN OBD.  Due to SocketCan's abstraction of hardware any "native" CAN interface may be used with this library.

## Suggested USB Adapters
- PCAN-USB (Peak/Grid Connect)
- CANUSB (lawicel)
- CANtact (cantact.io)

Other adapaters may work these are just suggested

## Protocols

OBD2 - Protocol required by emissions, may also be used for simple datalogging

UDS - More advanced diagnostic protocol, not required but commonly used

## State of Project

Still getting the basics spun up.  Stay tuned.

## License

GNU GPL v3

## Contribution

Contribution welcome, please mimic my coding style the best you can.
