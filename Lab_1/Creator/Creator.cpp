#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <limits>

using namespace std;

struct employee {
    int num;           
    char name[10];     
    double hours;      
};

int main(int argc, char* argv[]) {
    try {

        if (argc != 3) {
            throw invalid_argument(
                string("Usage: ") + argv[0] + " <output-file> <record-count>");
        }

        const char* filename = argv[1];
        int recordCount = stoi(argv[2]);

        if (recordCount <= 0) {
            throw invalid_argument(
                string("Invalid record count: ") + argv[2]);
        }

        ofstream fout(filename, ios::binary);
        fout.exceptions(ofstream::failbit | ofstream::badbit);

        for (int i = 0; i < recordCount; ++i) {
            employee emp;
            string tmp;

            cout << "Enter information about employee number " << (i + 1) << "\n";

            while (true) {
                cout << "Employee identification number: ";
                if (!(cin >> emp.num)) {
                    cout << "Error: please enter a valid integer for employee ID.\n";
                    cin.clear(); 
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    continue;
                }
                if (emp.num < 0) {
                    cout << "Error: ID can't be negative.\n";
                    continue;
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }

       

            while (true) {
                cout << "Employee's name: ";
                if (!getline(cin, tmp)) {
                    cout << "Input error. Please try again.\n";
                    continue;
                }
                
                size_t start = tmp.find_first_not_of(" \t");
                size_t end = tmp.find_last_not_of(" \t");

                if (start == string::npos) {
                    cout << "Name can't be empty. Please try again.\n";
                    continue;
                }

                tmp = tmp.substr(start, end - start + 1);

                
                if (tmp.length() > 9) {
                    cout << "Error: Name is too long. Maximum length is 9 characters.\n";
                    continue;
                }

          
                strcpy_s(emp.name, sizeof(emp.name), tmp.c_str());
                break;
            }

            while (true) {
                cout << "Number of working hours: ";
                if (!(cin >> emp.hours)) {
                    cout << "Error: please enter a valid count of hours.\n";
                    cin.clear(); 
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
                }
                if (emp.hours < 0) {
                    cout << "Error: Working hours can't be negative.\n";
                    continue;
                }
                break;
            }

            fout.write(reinterpret_cast<const char*>(&emp), sizeof(emp));
        }

        fout.close();
        cout << "Done. Wrote " << recordCount << " records into \"" << filename << "\"\n";
        
    }
   
    catch (const invalid_argument& e) {
        cerr << "Argument error: " << e.what() << endl;
        return 1;
    }
    catch (const out_of_range& e) {
        cerr << "Out of range error: " << e.what() << endl;
        return 2;
    }
    catch (const ios_base::failure& e) {
        cerr << "I/O error: " << e.what() << endl;
        return 3;
    }
    catch (const exception& e) {
        cerr << "Unexpected error: " << e.what() << endl;
        return 4;
    }
    return 0;
}

