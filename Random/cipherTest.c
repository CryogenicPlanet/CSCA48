#include <stdio.h>
#include <string.h>
#include <ctype.h>
int hasNewLine(char* str){
    return (str && *str && str[strlen(str) - 1] == '\n') ? 0 : 1;
}
int isValidText(char* str){
    for(int i = 0; i < strlen(str)-1; i++){
        if(isalnum(str[i]) == 0 && ispunct(str[i]) == 0 && isspace(str[i]) == 0){
            printf("%c\n",str[i]);
            return 1;
        }
    }
    return 0;
}
int main(int argc, char const *argv[])
{
    printf("New line test %d\n",hasNewLine("bm`^qeO�@ld��ce�i�enh^t}lT"));
    printf("Valid String Test %d\n",isValidText("Hello All A48 people! this is a reminder that the on-line lecture\n"));
    printf("Valid String Test %d\n",isValidText("bm`^qeO�@ld��ce�i�enh^t}lT"));
    printf("%c\n",'a' + 1);
    printf("%d\n", -1 % 255);
    return 0;
}
