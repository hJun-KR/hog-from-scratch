#include "../include/logger.h"
#include "../include/image.h"

int main(int argc, char** argv) {
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

    return 0;
}