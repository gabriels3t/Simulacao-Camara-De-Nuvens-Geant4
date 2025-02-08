# Simulação de Detector de Partículas com Geant4

Este projeto visa a criação de uma simulação de um detector de partículas utilizando o framework Geant4, com foco em uma câmara de nuvens. O cenário simulado envolve um aquário preenchido com etanol, cuja densidade é maior para simular o estado supersaturado do etanol, como ocorre quando ele passa de um estado gasoso para o líquido. Esse ambiente é cercado por paredes de vidro e está localizado dentro de um quarto controlado. A câmara de nuvens simula a trajetória de partículas carregadas, sendo visualizada por meio da condensação de vapor de etanol, similar ao que ocorre em detectores reais. A simulação abrange a geração de partículas fictícias chamadas "Geantinos" e a visualização das interações dessas partículas com o ambiente, permitindo o estudo das suas trajetórias e as reações no interior da câmara.

Para uma melhor compreensão sobre o Geant4 e o problema específico abordado neste projeto, acesse o arquivo [relatorio.pdf](relatorio.pdf).

## Estrutura do Projeto

O projeto é composto pelos seguintes arquivos principais:

- **FonteDeParticulas.cpp/hpp**: Define a fonte de partículas que será usada na simulação.
- **GeradorPrimario.cpp/hpp**: Implementa o gerador de partículas primárias (Geantinos).
- **MeuDetector.cpp/hpp**: Define a geometria do detector, incluindo o aquário, as paredes de vidro e o material (etanol).
- **main.cpp**: Configura e inicializa a simulação, incluindo a interface gráfica e a execução da simulação.

## Pré-requisitos

Para executar este projeto, você precisará ter o seguinte instalado:

- [Geant4](https://geant4.web.cern.ch/) (versão 10.x ou superior)
- [CMake](https://cmake.org/) (para compilar o projeto)
- [Qt](https://www.qt.io/) (para a interface gráfica)
- Compilador C++ compatível (GCC, Clang, etc.)

## Como Compilar e Executar

1. **Clone o repositório**:
   ```bash
   git clone https://github.com/gabriels3t/Simulacao-Camara-De-Nuvens-Geant4
   cd Simulacao-Camara-De-Nuvens-Geant4
1. **Clone o repositório**:
   ```bash
   git clone https://github.com/gabriels3t/Simulacao-Camara-De-Nuvens-Geant4
   cd Simulacao-Camara-De-Nuvens-Geant4
2. **Compilar**:
Este projeto utiliza um Makefile para facilitar o processo de compilação e execução. A seguir estão os comandos para compilar e executar o projeto.

<b>Compilação</b>

* Para compilar todos os arquivos do projeto:
   ```bash
    make compilar-todos
* Para compilar arquivos específicos: 
    ```bash
    make compilar-FonteDeParticulas
    make compilar-GeradorPrimario
    make compilar-MeuDetector
    make compilar-main
* Para realizar o link e gerar o executável final:

    ```bash
    make 
3. **Executar**:
Para executar o programa, utilizando o arquivo de macro macros/moun.mac, e redirecionando a saída para dados/result.txt:
    
    ```bash
    make run
Caso prefira executar manualmente, você pode rodar o seguinte comando:
    
    ./main macros/moun.mac > dados/result.txt
Esses passos são suficientes para compilar e rodar o projeto. Certifique-se de ter todos os pré-requisitos instalados antes de seguir com a execução.

