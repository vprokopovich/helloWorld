#include <iostream>
#include <cstddef>
#include <time.h>
#include <functional>
#include <vector>
#include <cstdint>

class Experiment
{
public:
    
    Experiment(int measurements = 10, int repetitions = 100)
        : m_countMeasurements(measurements)
        , m_countRepetitions(repetitions)
    {}

    typedef std::function<void()> fn_type;

    std::uint64_t run(fn_type& runFunction)
    {
        std::uint64_t retVal = 0;
        std::uint64_t measure = 0;

        for (int j = 0; j < m_countMeasurements; j++)
        {        
            measure = clock();

            for (int i = 0; i < m_countRepetitions; i++)
            {
                runFunction();
            }

            retVal += (clock() - measure) / m_countMeasurements;
        }

        return retVal;
    }
private:
    int m_countMeasurements;
    int m_countRepetitions;
};

// TODO: read about SIMD

int main()
{
    std::vector<std::pair<size_t, size_t>> dimensions = {{64, 4688}, {4688, 64}, {1000, 300}, {300, 1000}};
    /*
    std::cout << "========== Matrix as vector of vectors ==========" << std::endl;
    for (auto& dimension : dimensions)
    {
        auto m = dimension.first;
        auto n = dimension.second;

        int** pArr = new int*[m];  // Creates array of M pointers to arrays
        for (size_t i = 0; i < m; i++)
        {
            pArr[i] = new int[n];
        }
        

        std::function<void()> accessByRow = [&]()
        { 
            int summ = 0;
            for (size_t i = 0; i < m; i++)
            {
                for (size_t j = 0; j < n; j++)
                {
                    summ += pArr[i][j];
                }
            }
        };

        std::function<void()> accessByColumn = [&]()
        { 
            int summ = 0;
            for (size_t i = 0; i < n; i++)
            {
                for (size_t j = 0; j < m; j++)
                {
                    summ += pArr[j][i];
                }
            }
        };

        Experiment e;
        std::cout << "Matrix " << m << "x" << n << "(" << n << "elements in the row)" << std::endl;

        auto timeByRow = e.run(accessByRow) ;
        std::cout << "Average Access By Row:    "
                  << timeByRow
                  << " Processing time for element: " << static_cast<double>(timeByRow * 1000 / (m*n)) << "ns"
                  << std::endl;

        auto timeByColumn = e.run(accessByColumn);
        std::cout << "Average Access By Column: " << timeByColumn 
                  << " Processing time for element: " << static_cast<double>(timeByColumn * 1000 / (m*n)) << "ns"
                  << std::endl;

        for (size_t i = 0; i < m; i++)
        {
            delete[] pArr[i];
        }
        delete[] pArr;
    }


    std::cout << "========== Matrix as vector ==========" << std::endl;
    for (auto& dimension : dimensions)
    {
        auto m = dimension.first;
        auto n = dimension.second;
        int* pArr = new int[m*n];

        std::function<void()> accessByRow = [&]()
        { 
            int summ = 0;
            for (size_t i = 0; i < m; i++)
            {
                for (size_t j = 0; j < n; j++)
                {
                    //summ += pArr[i*n + j];
                    summ +=  *(pArr + i*n + j);
                }
            }
        };

        std::function<void()> accessByColumn = [&]()
        { 
            int summ = 0;
            for (size_t i = 0; i < n; i++)
            {
                for (size_t j = 0; j < m; j++)
                {
                    //summ += pArr[j*n + i];
                    summ += *(pArr + j*n + i);
                }
            }
        };

        Experiment e;
        std::cout << "Matrix " << m << "x" << n << std::endl;

        auto timeByRow = e.run(accessByRow) ;
        std::cout << "Average Access By Row:    "
                  << timeByRow
                  << " Processing time for element: " << static_cast<double>(timeByRow * 1000 / (m*n)) << "ns"
                  << std::endl;

        auto timeByColumn = e.run(accessByColumn);
        std::cout << "Average Access By Column: " << timeByColumn 
                  << " Processing time for element: " << static_cast<double>(timeByColumn * 1000 / (m*n)) << "ns"
                  << std::endl;

        delete[] pArr;
    }
    */

    {
        // Access to data in vector
        const size_t dim = 64 * 1024 * 1024;
        int* pVector = new int[dim];

        std::function<void()> processAllData = [&]()
        {
            for (size_t i = 0; i < dim; i++) pVector[i] *= 3;
        };

        std::function<void()> processPartOfData = [&]()
        {
            for (size_t i = 0; i < dim; i += 16) pVector[i] *= 3;
        };

        Experiment e;
        std::cout << "========== Access to data in vector ==========" << std::endl;

        auto timeAllData = e.run(processAllData) ;
        std::cout << "Average processing all data:    "
                  << timeAllData
                  << std::endl;

        auto timePartOfData = e.run(processPartOfData);
        std::cout << "Average processing part of data (1/16): " << timePartOfData 
                  << std::endl;

        delete[] pVector;
    }

    return 0;
}
