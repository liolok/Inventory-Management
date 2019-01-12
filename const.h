#ifndef CONST_H
#define CONST_H

#include <QString>

// Database
const QString DB_TYPE = "QSQLITE";
const QString DB_PATH = "./database.sqlite";

// User
const unsigned int USERNAME_MAX_LEN = 16;
const unsigned int PASSWORD_MAX_LEN = 16;
// Note that length must be less than max length above.
const QString DEFAULT_USERNAME = "admin";
const QString DEFAULT_PASSWORD = "admin";

// Item
const unsigned int ITEMNAME_MAX_LEN = 16;
const unsigned int CATEGORY_MAX_LEN = 16;
// This value should be quite small to avoid overflow.
const unsigned int INVENTORY_IO_MAX = 1000;

#endif // CONST_H
