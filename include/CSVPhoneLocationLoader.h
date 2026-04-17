#ifndef CSVPHONELOCATIONLOADER_H
#define CSVPHONELOCATIONLOADER_H

#include <Structs.h>
#include <vector>
#include <memory>

class CSVPhoneLocationLoader
{
public:
    CSVPhoneLocationLoader();
    ~CSVPhoneLocationLoader();

    void loadPhoneLocationCSV();

    const std::shared_ptr<PhonLocationInfo>  getByPrefixPhone(int32_t prefixPhone);

    // const std::vector<PhonLocationInfo>& getPhoneLocationDB();
private:
    const uint32_t MIN_PREFIX = 1300000;
    const uint32_t MAX_PREFIX = 1999999;
    std::unique_ptr<std::vector<std::shared_ptr<PhonLocationInfo>>> phoneLocationDB{nullptr};
};

#endif // CSVPHONELOCATIONLOADER_H
