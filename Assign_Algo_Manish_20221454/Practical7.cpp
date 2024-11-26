#include <iostream>
#include <vector>
using namespace std;

// Function to compute the Longest Prefix Suffix (LPS) array
void computeLPSArray(const string& pattern, vector<int>& lps) {
    int m = pattern.size();
    int len = 0; // Length of the previous longest prefix suffix
    lps[0] = 0;  // LPS of the first character is always 0

    int i = 1;
    while (i < m) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1]; // Fall back to the previous LPS
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

// KMP Search Function
void KMPSearch(const string& text, const string& pattern) {
    int n = text.size();
    int m = pattern.size();

    // Compute the LPS array
    vector<int> lps(m);
    computeLPSArray(pattern, lps);

    int i = 0; // Index for text
    int j = 0; // Index for pattern

    while (i < n) {
        if (pattern[j] == text[i]) {
            i++;
            j++;
        }

        if (j == m) {
            cout << "Pattern found at index " << (i - j) << endl;
            j = lps[j - 1]; // Reset j using LPS array
        } else if (i < n && pattern[j] != text[i]) {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }
}

// Main function
int main() {
    string text, pattern;

    cout << "Enter the text: ";
    cin >> text;

    cout << "Enter the pattern to search: ";
    cin >> pattern;

    KMPSearch(text, pattern);

    return 0;
}
