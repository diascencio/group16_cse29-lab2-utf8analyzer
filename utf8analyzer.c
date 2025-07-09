#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

//checks whether the string argument is valid ASCII(eg. all bytes are 127 or less)
//char str[]: the string to check
//returns a 1 for valid ascii, 0 for non-valid ascii
int IsAscii(char str[]){
	int i = 0;

	while(str[i]){
		if((unsigned char)str[i] > 127)
			return 0;
		i++;
	}
	return 1;
}

//Converts all ascii lowercase characters to ascii upercase
//char str[]: the string to be converted to uppercase
void ToUppercase(char str[]){
	int i = 0;

	while(str[i]){
		if(str[i] >= 97 && str[i] <= 122)
			str[i] -= 32;

		i++;
	}
	return;
}

//Finds the length of a given string
//char str[]: the string to find the length of
//returns the integer length
int ByteLength(char str[]){
	int i = 0, length = 0;
	while(str[i]){
		if(!(str[i] >= 0x80 && str[i] <= 0xBF))
			length++;
		i++;
	}
		
	return length;
}

//////////////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[]) {
    // implement the UTF-8 analyzer here
    char buffer[100], userString[100];
    int isAscii, byteLength;

    fgets(userString, 99, stdin);

    //check if userString is a valid ascii
    isAscii = IsAscii(userString);
    if(isAscii)
	    printf("Valid ASCII: true\n");
    else
	    printf("Valid ASCII: false\n");

    //print the converted uppercase converted string
    strcpy(buffer, userString); 
    ToUppercase(buffer);
    printf("Uppercased ASCII: %s", buffer);

    //find the length of the string
    byteLength = ByteLength(userString);
    printf("Length in bytes: %d\n", byteLength);
}
