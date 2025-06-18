#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
using namespace std;

struct Task {
    int id;
    string title;
    string dueDate; // Format: YYYY-MM-DD
};

vector<Task> tasks;
const string filename = "tasks.txt";

// Utility to get current date as string
string getCurrentDate() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    char buf[11];
    sprintf(buf, "%04d-%02d-%02d", 1900 + ltm->tm_year, 1 + ltm->tm_mon, ltm->tm_mday);
    return string(buf);
}

void loadTasks() {
    tasks.clear();
    ifstream fin(filename);
    Task t;
    while (fin >> t.id >> ws && getline(fin, t.title) && getline(fin, t.dueDate)) {
        tasks.push_back(t);
    }
    fin.close();
}

void saveTasks() {
    ofstream fout(filename);
    for (Task t : tasks) {
        fout << t.id << endl << t.title << endl << t.dueDate << endl;
    }
    fout.close();
}

void addTask() {
    Task t;
    cout << "Enter task title: ";
    cin.ignore();
    getline(cin, t.title);
    cout << "Enter due date (YYYY-MM-DD): ";
    cin >> t.dueDate;
    t.id = tasks.empty() ? 1 : tasks.back().id + 1;
    tasks.push_back(t);
    saveTasks();
    cout << "Task added successfully!\n";
}

void editTask() {
    int id;
    cout << "Enter task ID to edit: ";
    cin >> id;
    bool found = false;
    for (Task &t : tasks) {
        if (t.id == id) {
            cout << "New title: ";
            cin.ignore();
            getline(cin, t.title);
            cout << "New due date (YYYY-MM-DD): ";
            cin >> t.dueDate;
            found = true;
            break;
        }
    }
    if (found) {
        saveTasks();
        cout << "Task updated!\n";
    } else {
        cout << "Task not found.\n";
    }
}

void deleteTask() {
    int id;
    cout << "Enter task ID to delete: ";
    cin >> id;
    bool found = false;
    for (auto it = tasks.begin(); it != tasks.end(); ++it) {
        if (it->id == id) {
            tasks.erase(it);
            found = true;
            break;
        }
    }
    if (found) {
        saveTasks();
        cout << "Task deleted.\n";
    } else {
        cout << "Task not found.\n";
    }
}

void showTodayTasks() {
    string today = getCurrentDate();
    cout << "\nToday's Tasks (" << today << "):\n";
    bool any = false;
    for (Task t : tasks) {
        if (t.dueDate == today) {
            cout << "ID: " << t.id << " | " << t.title << " | Due: " << t.dueDate << endl;
            any = true;
        }
    }
    if (!any) cout << "No tasks for today.\n";
}

void listAllTasks() {
    cout << "\nAll Tasks:\n";
    for (Task t : tasks) {
        cout << "ID: " << t.id << " | " << t.title << " | Due: " << t.dueDate << endl;
    }
}

int main() {
    loadTasks();
    int choice;
    do {
        cout << "\n--- Task Scheduler ---\n";
        cout << "1. Add Task\n2. Edit Task\n3. Delete Task\n4. Show Today's Tasks\n5. Show All Tasks\n6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addTask(); break;
            case 2: editTask(); break;
            case 3: deleteTask(); break;
            case 4: showTodayTasks(); break;
            case 5: listAllTasks(); break;
            case 6: cout << "Goodbye!\n"; break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 6);
    return 0;
}
