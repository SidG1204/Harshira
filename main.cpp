#include <bits/stdc++.h>
using namespace std;

// Convert a string number from given base to decimal
long long convertToDecimal(const string &value, int base) {
    long long result = 0;
    for (char c : value) {
        int digit;
        if (isdigit(c)) digit = c - '0';
        else if (isalpha(c)) digit = tolower(c) - 'a' + 10;
        else continue;
        result = result * base + digit;
    }
    return result;
}

// Multiply current polynomial with (x - root)
vector<long long> multiplyPoly(const vector<long long> &poly, long long root) {
    vector<long long> result(poly.size() + 1, 0);

    for (size_t i = 0; i < poly.size(); i++) {
        result[i] += poly[i];              // coefficient * x
        result[i + 1] -= poly[i] * root;   // multiply by -root
    }
    return result;
}

int main() {
    // Hardcode JSON-like input (for test case 2)
    struct Root { int base; string value; };
    map<int, Root> roots = {
        {1, {6, "13444211440455345511"}},
        {2, {15, "aed7015a346d635"}},
        {3, {15, "6aeeb69631c227c"}},
        {4, {16, "e1b5e05623d881f"}},
        {5, {8, "316034514573652620673"}},
        {6, {3, "2122212201122002221120200210011020220200"}},
        {7, {3, "20120221122211000100210021102001201112121"}},
        {8, {6, "20220554335330240002224253"}},
        {9, {12, "45153788322a1255483"}},
        {10, {7, "1101613130313526312514143"}}
    };

    int n = 10;
    int k = 7; // minimum roots required
    vector<long long> decimalRoots;

    // Convert roots to decimal
    for (int i = 1; i <= n; i++) {
        long long dec = convertToDecimal(roots[i].value, roots[i].base);
        decimalRoots.push_back(dec);
    }

    // Use first k roots
    vector<long long> selected(decimalRoots.begin(), decimalRoots.begin() + k);

    // Start polynomial with "1"
    vector<long long> poly = {1};

    // Expand (x - r1)(x - r2)...(x - rk)
    for (long long root : selected) {
        poly = multiplyPoly(poly, root);
    }

    // Print polynomial
    cout << "Polynomial coefficients (highest degree first):\n";
    for (int i = poly.size() - 1; i >= 0; i--) {
        cout << poly[i] << (i > 0 ? " " : "");
    }
    cout << endl;

    return 0;
}
