#include <QProcess>
#include "xmlparsing.h"
#include "fmi.h"

FMI::FMI()
{

}

std::vector<double> FMI::fetch(QString starttime, QString endtime)
{
    QProcess proc;

    QString command = "curl";
    QStringList args;
    args << "-X" << "GET";

    QString pastURI = "https://opendata.fmi.fi/wfs?request=getFeature&version=2.0.0&storedquery_id=fmi::observations::weather::simple";
    QString futureURI = "https://opendata.fmi.fi/wfs?request=getFeature&version=2.0.0&storedquery_id=fmi::forecast::hirlam::surface::point::simple";
    QString URI;

    QString place = "&place=" + location_;
    QString params = "&parameters=";

    if (info_type_ == TEMPERATURE)
    {
        URI = pastURI;
        params += "t2m";
    }
    else if (info_type_ == WIND)
    {
        URI = pastURI;
        params += "ws_10min";
    }
    else if (info_type_ == CLOUDINESS)
    {
        URI = pastURI;
        params += "n_man";
    }
    else if (info_type_ == TEMPERATUREFORECAST)
    {
        URI = futureURI;
        params += "Temperature";
    }
    else if (info_type_ == WINDFORECAST)
    {
        URI = futureURI;
        params += "WindSpeedMS";
    }
    else
    {
        URI = pastURI;
        params = "";
    }

    QString stime = "&starttime=" + starttime;
    QString etime = "&endtime=" + endtime;

    args << URI + place + params + stime + etime;

    proc.start(command, args, QIODevice::ReadOnly);
    proc.waitForFinished();

    QString elem_name = "ParameterValue";

    std::vector<double> res = parse_given(elem_name, proc.readAllStandardOutput());
    return res;
}

void FMI::updateDataType(QString button)
{
    if (button == "wind") {
        info_type_ = WIND;
    }
    else if (button == "windForecast") {
        info_type_ = WINDFORECAST;
    }
    else if (button == "cloudiness") {
        info_type_ = CLOUDINESS;
    }
    else if (button == "temperature") {
        info_type_ = TEMPERATURE;
    }
    else if (button == "temperatureForecast") {
        info_type_ = TEMPERATUREFORECAST;
    }
}

void FMI::setLocation(QString location)
{
    location_ = location;
}
