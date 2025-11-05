#include <iostream>
#include <vector>
#include <algorithm> // Needed for std::max

// As requested in your preferences, we'll use this namespace.
using namespace std;

/**
 * @brief Solves the 0-1 Knapsack problem using dynamic programming.
 * @param W The total capacity of the knapsack.
 * @param w An array of weights for each item.
 * @param v An array of values for each item.
 * @param n The number of items.
 * @return The maximum value that can be achieved.
 */
int knapsack(int W, int w[], int v[], int n) {
    // we need to create our dp table to start with dynamic programming.
    // Your comment: "it had weights on one side and quanity on another"
    // Close! The table (dp) will have 'items' on one axis (rows) 
    // and 'knapsack capacity' on the other (columns).

    // `dp[i][j]` will store the maximum value that can be obtained
    // using the first 'i' items with a total capacity of 'j'.

    // Using vector<vector<int>> is standard C++ and safer than VLAs.
    // We create a table of size (n+1) x (W+1) and initialize all to 0.
    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));

    // Build the table dp[][] in a bottom-up manner
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= W; j++) {
            
            // Get the weight and value of the *current* item.
            // We use 'i-1' because the arrays w[] and v[] are 0-indexed,
            // but our DP table's item-axis is 1-indexed.
            int currentWeight = w[i - 1];
            int currentValue = v[i - 1];

            // Case 1: The current item's weight is more than the
            // current capacity 'j'. We CANNOT include this item.
            // So, the max value is the same as the max value
            // without this item (i.e., the value from the row above).
            if (currentWeight > j) {
                dp[i][j] = dp[i - 1][j];
            } 
            
            // Case 2: The current item can fit (weight <= j).
            // We have two choices:
            else {
                // Choice 1: Don't include the item.
                // The value is the same as the row above.
                int value_without_item = dp[i - 1][j];

                // Choice 2: Include the item.
                // The value is (current item's value) + (the max value
                // we could get with the *remaining capacity*).
                // Remaining capacity = j - currentWeight
                int value_with_item = currentValue + dp[i - 1][j - currentWeight];

                // We take the maximum of these two choices.
                dp[i][j] = max(value_with_item, value_without_item);
            }
        }
    }

    // The final answer is in the bottom-right corner of the table:
    // The max value using all 'n' items with the full capacity 'W'.
    return dp[n][W];
}

int main() {
    // Example items
    int v[] = {60, 100, 120}; // Values
    int w[] = {10, 20, 30};  // Weights
    int W = 50;              // Knapsack capacity

    // Calculate the number of items
    // sizeof(v) / sizeof(v[0]) is a standard C-style way
    // to get the length of a static array.
    int n = sizeof(v) / sizeof(v[0]);

    cout << "Knapsack Capacity: " << W << endl;
    cout << "Number of items: " << n << endl;
    cout << "--- Items (Value, Weight) ---" << endl;
    for(int i = 0; i < n; i++) {
        cout << "Item " << i+1 << ": (" << v[i] << ", " << w[i] << ")" << endl;
    }

    int maxValue = knapsack(W, w, v, n);

    cout << "\nMaximum value in knapsack: " << maxValue << endl;
    
    // Expected Output for this example:
    // Items 2 and 3 (100 + 120 = 220)
    // with weights (20 + 30 = 50).
    // Let's check:
    // dp[1][50] (item 1 only) = 60
    // dp[2][50] (items 1, 2) = max(dp[1][50], 100 + dp[1][30]) = max(60, 100 + 60) = 160
    // dp[3][50] (items 1, 2, 3) = max(dp[2][50], 120 + dp[2][20]) = max(160, 120 + 100) = 220
    // The code should output 220.

    return 0;
}