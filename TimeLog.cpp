//Header files
#include <iostream>
#include <fstream>
#include <ctime>
#include <iomanip>
using namespace std;

struct DataRecord {

        char logger; // Define logging Point A, B, C, ...
        double temp; // Logged Temperature
        time_t locTime; // Local Time
};

int main() {

        DataRecord data; //Create instance of struct

        //Memeber varaibles of struct
        data.logger = 'A';
        data.temp;
        data.locTime;

        ofstream outputfile("Data.txt"); //Open text file for writing 

        if (!outputfile) { // error control
                cout << "Cannot open file for writing." << endl;
                return 1;
        }

        ifstream inputfile("timelog.dat", ios::binary); //Open dat file for reading

        if (!inputfile.is_open()) { // error control
                cout << "Failed to open the file timelog.dat!" << endl;
                return 1;
        }

        outputfile << "Data A" << endl;

        //Process binary file and write to outputfile 'A'
        while (!inputfile.fail()) {
                inputfile.read((char*)(&data.logger), sizeof(data.logger));
                inputfile.read((char*)(&data.temp), sizeof(data.temp));
                inputfile.read((char*)(&data.locTime), sizeof(data.locTime));
                if (data.logger == 'A') {
                        struct tm* timeinfo;
                        time(&data.locTime);
                        timeinfo = localtime((&data.locTime));
                        outputfile << setprecision(2) << data.temp << " " << asctime(timeinfo) << endl;
                }
        }
        inputfile.close();
        outputfile.close();

        return 0;
}

