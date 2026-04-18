#include "PhoneNumberImportrer.h"
#include <QDebug>
#include <QUrl>
#include <memory>
#include <thread>
#include <QFile>
#include <InstanceDialog.h>
#include <filesystem>
#include <regex>

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

PhoneNumberImportrer::PhoneNumberImportrer(QObject *parent) : QObject(parent),
                                                              phoneNumberListModelPtr{new PhoneNumberListModel(parent)},
                                                              csvPhoneLocationLoaderPtr{std::make_shared<CSVPhoneLocationLoader>()},
                                                              textFileLoader{std::make_shared<TextFileLoader>()},
                                                              exportPhoneNumberPtr{std::make_unique<ExportPhoneNumber>()}
{

    std::thread{[this]()
                {
                    csvPhoneLocationLoaderPtr->loadPhoneLocationCSV();
                }}
        .detach();

    // 手机号加载成功的信号 刷新ui
    QObject::connect(this, &PhoneNumberImportrer::signalPhoneLoaded, this, [this]()
                     {
        this->phoneNumberListModelPtr->setPhoneDatas(std::move(phonesTemp));
        InstanceDialog::getInstance()->setLoadingDialogShow(false); });
}

PhoneNumberImportrer::~PhoneNumberImportrer()
{
    delete phoneNumberListModelPtr;
}

void PhoneNumberImportrer::importPhoneFile(const QVariant &variant)
{
    QUrl qurl = variant.toUrl();
    const auto path = qurl.toLocalFile().toStdString();
    std::filesystem::path fsPath{path};
    const auto extStr = fsPath.extension().string();
    std::regex regex{R"(\.(txt|text)$)", std::regex::icase};
    if (!std::regex_search(extStr.begin(), extStr.end(), regex))
    {
        qDebug() << "不支持的文件";
        InstanceDialog::getInstance()->setReminderDialogShowContent(true, "不支持的文件");
        return;
    }

    InstanceDialog::getInstance()->setLoadingDialogShow(true);

    std::thread{[variant, this]()
                {
                    QUrl qurl = variant.toUrl();
                    const auto path = qurl.toLocalFile();

                    textFileLoader->openFile(path);
                    std::vector<PhoneListModel> temp{};
                    phonesTemp.swap(temp);
                    phonesTemp = textFileLoader->loadAllPhones(csvPhoneLocationLoaderPtr);
                    setPhoneNumber(phonesTemp.size());
                    qDebug() << "导入数量：" << phonesTemp.size();
                    emit signalPhoneLoaded();
                }}
        .detach();
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
    this->phoneNumberListModelPtr->deduplicate([this]()
                                               {
        setPhoneNumber(this->phoneNumberListModelPtr->getPhoneDatas().size());
        setTopMsg("号码已去重处理"); });
}

void PhoneNumberImportrer::removeNonPhoneNumbers()
{
    this->phoneNumberListModelPtr->filterPhones();
    setPhoneNumber(this->phoneNumberListModelPtr->getPhoneDatas().size());
    setTopMsg("已移除非手机号");
}

void PhoneNumberImportrer::exportByRegion()
{
    auto& phoneDatas = phoneNumberListModelPtr->getPhoneDatas();
    if (phoneDatas.empty())
    {
        InstanceDialog::getInstance()->setReminderDialogShowContent(true, "没有可导出的号码");
        return;
    }
    exportPhoneNumberPtr->exportByRegion(phoneDatas);
}

Q_INVOKABLE void PhoneNumberImportrer::exportByCarrier()
{
    auto phoneDatas = phoneNumberListModelPtr->getPhoneDatas();
    if (phoneDatas.empty())
    {
        InstanceDialog::getInstance()->setReminderDialogShowContent(true, "没有可导出的号码");
        return;
    }
    exportPhoneNumberPtr->exportByCarrier(phoneDatas);
}
