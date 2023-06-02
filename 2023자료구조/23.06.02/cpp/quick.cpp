#include <iostream>

int a[100];

int Split(int* arr, int start, int end)
{
	int pivot = start; //피봇의 왼쪽은 피봇보다 작은 값들, 오른쪽은 큰 값들이 들어가도록 나눔
	int left = start + 1;
	int right = end;
	int temp;

	while (left <= right) //엇갈릴 떄까지 (엇갈렸다 => 피봇이 찾아졌다)
	{
		while (arr[left] <= arr[pivot] && left < end) // 현재 피봇과 left와 비교 (배열의 범위를 넘어가지 않도록 left < end 제한)
			left++;
		while (arr[right] >= arr[pivot] && right > start) // 이하 동문
			right--;

		if (left <= right) //피봇이 찾아지지 않았으면
		{
			//left랑 right랑 교환 후 피봇 계속 찾기
			temp = arr[left];
			arr[left] = arr[right];
			arr[right] = temp;
		}
	}

	//피봇이 찾아진 후
	temp = arr[start];
	arr[start] = arr[right];
	arr[right] = temp;

	return right;
}

void QuickSort(int* arr, int start, int end)
{
	if (start >= end)
		return;

	int pivot = Split(arr, start, end);

	QuickSort(arr, start, pivot - 1);
	QuickSort(arr, pivot + 1, end);
}

int main() {
	int n, i;
	std::cin >> n;
	for (i = 0; i < n; i++)
		std::cin >> a[i];
	
	QuickSort(a, 0, n-1);

	for (i = 0; i < n; i++)
		std::cout << a[i] << " ";

	return 0;
}