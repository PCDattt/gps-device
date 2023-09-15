#include "../include/Header.h"

uint16_t CalculateChecksum(const std::vector<uint8_t>& buffer) {
    // Initialize MD5 context
    MD5_CTX md5Context;
    MD5_Init(&md5Context);

    // Update the context with your data
    MD5_Update(&md5Context, buffer.data(), buffer.size());

    // Finalize the MD5 checksum
    uint8_t md5Checksum[MD5_DIGEST_LENGTH];
    MD5_Final(md5Checksum, &md5Context);

    // Convert the 2 last bytes MD5 checksum to a uint16_t
    uint16_t checksumtemp;
    checksumtemp = static_cast<uint16_t>(md5Checksum[MD5_DIGEST_LENGTH - 2]) << 8;
    checksumtemp |= static_cast<uint16_t>(md5Checksum[MD5_DIGEST_LENGTH - 1]);

    return checksumtemp;
}

bool ValidateChecksum(std::vector<uint8_t> buffer, uint16_t& checksum) {
    buffer.erase(buffer.end() - 2, buffer.end());
    // Calculate the checksum of the buffer
    uint16_t calculatedChecksum = CalculateChecksum(buffer);

    // Compare the checksums
    if (calculatedChecksum != checksum) return false;

    return true;
}