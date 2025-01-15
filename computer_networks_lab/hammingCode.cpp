#include <iostream>
#include <vector>
#include <string>
#include <cmath>

std::string calculateParityBits(const std::string &data)
{
    int n = data.size();
    int r = 0;

    // Determine the number of parity bits required
    while ((1 << r) < n + r + 1)
    {
        r++;
    }

    std::string hammingCode(n + r, '0');

    // Place the original data in the appropriate positions
    int j = 0;
    for (int i = 1; i <= n + r; ++i)
    {
        if ((i & (i - 1)) != 0)
        {
            hammingCode[i - 1] = data[j];
            j++;
        }
    }

    // Calculate parity bits
    for (int i = 0; i < r; ++i)
    {
        int pos = 1 << i;
        int parity = 0;
        for (int j = 1; j <= n + r; ++j)
        {
            if (j & pos && j != pos)
            {
                parity ^= (hammingCode[j - 1] - '0');
            }
        }
        hammingCode[pos - 1] = parity + '0';
    }

    return hammingCode;
}

std::string detectAndCorrectError(std::string hammingCode)
{
    int n = hammingCode.size();
    int r = 0;

    // Determine the number of parity bits
    while ((1 << r) < n + 1)
    {
        r++;
    }

    // Calculate the error position (if any)
    int errorPos = 0;
    for (int i = 0; i < r; ++i)
    {
        int pos = 1 << i;
        int parity = 0;
        for (int j = 1; j <= n; ++j)
        {
            if (j & pos)
            {
                parity ^= (hammingCode[j - 1] - '0');
            }
        }
        if (parity != 0)
        {
            errorPos += pos;
        }
    }

    // Correct the error if there's any
    if (errorPos != 0)
    {
        std::cout << "Error detected at position " << errorPos << std::endl;
        hammingCode[errorPos - 1] = (hammingCode[errorPos - 1] == '0') ? '1' : '0';
    }
    else
    {
        std::cout << "No error detected." << std::endl;
    }

    return hammingCode;
}

std::string sender(const std::string &data)
{
    std::string hammingCode = calculateParityBits(data);
    std::cout << "Hamming code to be sent: " << hammingCode << std::endl;
    return hammingCode;
}

std::string receiver(const std::string &hammingCode)
{
    std::string correctedCode = detectAndCorrectError(hammingCode);
    std::cout << "Received Hamming code: " << hammingCode << std::endl;
    std::cout << "Corrected Hamming code: " << correctedCode << std::endl;
    return correctedCode;
}

int main()
{
    std::string data;
    std::cout << "Enter original data (binary string): ";
    std::cin >> data;

    std::string hammingCode = sender(data);

    char choice;
    std::cout << "Do you want to simulate an error during transmission? (y/n): ";
    std::cin >> choice;

    std::string hammingCodeWithError = hammingCode;
    if (choice == 'y' || choice == 'Y')
    {
        int bitToFlip = 5; // Example: flipping the 6th bit
        if (bitToFlip < hammingCodeWithError.size())
        {
            hammingCodeWithError[bitToFlip] = (hammingCodeWithError[bitToFlip] == '0') ? '1' : '0';
        }
        std::cout << "Hamming code with error: " << hammingCodeWithError << std::endl;
    }

    receiver(hammingCodeWithError);

    return 0;
}
