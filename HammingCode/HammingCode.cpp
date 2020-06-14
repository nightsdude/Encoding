#include <iostream>
#include <string>
#include <fstream>
#include <climits>

using namespace std;

/** 
 * Conceptual implementation of hamming codes.
 */
class HammingCode {
    public:
    string code;
    int length;

    HammingCode() {}

    HammingCode(string code) {
        this->code = string(code); 
        this->length = code.length();
    }

    /**
     * Calculates hamming distance between 2 conceptual hamming codes.
     */
    int hammingDistance(HammingCode code) {
        int comparisonLength = min(this->length, code.length);
        int hammingDifference = 0;

        for (int i = 0; i < comparisonLength; i++) {
            if (this->code.at(i) != code.code.at(i)) {
                hammingDifference++;
            }    
        }

        hammingDifference += max(this->length, code.length) - comparisonLength;

        return hammingDifference;
    }

    /**
     * Finds the correct conceptual hamming code - the code with the lowest hamming distance.
     */
    HammingCode findCorrectCode(HammingCode hammingCodes[], int codesLength) {
        int distance = INT_MAX;
        for (int i = 0; i < codesLength; i++) 
            for (int j = i + 1; j < codesLength; j++) {
                int hammingDiff = hammingCodes[i].hammingDistance(hammingCodes[j]);
                if (hammingDiff < distance) {
                    distance = hammingDiff;
                }
            }

        for (int i = 0; i < codesLength; i++) {
            int hammingDiff = this->hammingDistance(hammingCodes[i]);
                if (hammingDiff <= (distance - 1) / 2) {
                    return hammingCodes[i];
                }
        }

        return HammingCode();
    }

    /**
     * Checks if object is uninitialized - its fields are default values.
     */ 
    bool isEmpty() {
        if (this->code.empty()) {
            return true;
        }

        return false;
    }

    /**
     * Returns string representation of the hamming code.
     */
    string toString() {
        return this->code;
    }
};

// Reads the hamming codes and the code supplied for error correction.
int main(int argc,char* argv[]) {
    string line;
    HammingCode hammingCodes[10000];

    if (argc < 3) {
        cout << "Command line arguments missing." << endl;
        return 1;
    }

    int codesLength = 0;

    ifstream file(argv[1]);
    if(file.is_open()) {
        cout << "Retrieved Hamming codes are:" << endl;
        while (!file.eof()) 
        {
            getline(file, line);
            hammingCodes[codesLength] = HammingCode(line);
            cout << line << endl;
            codesLength++;
        }
    }
    else {
        cout << "File " << argv[1] << "does not exist." << endl;
        return 1;
    }

    HammingCode input = HammingCode(argv[2]);

    HammingCode correctCode = input.findCorrectCode(hammingCodes, codesLength);

    if (correctCode.isEmpty()) {
        cout << "The error may not be corrected." << endl;
        return 0;
    }

    if(input.hammingDistance(correctCode) == 0) {
        cout << "The code is correct - there is no error." << endl;
        return 0;
    }

    cout << "The correct code is: " << correctCode.toString() << endl;
    return 0;
}