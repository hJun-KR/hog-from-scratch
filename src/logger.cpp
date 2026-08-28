#include <cstdarg>
#include <cstdio>

#include "logger.h"

/**
 * @brief 로그 레벨을 문자열로 변환합니다.
 * @param level 변환할 로그 레벨
 * @return 로그 레벨 문자열
 */
static const char* log_level_to_string(LogLevel level)
{
    switch (level) {
        case LogLevel::INFO:
            return "INFO";

        case LogLevel::ERROR:
            return "ERROR";

        case LogLevel::DEBUG:
            return "DEBUG";

        default:
            return "UNKNOWN";
    }
}

/**
 * @brief 로그를 출력합니다.
 * @param level 로그 레벨
 * @param log_file 로그가 발생한 파일 또는 모듈 이름
 * @param format 출력할 로그 형식
 */
void log(LogLevel level, const char* log_file, const char* format, ...)
{
    printf(
        "[%s][%s] ",
        log_level_to_string(level),
        log_file
    );

    va_list args;
    va_start(args, format);

    vprintf(format, args);

    va_end(args);
}

/**
 * @brief INFO 레벨의 로그를 출력합니다.
 * @param log_file 로그가 발생한 파일 또는 모듈 이름
 * @param format 출력할 로그 형식
 */
void log_info(const char* log_file, const char* format, ...)
{
    printf("[INFO][%s] ", log_file);

    va_list args;
    va_start(args, format);

    vprintf(format, args);

    va_end(args);
}

/**
 * @brief ERROR 레벨의 로그를 출력합니다.
 * @param log_file 로그가 발생한 파일 또는 모듈 이름
 * @param format 출력할 로그 형식
 */
void log_error(const char* log_file, const char* format, ...)
{
    printf("[ERROR][%s] ", log_file);

    va_list args;
    va_start(args, format);

    vprintf(format, args);

    va_end(args);
}

/**
 * @brief DEBUG 레벨의 로그를 출력합니다.
 * @param log_file 로그가 발생한 파일 또는 모듈 이름
 * @param format 출력할 로그 형식
 */
void log_debug(const char* log_file, const char* format, ...)
{
    printf("[DEBUG][%s] ", log_file);

    va_list args;
    va_start(args, format);

    vprintf(format, args);

    va_end(args);
}