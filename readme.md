# Campo Minado em C

Este projeto é uma implementação simples do clássico **Campo Minado** (Minesweeper) em linguagem **C**, executado diretamente no console.

## Sobre o Projeto

O jogo simula um campo minado de **8x8**, com diferentes níveis de dificuldade:

- **Fácil**: menos bombas por linha
- **Médio**: quantidade moderada de bombas
- **Difícil**: campo altamente bombardeado

O objetivo é abrir todas as casas que **não possuem bombas** para vencer.

O arquivo principal do projeto é:

```
campo_minado.c
```

---

## Como Jogar

1. Compile o código com um compilador C (por exemplo, `gcc`):

   ```bash
   gcc campo_minado.c -o campo_minado
   ```

2. Execute o programa:

   ```bash
   ./campo_minado
   ```

3. Escolha a dificuldade:

   ```
   [1] - Fácil
   [2] - Médio
   [3] - Difícil
   ```

4. Digite a posição (linha, coluna) para revelar uma casa.

   Exemplo:

   ```
   Digite a posição (x, y): 2, 3
   ```

5. Vence quem abrir todas as casas sem bomba!  
   Você pode digitar `0, 0` a qualquer momento para sair do jogo.

---

## Funcionalidades

- Escolha de **nível de dificuldade**.
- **Geração aleatória** de bombas.
- **Campo dinâmico** que mostra posições abertas e bombas.
- Contador de **número de jogadas**.
- **Condições de vitória e derrota**.

---

## Tecnologias Utilizadas

- Linguagem C (padrão C99/C11)
- Biblioteca padrão (`stdio.h`, `stdlib.h`, `string.h`, `time.h`)

---

## Estrutura

| Função | Descrição |
|:-|:-|
| `startGame()` | Exibe a tela inicial. |
| `setDifficulty()` | Define a dificuldade e as configurações do jogo. |
| `createField()` | Gera o campo com bombas e limites. |
| `calculateBombs()` | Conta bombas ao redor de uma casa. |
| `revealBombCount()` | Abre casas e revela áreas vazias. |
| `showField()` | Exibe o campo de jogo. |
| `showPos()` | Mostra a posição escolhida pelo jogador. |
| `play()` | Loop principal para jogar. |
| `main()` | Inicia o jogo. |

---

## Melhorias Futuras

- Adicionar marcação de bandeiras nas casas suspeitas.

---

## Autor

Desenvolvido por **Jonathan Santos**