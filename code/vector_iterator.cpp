#include <iostream>
#include <vector>

using namespace std;

void is_same(vector<int>::iterator it, vector<int>::iterator it_1) {

}

int main() {
    vector<int> vec;
    for(int i = 1; i <= 7; ++i)
        vec.push_back(i);
    cout << "The capacity = " << vec.capacity() << endl << endl;

    // size <= capacity，不需要重新分配
    auto itbegin = vec.begin();
    auto itend = vec.end();
    vec.push_back(8);
    auto itbegin_1 = vec.begin();
    auto itend_1 = vec.end();
    if(itbegin == itbegin_1)
        cout << "Begin same." << endl;
    else
        cout << "Begin different." << endl;
    if(itend == itend_1)
        cout << "End same." << endl;
    else
        cout << "End different." << endl;
    cout << endl;

    // size > capacity,重新分配内存
    vec.push_back(9);
    auto itbegin_2 = vec.begin();
    auto itend_2 = vec.end();
    if(itbegin_2 == itbegin_1)
        cout << "Begin same." << endl;
    else
        cout << "Begin different." << endl;
    if(itend_2 == itend_1)
        cout << "End same" <<endl;
    else
        cout << "End different." << endl;
    cout << endl;

    cout << "The size = " <<  vec.size() << endl;
    cout << "The capacity = " << vec.capacity() << endl << endl;

    // 删除元素
    auto itend_3 = vec.end();
    auto itbegin_3 = vec.begin();
    for(auto itmove = itbegin_3; itmove != itend_3; ++itmove) {
        cout << *itmove << " ";
        if(*itmove == 3) {
            vec.erase(itmove);
            cout << endl << "Now the 3rd number = " << *itmove;
            auto itbegin_4 = vec.begin();
            auto itend_4 = vec.end();
            cout << endl;
            if(itbegin_3 == itbegin_4)
                cout << "Begin same." << endl;
            else
                cout << "Begin different." << endl;
            if(itend_3 == itend_4)
                cout << "End same" <<endl;
            else
                cout << "End different." << endl;
        }
    }
    cout << endl << endl << "The size = " << vec.size() << endl << endl;

    // 正确删除方式
    for(auto itmove = vec.begin(); itmove != vec.end();) {
        cout << *itmove << " ";
        if(*itmove == 4) {
            itmove = vec.erase(itmove);
            cout << endl << "The next effect = " << *itmove << endl;
        }
        else
            ++itmove;
    }
    return 0;
}