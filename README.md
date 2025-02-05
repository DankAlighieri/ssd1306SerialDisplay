# Tarefa interface de comunicações

## 🛠️ Componentes Utilizados

- Placa de estudo BitDogLab
- Pico
- Cabo USB

## 💻 Firmware

Desenvolvido em C utilizando:

- IDE: Visual Studio Code
- SDK: Raspberry Pi Pico SDK
- LED Vermelho: GP13
- LED Verde: GP11
- LED Azul: GP12
- Botão: GP5 (com resistor pull-up)
- Botão: GP6 (com resistor pull-up)
- LED inicial da matriz de leds: GP7
- ssd1306 SDA 14
- ssd1306 SDL 15

## 🎯 Funcionamento

### Estado Inicial

- LED RGB, Matriz de LEDs e display desligados
- CPU aguarda input de caracter
- Interrupção dos botões em caso de borda de descida ativada

### Fluxo de Operação:

- Botão A pressionado
- Botão B pressionado  
- Tecla pressionada no teclado 

### Explicação


## 👥 Autoria
**Guilherme Emetério Santos Lima**  
[![GitHub](https://img.shields.io/badge/GitHub-Profile-blue?style=flat&logo=github)](https://github.com/DankAlighieri)