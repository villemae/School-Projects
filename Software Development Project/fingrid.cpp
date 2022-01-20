#include "fingrid.h"
#include "xmlparsing.h"
#include <fstream>
#include <iostream>
#include <string>

#include <QProcess>


Fingrid::Fingrid()
{

}

std::vector<double> Fingrid::fetch(QString starttime, QString endtime)
{

    // request
    // curl -X GET --header "x-api-key: <API_KEY>" "https://api.fingrid.fi/v1/variable/188/events/xml?start_time=2020-01-19T16:00:00Z&end_time=2020-01-19T19:00:00Z"*/
    
    QProcess proc;

    QString command = "curl";
    // HOX!! This program won't work correctly without personal API key. When provided, it should be typed in <API_KEY> slot below
    QStringList args;
    args << "-X" << "GET" << "--header" << "x-api-key: <API_KEY>";

    QString URI = "https://api.fingrid.fi/v1/variable/" + id_ + "/events/xml?";
    QString stime = "start_time=" + starttime;
    QString etime = "&end_time=" + endtime;
    args << URI + stime + etime;

    proc.start(command, args, QIODevice::ReadOnly);
    proc.waitForFinished();

    QString elem_name = "value";
    std::vector<double> res = parse_given(elem_name, proc.readAllStandardOutput());

    return res;
}

void Fingrid::updateDataType(QString button)
{
    id_ = API_ids.at(button);
}
