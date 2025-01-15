#include <iostream>
#include <vector>
#include <sstream>
#include <bitset>

using namespace std;

vector<string> split(const string &s, char delimiter)
{
    vector<string> tokens;
    string token;
    istringstream tokenStream(s);
    while (getline(tokenStream, token, delimiter))
    {
        tokens.push_back(token);
    }
    return tokens;
}

bool isValidNumber(const string &s)
{
    if (s.empty() || (s[0] == '0' && s.length() > 1))
        return false;
    for (char c : s)
    {
        if (!isdigit(c))
            return false;
    }
    return true;
}

bool isValidIPv4(const vector<string> &parts)
{
    if (parts.size() != 4)
        return false;
    for (const string &part : parts)
    {
        if (!isValidNumber(part))
            return false;
        int num = stoi(part);
        if (num < 0 || num > 255)
            return false;
    }
    return true;
}

char findClass(int firstOctet)
{
    if (firstOctet >= 1 && firstOctet <= 126)
        return 'A';
    else if (firstOctet >= 128 && firstOctet <= 191)
        return 'B';
    else if (firstOctet >= 192 && firstOctet <= 223)
        return 'C';
    else if (firstOctet >= 224 && firstOctet <= 239)
        return 'D';
    else
        return 'E';
}

string convertToBinary(const vector<string> &parts)
{
    string binaryIP = "";
    for (const string &part : parts)
    {
        bitset<8> binary(stoi(part));
        binaryIP += binary.to_string() + ".";
    }
    binaryIP.pop_back();
    return binaryIP;
}

int main()
{
    string input;
    cout << "Enter IPv4 address (decimal format): ";
    cin >> input;

    vector<string> parts = split(input, '.');

    if (!isValidIPv4(parts))
    {
        cout << "Invalid IPv4 address!" << endl;
        return 1;
    }

    int firstOctet = stoi(parts[0]);
    char ipClass = findClass(firstOctet);
    cout << "IP address is valid and its IP Class: " << ipClass << endl;

    string binaryIP = convertToBinary(parts);
    cout << "Binary format: " << binaryIP << endl;

    return 0;
}
