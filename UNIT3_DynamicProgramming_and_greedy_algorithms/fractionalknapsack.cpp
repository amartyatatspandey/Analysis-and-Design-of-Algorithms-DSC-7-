#include <iostream>
#include <vector>
#include <algorithm> // For std::sort

// As requested in your preferences, we'll use this namespace.
using namespace std;

/**
 * @brief A structure to represent an item
 * for the Fractional Knapsack problem.
 */
struct Item {
    int id;
    int value;
    int weight;
    double ratio; // value per weight

    // Constructor to easily create items
    Item(int id, int v, int w) : id(id), value(v), weight(w) {
        if (w > 0) {
            ratio = (double)value / weight;
        } else {
            ratio = 0.0; // Handle division by zero, though
                         // a 0-weight item with value > 0
                         // would be taken infinitely.
                         // We assume weights are positive.
        }
    }
};

/**
 * @brief A comparison function used by std::sort
 * to sort items based on their ratio (value per weight)
 * in descending order.
 * @param a The first item.
 * @param b The second item.
 * @return true if a's ratio is greater than b's ratio.
 */
bool compareItems(const Item& a, const Item& b) {
    return a.ratio > b.ratio;
}

/**
 * @brief Solves the Fractional Knapsack problem using a greedy approach.
 * @param W The total capacity of the knapsack.
 * @param items A vector of items.
 * @return The maximum total value that can be achieved.
 */
double fractionalKnapsack(int W, vector<Item>& items) {
    int n = items.size();

    // 1. Sort items based on value-per-weight ratio
    sort(items.begin(), items.end(), compareItems);

    cout << "--- Items Sorted by Value/Weight Ratio ---" << endl;
    for (const auto& item : items) {
        cout << "Item " << item.id 
             << " (Value: " << item.value 
             << ", Weight: " << item.weight 
             << ", Ratio: " << item.ratio << ")" << endl;
    }
    cout << "------------------------------------------" << endl;


    int currentWeight = 0;   // Current weight in knapsack
    double finalValue = 0.0; // Total value in knapsack

    cout << "\n--- Filling the Knapsack (Capacity: " << W << ") ---" << endl;

    // 2. Iterate through sorted items and fill the knapsack
    for (int i = 0; i < n; i++) {
        
        // Case 1: The entire item fits
        if (currentWeight + items[i].weight <= W) {
            currentWeight += items[i].weight;
            finalValue += items[i].value;
            cout << "Took full Item " << items[i].id 
                 << " (Weight: " << items[i].weight 
                 << ", Value: " << items[i].value << ")" << endl;
        } 
        
        // Case 2: Only a fraction of the item fits
        else {
            int remainingCapacity = W - currentWeight;
            
            // Take the fraction of the item
            double fraction = (double)remainingCapacity / items[i].weight;
            double valueOfFraction = items[i].ratio * remainingCapacity;
            
            finalValue += valueOfFraction;
            currentWeight += remainingCapacity; // Knapsack is now full
            
            cout << "Took " << (fraction * 100.0) << "% of Item " << items[i].id
                 << " (Weight: " << remainingCapacity 
                 << ", Value: " << valueOfFraction << ")" << endl;

            // 3. Knapsack is full, so we can stop
            break; 
        }
    }

    return finalValue;
}


int main() {
    int W = 50; // Knapsack capacity

    // Create a vector of items
    vector<Item> items;
    items.emplace_back(1, 60, 10);  // ID, Value, Weight
    items.emplace_back(2, 100, 20);
    items.emplace_back(3, 120, 30);

    /*
     * Ratios:
     * Item 1: 60 / 10 = 6
     * Item 2: 100 / 20 = 5
     * Item 3: 120 / 30 = 4
     *
     * Sorted Order (by ratio): Item 1, Item 2, Item 3
     *
     * Filling Process (W = 50):
     * 1. Take Item 1 (Weight 10, Value 60).
     * Remaining Capacity: 50 - 10 = 40. Total Value: 60.
     * 2. Take Item 2 (Weight 20, Value 100).
     * Remaining Capacity: 40 - 20 = 20. Total Value: 60 + 100 = 160.
     * 3. Take Item 3 (Weight 30, Value 120).
     * Can't take full item. Need to take fraction.
     * Fraction to take = 20 / 30 = 0.667
     * Value of fraction = 0.667 * 120 = 80
     * Weight of fraction = 20.
     * Remaining Capacity: 20 - 20 = 0. Total Value: 160 + 80 = 240.
     */

    cout << "Knapsack Capacity: " << W << endl << endl;

    double maxValue = fractionalKnapsack(W, items);

    cout << "\n------------------------------------------" << endl;
    cout << "Maximum value in knapsack: " << maxValue << endl;

    return 0;
}