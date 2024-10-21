#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct _data {
   int dia;
   int mes;
   int ano;
   int hora;
   int minuto;
};
typedef struct _data Data;

struct _evento {
   int codigo;
   Data dataEvento;
   float duracao;
   char descricao[100];
   struct _evento *proximo;
};
typedef struct _evento Evento;

Evento *agenda = NULL;

/*Função para criar um novo evento*/
Evento *criarEvento(int codigo, Data dataEvento, float duracao, char descricao[100]) {
   Evento *novo = (Evento *)malloc(sizeof(Evento));
   novo->codigo = codigo;
   novo->dataEvento = dataEvento;
   novo->duracao = duracao;
   strcpy(novo->descricao, descricao);
   novo->proximo = NULL;
   return novo;
}

/*Função para inserir um evento na agenda*/
void incluirEvento(int codigo, Data dataEvento, float duracao, char descricao[100]) {
   Evento *novo = criarEvento(codigo, dataEvento, duracao, descricao);
   if (agenda == NULL) {
       agenda = novo;
   } else {
      Evento *aux = agenda;
      while (aux->proximo != NULL) {
            aux = aux->proximo;
      }
      aux->proximo = novo;
   }
   printf("Evento adicionado com sucesso!\n");
}

/* Função para consultar eventos na agenda por data e/ou hora*/
void consultarEventos(Data dataEvento) {
   if (agenda == NULL) {
      printf("Agenda vazia.\n");
      
   }

   Evento *aux = agenda;
   int encontrado = 0;

   while (aux != NULL) {
      if (aux->dataEvento.dia == dataEvento.dia &&
          aux->dataEvento.mes == dataEvento.mes &&
          aux->dataEvento.ano == dataEvento.ano) {
         if (dataEvento.hora == -1) {
            printf("Codigo: %d\n", aux->codigo);
            printf("Data: %02d/%02d/%04d\n", aux->dataEvento.dia, aux->dataEvento.mes, aux->dataEvento.ano);
            printf("Hora: %02d:%02d\n", aux->dataEvento.hora, aux->dataEvento.minuto);
            printf("Duracao: %.1f\n", aux->duracao);
            printf("Descricao: %s\n\n", aux->descricao);
            encontrado = 1;
         } else if (aux->dataEvento.hora == dataEvento.hora &&
                    aux->dataEvento.minuto == dataEvento.minuto) {
            printf("Codigo: %d\n", aux->codigo);
            printf("Data: %02d/%02d/%04d\n", aux->dataEvento.dia, aux->dataEvento.mes, aux->dataEvento.ano);
            printf("Hora: %02d:%02d\n", aux->dataEvento.hora, aux->dataEvento.minuto);
            printf("Duracao: %.1f\n", aux->duracao);
            printf("Descricao: %s\n\n", aux->descricao);
            encontrado = 1;
            break;
         }
      }
      aux = aux->proximo;
   }

   if (!encontrado) {
      printf("Agenda vazia para a consulta realizada.\n");
   }
}


/* Função para alterar a descrição e a duração de um evento na agenda*/
void alterarEvento(Data dataEvento, float duracao, char descricao[100]) {
   if (agenda == NULL) {
      printf("Agenda vazia. Nenhum evento para alterar.\n");
      
   }

   Evento *aux = agenda;
   int encontrado = 0;

   while (aux != NULL) {
      if (aux->dataEvento.dia == dataEvento.dia &&
          aux->dataEvento.mes == dataEvento.mes &&
          aux->dataEvento.ano == dataEvento.ano &&
          aux->dataEvento.hora == dataEvento.hora &&
          aux->dataEvento.minuto == dataEvento.minuto) {
          encontrado = 1;
         break;
      }
      aux = aux->proximo;
   }

   if (encontrado) {
      strcpy(aux->descricao, descricao);
      aux->duracao = duracao;
      printf("Evento alterado com sucesso!\n");
   } else {
      printf("Compromisso nao encontrado.\n");
   }
}
/*Função para excluir um evento da agenda*/
void excluirEvento(Data dataEvento) {
   if (agenda == NULL) {
      printf("Agenda vazia. Nenhum evento para excluir.\n");
      
   }

   Evento *atual = agenda;
   Evento *anterior = NULL;
   int encontrado = 0;

   while (atual != NULL) {
      if (atual->dataEvento.dia == dataEvento.dia &&
          atual->dataEvento.mes == dataEvento.mes &&
          atual->dataEvento.ano == dataEvento.ano &&
          atual->dataEvento.hora == dataEvento.hora &&
          atual->dataEvento.minuto == dataEvento.minuto) {
         encontrado = 1;
         break;
      }
      anterior = atual;
      atual = atual->proximo;
   }

   if (encontrado) {
      if (anterior == NULL) {
         agenda = atual->proximo;
      } else {
         anterior->proximo = atual->proximo;
      }
      free(atual);
      printf("Evento excluido com sucesso!\n");
   } else {
      printf("Compromisso nao encontrado.\n");
   }
}


/* Função para listar todos os eventos da agenda*/
void listarEventos() {
   if (agenda == NULL) {
      printf("Agenda vazia.\n");
      
   }

   Evento *aux = agenda;

   while (aux != NULL) {
      printf("Codigo: %d\n", aux->codigo);
      printf("Data: %02d/%02d/%04d\n", aux->dataEvento.dia, aux->dataEvento.mes, aux->dataEvento.ano);
      printf("Hora: %02d:%02d\n", aux->dataEvento.hora, aux->dataEvento.minuto);
      printf("Duracao: %.1f\n", aux->duracao);
      printf("Descricao: %s\n\n", aux->descricao);
      aux = aux->proximo;
   }
}

int main() {
   int opcao;
   Data dataEvento;
   int codigo;
   float duracao;
   char descricao[100];

   do {
      printf("\n\tUFFSAgenda :\n");
      printf("\t1 - Incluir\n\t2 - Consultar\n\t3 - Alterar\n\t4 - Excluir\n\t5 - Listar todos\n\t6 - Sair\n");
      scanf("%d", &opcao);

      switch (opcao) {
         case 1:
            printf("Digite o codigo do evento: ");
            scanf("%d", &codigo);
            printf("Digite a data do evento (dd/mm/aaaa): ");
            scanf("%d/%d/%d", &dataEvento.dia, &dataEvento.mes, &dataEvento.ano);
            printf("Digite a hora do evento (hh:mm): ");
            scanf("%d:%d", &dataEvento.hora, &dataEvento.minuto);
            printf("Digite a duracao do evento: ");
            scanf("%f", &duracao);
            printf("Digite a descricao do evento: ");
            scanf(" %[^\n]", descricao);
            incluirEvento(codigo, dataEvento, duracao, descricao);
            break;

         case 2:
            printf("Digite a data do evento (dd/mm/aaaa): ");
            scanf("%d/%d/%d", &dataEvento.dia, &dataEvento.mes, &dataEvento.ano);
            printf("Deseja consultar por hora especifica? (S/N): ");
            char resposta;
            scanf(" %c", &resposta);
            if (resposta == 'S' || resposta == 's') {
               printf("Digite a hora do evento (hh:mm): ");
               scanf("%d:%d", &dataEvento.hora, &dataEvento.minuto);
            } else {
               dataEvento.hora = -1;  
            }
            consultarEventos(dataEvento);
            break;

         case 3:
            printf("Digite a data e hora do evento a ser alterado (dd/mm/aaaa hh:mm): ");
            scanf("%d/%d/%d %d:%d", &dataEvento.dia, &dataEvento.mes, &dataEvento.ano, &dataEvento.hora, &dataEvento.minuto);
            printf("Digite a nova descricao do evento: ");
            scanf(" %[^\n]", descricao);
            printf("Digite a nova duracao do evento: ");
            scanf("%f", &duracao);
            alterarEvento(dataEvento, duracao, descricao);
            break;

         case 4:
            printf("Digite a data e hora do evento a ser excluido (dd/mm/aaaa hh:mm): ");
            scanf("%d/%d/%d %d:%d", &dataEvento.dia, &dataEvento.mes, &dataEvento.ano, &dataEvento.hora, &dataEvento.minuto);
            excluirEvento(dataEvento);
            break;

         case 5:
            listarEventos();
            break;

         case 6:
            printf("Tchauuuuuuu ...\n");
            break;

         default:
            printf("Opção invalida. Tente novamente.\n");
            break;
      }

      printf("\n");

   } while (opcao != 6);

   return 0;
}
