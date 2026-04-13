Group 8's project: Mini environmental station with STM32

Project Overview : Mini environmental monitoring station with module LCD display using I2C module and can alert with buzzer when certain conditions are met, sent data measured to phone UART app via Bluetooth with UART communication (module HC-05). The station use mcu stm32f103c8t6 aka blue pill that can measure real-time temperature & humidity (module DHT11), gas (module MQ2), and can display them on the lcd screen. The device also has 2 button, 1 to snooze the alarm, 1 to change the display mode in cycle.

Requirement definition: [https://docs.google.com/spreadsheets/d/1O582D53Wys3Cwzh6xRYdXv68gtSpY5OcIZm6p9dKSyE/edit?gid=229854535#gid=229854535](https://docs.google.com/spreadsheets/d/1O582D53Wys3Cwzh6xRYdXv68gtSpY5OcIZm6p9dKSyE/edit?gid=229854535#gid=229854535)

System specification: [https://docs.google.com/spreadsheets/d/1O582D53Wys3Cwzh6xRYdXv68gtSpY5OcIZm6p9dKSyE/edit?gid=85428960#gid=85428960](https://docs.google.com/spreadsheets/d/1O582D53Wys3Cwzh6xRYdXv68gtSpY5OcIZm6p9dKSyE/edit?gid=85428960#gid=85428960)

Block diagram:


Power tree:


Schematic: 

PCB Layout: 
<img width="928" height="752" alt="image" src="https://github.com/user-attachments/assets/c8e59226-b8d6-4f9a-ba6a-4b1be59e4d02" />
<img width="959" height="720" alt="image" src="https://github.com/user-attachments/assets/627cadc2-1852-4459-9855-f624090b0c33" />


