#include <iostream>
#include <bitset>
#include <string>
#include <vector>

int binaryStringToDecimal(const std::string &binaryStr)
{
    return std::bitset<4>(binaryStr).to_ulong();
}

unsigned char calculateChecksum(const std::vector<int> &data)
{
    unsigned int sum = 0;

    for (int value : data)
    {
        sum += value;
    }

    while (sum >> 4)
    {
        sum = (sum & 0xF) + (sum >> 4);
    }

    return static_cast<unsigned char>(~sum & 0xF);
}

int main()
{
    std::string binaryInput;

    std::cout << "Enter up to 64-bit binary data:\n";
    std::cin >> binaryInput;

    if (binaryInput.length() > 64 || binaryInput.find_first_not_of("01") != std::string::npos)
    {
        std::cerr << "Invalid input. Please enter up to 64-bit binary data." << std::endl;
        return 1;
    }

    while (binaryInput.length() % 4 != 0)
    {
        binaryInput = "0" + binaryInput;
    }

    std::vector<int> data;
    for (size_t i = 0; i < binaryInput.length(); i += 4)
    {
        std::string segment = binaryInput.substr(i, 4);
        data.push_back(binaryStringToDecimal(segment));
    }

    unsigned char checksum = calculateChecksum(data);

    std::cout << "Checksum (decimal): " << static_cast<int>(checksum) << std::endl;
    std::cout << "Checksum (binary): " << std::bitset<4>(checksum) << std::endl;

    return 0;
}
