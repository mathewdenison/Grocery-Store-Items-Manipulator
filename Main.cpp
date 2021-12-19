#include <Python.h>
#include <iostream>
#include <iomanip>
#define NOMINMAX
#include <Windows.h>
#undef NOMINMAX
#include <cmath>
#include <string>
#include <fstream>

using namespace std;

/*
Description:
        To call this function, simply pass the function name in Python that you wish to call.
Example:
        callProcedure("printsomething");
Output:
        Python will print on the screen: Hello from python!
Return:
        None
*/
void CallProcedure(string pName)
{
    char* procname = new char[pName.length() + 1];
    std::strcpy(procname, pName.c_str());

    Py_Initialize();
    PyObject* my_module = PyImport_ImportModule("PythonCode");
    PyErr_Print();
    PyObject* my_function = PyObject_GetAttrString(my_module, procname);
    PyObject* my_result = PyObject_CallObject(my_function, NULL);
    Py_Finalize();

    delete[] procname;
}


/*
Description:
        To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
        int x = callIntFunc("PrintMe","Test");
Output:
        Python will print on the screen:
                You sent me: Test
Return:
        100 is returned to the C++
*/
int callIntFunc(string proc, string param)
{
    char* procname = new char[proc.length() + 1];
    std::strcpy(procname, proc.c_str());

    char* paramval = new char[param.length() + 1];
    std::strcpy(paramval, param.c_str());


    PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
    // Initialize the Python Interpreter
    Py_Initialize();
    // Build the name object
    pName = PyUnicode_FromString((char*)"PythonCode");
    // Load the module object
    pModule = PyImport_Import(pName);
    // pDict is a borrowed reference 
    pDict = PyModule_GetDict(pModule);
    // pFunc is also a borrowed reference 
    pFunc = PyDict_GetItemString(pDict, procname);
    if (PyCallable_Check(pFunc))
    {
        pValue = Py_BuildValue("(z)", paramval);
        PyErr_Print();
        presult = PyObject_CallObject(pFunc, pValue);
        PyErr_Print();
    }
    else
    {
        PyErr_Print();
    }
    //printf("Result is %d\n", _PyLong_AsInt(presult));
    Py_DECREF(pValue);
    // Clean up
    Py_DECREF(pModule);
    Py_DECREF(pName);
    // Finish the Python Interpreter
    Py_Finalize();

    // clean 
    delete[] procname;
    delete[] paramval;


    return _PyLong_AsInt(presult);
}


/*
Description:
        To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
        int x = callIntFunc("doublevalue",5);
Return:
        25 is returned to the C++
*/
int callIntFunc(string proc, int param)
{
    char* procname = new char[proc.length() + 1];
    std::strcpy(procname, proc.c_str());

    PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
    // Initialize the Python Interpreter
    Py_Initialize();
    // Build the name object
    pName = PyUnicode_FromString((char*)"PythonCode");
    // Load the module object
    pModule = PyImport_Import(pName);
    // pDict is a borrowed reference 
    pDict = PyModule_GetDict(pModule);
    // pFunc is also a borrowed reference 
    pFunc = PyDict_GetItemString(pDict, procname);
    if (PyCallable_Check(pFunc))
    {
        pValue = Py_BuildValue("(i)", param);
        PyErr_Print();
        presult = PyObject_CallObject(pFunc, pValue);
        PyErr_Print();
    }
    else
    {
        PyErr_Print();
    }
    //printf("Result is %d\n", _PyLong_AsInt(presult));
    Py_DECREF(pValue);
    // Clean up
    Py_DECREF(pModule);
    Py_DECREF(pName);
    // Finish the Python Interpreter
    Py_Finalize();

    // clean 
    delete[] procname;

    return _PyLong_AsInt(presult);
}


/*
Description:
        When this function is called, it will produce a menu to prompt user input.
Example:
        DrawMenu();
Output:
        Outputs a menu that will take user input between 1-4. User input will then execute the appropriate Python function.
        That is, a user input of 1 will output a list of unique words and their number of appearances, input of 2 will
        search for the number of a single item's appearances, an input of 3 will print a histogram of each item's appearances,
        and an input of 4 will quit the program.
Return:
        None
*/
void menu() {

    //Define variables required
    int LoopTotal = 0;                                                       
    int ItemTotal = 0;                                                      
    int Items = 0;                                           
    string userInput;                                                     
    string Name;                                                        
    ifstream fileInput;

    while (LoopTotal != 4) {

        //Create Menu
        cout << "1: Get total of each item" << endl;
        cout << "2: Get total based on given input" << endl;
        cout << "3: Histogram of each item with totals" << endl;
        cout << "4: Exit" << endl;

        cin >> LoopTotal;

        //Input validation.
        while (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid Entry\n;" << "Please Enter Valid Entry (1-4)";
            cin >> LoopTotal;
        }


        //Cases based on given valid inputs
        switch (LoopTotal) {

            //Calculate totals of each object
        case 1:
            //Clear menu, found online
            system("CLS");
            //Call python function
            CallProcedure("CountObj");                      
            cout << endl;
            break;

            //Get total based on user input
        case 2:
            //Clear menu
            system("CLS");
            cout << "Enter name of the product: " << endl;
            cin >> userInput;

            //Call python funtion and get information on total of user input from list
            ItemTotal = callIntFunc("CountTotals", userInput);

            cout << endl << userInput << ": " << ItemTotal << endl << endl;

            break;

            //Output histogram
        case 3:
            system("CLS");                                         
            CallProcedure("CollectData");
            //Call python function

            fileInput.open("frequency.dat");

            fileInput >> Name;
            fileInput >> Items;

            //Create loop to build histogram
            while (!fileInput.fail()) {

                //Output name and get set up for histogram with given total spaces between item name and item totals
                cout << setw(14) << left << Name << setw(6);


                //Output item quantities with a ~
                for (int i = 0; i < Items; i++) {

                    //Print tilde for count of item
                    cout << right << "~ ";
                }
                //Output new line and set up for new line in histogram
                std::cout << std::endl;
                fileInput >> Name;
                fileInput >> Items;
            }

            fileInput.close();
            break;

            //quit the program
        case 4:
            return;

            //Input validation
        default:
            std::cout << "Invalid input: ";
            std::cout << std::endl;
            break;
        }
    }
}

//Call main
void main()
{
    //Call menu
    menu();

}