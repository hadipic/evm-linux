INCLUDEPATH += $$PWD/../../../engines/jerryscript
INCLUDEPATH += $$PWD/../../../engines/jerryscript/jerryscript/jerry-core
INCLUDEPATH += $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/include
INCLUDEPATH += $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/api
INCLUDEPATH += $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/debugger
INCLUDEPATH += $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/base
INCLUDEPATH += $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/builtin-objects
INCLUDEPATH += $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/builtin-objects/typedarray
INCLUDEPATH += $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/operations
INCLUDEPATH += $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/jcontext
INCLUDEPATH += $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/jmem
INCLUDEPATH += $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/jrt
INCLUDEPATH += $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/lit
INCLUDEPATH += $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/parser/js
INCLUDEPATH += $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/parser/regexp
INCLUDEPATH += $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/vm
INCLUDEPATH += $$PWD/../../../engines/jerryscript/jerryscript/jerry-ext/include

HEADERS += \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/config.h \
    $$PWD/../../../engines/jerryscript/evm_type.h

SOURCES += \
    $$PWD/../../../engines/jerryscript/common.js.bc.c \
    $$PWD/../../../engines/jerryscript/evm.c

SOURCES += \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/api/jerry-debugger-transport.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/api/jerry-debugger.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/api/jerry-module.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/api/jerry-snapshot.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/api/jerryscript.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/debugger/debugger.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/base/ecma-alloc.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/base/ecma-gc.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/base/ecma-errors.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/base/ecma-extended-info.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/base/ecma-helpers-collection.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/base/ecma-helpers-conversion.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/base/ecma-helpers-errol.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/base/ecma-helpers-external-pointers.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/base/ecma-helpers-number.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/base/ecma-helpers-string.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/base/ecma-helpers-value.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/base/ecma-helpers.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/base/ecma-init-finalize.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/base/ecma-lcache.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/base/ecma-line-info.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/base/ecma-literal-storage.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/base/ecma-module.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/base/ecma-property-hashmap.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/builtin-objects/ecma-builtin-aggregateerror.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/builtin-objects/ecma-builtin-aggregateerror-prototype.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/builtin-objects/ecma-builtin-array-iterator-prototype.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/builtin-objects/ecma-builtin-array-prototype-unscopables.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/builtin-objects/ecma-builtin-array-prototype.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/builtin-objects/ecma-builtin-array.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/builtin-objects/ecma-builtin-arraybuffer-prototype.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/builtin-objects/ecma-builtin-arraybuffer.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/builtin-objects/ecma-builtin-async-from-sync-iterator-prototype.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/builtin-objects/ecma-builtin-async-function-prototype.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/builtin-objects/ecma-builtin-async-function.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/builtin-objects/ecma-builtin-async-generator-function.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/builtin-objects/ecma-builtin-async-generator-prototype.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/builtin-objects/ecma-builtin-async-generator.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/builtin-objects/ecma-builtin-async-iterator-prototype.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/builtin-objects/ecma-builtin-atomics.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/builtin-objects/ecma-builtin-bigint-prototype.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/builtin-objects/ecma-builtin-bigint.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/builtin-objects/ecma-builtin-boolean-prototype.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/builtin-objects/ecma-builtin-boolean.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/builtin-objects/ecma-builtin-dataview-prototype.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/builtin-objects/ecma-builtin-dataview.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/builtin-objects/ecma-builtin-date-prototype.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/builtin-objects/ecma-builtin-date.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/builtin-objects/ecma-builtin-error-prototype.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/builtin-objects/ecma-builtin-error.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/builtin-objects/ecma-builtin-evalerror-prototype.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/builtin-objects/ecma-builtin-evalerror.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/builtin-objects/ecma-builtin-function-prototype.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/builtin-objects/ecma-builtin-function.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/builtin-objects/ecma-builtin-generator-function.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/builtin-objects/ecma-builtin-generator-prototype.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/builtin-objects/ecma-builtin-generator.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/builtin-objects/ecma-builtin-global.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/builtin-objects/ecma-builtin-handlers.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/builtin-objects/ecma-builtin-helpers-date.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/builtin-objects/ecma-builtin-helpers-error.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/builtin-objects/ecma-builtin-helpers-json.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/builtin-objects/ecma-builtin-helpers-sort.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/builtin-objects/ecma-builtin-helpers.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/builtin-objects/ecma-builtin-intrinsic.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/builtin-objects/ecma-builtin-iterator-prototype.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/builtin-objects/ecma-builtin-json.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/builtin-objects/ecma-builtin-map-iterator-prototype.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/builtin-objects/ecma-builtin-map-prototype.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/builtin-objects/ecma-builtin-map.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/builtin-objects/ecma-builtin-math.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/builtin-objects/ecma-builtin-number-prototype.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/builtin-objects/ecma-builtin-number.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/builtin-objects/ecma-builtin-object-prototype.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/builtin-objects/ecma-builtin-object.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/builtin-objects/ecma-builtin-promise-prototype.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/builtin-objects/ecma-builtin-promise.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/builtin-objects/ecma-builtin-proxy.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/builtin-objects/ecma-builtin-rangeerror-prototype.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/builtin-objects/ecma-builtin-rangeerror.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/builtin-objects/ecma-builtin-referenceerror-prototype.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/builtin-objects/ecma-builtin-referenceerror.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/builtin-objects/ecma-builtin-reflect.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/builtin-objects/ecma-builtin-regexp-prototype.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/builtin-objects/ecma-builtin-regexp-string-iterator-prototype.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/builtin-objects/ecma-builtin-regexp.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/builtin-objects/ecma-builtin-set-iterator-prototype.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/builtin-objects/ecma-builtin-set-prototype.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/builtin-objects/ecma-builtin-set.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/builtin-objects/ecma-builtin-shared-arraybuffer-prototype.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/builtin-objects/ecma-builtin-shared-arraybuffer.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/builtin-objects/ecma-builtin-string-iterator-prototype.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/builtin-objects/ecma-builtin-string-prototype.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/builtin-objects/ecma-builtin-string.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/builtin-objects/ecma-builtin-symbol-prototype.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/builtin-objects/ecma-builtin-symbol.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/builtin-objects/ecma-builtin-syntaxerror-prototype.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/builtin-objects/ecma-builtin-syntaxerror.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/builtin-objects/ecma-builtin-type-error-thrower.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/builtin-objects/ecma-builtin-typeerror-prototype.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/builtin-objects/ecma-builtin-typeerror.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/builtin-objects/ecma-builtin-urierror-prototype.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/builtin-objects/ecma-builtin-urierror.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/builtin-objects/ecma-builtin-weakmap-prototype.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/builtin-objects/ecma-builtin-weakmap.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/builtin-objects/ecma-builtin-weakref-prototype.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/builtin-objects/ecma-builtin-weakref.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/builtin-objects/ecma-builtin-weakset-prototype.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/builtin-objects/ecma-builtin-weakset.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/builtin-objects/ecma-builtins.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/builtin-objects/typedarray/ecma-builtin-bigint64array-prototype.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/builtin-objects/typedarray/ecma-builtin-bigint64array.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/builtin-objects/typedarray/ecma-builtin-biguint64array-prototype.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/builtin-objects/typedarray/ecma-builtin-biguint64array.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/builtin-objects/typedarray/ecma-builtin-float32array-prototype.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/builtin-objects/typedarray/ecma-builtin-float32array.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/builtin-objects/typedarray/ecma-builtin-float64array-prototype.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/builtin-objects/typedarray/ecma-builtin-float64array.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/builtin-objects/typedarray/ecma-builtin-int16array-prototype.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/builtin-objects/typedarray/ecma-builtin-int16array.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/builtin-objects/typedarray/ecma-builtin-int32array-prototype.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/builtin-objects/typedarray/ecma-builtin-int32array.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/builtin-objects/typedarray/ecma-builtin-int8array-prototype.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/builtin-objects/typedarray/ecma-builtin-int8array.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/builtin-objects/typedarray/ecma-builtin-typedarray-helpers.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/builtin-objects/typedarray/ecma-builtin-typedarray-prototype.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/builtin-objects/typedarray/ecma-builtin-typedarray.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/builtin-objects/typedarray/ecma-builtin-uint16array-prototype.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/builtin-objects/typedarray/ecma-builtin-uint16array.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/builtin-objects/typedarray/ecma-builtin-uint32array-prototype.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/builtin-objects/typedarray/ecma-builtin-uint32array.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/builtin-objects/typedarray/ecma-builtin-uint8array-prototype.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/builtin-objects/typedarray/ecma-builtin-uint8array.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/builtin-objects/typedarray/ecma-builtin-uint8clampedarray-prototype.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/builtin-objects/typedarray/ecma-builtin-uint8clampedarray.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/operations/ecma-arguments-object.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/operations/ecma-array-object.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/operations/ecma-arraybuffer-object.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/operations/ecma-async-generator-object.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/operations/ecma-atomics-object.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/operations/ecma-big-uint.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/operations/ecma-bigint-object.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/operations/ecma-bigint.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/operations/ecma-boolean-object.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/operations/ecma-comparison.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/operations/ecma-container-object.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/operations/ecma-conversion.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/operations/ecma-dataview-object.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/operations/ecma-eval.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/operations/ecma-exceptions.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/operations/ecma-function-object.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/operations/ecma-get-put-value.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/operations/ecma-iterator-object.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/operations/ecma-jobqueue.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/operations/ecma-lex-env.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/operations/ecma-number-object.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/operations/ecma-objects-general.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/operations/ecma-objects.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/operations/ecma-promise-object.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/operations/ecma-proxy-object.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/operations/ecma-reference.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/operations/ecma-regexp-object.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/operations/ecma-shared-arraybuffer-object.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/operations/ecma-string-object.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/operations/ecma-symbol-object.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/ecma/operations/ecma-typedarray-object.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/jcontext/jcontext.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/jmem/jmem-allocator.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/jmem/jmem-heap.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/jmem/jmem-poolman.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/jrt/jrt-fatals.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/jrt/jrt-logging.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/lit/lit-char-helpers.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/lit/lit-magic-strings.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/lit/lit-strings.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/parser/js/byte-code.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/parser/js/common.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/parser/js/js-lexer.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/parser/js/js-parser-expr.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/parser/js/js-parser-line-info-create.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/parser/js/js-parser-mem.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/parser/js/js-parser-module.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/parser/js/js-parser-statm.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/parser/js/js-parser-tagged-template-literal.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/parser/js/js-parser-util.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/parser/js/js-parser.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/parser/js/js-scanner-ops.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/parser/js/js-scanner-util.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/parser/js/js-scanner.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/parser/js/parser-errors.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/parser/regexp/re-bytecode.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/parser/regexp/re-compiler.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/parser/regexp/re-parser.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/vm/opcodes-ecma-arithmetics.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/vm/opcodes-ecma-bitwise.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/vm/opcodes-ecma-relational-equality.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/vm/opcodes.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/vm/vm-stack.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/vm/vm-utils.c \
    $$PWD/../../../engines/jerryscript/jerryscript/jerry-core/vm/vm.c

#SOURCES += \
#       $$PWD/../../../engines/jerryscript/jerryscript/jerry-ext/util/print.c



