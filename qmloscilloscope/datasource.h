
//#ifndef DATASOURCE_H
#define DATASOURCE_H

#include <QtCore/QObject>
#include <QtCharts/QAbstractSeries>

class QQuickView;

QT_CHARTS_USE_NAMESPACE

class DataSource : public QObject
{
    Q_OBJECT
public:
    explicit DataSource(QQuickView *appViewer, QObject *parent = 0);

Q_SIGNALS:

public slots:
    void generateData(int type, int rowCount, int colCount);
    void update(QAbstractSeries *series);

private:
    QQuickView *m_appViewer;
    QList<QVector<QPointF> > m_data;
    int m_index;
};

//#endif DATASOURCE_H
