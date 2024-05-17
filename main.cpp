#include <iostream>
#include <iomanip>
#include <string.h>
#include <cstdint>

#include "sha256.h"
#include "miner.h"
#include "util.h"

int main()
{
    // 10th Block info
    char version[9]; // 8 characters for hex + 1 for null-terminator
    char prevhash[] = "000000008d9dc510f23c2657fc4f67bea30078cc05a90eb89e84cc475c080805";
    char merkle_root[] = "d3ad39fa52a89997ac7381c95eeffeaf40b66af7a57e9eba144be0a175a12b11";
    char time[9]; // 8 characters for hex + 1 for null-terminator
    char nbits[9]; // 8 characters for hex + 1 for null-terminator

    uint32_t decimal_version = 1;
    uint32_t decimal_time = 1231473952;
    uint32_t decimal_nbits = 486604799;

    decimal_to_hex(decimal_version, version, sizeof(version));
    decimal_to_hex(decimal_time, time, sizeof(time));
    decimal_to_hex(decimal_nbits, nbits, sizeof(nbits));

    convert_to_little_endian(version);
    convert_to_little_endian(prevhash);
    convert_to_little_endian(merkle_root);
    convert_to_little_endian(time);
    convert_to_little_endian(nbits);

    uint32_t result[8];
    uint32_t start_nonce = 1709517110;
    uint32_t end_nonce = 1709518210; // Example end nonce

    uint32_t nonce = mineblock(start_nonce, end_nonce, version, prevhash, merkle_root, time, nbits);

    if (nonce == static_cast<uint32_t>(-1))
    {
        std::cout << "No valid nonce found within the given range." << std::endl;
    }
    else
    {
        std::cout << "Block solved! Nonce: " << nonce << std::endl;
        std::cout << "Block hash:" << std::endl;

        hashblock(nonce, version, prevhash, merkle_root, time, nbits, result);

        // Reverse the result for correct endianness before printing
        for(int i = 0; i < 8; i++) {
            result[i] = Reverse32(result[i]);
        }

        print_bytes_reversed(reinterpret_cast<unsigned char *>(result), 32);
    }

    return 0;
}
