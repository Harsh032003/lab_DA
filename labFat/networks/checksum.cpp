#include <iostream>
#include <bitset>
#include <string>
#include <vector>

using namespace std;

int binaryStringToDecimal(const string &str)
{
    return bitset<4>(str).to_ulong();
}

unsigned char calculateChecksum(const vector<int> &data)
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
    string binaryInput;
    cout << "Enter up to 64-bit binary data: \n";
    cin >> binaryInput;

    if (binaryInput.length() > 64)
    {
        cout << "Invalid input\n";
        return -1;
    }
    for (int i = 0; i < binaryInput.size(); i++)
    {
        if (binaryInput[i] != '0' && binaryInput[i] != '1')
        {
            cout << "Invalid input\n";
            return -1;
        }
    }

    while (binaryInput.length() % 4 != 0)
    {
        binaryInput = "0" + binaryInput;
    }

    vector<int> data;
    for (int i = 0; i < binaryInput.size(); i += 4)
    {
        string segment = binaryInput.substr(i, 4);
        data.push_back(binaryStringToDecimal(segment));
    }

    unsigned char checksum = calculateChecksum(data);

    cout << "Checksum (decimal) : " << static_cast<int>(checksum) << "\n";
    cout << "Checksum (binary) : " << bitset<4>(checksum) << "\n";
}

/*#include <iostream>
#include <bitset>
#include <string>
#include <vector>

using namespace std;

int binaryStringToDecimal(const string &binaryStr)
{
    return bitset<4>(binaryStr).to_ulong();
}

unsigned char calculateChecksum(const vector<int> &data)
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
    string binaryInput;

    cout << "Enter up to 64-bit binary data:\n";
    cin >> binaryInput;

    if (binaryInput.length() > 64 || binaryInput.find_first_not_of("01") != std::string::npos)
    {
        cerr << "Invalid input. Please enter up to 64-bit binary data." << endl;
        return 1;
    }

    while (binaryInput.length() % 4 != 0)
    {
        binaryInput = "0" + binaryInput;
    }

    vector<int> data;
    for (size_t i = 0; i < binaryInput.length(); i += 4)
    {
        string segment = binaryInput.substr(i, 4);
        data.push_back(binaryStringToDecimal(segment));
    }

    unsigned char checksum = calculateChecksum(data);

    cout << "Checksum (decimal): " << static_cast<int>(checksum) << std::endl;

    cout << "Checksum (binary): " << bitset<4>(checksum) << std::endl;

    return 0;
}

*/
