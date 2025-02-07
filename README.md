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

### Fluxo de Operação

- Botão A pressionado
    - Primeira vez:
        1. LED verde aceso;
        2. Mensagem "LED Verde aceso" mostrada no display OLED;
        3. Mensagem "LED Verde aceso" enviada via interface serial;
    - Segunda vez:
        1. LED verde desligado;
        2. Mensagem "LED Verde desligado" mostrada no display OLED;
        3. Mensagem "LED Verde desligado" enviada via interface serial;
- Botão B pressionado
    - Primeira vez:
        1. LED azul aceso;
        2. Mensagem "LED azul aceso" mostrada no display OLED;
        3. Mensagem "LED azul aceso" enviada via interface serial;
    - Segunda vez:
        1. LED azul desligado;
        2. Mensagem "LED azul desligado" mostrada no display OLED;
        3. Mensagem "LED azul desligado" enviada via interface serial;
- Tecla pressionada no teclado
    - Caracter
        1. Limpa o display;
        2. Retorna o caracter pressionado via interface serial;
        3. Mostra o caracter no display;
        4. Se a matriz de LEDs estiver acesa, a desliga;
    - Numero
        1. Limpa o display;
        2. Retorna o numero pressionado via interface serial;
        3. Mostra o numero no display;

### Vídeo

[Vídeo demonstrativo do projeto](https://drive.google.com/file/d/1Fbk44jD_cP-Oth_4zdp8DUDqRbpXiYhu/view?usp=sharing)

## 👥 Autoria

**Guilherme Emetério Santos Lima**  
[![GitHub](https://img.shields.io/badge/GitHub-Profile-blue?style=flat&logo=github)](https://github.com/DankAlighieri)
