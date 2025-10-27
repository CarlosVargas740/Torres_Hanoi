/****************************************************************************
** Meta object code from reading C++ file 'disco.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../disco.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'disco.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN5DiscoE_t {};
} // unnamed namespace

template <> constexpr inline auto Disco::qt_create_metaobjectdata<qt_meta_tag_ZN5DiscoE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Disco",
        "discoPresionado",
        "",
        "Disco*",
        "disco",
        "discoSoltado",
        "posicion",
        "pos"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'discoPresionado'
        QtMocHelpers::SignalData<void(Disco *)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 4 },
        }}),
        // Signal 'discoSoltado'
        QtMocHelpers::SignalData<void(Disco *, QPointF)>(5, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 4 }, { QMetaType::QPointF, 6 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'pos'
        QtMocHelpers::PropertyData<QPointF>(7, QMetaType::QPointF, QMC::DefaultPropertyFlags | QMC::Writable | QMC::StdCppSet),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<Disco, qt_meta_tag_ZN5DiscoE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Disco::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN5DiscoE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN5DiscoE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN5DiscoE_t>.metaTypes,
    nullptr
} };

void Disco::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<Disco *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->discoPresionado((*reinterpret_cast< std::add_pointer_t<Disco*>>(_a[1]))); break;
        case 1: _t->discoSoltado((*reinterpret_cast< std::add_pointer_t<Disco*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QPointF>>(_a[2]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< Disco* >(); break;
            }
            break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< Disco* >(); break;
            }
            break;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (Disco::*)(Disco * )>(_a, &Disco::discoPresionado, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (Disco::*)(Disco * , QPointF )>(_a, &Disco::discoSoltado, 1))
            return;
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<QPointF*>(_v) = _t->pos(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setPos(*reinterpret_cast<QPointF*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *Disco::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Disco::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN5DiscoE_t>.strings))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "QGraphicsRectItem"))
        return static_cast< QGraphicsRectItem*>(this);
    return QObject::qt_metacast(_clname);
}

int Disco::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void Disco::discoPresionado(Disco * _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1);
}

// SIGNAL 1
void Disco::discoSoltado(Disco * _t1, QPointF _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1, _t2);
}
QT_WARNING_POP
