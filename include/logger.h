#ifndef LOGGER_H
#define LOGGER_H

/**
 * @brief 로그의 출력 레벨을 정의합니다.
 */
enum class LogLevel {
    INFO,
    ERROR,
    DEBUG
};

/**
 * @brief 로그를 출력합니다.
 * @param level 로그 레벨
 * @param log_file 로그가 발생한 파일 또는 모듈 이름
 * @param format 출력할 로그 형식
 */
void log(LogLevel level, const char* log_file, const char* format, ...);

/**
 * @brief INFO 레벨의 로그를 출력합니다.
 * @param log_file 로그가 발생한 파일 또는 모듈 이름
 * @param format 출력할 로그 형식
 */
void log_info(const char* log_file, const char* format, ...);

/**
 * @brief ERROR 레벨의 로그를 출력합니다.
 * @param log_file 로그가 발생한 파일 또는 모듈 이름
 * @param format 출력할 로그 형식
 */
void log_error(const char* log_file, const char* format, ...);

/**
 * @brief DEBUG 레벨의 로그를 출력합니다.
 * @param log_file 로그가 발생한 파일 또는 모듈 이름
 * @param format 출력할 로그 형식
 */
void log_debug(const char* log_file, const char* format, ...);

#endif // LOGGER_H