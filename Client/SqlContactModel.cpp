#include "SqlContactModel.h"

SqlContactModel::SqlContactModel(QObject *parent) : QSqlQueryModel(parent)
{
    qFatal("Cannot set query on SqlContactModel: %s", qPrintable(lastError().text()));
}




