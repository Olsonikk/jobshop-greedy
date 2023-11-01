// Your First C++ Program

#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm> 


using namespace std;

bool compareTuples(const tuple<int, int>& tuple1, const tuple<int, int>& tuple2) {
    // Porównujemy tupla na podstawie pierwszego elementu
    return get<0>(tuple1) < get<0>(tuple2);
}

int main() {
    int jobs = 3;
    int machines = 3;
    // int** processed = new int*[machines];

    vector<vector<tuple<int,int>>> ricardo;
    vector<tuple<int,int>> job0  = {make_tuple(2, 0), make_tuple(2, 1), make_tuple(2, 2)};
    vector<tuple<int,int>> job1  = {make_tuple(2, 1), make_tuple(4, 0), make_tuple(1, 2)};
    vector<tuple<int,int>> job2  = {make_tuple(4, 2), make_tuple(2, 1), make_tuple(1, 0)};
   
    ricardo.push_back(job0);
    ricardo.push_back(job1);
    ricardo.push_back(job2);

    // for(int i = 0; i < machines; i++) {
    //     processed[i] = new int[jobs];
    //     for (int j = 0; j < jobs; j++) {
    //         processed[i][j] = 0;
    //     }
    // }

    // for (int i = 0; i < machines; i++) {
    //     for (int j = 0; j < jobs; j++) {
    //         cout << processed[i][j] << " ";
    //     }
    //     cout << endl;
    // }


    // int machine_n[3][3] = {
    //     {0, 1, 2},
    //     {1, 0, 2},
    //     {2, 1, 0}
    // };

    // int task_length[3][3] = {
    //     {2, 2, 2},
    //     {2, 4, 1},
    //     {4, 2, 1}
    // };

     for (const auto& innerVector : ricardo) {
        for (const auto& tuple : innerVector) {
            int firstElement, secondElement;
            tie(firstElement, secondElement) = tuple;
            cout << "(" << firstElement << ", " << secondElement << ") ";
        }
        cout << endl;
    }


    for (auto& innerVector : ricardo) {
            sort(innerVector.begin(), innerVector.end(), compareTuples);
        }

    cout << endl;
    for (const auto& innerVector : ricardo) {
        for (const auto& tuple : innerVector) {
            int firstElement, secondElement;
            tie(firstElement, secondElement) = tuple;
            cout << "(" << firstElement << ", " << secondElement << ") ";
        }
        cout << endl;
    }
    return 0;
}


//TODO zmienic kolejnosc w tuplach