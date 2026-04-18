#include "TextFileLoader.h"
#include <QDebug>
#include <QtMath>
#include <QRegularExpression>
#include <sstream>
#include <math.h>
#include <thread>
#include <Structs.h>
#include <CSVPhoneLocationLoader.h>

TextFileLoader::TextFileLoader() {

}

TextFileLoader::~TextFileLoader()
{
    if (file.isOpen()) {
        file.close();
    }
}

std::vector<std::string> TextFileLoader::getPhonesByPage(const qint64 page)
{
    std::vector<std::string> stringList{};
    if (file.isOpen()) {
        const auto realPageSize = file.size(); //qMin(file.size(), pageSize);
        stringList.reserve(realPageSize);
        uchar * mapAddressPtr = file.map(page * pageSize, realPageSize);
        if (mapAddressPtr == nullptr) {
            qFatal() << "内存映射失败！";
            return {};
        }
        std::string package{reinterpret_cast<const char*>(mapAddressPtr), static_cast<uint64_t>(realPageSize)};
        std::istringstream iss{package};
        std::string line{};
        while(std::getline(iss, line, '\n')) {
            stringList.emplace_back(line);
        }
        file.unmap(mapAddressPtr);
        qDebug() << "映射的数据：" << realPageSize;
    }

    return stringList;
}

std::vector<PhoneListModel> TextFileLoader::loadAllPhones(std::shared_ptr<CSVPhoneLocationLoader> csvPhoneLocationLoaderPtr)
{
    std::vector<PhoneListModel> phonesLists{};

    if (file.isOpen()) {
        const auto mmap = file.map(0, file.size());
        const char* data = reinterpret_cast<const char*>(mmap);
        const auto size = file.size();
        int threads = std::thread::hardware_concurrency();
        threads = std::max(1, threads);
        int64_t blockSize = size / threads;

        std::vector<std::thread> threadList{};

        std::vector<FileLoaderBlock> threadBlock{};
        // 分块
        int64_t nextStartLen{0};
        for (int i = 0; i < threads; ++i) {
            int64_t start = nextStartLen;
            int64_t end = start + blockSize;
            if (end >= size) {
                threadBlock.emplace_back(FileLoaderBlock{start, end});
                break;
            }
            while(end < size && data[end] != '\n') {
                end ++;
            }
            threadBlock.emplace_back(FileLoaderBlock{start, end});
            nextStartLen = end + 1;
        }

        std::vector<std::vector<PhoneListModel>> threadInsidePhoneList(threadBlock.size());

        for (int i = 0; i < threadBlock.size(); ++i) {
            const auto blockIndex = threadBlock[i];
            int idx = i;
            threadList.emplace_back(std::thread{[=, &threadInsidePhoneList] () {
                std::vector<PhoneListModel> phones{};
                phones.reserve((blockIndex.end - blockIndex.start) / 12);
                int64_t lineStart = blockIndex.start;
                for (int64_t pos = blockIndex.start; pos < blockIndex.end; ++pos) {
                    if (data[pos] == '\n') {
                        int64_t len = pos - lineStart;
                        if (len > 0 && data[pos - 1] == '\r') {
                            --len;
                        }
                        int64_t slen = lineStart;
                        if (lineStart < blockIndex.end - 1 && data[lineStart] == '\r') {
                            ++slen;
                        }

                        phones.emplace_back();
                        auto& phoneModel = phones.back();

                        std::string phone{data + slen,  static_cast<uint64_t>(len)};
                        phoneModel.phone = std::move(phone);
                        if (phoneModel.phone.size() > 7) {
                            uint32_t prefix = 0;
                            for (int i = 0; i < 7; ++i) {
                                prefix = prefix * 10 + (data[slen + i] - '0');
                            }
                            std::string prefixPhone{data + slen, 7};
                            phoneModel.prefixPhone = prefix;
                        }

                        if (phoneModel.prefixPhone > 0) {
                            auto phoneLocationInfo = csvPhoneLocationLoaderPtr->getByPrefixPhone(phoneModel.prefixPhone);
                            phoneModel.locationInfo = phoneLocationInfo;
                        }

                        lineStart = pos + 1;
                    }
                }
                if (lineStart < blockIndex.end) {
                    phones.emplace_back();
                    auto& phoneModel = phones.back();
                    int64_t len = blockIndex.end - lineStart;
                    if (len > 0 && data[blockIndex.end - 1] == '\r') {
                        --len;
                    }
                    std::string phone{data + lineStart, static_cast<uint64_t>(len)};
                    phoneModel.phone = std::move(phone);
                    if (phoneModel.phone.size() > 7) {
                        uint32_t prefix = 0;
                        for (int i = 0; i < 7; ++i) {
                            prefix = prefix * 10 + (data[lineStart + i] - '0');
                        }
                        phoneModel.prefixPhone = prefix;
                    }

                    if (phoneModel.prefixPhone > 0) {
                        auto phoneLocationInfo = csvPhoneLocationLoaderPtr->getByPrefixPhone(phoneModel.prefixPhone);
                        phoneModel.locationInfo = phoneLocationInfo;
                    }
                }
                threadInsidePhoneList[idx] = std::move(phones);
            }});
        }
        for(auto& t : threadList) {
            t.join();
        }

        file.unmap(mmap);

        size_t totalLines = 0;
        for (const auto& list : threadInsidePhoneList) {
            totalLines += list.size();
        }
        phonesLists.reserve(totalLines);

        for (auto& list : threadInsidePhoneList) {
            phonesLists.insert(phonesLists.end(),
                               std::make_move_iterator(list.begin()),
                               std::make_move_iterator(list.end()));
        }
     }

    return phonesLists;
}

bool TextFileLoader::openFile(const QString& filePath)
{
    if (file.isOpen()) {
        file.close();
    }
    file.setFileName(filePath);
    if (!file.open(QIODevice::ReadWrite)) {
        qFatal() << "文件打开失败";
        return false;
    }
    return true;
}
