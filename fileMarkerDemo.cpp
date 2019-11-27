#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

int main ()
{
    size_t eofMarker;
    size_t marker;
    size_t characterCtr = 0;
    string line;
    fstream inOutFile;

// This program modifies censusdata.txt. So, after you run it,
// you will have to restore censusdata.txt.

    inOutFile.open ("censusdata.test.txt", fstream::ate | fstream:: in | fstream::out);
    if (!inOutFile)
    {
        cout << "File open error" << endl;
        return EXIT_FAILURE;
    }

    eofMarker = inOutFile.tellg ();
    inOutFile << "0 -> ";

    inOutFile.seekg (0, fstream::beg);

    while (inOutFile &&
           inOutFile.tellg () != eofMarker &&
           getline (inOutFile, line))
    {
        characterCtr = characterCtr + line.length () + 1;
        marker = inOutFile.tellg ();
        inOutFile.seekp (0, fstream::end);
        inOutFile << line << endl;
        inOutFile << characterCtr << " -> ";
        inOutFile.seekg (marker);
    }
    inOutFile.seekp (0, fstream::end);
    inOutFile << "   EOF" << endl;
    inOutFile.close ();

    return 0;
}
