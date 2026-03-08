#include <stdio.h>
#include <time.h>
#include <string.h>
#include <math.h>

#define BAR_WIDTH 60
#define BASE3_DIGITS 3
// Variables globales pour mémoriser la phrase précédente
char last_phrase[256] = "";

// Convertit un entier en base 3 sur N chiffres
void to_base3_fixed(int value, int digits, char *out) {
    for (int i = digits - 1; i >= 0; i--) {
        out[i] = (value % 3) + '0';
        value /= 3;
    }
    out[digits] = '\0';
}

// Retourne le mot correspondant à un chiffre en base 3
const char* word(char c) {
    if (c == '0') return "début";
    if (c == '1') return "milieu";
    return "fin";
}

// Construit la phrase en lisant les chiffres à l'envers (LSB → MSB)
void build_phrase(char *base3, char *out) {
    int len = strlen(base3);
    out[0] = '\0';

    for (int i = len - 1; i >= 0; i--) {
        strcat(out, word(base3[i]));

        if (i > 0) {
            if (base3[i-1] == '2')
                strcat(out, " de la ");
            else
                strcat(out, " du ");
        }
    }
}

// Convertit une valeur normalisée (entre min et max) en phrase
void value_to_phrase(double value, double min, double max, char *out) {
    double norm = (value - min) / (max - min);
    if (norm < 0) norm = 0;
    if (norm > 1) norm = 1;

    // Convertir en entier pour 3 chiffres en base 3
    int int_value = (int)(round(norm * (pow(3, BASE3_DIGITS) - 1)));

    char base3[BASE3_DIGITS + 1];
    to_base3_fixed(int_value, BASE3_DIGITS, base3);

    build_phrase(base3, out);
}

// Affiche la barre avec phrase
void draw_bar(double value, double min, double max)
{
    int pos = (value - min) / (max - min) * BAR_WIDTH;

    int m1 = BAR_WIDTH / 3;
    int m2 = 2 * BAR_WIDTH / 3;

    printf("│");

    for (int i = 0; i < BAR_WIDTH; i++)
    {
        if (i == m1)
            printf("FD");
        else if (i == m2)
            printf("DF");
        else if (i < pos)
            printf("█");
        else
            printf("░");
    }

    printf("│\n");

    char phrase[256];
    value_to_phrase(value, min, max, phrase);
    // Beep si la phrase a changé
    if (strcmp(phrase, last_phrase) != 0) {
        printf("\a"); // beep
        strcpy(last_phrase, phrase);
    }
    printf(" ");

    for (int i = 0; i < pos; i++)
        printf(" ");

    printf("%s\n", phrase);
}

int main()
{
    double age = 56;

    printf("\nVie (0 → 79 ans)\n");
    draw_bar(age, 0, 79);

    time_t t = time(NULL);
    struct tm *tm = localtime(&t);

    double hour = tm->tm_hour + tm->tm_min / 60.0;

    printf("\nJournee (6h → 24h)\n");
    draw_bar(hour, 6, 24);

    return 0;
}
