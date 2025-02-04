# 🚦 Sistema de Temporização com LEDs e Botão (Raspberry Pi Pico)

Projeto de controle de LEDs RGB com temporização por alarmes.Utiliza interrupções por hardware e debounce via software para garantir operação confiável.

##  Funcionalidades Principais
- **Acionamento por Botão:** Inicia a sequência ao pressionar o botão.
- **Sequência Automática:**
  - Todos LEDs ligados → Azul desliga (3s) → Vermelho desliga (3s) → Verde desliga (3s).
- **Debounce Software:** Filtra ruídos mecânicos do botão.
- **Não-Bloqueante:** Usa timers do hardware para não travar a execução.
- **Compatível com BitDogLab:** Usa GPIOs específicos da placa educacional.

## 📋 Pré-requisitos
### Hardware
| Componente              | Quantidade | Observações                          |
|-------------------------|------------|--------------------------------------|
| Raspberry Pi Pico W     | 1          | Microcontrolador principal           |
| LEDs RGB                | 1          | Ou 3 LEDs individuais (Vermelho, Verde, Azul) |
| Botão (Pushbutton)      | 1          | Para acionamento manual              |
| Resistores 330 Ω        | 3          | Proteção dos LEDs                    |

### Software
- [SDK do Raspberry Pi Pico](https://www.raspberrypi.com/documentation/microcontrollers/c-sdk.html)
- Compilador ARM (ex: `gcc-arm-none-eabi`)
- CMake (versão 3.12+)
  
  ### BitDogLab (Hardware Real)
   1- **Clone o repositório**
   2-  **Compile o projeto**
   3- **Grave na placa**

  ## 🔌 Pinagem (BitDogLab)

| GPIO | Componente       | Cor                |
|------|------------------|--------------------|
| 13   | LED              | 🔴 Vermelho         |
| 12   | LED              | 🔵 Azul            |
| 11   | LED              | 🟢 Verde           |
| 5    | 🕹️ Botão         | -                  |
| GND  | ⚡ Terra (comum) | -                  |

*Notas:*  
- *GPIOs seguem a numeração padrão da BitDogLab*  
- *Resistores de 330Ω conectados em série com os LEDs*  
- *Botão utiliza resistor pull-up interno*

# DESENVOLVIDO POR CÉSAR REBOUÇAS COSTA
