#include <iostream>
#include <string>
#include <fstream>
#include <climits>
#include <bitset> 

using namespace std;

#define B 8

/** 
 * Conceptual implementation of hamming codes.
 */
class HammingCode {
    public:
    bitset<B> bits;
    int size;

    HammingCode() {
        this->size = 0;
    }

    HammingCode(string code) {
        this->bits = bitset<B>(code);
        this->size = B; 
    }

    /**
     * Calculates hamming distance between 2 conceptual hamming codes.
     */
    int hammingDistance(HammingCode code) {
        int hammingDifference = 0;

        for (int i = 0; i < B; i++) {
            if (this->bits[i] != code.bits[i]) {
                hammingDifference++;
            }    
        }

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
        if (this->size == 0) {
            return true;
        }

        return false;
    }

    /**
     * Returns string representation of the hamming code.
     */
    string toString() {
        char bitChars[B];

        for (int i = 0; i < B; i++) {
            if(bits[i]) {
                bitChars[i] = '1';
            }
            else {
                bitChars[i] = '0';
            }
        }

        return string(bitChars);
    }
};

// Reads the hamming codes and the code supplied for error correction.
// USAGE: HammingCode hammingCodes 00000001
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
        cout << "The code is correct." << endl;
        return 0;
    }

    cout << "The correct code is: " << correctCode.toString() << endl;
    return 0;
}