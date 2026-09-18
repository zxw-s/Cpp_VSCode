#include <iostream>
#include <vector>
using namespace std;
int main()
{
    cout << "VSCode C++测试：你好！" << endl;
    vector<int> arr = {10, 20, 30, 40};
    for (auto num : arr)
    {
        cout << num << " ";
    }
    cout << endl;
    return 0;
}