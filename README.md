# MÉTODOS GET/POST COM ESP8266

**Autor(a):** Acssa passos sousa

**Data**:29/07/2022

**Descrição:** Configuração do módulo ESP utilizando o núcleo F411RE, com aplicação dos métodos GET E POST no servidor http://cloudecg-env-1.eba-wvqrkbtk.sa-east-1.elasticbeanstalk.com

**IDE:** STM32CUBEIDE V.1.8.0
______________________________________________________________________________________________________

## Configurações da IDE: 

Criando um novo projeto na área de trabalho do CUBE IDE:

1. Vá até a guia Arquivo > Novo > Projeto STM32

<img width="770" alt="image" src="https://user-images.githubusercontent.com/101206099/162268568-6a5fbd51-5a2c-4eef-9b4d-61510b893fa8.png">

2. Ao abrir a janela "Target selection" e selecione na aba "board selector" a plataforma de desenvolvimento a ser utilizada, para este caso NUCLEO-F411RE. 

<img width="960" alt="image" src="https://user-images.githubusercontent.com/101206099/162270921-1167cfc5-8806-4a85-99f1-6a3f9db821e5.png">

3. Dê um nome ao seu projeto e prossiga com o "Finish".

<img width="376" alt="image" src="https://user-images.githubusercontent.com/101206099/162271925-38ad9a78-8248-49fd-86d5-cdd3789f8ffe.png">

4. Para a comunicação serial com o ESP, altere as potas dos pinos PA12(USART6_RX) e PA11(USART6_TX).

<img width="502" alt="image" src="https://user-images.githubusercontent.com/101206099/181808984-da1fa277-14a4-43ad-9bd4-e52cb6a32ebe.png">

5. Na aquisição dos dados o botao B1 é utilizado, altere o pino PC13 para GPIO_EXTI13, vá em system core> NVIC e habilite as funções de acordo com a imagem:

<img width="803" alt="image" src="https://user-images.githubusercontent.com/101206099/181809755-f78288a4-cf74-4a46-b75e-8099dd7ce5d9.png">

6. A visualização dos dados serão realizadas através de um monitor serial, para que isso ocorra os pinos PA2 E PA3 devem estar configurados como USART_TX E USART_RX, respectivamene.

<img width="378" alt="image" src="https://user-images.githubusercontent.com/101206099/181810493-aa5f1383-aca9-40fc-a1e0-7f619ec4c336.png">

7. Mantenha as outras configurações como padrão, salve as alterações e gere o código no íncone demonstrado:

<img width="301" alt="image" src="https://user-images.githubusercontent.com/101206099/181810987-96e2671f-f98b-4e4e-97b6-eaeaaddcdd60.png">

_____________________________________________________________________________________________________________________________




