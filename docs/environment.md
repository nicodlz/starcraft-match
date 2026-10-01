# Initial environment inspection

Inspected 2026-10-01. The starting directory was empty, without Git history,
AGENTS.md or an executable. The executable search was restricted to this workspace,
three levels deep; unrelated personal directories were not scanned.

Host: Ubuntu 24.04.4 LTS, x86_64, Linux 6.8.0-136-generic.

| Tool | Observed availability | Role |
| --- | --- | --- |
| Python | 3.12.3; standard library, no pip | PE reader, JSON catalog, CLI, tests |
| GCC / G++ | 13.3.0 | Native candidate truth-table tests |
| Clang / Clang++ | 18.1.3 | Windows i686 COFF scaffold; no SDK needed for this function |
| CMake | 3.28.3 | Available; unnecessary for isolated compiler invocations |
| GNU objdump | Binutils 2.42 | Original and candidate x86 disassembly |
| LLVM tools | Versioned `llvm-objdump-18`, `llvm-readobj-18`, `llvm-objcopy-18`, etc. | Optional PE/COFF investigation |
| Git | 2.43.0 | Source tracking and local publication guard |
| Ghidra / analyzeHeadless | Not found in PATH or /opt | Optional function discovery and decompilation |
| radare2 / rizin | Not found in PATH | Optional alternative analysis |
| Java | Not found in PATH; /usr/lib/jvm absent | Required by a future Ghidra installation |
| Wine | Not found in PATH | Historical Windows compiler execution / later differential tests |
| Ninja | Not found in PATH | Not required |
| Historic MSVC | Not found | Exact matching investigation |

No optional tools were installed. Python, Clang and objdump suffice for the working
analysis → isolated compile → byte/disassembly comparison primitive. `make` is a
convenience layer; each command can also be run directly.

Following the user's explicit download request, the competition distribution was
retrieved and only its executable extracted. See [binary provenance](binary-provenance.md).
