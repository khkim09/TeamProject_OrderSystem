/*

Time 구조체 관련 함수

*/
#include "Time.h"

Time::Time() {
    sec = 0;
    min = 0;
    hour = 0;
    day = 0;
    month = 0;
    year = 0;
}

//현재 날짜, 시간을 계산해주는 함수
//https://dev-astra.tistory.com/182
void Time::setTime() {
    time_t timer = time(NULL);
    struct tm t;
    localtime_s(&t, &timer);

    sec = t.tm_sec;
    min = t.tm_min;
    hour = t.tm_hour;
    day = t.tm_mday;
    month = t.tm_mon + 1;
    year = t.tm_year + 1900;
}

// Time을 출력하는 함수
void Time::printTime() const {
    std::cout << year << "." << month << "." << day << ". " << hour << ":" << min << ":" << sec;
}

void Time::loadFromFile(ifstream& file) {
	file >> sec >> min >> hour >> day >> month >> year;
}

void Time::saveToFile(ofstream& file) const {
	file << sec << " " << min << " " << hour << " "
		<< day << " " << month << " " << year << " ";
}