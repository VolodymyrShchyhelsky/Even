#ifndef SQLQUERIES_H
#define SQLQUERIES_H

#include "QSqlQuery"
#include "QString"

static QSqlQuery addIntoTableQ(
        "insert into guest (id, age)"
        "values (:id, :age)"
        );

static QString ADD_Q = "insert into guest (id, age) values (?, ?)";

#endif // SQLQUERIES_H
