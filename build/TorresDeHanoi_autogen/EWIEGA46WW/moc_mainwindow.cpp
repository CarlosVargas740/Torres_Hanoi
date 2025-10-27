/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../mainwindow.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.9.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN10MainWindowE_t {};
} // unnamed namespace

template <> constexpr inline auto MainWindow::qt_create_metaobjectdata<qt_meta_tag_ZN10MainWindowE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "MainWindow",
        "iniciarJuego",
        "",
        "resolverAutomatico",
        "resolverDesdeAqui",
        "reiniciar",
        "siguienteMovimiento",
        "cambiarVelocidad",
        "valor",
        "cambiarTema",
        "mostrarPantallaJuego",
        "mostrarAcercaDe",
        "animarParticulas",
        "mostrarMensajeFlotante",
        "mensaje",
        "color",
        "reproducirSonidoMovimiento",
        "mostrarHistorial",
        "guardarPartida",
        "cargarPartida",
        "mostrarEstadisticas",
        "cambiarDificultad",
        "activarModoZen",
        "mostrarTutorial",
        "onDiscoPresionado",
        "Disco*",
        "disco",
        "onDiscoSoltado",
        "posicion"
    };

    QtMocHelpers::UintData qt_methods {
        // Slot 'iniciarJuego'
        QtMocHelpers::SlotData<void()>(1, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'resolverAutomatico'
        QtMocHelpers::SlotData<void()>(3, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'resolverDesdeAqui'
        QtMocHelpers::SlotData<void()>(4, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'reiniciar'
        QtMocHelpers::SlotData<void()>(5, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'siguienteMovimiento'
        QtMocHelpers::SlotData<void()>(6, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'cambiarVelocidad'
        QtMocHelpers::SlotData<void(int)>(7, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Int, 8 },
        }}),
        // Slot 'cambiarTema'
        QtMocHelpers::SlotData<void()>(9, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'mostrarPantallaJuego'
        QtMocHelpers::SlotData<void()>(10, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'mostrarAcercaDe'
        QtMocHelpers::SlotData<void()>(11, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'animarParticulas'
        QtMocHelpers::SlotData<void()>(12, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'mostrarMensajeFlotante'
        QtMocHelpers::SlotData<void(QString, QColor)>(13, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QString, 14 }, { QMetaType::QColor, 15 },
        }}),
        // Slot 'reproducirSonidoMovimiento'
        QtMocHelpers::SlotData<void()>(16, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'mostrarHistorial'
        QtMocHelpers::SlotData<void()>(17, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'guardarPartida'
        QtMocHelpers::SlotData<void()>(18, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'cargarPartida'
        QtMocHelpers::SlotData<void()>(19, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'mostrarEstadisticas'
        QtMocHelpers::SlotData<void()>(20, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'cambiarDificultad'
        QtMocHelpers::SlotData<void()>(21, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'activarModoZen'
        QtMocHelpers::SlotData<void()>(22, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'mostrarTutorial'
        QtMocHelpers::SlotData<void()>(23, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onDiscoPresionado'
        QtMocHelpers::SlotData<void(Disco *)>(24, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 25, 26 },
        }}),
        // Slot 'onDiscoSoltado'
        QtMocHelpers::SlotData<void(Disco *, QPointF)>(27, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 25, 26 }, { QMetaType::QPointF, 28 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<MainWindow, qt_meta_tag_ZN10MainWindowE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10MainWindowE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10MainWindowE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN10MainWindowE_t>.metaTypes,
    nullptr
} };

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<MainWindow *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->iniciarJuego(); break;
        case 1: _t->resolverAutomatico(); break;
        case 2: _t->resolverDesdeAqui(); break;
        case 3: _t->reiniciar(); break;
        case 4: _t->siguienteMovimiento(); break;
        case 5: _t->cambiarVelocidad((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 6: _t->cambiarTema(); break;
        case 7: _t->mostrarPantallaJuego(); break;
        case 8: _t->mostrarAcercaDe(); break;
        case 9: _t->animarParticulas(); break;
        case 10: _t->mostrarMensajeFlotante((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QColor>>(_a[2]))); break;
        case 11: _t->reproducirSonidoMovimiento(); break;
        case 12: _t->mostrarHistorial(); break;
        case 13: _t->guardarPartida(); break;
        case 14: _t->cargarPartida(); break;
        case 15: _t->mostrarEstadisticas(); break;
        case 16: _t->cambiarDificultad(); break;
        case 17: _t->activarModoZen(); break;
        case 18: _t->mostrarTutorial(); break;
        case 19: _t->onDiscoPresionado((*reinterpret_cast< std::add_pointer_t<Disco*>>(_a[1]))); break;
        case 20: _t->onDiscoSoltado((*reinterpret_cast< std::add_pointer_t<Disco*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QPointF>>(_a[2]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 19:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< Disco* >(); break;
            }
            break;
        case 20:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< Disco* >(); break;
            }
            break;
        }
    }
}

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10MainWindowE_t>.strings))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 21)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 21;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 21)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 21;
    }
    return _id;
}
QT_WARNING_POP
