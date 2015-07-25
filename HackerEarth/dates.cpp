#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

vector<string> splitString(string input, string delimiter)
{
 vector<string> output;
 size_t start = 0;
 size_t end = 0;

 while (start != string::npos && end != string::npos)
 {
    start = input.find_first_not_of(delimiter, end);

    if (start != string::npos)
    {
       end = input.find_first_of(delimiter, start);

       if (end != string::npos)
       {
          output.push_back(input.substr(start, end - start));
       }
       else
       {
          output.push_back(input.substr(start));
       }
    }
 }

 return output;

}

int main(int argc, char** argv) {
	int t;
	cin >> t;
	for (int i = 0; i < t; i++) {
		string str1;
		cin >> str1;
		vector<string> start = splitString(str1, ":");
		string str2;
		cin >> str2;
		vector<string> end = splitString(str2, ":");
		int count;
		//same year
		if (start[2] == end[2]) {
			int yr = stoi(start[2]) % 100;
			int day1 = stoi(start[0]);
			int day2 = stoi(end[0]);
			int month1 = stoi(start[1]);
			int month2 = stoi(end[1]);
			if (day1 <= yr - 2 && day2 >= yr - 2
					&& month1 <= yr - 1 && month2 >= yr - 1
					&& yr <= 13) {
				count++;
			}
		} else if (stoi(start[2]) > stoi(start[1])){
			//start year
			int yr1 = stoi(start[2]) % 100;
			int day = stoi(start[0]);
			int month = stoi(start[1]);
			if (day <= yr1 - 2 && month <= yr1 - 1 && yr1 <= 13) {
				count++;
			}
			//end year
			int yr2 = stoi(end[2]) % 100;
			day = stoi(end[0]);
			month = stoi(end[1]);
			if (day >= yr2 - 2 && month >= yr2 - 1 && yr2 <= 13) {
				count++;
			}
			yr1 = stoi(start[2]);
			yr2 = stoi(end[2]);
			if (yr2 - yr1 <= 100) {
				count += max(0, min(yr2 % 100 - 1, 13) - max(3, yr1 % 100 + 1));
			} else {
				count += max(0, min(yr2 % 100 - 1, 13) - 3);
				//count += (yr2 / 100 - yr1 / 100 - 1) * 11;
				count += max(0, 13 - max(3, yr1 % 100 + 1));
			}
		}
		cout << count << endl;
	}
	return 0;
}