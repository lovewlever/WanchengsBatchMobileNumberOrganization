#include "InstanceDialog.h"

InstanceDialog::InstanceDialog(QObject *parent)
    : QObject{parent}
{}

InstanceDialog *InstanceDialog::getInstance() { 
    if (InstanceDialog::_instance == nullptr) {
        std::lock_guard lg{InstanceDialog::_mutex};
        if (InstanceDialog::_instance == nullptr) {
            InstanceDialog::_instance = new InstanceDialog();
        }
    }
    return _instance;
 }

float_t InstanceDialog::getLoadingDialogProcressValue() const
{
    return loadingDialogProcressValue;
}

void InstanceDialog::setLoadingDialogProcressValue(float_t newLoadingDialogProcressValue)
{
    if (loadingDialogProcressValue == newLoadingDialogProcressValue)
        return;
    loadingDialogProcressValue = newLoadingDialogProcressValue;
    emit loadingDialogProcressValueChanged();
}

bool InstanceDialog::getLoadingDialogShow() const
{
    return loadingDialogShow;
}

void InstanceDialog::setLoadingDialogShow(bool newLoadingDialogShow)
{
    if (loadingDialogShow == newLoadingDialogShow)
        return;
    loadingDialogShow = newLoadingDialogShow;
    emit loadingDialogShowChanged();
}
