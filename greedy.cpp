// Your First C++ Program

#include <iostream>
#include <vector>
#include <array>
#include <algorithm> 
#include <fstream>
#include <string>


using namespace std;

bool compareTasks(const array<int, 2>& task1, const array<int, 2>& task2) {
    // Porównujemy taska na podstawie pierwszego elementu
    return get<1>(task1) < get<1>(task2);
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

int currTimeJump(int currTime, int* job_total, int jobs, bool success){ //jesli success=true, zwroc najmniejsza, ww. drugi najmniejszy
    int smallest;
    int second_smallest;

    if(job_total[0] < job_total[1]){
        smallest = job_total[0];
        second_smallest = job_total[1];
    }
    else{
        smallest = job_total[1];
        second_smallest = job_total[0];
    }
    for(int i = 2; i<jobs; i++){
        if(job_total[i] < second_smallest){
            if(job_total[i] < smallest){
                smallest = job_total[i];
            }
            else{
                second_smallest = job_total[i];
            }
        }
    }
    if(success) return smallest;
    return second_smallest;
    
}

void putTasks(int jobs, int machines, vector<vector<array<int,2>>> &arr, int *jobs_free, int& currTime, int* job_total){
    int duration,machine_n;
    bool jobs_inserted;
    for(int i=0;i<jobs;i++){
        jobs_inserted = false;
        for(int j=0;j<machines;j++){
            duration = arr[i][j][1];
            machine_n = arr[i][j][0];
            if(jobs_free[i] == 0 && TimeLeft(machine_n,currTime,job_total) && machine_n >= 0){ //success!
                jobs_inserted = true;
                jobs_free[i]=duration;
                job_total[machine_n] += duration;
                arr[i][j][0]=-1;
                break;
            }
        }
    }

    currTime = currTimeJump(currTime, job_total, jobs, jobs_inserted);
}

void printArray(int* array, int jobs){
    for(int i = 0; i<jobs;i++){
        cout << array[i] << " ";
    }
    cout << endl;
}

void printVector(vector<vector<array<int,2>>> mainVector){
    for (const auto& innerVector : mainVector) {
        for (const auto& task : innerVector) {
            int firstElement, secondElement;
            cout << "(" << task[0] << ", " << task[1] << ") ";
        }
        cout << endl;
    }
    cout << endl;
}



void updateJF(int* jobs_free, int currTime, int jobs){
    for(int i=0; i< jobs; i++){
        if(jobs_free[i] - currTime > 0){
            jobs_free[i] -= currTime;
        }
        else jobs_free[i] = 0;
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

    cout << "JOBS: " << jobs << endl << "MACHINES: " << machines << endl;
        
    printVector(ricardo);

    for(auto& innerVector : ricardo) {
            sort(innerVector.begin(), innerVector.end(), compareTasks);
        }

    printVector(ricardo);

    //Schedulling

    putTasks(jobs,machines,ricardo,jobs_free,currTime,job_total);

    
    cout << "curtime" << currTime;
    cout << endl;

    updateJF(jobs_free, currTime, jobs);

    printVector(ricardo);
    
    printArray(jobs_free, jobs);
    printArray(job_total, jobs);


    cout << endl;
    cout << endl;
    cout << endl;

    putTasks(jobs,machines,ricardo,jobs_free,currTime,job_total);

    
    cout << "curtime" << currTime;
    cout << endl;

    updateJF(jobs_free, currTime, jobs);

    printVector(ricardo);
    
    printArray(jobs_free, jobs);
    printArray(job_total, jobs);

    return 0;
}


