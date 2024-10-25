#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <cmath>
#include <nlohmann/json.hpp>  

using json = nlohmann::json;
using namespace std;

// Function to decode y value from given base to decimal
long long decodeValue(int base, const string& value) {
    long long result = 0;
    for (char digit : value) {
        int num = (isdigit(digit)) ? digit - '0' : digit - 'a' + 10;
        result = result * base + num;
    }
    return result;
}

// Function to apply Lagrange interpolation at x = 0
long long findConstantTerm(const vector<pair<int, long long>>& points, int k) {
    long long constantTerm = 0;
    for (int j = 0; j < k; ++j) {
        long long xj = points[j].first;
        long long yj = points[j].second;
        
        
        long long term = yj;
        for (int i = 0; i < k; ++i) {
            if (i != j) {
                long long xi = points[i].first;
                term = term * (-xi) / (xj - xi);
            }
        }
        
        
        constantTerm += term;
    }
    return constantTerm;
}

int main() {
    // Load JSON from file
    ifstream inputFile1("input1.json");
    ifstream inputFile2("input2.json");
    json testCase1, testCase2;
    inputFile1 >> testCase1;
    inputFile2 >> testCase2;

    vector<pair<int, long long>> points1, points2;
    int k1 = testCase1["keys"]["k"];
    int k2 = testCase2["keys"]["k"];

    // Parse the points for testCase1
    for (auto& [xStr, val] : testCase1.items()) {
        if (xStr != "keys") {
            int x = stoi(xStr);
            int base = val["base"];
            string yValue = val["value"];
            long long y = decodeValue(base, yValue);
            points1.push_back({x, y});
        }
    }

    // Parse the points for testCase2
    for (auto& [xStr, val] : testCase2.items()) {
        if (xStr != "keys") {
            int x = stoi(xStr);
            int base = val["base"];
            string yValue = val["value"];
            long long y = decodeValue(base, yValue);
            points2.push_back({x, y});
        }
    }

    // Calculate the constant term for each test case
    long long constantTerm1 = findConstantTerm(points1, k1);
    long long constantTerm2 = findConstantTerm(points2, k2);

    // Output the constant terms
    cout << "Constant term for test case 1: " << constantTerm1 << endl;
    cout << "Constant term for test case 2: " << constantTerm2 << endl;

    return 0;
}
