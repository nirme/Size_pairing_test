/****************************************************************************
** Meta object code from reading C++ file 'main_class.h'
**
** Created: Thu 10. Mar 14:24:17 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../main_class.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'main_class.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_main_class[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      17,   11,   12,   11, 0x08,
      31,   11,   11,   11, 0x08,
      44,   11,   11,   11, 0x08,
      64,   55,   11,   11, 0x08,
      87,   11,   12,   11, 0x08,
     108,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_main_class[] = {
    "main_class\0\0bool\0addPathLine()\0"
    "selectPath()\0makeList()\0fileList\0"
    "makeVisibleList(list*)\0handleDevideButton()\0"
    "menageRadioButtons()\0"
};

const QMetaObject main_class::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_main_class,
      qt_meta_data_main_class, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &main_class::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *main_class::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *main_class::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_main_class))
        return static_cast<void*>(const_cast< main_class*>(this));
    return QWidget::qt_metacast(_clname);
}

int main_class::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: { bool _r = addPathLine();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 1: selectPath(); break;
        case 2: makeList(); break;
        case 3: makeVisibleList((*reinterpret_cast< list*(*)>(_a[1]))); break;
        case 4: { bool _r = handleDevideButton();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 5: menageRadioButtons(); break;
        default: ;
        }
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
