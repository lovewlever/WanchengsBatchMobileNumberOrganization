#ifndef PHONENUMBERLISTMODEL_H
#define PHONENUMBERLISTMODEL_H

#include <QAbstractListModel>

class PhoneNumberListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit PhoneNumberListModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QHash<int,QByteArray> roleNames() const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    void phoneDisorder();
    void deduplicate();
    /**
     * 清除非手机号
     * @brief filterPhones
     */
    void filterPhones();


    void setPhoneDatas(const std::vector<std::string>&& phoneDatas);

    std::vector<std::string>& getPhoneDatas();

private:

    std::vector<std::string> phoneDatas;

    enum RoleNames {
        Phone
    };
};

#endif // PHONENUMBERLISTMODEL_H
