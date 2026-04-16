#include "CSVPhoneLocationLoader.h"
#include <QFile>
#include <QDebug>
#include <QString>

CSVPhoneLocationLoader::CSVPhoneLocationLoader(): phoneLocationDB{std::make_unique<std::vector<std::shared_ptr<PhonLocationInfo>>>(MAX_PREFIX - MIN_PREFIX + 1)} {}

CSVPhoneLocationLoader::~CSVPhoneLocationLoader()
{
    qDebug() << "~CSVPhoneLocationLoader";
}

void CSVPhoneLocationLoader::loadPhoneLocationCSV()
{
    QFile file{":/phone_location.csv"};
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qFatal() << "PhoneLocation加载失败！！";
        return;
    }
    phoneLocationDB->reserve(MAX_PREFIX - MIN_PREFIX + 1);
    while(!file.atEnd()) {
        const auto line = file.readLine().trimmed();
        QString string{line};
        uint32_t prefix{0};
        std::string province, city, carrier;
        QStringList stringList = string.split(",");
        bool isOk{false};
        uint32_t uuuiint = stringList[2].trimmed().replace('\'', "").toUInt(&isOk);
        if (isOk) {
            prefix = uuuiint;
        }
        province = stringList[3].trimmed().replace('\'', "").toStdString();
        city = stringList[4].trimmed().replace('\'', "").toStdString();
        carrier = stringList[5].trimmed().replace('\'', "").toStdString();
        if (prefix <= 0) continue;
        if (prefix >= 10000000) {
            prefix = prefix / 10;  // 去掉最后一位
        }
        while(prefix < MIN_PREFIX) {
            prefix = prefix * 10;
        }
        if (prefix > 0) {
            (*phoneLocationDB)[prefix - MIN_PREFIX] = std::make_shared<PhonLocationInfo>(prefix, province, city, carrier);
        }
    }

    qDebug() << "PhoneLocation数据：" << phoneLocationDB->size();

}

const std::shared_ptr<PhonLocationInfo> CSVPhoneLocationLoader::getByPrefixPhone(int32_t prefixPhone)
{
    try {
         return (*phoneLocationDB).at(prefixPhone - MIN_PREFIX);
    } catch (const std::out_of_range& e) {
        return nullptr;
    }

}

// const std::vector<PhonLocationInfo> &CSVPhoneLocationLoader::getPhoneLocationDB()
// {
//     return phoneLocationDB;
// }
