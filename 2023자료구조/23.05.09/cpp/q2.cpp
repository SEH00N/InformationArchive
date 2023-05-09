#include <iostream>
#include <string>
#include <queue>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    queue<int> q1;
    int count;
    string command;
    cin >> count;

    for (int i = 0; i < count; ++i) {
        cin >> command;

        if (command == "push") {
            int num;
            cin >> num;
            q1.push(num);
        }
        else if (command == "pop") {
            if (q1.empty())
                cout << -1 << endl;
			else {
				cout << q1.front() << endl;
				q1.pop();
            }
        }
        else if (command == "front") {
            if (q1.empty())
                cout << -1 << endl;
            else
                cout << q1.front() << endl;
        }
        else if (command == "back") {
            if (q1.empty())
                cout << -1 << endl;
            else
                cout << q1.back() << endl;
        }
        else if (command == "size")
            cout << q1.size() << endl;
        else if (command == "empty")
            cout << q1.empty() << endl;
    }

    return 0;
}