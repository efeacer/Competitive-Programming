/**
 * Given a set of coins and a taget amount of money, this program computes the way of changing this money
 * with smallest number of coins.
 * @author EFE ACER
 */

//Necessary Imports
#include <iostream>
#include <set>
#include <vector>
#include <unordered_map>

using namespace std;

//Constant declerations
int UNDEFINED = INT_MAX - 1;

//Function Declerations
int makeChangeIterative(set<int, greater<int>> & coinsAvailable, int & targetAmount, int firstCoinInEachSolution[], unordered_map<int, int> & memory);
int makeChangeRecursive(set<int, greater<int>> & coinsAvailable, int currentAmount, int firstCoinInEachSolution[], unordered_map<int, int> & memory);
vector<int> getBestSolution(int firstCoinInEachSolution[], int targetAmount, unordered_map<int, int> & memory);
void printFirstCoinInEachSolution(int firstCoinInEachSolution[], int & size);
void printBestSolution(vector<int> & bestSolution);
void printCoinsAvailable(set<int, greater<int>> & coinsAvailable);

//Main Method
int main() {
    cout << "Given a set of coins and a taget amount of money, this program computes"
    " the way of changing this money with the smallest number of coins. (it is assumed that"
    " the inputs are comformable.)\n\n";
    cout << "Enter the number of coins that are available to you: ";
    int numberOfCoins;
    cin >> numberOfCoins;
    cout << "Enter the coins in your coin set as space seperated numbers:\n ";
    set<int, greater<int>> coinsAvailable;
    for (int i = 0; i < numberOfCoins; i++) {
        int coin;
        cin >> coin;
        coinsAvailable.insert(coin);
    }
    printCoinsAvailable(coinsAvailable);
    cout << "Enter the taget amount of money: ";
    int targetAmount;
    cin >> targetAmount;
    unordered_map<int, int> memory;
    int firstCoinInEachSolution[targetAmount + 1];
    makeChangeIterative(coinsAvailable, targetAmount, firstCoinInEachSolution, memory); //uncomment for the iterative solution
    //makeChangeRecursive(coinsAvailable, targetAmount, firstCoinInEachSolution, memory); //uncomment for the recursive solution
    vector<int> bestSolution = getBestSolution(firstCoinInEachSolution, targetAmount, memory);
    printBestSolution(bestSolution);
}

/**
 * @brief Uses a dynamic programming aproach, computes and returns the smallest amount
 * of coins that can be used to change the given money. Keeps track of the first money
 * used in each solution to be able to get back to the optimal solution.
 * @param coinsAvailable The set of coins that are available.
 * @param firstCoinInEachSolution An array of the first coins used in each solution.
 * @param targetAmount The amount we want to change.
 * @param memory A mapping between the money amounts and the minimum number of coins used to change them.
 * @return The smallest amount of coins that can be used to change the given money
 */
int makeChangeIterative(set<int, greater<int>> & coinsAvailable, int & targetAmount, int firstCoinInEachSolution[], unordered_map<int, int> & memory) {
    memory[0] = 0; //0 ways of changing 0 amount of money
    for (int currentAmount = 1; currentAmount <= targetAmount; currentAmount++) {
        memory[currentAmount] = UNDEFINED; //we don't know how to change the current amount yet
        for (auto coin: coinsAvailable) {
            if (currentAmount - coin >= 0 && memory[currentAmount - coin] != UNDEFINED && memory[currentAmount - coin] + 1 < memory[currentAmount]) {
                memory[currentAmount] = memory[currentAmount - coin] + 1;
                firstCoinInEachSolution[currentAmount] = coin; //to keep track of the best solution
            }
        }
    }
    return memory[targetAmount];
}

/**
 * @brief Uses recursive memoization, computes and returns the smallest amount
 * of coins that can be used to change the given money. Keeps track of the first money
 * used in each solution to be able to get back to the optimal solution.
 * @param coinsAvailable The set of coins that are available.
 * @param firstCoinInEachSolution An array of the first coins used in each solution.
 * @param currentAmount The amount we want to change.
 * @param memory A mapping between the money amounts and the minimum number of coins used to change them.
 * @return The smallest amount of coins that can be used to change the given money
 */
int makeChangeRecursive(set<int, greater<int>> & coinsAvailable, int currentAmount, int firstCoinInEachSolution[], unordered_map<int, int> & memory) {
    if (currentAmount < 0) {
        return UNDEFINED; //it is not defined to make a change for a negative amount of money
    } else if (currentAmount == 0) {
        return 0; //0 ways of changing 0 amount of money
    } else if (memory.count(currentAmount)) {
        return memory[currentAmount]; //memoization
    }
    int bestSolution = UNDEFINED;
    for (auto coin: coinsAvailable) {
        int solution = makeChangeRecursive(coinsAvailable, currentAmount - coin, firstCoinInEachSolution, memory) + 1;
        if (solution < bestSolution) {
            bestSolution = solution;
            firstCoinInEachSolution[currentAmount] = coin; //to keep track of the best solution
        }
    }
    memory[currentAmount] = bestSolution; //memoization
    return bestSolution;
}

/**
 * @brief Generates the best solution from an array of the first coins used in each solution.
 * @param firstCoinInEachSolution An array of the first coins used in each solution.
 * @param targetAmount The amount we want to change.
 * @param memory A mapping between the money amounts and the minimum number of coins used to change them.
 * @return The best solution stored in a list.
 */
vector<int> getBestSolution(int firstCoinInEachSolution[], int targetAmount, unordered_map<int, int> & memory) {
    vector<int> bestSolution;
    if (memory[targetAmount] == UNDEFINED) {
        return bestSolution;
    }
    while (targetAmount > 0) {
        bestSolution.push_back(firstCoinInEachSolution[targetAmount]);
        targetAmount -= firstCoinInEachSolution[targetAmount];
    }
    return bestSolution;
}

/**
 * @brief Prints the set of coins that are available.
 * @param coinsAvailable The set of coins that are available.
 */
void printCoinsAvailable(set<int, greater<int>> & coinsAvailable) {
    string coinSet = "The set of coins available: [";
    for (auto coinAvailable: coinsAvailable) {
        coinSet += to_string(coinAvailable) + ", ";
    }
    coinSet = coinSet.substr(0, coinSet.length() - 2) + "]\n";
    cout << coinSet;
}

/**
 * @brief Prints the a list of coins.
 * @param bestSolution The given list of coins.
 */
void printBestSolution(vector<int> & bestSolution) {
    if (bestSolution.empty()) {
        cout << "There is no way to change the amount you have entered.\n";
        return;
    }
    string usedCoins = "The list of " + to_string(bestSolution.size()) + " coins used: [";
    for (auto coinUsed: bestSolution) {
        usedCoins += to_string(coinUsed) + ", ";
    }
    usedCoins = usedCoins.substr(0, usedCoins.length() - 2) + "]\n";
    cout << usedCoins;
}



