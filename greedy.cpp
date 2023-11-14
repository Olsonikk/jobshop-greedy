// Your First C++ Program

#include <iostream>
#include <vector>
#include <array>
#include <algorithm> 
#include <fstream>
#include <string>
#include <climits>
#include <stack>


using namespace std;

bool compareTasks(const vector<int>& task1, const vector<int>& task2) {
    // Porównujemy taska na podstawie pierwszego elementu
    return task1[1] > task2[1];
}

/*void print_element(int job_n, int task_n, vector<vector<array<int,2>>> local_vector){
    int machine_n, duration;
    tie(machine_n, duration) = local_vector[job_n][task_n];
    cout << "Job: " << job_n << " Task: " << task_n << " Machine: " << machine_n << " Duration: " << duration <<endl;
}*/

vector<vector<array<int,2>>> read_orlib(string filename, int* jobs, int* machines){
    //ifstream input_file(filename);
    
    // array<int,2> task;

    // if(input_file.fail()){
    //     perror("Error ocurred while opening the file!");
    //     exit(1);
    // }
    // else{
    //     int a,b;
        
    //     input_file >> *jobs;
    //     input_file >> *machines;
    //     vector<vector<array<int,2>>> main_vector(*machines);
    //     for(int x=0; x < *jobs; x++){
    //         for(int i=0; i < *machines; i++){
    //         input_file >> a >> b;
    //         task = {a,b};
    //         main_vector[x].push_back(task);
    //     } 
    //     }
    //     return main_vector;
    // }
    ifstream inputFile(filename);  // Zastąp "nazwa_pliku.txt" właściwą nazwą pliku

    if (!inputFile.is_open()) {
        cout << "Nie można otworzyć pliku!" << endl;
        exit(1);
    }

    inputFile >> *jobs >> *machines;

    vector<vector<array<int, 2>>> data(*jobs, vector<array<int, 2>>(*machines));

    for (int i = 0; i < *jobs; ++i) {
        for (int j = 0; j < *machines; ++j) {
            inputFile >> data[i][j][0] >> data[i][j][1];
        }
    }

    inputFile.close();
    return data;
}

bool TimeLeft(int elem, int currTime, int * job_total){
    if(job_total[elem] == currTime) return true;
    return false;
}

int currTimeJump(int currTime, int* job_total, int jobs, bool success){ //jesli success=true, zwroc najmniejsza, ww. drugi najmniejszy
    int smallest;
    int second_smallest;

    // if(job_total[0] < job_total[1]){
    //     smallest = job_total[0];
    //     second_smallest = job_total[1];
    // }
    // else{
    //     smallest = job_total[1];
    //     second_smallest = job_total[0];
    // }
    // for(int i = 2; i<jobs; i++){
    //     if(job_total[i] < second_smallest){
    //         if(job_total[i] < smallest){
    //             smallest = job_total[i];
    //         }
    //         else{
    //             second_smallest = job_total[i];
    //         }
    //     }
    // }
    smallest = INT_MAX;
    second_smallest = INT_MAX;

    for (int i = 0; i < jobs; ++i) {
        if (job_total[i] < smallest) {
            second_smallest = smallest;
            smallest = job_total[i];
        } else if (job_total[i] < second_smallest && job_total[i] != smallest) {
            second_smallest = job_total[i];
        }
    }
    if(!success){
        for(int i=0;i<jobs;i++){
            if(job_total[i]<second_smallest) job_total[i]=second_smallest; 
        }
        return second_smallest;
    }else{
        return smallest;
    }
    
}

void putTasks(int jobs, int machines, vector<vector<array<int,2>>> &arr, int *jobs_free, int& currTime, int* job_total,int& ctrl,vector<stack<int>> &out){
    int duration,machine_n;
    bool jobs_inserted;
    for(int i=0;i<jobs;i++){
        jobs_inserted = false;
        for(int j=0;j<machines;j++){
            duration = arr[i][j][1];
            machine_n = arr[i][j][0];
            //do osobnej funkcji bool
                if(machine_n>=0){
                    if(jobs_free[i] == 0 && TimeLeft(machine_n,currTime,job_total)){ //success!
                        jobs_inserted = true;
                        jobs_free[i]=duration;
                        //przerobić na funkcje
                        out[i].push(currTime);
                        job_total[machine_n] += duration;
                        arr[i][j][0]=-1;
                        ctrl++;
                    }
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

void PrintStack(stack<int>& stk)
{
    if (stk.empty())
        return;


    int top = stk.top();
    stk.pop();
    PrintStack(stk);
    cout << top << " ";
    //stk.push(top);
}

void updateJF(int* jobs_free, int GoneCurrTime, int CurrTime,int jobs){
    for(int i=0; i< jobs; i++){
        if(jobs_free[i] + GoneCurrTime - CurrTime > 0){
            jobs_free[i] = jobs_free[i] + GoneCurrTime - CurrTime;
        }
        else jobs_free[i] = 0;
    }
}

vector<vector<int>> priority(vector<vector<array<int,2>>> VectorOfVectors){
    int size = VectorOfVectors.size();
    int inner_size = VectorOfVectors[0].size();
    // int ** ctimes = new int * [size];
    vector<vector<int>> ctimes(size); // size = job number
    int temp = 0;
    // for (int i = 0; i<size; i++)
	// ctimes[i] = new int [2];

    for(int i=0;i<size;i++){
        temp = 0;
        for(int j=0;j<inner_size;j++){
            temp += VectorOfVectors[i][j][1];
        }
        ctimes[i].push_back(i);
        ctimes[i].push_back(temp);
    }
    sort(ctimes.begin(), ctimes.end(), compareTasks);

    return ctimes;
}

int main(int argc, char** argv) {

    
    int jobs, machines;
    vector<vector<array<int,2>>> ricardo;
    int control = 0;
    vector<vector<int>> ctimes;
    
    //ricardo = read_orlib(argv[1], &jobs, &machines);
    ricardo = read_orlib("instance2.txt", &jobs, &machines);
    
    int currTime = 0;
    int goneCurrTime;
    int * jobs_free = new int[jobs];
    fill_n(jobs_free, jobs, 0);
    int * job_total = new int[jobs];
    fill_n(job_total, jobs, 0);
    // int ** output = new int * [jobs];
    // for (int i = 0; i<jobs; i++)
	// 	output[i] = new int [machines];
    vector<stack<int>> output;
    for(int i=0;i<jobs;i++){
        stack<int> job;
        output.push_back(job);
    }

    cout << "JOBS: " << jobs << endl << "MACHINES: " << machines << endl;
        
    printVector(ricardo);

    
    while(control<jobs*machines){
        printArray(jobs_free, jobs);
        printArray(job_total,jobs);
        updateJF(jobs_free, goneCurrTime, currTime, jobs);
        cout<<currTime<<endl;
        goneCurrTime = currTime;
        putTasks(jobs,machines,ricardo,jobs_free,currTime,job_total,control,output);
        printVector(ricardo);
        printArray(jobs_free, jobs);
        printArray(job_total, jobs);
        
        //cout<<control;
        cout<<endl<<endl;
    }
    cout<<"Dziala XDDD"<<endl;
    
    for(int i=0;i<output.size();i++){
        PrintStack(output[i]);
        cout<<endl;
    }
    
    ctimes = priority(ricardo);

    for (const auto& innerVector : ctimes) {
        cout << "(" << innerVector[0] << ", " << innerVector[1] << ") ";
        cout << endl;
    }
    cout << endl;

    delete job_total;
    delete jobs_free;

    return 0;
}


