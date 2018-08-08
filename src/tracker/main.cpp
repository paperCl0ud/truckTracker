#include <iostream>
#include <iomanip>
#include <fstream>
#include <stdint.h>
#include <string>
#include <cmath>
#include <vector>

const uint8_t NUM_VALS_IN_FIRST_STR = 2;
const uint8_t NUM_VALS_IN_STR       = 3;

std::vector<double> splitString(const std::string& string, char seperator)
{
    std::string::size_type lastPos = 0;
    std::string::size_type     pos = 0; 
    
    std::vector<double> output;

    while ((pos = string.find(seperator, pos)) != std::string::npos)
    {
        output.push_back(std::stod(string.substr(lastPos, pos - lastPos)));
        lastPos = ++pos;
    }

    output.push_back(std::stod(string.substr(lastPos, pos - lastPos)));

    return output;
}

int main(int argc, char *argv[])
{
    std::string inputFileName;

    if (argc > 1) 
    {
        inputFileName  = argv[1];
    }
    else
    {
        std::cerr << "Enter the command line argument" << std::endl;
        return 0;
    }

    std::ifstream file(inputFileName);

    if (file.is_open())
    {
        std::string line;

        getline(file, line);

        std::vector<double> vec = splitString(line, ' ');

        if (vec.size() != NUM_VALS_IN_FIRST_STR)
        {
            std::cerr << "Wrong input file format" << std::endl;
            return 0;
        }

        double currentX = 0;
        double currentY = 0;

        double b = vec[0];
        double R = vec[1];

        while (getline(file, line, '\n'))
        {
            vec = splitString(line, ' ');

            if (vec.size() != NUM_VALS_IN_STR)
            {
                std::cerr << "Wrong input file format" << std::endl;
                return 0;
            }

            double timeStamp  = vec[0];
            double angleLeft  = vec[1];
            double angleRight = vec[2];

            currentX = ((angleLeft + angleRight) * (0.5 * R)) * cos((angleRight - angleLeft) * (R / b));
            currentY = ((angleLeft + angleRight) * (0.5 * R)) * sin((angleRight - angleLeft) * (R / b));
        }

        file.close();

        double radiusVector = sqrt(pow(currentX, 2) + pow(currentY, 2));

        std::cout << "Current position (X; Y): "
                  << std::setprecision(std::numeric_limits<double>::digits10 + 1)
                  << currentX 
                  << " ; " 
                  << currentY
                  << std::endl; 

        std::cout << "Current radius vetor:    "
                  << std::setprecision(std::numeric_limits<double>::digits10 + 1)
                  << radiusVector
                  << std::endl;
    }

    return 0;
}
