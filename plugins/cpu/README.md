---
title: Plugin: CPU Microcode
---

## Introduction

This plugin reads the sysfs attributes associated with CPU microcode.
It displays a read-only value of the CPU microcode version loaded onto
the physical CPU at fwupd startup.

## GUID Generation

These devices add extra instance IDs from the CPUID values, e.g.

* `CPUID\PRO_0&FAM_06` (only-quirk)
* `CPUID\PRO_0&FAM_06&MOD_0E`
* `CPUID\PRO_0&FAM_06&MOD_0E&STP_3`

## Quirk Use

This plugin uses the following plugin-specific quirks:

### CpuMitigationsRequired

Mitigations required for this specific CPU. Valid values are:

* `gds`

Since: 1.9.4

* `sinkclose`

Since: 2.0.2

### CpuSinkcloseMicrocodeVersion

Minimum version of microcode to mitigate the `sinkclose` vulnerability.

Since: 2.0.2

## External Interface Access

This plugin requires no extra access.

## Security Checks

### AMD RDRAND/RDSEED Erratum (SB-7055)

The plugin includes a runtime test for AMD Security Bulletin SB-7055, which affects
certain AMD processors where concurrent use of RDRAND and RDSEED instructions may
cause system instability or incorrect random number generation.

The test spawns two threads that concurrently execute:
* RDRAND instruction with 16-bit output
* RDSEED instruction with 16-bit output

Each thread performs 100,000 iterations. If the system has the vulnerability, the test
may hang, crash, or return an error. On systems without the vulnerability, the test
completes successfully.

This check is only performed on AMD CPUs and is classified as HSI level 2 (Important).

Since: 2.0.9

## Version Considerations

This plugin has been available since fwupd version `1.4.0`.
