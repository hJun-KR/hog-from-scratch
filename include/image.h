#ifndef IMAGE_H
#define IMAGE_H

#include <cstdint>
#include <cstddef>

/**
 * @brief 이미지 데이터를 관리하는 구조체
 */

struct Image {
    uint8_t* data = nullptr; // 이미지 데이터 1byte
    size_t size = 0; // 데이터의 크기 추적하기
    int w = 0; // 이미지의 width
    int h = 0; // 이미지의 height
    int channels = 0; // 픽셀당 색상 값: RGB = 3, GPA 4
};

#endif // IMAGE_H