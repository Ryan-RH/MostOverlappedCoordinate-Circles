#include <iostream>
#include <vector>
#include <cmath>
#include <array>
//#include <chrono>

int main()
{
    // Circle Data
    double circleX[] = { 14.11450195, 14.14184093, 14.15435028, 14.16206741, 14.16951752,
        14.17171097, 14.18569565, 14.19700241, 14.23129082, 14.24083233,
        14.24290752, 14.24968338, 14.2518959, 14.26536751, 14.27209759,
        14.27612877, 14.2904377, 14.29187012, 14.29409599, 14.29618549,
        14.30615044, 14.31624985, 14.3206892, 14.3228569, 14.36143875,
        14.36351967, 14.36470699, 14.36697292, 14.37235737, 14.41422081,
        14.42583466, 14.43226814, 14.43319225, 14.4437027, 14.4557848,
        14.46592999, 14.47036076, 14.47452068, 14.47815609, 14.52229309,
        14.53059006, 14.53404236, 14.5411644 };
    double circleY[] = { -0.35319126,-0.44222349,-0.44763246,-0.35669261,-0.24366629,
     -0.3998799,-0.38940558,-0.57744932,-0.45223859,-0.21021004,
     -0.44250247,-0.45866323,-0.47203487,-0.51684451,-0.44884869,
     -0.2018993,-0.40296811,-0.23641759,-0.18019417,-0.33391538,
     -0.53565156,-0.45215255,-0.40939832,-0.26936951,-0.30894437,
     -0.55504167,-0.47177047,-0.45573688,-0.43100587,-0.5805912,
     -0.21770373,-0.199422,-0.17372169,-0.38522363,-0.56950212,
     -0.56947368,-0.48770753,-0.24940367,-0.31492445,-0.54263926,
     -0.53460872,-0.4053807,-0.43733299 };
    double radius = 0.014;

    //auto start = std::chrono::high_resolution_clock::now();

    int circleDataSize = sizeof(circleX) / sizeof(circleX[0]);
    std::vector<std::vector<std::array<int, 3>>> overlapTwo(circleDataSize);
    for (int i = 0; i < circleDataSize - 1; i++)
    {
        for (int j = i + 1; j < circleDataSize; j++)
        {
            double circleXDiff = std::abs(circleX[i] - circleX[j]);
            double circleYDiff = std::abs(circleY[i] - circleY[j]);
            double distanceBetween = std::sqrt(circleXDiff * circleXDiff + circleYDiff * circleYDiff);
            if (distanceBetween < 2 * radius)
            {
                std::array<int, 3> overlapCircle = { i,j, -1 };
                overlapTwo[i].push_back(overlapCircle);
            }
        }
    }

    for (int firstERow = 0; firstERow < overlapTwo.size(); firstERow++)
    {
        for (int indCaller = 0; indCaller < overlapTwo[firstERow].size(); indCaller++)
        {
            int rowToFind = overlapTwo[firstERow][indCaller][1];
            for (int indCallee = 0; indCallee < overlapTwo[rowToFind].size(); indCallee++)
            {
                for (int indCallback = 0; indCallback < overlapTwo[firstERow].size(); indCallback++)
                {
                    if (overlapTwo[rowToFind][indCallee][1] == overlapTwo[firstERow][indCallback][1])
                    {
                        overlapTwo[rowToFind][indCallee][2] = overlapTwo[firstERow][indCaller][0];
                        break;
                    }
                }
            }
        }
    }

    std::vector<int> mostOverlaps;
    for (int i = overlapTwo.size()-1; i >= 0; i--)
    {
        for (int j = overlapTwo[i].size()-1; j >= 0; j--)
        {
            std::vector<int> overlapsBuffer;
            overlapsBuffer.push_back(overlapTwo[i][j][0]);
            overlapsBuffer.push_back(overlapTwo[i][j][1]);
            int iTemp = i;
            int jTemp = j;
            while (overlapTwo[iTemp][jTemp][2] != -1)
            {
                int hop = overlapTwo[iTemp][jTemp][2];
                overlapsBuffer.push_back(hop);
                for (int k = 0; k < overlapTwo[hop].size(); k++)
                {
                    if (overlapTwo[hop][k][1] == overlapTwo[iTemp][jTemp][0])
                    {
                        jTemp = k;
                        break;
                    }
                }
                iTemp = hop;
            }
            if (overlapsBuffer.size() > mostOverlaps.size())
            {
                mostOverlaps = overlapsBuffer;
            }
        }
    }


    double xTotal = 0;
    double yTotal = 0;
    for (const auto& hop : mostOverlaps)
    {
        xTotal += circleX[hop];
        yTotal += circleY[hop];
    }
    double xCoord = xTotal / mostOverlaps.size();
    double yCoord = yTotal / mostOverlaps.size();

    //auto end = std::chrono::high_resolution_clock::now();

    std::cout << "(" << xCoord << ", " << yCoord << "): " << mostOverlaps.size() << "\n";
    //std::chrono::duration<double> duration = end - start;
    //std::cout << "Time taken: " << duration.count() << " seconds." << std::endl;

    return 0;
}