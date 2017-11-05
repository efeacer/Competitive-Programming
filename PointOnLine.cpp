#include <iostream>

using namespace std;

int main() {
    int numberOfPoints, distanceLimit;
    cin >> numberOfPoints >> distanceLimit;
    int points[numberOfPoints]; //the array holding the points
    for (int i = 0; i < numberOfPoints; i++) { //reading the inputs
        cin >> points[i];
    }
    long long count = 0;
    for (int i = 0; i < numberOfPoints; i++) {
        int index = i;
        for (int jump = (numberOfPoints - i) / 2; jump >= 1; jump /= 2) { //binary search loop
            while (index + jump < numberOfPoints && points[index + jump] - points[i] <= distanceLimit) {
                index += jump;
            }
        }
        if (index - i >= 2) { //finding the index where the point with the maximum magnitude is
            count += (long long) (index - i) * (index - i - 1) / 2; //counting the solutions
        }
    }
    cout << count << endl;
    return 0;
}

