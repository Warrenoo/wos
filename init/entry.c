#include "console.h"
#include "string.h"

int kern_entry()
{

    console_clear();
    console_write("Hello, Wos!\n");

    char str[20] = "test copy\n";
    char str1[20];

    strcpy(str1, str);
    console_write(str);
    console_write(str1);

    return 0;
}
