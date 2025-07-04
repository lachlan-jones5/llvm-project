// NOTE: Assertions have been autogenerated by utils/update_cc_test_checks.py
// REQUIRES: riscv-registered-target
// RUN: %clang_cc1 -triple riscv64 -target-feature +v \
// RUN:   -target-feature +zvfh -disable-O0-optnone  \
// RUN:   -emit-llvm %s -o - | opt -S -passes=mem2reg | \
// RUN:   FileCheck --check-prefix=CHECK-ZVF %s

// RUN: not %clang_cc1 -triple riscv64 -target-feature +v \
// RUN:   -target-feature +zvfhmin -emit-llvm-only %s 2>&1 | \
// RUN:   FileCheck %s --check-prefix=CHECK-ZVFHMIN-ERR

#include <riscv_vector.h>

// CHECK-ZVF-LABEL: @test_vfadd_vv_f16m1(
// CHECK-ZVF-NEXT:  entry:
// CHECK-ZVF-NEXT:    [[TMP0:%.*]] = call <vscale x 4 x half> @llvm.riscv.vfadd.nxv4f16.nxv4f16.i64(<vscale x 4 x half> poison, <vscale x 4 x half> [[OP1:%.*]], <vscale x 4 x half> [[OP2:%.*]], i64 [[VL:%.*]])
// CHECK-ZVF-NEXT:    ret <vscale x 4 x half> [[TMP0]]
//

// CHECK-ZVFHMIN-ERR: builtin requires at least one of the following extensions: zvfh

vfloat16m1_t test_vfadd_vv_f16m1(vfloat16m1_t op1, vfloat16m1_t op2, size_t vl) {
  return __riscv_vfadd(op1, op2, vl);
}
