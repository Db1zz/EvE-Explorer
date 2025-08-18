#ifndef EVE_EXPLORER_INCLUDE_EVE_EXPLORER_QML_INTEGRATION_VECTOR_INTEGRATION_H_
#define EVE_EXPLORER_INCLUDE_EVE_EXPLORER_QML_INTEGRATION_VECTOR_INTEGRATION_H_

#include <QtQmlIntegration/qqmlintegration.h>

#include <QObject>
#include <QVector>

#include "eve_explorer/sqlite_eve_universe_database.h"

// class SqliteEveUniverseDbIntegration : public QObject {
//   Q_OBJECT
//   Q_PROPERTY(std::string name READ get_name WRITE set_name)
//   QML_ELEMENT
//  public:
//   SqliteEveUniverseDbIntegration()
//       :
//       _db("/Users/georgiyonischenko/Projects/eve_map/eve_explorer/resources/"
//             "sde/eve_universe_db.sqlite") {}

// //  public slots:
// //   Q_INVOKABLE QVector<eve_explorer::types::Test> get_solar_systems() {
// //     QVector<eve_explorer::types::Test> vec;
// //     vec.append((eve_explorer::types::Test){.aboba = 1, .mama = 2});
// // 	vec.append((eve_explorer::types::Test){.aboba = 3, .mama = 4});
// // 	vec.append((eve_explorer::types::Test){.aboba = 5, .mama = 6});
// // 	return vec;
// //   }

// public:
//   void set_name(std::string name) { _name = name; }
//   std::string get_name(void) { return _name; }

//  private:
//   std::string _name;
//   eve_explorer::database::SQLiteEveUniverseDatabase _db;
// };

struct TestContainer {
  Q_GADGET
//   Q_PROPERTY(QString name READ get_name WRITE set_name)
//   Q_PROPERTY(QString last_name READ get_last_name WRITE set_last_name)
  QML_VALUE_TYPE(testContainer)

//  public:
//   TestContainer() = default;
//   TestContainer(const QString& name, const QString& last_name) 
//     : _name(name), _last_name(last_name) {}
//   ~TestContainer() = default;

//   QString get_name(void) { return _name; }
//   QString get_last_name(void) { return _last_name; }
//   void set_name(const QString& name) { _name = name; }
//   void set_last_name(const QString& last_name) { _last_name = last_name; }

//  private:
//   QString _name;
//   QString _last_name;
public:
   QString _name;
   QString _last_name;
};

class StoresTestContainers : public QObject {
  Q_OBJECT
  QML_ELEMENT

 public:
   StoresTestContainers() {
    // TestContainer t1;
    // // t1.set_name("Aboba");
    // // t1.set_last_name("Abobovi4");
    // TestContainer t2;
    // t2.set_name("Abobus");
    // t2.set_last_name("Abiba)");
    // _vector.push_back(t1);
    // _vector.push_back(t2);
  }

 public slots:

  QVector<TestContainer> get_vector(void) { return _vector; }

 private:
  QVector<TestContainer> _vector;
};

#endif  // EVE_EXPLORER_INCLUDE_EVE_EXPLORER_QML_INTEGRATION_VECTOR_INTEGRATION_H_