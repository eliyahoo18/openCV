#include "mission1.h"



uchar keepItUCharValue(double sum) {
    return  (uchar) keepBetween(sum, 255, 0);
}

double keepBetween(double sum, int max, int min) {
    return sum > 255 ? 255 : sum < 0 ? 0 : sum;
}

std::vector<cv::Vec3b*> cellNeighborAsArray(cv::Mat &mat, int row, int col) {
    std::vector<cv::Vec3b*> cells = {
            &mat.at<cv::Vec3b>(row - 1, col - 1), &mat.at<cv::Vec3b>(row - 1, col), &mat.at<cv::Vec3b>(row, col - 1),
            &mat.at<cv::Vec3b>(row, col - 1),     &mat.at<cv::Vec3b>(row, col),     &mat.at<cv::Vec3b>(row - 1, col),
            &mat.at<cv::Vec3b>(row + 1, col - 1), &mat.at<cv::Vec3b>(row, col - 1), &mat.at<cv::Vec3b>(row - 1, col - 1),
    };
    return cells;
}

void turnToGrayByAverage(cv::Mat& mat) {

    for (int row = 0; row < mat.rows; row++) {
        for (int col = 0; col < mat.cols; col++) {
            cv::Vec3b& vec = mat.at<cv::Vec3b>(row, col);

            int average = (vec[RED] + vec[GREEN] + vec[BLUE]) / 3;
            vec[RED] = vec[GREEN] = vec[BLUE] = average;
        }
    }
}

cv::Mat sharpness(cv::Mat& mat) {
    cv::Mat newMat = mat.clone();
    double mask[3][3] = {
            {1,1,1},
            {0,0,0},
            {-1,-1,-1},
    };

    for (int row = 1; row < mat.rows - 1; row++) {
        for (int col = 1; col < mat.cols - 1; col++) {
            masking(mat, newMat, row, col, (double*) mask, RED);
            masking(mat, newMat, row, col, (double*) mask, GREEN);
            masking(mat, newMat, row, col, (double*) mask, BLUE);
        }
    }

    return newMat;
}

void masking(cv::Mat &mat, cv::Mat& newMat, int row, int col, double* mask, int color) {
    cv::Vec3b &destVec = newMat.at<cv::Vec3b>(row, col);
    std::vector<cv::Vec3b*> cells = cellNeighborAsArray(mat, row, col);

    double sum = 0;
    for (int i = 0; i < 3 * 3; i++)
        sum += mask[i] * (*cells[i])[color];

    destVec[color] = keepItUCharValue(sum);
}

cv::Mat blending(const cv::Mat &mat1, const cv::Mat &mat2, float alpha) {
    cv::Mat dest = mat1.clone();

    for (int row = 0; row < mat1.rows; row++) {
        for (int col = 0; col < mat1.cols; col++) {
            if (row >= mat2.rows || col >= mat2.cols)
                continue;

            cv::Vec3b px1 = mat1.at<cv::Vec3b>(row, col);
            cv::Vec3b px2 = mat2.at<cv::Vec3b>(row, col);

            dest.at<cv::Vec3b>(row, col) = calcBlending(px1, px2, alpha);
        }
    }

    return dest;
}

cv::Vec3b calcBlending(cv::Vec3b& px1, cv::Vec3b& px2, float alpha) {
    cv::Vec3b px;
    for (int i = 0; i < 3; i++)
        px[i] = calcBlendingForColor(px1[i], px2[i], alpha);

    return px;
}

uchar calcBlendingForColor(uchar& px1, uchar& px2, float alpha) {
    return keepItUCharValue(alpha * (double) px1 + (1 - alpha) * (double) px2);
}

cv::Mat gaussian(const cv::Mat &mat) {
    cv::Mat dest(mat.rows / 2, mat.cols / 2, mat.type());

    for (int row = 0, destRow = 0; row < mat.rows; row += 2, destRow++) {
        for (int col = 0, destCol = 0; col < mat.cols; col += 2, destCol++) {
            cv::Vec3b& px = dest.at<cv::Vec3b>(destRow, destCol);

            px = calcAveraveOfPixels(mat.at<cv::Vec3b>(row, col),
                                     mat.at<cv::Vec3b>(row + 1, col),
                                     mat.at<cv::Vec3b>(row, col + 1),
                                     mat.at<cv::Vec3b>(row + 1, col + 1));
        }
    }

    return dest;
}

cv::Vec3b calcAveraveOfPixels(const cv::Vec3b &px1, const cv::Vec3b &px2, const cv::Vec3b &px3, const cv::Vec3b &px4) {
    cv::Vec3b px;
    for (int i = 0; i < 3; i++)
        px[i] = (px1[i] + px2[i] + px3[i] + px4[i]) / 4;

    return px;
}

cv::Mat gaussian2(const cv::Mat &mat) {
    cv::Mat dest(mat.rows * 2, mat.cols * 2, mat.type());

    for (int row = 0, destRow = 0; row < dest.rows; row += 2, destRow++) {
        for (int col = 0, destCol = 0; col < dest.cols; col += 2, destCol++) {
            cv::Vec3b px = mat.at<cv::Vec3b>(destRow, destCol);

            dest.at<cv::Vec3b>(row, col) = px;
            dest.at<cv::Vec3b>(row + 1, col) = px;
            dest.at<cv::Vec3b>(row, col + 1) = px;
            dest.at<cv::Vec3b>(row + 1, col + 1) = px;
        }
    }

    return dest;
}

