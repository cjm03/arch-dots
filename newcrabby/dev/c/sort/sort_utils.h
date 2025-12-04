#ifndef SORT_UTILS_H
#define SORT_UTILS_H


const int sortedArr[] = {
    172, 358, 783, 1048, 1273, 1314, 1405, 1690, 1769, 1917,
    2254, 2440, 2474, 2825, 3129, 3239, 3335, 4099, 4171, 4302,
    4657, 4975, 5177, 5319, 5555, 5835, 6164, 6317, 6667, 7001,
    7024, 7060, 7284, 7294, 7534, 7592, 7593, 8188, 8346, 8368,
    8573, 9018, 9085, 9279, 9404, 9561, 9745, 9787, 9839, 9868
};

void swap(int* a, int* b);
void printverify(int arr[], const int sortedarr[], int n);
void printverifyVerbose(int arr[], const int sortedarr[], int n);

#endif // SORT_UTILS_H
