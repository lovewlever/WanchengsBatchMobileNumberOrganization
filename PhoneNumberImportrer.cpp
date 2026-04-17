#include "PhoneNumberImportrer.h"
#include <QDebug>
#include <QUrl>
#include <thread>
#include <QFile>

PhoneNumberListModel *PhoneNumberImportrer::getPhoneNumberListModelPtr() const
{
    return phoneNumberListModelPtr;
}

void PhoneNumberImportrer::setPhoneNumberListModelPtr(PhoneNumberListModel *newPhoneNumberListModelPtr)
{
    if (phoneNumberListModelPtr == newPhoneNumberListModelPtr)
        return;
    phoneNumberListModelPtr = newPhoneNumberListModelPtr;
    emit phoneNumberListModelPtrChanged();
}



int64_t PhoneNumberImportrer::getPhoneNumber() const
{
    return phoneNumber;
}

void PhoneNumberImportrer::setPhoneNumber(int64_t newPhoneNumber)
{
    if (phoneNumber == newPhoneNumber)
        return;
    phoneNumber = newPhoneNumber;
    emit phoneNumberChanged();
}

QString PhoneNumberImportrer::getTopMsg() const
{
    return topMsg;
}

void PhoneNumberImportrer::setTopMsg(const QString &newTopMsg)
{
    if (topMsg == newTopMsg)
        return;
    topMsg = newTopMsg;
    emit topMsgChanged();
}

PhoneNumberImportrer::PhoneNumberImportrer(QObject *parent): QObject(parent),
    phoneNumberListModelPtr{new PhoneNumberListModel(parent)},
    csvPhoneLocationLoaderPtr{std::make_shared<CSVPhoneLocationLoader>()},
    textFileLoader{std::make_shared<TextFileLoader>()}
{
    QPointer pointer{this};
    std::thread{[pointer]() {
            if (!pointer.isNull()) {
            const auto thizz = pointer.get();
                thizz->csvPhoneLocationLoaderPtr->loadPhoneLocationCSV();
            }
    }}.detach();
}

PhoneNumberImportrer::~PhoneNumberImportrer()
{
    delete phoneNumberListModelPtr;
}

void PhoneNumberImportrer::importPhoneFile(const QVariant &variant)
{
    std::vector<std::string> phones{};
    phones.reserve(100000);
    QUrl qurl = variant.toUrl();
    const auto path = qurl.toLocalFile();


    textFileLoader->openFile(path);
    // auto StrintgList = fileLoader.getPhonesByPage(0);
    auto StrintgList = textFileLoader->loadAllPhones(csvPhoneLocationLoaderPtr);
    setPhoneNumber(StrintgList.size());
    this->phoneNumberListModelPtr->setPhoneDatas(std::move(StrintgList));
    qDebug() << "导入数量：" << phones.size();
}

void PhoneNumberImportrer::cleanPhone()
{
    this->phoneNumberListModelPtr->setPhoneDatas({});
    this->setPhoneNumber(0);
    setTopMsg("号码已清空");
}

void PhoneNumberImportrer::phoneDisorder()
{
    this->phoneNumberListModelPtr->phoneDisorder();
    setTopMsg("号码已乱序处理");
}

void PhoneNumberImportrer::phoneDeduplication()
{
    this->phoneNumberListModelPtr->deduplicate();
    setPhoneNumber(this->phoneNumberListModelPtr->getPhoneDatas().size());
    setTopMsg("号码已去重处理");
}

void PhoneNumberImportrer::removeNonPhoneNumbers()
{
    this->phoneNumberListModelPtr->filterPhones();
    setPhoneNumber(this->phoneNumberListModelPtr->getPhoneDatas().size());
    setTopMsg("已移除非手机号");
}
