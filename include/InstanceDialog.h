#ifndef INSTANCEDIALOG_H
#define INSTANCEDIALOG_H

#include <QObject>
#include <mutex>

class InstanceDialog : public QObject
{
    Q_OBJECT

private:
    inline static std::mutex _mutex{};
    inline static InstanceDialog *_instance{nullptr};

    bool loadingDialogShow{false};
    float_t loadingDialogProcressValue{0};

    Q_PROPERTY(bool loadingDialogShow READ getLoadingDialogShow WRITE setLoadingDialogShow NOTIFY loadingDialogShowChanged FINAL)

    Q_PROPERTY(float_t loadingDialogProcressValue READ getLoadingDialogProcressValue WRITE setLoadingDialogProcressValue NOTIFY loadingDialogProcressValueChanged FINAL)

public:
    explicit InstanceDialog(QObject *parent = nullptr);

    static InstanceDialog *getInstance();

    bool getLoadingDialogShow() const;
    void setLoadingDialogShow(bool newLoadingDialogShow);

    float_t getLoadingDialogProcressValue() const;
    void setLoadingDialogProcressValue(float_t newLoadingDialogProcressValue);

signals:
    void loadingDialogShowChanged();
    void loadingDialogProcressValueChanged();
};

#endif // INSTANCEDIALOG_H
