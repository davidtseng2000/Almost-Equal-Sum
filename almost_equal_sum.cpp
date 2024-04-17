#include<bits/stdc++.h>

using namespace std;

string output_file = "./out.txt";

struct SetInfo {
    vector<string> elements;
    vector<float> values;
    float sum;
};

vector<SetInfo> divide_almost_equally(vector<pair<string, float>>& inputs, int num_chunks) {
    sort(inputs.begin(), inputs.end(), [](const pair<string, float>& a, const pair<string, float>& b) {
        return a.second > b.second;
    });
    priority_queue<pair<float, int>, vector<pair<float, int>>, greater<pair<float, int>>> heap;
    for (int idx = 0; idx < num_chunks; ++idx) {
        heap.push(make_pair(0, idx));
    }
    vector<SetInfo> sets(num_chunks);
    int arr_idx = 0;
    while (arr_idx < inputs.size()) {
        auto top = heap.top();
        float set_sum = top.first;
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

void printBefore(vector<pair<string,float>> inputs){

    ofstream outputFile(output_file);

    float total_sum = accumulate(inputs.begin(), inputs.end(), 0, [](float sum, const pair<string, float>& p) {
        return sum + p.second;
    });    
    
    for(int i = 0; i < 50; i++) outputFile << '*';
    outputFile << endl;

    outputFile  << "Sorted Array: ";
    for (pair<string,float> val : inputs) {
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
        for (float num : sets[i].values) {
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
    vector<pair<string,float>> inputs;
    string name;
    float value;
    inputFile >> num_chunks;
    while (inputFile >> name >> value) { 
        inputs.push_back(make_pair(name, value));
    }
    inputFile.close(); 

    // Counting total sum before process
    sort(inputs.begin(), inputs.end(), [](const pair<string, float>& a, const pair<string, float>& b) {
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
