#ifndef _SLE_PRINTER_SLE_H_
#define _SLE_PRINTER_SLE_H_

#include <iomanip>

#include "SLE.h"

class PrinterSLE {
 public:
  static void PrintSLE(const SLE& system);
  static void PrintParallelResultSLE(const SLE& system);
  static void PrintSerialResultSLE(const SLE& system);
};

#endif  // _SLE_PRINTER_SLE_H_