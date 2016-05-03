#include "console.h"
#include "string.h"

int kern_entry()
{

    console_clear();
    console_write("Hello, Wos!\n");

    char str[20] = "test copy";
    char str1[20] = ", 123456\n";

    strcat(str, str1);
    console_write(str);

    char str2[32];

    tostring(str2, strcmp("123", "123"));
    console_write(str2);
    console_write("\n----\n");
    tostring(str2, strcmp("1234", "1235"));
    console_write(str2);
    console_write("\n----\n");
    tostring(str2, strcmp("", ""));
    console_write(str2);
    console_write("\n----\n");


    char str0[10] = "12345";
    char str00[10] = "-12343";

    int32_t num = toint(str0) + toint(str00);

    tostring(str2, num);

    console_write(str2);
    console_write("\n----\n");

    return 0;
}
