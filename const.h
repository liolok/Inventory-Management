#ifndef CONST_H
#define CONST_H

#include <QString>
#include <QtDebug>
#include <QSqlQuery>

const unsigned int USERNAME_MAX_LEN = 16;
const unsigned int PASSWORD_MAX_LEN = 16;

// Note that length must be less than max length above.
const QString DEFAULT_USERNAME = "admin";
const QString DEFAULT_PASSWORD = "admin";

const QString DB_TYPE = "QSQLITE";
const QString DB_PATH = "./database.sqlite";

#endif // CONST_H
