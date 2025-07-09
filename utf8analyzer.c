#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>


//aid function for 4,5,6
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

// Function 4
void codepoint_number(){
    int codepoint_count = 0;
    int pos = 0;
    int len = strlen(test_string);
    
    while (pos < len) {
        int char_len = get_utf8_char_length(test_string, pos);
        codepoint_count++;
        pos += char_len;
    }
    printf("Number of code points: %d\n", codepoint_count);
}


//Function 5

void bytes_per_codepoint(){
unsigned int codepoints[1000]; // Assuming max 1000 codepoints
    int count = 0;
    int pos = 0;
    
    while (pos < len) {
        int char_len = get_utf8_char_length(test_string, pos);
        unsigned int codepoint = decode_utf8_char(test_string, pos, char_len);
        codepoints[count] = codepoint;
        count++;
        pos += char_len;
    }
    
    printf("Code points as decimal numbers: ");
    for (int j = 0; j < count; j++) {
        printf("%u ", codepoints[j]);
    }
    printf("\n");
}


//Function 6

void length_in_bytes(){
    int byte_lengths[1000];
    int count = 0;
    int pos = 0;
    
    while (pos < len) {
        int char_len = get_utf8_char_length(test_string, pos);
        byte_lengths[count] = char_len;
        count++;
        pos += char_len;
    }
    
    printf("Bytes per code point: ");
    for (int j = 0; j < count; j++) {
        printf("%d ", byte_lengths[j]);
    }
    printf("\n");

    return 0;
}



// Function 7
uint8_t codepoint_size(char string) {

        uint8_t byte = string;

        if(byte == 0b00000000){
                return 0;
        } else if((byte & 0b10000000) == 0b00000000){
                return 1;
        } else if ((byte & 0b11100000) == 0b11000000){
                return 2;
        } else if ((byte & 0b11110000) == 0b11100000){
                return 3;
        } else if ((byte & 0b11111000) == 0b11110000){
                return 4;
        }

        return -1;
}

void utf8_substring_6(char str[]) {
    //Implement utf8_substring in the body of this function!


        uint8_t byte_start = 0;

        uint8_t byte_end = byte_start;
        for(int i = 0; i < 6; i++){
                byte_end += codepoint_size(str[byte_end]);
        }

        int sub_length = byte_end - byte_start;
        char substring[sub_length + 1];
        for(int i = 0; i < sub_length; i++){
                substring[i] = str[byte_start + i];
        }
        substring[sub_length] = 0b00000000;

        printf("%s\n", substring);
}

// Function 8

void utf8_substring(const char str[], int start, int end, char substring[]) {
        int byte_start = 0;
        for (int i = 0; i < start; i++) {
                if(str[byte_start] == '\0') {
                substring[0] = '\0';
                        return;
                }
                int size = codepoint_size(str[byte_start]);
                if(size <= 0) {
                        substring[0] = '\0';
                        return;
                }
                byte_start += size;
        }

        int byte_end = byte_start;
        for (int i = start; i < end; i++) {
                if (str[byte_end] == '\0') {
                        break;
                }
                int size = codepoint_size(str[byte_end]);
                if (size <= 0) {
                        break;
                }
                byte_end += size;
        }

        int sub_length = byte_end - byte_start;
        for (int i = 0; i < sub_length; i++) {
                substring[i] = str[byte_start + i];
        }
            substring[sub_length] = '\0';
}

uint32_t decode(char encoding[]){
        uint32_t result = 0;

        uint8_t byte = (uint8_t) encoding[0];

        if((byte & 0x80) == 0){
                return byte;
        } else if((byte & 0xE0) == 0xC0){

                result += (encoding[1] & 0b00111111);
                result += ((byte & 0b00011111) << 6);

                return result;
        } else if((byte & 0xF0) == 0xE0){

                result += (encoding[2] & 0b00111111);
                result += ((encoding[1] & 0b00111111) << 6);

                result += ((byte & 0b00001111) << 12);
                return result;
        } else if((byte & 0xF8) == 0xF0){

                result += (encoding[3] & 0b00111111);
                result += ((encoding[2] & 0b00111111) << 6);
                result += ((encoding[1] & 0b00111111) << 12);
                result += ((byte & 0b00000111) << 18);

                return result;
        }

        return 0;
}

void animal_emoji(char str[]){
    char result[5];
    int codepoint_index = 0;
    int byte_index = 0;
    
    while (str[byte_index] != '\0') {
        utf8_substring(str, codepoint_index, codepoint_index + 1, result);
        uint32_t animal = decode(result);

        if ((animal >= 0x1F400 && animal <= 0x1F43F) ||
            (animal >= 0x1F980 && animal <= 0x1F9AE)) {
            printf("%s", result);
        }

        byte_index += codepoint_size(str[byte_index]);
        codepoint_index++;
    }
    printf("The number of codepoints is: %d\n", count);
}


//Function 9
void encode_utf8(uint32_t num, char dest[]) {
        //TODO: Complete this function

    	dest[0] = dest[1] = dest[2] = dest[3] = 0;
    
    	if (num <= 0x7F) {

        	dest[0] = (char)num;
    	}
    	else if (num <= 0x7FF) {

        	char byte1 = (char)((num & 0b11111000000) >> 6);
        	byte1 = byte1 | 0b11000000;
        
        	char byte2 = (char)((num & 0b111111) | 0b10000000);
        
        	dest[0] = byte1;
        	dest[1] = byte2;
    	}
    	else if (num <= 0xFFFF) {

        	char byte1 = (char)((num & 0b1111000000000000) >> 12);
        	byte1 = byte1 | 0b11100000;
        
        	char byte2 = (char)((num & 0b111111000000) >> 6);
        	byte2 = byte2 | 0b10000000;
        
        	char byte3 = (char)((num & 0b111111) | 0b10000000);
        
        	dest[0] = byte1;
        	dest[1] = byte2;
        	dest[2] = byte3;
    	}
    	else if (num <= 0x10FFFF) {
        	char byte1 = (char)((num & 0b111000000000000000000) >> 18);
        	byte1 = byte1 | 0b11110000;

        	char byte2 = (char)((num & 0b111111000000000000) >> 12);
        	byte2 = byte2 | 0b10000000;
        
        	char byte3 = (char)((num & 0b111111000000) >> 6);
        	byte3 = byte3 | 0b10000000;
        
        	char byte4 = (char)((num & 0b111111) | 0b10000000);
        
        	dest[0] = byte1;
        	dest[1] = byte2;
        	dest[2] = byte3;
        	dest[3] = byte4;
    	}
}


void print_codepoint_plus_one(char str[]) {
    	char extracted[5];
    	char output[5];

    	utf8_substring(str, 3, 4, extracted);

    	uint32_t cp = decode(extracted);

    	uint32_t next_cp = cp + 1;

    	encode_utf8(next_cp, output);

    	printf("Next character of Codepoint is at index 3: %s\n", output);
}




int main(int argc, char *argv[]) {
   // if (argc != 2) {
   //     fprintf(stderr, "Usage: utf8analyzer \"<UTF-8 encoded string>\"\n");
   //     return 1;
   // }
    
    char buffer[] = "My 🐩's name is Erdős.";
    // implement the UTF-8 analyzer here
    
    //Analyzer function 7
    printf("Substring of the first 6 code points: ");
    utf8_substring_6(buffer);

    //Analyzer function 8
    printf("Animal emojis: ");
    animal_emoji(buffer);

    //Analyzer function 9
    print_codepoint_plus_one(buffer);
}


int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: utf8analyzer \"<UTF-8 encoded string>\"\n");
        return 1;
    }

    char* test_string = argv[1];

    printf("Input: %s\n", test_string);


