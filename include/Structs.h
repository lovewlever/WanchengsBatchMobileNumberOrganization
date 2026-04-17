#ifndef STRUCTS_H
#define STRUCTS_H
#include <string>
#include <memory>

struct PhonLocationInfo {
    uint32_t prefix;
    std::string province;
    std::string city;
    std::string carrier;


    // 默认构造函数
    PhonLocationInfo() = default;

    // 带参数的构造函数
    PhonLocationInfo(uint32_t p, const std::string& prov,
                     const std::string& c, const std::string& car)
        : prefix(p), province(prov), city(c), carrier(car) {}

    // 移动语义版本（更高效）
    PhonLocationInfo(uint32_t p, std::string&& prov,
                     std::string&& c, std::string&& car)
        : prefix(p), province(std::move(prov)),
        city(std::move(c)), carrier(std::move(car)) {}
};


struct FileLoaderBlock {
    int64_t start{0};
    int64_t end{0};
};


struct PhoneListModel {
    std::shared_ptr<PhonLocationInfo> locationInfo{nullptr};
    uint32_t prefixPhone{0};
    std::string phone{""};
};

#endif // STRUCTS_H
