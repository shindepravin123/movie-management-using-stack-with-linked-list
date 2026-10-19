// Income Tax Slab Lookup using a Binary Search Tree (Floor & Ceiling)
// Each node represents a slab lower boundary and its tax rate.
#include <iostream>
#include <vector>
using namespace std;

struct Node {
    long long limit;   // Slab lower limit (Rs.)
    double rate;       // Tax rate in percent
    Node *left, *right;

    Node(long long l, double r)
        : limit(l), rate(r), left(NULL), right(NULL) {}
};

Node *root = NULL;

Node* insertSlab(Node *r, long long limit, double rate) {
    if (r == NULL)
        return new Node(limit, rate);

    if (limit < r->limit)
        r->left = insertSlab(r->left, limit, rate);
    else if (limit > r->limit)
        r->right = insertSlab(r->right, limit, rate);
    else
        r->rate = rate; // Update the rate if the limit already exists.

    return r;
}

// Returns the largest slab limit less than or equal to income.
Node* floorSlab(Node *r, long long income) {
    Node *res = NULL;

    while (r != NULL) {
        if (r->limit == income)
            return r;

        if (r->limit < income) {
            res = r;
            r = r->right;
        } else {
            r = r->left;
        }
    }

    return res;
}

// Returns the smallest slab limit greater than or equal to income.
Node* ceilSlab(Node *r, long long income) {
    Node *res = NULL;

    while (r != NULL) {
        if (r->limit == income)
            return r;

        if (r->limit > income) {
            res = r;
            r = r->left;
        } else {
            r = r->right;
        }
    }

    return res;
}

void inorder(Node *r, vector<Node*> &v) {
    if (r == NULL)
        return;

    inorder(r->left, v);
    v.push_back(r);
    inorder(r->right, v);
}

void destroy(Node *r) {
    if (r == NULL)
        return;

    destroy(r->left);
    destroy(r->right);
    delete r;
}

void displaySlabs() {
    vector<Node*> v;
    inorder(root, v);

    if (v.empty()) {
        cout << "No slabs defined.\n";
        return;
    }

    cout << "\nIncome From (Rs.)\tRate\n";
    cout << "-------------------------------\n";

    for (size_t i = 0; i < v.size(); i++)
        cout << v[i]->limit << "\t\t\t" << v[i]->rate << "%\n";
}

void lookup() {
    long long income;

    cout << "Enter annual income (Rs.): ";
    if (!(cin >> income)) {
        cout << "Invalid input.\n";
        return;
    }

    if (income < 0) {
        cout << "Invalid income. Income cannot be negative.\n";
        return;
    }

    Node *f = floorSlab(root, income);
    Node *c = ceilSlab(root, income);

    if (f)
        cout << "Floor slab limit: Rs. " << f->limit
             << " (rate " << f->rate << "%)\n";
    else
        cout << "Floor slab limit: none (income is below the lowest slab).\n";

    if (c)
        cout << "Ceiling slab limit: Rs. " << c->limit
             << " (rate " << c->rate << "%)\n";
    else
        cout << "Ceiling slab limit: none (income is above the highest slab).\n";
}

void calculateTax() {
    long long income;

    cout << "Enter annual income (Rs.): ";
    if (!(cin >> income)) {
        cout << "Invalid input.\n";
        return;
    }

    if (income < 0) {
        cout << "Invalid income. Income cannot be negative.\n";
        return;
    }

    vector<Node*> v;
    inorder(root, v);

    double tax = 0.0;

    // Apply each slab's rate only to income within that slab's range.
    for (size_t i = 0; i < v.size() && v[i]->limit < income; i++) {
        long long upper = income;

        if (i + 1 < v.size() && v[i + 1]->limit < income)
            upper = v[i + 1]->limit;

        tax += (upper - v[i]->limit) * v[i]->rate / 100.0;
    }

    Node *f = floorSlab(root, income);

    cout << "Applicable slab starts at: Rs. " << (f ? f->limit : 0) << "\n";
    cout << "Estimated total tax (before cess/rebate): Rs. " << tax << "\n";
    cout << "Note: This is a sample slab model, not official tax advice.\n";
}

void addSlab() {
    long long limit;
    double rate;

    cout << "Enter slab lower limit (Rs.): ";
    if (!(cin >> limit)) {
        cout << "Invalid input.\n";
        return;
    }

    cout << "Enter tax rate (%): ";
    if (!(cin >> rate)) {
        cout << "Invalid input.\n";
        return;
    }

    if (limit < 0 || rate < 0 || rate > 100) {
        cout << "Invalid input. Limit must be non-negative and rate must be from 0 to 100.\n";
        return;
    }

    root = insertSlab(root, limit, rate);
    cout << "Slab saved successfully.\n";
}

void loadSampleSlabs() {
    // Illustrative sample slabs; update them for your project requirements.
    long long limits[] = {0, 400000, 800000, 1200000, 1600000, 2000000, 2400000};
    double rates[] = {0, 5, 10, 15, 20, 25, 30};

    // Insert in a mixed order to create a reasonably balanced BST.
    int order[] = {3, 1, 5, 0, 2, 4, 6};

    for (int i = 0; i < 7; i++)
        root = insertSlab(root, limits[order[i]], rates[order[i]]);
}

int main() {
    loadSampleSlabs();

    int choice;

    do {
        cout << "\n--- INCOME TAX SLAB LOOKUP (BST) ---\n";
        cout << "1. Add / update slab\n";
        cout << "2. Display slabs\n";
        cout << "3. Find floor and ceiling for income\n";
        cout << "4. Calculate tax\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";

        if (!(cin >> choice)) {
            cout << "Invalid input. Exiting program.\n";
            break;
        }

        switch (choice) {
            case 1:
                addSlab();
                break;
            case 2:
                displaySlabs();
                break;
            case 3:
                lookup();
                break;
            case 4:
                calculateTax();
                break;
            case 5:
                cout << "Bye!\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);

    destroy(root);
    root = NULL;

    return 0;
}
