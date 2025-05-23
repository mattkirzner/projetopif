# 🎮 SpeedAirHockey

## 📁 Estrutura do Repositório
projetopif/
├── src/ # Código-fonte do jogo
│ ├── main.c
│ ├── game.c
├── include/ # Arquivos de cabeçalho
│ ├── game.h
├── build/ # Arquivos binários gerados
├── README.md # Documentação do projeto
├── Makefile # Script de compilação



## 👥 1. Integrantes do Grupo (usuários no GitHub)

- Juliana Marçal Bezerra Jardim - [@juliana-m-b-jardim](https://github.com/juliana-m-b-jardim)  
- Luiz Henrique da Silva Neves - [@luiz380](https://github.com/luiz380)  
- Matheus José Cardoso Luna - [@matheusluna12](https://github.com/matheusluna12)  
- Matheus Rangel Kirzner - [@mattkirzner](https://github.com/mattkirzner)  
- Paulo César Ferreira de Assis - [@Mareaturbo2](https://github.com/Mareaturbo2)  
- Robson Sandro Andrade Cunha Filho - [@Robson3699](https://github.com/Robson3699)  

---

## 🧑‍🏫 2. Nome da Disciplina

**Programação Imperativa e Funcional - 2025.1**

---

## 🏫 3. Nome da Instituição de Ensino

**CESAR School**

---

## 🕹️ 4. Nome do Jogo Desenvolvido

**SpeedAirHockey**

---

## ⚙️ 5. Instruções Detalhadas para Compilar e Executar o Jogo
      ✅ Pré-requisitos
      Antes de começar, certifique-se de ter o ambiente pronto:

   🔧 Compilador GCC instalado
      (No Linux, execute: sudo apt install build-essential)

      📁 A pasta build/ precisa existir na raiz do projeto
      (Se necessário, crie com mkdir build)

      💻 Terminal configurado para rodar comandos
   🔨 Como Compilar
         Abra o terminal na raiz do projeto e execute:
         gcc ./src/*.c -I./include -o ./build/game
         Esse comando irá:

         ✅ Compilar todos os arquivos .c da pasta src/
         ✅ Incluir os cabeçalhos da pasta include/
         ✅ Gerar o executável game na pasta build/
   🚀 Como Executar
      Após compilar com sucesso, rode o jogo com:
      ./build/game
      O jogo será aberto diretamente no terminal, com suporte a controle via teclado.
      📌 Dica: Certifique-se de estar na raiz do projeto para que o caminho funcione corretamente.

## 📜 6. Descrição do Jogo

**SpeedAirHockey** é um jogo digital baseado no clássico Air Hockey de arcades.  
Desenvolvido em linguagem C, ele permite que dois jogadores se enfrentem localmente com uma experiência dinâmica e responsiva.

### 🎯 Regras:

- Dois jogadores competem tentando marcar gols.
- O primeiro a alcançar 13 pontos vence.
- O placar de cada jogador é exibido durante a partida.
- A bola acelera ao colidir com as bordas horizontais (eixo X).

### 🎮 Controles:

- **Player 1**: `W` (cima), `S` (baixo)  
- **Player 2**: `O` (cima), `L` (baixo)

> O sistema interpreta essas entradas para mover as raquetes e atualizar o estado do jogo.

---

**🎉 Bom jogo!**

