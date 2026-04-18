#ifndef EXPORTPHONENUMBER_H
#define EXPORTPHONENUMBER_H

/**
 * 导出文件
 */
#include <utility>
#include <string>
#include <Structs.h>
#include <QVariant>

class ExportPhoneNumber
{
public:
    ExportPhoneNumber();
    ~ExportPhoneNumber();

    /**
     * 按照地区导出
     */
    std::pair<bool, std::string> exportByRegion(std::vector<PhoneListModel>& phones);

    /**
     * 按照运营商导出
     */
    std::pair<bool, std::string> exportByCarrier(std::vector<PhoneListModel> &phones);

    /**
     * 分批导出
     */
    std::pair<bool, std::string> exportByInBatch(std::vector<PhoneListModel> &phones, const QVariant& variant);

};

#endif // EXPORTPHONENUMBER_H
