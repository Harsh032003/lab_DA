#include <iostream>
#include <vector>
#include <iomanip>
#include <sstream>

unsigned short calculateChecksum(const std::vector<unsigned char> &data)
{
    unsigned long sum = 0;
    size_t length = data.size();

    std::vector<unsigned char> paddedData = data;
    if (length % 2 != 0)
    {
        paddedData.push_back(0x00);
    }

    for (size_t i = 0; i < paddedData.size(); i += 2)
    {
        unsigned short word = (paddedData[i] << 8) + paddedData[i + 1];
        sum += word;

        sum = (sum & 0xFFFF) + (sum >> 16);
    }

    sum = (sum & 0xFFFF) + (sum >> 16);

    return ~static_cast<unsigned short>(sum);
}

std::string formatHexOutput(const std::vector<unsigned char> &data)
{
    std::ostringstream oss;
    for (size_t i = 0; i < data.size(); ++i)
    {
        if (i > 0 && i % 2 == 0)
        {
            oss << ' ';
        }
        oss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(data[i]);
    }
    return oss.str();
}

std::vector<unsigned char> sender(const std::string &data)
{
    std::vector<unsigned char> dataBytes(data.begin(), data.end());
    unsigned short checksum = calculateChecksum(dataBytes);

    std::cout << "Generated Checksum (in hex): " << std::hex << std::setw(4) << std::setfill('0') << checksum << std::endl;

    dataBytes.push_back(static_cast<unsigned char>(checksum >> 8));   // high byte
    dataBytes.push_back(static_cast<unsigned char>(checksum & 0xFF)); // low byte

    std::string formattedHexOutput = formatHexOutput(dataBytes);
    std::cout << "Data to be sent (in hex, grouped by 4): " << formattedHexOutput << std::endl;

    return dataBytes;
}

bool receiver(const std::vector<unsigned char> &dataWithChecksum)
{

    std::vector<unsigned char> data(dataWithChecksum.begin(), dataWithChecksum.end() - 2);
    unsigned short receivedChecksum = (dataWithChecksum[dataWithChecksum.size() - 2] << 8) |
                                      dataWithChecksum[dataWithChecksum.size() - 1];

    unsigned short calculatedChecksum = calculateChecksum(data);

    return calculatedChecksum == receivedChecksum;
}

int main()
{
    std::string data;
    std::cout << "Enter a string to send: ";
    std::getline(std::cin, data);

    std::vector<unsigned char> dataWithChecksum = sender(data);

    if (receiver(dataWithChecksum))
    {
        std::cout << "Data is correct, no errors." << std::endl;
    }
    else
    {
        std::cout << "Data is corrupted, checksum does not match." << std::endl;
    }

    return 0;
}
