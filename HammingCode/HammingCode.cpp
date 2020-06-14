#include <iostream>
#include <string>
#include <fstream>
#include <climits>
#include <bitset> 

using namespace std;

#define B 8

/** 
 * Implementation of hamming codes.
 */
class HammingCode {
    private:
    bitset<B> bits;
    int size;
    
    public:
    HammingCode() {
        this->size = 0;
    }

    HammingCode(string code) {
        this->bits = bitset<B>(code);
        this->size = B; 
    }

    /**
     * Calculates hamming distance between 2 hamming codes.
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
     * Checks if object is unpopulated.
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
                bitChars[B - i - 1] = '1'; // bitset uses the other endian
            }
            else {
                bitChars[B - i - 1] = '0'; // bitset uses the other endian
            }
        }

        return string(bitChars);
    }
};

/**
 * Container for HammingCode objects.
 */
class HammingCodes {
    private:
        HammingCode hammingCodes[10000];
        int size;
        int distance;


    public:

    /**
     * Placeholder constructor.
     * Used as a null.
     */
    HammingCodes() {
        this->size = 0;
        this->distance = 0;
    }

    /**
     * Constructs the immutable object.
     * It calculates the minimal hamming distance btw any of the codes and stores it for later code error detection and correction. 
     */
    HammingCodes(string codes[], int codesLength) {
        for(int i = 0; i < codesLength; i++) {
            hammingCodes[i] = codes[i];
        }

        this->size = codesLength;

        int distance = INT_MAX;
        for (int i = 0; i < this->size; i++) 
            for (int j = i + 1; j < this->size; j++) {
                int hammingDiff = this->hammingCodes[i].hammingDistance(this->hammingCodes[j]);
                if (hammingDiff < distance) {
                    distance = hammingDiff;
                }
            }

        this->distance = distance;
    }

    /**
     * Finds the correct hamming code - the code with the lowest hamming distance.
     */
    HammingCode findCorrectCode(HammingCode code) {
        int correctionDist = (this->distance - 1) / 2;
        
        for (int i = 0; i < this->size; i++) {
            int hammingDiff = code.hammingDistance(hammingCodes[i]);
                if (hammingDiff <= correctionDist) {
                    return hammingCodes[i];
                }
        }

        return HammingCode();
    }

};

// Reads the hamming codes and the code supplied for error correction.
// USAGE: HammingCode hammingCodes 00000001
int main(int argc,char* argv[]) {
    string line;
    
    string codes[10000];
    HammingCodes hammingCodes;

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
            codes[codesLength] = line;
            cout << line << endl;
            codesLength++;
        }

        hammingCodes = HammingCodes(codes, codesLength);
    }
    else {
        cout << "File " << argv[1] << "does not exist." << endl;
        return 1;
    }

    HammingCode input = HammingCode(argv[2]);

    HammingCode correctCode = hammingCodes.findCorrectCode(input);

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