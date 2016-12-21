
#include "private/json_p.h"

///////////////////////////////////////////////////////////////////////////////
binn_t json_to_binn(const char* const json_str) {
  json_t *base;
  //json_error_t error;
  binn_t item;

  base = json_loads(json_str, 0, NULL);
  if (!base) return BINN_INVALID;

  item = json_obj_to_binn(base);

  json_decref(base);
  return item;
}