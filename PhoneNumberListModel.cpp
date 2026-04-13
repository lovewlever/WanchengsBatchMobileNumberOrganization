#include "PhoneNumberListModel.h"
#include <random>

PhoneNumberListModel::PhoneNumberListModel(QObject *parent)
    : QAbstractListModel(parent)
{}

int PhoneNumberListModel::rowCount(const QModelIndex &parent) const
{
    return phoneDatas.size();
}

QHash<int, QByteArray> PhoneNumberListModel::roleNames() const
{
    return { {Phone, "phone"} };
}

QVariant PhoneNumberListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    switch (role) {
    case Phone:
        return QString::fromStdString(phoneDatas[index.row()]);
    default:
        break;
    }

    return "未识别";
}

void PhoneNumberListModel::phoneDisorder()
{
    beginResetModel();
    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(phoneDatas.begin(), phoneDatas.end(), gen);
    endResetModel();
}

void PhoneNumberListModel::setPhoneDatas(const std::vector<std::string> &&phoneDatas)
{
    beginResetModel();
    this->phoneDatas = std::move(phoneDatas);
    endResetModel();
}

std::vector<std::string> &PhoneNumberListModel::getPhoneDatas()
{
    return this->phoneDatas;
}

void PhoneNumberListModel::deduplicate()
{
    beginResetModel();
    std::unordered_set<std::string> seen;
    std::vector<std::string> result;

    result.reserve(phoneDatas.size());

    for (const auto& item : phoneDatas) {
        if (seen.insert(item).second) {  // 第一次出现
            result.push_back(item);
        }
    }

    phoneDatas = std::move(result);
    endResetModel();
}

bool isValidPhone(const std::string& s)
{
    if (s.size() != 11) return false;
    if (s[0] != '1') return false;

    return std::all_of(s.begin(), s.end(), ::isdigit);
}

std::string normalize(std::string s)
{
    // 去空格
    s.erase(std::remove_if(s.begin(), s.end(), ::isspace), s.end());

    // 去 +86
    if (s.rfind("+86", 0) == 0) {
        s = s.substr(3);
    }

    // 去 86
    if (s.rfind("86", 0) == 0) {
        s = s.substr(2);
    }

    return s;
}

void PhoneNumberListModel::filterPhones()
{
    beginResetModel();
    std::vector<std::string> result;
    result.reserve(phoneDatas.size());

    for (auto& item : phoneDatas) {
        auto s = normalize(item);

        if (isValidPhone(s)) {
            result.push_back(s);
        }
    }

    phoneDatas = std::move(result);
    endResetModel();
}
