# Line Following Robot

A small two-wheel robot that follows a black line on the floor by itself. At first it sounded like a simple beginner project, but I wanted to design the whole thing myself: the body, the wiring and the code. An Arduino Nano reads a row of 5 infrared sensors under the front of the robot. Based on which sensors see the line, it speeds up one wheel and slows the other through a TB6612FNG motor driver, so the robot steers back onto the track. The body is a plate I designed in Fusion 360 for 3D printing. I'm building it to learn how CAD, electronics and code work together on a small robot.

## Status
The CAD, the circuit plan and the code are done. The robot is not built yet and the code has not run on real hardware, so every number in the code is a starting guess.

## Built With
- Arduino Nano (CH340 clone)
- 5-channel TCRT5000 IR sensor array
- TB6612FNG motor driver module
- 2 TT gear motors with 65 mm wheels
- 2 x 18650 cells with a buck converter for 5V
- Fusion 360 for the chassis, Arduino IDE for the code

## Bill Of Materials

| Component | Qty | Purpose | Purchase link |
|---|---|---|---|
| Arduino Nano (CH340, soldered) | 1 | Main controller: reads the sensors, runs the steering code, drives the motor driver | https://roboway.in/shop/arduino-nano-v3-0-development-board-ch340-clone-compatible-model-soldered |
| USB cable for the Nano (mini-USB or USB-C, to match the board) | 1 | Uploads code and powers the board on the bench | Local shop |
| 5-channel IR sensor array (TCRT5000L) | 1 | Looks down at the floor to tell the black line from the white surface | https://roboway.in/shop/tcrt5000l-5-channel-tracking-sensor-tracking-module-infrared-sensor |
| TB6612FNG motor driver module | 1 | Drives the left and right motors and wastes far less power than an L298N | https://roboway.in/shop/tb6612fng-dual-motor-driver-module-1a-for-arduino |
| TT gear motor with 65 mm rubber wheel | 2 | Two-wheel drive, the robot steers by running one wheel faster than the other | https://colgroad.com/product/tt-gear-motor-with-65mm-rubber-wheel |
| Metal ball caster | 1 | Third support point at the back so the robot balances | https://robocraze.com/products/metal-ball-omni-directional-caster-wheel |
| Adjustable buck converter (MP1584, 3A) | 1 | Steps the battery down to a steady 5V for the Arduino, driver logic and sensors | https://www.rytronics.in/product/mini-mp1584-dc-dc-3a-adjustable-buck-module/ |
| SPDT slide switch | 1 | Main on/off switch | Local shop |
| 18650 Li-ion cell (protected) | 2 | Battery pack in series (2S, about 7.4V) | Local shop, from a trusted seller |
| 2-slot 18650 holder (series wiring) | 1 | Holds the two cells | https://stemvolt.in/product/2-slot-18650-lithium-battery-holder/ |
| 2-bay 18650 charger | 1 | Charges the cells outside the robot | https://www.amazon.in/Rechargeable-Lithium-Batteries-Capacity-Charging/dp/B0HPKNXB1Y |
| Capacitor kit (needs 470 uF, 100 uF and 0.1 uF) | 1 | 470 uF on the motor supply, 100 uF on the 5V line, 0.1 uF on the 5V line and across each motor | https://www.theengineerstore.in/products/orange-500pcs-0-1uf-1000uf-plug-in-electrolytic-capacitor-kit |
| Breadboard | 1 | Test the wiring before soldering | https://robu.in/product/mb102-830-points-solderless-prototype-pcb-breadboard-high-quality/?gad_source=1&gad_campaignid=17427802703&gbraid=0AAAAADvLFWfQJu5IRqfuueVA79jtB_jz_&gclid=Cj0KCQiA-8XXBhDaARIsADnEOrCrw-nMEVTiFGZEYlI4sBkP3on9tEbcDeJd9OhFyKKFEWJ2oowoPL4aApJXEALw_wcB|
| Jumper wire set | 1 | Test wiring | (https://robu.in/product/male-to-female-jumper-wires-40-pin-30cm/?gad_source=1&gad_campaignid=17427802703&gbraid=0AAAAADvLFWfQJu5IRqfuueVA79jtB_jz_&gclid=Cj0KCQiA-8XXBhDaARIsADnEOrCAunV3S3byX8FiwPW218qY_9EctsgCyyDF8KSz2syjbHw-GCbOs8MaAoN0EALw_wcB)|
| Silicone wire 22AWG | 1 | Power and motor wiring | Local shop |
| Male header pins | 1 strip | For modules that come without pins | Local shop |
| M3 x 10 mm screws | 1 pack | Motors, caster and boards on the chassis | https://www.amazon.in/Rpi-shop-Phillip-Phillips-Quantity/dp/B08FG7DL3T/ |
| M3 x 16 mm screws | 1 pack | Sensor bar standoffs | https://www.amazon.in/Rpi-shop-tensile-Machine-Quantity/dp/B07XY5YXKD |
| M3 standoffs and nuts | 1 set | Hang the sensor bar under the front shelf | Local shop |
| Zip ties or velcro strap | 1 set | Hold the battery holder and the motors | Local shop |
| Heat shrink tubing | 1 set | Cover soldered joints | Local shop |
| PLA filament (about 100 g) | 1 | The chassis | Local shop or print shop |
| Black electrical tape and white poster board | 1 each | Test track | Local shop |
| Multimeter | 1 | Set the buck converter to 5V, check for shorts | Local shop |
| Soldering iron and solder | 1 | Joins wires and header pins | Local shop |
| Wire cutter and stripper | 1 | Prepares the wires | Local shop |
| Calipers or a ruler | 1 | Measure every part before finalising the CAD | Local shop |

## Circuit Diagram
<img width="729" height="455" alt="circuit_diagram" src="https://github.com/user-attachments/assets/0346d820-ff8f-4404-a4d7-b3289c33479e" />

This is a planned wiring diagram. The tool I drew it in shows both big capacitors as 1 uF. The real build uses 470 uF at the motor supply and 100 uF on the 5V line.

## Pin Map
Board: Arduino Nano.

| Arduino pin | Connects to | Purpose |
|---|---|---|
| A0 to A4 | Sensor outputs 1 to 5 (A0 is the far left) | Read the line |
| D5 | Driver PWMA | Left motor speed |
| D7 | Driver AIN1 | Left motor direction |
| D8 | Driver AIN2 | Left motor direction |
| D6 | Driver PWMB | Right motor speed |
| D9 | Driver BIN1 | Right motor direction |
| D10 | Driver BIN2 | Right motor direction |
| D4 | Driver STBY | Turns the driver on |
| 5V | Driver VCC, sensor 5V | Logic power |
| GND | All grounds | Common ground |

### Power and load connections

| From | To |
|---|---|
| Cell 1 negative | Cell 2 positive (series junction) |
| Pack positive | Power switch |
| Power switch | Driver VM and buck converter input |
| Pack negative | Common GND |
| Buck converter output (5V) | Arduino 5V, driver VCC, sensor 5V |
| Driver AO1 and AO2 | Left motor |
| Driver BO1 and BO2 | Right motor |
| 470 uF capacitor | Across driver VM and GND |
| 100 uF and 0.1 uF capacitors | Across the 5V line and GND |
| 0.1 uF capacitor | Across each motor's terminals |

### Before wiring
- Set the buck converter to 5.0V with a multimeter before the Arduino or the sensors touch it.
- With the switch off, the buck input and the driver VM should read 0V.
- Do not plug USB into the Nano while the buck converter is also feeding its 5V pin.

## Assembly guide
This is the order I plan to build it in. I haven't done it yet, so it may change.

1. Measure every part with calipers and compare the numbers with the parameters in the Fusion file.
2. Print the chassis and check that the motors fit between the rails.
3. Solder wires to the motors and put a 0.1 uF capacitor across each one.
4. Fit the motors, the wheels and the caster.
5. Wire the battery holder, the switch and the buck converter only. Set the output to 5.0V, then switch off.
6. Mount the Nano, the driver and the battery holder in their pockets and strap the battery down.
7. Wire the rest using the pin map. Keep the motor wires away from the sensor wires.
8. Hang the sensor bar under the front shelf on standoffs, about 3 to 4 mm above the floor.
9. Test with the wheels lifted off the ground. Both wheels should turn forward. If one turns backward, swap that motor's two wires.
10. Test on a track of black tape on white paper, with wide gentle curves first.

## Calibration
- Set PRINT_MODE to true, upload, and open the Serial Monitor at 9600 baud. Read the numbers with the sensors over tape and then over paper to find the threshold.
- Set BLACK_IS_HIGH to match whether the line reads high or low.
- If the robot steers away from the line, reverse the WEIGHTS order or flip the sign of the correction.
- Start with Kd at 0, raise Kp until it follows a straight line, then raise Kd until the wobble goes away.
- If it flies off sharp turns, lower BASE_SPEED.

## Things that might go wrong
I haven't built it yet, so these are things I expect, not things I have seen.
- The motors don't move. The STBY pin must be HIGH, and the driver needs power on both VM and VCC.
- The Arduino resets when the motors start. A bigger capacitor on the motor supply is the likely fix.
- The motors get too much voltage. The battery gives about 7.4 to 8.4V and many TT motors are rated lower, so the code caps the speed at 180 out of 255.
- The robot loses the line on a tight curve. Lower the speed or move the sensors further ahead of the wheels.
- The Nano doesn't show up on the computer. The CH340 chip may need a driver.

## Safety
Use protected 18650 cells and charge them outside the robot. Take them out if it will sit unused for a long time. Ask an adult to help with soldering and charging.

## CAD Models
1. Made a dummy box for each part, driven by a parameters table.
<img width="650" height="400" alt="Screenshot 2026-11-09 at 3 22 18 PM" src="https://github.com/user-attachments/assets/ca16a32d-f2d2-44be-b5b8-f57f666948a5" />


2. Base plate and motor rails.
<img width="650" height="400" alt="Screenshot 2026-11-09 at 3 23 04 PM" src="https://github.com/user-attachments/assets/82b3c079-711e-41cf-8720-c32c165198f1" />


3. Sensor shelf, caster holes, pockets for the Nano and driver, battery strap slots.

<img width="650" height="400" alt="Screenshot 2026-11-09 at 3 25 26 PM" src="https://github.com/user-attachments/assets/534cea31-0a5f-486c-8649-162f60cb1ebe" />


4. Wheels and sensor bar, interference check with no overlaps.

<img width="650" height="400" alt="Screenshot 2026-11-09 at 3 25 55 PM" src="https://github.com/user-attachments/assets/4c664efe-1f33-4ec2-8af6-f183e07e4383" />

Not modelled yet: the caster. The sizes of the motor, battery holder and sensor board come from typical listings and need to be checked against the real parts.

## Known gaps
- The robot is not built or tested.
- The caster is not in the CAD yet.
- The sensor threshold, Kp and Kd are guesses until I test on a track.
