Projeto Catavento – Simulação de Usina Eólica

Este projeto foi desenvolvido por João Victor Benício, Mateus Jorge e Rau da Silva no Instituto Mauá de Tecnologia para as matérias de Instrumentação e Microcontroladores. O objetivo é simular o funcionamento de uma usina eólica em escala reduzida utilizando fabricação digital e programação embarcada.

Resumo do Projeto

O sistema foi construído com peças impressas em 3D, partes cortadas a laser e um sensor baseado em um potenciômetro linear. Esse sensor é acionado pela rotação de uma biruta, representando a direção do vento. A leitura do potenciômetro permite simular o comportamento de um sistema de medição em uma estação eólica.

A parte lógica do projeto foi desenvolvida em MicroPython para o microcontrolador Raspberry Pi Pico. Também foi incluído um código equivalente em linguagem C como alternativa.

Estrutura de Pastas

cortar_a_lazer              Arquivos vetoriais (DXF ou SVG) prontos para corte a laser  
eletronica                  Diagramas esquemáticos autoexplicativos e lista de componentes  
headme.md                   Este arquivo de descrição do projeto  
main.c                      Código-fonte em linguagem C para o Raspberry Pi Pico  
pasta_codigo_python_conpactado.zip    Código principal em MicroPython compactado  
print_3d                    Arquivos STL das peças para impressão 3D  

Objetivo Didático

Este projeto permite o aprendizado prático de conceitos como:

- Modelagem 3D e corte a laser
- Leitura analógica de sensores
- Programação embarcada com MicroPython e C
- Integração entre hardware e software

Execução

1. Monte a estrutura física utilizando as peças impressas e cortadas.
2. Conecte o potenciômetro linear conforme o diagrama da pasta eletronica.
3. Envie o código da pasta compactada para o Raspberry Pi Pico.
4. Caso prefira utilizar o código em linguagem C, compile e carregue o arquivo main.c.
5. Gire a biruta para simular a variação da direção do vento e observe os dados lidos pelo potenciômetro.

Licença

Este projeto é de uso educacional e pode ser reproduzido com a devida atribuição aos autores.
