#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include <cstring>
#include "../include/logger.h"
#include "../include/image.h"
#include "../include/stb_image.h"
#include "../include/stb_image_write.h"

/**
 * @brief 파일 경로를 받아 이미지 객체를 생성하고 파일을 로드합니다.
 * @param filename 로드할 이미지 파일 경로
 */
Image::Image(const char* filename) {
    log_debug("IMAGE", "파일 로드 생성자 호출: %s\n", filename);
    if (read(filename)) {
        log_info("IMAGE", "FILE을 정상적으로 읽었습니다 : %s\n", filename);
    } else {
        log_error("IMAGE", "FILE을 읽거나 찾을 수 없습니다 : %s\n", filename);
    }
}

/**
 * @brief 지정된 가로, 세로, 채널 크기로 빈 이미지 버퍼 메모리를 동적 할당합니다.
 * @param w 이미지 가로 너비
 * @param h 이미지 세로 높이
 * @param channels 이미지 채널 수
 */
Image::Image(int w, int h, int channels) : w(w), h(h), channels(channels) {
    size = static_cast<size_t>(w) * h * channels;
    log_debug("IMAGE", "빈 이미지 버퍼 생성자 호출 [w: %d, h: %d, channels: %d, size: %zu bytes]\n", w, h, channels, size);
    
    if (size > 0) {
        data = new uint8_t[size];
    } else {
        data = nullptr;
        log_error("IMAGE", "유효하지 않은 이미지 크기입니다 (size=0).\n");
    }
}

/**
 * @brief 복사 생성자 (깊은 복사 수행)
 * @param img 복사할 대상 Image 객체
 */
Image::Image(const Image& img) : Image(img.w, img.h, img.channels) {
    log_debug("IMAGE", "복사 생성자 호출 (Deep Copy 수행중...)\n");
    if (img.data && size > 0) {
        std::memcpy(data, img.data, size);
        log_debug("IMAGE", "이미지 데이터 메모리 복사 완료 (%zu bytes)\n", size);
    } else {
        log_error("IMAGE", "복사할 원본 이미지 데이터가 유효하지 않습니다.\n");
    }
}

/**
 * @brief 소멸자 (동적 할당된 이미지 픽셀 데이터 버퍼 해제)
 */
Image::~Image() {
    if (data != nullptr) {
        log_debug("IMAGE", "소멸자 호출: 이미지 메모리 버퍼 해제중...\n");
        stbi_image_free(data); 
        data = nullptr;
    }
}

/**
 * @brief stb_image 라이브러리를 사용하여 이미지 파일을 메모리로 읽어옵니다.
 * @param filename 로드할 이미지 파일 경로
 * @return 성공 시 true, 실패 시 false
 */
bool Image::read(const char* filename) {
    log_debug("IMAGE", "stbi_load() 실행 중: %s\n", filename);
    data = stbi_load(filename, &w, &h, &channels, 0);
    if (data != nullptr) {
        size = static_cast<size_t>(w) * h * channels; // 로드 성공 시 전체 데이터 크기 갱신
        log_debug("IMAGE", "이미지 디코딩 성공 [w: %d, h: %d, channels: %d, size: %zu bytes]\n", w, h, channels, size);
        return true;
    }
    return false;
}

/**
 * @brief 파일 확장자에 맞춰 이미지 데이터를 지정된 파일 형식으로 저장합니다.
 * @param filename 저장할 이미지 파일 경로 및 이름
 * @return 저장 성공 시 true, 실패 시 false
 */
bool Image::write(const char* filename) {
    if (data == nullptr || size == 0) {
        log_error("IMAGE", "저장할 이미지 데이터가 없습니다.\n");
        return false;
    }

    ImageType type = getFileType(filename);
    int success = 0;

    log_debug("IMAGE", "이미지 파일 저장 시도: %s (TypeEnum: %d)\n", filename, type);

    switch (type)
    {
    case PNG:
        // PNG 저장 (stride: 이미지 한 줄의 바이트 크기 = w * channels)
        success = stbi_write_png(filename, w, h, channels, data, w * channels);
        break;
    case JPG:
        // JPG 저장 (압축 품질: 100)
        success = stbi_write_jpg(filename, w, h, channels, data, 100);
        break;
    case BMP:
        success = stbi_write_bmp(filename, w, h, channels, data);
        break;
    case TGA:
        success = stbi_write_tga(filename, w, h, channels, data);
        break;
    }

    if (success != 0) {
        log_info("IMAGE", "FILE을 정상적으로 저장했습니다 : %s\n", filename);
        return true;
    } else {
        log_error("IMAGE", "FILE 저장 실패 : %s\n", filename);
        return false;
    }
}

/**
 * @brief 파일 경로명 문자열에서 확장자를 추출하여 ImageType enum을 반환합니다.
 * @param filename 판별할 이미지 파일 경로
 * @return 추출된 ImageType (기본값: PNG)
 */
ImageType Image::getFileType(const char* filename) {
    const char* ext = strrchr(filename, '.');
    if (ext != nullptr) {
        if (strcmp(ext, ".png") == 0 || strcmp(ext, ".PNG") == 0) {
            return PNG;
        } else if (strcmp(ext, ".jpg") == 0 || strcmp(ext, ".JPG") == 0 || strcmp(ext, ".jpeg") == 0) {
            return JPG;
        } else if (strcmp(ext, ".bmp") == 0 || strcmp(ext, ".BMP") == 0) {
            return BMP;
        } else if (strcmp(ext, ".tga") == 0 || strcmp(ext, ".TGA") == 0) {
            return TGA;
        }
    }
    log_debug("IMAGE", "확장자를 찾을 수 없어 기본 포맷(PNG)으로 지정합니다.\n");
    return PNG;
}