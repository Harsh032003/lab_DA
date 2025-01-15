#include <bits/stdc++.h>
using namespace std;

bool solve()
{
    string input1;
    string input2;

    cin >> input1;
    cin >> input2;
    map<char, int> mp1;
    map<char, int> mp2;

    for (int i = 0; i < input1.size(); i++)
    {
        mp1[input1[i]]++;
        mp2[input2[i]]++;
    }

    for (auto i : mp1)
    {
        if (mp2[i.first] != i.second)
        {
            return false;
        }
    }

    return true;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;

    while (t--)
        cout << solve();

    return 0;
}