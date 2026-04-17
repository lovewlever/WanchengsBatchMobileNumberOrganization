#ifndef TEXTFILELOADER_H
#define TEXTFILELOADER_H

#include <QFile>
#include <vector>
#include <string>
#include <CSVPhoneLocationLoader.h>

class TextFileLoader
{
public:
    TextFileLoader();
    ~TextFileLoader();

    bool openFile(const QString& filePath);

    std::vector<std::string> getPhonesByPage(const qint64 page);

    std::vector<PhoneListModel> loadAllPhones(std::shared_ptr<CSVPhoneLocationLoader> csvPhoneLocationLoaderPtr);

private:
    qint64 page{0};
    qint64 pageSize{10 * 1024 * 1024};
    QFile file;

};

#endif // TEXTFILELOADER_H
