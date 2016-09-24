#include "gametracker.h"
#include <QtNetwork>
#include <QCoreApplication>
#define _WIN32_DCOM
#include <iostream>
using namespace std;
#include <comdef.h>
#include <Wbemidl.h>
# pragma comment(lib, "wbemuuid.lib")
#include <iostream>
#include <fstream>

#include "stdio.h"

int nDeaths = 0;

Q_EXPORT_PLUGIN2(gametracker, gametracker);

enum {TCPSOCK_TIMEOUT=5000};    //tcp timeout
enum {TCPENTRY_TIMEOUT=10000};  //entry lifetime

gametracker::gametracker()
{
    connect(&m_xTimerTick,SIGNAL(timeout()),this,SLOT(OnTick()));
    m_xTimerTick.setInterval(2000);
    m_xTimerTick.start();
		std::ofstream ofs ("test.txt", std::ofstream::out);
	ofs << "init";

	ofs.close();
}

const QStringList& gametracker::GetList()
{
    return QStringList()<<"Run";
}

QVariant gametracker::GetValue(QString p_sName,const QVariantList& p_axParams)
{
	/*
    int option;
    option=p_axParams.at(0).toInt();
    QVariant returner;
    returner.setValue(-1);
    _bstr_t q;

    if ( option == 0 )
        q=L"Select * from Sensor WHERE Name LIKE 'CPU%' AND SensorType = 'Clock'";
    else if ( option == 1 )
        q=L"Select * from Sensor WHERE Name LIKE 'CPU%' AND SensorType = 'Temperature'";
    else if ( option == 2 )
        q=L"Select * from Sensor WHERE Name LIKE 'GPU%' AND SensorType = 'Temperature'";
    else if ( option == 3 ) {
        int s;
        s=p_axParams.at(1).toInt();

        if ( s == 1 )
            q=L"Select * from Sensor WHERE Name LIKE 'GPU Memory' AND SensorType = 'Load'";
        else if ( s == 2 )
            q=L"Select * from Sensor WHERE Name LIKE 'GPU Video Engine' AND SensorType = 'Load'";
        else
            q=L"Select * from Sensor WHERE Name LIKE 'GPU Core' AND SensorType = 'Load'";
    }
    else if ( option == 4 )
        q=L"Select * from Sensor WHERE Name LIKE 'GPU%' AND SensorType = 'Fan'";
    else if ( option == 5 ) {
        int fan;
        fan=p_axParams.at(1).toInt();
        fan=fan+1;
        _bstr_t f=fan;
        q=L"Select * from Sensor WHERE Identifier LIKE '/lpc/%' AND SensorType = 'Fan' AND Index = '"+f+"'";

    }
    else if ( option == 6 ){

        QString gpu=p_axParams.at(1).toString();
        _bstr_t g=SysAllocString(gpu.toStdWString().c_str());
        q=L"Select * from Sensor WHERE Name LIKE 'GPU "+g+"' AND SensorType = 'Clock'";
    }
    else if ( option == 7 )
        q=L"Select * from Sensor WHERE Identifier LIKE '/lpc/%' AND SensorType = 'Fan' AND Index = '3'";
    else
        return returner;
    float gputemp;

	
    gputemp=GetMax(q);

    returner.setValue(gputemp);

    return returner.toInt();*/
	std::ofstream ofs ("test.txt", std::ofstream::out);
	ofs << "GetValue was called.";
	ofs.close();
	++nDeaths;
	return nDeaths;



}

void gametracker::OnTick()
{
}


