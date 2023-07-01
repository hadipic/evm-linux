//This is auto-generated file
#ifdef EVM_US_MODULE_LIBC

#include "evm_module.h"

static evm_val_t evm_module_libc_fopen(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_res;
  evm_cffi_val_t cffi_args[2];
  evm_cffi_exec_param(e, cffi_args, "ss", argc, v);
  cffi_res.p = fopen(cffi_args[0].s, cffi_args[1].s);
  return evm_cffi_exec_ret(e, cffi_res, "pss");
}

static evm_val_t evm_module_libc_fclose(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_args[1];
  evm_cffi_exec_param(e, cffi_args, "p", argc, v);
  fclose(cffi_args[0].p);
  return EVM_UNDEFINED;
}

static evm_val_t evm_module_libc_fread(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_res;
  evm_cffi_val_t cffi_args[4];
  evm_cffi_exec_param(e, cffi_args, "siip", argc, v);
  cffi_res.i32 = fread(cffi_args[0].s, cffi_args[1].i32, cffi_args[2].i32, cffi_args[3].p);
  return evm_cffi_exec_ret(e, cffi_res, "isiip");
}

static evm_val_t evm_module_libc_fwrite(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_res;
  evm_cffi_val_t cffi_args[4];
  evm_cffi_exec_param(e, cffi_args, "siip", argc, v);
  cffi_res.i32 = fwrite(cffi_args[0].s, cffi_args[1].i32, cffi_args[2].i32, cffi_args[3].p);
  return evm_cffi_exec_ret(e, cffi_res, "isiip");
}

static evm_val_t evm_module_libc_fseek(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_res;
  evm_cffi_val_t cffi_args[3];
  evm_cffi_exec_param(e, cffi_args, "pii", argc, v);
  cffi_res.i32 = fseek(cffi_args[0].p, cffi_args[1].i32, cffi_args[2].i32);
  return evm_cffi_exec_ret(e, cffi_res, "ipii");
}

static evm_val_t evm_module_libc_ftell(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_res;
  evm_cffi_val_t cffi_args[1];
  evm_cffi_exec_param(e, cffi_args, "p", argc, v);
  cffi_res.i32 = ftell(cffi_args[0].p);
  return evm_cffi_exec_ret(e, cffi_res, "ip");
}

static evm_val_t evm_module_libc_fflush(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
  evm_cffi_val_t cffi_res;
  evm_cffi_val_t cffi_args[1];
  evm_cffi_exec_param(e, cffi_args, "p", argc, v);
  cffi_res.i32 = fflush(cffi_args[0].p);
  return evm_cffi_exec_ret(e, cffi_res, "ip");
}


void evm_module_libc(evm_t *e) {
  evm_val_t obj = evm_object_create(e);
  evm_prop_set(e, obj, "fopen", evm_mk_native(e, evm_module_libc_fopen, "fopen", 2));
  evm_prop_set(e, obj, "fclose", evm_mk_native(e, evm_module_libc_fclose, "fclose", 1));
  evm_prop_set(e, obj, "fread", evm_mk_native(e, evm_module_libc_fread, "fread", 4));
  evm_prop_set(e, obj, "fwrite", evm_mk_native(e, evm_module_libc_fwrite, "fwrite", 4));
  evm_prop_set(e, obj, "fseek", evm_mk_native(e, evm_module_libc_fseek, "fseek", 3));
  evm_prop_set(e, obj, "ftell", evm_mk_native(e, evm_module_libc_ftell, "ftell", 1));
  evm_prop_set(e, obj, "fflush", evm_mk_native(e, evm_module_libc_fflush, "fflush", 1));
  evm_module_add(e, "libc", obj);
}
#endif
