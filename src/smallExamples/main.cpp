#include <iostream>
#include <cstddef>
#include <time.h>
#include <functional>
#include <vector>

class Experiment
{
public:
    Experiment()
        : m_repetitions(50)
    {}

    typedef std::function<void()> fn_type;

    std::uint64_t run(fn_type& runFunction)
    {
        std::uint64_t retVal = 0;
        std::uint64_t measure = 0;

        for (int j = 0; j < m_repetitions; j++)
        {        
            measure = clock();

            for (int i = 0; i < m_repetitions; i++)
            {
                runFunction();
            }

            retVal += clock() - measure;
        }

        return retVal / m_repetitions;
    }
private:
    int m_repetitions;
};

// TODO: SIMD

int main()
{
    std::vector<std::pair<size_t, size_t>> dimensions = {{64, 4688}, {4688, 64}, {1000, 300}, {300, 1000}};

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
    //////////////////////////////////////
    /*
    std::cout << "Created matrix as 1 array" << std::endl;
    {
        int* pArr = new int[m*n];

        std::cout << "Accessing matrix by row" << std::endl;
        for (auto iteration = 0; iteration < 10; iteration++)
        {
            long t1 = clock();

            for (auto k = 0; k < repetitions; k++)
            {
                int summ = 0;
                //int* previousAddress = nullptr;
                for (size_t i = 0; i < m; i++)
                {
                    for (size_t j = 0; j < n; j++)
                    {
                        //summ += pArr[i*n + j];
                        summ +=  *(pArr + i*n + j);
                    }
                }

            }
            long t2 = clock();
            std::cout << "Time: " << t2 - t1 << std::endl;

        }

        std::cout << "Accessing matrix by column" << std::endl;
        for (auto iteration = 0; iteration < 10; iteration++)
        {
            long t1 = clock();

            for (auto k = 0; k < repetitions; k++)
            {
                int summ = 0;
                //int* previousAddress = nullptr;
                for (size_t i = 0; i < n; i++)
                {
                    for (size_t j = 0; j < m; j++)
                    {
                        //summ += pArr[j*n + i];
                        summ += *(pArr + j*n + i);
                    }
                }

            }
            long t2 = clock();
            std::cout << "Time: " << t2 - t1 << std::endl;
        }

        delete[] pArr;
    }
    */

    return 0;
}


/*
const size_t m = 1000;
const size_t n = 300;



Created matrix as array of arrays
Accessing matrix by row
Time: 646
Time: 641
Time: 636
Time: 638
Time: 637
Time: 637
Time: 638
Time: 643
Time: 636
Time: 636
Accessing matrix by column
Time: 773
Time: 769
Time: 774
Time: 769
Time: 768
Time: 774
Time: 772
Time: 772
Time: 771
Time: 768
Created matrix as 1 array
Accessing matrix by row
Time: 748
Time: 748
Time: 745
Time: 754
Time: 746
Time: 748
Time: 749
Time: 751
Time: 747
Time: 745
Accessing matrix by column
Time: 717
Time: 725
Time: 717
Time: 717
Time: 724
Time: 722
Time: 724
Time: 727
Time: 722
Time: 720
Press any key to continue . . .
*/

/*
const size_t m = 4688;      // To fit in L1
const size_t n = 64;        // To fit in L1


Created matrix as array of arrays
Accessing matrix by row
Time: 675
Time: 668
Time: 669
Time: 668
Time: 671
Time: 671
Time: 671
Time: 673
Time: 670
Time: 671
Accessing matrix by column
Time: 827
Time: 827
Time: 826
Time: 826
Time: 830
Time: 824
Time: 825
Time: 831
Time: 826
Time: 823
Created matrix as 1 array
Accessing matrix by row
Time: 780
Time: 780
Time: 777
Time: 776
Time: 778
Time: 777
Time: 778
Time: 777
Time: 781
Time: 778
Accessing matrix by column
Time: 762
Time: 765
Time: 763
Time: 767
Time: 764
Time: 765
Time: 765
Time: 765
Time: 764
Time: 765
Press any key to continue . . .
*/


/*
const size_t m = 64;          // To fit in L1
const size_t n = 4688;        // To fit in L1

Created matrix as array of arrays
Accessing matrix by row
Time: 654
Time: 651
Time: 649
Time: 653
Time: 648
Time: 648
Time: 651
Time: 650
Time: 650
Time: 650
Accessing matrix by column
Time: 732
Time: 737
Time: 740
Time: 731
Time: 738
Time: 730
Time: 731
Time: 735
Time: 732
Time: 735
Created matrix as 1 array
Accessing matrix by row
Time: 741
Time: 739
Time: 739
Time: 742
Time: 739
Time: 739
Time: 740
Time: 738
Time: 740
Time: 740
Accessing matrix by column
Time: 719
Time: 729
Time: 720
Time: 716
Time: 721
Time: 719
Time: 721
Time: 718
Time: 715
Time: 720
Press any key to continue . . .
*/