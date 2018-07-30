# QtCreator Project File

# Dicegame demostration of TDD using CppUTest and code coverage using gcov
# Ed Sutton

QT -= core
QT -= gui

TEMPLATE      = subdirs

CONFIG += ordered
SUBDIRS       += dicegame_main/dicegame.pro
SUBDIRS       += dicegame_test/dicegame_test.pro

