#include "sqlite3Database.hpp"
#include <time.h>
#include <sstream>

#define LOG_PREFIX "AppCli"

#define DBG if(1)


sqlite3Database::sqlite3Database(char *filename) 
    : DatabaseInterface(filename) 
{
    int rc = sqlite3_open(filename, &db);
    if(rc) {
        sqlite3_close(db);
        return;
    }
    if(!this->tableExists())
        this->createTable();
}

sqlite3Database::~sqlite3Database() {
    DBG printf("sqlite3Database::~sqlite3Database()");
    if(zErrMsg != NULL) 
        sqlite3_free(zErrMsg);
    if(db != NULL)
        sqlite3_close(db);
}

void sqlite3Database::createSensor(const Sensor &sensor) {
    DBG printf("sqlite3Database::createSensor\n");
    if(sensorExists(sensor)) {
        DBG printf("sqlite3Database::createSensor: sensor is exists");
        return;
    }
    char req[128] = "";
    time_t timestamp = time(NULL);
    int id = sensor.getId();
    sprintf(req, "insert into %s values(%d, '%s', %ld, '%s', %d, %d);", TABLE_NAME, sensor.getId(), sensor.getName().c_str(), timestamp, sensor.getData().c_str(), sensor.getSensorType(), sensor.getMessageType());
    DBG printf("sqlite3Database::createSensors: sql: %s\n", req);
    sqlite3_exec(db, req, NULL, 0, &zErrMsg);
    DBG printf("sqlite3Database::createSensors: zErrMsg = %s\n", zErrMsg);
}

void sqlite3Database::retrieveSensor(Sensor &sensor, int flag) {
    std::ostringstream stringStream;
    stringStream << "select * from " << TABLE_NAME << " where 1 ";
    if( flag & FLAG_BY_ID )
        stringStream << "and id = " << sensor.getId() << " ";
    if( flag & FLAG_BY_NAME )
        stringStream << "and name = '" << sensor.getName() << "' ";
    if( flag & FLAG_BY_SENSOR_TYPE )
        stringStream << "and sensor_type = " << sensor.getSensorType() << " ";
    if( flag & FLAG_BY_MESSAGE_TYPE )
        stringStream << "and message_type = " << sensor.getMessageType() << " ";
    stringStream << ";";

    sqlite3_exec(db, stringStream.str().c_str(), sqlite3Database::retrieve_callback, (void*)&sensor, &zErrMsg);
}

void sqlite3Database::retrieveSensor(int row, Sensor &sensor, int flag) {
    std::ostringstream stringStream;
    stringStream << "select * from " << TABLE_NAME << " where 1 ";

    if(flag & FLAG_BY_ID)
        stringStream << "and id = " << sensor.getId() << " ";
    if(flag & FLAG_BY_NAME)
        stringStream << "and name = '" << sensor.getName() << "' ";
    if(flag & FLAG_BY_SENSOR_TYPE) 
        stringStream << "and sensor_type = " << sensor.getSensorType() << " ";
    if(flag & FLAG_BY_MESSAGE_TYPE)
        stringStream << "and message_type = " << sensor.getMessageType() << " ";

    stringStream << " limit 1 offset " << row << ";";
    sqlite3_exec(db, stringStream.str().c_str(), sqlite3Database::retrieve_callback, (void*)&sensor, &zErrMsg);
}

void sqlite3Database::updateSensor(const Sensor &sensor) {
    char req[128];
    if(sensorExists(sensor)) {
        sprintf(req, "update %s set name = '%s', data = '%s' where id = %d;", TABLE_NAME, sensor.getName().c_str(), sensor.getData().c_str(), sensor.getId());
        sqlite3_exec(db, req, NULL, 0, &zErrMsg);
    } else {
        createSensor(sensor);
    }
}

void sqlite3Database::deleteSensor(const Sensor &sensor) {
    char req[128];
    sprintf(req, "delete from %s where id = %d;", TABLE_NAME, sensor.getId());
    sqlite3_exec(db, req, NULL, 0, &zErrMsg);
}

time_t String2Timestamp(char *v) {
    time_t res = 0;
    sscanf(v, "%ld", &res);
    return res;
}

void Timestamp2String(time_t timestamp, char *v) {
    sprintf(v, "%ld", timestamp);
}

int sqlite3Database::retrieve_callback(void *data, int argc, char **argv, char **azColName) {
    Sensor *s = (Sensor*)data;
    s->setName(argv[1] != NULL ? argv[1] : "")->
        setData(argv[3] != NULL ? argv[3] : "")->
        setSensorType(atoi(argv[4]))->
        setMessageType(atoi(argv[5]));
}

bool sqlite3Database::sensorExists(const Sensor &sensor) {
    return sensorsCount(&sensor) > 0;
}

int sqlite3Database::sensorsCount(const Sensor *sensor) {
    DBG printf("sqlite3Database::sensorsCount\n");
    char req[64] = "";
    int count = 0;
    if(sensor != NULL) {
        sprintf(req, "select count() from %s where id = %d;", TABLE_NAME, sensor->getId());
        DBG printf("sqlite3Database::sensorsCount: req = %s\n", req);
    } else {
        sprintf(req, "select count() from %s;", TABLE_NAME);
        DBG printf("sqlite3Database::sensorsCount: req = %s\n", req);
    }
    sqlite3_exec(db, req, &sqlite3Database::sensors_count_callback, (void*)&count, &zErrMsg);
    DBG printf("sqlite3Database::sensorsCount: count = %d\n", count);
    return count;
}

int sqlite3Database::sensors_count_callback(void *data, int argc, char **argv, char **azColName) {
    DBG printf("sqlite3Database::sensors_count_callback\n");
    int * count = (int*)data;
    (*count) = atoi(argv[0]);
}


void sqlite3Database::createTable() {
    char req[150] = "";
    sprintf(req, "create table %s(id unsigned int, name varchar(32), last_data_date integer, data varchar(255), sensor_type int, message_type int);", TABLE_NAME);
    sqlite3_exec(db, req, NULL, 0, &zErrMsg);
}

bool sqlite3Database::tableExists() {
    char req[128] = "";
    sprintf(req, "select name from sqlite_master where type='table' and name='%s';", TABLE_NAME);
    int count = 0;
    sqlite3_exec(db, req, &sqlite3Database::sensors_count_callback, (void*)&count, &zErrMsg);
    return (count > 0);
}
