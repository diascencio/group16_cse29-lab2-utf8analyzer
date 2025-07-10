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

     int count = 0;                                                                                          int pos = 0;                                                                                            int len = strlen(the_name_of_input_str);                                                                                                                                                                        while (pos < len) {                                                                                         int char_len = get_utf8_char_length(the_name_of_input_str, pos);                                        count++;                                                                                                pos += char_len;                                                                                    }                                                                                                       printf("The number of codepoints is: %d\n", count);                                                     }                                                                                                           int byte_lengths[1000];                                                                                 count = 0;                                                                                              pos = 0;                                                                                                                                                                                                        while (pos < len) {                                                                                         int char_len = get_utf8_char_length(test_strings[i], pos);                                              byte_lengths[count] = char_len;                                                                         count++;                                                                                                pos += char_len;                                                                                    }                                                                                                                                                                                                               printf("Bytes per codepoint: ");                                                                        for (int j = 0; j < count; j++) {                                                                           printf("%d ", byte_lengths[j]);                                                                     }                                                                                                       printf("\n"); 
}

int get_utf8_char_length(char* str, int pos) {
    unsigned char byte = (unsigned char)str[pos];
    
    if (byte <= 0x7F) {
        return 1;  
    } else if ((byte & 0xE0) == 0xC0) {
        return 2;  
    } else if ((byte & 0xF0) == 0xE0) {
        return 3;  
    } else if ((byte & 0xF8) == 0xF0) {
        return 4;  
    }
    
    return -1;
}

int32_t decode_utf8_char(const char* str, int pos, int char_len) {
    unsigned char* bytes = (unsigned char*)str;
    int32_t codepoint = 0;
    
    if (char_len == 1){
        codepoint = bytes[pos];
    }
    else if (char_len == 2){
        codepoint = ((bytes[pos] & 0x1F) << 6) | (bytes[pos + 1] & 0x3F);
    }
    else if (char_len == 3){
        codepoint = ((bytes[pos] & 0x0F) << 12) | 
                       ((bytes[pos + 1] & 0x3F) << 6) | 
                       (bytes[pos + 2] & 0x3F);
    }
    else if (char_len == 4){
        codepoint = ((bytes[pos] & 0x07) << 18) | 
                       ((bytes[pos + 1] & 0x3F) << 12) | 
                       ((bytes[pos + 2] & 0x3F) << 6) | 
                       (bytes[pos + 3] & 0x3F);
    }
    return codepoint;
}
