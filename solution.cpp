#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

//////////////////////////////////////////////////////
//                 Set config below                 //
//////////////////////////////////////////////////////

// When CurrentAccuracy is not greater than 
// TargetAccuracy, we consider the x_i^* as the 
// optimal value.                                  
const double TargetAccuracy = 0.1;

// RandomAlphaGenerator will generator a array of
// \alpha_i where each \alpha_i is not bigger than 
// AlphaiMax and not smaller than AlphaiMin     
const double AlphaiMax = 2;
const double AlphaiMin = 1;

// Default StepPerCycle
double StepPerCycle = (AlphaiMax - AlphaiMin) / 10;

///////////////////////////////////////////////////////
//                     Utils                         //
///////////////////////////////////////////////////////

vector<double> RandomAlphaGenerator(
    int /* how many \alpha_i to generate = */ AlphaiCount) {
    time_t t;
    srand((unsigned) time(&t));
    vector<double> Alpha;
    for(int i = 0; i < AlphaiCount; i++) {
        double ZeroOneRand;
        ZeroOneRand = (double) (rand() % 999) / 999;
        Alpha.push_back(
            ZeroOneRand * (AlphaiMax - AlphaiMin) + AlphaiMin
        );
    }
    return Alpha;
}

// Loss caculator.
// Loss Function: L = \sum \max{0, 1/v^* - \alpha_i} - 1
// We make abs(L) as small as possible
double CaculateLoss(vector<double>* Alpha,
                    double x) {
    return 0;
}

// LastLoss: for StepController to dertermine whether
// it should make the step smaller for the next cycle
double LastLoss = AlphaiMax;
// StepController: make the step smaller when abs(Loss)
// does not converge.
// Returns a double var of updated StepPerCycle
double StepController() {
    return 0;
}

// Optimizer, core function
double Optimizer(vector<double>* Alpha,
                 double x) {
    return 0;
}

int main() {
    cout << "Enter the count of channels: ";
    int AlphaiCount; 
    cin >> AlphaiCount; cout << endl;

    // print the Alpha sequence
    cout << "Alpha = [";
    vector<double> Alpha = RandomAlphaGenerator(AlphaiCount);
    for (vector<double>::iterator iter = Alpha.begin();
         iter != Alpha.end(); iter++) {
        if (iter != Alpha.begin()) cout << ", ";
        cout << *iter;
    } cout << "]" << endl;


}