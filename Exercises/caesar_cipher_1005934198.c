// CSC A48 - Exercise 9 - Caesar Cipher v2.0
// Complete where indicated below.
//
// Do not add any additional functions
// and do not leave any print statements
// in your final submission for testing!
//
// F. Estrada, Updated March 2020.

#include<stdio.h>
#include<stdlib.h>
#include <string.h>

#define MAX_STR_LEN 2048

void caesar_cipher(unsigned char plaintext[MAX_STR_LEN], unsigned char password[MAX_STR_LEN])
{
 // This function encodes the input text in plaintext[] using the caesar
 // cipher process with the specified password (please see the exercise
 // description to see how that works).
 //
 // The function must ensure that the 'end-of-string' delimiter is preserved,
 // and that no other character can become the 'end-of-string'. 
 // 
 // You want to make sure you understand what values can be stored in each
 // entry of the plaintext[] string, and you'll want to look at an ASCII table
 // to check that your function does the right thing.
 //
 // *** TEST your code with multiple input strings, using different passwords,
 //     and verify it works in 
 //     every case! if you get incomplete because your function failed our
 //     tests it means you did not test carefully enough.
    //printf("CALLING ENCRYPTION\n");
    int len;
    for(len = 0; plaintext[len] != '\0'; len++);
    int passLen;
    for(passLen = 0; password[passLen] != '\0'; passLen++);
    int passCount = 0;
    //printf("input length %d, password length %d",len,passLen);
    for(int i = 0; i < len; i++){
        int temp;
        if(passCount + 1 < passLen){
            passCount++;
        } else {
            passCount = 0;
        }
        temp = (int)plaintext[i] + (int)password[passCount];
        if(temp >= 255){
            // Handle
            temp = temp % 255;
        } 
        if(temp == 0){
            temp = temp + 1;
        }
        
            //printf("Encrypted %c \n",temp);
        plaintext[i] = (char)temp;
        

    }
}

void caesar_decipher(unsigned char cryptotext[MAX_STR_LEN], unsigned char password[MAX_STR_LEN])
{
 // This function reverses the encryption process and returns the original
 // text given the encrypted string and the password used to encrypt it.
 // 
 // The function has the same constraints as 'caesar_cipher()', that is, it
 // must respect the 'end-of-string' delimiter, and ensure no other
 // character becomes 'end-of-string' after decoding.
 //
 // Be smart about how you implement this function!
    
 // TO DO: Implement this function

   int len;
    for(len = 0; cryptotext[len] != '\0'; len++);
    int passLen;
    for(passLen = 0; password[passLen] != '\0'; passLen++);
    int passCount = 0;
    for(int i = 0; i < len; i++){
        int temp;
        if(passCount + 1 < passLen){
            passCount++;
        } else {
            passCount = 0;
        }
        temp = (int)cryptotext[i] - (int)password[passCount];
        if(temp <= 0){
            temp = 255  + (temp % 255);
        } 
        if (temp == 0){
            temp = temp + 1;
        }
        cryptotext[i] = (char)temp;
    }     
}

#ifndef __testing

int main()
{
    
    char a_passage[5][MAX_STR_LEN]={"When did the world begin and how? \n   I asked a lamb, a goat, a cow:\n",
                                    "What’s it all about and why? \n    I asked a hog as he went by:\n",
                                    "Where will the whole thing end, and when? \n   I asked a duck, a goose and a hen:\n",
                                    "And I copied all the answers too, \n   A quack, a honk, an oink, a moo.\n",
                                    " --- Robert Clairmont\n"};
 
    printf("**** Original input text lines:\n\n");
    for (int i=0; i<5; i++)
        printf("%s",a_passage[i]);

    // Encode the input test lines
    caesar_cipher(&a_passage[0][0],"Blueberries are blue");
    caesar_cipher(&a_passage[1][0],"Blueberries are blue");
    caesar_cipher(&a_passage[2][0],"Blueberries are blue");
    caesar_cipher(&a_passage[3][0],"Blueberries are blue");
    caesar_cipher(&a_passage[4][0],"Blueberries are blue");

    printf("\n**** Encrypted text lines:\n\n");
    for (int i=0; i<5; i++)
        printf("%s",a_passage[i]);

    // Decode the encrypted strings
    caesar_decipher(&a_passage[0][0],"Blueberries are blue");
    caesar_decipher(&a_passage[1][0],"Blueberries are blue");
    caesar_decipher(&a_passage[2][0],"Blueberries are blue");
    caesar_decipher(&a_passage[3][0],"Blueberries are blue");
    caesar_decipher(&a_passage[4][0],"Blueberries are blue");

    printf("\n**** Decoded text lines (should be identical to original input!):\n\n");
    for (int i=0; i<5; i++)
        printf("%s",a_passage[i]);
    


    // // Custom Cipher Test Cases
    // // Password MisMatch
    // printf("---- Tests --- \n");

    // char input[MAX_STR_LEN] = {"I'm Not A Pyschopath \n I am a high functioning Sociopath Do your Research"};
    // char temp[MAX_STR_LEN];
    // strcpy(temp,input);
    // caesar_cipher(&input[0],"Sherlock");
    // if(strcmp(temp,input) == 0){
    //     printf("Did not Encrypt\n");
    //     return 1;
    // }
    // caesar_decipher(&input[0],"Sherlock Holmes");
    // if(strcmp(temp,input) == 0){
    //     printf("Password Mismatch\n");
    //     return 1;
    // }
    // printf("Passed Password Test\n");

    // // Greater than 255 Test
    // char input2[MAX_STR_LEN] = {"§"};
    // strcpy(input,input2);
    // strcpy(temp,input);
    // caesar_cipher(&input[0],"~");
    // if(strcmp(temp,input) == 0){
    //     printf("Did not Encrypt\n");
    //     return 1;
    // }
    // caesar_decipher(&input[0],"~");
    // if(strcmp(temp,input) != 0){
    //     printf("Wrong decryption\n");
    //     printf("****** Output **** \n");
    //     printf("%s\n",input);
    //     return 1;
    // }
    // printf("Passed Greater than 255 Test\n");
    // printf("Input\t Output\n");
    // printf("%s\t%s\n",temp,input);

    // // Zero Test
    // char input3[MAX_STR_LEN] = {"Ð"};
    // strcpy(input,input3);
    // strcpy(temp,input);
    // caesar_cipher(&input[0],"/");
    // if(strcmp(temp,input) == 0){
    //     printf("Did not Encrypt\n");
    //     return 1;
    // }
    // caesar_decipher(&input[0],"/");
    // if(strcmp(temp,input) != 0){
    //     printf("Wrong decryption\n");
    //     printf("****** Output **** \n");
    //     printf("%s\n",input);
    //     return 1;
    // }
    // printf("Passed Zero Test\n");
    // printf("Input\t Output\n");
    // printf("%s\t%s\n",temp,input);
    

    return 0;
    
}

#endif
