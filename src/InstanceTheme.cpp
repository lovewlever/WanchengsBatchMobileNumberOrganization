#include "InstanceTheme.h"

#include <qdiriterator.h>
#include <QGuiApplication>
#include <QStyleHints>

InstanceTheme::InstanceTheme(QObject *parent)
    : QObject{parent}
{
    QDirIterator it(":", QDirIterator::Subdirectories);
    while (it.hasNext()) {
        qDebug() << it.next();
    }

    QFile file(":/json/material-theme.json");

    qDebug() << "exists =" << file.exists();

    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Material theme load fail!!!";
        //  throw std::runtime_error("open failed");
    } else {
        QByteArray data = file.readAll();
        const Theme theme = nlohmann::json::parse(data.constData());

        const auto isDark = QGuiApplication::styleHints()->colorScheme() == Qt::ColorScheme::Dark;

        this->setPrimary(QColor::fromString(QString::fromStdString({isDark ? theme.schemes.dark.primary : theme.schemes.light.primary})));
        this->setOnPrimary(QColor::fromString(QString::fromStdString({isDark ? theme.schemes.dark.onPrimary : theme.schemes.light.onPrimary})));
        this->setPrimaryContainer(QColor::fromString(QString::fromStdString({isDark ? theme.schemes.dark.primaryContainer : theme.schemes.light.primaryContainer})));
        this->setOnPrimaryContainer(QColor::fromString(QString::fromStdString({isDark ? theme.schemes.dark.onPrimaryContainer : theme.schemes.light.onPrimaryContainer})));
        this->setSecondary(QColor::fromString(QString::fromStdString({isDark ? theme.schemes.dark.secondary : theme.schemes.light.secondary})));
        this->setSecondaryContainer(QColor::fromString(QString::fromStdString({isDark ? theme.schemes.dark.secondaryContainer : theme.schemes.light.secondaryContainer})));
        this->setOnSecondaryContainer(QColor::fromString(QString::fromStdString({isDark ? theme.schemes.dark.onSecondaryContainer : theme.schemes.light.onSecondaryContainer})));
        this->setBackground(QColor::fromString(QString::fromStdString({isDark ? theme.schemes.dark.background : theme.schemes.light.background})));
        this->setSurface(QColor::fromString(QString::fromStdString({isDark ? theme.schemes.dark.surface : theme.schemes.light.surface})));
        this->setSurfaceContainer(QColor::fromString(QString::fromStdString({isDark ? theme.schemes.dark.surfaceContainer : theme.schemes.light.surfaceContainer})));
        this->setOnSurface(QColor::fromString(QString::fromStdString({isDark ? theme.schemes.dark.onSurface : theme.schemes.light.onSurface})));
        this->setOutline(QColor::fromString(QString::fromStdString({isDark ? theme.schemes.dark.outline : theme.schemes.light.outline})));
        this->setError(QColor::fromString(QString::fromStdString({isDark ? theme.schemes.dark.error : theme.schemes.light.error})));
        this->setErrorContainer(QColor::fromString(QString::fromStdString({isDark ? theme.schemes.dark.errorContainer : theme.schemes.light.errorContainer})));
    }
}

InstanceTheme* InstanceTheme::getInstance() {
    if (InstanceTheme::instance_ == nullptr) {
        std::lock_guard<std::mutex> lock(InstanceTheme::mutex_);
        if (InstanceTheme::instance_ == nullptr) {
            InstanceTheme::instance_ = new InstanceTheme();
        }
    }
    return InstanceTheme::instance_;
}

QColor InstanceTheme::getOnPrimary() const
{
    return onPrimary;
}

void InstanceTheme::setOnPrimary(const QColor &newOnPrimary)
{
    if (onPrimary == newOnPrimary)
        return;
    onPrimary = newOnPrimary;
    emit onPrimaryChanged();
}

QColor InstanceTheme::getOnSecondaryContainer() const
{
    return onSecondaryContainer;
}

void InstanceTheme::setOnSecondaryContainer(const QColor &newOnSecondaryContainer)
{
    if (onSecondaryContainer == newOnSecondaryContainer)
        return;
    onSecondaryContainer = newOnSecondaryContainer;
    emit onSecondaryContainerChanged();
}

QColor InstanceTheme::getOnPrimaryContainer() const
{
    return onPrimaryContainer;
}

void InstanceTheme::setOnPrimaryContainer(const QColor &newOnPrimaryContainer)
{
    if (onPrimaryContainer == newOnPrimaryContainer)
        return;
    onPrimaryContainer = newOnPrimaryContainer;
    emit onPrimaryContainerChanged();
}

QColor InstanceTheme::getSecondary() const
{
    return secondary;
}

void InstanceTheme::setSecondary(const QColor &newSecondary)
{
    if (secondary == newSecondary)
        return;
    secondary = newSecondary;
    emit secondaryChanged();
}

QColor InstanceTheme::getSecondaryContainer() const
{
    return secondaryContainer;
}

void InstanceTheme::setSecondaryContainer(const QColor &newSecondaryContainer)
{
    if (secondaryContainer == newSecondaryContainer)
        return;
    secondaryContainer = newSecondaryContainer;
    emit secondaryContainerChanged();
}

QColor InstanceTheme::getOnSurface() const
{
    return onSurface;
}

void InstanceTheme::setOnSurface(const QColor &newOnSurface)
{
    if (onSurface == newOnSurface)
        return;
    onSurface = newOnSurface;
    emit onSurfaceChanged();
}

QColor InstanceTheme::getPrimaryContainer() const
{
    return primaryContainer;
}

void InstanceTheme::setPrimaryContainer(const QColor &newPrimaryContainer)
{
    if (primaryContainer == newPrimaryContainer)
        return;
    primaryContainer = newPrimaryContainer;
    emit primaryContainerChanged();
}

QColor InstanceTheme::getErrorContainer() const
{
    return errorContainer;
}

void InstanceTheme::setErrorContainer(const QColor &newErrorContainer)
{
    if (errorContainer == newErrorContainer)
        return;
    errorContainer = newErrorContainer;
    emit errorContainerChanged();
}

QColor InstanceTheme::getError() const
{
    return error;
}

void InstanceTheme::setError(const QColor &newError)
{
    if (error == newError)
        return;
    error = newError;
    emit errorChanged();
}

QColor InstanceTheme::getOutline() const
{
    return outline;
}

void InstanceTheme::setOutline(const QColor &newOutline)
{
    if (outline == newOutline)
        return;
    outline = newOutline;
    emit outlineChanged();
}

QColor InstanceTheme::getSurfaceContainer() const
{
    return surfaceContainer;
}

void InstanceTheme::setSurfaceContainer(const QColor &newSurfaceContainer)
{
    if (surfaceContainer == newSurfaceContainer)
        return;
    surfaceContainer = newSurfaceContainer;
    emit surfaceContainerChanged();
}

QColor InstanceTheme::getSurface() const
{
    return surface;
}

void InstanceTheme::setSurface(const QColor &newSurface)
{
    if (surface == newSurface)
        return;
    surface = newSurface;
    emit surfaceChanged();
}

QColor InstanceTheme::getBackground() const
{
    return background;
}

void InstanceTheme::setBackground(const QColor &newBackground)
{
    if (background == newBackground)
        return;
    background = newBackground;
    emit backgroundChanged();
}

QColor InstanceTheme::getPrimary() const
{
    return primary;
}

void InstanceTheme::setPrimary(const QColor &newPrimary)
{
    if (primary == newPrimary)
        return;
    primary = newPrimary;
    emit primaryChanged();
}
