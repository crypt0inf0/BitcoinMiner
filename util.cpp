#include <cstdint>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string.h>

void decimal_to_hex(uint32_t decimal, char* hex_str, size_t hex_str_size)
{
    if (hex_str_size < 9) {
        std::cerr << "Hex string buffer is too small." << std::endl;
        return;
    }

    std::stringstream ss;
    ss << std::uppercase << std::setfill('0') << std::setw(8) << std::hex << decimal;

    std::string hex = ss.str();
    strncpy(hex_str, hex.c_str(), hex_str_size - 1);
    hex_str[hex_str_size - 1] = '\0'; // Ensure null-termination
}

void convert_to_little_endian(char* hex_str)
{
    size_t len = strlen(hex_str);
    if (len % 2 != 0) {
        std::cerr << "Hex string length should be even." << std::endl;
        return;
    }

    for (size_t i = 0; i < len / 2; i += 2) {
        std::swap(hex_str[i], hex_str[len - 2 - i]);
        std::swap(hex_str[i + 1], hex_str[len - 1 - i]);
    }
}

void print_bytes(const unsigned char *data, size_t dataLen, bool format = true) {
    for(size_t i = 0; i < dataLen; ++i) {
        std::cout << std::hex << std::setw(2) << (int)data[i];
        if (format) {
            std::cout << (((i + 1) % 16 == 0) ? "\n" : " ");
        }
    }
    std::cout << std::endl;
}

void print_bytes_reversed(const unsigned char *data, size_t dataLen, bool format = true) {
    for(size_t i = dataLen; i > 0; i--) {
        std::cout << std::hex << std::setw(2) << (int)data[i - 1];
        if (format) {
            std::cout << (((i - 1) % 16 == 0) ? "\n" : " ");
        }
    }
    std::cout << std::endl;
}

uint32_t Reverse32(uint32_t value)
{
    return (((value & 0x000000FF) << 24) |
            ((value & 0x0000FF00) <<  8) |
            ((value & 0x00FF0000) >>  8) |
            ((value & 0xFF000000) >> 24));
}

unsigned char* hexstr_to_char(const char* hexstr)
{
    size_t len = strlen(hexstr);
    size_t final_len = len / 2;
    unsigned char* chars = (unsigned char*)malloc((final_len + 1));
    for(size_t i = 0, j = 0; j < final_len; i += 2, j++)
        chars[j] = (hexstr[i] % 32 + 9) % 25 * 16 + (hexstr[i+1] % 32 + 9) % 25;
    chars[final_len] = '\0';
    return chars;
}

void hexstr_to_intarray(const char* hexstr, uint32_t* outputloc)
{
    size_t len = strlen(hexstr);
    size_t intlen = (len + 7) / 8; // +7 ensures that we do a ceiling divide
    unsigned char* bytes = hexstr_to_char(hexstr);

    for(size_t i = 0; i < intlen; i++)
    {
        /* uint32_t a = (uint32_t)bytes[i * 4 + 3] << 24; */
        *(outputloc + i) = ((uint32_t)bytes[i * 4])
            + ((uint32_t)bytes[i * 4 + 1] << 8)
            + ((uint32_t)bytes[i * 4 + 2] << 16)
            + ((uint32_t)bytes[i * 4 + 3] << 24);
    }
    free(bytes);
}
