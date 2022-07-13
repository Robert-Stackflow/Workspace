
add_library(Qt5::SqliteCipherDriverPlugin MODULE IMPORTED)


_populate_Sql_plugin_properties(SqliteCipherDriverPlugin RELEASE "sqldrivers/sqlitecipher.dll" TRUE)
_populate_Sql_plugin_properties(SqliteCipherDriverPlugin DEBUG "sqldrivers/sqlitecipherd.dll" TRUE)

list(APPEND Qt5Sql_PLUGINS Qt5::SqliteCipherDriverPlugin)
set_property(TARGET Qt5::Sql APPEND PROPERTY QT_ALL_PLUGINS_sqldrivers Qt5::SqliteCipherDriverPlugin)
set_property(TARGET Qt5::SqliteCipherDriverPlugin PROPERTY QT_PLUGIN_TYPE "sqldrivers")
set_property(TARGET Qt5::SqliteCipherDriverPlugin PROPERTY QT_PLUGIN_EXTENDS "")
set_property(TARGET Qt5::SqliteCipherDriverPlugin PROPERTY QT_PLUGIN_CLASS_NAME "SqliteCipherDriverPlugin")
