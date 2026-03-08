#include <stdio.h>
#include <time.h>
#include <string.h>

#define BAR_WIDTH 60

void to_base3(int value, char *out)
{
    char tmp[32];
    int i = 0;

    if (value == 0)
    {
        strcpy(out, "0");
        return;
    }

    while (value > 0)
    {
        tmp[i++] = '0' + (value % 3);
        value /= 3;
    }

    int j = 0;
    while (i > 0)
        out[j++] = tmp[--i];

    out[j] = '\0';
}

const char* word(char c)
{
    if (c == '0') return "debut";
    if (c == '1') return "milieu";
    return "fin";
}

void build_phrase(char *base3, char *out)
{
    int len = strlen(base3);
    out[0] = '\0';

    for (int i = len - 1; i >= 0; i--)
    {
        const char *w = word(base3[i]);
        strcat(out, w);

        if (i > 0)
        {
            if (base3[i-1] == '2')
                strcat(out, " de la ");
            else
                strcat(out, " du ");
        }
    }
}

void draw_bar(double value, double min, double max)
{
    int pos = (value - min) / (max - min) * BAR_WIDTH;

    int m1 = BAR_WIDTH / 3;
    int m2 = 2 * BAR_WIDTH / 3;

    printf("│");

    for (int i = 0; i < BAR_WIDTH; i++)
    {
        if (i == m1)
            printf("1");
        else if (i == m2)
            printf("2");
        else if (i < pos)
            printf("█");
        else
            printf("░");
    }

    printf("│\n");

    char base3[32];
    char phrase[256];

    to_base3((int)value, base3);
    build_phrase(base3, phrase);

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