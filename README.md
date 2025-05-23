 "=================================================="
 "                SpeedAirHockey                    "
 "=================================================="

 ">> Estrutura do Repositório:"

 "/projeto"
 "├── src/        # Código-fonte (.c)"
 "├── include/    # Cabeçalhos (.h)"
 "├── build/      # Saídas de compilação"
 "├── README.md   # Descrição do projeto"
 "├── Makefile    # Arquivo de build (opcional)"
 "└── LICENSE     # Licença (opcional)"

 "=================================================="
 "1. Integrantes do Grupo (usuários no GitHub):"

- Juliana Marçal Bezerra Jardim - [@juliana-m-b-jardim](https://github.com/juliana-m-b-jardim)
- Luiz Henrique da Silva Neves - [@luiz380](https://github.com/luiz380)
- Matheus José Cardoso Luna - [@matheusluna12](https://github.com/matheusluna12)
- Matheus Rangel Kirzner - [@mattkirzner](https://github.com/mattkirzner)
- Paulo César Ferreira de Assis - [@Mareaturbo2](https://github.com/Mareaturbo2)
- Robson Sandro Andrade Cunha Filho - [@Robson3699](https://github.com/Robson3699)

 "=================================================="
 "2. Nome da Disciplina:"
 "   Programação Imperativa e Funcional - 2025.1"

 "3. Nome da Instituição de Ensino:"
 "   CESAR School"

 "4. Nome do Jogo Desenvolvido:"
 "   SpeedAirHockey"

 "=================================================="
 "5. Instruções para Compilar e Executar o Jogo:"

 "-> Pré-requisitos:"
 "   - Ter o compilador GCC instalado."
 "     (No Linux: sudo apt install build-essential)"

 "-> Compilar o jogo manualmente:"
 "   No terminal, estando na raiz do projeto, execute:"
 "     gcc ./src/*.c -I./include -o ./build/game"

 "   Este comando compila todos os arquivos .c na pasta 'src/',"
 "   incluindo os cabeçalhos da pasta 'include/', e gera o executável 'game'"
 "   dentro da pasta 'build/'."

 "-> Executar o jogo:"
 "   Após a compilação, execute o jogo com:"
 "     ./build/game"

 "   O jogo será iniciado no terminal com suporte a entrada de teclado."
 "   Certifique-se de que o terminal esteja na raiz do projeto."

 "=================================================="
 "6. Descrição do Jogo:"

 "SpeedAirHockey é um jogo digital baseado no clássico Air Hockey de arcades."
 "Desenvolvido em linguagem C, ele permite que dois jogadores se enfrentem localmente,"
 "com uma experiência dinâmica e responsiva."

 "-> Regras do jogo:"
 "   - Dois jogadores competem tentando marcar gols no adversário."
 "   - O primeiro a alcançar 13 pontos vence."
 "   - O placar de cada jogador é exibido durante a partida."
 "   - A bola acelera ao colidir com as bordas horizontais (eixo X)."

 "-> Controles:"
 "   - Player 1: W (cima), S (baixo)"
 "   - Player 2: O (cima), L (baixo)"

 "   O sistema interpreta as entradas para mover as raquetes na tela e atualizar o jogo."

 "=================================================="
 "                 Bom jogo! 🎮                      "
 "=================================================="
