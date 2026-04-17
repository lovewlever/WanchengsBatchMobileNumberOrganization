#ifndef PHONENUMBERIMPORTRER_H
#define PHONENUMBERIMPORTRER_H

#include <QObject>
#include <QQmlEngine>
#include <PhoneNumberListModel.h>
#include <CSVPhoneLocationLoader.h>
#include <TextFileLoader.h>
#include <ExportPhoneNumber.h>
#include <qtmetamacros.h>

class PhoneNumberImportrer : public QObject
{
    Q_OBJECT
    QML_ELEMENT

private:
    PhoneNumberListModel* phoneNumberListModelPtr{nullptr};
    Q_PROPERTY(PhoneNumberListModel *phoneNumberListModelPtr READ getPhoneNumberListModelPtr WRITE setPhoneNumberListModelPtr NOTIFY phoneNumberListModelPtrChanged FINAL)

    int64_t phoneNumber{0};

    Q_PROPERTY(int64_t phoneNumber READ getPhoneNumber WRITE setPhoneNumber NOTIFY phoneNumberChanged FINAL)

    QString topMsg{""};

    Q_PROPERTY(QString topMsg READ getTopMsg WRITE setTopMsg NOTIFY topMsgChanged FINAL)





    std::shared_ptr<CSVPhoneLocationLoader> csvPhoneLocationLoaderPtr{nullptr};
    std::shared_ptr<TextFileLoader> textFileLoader{nullptr};
    std::unique_ptr<ExportPhoneNumber> exportPhoneNumberPtr{nullptr};

    std::vector<PhoneListModel> phonesTemp{};

public:
    explicit PhoneNumberImportrer(QObject *parent = nullptr);
    ~PhoneNumberImportrer();

    /**
     * 导入手机号
     * @brief importPhoneFile
     * @param variant
     */
    Q_INVOKABLE void importPhoneFile(const QVariant &variant);

    /**
     * 清空手机号
     * @return
     */
    Q_INVOKABLE void cleanPhone();

    /**
     * 号码乱序
     * @return
     */
    Q_INVOKABLE void phoneDisorder();

    /**
     * 去重
     * @return
     */
    Q_INVOKABLE void phoneDeduplication();

    /**
     * 除去非手机号
     * @return
     */
    Q_INVOKABLE void removeNonPhoneNumbers();

    /**
     * 按地区导出
     */
    Q_INVOKABLE void exportByRegion();

    /**
     * 按照运营商导出
     */
    Q_INVOKABLE void exportByCarrier();

    PhoneNumberListModel *getPhoneNumberListModelPtr() const;
    void setPhoneNumberListModelPtr(PhoneNumberListModel *newPhoneNumberListModelPtr);

    int64_t getPhoneNumber() const;
    void setPhoneNumber(int64_t newPhoneNumber);

    QString getTopMsg() const;
    void setTopMsg(const QString &newTopMsg);

signals:
    void phoneNumberListModelPtrChanged();
    void phoneNumberChanged();
    void topMsgChanged();

    /**
     * 手机号加载成功信号
     */
    void signalPhoneLoaded();
};

#endif // PHONENUMBERIMPORTRER_H
