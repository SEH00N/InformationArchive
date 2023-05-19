#include <iostream>
#include <vector>

std::vector<int> solution(std::vector<int> arr)
{
    std::vector<int> answer;

    for (int i = 0; i < arr.size(); ++i)
        if (answer.empty() || answer[answer.size() - 1] != arr[i])
            answer.push_back(arr[i]);

    return answer;
}

std::vector<int> solution(std::vector<int> progresses, std::vector<int> speeds) 
{
    std::vector<int> answer;
    int error, last, count = 0;
    
    error = 100 - progresses[0];
    last = static_cast<int>(std::round(error / speeds[0]));

    for (int i = 1; i < progresses.size(); ++i)
    {
        error = 100 - progresses[i];
        error = static_cast<int>(std::round(error / speeds[i]));

        ++count;
        if (error > last)
        {
            answer.push_back(count);
            last = error;
            count = 0;
        }
    }

    if(error != last)
        answer.push_back(++count);

    return answer;
}

int main()
{
    std::vector<int> arr{ 4,4,4,3,3 };
    arr = solution(arr);

    for (int i = 0; i < arr.size(); ++i)
        std::cout << arr[i] << ' ';

	return 0;
}