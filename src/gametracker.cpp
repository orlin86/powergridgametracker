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

Q_EXPORT_PLUGIN2(gametracker, gametracker);

enum {TCPSOCK_TIMEOUT=5000};    //tcp timeout
enum {TCPENTRY_TIMEOUT=10000};  //entry lifetime

gametracker::gametracker()
{
	nDeaths = 0;
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
	std::ofstream ofs ("test.txt", std::ofstream::out | std::ofstream::app);
	ofs << "GetValue was called.";
	ofs.close();
	 
	if (pollWebSocketStatus())
		{
			ofs << ".";
			auto val = pollNumDeaths();
			if (nDeaths != val)
			{
				ofs << "nDeaths changed: " << val;
			}
			nDeaths = val;
		}
		else
		{
			ofs << "WebSocket not open. Terminating." << std::endl;
			ofs.close();
		}
	return nDeaths;
}

void gametracker::OnTick()
{
}


