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
const double TargetAccuracy = 1e-5;
// How many water
const double WaterSum = 1;

// If abs(LastLoss) >= StepControlThreshold * abs(CurrentLoss), 
// we will divide the StepPerCycle by StepDivider
const double StepControlThreshold = 0.5;
const double StepDivider = 2;

// RandomAlphaGenerator will generator a array of
// \alpha_i where each \alpha_i is not bigger than 
// AlphaiMax and not smaller than AlphaiMin     
const double AlphaiMax = 2;
const double AlphaiMin = 1;
double ExpectedLoss = TargetAccuracy * (AlphaiMax - AlphaiMin);
// Default StepPerCycle
double StepPerCycle = (AlphaiMax - AlphaiMin) / 10;

///////////////////////////////////////////////////////
//                     Utils                         //
///////////////////////////////////////////////////////

// if sgn(x)m == sgn(y) return 0, else return 1
bool SgnDiff(double x, double y) {
    if ((x >= 0 && y <= 0) || (x <= 0 && y >= 0))
        return 1;
    else 
        return 0;
}

vector<double> RandomAlphaGenerator(
    int /* how many \alpha_i to generate = */ AlphaiCount) {
    // initialize rand function
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
double CaculateLoss(vector<double>& Alpha,
                    double y) {
    // We first caculate the sum of the 'water'
    // then get the loss by L = S - 1.
    double Sum = 0;
    for(vector<double>::iterator iter = Alpha.begin();
        iter != Alpha.end(); iter++) {
        if (y > *iter)
            Sum += y - *iter;
    }
    double Loss = Sum - WaterSum;
    return Loss;
}

// LastLoss: for StepController to dertermine whether
// it should make the step smaller for the next cycle
double LastLoss;
// StepController: make the step smaller when abs(Loss)
// does not converge.
int StepCount = 0;
// Returns a double var of updated StepPerCycle
void StepController(double CurrentLoss) {
    if (abs(CurrentLoss) <= StepControlThreshold * abs(LastLoss))
        StepPerCycle /= StepDivider;
    if (abs(CurrentLoss) > abs(LastLoss) 
        || SgnDiff(CurrentLoss, LastLoss)) {
        StepPerCycle /= StepDivider;
        StepPerCycle = - StepPerCycle;
    }
        
    StepCount++;
    return;
}

// Optimizer, core function
double Optimizer(vector<double>& Alpha,
                 double y) {
    // double CurrentLoss = CaculateLoss(Alpha, y);
    // if (abs(CurrentLoss) <= ExpectedLoss) {
    //     LastLoss = CurrentLoss;
    //     return y;
    // } else {
    //     StepController(CurrentLoss);
    //     LastLoss = CurrentLoss;
    //     y += StepPerCycle;
    //     return Optimizer(Alpha, y);
    // }

    // SHOULD NOT USE RECURSION 
    // WILL CAUSE STACK OVERFLOW if n >= 500
    // Use while conditionals instead
    double CurrentLoss = CaculateLoss(Alpha, y);
    LastLoss = CurrentLoss;
    while (abs(CurrentLoss) > ExpectedLoss) {
        StepController(CurrentLoss);
        LastLoss = CurrentLoss;
        y += StepPerCycle;
        CurrentLoss = CaculateLoss(Alpha, y);
    }
    LastLoss = CurrentLoss;
    return y;
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

    double ExpectedY = Optimizer(Alpha, AlphaiMin);

    cout << ExpectedY << "\t" << LastLoss << "\t"
         << StepCount << endl;
    return 0;
}