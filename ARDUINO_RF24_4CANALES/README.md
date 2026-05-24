# 📡 Control Inalámbrico de 4 Canales por RF NRF24L01 + Arduino Nano
 
Control inalámbrico de 4 salidas independientes usando módulos NRF24L01 y Arduino Nano.
El sistema consta de un transmisor con 4 botones con antirrebote y un receptor que
conmuta 4 puertos de salida segun la senal recibida por radiofrecuencia.
 
---
 
## Estructura del repositorio

```text
ARDUINO_RF24_4CANALES/
├── Codigo/
│   ├── transmisor.ino
│   └── receptor.ino
├── Diagrama/
│   ├── transmisor.pdsprj
│   └── receptor.pdsprj
├── Imagenes/
│   ├── esquema_transmisor.png
│   └── esquema_receptor.png
└── README.md
```

---

## Como funciona
 
El transmisor lee 4 botones fisicos mediante la libreria a_rebote para eliminar el
efecto rebote. Al presionar un boton, envia un arreglo de 4 enteros por el canal RF.
 
El receptor escucha continuamente ese canal. Al detectar un dato entrante, conmuta
(toggle) la salida correspondiente y activa un pin de monitoreo para indicar actividad.
 
[BOTON 1..4] -> Nano Transmisor -> NRF24L01 ))) ... ((( NRF24L01 -> Nano Receptor -> [SALIDA 1..4]
 
---
 
## Hardware necesario
 
| Componente           | Cantidad | Notas                                 |
|----------------------|----------|---------------------------------------|
| Arduino Nano         | 2        | Uno para TX, uno para RX              |
| Modulo NRF24L01      | 2        | Recomendado con adaptador de 3.3V     |
| Pulsadores / botones | 4        | Para el transmisor                    |
| LEDs o reles         | 4        | Para el receptor                      |
| Resistencias 220 ohm | 4        | Si usas LEDs                          |
| Capacitor 100uF      | 2        | Para estabilizar voltaje del NRF24L01 |
 
NOTA: El NRF24L01 opera a 3.3V. Conectar a 5V puede daniarlo.
 
---
 
## Diagrama de pines — Arduino Nano
 
-- Ambas placas (TX y RX) — NRF24L01 --
 
| NRF24L01 | Arduino Nano |
|----------|--------------|
| CE       | D9           |
| CSN      | D10          |
| MOSI     | D11          |
| MISO     | D12          |
| SCK      | D13          |
| VCC      | 3.3V         |
| GND      | GND          |
 
-- Transmisor — Botones --
 
# 📡 Control Inalámbrico de 4 Canales por RF — NRF24L01 + Arduino Nano
 
Control inalámbrico de 4 salidas independientes usando módulos NRF24L01 y una placa Arduino.
El sistema consta de un transmisor con 4 botones con antirrebote y un receptor que
conmuta 4 puertos de salida segun la senal recibida por radiofrecuencia.
 
---

 
## Como funciona
 
El transmisor lee 4 botones fisicos mediante la libreria a_rebote para eliminar el
efecto rebote. Al presionar un boton, envia un arreglo de 4 enteros por el canal RF.
 
El receptor escucha continuamente ese canal. Al detectar un dato entrante, conmuta
(toggle) la salida correspondiente y activa un pin de monitoreo para indicar actividad.
 
[BOTON 1..4] -> Nano Transmisor -> NRF24L01 ))) ... ((( NRF24L01 -> Nano Receptor -> [SALIDA 1..4]
 
---
 
## Hardware necesario
 
| Componente           | Cantidad | Notas                                 |
|----------------------|----------|---------------------------------------|
| Arduino Nano         | 2        | Uno para TX, uno para RX              |
| Modulo NRF24L01      | 2        | Recomendado con adaptador de 3.3V     |
| Pulsadores / botones | 4        | Para el transmisor                    |
| LEDs o reles         | 4        | Para el receptor                      |
| Resistencias 220 ohm | 4        | Si usas LEDs                          |
| Capacitor 100uF      | 2        | Para estabilizar voltaje del NRF24L01 |

 
---
 
## Diagrama de pines — Arduino Nano
 
-- Ambas placas (TX y RX) — NRF24L01 --
 
| NRF24L01 | Arduino Nano |
|----------|--------------|
| CE       | D9           |
| CSN      | D10          |
| MOSI     | D11          |
| MISO     | D12          |
| SCK      | D13          |
| VCC      | 3.3V         |
| GND      | GND          |
 
-- Transmisor — Botones --
 
| Boton    | Arduino Nano |
|----------|--------------|
| BOTON 1  | D2           |
| BOTON 2  | D3           |
| BOTON 3  | D4           |
| BOTON 4  | D5           |
 
-- Receptor — Salidas --
 
| Salida      | Arduino Nano |
|-------------|--------------|
| LED1        | D2           |
| LED2        | D3           |
| LED3        | D4           |
| LED4        | D5           |
| Monitor TX  | D8           |
 
---
 
## Librerias requeridas
 
Instala desde el Administrador de Librerias de Arduino IDE:
 
| Libreria   | Autor   | Funcion                             |
|------------|---------|-------------------------------------|
| RF24       | TMRh20  | Comunicacion con modulo NRF24L01    |
| a_rebote   | ---     | Eliminacion de rebote en pulsadores |
 
---
 
## Esquemas en Proteus
 
Los archivos .pdsprj estan en la carpeta Diagrama/. Requieren Proteus 8 o superior.
Las capturas de los esquemas estan en la carpeta Imagenes/.
 
