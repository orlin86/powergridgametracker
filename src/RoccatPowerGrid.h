#ifndef ROCCATPOWERGRID_H
#define ROCCATPOWERGRID_H

#include <QtCore>
#include <QtNetwork>
#include <QtGui>

#if defined(POWERGRID_LIBRARY)
#  define POWERGRID_EXPORT Q_DECL_EXPORT
#else
#  define POWERGRID_EXPORT Q_DECL_IMPORT
#endif

/*! \brief Plugin Base Interface
 * The abstract parent of all plugin classes. */
class IPluginBase : public QObject
{
public:
    virtual ~IPluginBase() {}
    /*! each plugin is identified by a unique name */
    virtual QString GetName()=0;

    /*! plugins can maintain a config which will be saved inside the UserConfig.
        config will also be generated by config-ui defined inside json Controls section*/
    virtual void SetConfig(QVariantMap p_xCfg) {}
    virtual QVariantMap GetConfig() {return QVariantMap();}

    //function calls for javascript & config interface
    /*! this is a plugins main interface for communication with javascript,
        it can be used for providing data and invoking functions*/
    virtual QVariant GetValue(QString p_sName,const QVariantList& p_axParams) {p_sName;p_axParams;return QVariant::Invalid;}
};
Q_DECLARE_INTERFACE(IPluginBase, "org.roccat.powergrid.IPluginBase")

/*! \brief Interface for Function Provider Plugins
 * Basic plugin type, communicates through GetValue(...)*/
class IFuncProvider : public IPluginBase
{
public:
    /*! \return list of provided functions */
    virtual const QStringList& GetList()=0;
};
Q_DECLARE_INTERFACE(IFuncProvider, "org.roccat.powergrid.IFuncProvider")

/*! \brief Interface for Data Source Plugins
 * Data Source Plugins are used by the incoming center*/
class IIncomingDataSource : public IPluginBase
{
public:
    //QMap<UTC_time_in_ms,data> (use micoseconds for secondary sorting criteria or uniquification)
    //keys are sorted automatically, newest entry is last
    /*! Data Source entry list format
     *  QMap<UTC_time_in_ms,data> (use micoseconds for secondary sorting criteria or uniquification)
     *  keys are sorted automatically, newest entry is last
     *  An entry should contain the following keys:
     *      - title   -   title of entry
     *      - text    -   additional text (optional)
     *      - link    -   link for user tapping on entry (optional)
     *      - id      -   unique id, used for identifying duplicates
     *      - time    -   timestamp of entry (should be the same as QMap key)
     *      - icon    -   (optional)
     *      - resp    -   response id for responsable messages, incoming center will call SendResponse(respID,msgString) via GetValue (optional)
     */
    typedef QMap<qint64,QVariantMap> TEntries;

    /*! \return list of data entries, these need to be cached by the plugin internally */
    virtual TEntries GetEntries()=0;
};
Q_DECLARE_INTERFACE(IIncomingDataSource, "org.roccat.powergrid.IIncomingDataSource")

/*! \brief Window message hook interface
    some plugins may need to catch custom window messages to communicate with other windows,
    \see PluginTools::AddWindowMessageProxy and PluginTools::RemWindowMessageProxy */
class IWindowMessageProxy
{
public:
    virtual ~IWindowMessageProxy() {}
#if defined(Q_WS_WIN)
    virtual bool winEvent(MSG*,long*) {return false;}
#endif //Q_WS_WIN
#if defined(Q_WS_MAC)
    virtual bool macEvent(EventHandlerCallRef, EventRef) {return false;}
#endif //Q_WS_MAC
#if defined(Q_WS_X11)
    virtual bool x11Event(XEvent *) {return false;}
#endif //Q_WS_X11
};

#ifdef GetTempPath
#undef GetTempPath
#endif

/*! \brief Utility functions for plugins
 */
class POWERGRID_EXPORT PluginTools
{
public:
    /*! creates QXmlStreamReader compatible output */
    static QByteArray DoTidyHtml2Xml(const char* p_pcxSrc);
    /*! get certificates from Data/SSLCerts/CA */
    static QList<QSslCertificate> GetRootCAs();
    /*! creates shared HTTP disk cache for QNetworkAccessManager */
    static QAbstractNetworkCache* GetWebCache();
    /*! get HANDLE of main window */
    static WId GetMainWindowHandle();
    /*! add main window message proxy */
    static void AddWindowMessageProxy(IWindowMessageProxy* p_pxProxy);
    /*! remove main window message proxy */
    static void RemWindowMessageProxy(IWindowMessageProxy* p_pxProxy);

    //paths ...
    /*! \return temp path for power-grid application */
    static QString GetTempPath();
    /*! \return data path for power-grid application */
    static QString GetDataPath();
    /*! \return user path for power-grid application */
    static QString GetUserPath();
    /*! resolves special path names to absolute paths */
    static QString ResolvePath(QString p_sPath);
};

/*! \brief Logger
 *  Logging will show up inside console, in log.txt in the temp directory, and in the
 *  interactive logger (press ALT double-click on version string, or
 *  start power-grid with '-log' cmd-line-parameter
 */
class POWERGRID_EXPORT PluginLogger
{
public:
    enum LogLevel
    {
       TraceLevel = 0,
       DebugLevel,
       InfoLevel,
       WarnLevel,
       ErrorLevel,
       FatalLevel
    };

    static LogLevel GetLogLevel();

    class POWERGRID_EXPORT Helper
    {
    public:
       explicit Helper(LogLevel logLevel) :
             level(logLevel),
             qtDebug(&buffer) {}
       ~Helper();
       QDebug& stream(){ return qtDebug; }

    private:
       void writeToLog();

       LogLevel level;
       QString buffer;
       QDebug qtDebug;
    };

};

#define PGLOG_TRACE() \
    if( PluginLogger::GetLogLevel() > PluginLogger::TraceLevel ){} \
    else PluginLogger::Helper(PluginLogger::TraceLevel).stream()
#define PGLOG_DEBUG() \
    if( PluginLogger::GetLogLevel() > PluginLogger::DebugLevel ){} \
    else PluginLogger::Helper(PluginLogger::DebugLevel).stream()
#define PGLOG_INFO()  \
    if( PluginLogger::GetLogLevel() > PluginLogger::InfoLevel ){} \
    else PluginLogger::Helper(PluginLogger::InfoLevel).stream()
#define PGLOG_WARN()  \
    if( PluginLogger::GetLogLevel() > PluginLogger::WarnLevel ){} \
    else PluginLogger::Helper(PluginLogger::WarnLevel).stream()
#define PGLOG_ERROR() \
    if( PluginLogger::GetLogLevel() > PluginLogger::ErrorLevel ){} \
    else PluginLogger::Helper(PluginLogger::ErrorLevel).stream()
#define PGLOG_FATAL() \
    PluginLogger::Helper(PluginLogger::FatalLevel).stream()


#endif // ROCCATPOWERGRID_H
