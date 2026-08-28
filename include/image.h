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
};

#endif // IMAGE_H