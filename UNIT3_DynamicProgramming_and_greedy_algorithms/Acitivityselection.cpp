#include <iostream>
#include <vector>
#include <algorithm> // For std::sort

// As requested in your preferences, we'll use this namespace.
using namespace std;

/**
 * @brief A structure to represent an activity,
 * containing its start time and finish time.
 */
struct Activity {
    int id;
    int start;
    int finish;
};

/**
 * @brief A comparison function used by std::sort
 * to sort activities based on their finish time.
 * @param a The first activity.
 * @param b The second activity.
 * @return true if a finishes before b, false otherwise.
 */
bool compareActivities(const Activity& a, const Activity& b) {
    return (a.finish < b.finish);
}

/**
 * @brief Solves the Activity Selection problem.
 * Prints the IDs of the selected activities.
 * @param activities A vector of all activities.
 */
void selectActivities(vector<Activity>& activities) {
    int n = activities.size();
    if (n == 0) {
        cout << "No activities to select." << endl;
        return;
    }

    // 1. Sort activities based on finish time
    sort(activities.begin(), activities.end(), compareActivities);

    cout << "--- Activities Sorted by Finish Time ---" << endl;
    for (const auto& act : activities) {
        cout << "Activity " << act.id << ": [" << act.start << ", " << act.finish << "]" << endl;
    }
    cout << "---------------------------------------" << endl;
    

    cout << "\n--- Selected Activities ---" << endl;

    // 2. The first activity is always selected
    //