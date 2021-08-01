# Implementação do Protocolo CAN para placa Toradex Colibri VF50 e Mbed - Controle da Formiga Mecatrônica

<h2 align="center"> SEM0544 - Sistemas Embarcados

</h2>

<h3 align="center"> 
  
Universidade de São Paulo </p>
Escola de Engenharia de São Carlos </p>
Departamento de Engenharia Elétrica e Computação </p> </p> </p>

</h3>

<h3 align="center"> <img src="./Imagens/unnamed.png" 
     alt="Logo EESC" height="100">
</h3>
  
Professores: </p>
**Glauco Augusto de Paula Caurin** </p>
**Daniel Varela Magalhães**

Alunos:</p>
**[Gustavo Batistom Vasquez](https://github.com/gustavobvasquez)** *n° USP: 9805150* </p>
**[Leonardo Ferreira Rosa Zago](https://github.com/leonardozado)** *n° USP: 9805355* </p>
**[Leonardo Rodrigues de Ávila Oliverira](https://github.com/Leonardorodriguesoliveira)** *n° USP: 9805205* </p>

<h5 align="center"> 
  
31 de julho de 2021

</h5>

# 1) Objetivos
  O projeto se baseia no funcionamento de 12 motores PWM que realizam a movimentação da formiga mecatrônica através de utilização de sistemas embarcados. Para isso, o objetivo foi desenvolver a comunicação, através do protocolo de comunicacão CAN, entre uma placa com linux embarcado (Toradex VF50) e a placa da Mbed (LPC1768), onde os motores estarão conectados as portas PWM. Desta forma o projeto tem a flexibilidade de contar com um sistema operacional, para inclusão de diversas funcionalidades futuras, e também pode-se utilizar do poder de processamento existênte na Mbed. 



# 2) Materiais e métodos
  Para a realização do projeto, foram utilizadas a placa Colibri VF50 da Toradex e 2 placas Mbed LPC1768. O diagrama de blocos a seguir demonstra a estrutura de comunicação desde a placa com o S.O. embarcado até a informação de PWM dos motores.
  
  </h3>

<h3 align="center"> <img src="./Imagens/Diagrama de Blocos_Formiga.PNG" 
     alt="DB" height="500">
</h3>

  O fluxo de funciomento será da seguinte forma, a placa da toradex envia uma mensagem de funcionamento via protocolo Can para as placas da Mbed. Recebendo esta informação a placa da Mbed executa a rotina programada para controle dos PWM de acordo com a mensagem recebida (Levantan, Anda para frente, Abaixa, Vire a direita, etc.)
  
  

# 3) Desenvolvimento

# 4) Concluões finais
--> Protocolo Can facilita a adiação de novos componentes "sistema de varal"
--> Parte do codigo estar na mbed diminui o processamento realizado no processador com S.O. possibilitanto adição de novas funcionalidades no futuro (câmera, braço robótico entre outros)

