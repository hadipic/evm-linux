#ifdef CONFIG_EVM_MODULE_ASSERT
#include "evm_module.h"

enum
{
    NOT_EQUAL,    // !=
    EQUAL,        // ==
    GREATER,      // >
    GREATER_THAN, // >=
    LESS_THAN,    // <=
    LESS          // <
};

//assert(value[, message])
static evm_val_t evm_module_assert_assert(evm_t *e, evm_val_t p, int argc, evm_val_t *v)
{
    if (argc < 1)
        return evm_mk_undefined(e);

    const char *message = NULL;

    if (argc > 1 && evm_is_string(e, v[1]))
        message = evm_2_string(e, v[1]);

    if (evm_is_boolean(e, v[0]))
    {
        if (evm_2_boolean(e, v[0]))
            return evm_mk_boolean(e, 1);
        evm_throw(e, evm_mk_string(e, message));
    }
    else if (evm_is_number(e, v[0]))
    {
        if (evm_2_integer(e, v[0]))
            return evm_mk_boolean(e, 1);
        evm_throw(e, evm_mk_string(e, message));
    }
    return evm_mk_undefined(e);
}

//doesNotThrow(block[, message])
static evm_val_t evm_module_assert_doesNotThrow(evm_t *e, evm_val_t p, int argc, evm_val_t *v)
{
    if (argc < 1 || !evm_is_callable(e, v[0]))
        return evm_mk_undefined(e);

    const char *message = NULL;
    if (argc > 1 && evm_is_string(e, v[1]))
        message = evm_2_string(e, v[1]);
    evm_val_t res = evm_call_free(e, v[0], evm_mk_undefined(e), 0, NULL);
    if ( evm_2_boolean(e, res) ) {
        return evm_mk_boolean(e, 1);
    } else {
        evm_throw(e, evm_mk_string(e, message));
    }
}

static evm_val_t compare(evm_t *e, evm_val_t l, evm_val_t r) {
    if (evm_is_integer(e, l)) {
        if (evm_is_integer(e, r)) {
            if (evm_2_integer(e, l) == evm_2_integer(e, r)) {
                return evm_mk_boolean(e, 1);
            } else {
                return evm_mk_boolean(e, 0);
            }
        } else {
            return evm_mk_boolean(e, 0);
        }
    } else if (evm_is_boolean(e, l)) {
        if (evm_2_boolean(e, r)) {
            if (evm_2_boolean(e, l) == evm_2_boolean(e, r)) {
                return evm_mk_boolean(e, 1);
            } else {
                return evm_mk_boolean(e, 0);
            }
        } else {
            return evm_mk_boolean(e, 0);
        }
    } else if (evm_is_string(e, l)) {
        if (evm_is_string(e, r)) {
            if (strcmp(evm_2_string(e, l), evm_2_string(e, r)) == 0) {
                return evm_mk_boolean(e, 1);
            } else {
                return evm_mk_boolean(e, 0);
            }
        } else {
            return evm_mk_boolean(e, 0);
        }
    } else {
        return evm_mk_boolean(e, 0);
    }
}

//equal(actual, expected[, message])
static evm_val_t evm_module_assert_equal(evm_t *e, evm_val_t p, int argc, evm_val_t *v)
{
    if (argc <= 1)
        return evm_mk_undefined(e);

    const char *message = NULL;
    if (argc > 1 && evm_is_string(e, v[1]))
        message = evm_2_string(e, v[1]);

    evm_val_t result = compare(e, v[0], v[1]);
    if ( evm_2_boolean(e, result) )
        return result;
    else {
        evm_throw(e, evm_mk_string(e, message));
    }
}

static evm_val_t compare_by_value(evm_t *e, evm_val_t l, evm_val_t r, int _operator) {
    evm_val_t result;
    switch (_operator) {
    case NOT_EQUAL: {
        if (evm_2_integer(e, l) != evm_2_integer(e, r)) {
            result = evm_mk_boolean(e, 0);
        } else {
            result = evm_mk_boolean(e, 1);
        }
        break;
    }
    case EQUAL: {
        if (evm_2_integer(e, l) == evm_2_integer(e, r)) {
            result = evm_mk_boolean(e, 0);
        } else {
            result = evm_mk_boolean(e, 1);
        }
        break;
    }
    case GREATER: {
        if (evm_2_integer(e, l) > evm_2_integer(e, r)) {
            result = evm_mk_boolean(e, 0);
        } else {
            result = evm_mk_boolean(e, 1);
        }
        break;
    }
    case GREATER_THAN: {
        if (evm_2_integer(e, l) >= evm_2_integer(e, r)) {
            result = evm_mk_boolean(e, 0);
        } else {
            result = evm_mk_boolean(e, 1);
        }
        break;
    }
    case LESS_THAN: {
        if (evm_2_integer(e, l) <= evm_2_integer(e, r)) {
            result = evm_mk_boolean(e, 0);
        } else {
            result = evm_mk_boolean(e, 1);
        }
        break;
    }
    case LESS: {
        if (evm_2_integer(e, l) < evm_2_integer(e, r)) {
            result = evm_mk_boolean(e, 0);
        } else {
            result = evm_mk_boolean(e, 1);
        }
        break;
    }
    }
    return result;
}

//fail(actual, expected, message, operator)
//operator: != | == | > | >= | < | <=
static evm_val_t evm_module_assert_fail(evm_t *e, evm_val_t p, int argc, evm_val_t *v)
{
    if (argc <= 3 || !evm_is_string(e, v[3]))
        return evm_mk_undefined(e);

    const char *message = evm_2_string(e, v[2]);

    evm_val_t result = evm_module_assert_equal(e, p, argc, v);
    if ( evm_2_boolean(e, result) ) {
        evm_throw(e, evm_mk_string(e, message));
    }

    const char *_operator= evm_2_string(e, v[3]);
    if (strcmp(_operator, "!=") == 0) {
        result = compare_by_value(e, v[0], v[1], NOT_EQUAL);
    } else if (strcmp(_operator, "==") == 0) {
        result = compare_by_value(e, v[0], v[1], EQUAL);
    } else if (strcmp(_operator, ">") == 0) {
        result = compare_by_value(e, v[0], v[1], GREATER);
    } else if (strcmp(_operator, ">=") == 0) {
        result = compare_by_value(e, v[0], v[1], GREATER_THAN);
    } else if (strcmp(_operator, "<=") == 0) {
        result = compare_by_value(e, v[0], v[1], LESS_THAN);
    } else if (strcmp(_operator, "<") == 0) {
        result = compare_by_value(e, v[0], v[1], LESS);
    } else {
        result = evm_mk_undefined(e);
    }
    return result;
}

//notEqual(actual, expected[, message])
static evm_val_t evm_module_assert_notEqual(evm_t *e, evm_val_t p, int argc, evm_val_t *v)
{
    if (argc < 2)
        return evm_mk_undefined(e);

    const char *message = NULL;
    if (argc > 1 && evm_is_string(e, v[2]))
        message = evm_2_string(e, v[2]);

    evm_val_t result = compare(e, v[0], v[1]);
    if ( evm_2_boolean(e, result) ) {
        evm_throw(e, evm_mk_string(e, message));
    }
    return evm_mk_boolean(e, 1);
}

//notStrictEqual(actual, expected[, message])
static evm_val_t evm_module_assert_notStrictEqual(evm_t *e, evm_val_t p, int argc, evm_val_t *v)
{
    return evm_module_assert_notEqual(e, p, argc, v);
}

//strictEqual(actual, expected[, message])
static evm_val_t evm_module_assert_strictEqual(evm_t *e, evm_val_t p, int argc, evm_val_t *v)
{
    return evm_module_assert_equal(e, p, argc, v);
}

//throws(block[, expected, message])
static evm_val_t evm_module_assert_throws(evm_t *e, evm_val_t p, int argc, evm_val_t *v)
{
    if (argc < 1 || !evm_is_callable(e, v[0]))
        return evm_mk_undefined(e);

    const char *message = NULL;
    if (argc > 1 && evm_is_string(e, v[1]))
        message = evm_2_string(e, v[1]);
    evm_val_t res = evm_call_free(e, v[0], evm_mk_undefined(e), 0, NULL);
    if ( evm_2_boolean(e, res) ) {
        evm_throw(e, evm_mk_string(e, message));
    } else {
        return evm_mk_boolean(e, 1);
    }
}

evm_err_t evm_module_assert(evm_t *e)
{
    evm_val_t obj = evm_object_create(e);
    evm_prop_set(e, obj, "assert", evm_mk_native(e, evm_module_assert_assert, "assert", 1));
    evm_prop_set(e, obj, "doesNotThrow", evm_mk_native(e, evm_module_assert_doesNotThrow, "doesNotThrow", 1));
    evm_prop_set(e, obj, "equal", evm_mk_native(e, evm_module_assert_equal, "equal", 1));
    evm_prop_set(e, obj, "fail", evm_mk_native(e, evm_module_assert_fail, "fail", 1));
    evm_prop_set(e, obj, "notEqual", evm_mk_native(e, evm_module_assert_notEqual, "notEqual", 1));
    evm_prop_set(e, obj, "notStrictEqual", evm_mk_native(e, evm_module_assert_notStrictEqual, "notStrictEqual", 1));
    evm_prop_set(e, obj, "strictEqual", evm_mk_native(e, evm_module_assert_strictEqual, "strictEqual", 1));
    evm_prop_set(e, obj, "throws", evm_mk_native(e, evm_module_assert_throws, "throws", 1));
    evm_module_add(e, "assert", obj);
    return ec_ok;
}
#endif
