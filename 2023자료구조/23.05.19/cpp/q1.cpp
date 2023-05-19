#include <iostream>
#include <list>
using namespace std;

#pragma region "연결리스트로 스택 쿠현하기"
//struct NODE {
//    NODE* next;
//    int data;
//};
//
//void Push(int _data);
//int Pop();
//bool isEmpty();
//void printData();
//void Menu();
//NODE* s_top;
//
//int main() {
//    int data, nKey = 0;
//    while (true) {
//        Menu();
//        cin >> nKey;
//        cout << "\n";
//        switch (nKey) {
//        case 1:
//            cout << "Push : ";
//            cin >> data;
//            Push(data);
//            break;
//        case 2:
//            cout << "Pop : " << Pop() << endl;
//            break;
//        case 3:
//            printData();
//            break;
//        default:
//            cout << "입력 오류" << endl;
//            break;
//        }
//        cout << "\n";
//    }
//    return 0;
//}
//
//void Push(int _data) {
//    NODE* temp = new NODE;
//    temp->next = NULL;
//    temp->data = _data;
//    if (isEmpty()) {
//        s_top = temp;
//    }
//    else {
//        temp->next = s_top;
//        s_top = temp;
//    }
//}
//
//int Pop() {
//    if (isEmpty()) return -1;
//    NODE* delTemp = s_top;
//    int rData = delTemp->data;
//    
//    s_top = delTemp->next;
//    delete delTemp;
//
//    return rData;
//}
//
//void printData() {
//    if (isEmpty()) {
//        cout << "Stack is Empty" << endl;
//        return;
//    }
//    NODE* top = s_top;
//    for (; top != NULL; top = top->next) {
//        cout << "| " << top->data << " |" << endl;
//    }
//    cout << "-----" << endl;
//}
//
//bool isEmpty() { return s_top == NULL; }
//
//void Menu()
//{
//    cout << "1. Push" << endl;
//    cout << "2. Pop" << endl;
//    cout << "3. Show Stack" << endl;
//    cout << "INPUT : ";
//}
#pragma endregion

#pragma region "연결리스트로 큐 쿠현하기"
struct NODE
{
    NODE* next;
    int data;
};
void enQueue(int _data);
int deQueue();
void printData();
bool isEmpty();
void Menu();
NODE* q_front;
NODE* q_rear;
int q_count;
int main()
{
    int data, nKey = 0;
    while (true)
    {
        Menu();
        cin >> nKey;
        cout << "\n";
        switch (nKey)
        {
        case 1:
            cout << "Enqueue: ";
            cin >> data;
            enQueue(data);
            cout << "log >> s_count : " << q_count << endl;
            break;
        case 2:
            cout << "Dequeue: " << deQueue() << endl;
            break;
        case 3:
            printData();
            break;
        default:
            cout << "입력 오류" << endl;
            break;
        }
        cout << "\n";
    }
    return 0;
}
void enQueue(int _data)
{
    NODE* temp = new NODE;
    temp->next = NULL;
    temp->data = _data;
    if (isEmpty()) {
        q_front = temp;
        q_rear = temp;
    }
    else {
        q_rear->next = temp;
        q_rear = temp;
    }
    q_count++;
}
int deQueue()
{
    if (isEmpty()) {
        cout << "\nQueue is Empty\n\n";
        return -1;
    }
    NODE* delTemp = q_front;
    int rData = delTemp->data;

    q_front = q_front->next;
    delete delTemp;

    q_count--;
    return rData;
}

void printData()
{
    if (isEmpty())
    {
        cout << "\nQueue is Empty\n\n";
        return;
    }
    NODE* front = q_front;
    for (; front != NULL; front = front->next)
        cout << front->data << " ";
    cout << endl;
}
bool isEmpty() { return q_count == 0; }

void Menu()
{
    cout << "1. Enqueue" << endl;
    cout << "2. Dequeue" << endl;
    cout << "3. Show Queue" << endl;
    cout << "INPUT : ";
}
#pragma endregion 

#pragma region "stl list 사용법"
//int main()
//{
//	// list 선언 
//	list <int> l1;
//	list <int> l2(5, 3); // 5개의 원소를 3으로 초기화
//	list <int> l3{2,4}; // 2, 4로 초기화
//
//	// 값 추가
//	l3.push_front(1); // 리스트의 맨 앞에 값 추가
//	l3.push_back(5); // 리스트의 맨 끝에 값 추가
//	list<int>::iterator iter = l3.begin(); // 반복자가 첫번째 값을 가리킴
//	iter++; // 두번째 값 가리킴
//	iter++;// 세번째 값 가리킴
//	l3.insert(iter, 3); // 반복자가 가리키는 곳에 값 추가
//
//	for (auto n : l3)
//	{
//		cout << n;
//	}
//	cout << endl;
//
//	// 값 삭제 
//	l3.pop_front(); // 리스트 맨 앞 삭제 
//	l3.pop_back(); // 리스트 맨 뒤 삭제
//	cout << l3.size() << endl; // 리스트에 들어 있는 원소 개수 반환
//	cout << l3.empty() << endl; // 리스트가 비어있으면 1, 아니면 0 반환
//	l3.erase(iter); // 반복자가 가리키는 곳을 제거하고 그 다음 원소의 위치를 반환
//
//	for (auto n : l3)
//	{
//		cout << n;
//	}
//
//}
#pragma endregion