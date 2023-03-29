#include <stdio.h>
#include <ctype.h>
#define TAM_MAX 10000
#define FIM '$'

// colocar um numero na pilha
void push(int op, int *idx, int pilha[]);
// retirar um numero da pilha 
int pop(int *idx, int pilha[]);
// controlar o index da pilha 

// Uma função para transformar uma sequencia de char em numero;
int ConverterStringEmNumero(char *str);
char LeString(char *str, char buffer[], int *pidxb, int *pavisa);
char get(char buffer[], int *pidxb, int *pavisa);
char unget(int *pavisa);

int main(){
    int pilha[TAM_MAX];
    char op[TAM_MAX];
    char buffer[TAM_MAX];
    int idx =0;
    int *pidx = &idx;
    int idxb =0;
    int *pidxb = &idxb;
    int avisa =0;
    int *pavisa = &avisa;
    char c;
// colocar só os numeros na pilha
    int i=0;
    while((c=LeString(op,buffer, pidxb, pavisa))!= FIM){
        if(isdigit(op[0]))
            push(ConverterStringEmNumero(op), pidx, pilha);

        switch(c){
            case '+':
            push( pop(pidx,pilha) + pop(pidx,pilha), pidx, pilha);
            break;
            case '-':
            int num1 = pop(pidx,pilha);
            push(pop(pidx,pilha)- num1, pidx, pilha);
            break;
            case '*':
             push( pop(pidx,pilha) * pop(pidx,pilha), pidx, pilha);
            break;
            case '/':
            int num2= pop(pidx,pilha);
            push(pop(pidx,pilha)/ num2, pidx, pilha);
            break;
        }    
    };
    printf("Esse é o resultado:%d\n", pilha[0]);
   
    return 0;
}
void push(int n, int *idx, int pilha[]){
    pilha[*idx] = n;
    (*idx)++;

    
}

int pop(int *idx, int pilha[]){
    *idx = *idx -1;
    return pilha[*idx];
}
int ConverterStringEmNumero(char *str){
    int sinal, num=0;
    sinal = (str[0] == 1) ? -1: 1;

    for(int i=0; str[i]; i++){
        num = num*10 + (str[i]-'0');
    }
    return num*sinal;
}
char LeString(char *str, char buffer[], int *pidxb, int *pavisa){
    char c='a';
    while((c=get(buffer, pidxb, pavisa))==' ' || c=='\t' || c=='\b' || c=='\r')
        ;
    if( !isdigit(c) || c =='+' || c=='-' || c=='*' || c=='/'){
        str[0] =c;
        return c;
    }
    int i=0;
    str[i]=c;
    for(i=1;isdigit(c=get(buffer, pidxb, pavisa)); i++)
        str[i]= c;

    str[i] = '\0';
    if(c!=FIM)
        unget();
    else c='\0';
    return c;
}
char get(char buffer[], int *pidxb, int *pavisa){
    char c;
    if(*pavisa){
        *pavisa =0;
        return buffer[(*pidxb)-1];
    }
    c = getchar();
    buffer[*(pidxb)]= c;
    (*pidxb)++;
    return buffer[*pidxb -1];
}
char unget(int *pavisa){
    *pavisa = 1;
}
// 1 2 * 2 7 - *
// (1*2) *(2-7)= -10;
// dois numeros na pilha e um sinal resolve;
// [a,d];
