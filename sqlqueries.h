#ifndef SQLQUERIES_H
#define SQLQUERIES_H

#include "QSqlQuery"
#include "QString"

static QSqlQuery createVisitorsTableQ(
        "create table if not exist person"
        "(id integer primary key, "
        "firstname varchar(20))");

static QSqlQuery addIntoTableQ(
        "insert into person (id, age)"
        "values (:id, :age)"
        );

static QString ADD_Q = "insert into person (id, age) values (?, ?)";

#endif // SQLQUERIES_H
