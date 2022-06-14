#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <memory.h>

using namespace std;
typedef int element;
int  adaptiveProcess(vector<vector<element>> im, int row, int col, int kernelSize, int maxSize);
vector<vector<element>> work(vector<vector<element>> src);
int main()
{
    cout << "Hello World!" << endl;
    vector<vector<int>> vect
            {
                {1, 2, 3, 100, 210, 40, 50},
                {4, 5, 6, 110, 230, 30, 55},
                {7, 8, 9, 140, 210, 20, 52},
                {4, 27, 36, 160, 20, 60, 50},
                {5, 58, 65, 10, 240, 70, 75},
                {7, 89, 94, 40, 220, 80, 82}
            };

    vect = work(vect);
    cout << "Filas:"<<vect.size()<<"; Columnas:"<<vect[0].size() << endl;

    return 0;
}

//   MEDIAN calculation
//     elements - input elements
//     N        - number of input elements



int  adaptiveProcess(vector<vector<element>> im, int row, int col, int kernelSize, int maxSize)
{
    vector <int> pixels;
    for(int a = -kernelSize / 2; a <= kernelSize / 2; a++){
        for(int b = -kernelSize / 2; b <= kernelSize / 2; b++){
            pixels.push_back(im[row + a][col + b]);
        }
    }
    sort(pixels.begin(), pixels.end());
    auto min = pixels[0];
    auto max = pixels[kernelSize * kernelSize - 1];
    auto med = pixels[kernelSize * kernelSize / 2];
    element zxy = im[row][col];
    if(med > min && med < max){
        if(zxy > min && zxy < max){
            return zxy;
        }else{
            return med;
        }
    }
    else{
        kernelSize += 2;
        if(kernelSize <= maxSize)
            return adaptiveProcess(im, row, col, kernelSize, maxSize);
        else
            return med;
    }
}

vector<vector<element>> work(vector<vector<element>> src){
    vector<vector<element>> dst = src;
    int minSize = 3;
    int maxSize = 7;
    //copyMakeBorder(src, dst, maxSize / 2, maxSize / 2, maxSize / 2, maxSize / 2, BORDER_REFLECT);
    int rows = dst.size();
    int cols = dst[0].size();
    for(int j = maxSize / 2; j < rows - maxSize / 2; j++){
        for(int i = maxSize / 2; i < cols * 1 - maxSize / 2; i++){
            dst[i][j] = adaptiveProcess(dst, j, i, minSize, maxSize);
        }
    }
    return dst;
}

