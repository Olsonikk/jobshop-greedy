// Your First C++ Program

#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm> 
#include <fstream>
#include <string>


using namespace std;

bool compareTuples(const tuple<int, int>& tuple1, const tuple<int, int>& tuple2) {
    // Porównujemy tupla na podstawie pierwszego elementu
    return get<1>(tuple1) < get<1>(tuple2);
}

void print_element(int job_n, int task_n, vector<vector<tuple<int,int>>> local_vector){
    int machine_n, duration;
    tie(machine_n, duration) = local_vector[job_n][task_n];
    cout << "Job: " << job_n << " Task: " << task_n << " Machine: " << machine_n << " Duration: " << duration <<endl;
}

vector<vector<tuple<int,int>>> read_orlib(string filename, int* jobs, int* machines){
    ifstream input_file(filename);
    
    tuple<int, int> task;

    if(input_file.fail()){
        perror("Error ocurred while opening the file!");
        exit(1);
    }
    else{
        int a,b;
        
        input_file >> *jobs;
        input_file >> *machines;
        vector<vector<tuple<int,int>>> main_vector(*machines);
        for(int x=0; x < *jobs; x++){
            for(int i=0; i < *machines; i++){
            input_file >> a >> b;
            task = make_tuple(a,b);
            main_vector[x].push_back(task);
        } 
        }
        return main_vector;
    }
    
}

int main(int argc, char** argv) {

    int jobs, machines;
    vector<vector<tuple<int,int>>> ricardo;

    ricardo = read_orlib(argv[1], &jobs, &machines);

    cout << endl;

    cout << "JOBS: " << jobs << endl << "MACHINES: " << machines << endl;
        

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

    //Schedulling


    print_element(2, 2, ricardo);

   
    
    return 0;
}


