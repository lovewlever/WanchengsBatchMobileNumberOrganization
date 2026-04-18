#include "ExportPhoneNumber.h"
#include <unordered_map>
#include <vector>
#include <fstream>

ExportPhoneNumber::ExportPhoneNumber() {}

ExportPhoneNumber::~ExportPhoneNumber() {}

/**
 * 按照地区导出
 */
std::pair<bool, std::string> ExportPhoneNumber::exportByRegion(std::vector<PhoneListModel> &phones)
{
    std::unordered_map<std::string_view, std::vector<PhoneListModel *>> regionMap{};
    for (auto &model : phones)
    {
        const auto &li = model.locationInfo;
        if (li == nullptr)
        {
            regionMap["未知地区"].emplace_back(&model);
        }
        else
        {
            regionMap[model.locationInfo->province].emplace_back(&model);
        }
    }

    const auto sizet = regionMap.size();

    for (const auto &pair : regionMap)
    {
        {
            const auto& vecs = pair.second;
            if (vecs.empty()) continue;
            std::ofstream fsWriter{std::string{"/Users/lovewlever/Downloads/" + std::string{pair.first} + ".txt"}, std::ios_base::out};
            if (fsWriter.is_open())
            {
                for (const auto &plModel : pair.second)
                {
                    if (plModel != nullptr) {
                        fsWriter << plModel->phone << "\n";
                    }
                    
                }
                fsWriter.flush();
            }
        }
    }

    return std::pair<bool, std::string>();
}

std::pair<bool, std::string> ExportPhoneNumber::exportByCarrier()
{
    return std::pair<bool, std::string>();
}
