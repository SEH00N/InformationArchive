#include <iostream>

int a[100];

int Split(int* arr, int start, int end)
{
	int pivot = start; //�Ǻ��� ������ �Ǻ����� ���� ����, �������� ū ������ ������ ����
	int left = start + 1;
	int right = end;
	int temp;

	while (left <= right) //������ ������ (�����ȴ� => �Ǻ��� ã������)
	{
		while (arr[left] <= arr[pivot] && left < end) // ���� �Ǻ��� left�� �� (�迭�� ������ �Ѿ�� �ʵ��� left < end ����)
			left++;
		while (arr[right] >= arr[pivot] && right > start) // ���� ����
			right--;

		if (left <= right) //�Ǻ��� ã������ �ʾ�����
		{
			//left�� right�� ��ȯ �� �Ǻ� ��� ã��
			temp = arr[left];
			arr[left] = arr[right];
			arr[right] = temp;
		}
	}

	//�Ǻ��� ã���� ��
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