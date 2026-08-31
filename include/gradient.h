#ifndef GRADIENT_H
#define GRADIENT_H

#include <cstdint>
#include <cstddef>

#include "image.h"

/**
 * @brief 이미지의 그래디언트(크기 및 방향)를 계산하고 관리하는 클래스
 */
struct Gradient {
    int w = 0;
    int h = 0;
    float* magnitude = nullptr; // 그래디언트 크기 (Magnitude: sqrt(Gx^2 + Gy^2))
    float* orientation = nullptr; // 그래디언트 방향 (Orientation: arctan(Gy / Gx), degree 또는 radian)

    /**
     * @brief 지정된 크기로 버퍼를 생성하는 생성자
     * @param w 가로 크기
     * @param h 세로 크기
     */
    Gradient(int w, int h);

    /**
     * @brief 복사 생성자 (깊은 복사)
     * @param other 복사할 Gradient 객체
     */
    Gradient(const Gradient& other);

    /**
     * @brief 소멸자 (동적 할당 메모리 해제)
     */
    ~Gradient();

    /**
     * @brief 입력 이미지로부터 X, Y 방향 그래디언트를 계산하여 magnitude와 orientation을 구합니다.
     * @param img 그래디언트를 계산할 대상 Image 객체 (보통 Grayscale 이미지)
     * @return 계산 성공 여부
     */
    bool computeGradient(const Image& img);
    
    /**
     * @brief 특정 (x, y) 좌표의 그래디언트 크기(Magnitude)를 반환합니다.
     * @param x 가로 좌표
     * @param y 세로 좌표
     * @return 그래디언트 크기 값 (유효하지 않은 좌표일 경우 0.0f)
     */
    float getMagnitude(int x, int y) const;

    /**
     * @brief 특정 (x, y) 좌표의 그래디언트 방향(Orientation)을 반환합니다.
     * @param x 가로 좌표
     * @param y 세로 좌표
     * @return 그래디언트 방향 값 (도/Degree 또는 라디안/Radian)
     */
    float getOrientation(int x, int y) const;

};

#endif