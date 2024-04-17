#include<bits/stdc++.h>

using namespace std;

string output_file = "./out.txt";

struct SetInfo {
    vector<string> elements;
    vector<int> values;
    int sum;
};

vector<SetInfo> divide_almost_equally(vector<pair<string, int>>& inputs, int num_chunks) {
    sort(inputs.begin(), inputs.end(), [](const pair<string, int>& a, const pair<string, int>& b) {
        return a.second > b.second;
    });
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> heap;
    for (int idx = 0; idx < num_chunks; ++idx) {
        heap.push(make_pair(0, idx));
    }
    vector<SetInfo> sets(num_chunks);
    int arr_idx = 0;
    while (arr_idx < inputs.size()) {
        auto top = heap.top();
        int set_sum = top.first;
        int set_idx = top.second;
        heap.pop();
        sets[set_idx].elements.push_back(inputs[arr_idx].first);
        sets[set_idx].values.push_back(inputs[arr_idx].second);
        sets[set_idx].sum += inputs[arr_idx].second;
        heap.push(make_pair(sets[set_idx].sum, set_idx));
        arr_idx++;
    }
    return sets;
}


// void printdummy(){
//     for(int i = 0; i < 50; i++) cout << '*';
//     cout << endl;
// }

void printBefore(vector<pair<string,int>> inputs){

    ofstream outputFile(output_file);

    int total_sum = accumulate(inputs.begin(), inputs.end(), 0, [](int sum, const pair<string, int>& p) {
        return sum + p.second;
    });    
    
    for(int i = 0; i < 50; i++) outputFile << '*';
    outputFile << endl;

    outputFile  << "Sorted Array: ";
    for (pair<string,int> val : inputs) {
        outputFile  << val.second << " ";
    }
    outputFile  << endl << "Total sum: " << total_sum <<  endl;
    outputFile.close();

    for(int i = 0; i < 50; i++) outputFile << '*';
    outputFile << endl;
}

void printAfter(vector<SetInfo> sets){

    ofstream outputFile(output_file, ios::app);

    int num_chunks = sets.size();
    for (int i = 0; i < num_chunks; ++i) {
        for(int i = 0; i < 50; i++) outputFile << '*';
            outputFile << endl;

        outputFile << "Set " << i + 1 << ": ";
        for (string name : sets[i].elements) {
            outputFile << name << " ";
        }
        outputFile << endl;

        outputFile << "Values ";
        for (int num : sets[i].values) {
            outputFile << num << " ";
        }
        outputFile << endl;

        outputFile << "Total sum: " << sets[i].sum << endl;
    }
    outputFile.close();
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <input_file>" << endl;
        return 1;
    }

    int num_chunks;

    ifstream inputFile(argv[1]);
    if (!inputFile) {
        cerr << "Failed to open the file." << endl;
        return 1;
    }

    // Reading inputs from input_file
    vector<pair<string,int>> inputs;
    string name;
    int value;
    inputFile >> num_chunks;
    while (inputFile >> name >> value) { 
        inputs.push_back(make_pair(name, value));
    }
    inputFile.close(); 

    // Counting total sum before process
    sort(inputs.begin(), inputs.end(), [](const pair<string, int>& a, const pair<string, int>& b) {
        return a.second > b.second;
    });    
    // printdummy();
    printBefore(inputs);
    // printdummy();    

    // Main dividing algorithm
    auto sets = divide_almost_equally(inputs, num_chunks);
    printAfter(sets);

    return 0;
}
