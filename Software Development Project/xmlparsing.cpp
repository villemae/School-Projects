#include "xmlparsing.h"
#include <QXmlStreamReader>
#include <stdexcept>
//rapidXML

std::vector<double> parse_given(QString elem_name, QByteArray data)
{
    std::vector<double> res;

    QXmlStreamReader reader(data);

    while (!reader.atEnd())
    {
        reader.readNext();
        if (reader.tokenType() == QXmlStreamReader::StartElement)
        {
            if (reader.name() == elem_name)
            {
                try
                {
                    res.push_back(std::stod(reader.readElementText().toStdString()));
                }
                catch (const std::invalid_argument& ia)
                {
                    continue;
                }
            }
        }
    }
    return res;
}
