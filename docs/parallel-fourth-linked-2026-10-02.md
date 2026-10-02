# Fourth session: first standard-linked continuation

Two additional complete C contributions match the pinned executable after genuine external-symbol linking: **86 bytes**. The validated integration snapshot contains **392 exact functions / 22,831 bytes**, including the other sessions’ already merged work.

| Function | Whole contribution | Method |
| --- | ---: | --- |
| [00452320](functions/00452320.md) | 41 / 41 bytes | MSVC C plus canonical external-only GNU ld |
| [004C2EC0](functions/004C2EC0.md) | 45 / 45 bytes | MSVC C plus canonical external-only GNU ld |

The coordinator reused the linker adapter already merged by the other session. The default isolated-COFF extractor still rejects unresolved relocations. These contributions use explicit per-function linking records, reviewed external code addresses and complete compiler-generated sections; the linker consumes no original code bytes. Defined helpers cannot be rebound, and contexts are excluded explicitly. This evidence is separate from zero-relocation COFF matching.

The coordinator freshly reviewed the pinned SHA-256, complete entry/body boundaries, callers, memory access widths and actual dependency contracts, then independently compiled the public sources and inspected their new canonical reports. The imported Storm implementation is absent; its observed stack cleanup is explicitly inferred. Neither dependency implementations nor context helpers count as recovered functions.

Validation: local `make`, full local `make proof`, source-only Clang compilation and the publication guard. Similarity/semantic metrics remain null. No instruction copies, assembly, post-build patches, byte normalization, selected subsequences, original-process execution or whole-program linking is claimed. The standard linker’s full virtual contribution extent is established independently of original size; file-alignment padding is outside that compiler contribution.

The bounded rounds retain disjoint addresses and a cumulative20-variant limit. Other linked candidates with incompatible private call contracts remain private and nonexact.

A second bounded continuation adds five independently rebuilt complete contributions: **371 bytes**. The resulting integration snapshot contains **397 exact functions / 23,202 bytes**.

| Function | Whole contribution | Reviewed contract |
| --- | ---: | --- |
| [00471010](functions/00471010.md) | 53 / 53 bytes | Private BL byte input, external import thunk |
| [00421730](functions/00421730.md) | 54 / 54 bytes | Private EAX input, reviewed no-argument helper |
| [00470DB0](functions/00470DB0.md) | 54 / 54 bytes | Two stack byte inputs with RET8 |
| [00499D00](functions/00499D00.md) | 54 / 54 bytes | ECX context, two stack arguments, reviewed helper RET4 |
| [004CB5B0](functions/004CB5B0.md) | 156 / 156 bytes | Private EDX input, two external data relocations |

The last contribution retains the unsigned byte index wrap and unsigned 32-bit mask behavior. Its compiler-emitted unreferenced fill helper and hypothetical caller are separately inventoried and excluded. Valid input/data extents remain a precondition; corrupt-input behavior has not been established by original execution. Imported implementations remain unavailable. All seven new functions together account for **457 bytes**, using the shared linker without changing compiler profiles or matching tooling.
