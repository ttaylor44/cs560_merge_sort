/*
Taran Taylor u793s399
compile using g++ -std=c++20 -o out merge_sort.cpp
then ./out to run program

This program will run part A of the assignment after you assert how many 
integers you want to sort. It will display all information to the console. 

It will then prompt you to run part b or not. 
*/

#include <iostream>
#include <random>
#include <vector>
#include <chrono>
#include <fstream>

#define MAX_RANGE 10000

std::vector<int> getInputAndGenerate(std::vector<int> &nums);
void printNums(std::vector<int> nums);
void merge(std::vector<int> &nums, int p, int q, int r);
void mergeSort(std::vector<int> &nums, int l, int r);
int run10();
int run100();
int run1000();
int run10000();
void outputToFile(std::vector<int> &nums);
void runPartB();

int main() {
    std::vector<int> nums;
    getInputAndGenerate(nums);
    //if you want to see the vector before the sort uncomment the next line
    //printNums(nums);

    auto start = std::chrono::high_resolution_clock::now();

    mergeSort(nums, 0, nums.size() - 1);

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Time taken to sort N integers: " << duration.count() << " microseconds." << std::endl;
    
    char choice;
    std::cout << "\n\nOutput sorted vector to console(c) or file(f)? ";
    std::cin >> choice;
    if(choice == 'c' || choice == 'C') {
        printNums(nums);
    } 
    else if(choice == 'f' || choice == 'F') {
        outputToFile(nums);
    }

    runPartB();
    
    return 0;
}

void runPartB() {
    char ans;
    int sum10 = 0, sum100 = 0, sum1000 = 0, sum10000 = 0;
    std::cout << "\n\nRun Part B? (y/n): ";
    std::cin >> ans;
    std::cout << std::endl << std::endl;
    if(ans == 'y' || ans == 'Y') {
        for(int i = 0; i < 5; i++) {
            sum10 += run10();
            sum100 += run100();
            sum1000 += run1000();
            sum10000 += run10000();

        }
        std::cout << sum10/5 << " is the average runtime for 10 integers." << std::endl;
        std::cout << sum100/5 << " is the average runtime for 100 integers." << std::endl;
        std::cout << sum1000/5 << " is the average runtime for 1000 integers." << std::endl;
        std::cout << sum10000/5 << " is the average runtime for 10000 integers." << std::endl;
    }
}

void outputToFile(std::vector<int> &nums) {
    std::cout << "\n\nCheck directory for file named: outFile.txt" << std::endl << std::endl;
    std::ofstream outFile("outFile.txt");
    for(int i = 0; i < nums.size(); i++) {
        outFile << nums[i] << " ";
        if(i > 0 && i % 10 == 0) {
            outFile << "\n";
        }
    }
    outFile.close();
}

std::vector<int> getInputAndGenerate(std::vector<int> &nums) {
   
    //get number of intgers from user

    int N = 0;
    std::cout << "Enter number of integers to generate: ";
    std::cin >> N;
    
    //using random device, generate a number between 0 and 10000

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> getNum(0, MAX_RANGE); 

    //enter the number integers desired into a vector

    for(int i = 0; i < N; i++) {
        nums.push_back(getNum(rng));
    }
    return nums;
}

void printNums(std::vector<int> nums) {
    for(int i = 0; i < nums.size(); i++) {
        std::cout << nums[i] << " ";
    }
    std::cout << std::endl;
}

void merge(std::vector<int> &nums, int p, int q, int r) {
    int n1 = q - p + 1;
    int n2 = r - q;

    int L[n1], R[n2];

    for(int i = 0; i < n1; i++) {
        L[i] = nums[p + i];
    }
    for(int j = 0; j < n2; j++) {
        R[j] = nums[q + 1 + j];
    }

    int i = 0, j = 0, k = p;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
        nums[k] = L[i];
        i++;
        } else {
        nums[k] = R[j];
        j++;
        }
        k++;
    }

    while (i < n1) {
        nums[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        nums[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(std::vector<int> &nums, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;

        mergeSort(nums, l, m);
        mergeSort(nums, m + 1, r);

        merge(nums, l, m, r);
    }
}

int run10() {
    /*
    get vector full of 10 intgers run mergeSort and return the runtime.
    */
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> getNum(0, MAX_RANGE); 
    
    std::vector<int> nums;

    for(int i = 0; i < 10; i++) {
        nums.push_back(getNum(rng));
    }

    auto start = std::chrono::high_resolution_clock::now();
    mergeSort(nums, 0, nums.size() - 1);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = duration_cast<std::chrono::microseconds>(stop - start);
    int runtime = duration.count();

    return runtime;
}

int run100() {
    /*
    get vector full of 10 intgers run mergeSort and return the runtime.
    */
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> getNum(0, MAX_RANGE); 
    
    std::vector<int> nums;

    for(int i = 0; i < 100; i++) {
        nums.push_back(getNum(rng));
    }

    auto start = std::chrono::high_resolution_clock::now();
    mergeSort(nums, 0, nums.size() - 1);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = duration_cast<std::chrono::microseconds>(stop - start);
    int runtime = duration.count();

    return runtime;
}

int run1000() {
    /*
    get vector full of 10 intgers run mergeSort and return the runtime.
    */
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> getNum(0, MAX_RANGE); 
    
    std::vector<int> nums;

    for(int i = 0; i < 1000; i++) {
        nums.push_back(getNum(rng));
    }

    auto start = std::chrono::high_resolution_clock::now();
    mergeSort(nums, 0, nums.size() - 1);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = duration_cast<std::chrono::microseconds>(stop - start);
    int runtime = duration.count();

    return runtime;
}

int run10000() {
    /*
    get vector full of 10 intgers run mergeSort and return the runtime.
    */
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> getNum(0, MAX_RANGE); 
    
    std::vector<int> nums;

    for(int i = 0; i < 10000; i++) {
        nums.push_back(getNum(rng));
    }

    auto start = std::chrono::high_resolution_clock::now();
    mergeSort(nums, 0, nums.size() - 1);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = duration_cast<std::chrono::microseconds>(stop - start);
    int runtime = duration.count();

    return runtime;
}