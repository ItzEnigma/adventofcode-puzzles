#include <algorithm>
#include <array>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

bool isRealRoom(const string& room)
{
    /** 1. Build a map of character frequencies
     * 2. Sort the characters by frequency (descending) and then alphabetically (ascending)
     * 3. Take the first five characters from the sorted list and compare them to the checksum provided in the input
     */
    unordered_map<char, int> frequencyMap;
    for (char c : room)
    {
        if (c >= 'a' && c <= 'z')
        {
            frequencyMap[c]++;
        }
    }

    vector<pair<char, int>> frequencyVector(frequencyMap.begin(), frequencyMap.end());
    sort(frequencyVector.begin(),
         frequencyVector.end(),
         [](const pair<char, int>& a, const pair<char, int>& b)
         {
             if (a.second == b.second)
                 return a.first < b.first; // Sort alphabetically if frequencies are equal
             return a.second > b.second;   // Sort by frequency (descending)
         });

    string calculatedChecksum;
    for (size_t i = 0; i < 5 && i < frequencyVector.size(); ++i)
    {
        calculatedChecksum += frequencyVector[i].first;
    }

    size_t checksumStart = room.find('[');
    size_t checksumEnd = room.find(']');

    if (checksumStart != string::npos && checksumEnd != string::npos && checksumEnd > checksumStart)
    {
        string providedChecksum = room.substr(checksumStart + 1, checksumEnd - checksumStart - 1);
        return calculatedChecksum == providedChecksum;
    }
    return false;
}

string decryptRoomName(const string& room)
{
    size_t lastDash = room.rfind('-');
    size_t checksumStart = room.find('[');
    if (lastDash != string::npos && checksumStart != string::npos && checksumStart > lastDash)
    {
        int sectorId = stoi(room.substr(lastDash + 1, checksumStart - lastDash - 1));
        string encryptedName = room.substr(0, lastDash);
        string decryptedName;

        for (char c : encryptedName)
        {
            if (c >= 'a' && c <= 'z')
            {
                decryptedName += (c - 'a' + sectorId) % 26 + 'a';
            }
            else if (c == '-')
            {
                decryptedName += ' ';
            }
        }
        return decryptedName;
    }
    return "";
}

/** Helper to parse directions */
vector<string> getInput()
{
    vector<string> lines;
    string line;
    while (getline(cin, line))
    {
        if (line.empty())
            break; // skip empty lines if needed
        lines.push_back(line);
    }
    return lines;
}

int main()
{
    vector<string> input = getInput();

    for (const string& room : input)
    {
        if (isRealRoom(room))
        {
            string decryptedName = decryptRoomName(room);
            if (decryptedName == "northpole object storage")
            {
                size_t lastDash = room.rfind('-');
                size_t checksumStart = room.find('[');
                if (lastDash != string::npos && checksumStart != string::npos && checksumStart > lastDash)
                {
                    int sectorId = stoi(room.substr(lastDash + 1, checksumStart - lastDash - 1));
                    cout << sectorId
                         << endl; // Output the sector ID of the room where "northpole object storage" is located
                    break;
                }
            }
        }
    }

    return 0;
}
