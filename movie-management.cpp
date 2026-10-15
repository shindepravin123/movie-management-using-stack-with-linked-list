#include <iostream>
#include <string>
using namespace std;

struct Movie {
    string name;
    int year;
    Movie* next;
};

Movie* top = NULL;

// Add movie
void push() {
    Movie* newMovie = new Movie;

    cout << "Enter movie name: ";
    cin.ignore();
    getline(cin, newMovie->name);

    cout << "Enter release year: ";
    cin >> newMovie->year;

    newMovie->next = top;
    top = newMovie;

    cout << "Movie added successfully!\n";
}

// Remove movie
void pop() {
    if (top == NULL) {
        cout << "No movies available.\n";
        return;
    }

    Movie* temp = top;

    cout << "Removed movie: " << top->name << endl;

    top = top->next;
    delete temp;
}

// Display movies
void display() {
    if (top == NULL) {
        cout << "No movies available.\n";
        return;
    }

    Movie* temp = top;

    cout << "\n--- Movie List ---\n";

    while (temp != NULL) {
        cout << "Movie: " << temp->name
             << " | Year: " << temp->year << endl;

        temp = temp->next;
    }
}

int main() {
    int choice;

    while (true) {
        cout << "\n--- Movie Management ---\n";
        cout << "1. Add Movie\n";
        cout << "2. Remove Movie\n";
        cout << "3. Display Movies\n";
        cout << "4. Exit\n";

        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                push();
                break;

            case 2:
                pop();
                break;

            case 3:
                display();
                break;

            case 4:
                return 0;

            default:
                cout << "Invalid choice!\n";
        }
    }
}