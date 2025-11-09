#include <iostream>
#include <limits.h>
#include <cfloat>
using namespace std;

double function(double x1, double x2)
{
    double first = x2 - (x1 * x1);
    double second = (1 - x1) * (1 - x1);
    double third = first * first;
    double answer = (100 * third) + second;
    return answer;
}

int pgb_index(double fitness[])
{
    float min = INT_MAX;
    int index = -1;
    for (int i = 0; i < 8; i++)
    {
        if (fitness[i] < min)
        {
            min = fitness[i];
            index = i;
        }
    }
    return index;
}

int main()
{
    float lower_limit = -5.0;
    float upper_limit = 5.0;
    float gbest = 14.222;
    float c1 = 1.5;
    float c2 = 2.0;
    float w = 0.75;

    double data[8][4] = {
        {2.212, 3.009, 0.0, 0.0},
        {-2.289, -2.396, 0.0, 0.0},
        {-2.393, -4.790, 0.0, 0.0},
        {-0.639, 1.692, 0.0, 0.0},
        {-3.168, 0.706, 0.0, 0.0},
        {0.215, -2.350, 0.0, 0.0},
        {-0.742, 1.934, 0.0, 0.0},
        {-4.563, 4.791, 0.0, 0.0}

    };

    double fitness[8] = {DBL_MAX, DBL_MAX, DBL_MAX, DBL_MAX, DBL_MAX, DBL_MAX, DBL_MAX, DBL_MAX};
    double local_best[8][2];

    for (int i = 0; i < 8; i++)
    {
        local_best[i][0] = data[i][0];
        local_best[i][1] = data[i][1];
    }

    float r1[8] = {0.661, 0.919, 0.782, 0.299, 0.874, 0.133, 0.031, 0.366};
    float r2[8] = {0.312, 0.271, 0.824, 0.055, 0.595, 0.582, 0.736, 0.954};

    while (gbest >= 14.222)
    {

        // fitness calculation and local_best updation
        for (int i = 0; i < 8; i++)
        {
            double last = fitness[i];
            double current = function(data[i][0], data[i][1]);
            if (current < last)
            {
                fitness[i] = current;
                local_best[i][0] = data[i][0];
                local_best[i][1] = data[i][1];
            }
            if (fitness[i] < gbest)
            {
                gbest = fitness[i];
            }
        }

        // velocity updation
        cout << "Printing Particle Velocity" << endl;
        cout << "------------------------------------------------------------------------------------------------------------------------------";
        cout << endl;

        for (int i = 0; i < 8; i++)
        {
            int g_index = pgb_index(fitness);

            data[i][2] = w * data[i][2] + c1 * r1[i] * (local_best[i][0] - data[i][0]) + c2 * r2[i] * (data[g_index][0] - data[i][0]);
            data[i][3] = w * data[i][3] + c1 * r1[i] * (local_best[i][1] - data[i][1]) + c2 * r2[i] * (data[g_index][1] - data[i][1]);

            cout << data[i][2] << " " << data[i][3] << endl;
        }

        // updating particle position

        cout << "Printing Particles : " << endl;
        cout << "------------------------------------------------------------------------------------------------------------------------------";
        cout << endl;

        for (int i = 0; i < 8; i++)
        {

            data[i][0] = data[i][0] + data[i][2];

            if (data[i][0] < lower_limit)
            {
                data[i][0] = -5.0;
            }
            else if (data[i][0] > upper_limit)
            {
                data[i][0] = 5.0;
            }

            data[i][1] = data[i][1] + data[i][3];

            if (data[i][1] < lower_limit)
            {
                data[i][1] = -5.0;
            }
            else if (data[i][1] > upper_limit)
            {
                data[i][1] = 5.0;
            }

            cout << data[i][0] << " " << data[i][1] << endl;
        }

        cout << "Printing Final Fitness :" << endl;
        cout << "------------------------------------------------------------------------------------------------------------------------------";
        cout << endl;
        for (int i = 0; i < 8; i++)
        {
            cout << fitness[i] << " " << endl;
        }
    }
    cout << "------------------------------------------------------------------------------------------------------------------------------";
    cout << endl;

    return 0;
}