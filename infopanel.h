
#ifndef INFOPANEL_H
#define INFOPANEL_H


#include <QGLWidget>
#include <QFont>
#include <QHash>
#include <QString>

/*
 * Class that handles drawing of key-value text pairs
 * to be displayed in OpenGL. Useful for debugging values.
 */

class InfoPanel
{
public:
    InfoPanel(QGLWidget *parent = 0);
    ~InfoPanel();
    struct Entry {
        QString key;
        QString value;
        int x; int y; // x, y pos
        Entry() {}
        Entry( const QString &k, const QString &v ) : key(k), value(v) {}
        Entry( const Entry &entry ) : key(entry.key), value(entry.value), x(entry.x), y(entry.y) {}
    };

    void setFont( const QFont &font ) { m_font = font; }
    void addInfo( const QString &key, const QString &value = QString() );
    void setInfo( const QString &key, const QString &value, bool layout = true );
    void removeInfo( const QString &key );

    void render();

private:
    QHash<QString, Entry> m_info;
    QList<QString> m_order;

    QFont m_font;
    int m_spacing, m_margin;

    QGLWidget *m_parent;

    void updateLayout();

};



#endif // INFOPANEL_H

