#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Clear(){
  printf("\033[0;0H\033[2J");
}

typedef struct {
  float valor;
  char *selo;
}produto;

typedef struct {
  produto *produtos;
  int total_produtos;
  float total_valor;
}carrinho;

carrinho init_car(){
  carrinho novo_car;
  novo_car.produtos = (produto*) malloc(2*sizeof(produto));
  novo_car.total_produtos = 0;
  novo_car.total_valor = 0;
  return novo_car;
}

void adicionar_produto_a_compra(float valor, char *selo, carrinho *carrinho){
  int indice = carrinho->total_produtos;
  int capacidade = indice+2;
  produto coisa;
  coisa.selo = (char*) malloc(7*sizeof(char));
  coisa.valor = valor;
  coisa.selo = selo;
  carrinho->produtos[indice] = coisa;
  carrinho->produtos = (produto*) realloc(carrinho->produtos,capacidade*sizeof(produto));
  carrinho->total_produtos++;
}

int get_total_de_produtos(carrinho *carrinho){
  return carrinho->total_produtos;
}

float get_valor_da_compra(carrinho *carrinho){
  carrinho->total_valor = 0;
  for(int x=0; x<carrinho->total_produtos; x++){
    carrinho->total_valor += carrinho->produtos[x].valor;
  }
  return carrinho->total_valor;
}

void set_desconto_ouro(carrinho *car){
  float desconto = 0;
  
  for(int x=0; x<car->total_produtos; x++){
    if(strcmp(car->produtos[x].selo, "ouro") == 0){
      desconto = car->produtos[x].valor * 0.10;
      car->produtos[x].valor -= desconto;
    }
  }
  if(desconto > 0){
    printf("\nDesconto de selo ouro aplicado: desconto de 10%% do valor dos produtos de selo ouro.\n");
  }
}

void set_desconto_prata(carrinho *carrinho){
  if(carrinho->total_produtos > 5){
    for(int x=0; x<carrinho->total_produtos; x++){
      if(strcmp (carrinho->produtos[x].selo, "prata") == 0){
        float desconto = carrinho->produtos[x].valor * 0.05;
        carrinho->produtos[x].valor -= desconto;
      }
    }
    printf("\nDesconto de selo prata aplicado: mais de 5 produtos no carrinho.\n");
  }
}
void set_desconto_bronze(carrinho *carrinho){
  int bronze = 0;
  for(int x=0; x<carrinho->total_produtos; x++){
    if(strcmp (carrinho->produtos[x].selo, "bronze") == 0){
      bronze++;
    }
  }
  if(bronze > 5){
    for(int x=0; x<carrinho->total_produtos; x++){
      if(strcmp (carrinho->produtos[x].selo, "bronze") == 0){
        float desconto = carrinho->produtos[x].valor * 0.05;
        carrinho->produtos[x].valor -= desconto;
      }
    }
    printf("\nDesconto de selo bronze aplicado: mais de 5 produtos de selo bronze no carrinho.\n");
  }
}
int main(void) {
  carrinho novo_car = init_car();
  int usu;
  float valor;
  int selo;
  
  while(1){
    char *prod = (char*) malloc(7*sizeof(char));
    printf("Bem-vindo ao adicionador de produtos Atom-13.\n1. Adicionar produto ao carrinho.\n2. Imprimir Total de produtos.\n3. Imprimir total da compra (sem descontos).\n4. Imprimir total da compra aplicando todos os descontos (Finaliza o programa).");
    printf("\n\nOpção: ");
    scanf("%d", &usu);
    
    switch(usu){
      case 1:
        printf("\nValor: ");
        scanf("%f", &valor);
        printf("Escolha o selo:\n 1. Ouro\n 2. Prata\n 3. Bronze");
        printf("\nSelo: ");
        scanf("%d", &selo);
        switch(selo){
          case 1:
            prod = "ouro";
          break;
          case 2:
            prod = "prata";
          break;
          case 3:
            prod = "bronze";
          break;
        }
        adicionar_produto_a_compra(valor, prod, &novo_car);
        usu=0;
        Clear();
        break;
      case 2:
        Clear();
        int total_prod = get_total_de_produtos(&novo_car);
        printf("\nTotal de produtos atuais: %d", total_prod);
        printf("\n\n");
        break;
      case 3:
        Clear();
        float total_comp = get_valor_da_compra(&novo_car);
        printf("\nTotal da compra sem descontos: R$ %.2f", total_comp);
        printf("\n\n");
        break;
      case 4:
        Clear();
        set_desconto_ouro(&novo_car);
        set_desconto_prata(&novo_car);
        set_desconto_bronze(&novo_car);
        float total_final = get_valor_da_compra(&novo_car);
        printf("\nTotal da compra com descontos: R$ %.2f", total_final);
        break;
    }
    if(usu==4){
      break;
    }
  }
  printf("\n\nPrograma finalizado!!!");
  return 0;
}