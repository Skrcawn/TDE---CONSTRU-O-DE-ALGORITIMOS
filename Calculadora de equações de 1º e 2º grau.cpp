#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>


void extrair_coeficientes(char eq[], float *a, float *b, float *c) {
    *a = 0.0f;
    *b = 0.0f;
    *c = 0.0f;

    char *current_char = eq;
    char term_buffer[50];
    int i_term;
    char sign;
    float value;

    while (*current_char != '\0' && *current_char != '\n') {
        sign = '+';
        if (*current_char == '+' || *current_char == '-') {
            sign = *current_char;
            current_char++;
        }

        i_term = 0;
        while (*current_char != '\0' && *current_char != '\n' && *current_char != '+' && *current_char != '-') {
            term_buffer[i_term++] = *current_char;
            current_char++;
        }
        term_buffer[i_term] = '\0';

        if (strlen(term_buffer) == 0) continue;

        char *x2_pos = strstr(term_buffer, "x^2");
        char *x_pos = strstr(term_buffer, "x");

        if (x2_pos != NULL) {
            if (x2_pos == term_buffer) {
                value = 1.0f;
            } else {
                char num_str[20];
                strncpy(num_str, term_buffer, x2_pos - term_buffer);
                num_str[x2_pos - term_buffer] = '\0';
                value = atof(num_str);
            }
            *a += (sign == '-') ? -value : value;
        }
        else if (x_pos != NULL) {
            if (x_pos == term_buffer) {
                value = 1.0f;
            } else {
                char num_str[20];
                strncpy(num_str, term_buffer, x_pos - term_buffer);
                num_str[x_pos - term_buffer] = '\0';
                value = atof(num_str);
            }
            *b += (sign == '-') ? -value : value;
        }
        else {
            value = atof(term_buffer);
            *c += (sign == '-') ? -value : value;
        }
    }
}


void resolver_equacao(float a, float b, float c) {
    float delta, x1, x2;

    printf("-------------------------------------------------------\n");
    printf("Coeficientes da equação:\n");
    printf("  a = %.2f", a);
    printf("  b = %.2f", b);
    printf("  c = %.2f\n", c);
    printf("\n", c);

    if (a != 0) {
        printf("Grau da Equação: 2º grau\n");
        delta = b * b - 4 * a * c;
        printf("Valor do Discriminante (Delta): %.2f\n", delta);

        if (delta < 0) {
            printf("Possui Solução Real? Não\n");
            printf("Solução: x = N.A. (As soluções são números complexos, não reais.)\n");
        } else if (delta == 0) {
            x1 = -b / (2 * a);
            printf("Possui Solução Real? Sim\n");
            printf("Solução: x = %.2f (Raiz dupla)\n", x1);
        } else {
            x1 = (-b + sqrt(delta)) / (2 * a);
            x2 = (-b - sqrt(delta)) / (2 * a);
            printf("Possui Solução Real? Sim\n");
            printf("Soluções: x1 = %.2f, x2 = %.2f\n", x1, x2);
        }
    }
    else if (b != 0) {
        printf("Grau da Equação: 1º grau\n");
        x1 = -c / b;
        printf("Possui Solução Real? Sim\n");
        printf("Solução: x = %.2f\n", x1);
    }
    else {
        if (c == 0) {
            printf("Grau da Equação: N.A. (Identidade)\n");
            printf("Possui Solução Real? Sim (soluções são infinitas)\n");
            printf("Solução: Qualquer valor para x é válido.\n");
        } else {
            printf("Grau da Equação: N.A. (Não é uma equação válida)\n");
            printf("Possui Solução Real? Não\n");
            printf("Solução: x = N.A.\n");
        }
    }
}

int main() {
    setlocale(LC_ALL, "Portuguese");

    char eq[100];
    float a, b, c;

    printf("    RESOLVEDOR DE EQUAÇÕES DE 1º E 2º GRAU         \n");
    printf("________________________________________________________________________________\n");
    printf("Instruções para utilizar:\n");
    printf(" - Digitar a equação no formato padrão (ex: +1x^2+2x+1).\n");
    printf(" - Termos sem coeficiente numérico (ex: x^2 ou -x) serão tratados como 1 ou -1.\n");
    printf("--------------------------------------------------------------------------------\n");

    while (1) {
        printf("Equação: ");
        fflush(stdin);
        fgets(eq, sizeof(eq), stdin);

        extrair_coeficientes(eq, &a, &b, &c);
        resolver_equacao(a, b, c);

        printf("--------------------------------------------------------------------------------\n");
        printf("Aperte ENTER para começar outra resolução de equação...\n");
        getchar(); 
    }

    return 0;
}

