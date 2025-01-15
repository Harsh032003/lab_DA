#include <iostream>
using namespace std;

string xorfun(string encoded, string crc)
{
    int crclen = crc.length();
    for (int i = 0; i <= (encoded.length() - crclen);)
    {
        for (int j = 0; j < crclen; j++)
        {
            encoded[i + j] = encoded[i + j] == crc[j] ? '0' : '1';
        }
        for (; i < encoded.length() && encoded[i] != '1'; i++)
            ;
    }
    return encoded;
}
int main()
{
    string data, crc, encoded = "";
    cout << endl
         << "For sender side :" << endl;
    cout << "Enter Data bits: " << endl;

    cin >> data;
    cout << "Enter Generator: " << endl;
    cin >> crc;

    encoded += data;
    int datalen = data.length();
    int crclen = crc.length();

    for (int i = 1; i <= (crclen - 1); i++)
        encoded += '0';
    encoded = xorfun(encoded, crc);
    cout << "Checksum generated is: ";

    cout << encoded.substr(encoded.length() - crclen + 1) << endl
         << endl;

    cout << "Message to be Transmitted over network: ";
    cout << data + encoded.substr(encoded.length() - crclen + 1);

    cout << endl
         << "For receiver side :" << endl;
    cout << endl

         << "Enter the received message: " << endl;
    cin >> encoded;
    encoded = xorfun(encoded, crc);
    for (char i : encoded.substr(encoded.length() - crclen + 1))
    {
        if (i != '0')
        {
            cout << "Error in communication" << endl;
            return 0;
        }
    }
    cout << "No Error!" << endl;
    return 0;
}
