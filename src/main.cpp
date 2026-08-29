#include "../include/logger.h"
#include "../include/image.h"

int main(int argc, char** argv) {
    /** 
     * 이미지 조회, 한줄 픽셀 바꾸기, 복사, 이미지 생성
    log_debug("MAIN", "main 함수 실행");
    Image test("test.jpg");
    test.write("new.png");

    Image copy = test;
    for (int i = 0; i < copy.w * copy.channels; ++i) {
        copy.data[i] = 255;
    }
    copy.write("copy.png");

    Image blank(100, 100, 3);
    blank.write("blank.jpg");
    */

    /**
     * 이미지 그레이 스케일화(avg: 산술 평균 방식, lum: 인간의 시각 인지 가중치 방식)
    Image test("test1.jpg");

    Image gray_avg = test;
    gray_avg.grayscale_avg();
    gray_avg.write("gray_avg.png");

    Image gray_lum = test;
    gray_lum.grayscale_lum();
    gray_lum.write("gray_lum.png");
    */

    Image test("test.jpg");
    test.colorMask(0, 0, 1);
    test.write("blue.png");



    return 0;
}