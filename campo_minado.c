#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define FIELD_SIZE 10

int field[FIELD_SIZE][FIELD_SIZE], current;
char difficulty[7];
int bombs = 0, reveals = 0, plays = 1;
int chance, bombs_limit, line_limit;
int endGame = 0;

void startGame()
{
  printf("-----------------------------------------------\n");
  printf("---------|       CAMPO MINADO        |---------\n");
  printf("---------|    Desenvolvido em C      |---------\n");
  printf("---------|   Por: Jonathan Santos    |---------\n");
  printf("-----------------------------------------------\n");
}

void setDifficulty()
{
  int difficultyLevel;

  printf("-----------------------------------------------\n");
  printf("---------|  Selecao de Dificuldade   |---------\n");
  printf("---------|       [1] - Facil         |---------\n");
  printf("---------|       [2] - Medio         |---------\n");
  printf("---------|      [3] - Dificil        |---------\n");
  printf("-----------------------------------------------\n");
  printf("---------| Digite a dificuldade: ");
  scanf("%d", &difficultyLevel);
  
  while (difficultyLevel != 1 && difficultyLevel != 2 && difficultyLevel != 3)
  {
    printf("---------| Nivel de dificuldade invalida. \n");
    printf("---------| Digite a dificuldade: ");
    scanf("%d", &difficultyLevel);
  }

  switch (difficultyLevel)
  {
    case 1:
    strcpy(difficulty, "Facil  ");
    bombs_limit = 8;
    line_limit = 1;
    break;
    case 2:
    strcpy(difficulty, "Medio  ");
    bombs_limit = 16;
    line_limit = 2;
    break;
    case 3:
    strcpy(difficulty, "Dificil");
    bombs_limit = 24;
    line_limit = 3;
    break;
    
    default:
    break;
  }
  chance = bombs_limit*100/64;
}

void createField()
{
  for (int i = 0; i < FIELD_SIZE; i++)
  {
    int line_bombs = 0;
    for(int j = 0; j < FIELD_SIZE; j++)
    {
      int value;
      if (i == 0 && j == 0)
        value = 201; // Canto Superior Esquerdo
      else if(i == 0 && j == 9)
        value = 187; // Canto Superior Direito
      else if(i== 9 && j == 0)
        value = 200; // Canto Inferior Esquerdo
      else if(i == 9 && j == 9)
        value = 188; // Canto Inferior Direito
      else if(i == 0 || i == 9)
        value = 205; // Borda Horizontal
      else if(j == 0 || j == 9)
        value = 186; // Borda Vertical
      else if(rand()%100 < chance && bombs < bombs_limit && line_bombs < line_limit)
      {
        value = 15; // Bomba
        bombs++;
        line_bombs++;
      }
      else
        value = -1;
        
      field[i][j] = value;
    }
  }
}

int calculateBombs(int x, int y)
{
  int bombs = 0;
  for(int i = -1; i <= 1; i++)
  {
    for(int j = -1; j <= 1; j++)
    {
      if(i == 0 && j == 0) continue;
      if(field[x+i][y+j] == 15) bombs++;
    }
  }
  return bombs;
}

void revealBombCount(int x, int y)
{
  if(field[x][y] != -1)
    return;

  int bombsCount = calculateBombs(x, y);
  field[x][y] = bombsCount;
  reveals++;

  if(bombsCount == 0)
    for(int i = -1; i <= 1; i++) 
    {
      for (int j = -1; j <= 1; j++) 
      {
        revealBombCount(x + i, y + j);
      }
    }
}

void showField()
{
  printf("-----------------------------------------------\n");
  printf("---------|        Campo Minado       |---------\n");
  printf("---------|   Dificuldade: %s    |---------\n", difficulty);
  printf("---------|         Jogada %02d         |---------\n", plays);
  printf("-----------------------------------------------\n");
  for(int i = -1; i < 10; i++)
  {
    printf("---------|   ");
    for(int j = -1; j < 10; j++)
    {
      if(i < 0) // Faz a numeração das colunas
      {
        if(j < 0)
          printf("    ");
        else if(j < 8)
          printf("%d ", j+1);
        else if(j == 8)
          printf("  ");
        continue;
      }

      if(j < 0) // Faz a numeração das linhas
      {
        if(i < 1 || i > 8)
          printf("  ");
        else if(i <= 8)
          printf("%d ", i);
        continue;
      }

      int value1 = field[i][j];
      int value2 = 32;

      if(value1 == 200 || value1 == 201 || value1 == 205)
        value2 = 205;

      if(value1 == -1)
        value1 = 254;
      else if(value1 <= 8) 
        value1 += 48; // Incrementação para equiparar o Inteiro com seu código ASCII

      if(value1 == 15 && !endGame)
        value1 = 254; 

      printf("%c%c", value1, value2);
    }
    printf("  |---------\n");
  }
  
  printf("-----------------------------------------------\n");
}

void showPos(int pos[2])
{
  int x = pos[0];
  int y = pos[1];
  current = field[x][y];
  
  if(current == -1)
  {
    revealBombCount(x, y);
    plays++;
  }
  if(current == 15)
    endGame = 1;
  
  showField();
  printf("---------| Bombas: [%d]\n", bombs);
  printf("---------| Ultima posicao aberta: [%d, %d]\n", pos[0], pos[1]);
}

int play()
{
  int pos[2];
  while (1)
  {
    printf("---------| Digite a posicao (x, y): ");
    scanf("%d, %d", &pos[0], &pos[1]);
    
    if(pos[0] == 0 && pos[1] == 0)
    {
      printf("Você escolheu sair!");
      exit(1);
      break;
    }
      
    if(pos[0] < 1 || pos[0] > 8 || pos[1] < 1 || pos[1] > 8)
    {
      printf("Posicao invalida!");
      continue;
    }
    system("cls");
    showPos(pos);

    if(current == 15)
      return 0;
    if(64 - bombs == reveals)
      return 99;
  }
}

int main()
{
  srand(time(NULL));

  startGame();
  setDifficulty();
  createField();
  system("cls");
  showField();
  printf("---------| Bombas: [%d]\n", bombs);
  
  int result = play();

  if(result == 0)
    printf("---------| Voce perdeu!");
  else if(result == 99)
    printf("---------| Parabens! Voce venceu!");
  else
    printf("---------| Nem venceu nem perdeu, algum erro aconteceu!");
}