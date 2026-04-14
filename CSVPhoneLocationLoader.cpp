#include "CSVPhoneLocationLoader.h"
#include <QFile>
#include <QDebug>
#include <QString>

CSVPhoneLocationLoader::CSVPhoneLocationLoader() {}

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
    while(!file.atEnd()) {
        const auto line = file.readLine().trimmed();
        QString string{line};
        std::string prefix, province, city, carrier;
        QStringList stringList = string.split(",");
        prefix = stringList[2].toStdString();
        province = stringList[3].toStdString();
        city = stringList[4].toStdString();
        carrier = stringList[5].toStdString();

        phoneLocationDB[prefix] = { prefix, province, city, carrier};
    }

    qDebug() << "PhoneLocation数据：" << phoneLocationDB.size();

}
