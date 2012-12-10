#ifndef CircularDisplay_h
#define CircularDisplay_h

#include <QPixmap>

class CircularDisplay : public QPixmap
{
public:
    CircularDisplay(const QString& name, int w = 90, int h = 90);
    virtual ~CircularDisplay();

    void initShape();
    void setDisplayColor(QColor col);
    void collected(int amount);

    void activate();
    void deactivate();
    bool active() const;

    void updateDisplay();

signals:
    
public slots:

private:
    int m_partCount;
    int m_maxValue;
    int m_value;
    int m_consumeSpeed;
    bool m_activated;
    QColor m_displayColor;
    QString m_name;
};

#endif // CircularDisplay_h
