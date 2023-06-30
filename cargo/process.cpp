#include <iostream>
#include <cmath>

// 定义图像大小
const int ROWS = 1856;
const int COLS = 800;

// 大津法二值化函数
void otsuBinarization(unsigned char* array, int rows, int cols) {
    // 统计像素灰度值的直方图
    int histogram[256] = {0};
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            unsigned char grayValue = *(array + i * cols + j);
            histogram[grayValue]++;
        }
    }

    // 计算总像素数
    int totalPixels = ROWS * COLS;

    // 计算类间方差
    float maxVariance = 0.0;
    int threshold = 0;
    int sumB = 0;
    int sumF = 0;
    int countB = 0;
    int countF = 0;

    for (int i = 0; i < 256; i++) {
        countB += histogram[i];
        if (countB == 0)
            continue;

        countF = totalPixels - countB;
        if (countF == 0)
            break;

        sumB += i * histogram[i];
        float meanB = sumB / countB;
        float meanF = (totalPixels * i - sumB) / countF;

        float variance = countB * countF * std::pow(meanB - meanF, 2);
        if (variance > maxVariance) {
            maxVariance = variance;
            threshold = i;
        }
    }

    // 对图像进行二值化
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (*(array + i * cols + j) >= threshold) {
                // 黄色变成白色
                *(array + i * cols + j) = 255;
            } else {
                // 其余变成黑色
                *(array + i * cols + j) = 0;
            }
        }
    }
}

