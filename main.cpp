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
    char version[] = "01000000";
    char prevhash[] = "0508085C47CC849EB80EA905CC7800A3BE674FFC57263CF210C59D8D00000000";
    char merkle_root[] = "112BA175A1E04B14BA9E7EA5F76AB640AFFEEF5EC98173AC9799A852FA39ADD3";
    char time[9]; // 8 characters for hex + 1 for null-terminator
    char nbits[] = "FFFF001D";

    uint32_t decimal_time = 1231473952;
    decimal_to_hex(decimal_time, time, sizeof(time));

    std::cout << "Time in hex (big-endian): " << time << std::endl;

    convert_to_little_endian(time);

    std::cout << "Time in hex (little-endian): " << time << std::endl;

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
