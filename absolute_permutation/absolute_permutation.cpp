#include <bits/stdc++.h>
#include <math.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Permutate sequence of first `n` natural numbers such that |permutation[i] - i| == k
 */

vector<int> absolutePermutation(int n, int k)
{
    std::vector<int> a(n);
    std::iota(a.begin(), a.end(), 1);
    if (k == 0)
    {
        return a;
    }
    else if (remainder(n, 2 * k) == 0)
    {
        auto pos = a.begin();
        while (pos != a.end())
        {
            std::rotate(pos, pos + k, pos + 2 * k);
            pos += 2 * k;
        }
        return a;
    }
    else
    {
        return {-1};
    }
}

int main(int argv, char *argc[])
{
    string bin_path{argc[0]};
    string bin_dir = bin_path.substr(0, bin_path.find_last_of('/'));
    string data_path = bin_dir + "/data";
    ifstream fin(data_path);
    ofstream fout("result");

    string t_temp;
    getline(fin, t_temp);

    int t = stoi(ltrim(rtrim(t_temp)));

    for (int t_itr = 0; t_itr < t; t_itr++)
    {
        string first_multiple_input_temp;
        getline(fin, first_multiple_input_temp);

        vector<string> first_multiple_input = split(ltrim(first_multiple_input_temp));

        int n = stoi(first_multiple_input[0]);

        int k = stoi(first_multiple_input[1]);

        vector<int> result = absolutePermutation(n, k);

        for (size_t i = 0; i < result.size(); i++)
        {
            fout << result[i];

            if (i != result.size() - 1)
            {
                fout << " ";
            }
        }

        fout << "\n";
    }

    fout.close();

    return 0;
}

string ltrim(const string &str)
{
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace))));

    return s;
}

string rtrim(const string &str)
{
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end());

    return s;
}

vector<string> split(const string &str)
{
    vector<string> tokens;

    string::size_type start = 0;
    string::size_type end = 0;

    while ((end = str.find(" ", start)) != string::npos)
    {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}
