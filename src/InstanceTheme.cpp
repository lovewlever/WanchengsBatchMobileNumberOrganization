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
        this->setPrimaryContainer(QColor::fromString(QString::fromStdString({isDark ? theme.schemes.dark.primaryContainer : theme.schemes.light.primaryContainer})));
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
