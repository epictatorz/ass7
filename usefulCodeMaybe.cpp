#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;

struct instruction
{
    string operation;
    char *operand;
};

int main ()
{
    instruction program [20];
    int i = -1;
    string operation;
    string operand;
    char dummy;

    cin >> operation;
    while (operation != "-1")
    {
        i ++;
        program [i].operation = operation;
        cin.get (dummy);
        if (dummy == '\n')
        {
            operand = "";
        }
        else
        {
            getline (cin, operand);
        }
        program [i].operand = new char [operand.length () + 1];
        strcpy (program [i].operand, operand.c_str ());
        cout << program [i].operation << " ";
        if (program [i].operation == "jump")
        {
            cout << atoi (program [i].operand);
        }
        else
        {
            cout << program [i].operand;
        }
        cout << endl;
        cin >> operation;
    }

    while (i > 0)
    {
        if (program [i].operand != (char) NULL)
        {
            free (program [i].operand);
        }
        i --;
    }

    return 0;
}
