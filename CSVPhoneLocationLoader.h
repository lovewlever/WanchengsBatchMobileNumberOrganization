#ifndef CSVPHONELOCATIONLOADER_H
#define CSVPHONELOCATIONLOADER_H

#include <unordered_map>
#include <Structs.h>

class CSVPhoneLocationLoader
{
public:
    CSVPhoneLocationLoader();
    ~CSVPhoneLocationLoader();


    void loadPhoneLocationCSV();


private:
    std::unordered_map<std::string, PhonLocationInfo> phoneLocationDB{};
};

#endif // CSVPHONELOCATIONLOADER_H
