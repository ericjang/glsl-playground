
#include <QGridLayout>
#include <QLabel>

#include "infopanel.h"



InfoPanel::InfoPanel(QGLWidget *parent) :
    m_parent(parent)
{
    m_font = QFont("Helvetica", 10);
    m_spacing = 2;
    m_margin = 20;
}

InfoPanel::~InfoPanel()
{

}



void InfoPanel::addInfo(const QString &key, const QString &value) {
    m_info.insert(key, Entry(key, value));
    m_order += key;
    updateLayout();
}

void InfoPanel::setInfo(const QString &key, const QString &value, bool layout) {
    if ( !m_info.contains(key) ) {
        m_info.insert( key, Entry(key, value) );
        m_order += key;
    } else {
        m_info[key].value = value;
    }
    if ( layout ) updateLayout();
}

void
InfoPanel::removeInfo( const QString &key )
{
    if ( m_info.contains(key) ) {
        m_info.remove( key );
        m_order.removeAll( key );
    }
    updateLayout();
}

void
InfoPanel::updateLayout()
{
    QFontMetrics metrics( m_font );
    int h = metrics.height();
    int y = metrics.ascent() + m_margin;
    int x0 = m_margin;
    for ( int i = 0; i < m_order.size(); ++i ) {
        Entry &entry = m_info[m_order[i]];
        entry.y = y;
        entry.x = x0;
        y += (h+m_spacing);
    }
}

void
InfoPanel::render()
{
    //glPushAttrib( GL_COLOR_BUFFER_BIT );
    glColor4f( 1.f, 1.f, 1.f, 1.f );
    //glColor3f(1.f,1.f,1.f);
    for ( QHash<QString, Entry>::const_iterator it = m_info.begin(); it != m_info.end(); ++it ) {
        const Entry &entry = it.value();
        m_parent->renderText( entry.x, entry.y, QString("%1: %2").arg(entry.key, entry.value) );
    }

 //   glPopAttrib();
}




