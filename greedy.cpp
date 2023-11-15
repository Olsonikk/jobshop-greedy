#include <iostream>
#include <vector>
#include <array>
#include <algorithm> 
#include <fstream>
#include <string>
#include <climits>
#include <stack>


using namespace std;

bool compareTasks(const array<int,3>& task1, const array<int,3>& task2) {
    // Porównujemy taska na podstawie pierwszego elementu
    return task1[0] > task2[0];
}

/*void print_element(int job_n, int task_n, vector<vector<array<int,2>>> local_vector){
    int machine_n, duration;
    tie(machine_n, duration) = local_vector[job_n][task_n];
    cout << "Job: " << job_n << " Task: " << task_n << " Machine: " << machine_n << " Duration: " << duration <<endl;
}*/

vector<vector<array<int,2>>> read_tailard(string filename, int* jobs, int* machines){
    ifstream inputFile(filename);

    if (!inputFile.is_open()) {
        cout << "Nie można otworzyć pliku!" << endl;
        exit(1);
    }

    string tmp;

    inputFile >> *jobs >> *machines;
    
    getline(inputFile, tmp);
    getline(inputFile, tmp);

    vector<vector<array<int, 2>>> data(*jobs, vector<array<int, 2>>(*machines));

    for (int i = 0; i < *jobs; ++i) {
        for (int j = 0; j < *machines; ++j) {
            inputFile >> data[i][j][1];
        }
    }
    inputFile>>tmp;
    for (int i = 0; i < *jobs; ++i) {
        for (int j = 0; j < *machines; ++j) {
            inputFile >> tmp;
            data[i][j][0] = stoi(tmp)-1;
        }
    }

    inputFile.close();
    return data;
}

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

int currTimeJump(int currTime, int* job_total, int machines, bool success){ //jesli success=true, zwroc najmniejsza, ww. drugi najmniejszy
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

    for (int i = 0; i < machines; i++) {
        if (job_total[i] < smallest) {
            second_smallest = smallest;
            smallest = job_total[i];
        } else if (job_total[i] < second_smallest && job_total[i] != smallest) {
            second_smallest = job_total[i];
        }
    }
    if(!success){
        for(int i=0;i<machines;i++){
            if(job_total[i]<second_smallest) job_total[i]=second_smallest; 
        }
        return second_smallest;
    }else{
        return smallest;
    }
    
}

void PutInVec(int index,int machine_n,int duration, int currTime, int* job_total, int* job_free, int* job_index,vector<vector<array<int,2>>> &arr){
    // if(TimeLeft(machine_n,currTime,job_total)){ //success!
    //     job_free[index]=duration;
    //     job_total[machine_n] += duration;
    //     job_index[index]++;
    //     return true;
    // }
    // return false;
    job_free[index]=duration;
    job_total[machine_n] += duration;
    job_index[index]++;
}

void putTasks(int jobs, int machines, vector<vector<array<int,2>>> &arr, int *jobs_free, int& currTime, int* job_total,int& ctrl,vector<stack<int>> &out){
    int duration,machine_n;
    bool jobs_inserted;
    for(int i=0;i<jobs;i++){
        if(jobs_free[i] == 0){  
            jobs_inserted = false;
            for(int j=0;j<machines;j++){
                duration = arr[i][j][1];
                machine_n = arr[i][j][0];
                //do osobnej funkcji bool
                if(machine_n>=0){
                    if(TimeLeft(machine_n,currTime,job_total)){ //success!
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
    }

    currTime = currTimeJump(currTime, job_total, machines, jobs_inserted);
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

void PrintStack(stack<int> &stk, ofstream &outputFile)
{   
    if (stk.empty())
        return;
    int top = stk.top();
    stk.pop();
    PrintStack(stk, outputFile);
    outputFile << top << " ";
}

void updateJF(int* jobs_free, int GoneCurrTime, int CurrTime,int jobs){
    for(int i=0; i< jobs; i++){
        if(jobs_free[i] + GoneCurrTime - CurrTime > 0){
            jobs_free[i] = jobs_free[i] + GoneCurrTime - CurrTime;
        }
        else jobs_free[i] = 0;
    }
}

// int* Priority(vector<vector<array<int,2>>> VectorOfVectors){
//     int size = VectorOfVectors.size();
//     int inner_size = VectorOfVectors[0].size();
//     // int ** ctimes = new int * [size];
//     vector<vector<int>> ctimes(size); // size = job number
//     int * output_ctimes = new int[size];
//     int temp = 0;
//     // for (int i = 0; i<size; i++)
// 	// ctimes[i] = new int [2];

//     for(int i=0;i<size;i++){
//         temp = 0;
//         for(int j=0;j<inner_size;j++){
//             temp += VectorOfVectors[i][j][1];
//         }
//         ctimes[i].push_back(i);
//         ctimes[i].push_back(temp);
//     }
//     sort(ctimes.begin(), ctimes.end(), compareTasks);
    
//     for(int i=0;i<size;i++){
//         output_ctimes[i] = ctimes[i][0];
//     }

//     return output_ctimes;
// }

bool isReady(int index, int machine_n, int currTime, int* job_total, int* job_free, int* job_endFlag){
    if(job_endFlag[index]== 1 && job_free[index] == 0 && TimeLeft(machine_n, currTime, job_total)) return true;
    return false;
}

int main(int argc, char** argv) {
    int jobs, machines,cmax;
    int duration,machine_n;
    vector<vector<array<int,2>>> ricardo;

    // ricardo = read_tailard("tai80.txt",&jobs, &machines);
    // printVector(ricardo);

    int control = 0;
    int* ctimes;
    
    //ricardo = read_orlib(argv[1], &jobs, &machines);
    ricardo = read_orlib("instance5.txt", &jobs, &machines);
    printVector(ricardo);
    
    int currTime = 0;
    int goneCurrTime;
    int * job_endFlag = new int[jobs];
    fill_n(job_endFlag, jobs, 1);
    int * job_index = new int[jobs];
    fill_n(job_index, jobs, 0);
    int * job_free = new int[jobs];
    fill_n(job_free, jobs, 0);
    int * job_total = new int[machines];
    fill_n(job_total, machines, 0);
    // int ** output = new int * [jobs];
    // for (int i = 0; i<jobs; i++)
	// 	output[i] = new int [machines];
    vector<array<int,3>> chosen;
    vector<stack<int>> output;
    for(int i=0;i<jobs;i++){
        stack<int> job;
        output.push_back(job);
    }
    
    bool job_ready,success;

    while(control<jobs*machines){
        goneCurrTime = currTime;
        success = false;
        //putTasks(jobs,machines,ricardo,jobs_free,currTime,job_total,control,output);
        // for(int i=0;i<jobs;i++){
        //     if(job_endFlag[i]==1){
        //         //cout<<i<<" "<<job_index[i]<<endl;
        //         job_ready = false;
        //         if(job_free[i] == 0){  
        //             duration = ricardo[i][job_index[i]][1];
        //             machine_n = ricardo[i][job_index[i]][0];
        //             // cout<<"X "<<machine_n<<" "<<duration<<endl;
        //             //do osobnej funkcji bool
        //             //job_ready = PutInVec(i,machine_n,duration,currTime,job_total,job_free,job_index,ricardo);
        //             job_ready = TimeLeft(machine_n, currTime, job_total);
        //         }
        //         if(job_ready){
        //             success = true;
        //             PutInVec(i,machine_n,duration,currTime,job_total,job_free,job_index,ricardo);
        //             if(job_index[i] == machines) job_endFlag[i] = 0;
        //             //cout<<"X: "<<ricardo[i][job_index[i]-1][0]<<" "<<ricardo[i][job_index[i]-1][1]<<endl;
        //             output[i].push(currTime);
        //             control++;
        //         }
        //     }
        // }
        for(int i=0;i<jobs;i++){
            job_ready = false;
            duration = ricardo[i][job_index[i]][1];
            machine_n = ricardo[i][job_index[i]][0];
            //pętla dodająca taski sprawdzone f isReady do wektora
            if(isReady(i, machine_n, currTime, job_total, job_free, job_endFlag)){
                chosen.push_back({duration,machine_n,i});
            }
        }
        // for (const auto& tablica : chosen){
        // cout << "[" << tablica[0] << ", " << tablica[1] <<", "<<tablica[2]<< "] ";
        // }
        //cout<<endl;
        sort(chosen.begin(), chosen.end(), compareTasks);
        // for (const auto& tablica : chosen){
        // cout << "[" << tablica[0] << ", " << tablica[1] <<", "<<tablica[2]<< "] ";
        // }

        for (int i=0;i<chosen.size();i++){
            if(isReady(chosen[i][2], chosen[i][1], currTime, job_total, job_free, job_endFlag)){
                success = true;
                PutInVec(chosen[i][2],chosen[i][1],chosen[i][0],currTime,job_total,job_free,job_index,ricardo);
                if(job_index[chosen[i][2]] == machines) job_endFlag[chosen[i][2]] = 0;
                //cout<<"X: "<<ricardo[i][job_index[i]-1][0]<<" "<<ricardo[i][job_index[i]-1][1]<<endl;
                output[chosen[i][2]].push(currTime);
                control++;
            }
        }
        chosen.clear();
        // if(job_ready){
        //     success = true;
        //     PutInVec(i,machine_n,duration,currTime,job_total,job_free,job_index,ricardo);
        //     if(job_index[i] == machines) job_endFlag[i] = 0;
        //     //cout<<"X: "<<ricardo[i][job_index[i]-1][0]<<" "<<ricardo[i][job_index[i]-1][1]<<endl;
        //     output[i].push(currTime);
        //     control++;
        // }
        currTime = currTimeJump(currTime, job_total, machines, success);
        //cout<<currTime;
        //cout<<endl;
        //printArray(job_free,jobs);
        //printArray(job_total,machines);
        //cout<<endl;
        updateJF(job_free, goneCurrTime, currTime, jobs);
        //cout<<"XD"<<endl;
    }
    // //cout<<"Dziala XDDD"<<endl;
    //cout<<"co jest kurwa";
    //printArray(job_free, jobs);
    printArray(job_total, machines);
    cout<<endl;
    cout<<*max_element(job_total,job_total+machines)<<endl;

    ofstream outFile("output.txt");
    for(int i=0;i<output.size();i++){
        PrintStack(output[i], outFile); //dodac na poczatek pliku Cmax
        outFile<<endl;
    }
    outFile.close();
    
    // // for (const auto& innerVector : ctimes) {
    // //     cout << "(" << innerVector[0] << ", " << innerVector[1] << ") ";
    // //     cout << endl;
    // // }
    // // cout << endl;
    

    delete job_total;
    delete job_free;
    delete job_endFlag;
    delete job_index;

    return 0;
}


