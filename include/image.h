#ifndef IMAGE_H
#define IMAGE_H

#include <cstdint>
#include <cstddef>

/**
 * @brief 지원하는 이미지 파일 형식 목록
 */
enum ImageType {
    PNG,
    JPG,
    BMP,
    TGA
};

/**
 * @brief 이미지 데이터를 관리하는 구조체
 */
struct Image {
    uint8_t* data = nullptr; // 이미지 데이터 1byte
    size_t size = 0;         // 데이터의 크기 추적하기
    int w = 0;                // 이미지의 width
    int h = 0;                // 이미지의 height
    int channels = 0;         // 픽셀당 색상 값: RGB = 3, RGBA = 4

    /**
     * @brief 이미지 파일을 로드하여 객체를 생성합니다.
     * @param filename 읽어올 이미지 경로
     */
    Image(const char* filename);

    /**
     * @brief 지정된 크기와 채널로 빈 이미지 버퍼를 생성합니다.
     * @param w 가로 길이
     * @param h 세로 길이
     * @param channels 채널 수
     */
    Image(int w, int h, int channels);

    /**
     * @brief 다른 Image 객체를 깊은 복사(Deep Copy)하여 생성합니다.
     * @param img 복사할 대상의 Image 객체
     */
    Image(const Image& img);

    /**
     * @brief 객체 소멸 시 할당된 이미지 데이터 버퍼(data)를 해제합니다.
     */
    ~Image();

    /**
     * @brief 이미지 파일을 읽어와 메모리에 로드합니다.
     * @param filename 읽어올 이미지 파일 경로
     * @return 성공 시 true, 실패 시 false
     */
    bool read(const char* filename);

    /**
     * @brief 현재 메모리의 이미지 데이터를 파일로 저장합니다.
     * @param filename 저장할 이미지 파일 경로 및 이름
     * @return 저장 성공 시 true, 실패 시 false
     */
    bool write(const char* filename);

    /**
     * @brief 파일 확장자를 기반으로 ImageType을 추출합니다.
     * @param filename 이미지 파일 경로 또는 파일명
     * @return 판별된 ImageType 열거형 값 (PNG, JPG, BMP, TGA)
     */
    ImageType getFileType(const char* filename);

    /**
     * @brief 산술 평균 방식(Average Method)으로 이미지를 흑백(Grayscale)으로 변환합니다.
     *        (R + G + B) / 3
     * @return 변환된 자신 객체의 참조자 (Image&)
     */
    Image& grayscale_avg();

    /**
     * @brief 인간의 시각 인지 가중치 방식(Luminance/Luma Method)으로 이미지를 흑백(Grayscale)으로 변환합니다.
     *        (0.2126 * R + 0.7152 * G + 0.0722 * B)
     * @return 변환된 자신 객체의 참조자 (Image&)
     */
    Image& grayscale_lum();

    /**
     * @brief 각 채널 값에 지정된 비율을 곱해 색상 마스크를 적용합니다.
     * @param r Red 채널에 곱할 비율
     * @param g Green 채널에 곱할 비율
     * @param b Blue 채널에 곱할 비율
     * @return 변환된 자신 객체의 참조자 (Image&)
     */
    Image& colorMask(float r, float g, float b);

    /**
     * @brief (x, y) 좌표의 픽셀 값을 가져옵니다. 이미지 범위를 벗어나면 가장자리 픽셀 값으로 Clamp 처리합니다.
     * @param x 가로 좌표
     * @param y 세로 좌표
     * @param c 채널 인덱스 (기본값 0: Grayscale)
     * @return 픽셀 값 (0 ~ 255)
     */
    uint8_t getPixelClamped(int x, int y, int c = 0) const;
};

#endif // IMAGE_H