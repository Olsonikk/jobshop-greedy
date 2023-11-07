// Your First C++ Program

#include <iostream>
#include <vector>
#include <array>
#include <algorithm> 
#include <fstream>
#include <string>


using namespace std;

bool compareTuples(const array<int, 2>& tuple1, const array<int, 2>& tuple2) {
    // Porównujemy tupla na podstawie pierwszego elementu
    return get<1>(tuple1) < get<1>(tuple2);
}

/*void print_element(int job_n, int task_n, vector<vector<array<int,2>>> local_vector){
    int machine_n, duration;
    tie(machine_n, duration) = local_vector[job_n][task_n];
    cout << "Job: " << job_n << " Task: " << task_n << " Machine: " << machine_n << " Duration: " << duration <<endl;
}*/

vector<vector<array<int,2>>> read_orlib(string filename, int* jobs, int* machines){
    ifstream input_file(filename);
    
    array<int,2> task;

    if(input_file.fail()){
        perror("Error ocurred while opening the file!");
        exit(1);
    }
    else{
        int a,b;
        
        input_file >> *jobs;
        input_file >> *machines;
        vector<vector<array<int,2>>> main_vector(*machines);
        for(int x=0; x < *jobs; x++){
            for(int i=0; i < *machines; i++){
            input_file >> a >> b;
            task = {a,b};
            main_vector[x].push_back(task);
        } 
        }
        return main_vector;
    }
    
}

bool TimeLeft(int elem, int currTime, int * job_total){
    if(job_total[elem] == currTime) return true;
    return false;
}

void putTasks(int jobs, int machines, vector<vector<array<int,2>>> &arr, int* jobs_free, int currTime, int* job_total){
    int duration,machine_n;
    for(int i=0;i<jobs;i++){
        for(int j=0;j<machines;j++){
            duration = arr[i][j][1];
            machine_n = arr[i][j][0];
            if(jobs_free[i] == 0 && TimeLeft(duration,currTime,job_total)){
                cout<<machine_n<<" "<<duration<<endl;
                jobs_free[i]=duration;
                job_total[machine_n] += duration;
                arr[i][j][0]=-1;
                break;
            }
        }
    }
}

int main(int argc, char** argv) {

    int jobs, machines;
    vector<vector<array<int,2>>> ricardo;

    //ricardo = read_orlib(argv[1], &jobs, &machines);
    ricardo = read_orlib("instance1.txt", &jobs, &machines);

    int currTime = 0;
    int * jobs_free = new int[jobs];
    fill_n(jobs_free, jobs, 0);
    int * job_total = new int[jobs];
    fill_n(job_total, jobs, 0);
    int ** output = new int * [jobs];
    for (int i = 0; i<jobs; i++)
		output[i] = new int [machines];

    

    cout << endl;

    cout << "JOBS: " << jobs << endl << "MACHINES: " << machines << endl;
        

     for (const auto& innerVector : ricardo) {
        for (const auto& tuple : innerVector) {
            int firstElement, secondElement;
            cout << "(" << tuple[0] << ", " << tuple[1] << ") ";
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
            cout << "(" << tuple[0] << ", " << tuple[1] << ") ";
        }
        cout << endl;
    }

    //Schedulling


    //print_element(2, 2, ricardo);
    putTasks(jobs,machines,ricardo,jobs_free,currTime,job_total);
   
   for (const auto& innerVector : ricardo) {
        for (const auto& tuple : innerVector) {
            int firstElement, secondElement;
            cout << "(" << tuple[0] << ", " << tuple[1] << ") ";
        }
        cout << endl;
    }
    
    return 0;
}


