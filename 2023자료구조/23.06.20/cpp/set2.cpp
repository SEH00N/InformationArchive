#include <string>
#include <set>

using namespace std;

string solution(string my_string) {
    set<char> set;
    string answer = "";

    for (int i = 0; i < my_string.size(); ++i)
    {
        if (set.find(my_string[i]) == set.end())
        {
            set.insert(my_string[i]);
            answer += my_string[i];
        }
    }

    return answer;
}