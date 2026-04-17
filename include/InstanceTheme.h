#ifndef INSTANCETHEME_H
#define INSTANCETHEME_H

#include <QObject>
#include <theme.h>
#include <QColor>
#include <mutex>

class InstanceTheme : public QObject
{
    Q_OBJECT
public:
    explicit InstanceTheme(QObject *parent = nullptr);

    static InstanceTheme* getInstance();

    inline static InstanceTheme* instance_;
    inline static std::mutex mutex_;

    QColor primary;
    QColor onPrimary;
    QColor primaryContainer;
    QColor onPrimaryContainer;
    QColor secondary;
    QColor secondaryContainer;
    QColor onSecondaryContainer;
    QColor background;
    QColor surface;
    QColor surfaceContainer;
    QColor onSurface;
    QColor outline;
    QColor error;
    QColor errorContainer;

    QColor getPrimary() const;
    void setPrimary(const QColor &newPrimary);

    QColor getBackground() const;
    void setBackground(const QColor &newBackground);

    QColor getSurface() const;
    void setSurface(const QColor &newSurface);

    QColor getSurfaceContainer() const;
    void setSurfaceContainer(const QColor &newSurfaceContainer);

    QColor getOutline() const;
    void setOutline(const QColor &newOutline);

    QColor getError() const;
    void setError(const QColor &newError);

    QColor getErrorContainer() const;
    void setErrorContainer(const QColor &newErrorContainer);

    QColor getPrimaryContainer() const;
    void setPrimaryContainer(const QColor &newPrimaryContainer);

    QColor getOnSurface() const;
    void setOnSurface(const QColor &newOnSurface);

    QColor getSecondaryContainer() const;
    void setSecondaryContainer(const QColor &newSecondaryContainer);

    QColor getSecondary() const;
    void setSecondary(const QColor &newSecondary);

    QColor getOnPrimaryContainer() const;
    void setOnPrimaryContainer(const QColor &newOnPrimaryContainer);

    QColor getOnSecondaryContainer() const;
    void setOnSecondaryContainer(const QColor &newOnSecondaryContainer);

    QColor getOnPrimary() const;
    void setOnPrimary(const QColor &newOnPrimary);

signals:
    void primaryChanged();
    void backgroundChanged();

    void surfaceChanged();

    void surfaceContainerChanged();

    void outlineChanged();

    void errorChanged();

    void errorContainerChanged();

    void primaryContainerChanged();

    void onSurfaceChanged();

    void secondaryContainerChanged();

    void secondaryChanged();

    void onPrimaryContainerChanged();

    void onSecondaryContainerChanged();

    void onPrimaryChanged();

private:
    Q_PROPERTY(QColor primary READ getPrimary WRITE setPrimary NOTIFY primaryChanged FINAL)
    Q_PROPERTY(QColor background READ getBackground WRITE setBackground NOTIFY backgroundChanged FINAL)
    Q_PROPERTY(QColor surface READ getSurface WRITE setSurface NOTIFY surfaceChanged FINAL)
    Q_PROPERTY(QColor surfaceContainer READ getSurfaceContainer WRITE setSurfaceContainer NOTIFY surfaceContainerChanged FINAL)
    Q_PROPERTY(QColor outline READ getOutline WRITE setOutline NOTIFY outlineChanged FINAL)
    Q_PROPERTY(QColor error READ getError WRITE setError NOTIFY errorChanged FINAL)
    Q_PROPERTY(QColor errorContainer READ getErrorContainer WRITE setErrorContainer NOTIFY errorContainerChanged FINAL)
    Q_PROPERTY(QColor primaryContainer READ getPrimaryContainer WRITE setPrimaryContainer NOTIFY primaryContainerChanged FINAL)
    Q_PROPERTY(QColor onSurface READ getOnSurface WRITE setOnSurface NOTIFY onSurfaceChanged FINAL)
    Q_PROPERTY(QColor secondaryContainer READ getSecondaryContainer WRITE setSecondaryContainer NOTIFY secondaryContainerChanged FINAL)
    Q_PROPERTY(QColor secondary READ getSecondary WRITE setSecondary NOTIFY secondaryChanged FINAL)
    Q_PROPERTY(QColor onPrimaryContainer READ getOnPrimaryContainer WRITE setOnPrimaryContainer NOTIFY onPrimaryContainerChanged FINAL)
    Q_PROPERTY(QColor onSecondaryContainer READ getOnSecondaryContainer WRITE setOnSecondaryContainer NOTIFY onSecondaryContainerChanged FINAL)
    Q_PROPERTY(QColor onPrimary READ getOnPrimary WRITE setOnPrimary NOTIFY onPrimaryChanged FINAL)
};

#endif // INSTANCETHEME_H
