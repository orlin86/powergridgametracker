#ifndef gametracker_H
#define gametracker_H

#include "RoccatPowerGrid.h"

//see: http://doc.qt.digia.com/qt/plugins-howto.html

class gametracker : public IFuncProvider
{
    Q_OBJECT
    Q_INTERFACES(IFuncProvider)

public:
    gametracker();

    enum TCPState
    {
        TS_InvHost=-3,
        TS_Timeout=-2,
        TS_ConErr=-1,
        TS_Pending=0,
    };

    struct TTCPEntry
    {
        QTcpSocket* m_pxSock;
        int m_iState;
        qint64 m_iTimeStart;
        QUuid m_xHandle;
    };

    QList<TTCPEntry> m_axEntries;
    QTimer m_xTimerTick;

    virtual QString GetName() {return "gametracker";}
    virtual const QStringList& GetList();
    virtual QVariant GetValue(QString p_sName,const QVariantList& p_axParams);

public slots:
    void OnTick();
};

#endif // SAMPLE2_H
